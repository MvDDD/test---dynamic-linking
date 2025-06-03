#include "error.h"
#include <stdlib.h>
#include "libver.h"

LIBVER_C(ERROR_MAIN_C, "1.6.4")

static void **hashtable = NULL;
static size_t hashtable_length = 0;
static size_t hashtable_usage = 0;
typedef void(*voidfunc)(void);
voidfunc cleanupfuncs[100];
static size_t cleanupLength = 0;

#define ONE ((void *)1)

void einit() {
	hashtable = (void **)calloc(32, sizeof(void *));
	hashtable_length = 32;
	hashtable_usage = 0;
}

void eregistercleanup(voidfunc func){
	if (cleanupLength > 100-2){
		error(ERR_OOM, "too many cleanups", __POSITION__);
	}
	cleanupfuncs[cleanupLength++]=func;
}

static void expandError();
static char *getErrString(errorType err);


static void addError(void *pointer){
	expandError();
	uintptr_t hash = (uintptr_t)pointer % hashtable_length;
	while (1){
		if (hashtable[hash] == NULL || hashtable[hash] == ONE){
			break;
		}
		hash = (hash + 1) % hashtable_length;;
	}
	hashtable[hash] = pointer;
	hashtable_usage++;
}

static inline void expandError() {
	if ((hashtable_usage*100)/hashtable_length > 75){
		void **oldhashtable = hashtable;
		size_t oldhashtable_length = hashtable_length;
		
		size_t newhashtable_length = oldhashtable_length*2;
		void **newhashtable = (void **)calloc(newhashtable_length, sizeof(void *));

		if (newhashtable == NULL){
			error(ERR_INTERN_HASHERROR, "failed to expand hashtable (OOM)", __POSITION__);
		}

		hashtable = newhashtable;
		hashtable_length = newhashtable_length;

		for (size_t i = 0; i < oldhashtable_length; i++){
			if (oldhashtable[i] != NULL && oldhashtable[i] != ONE){
				uintptr_t hash = (uintptr_t)oldhashtable[i] % hashtable_length;
				while (newhashtable[hash] != NULL) {
					hash = (hash + 1) % hashtable_length;
				}
				newhashtable[hash] = oldhashtable[i];
			}
		}
		free(oldhashtable);
	}
}


static void deleteError(void *pointer){
	uintptr_t hash = (uintptr_t)pointer % hashtable_length;
	while (1){
		if (hashtable[hash] == pointer){
			break;
		}
		if (hashtable[hash] == NULL){
			error(ERR_INTERN_HASHERROR, "allocation hash not found in hashtable", __POSITION__);
		}
		hash = (hash + 1) % hashtable_length;
	}
	hashtable[hash] = ONE;
	hashtable_usage--;
}

static int hasError(void *pointer){
	uintptr_t hash = (uintptr_t)pointer % hashtable_length;
	while (1){
		if (hashtable[hash] == pointer){
			return 1;
		}
		if (hashtable[hash] == NULL){
			return 0;
		}
		hash = (hash + 1) % hashtable_length;
	}
}

static void ERROR_FREE_ALL(){
	printf("number of stray pointers: %zu\n", hashtable_usage);
	for (size_t i = 0; i < hashtable_length; i++){
		if (hashtable[i] != NULL && hashtable[i] != ONE){
			free(hashtable[i]);
			hashtable[i] = NULL;
		}
	}
	free(hashtable);
}


void ebind(bindCallBack_t bindCallBack) {
	if (bindCallBack == NULL){
		error(ERR_DLL_LOAD, "bindCallBack is NULL", __POSITION__);
	}
	bindCallBack(emalloc, ecalloc, erealloc, efree, error, eexit, eregistercleanup);
}
void exposedType error(errorType type, const char *msg, const char *position) {
	printf("\x1b[31mERROR: %s :%s\n\t%s\n\x1b[0m", getErrString(type), position, msg);

}
void exposedType efree(void *pointer) {
	deleteError(pointer);
	free(pointer);
}
void *exposedType emalloc(size_t size) {
	void *pointer = malloc(size);
	addError(pointer);
	return pointer;
}

void *exposedType ecalloc(size_t num, size_t size) {
	void *pointer = calloc(num, size);
	if (pointer == NULL){
		error(ERR_CALLOC_ERROR, "allocation hash not found in hashtable", __POSITION__);
	}
	addError(pointer);
	return pointer;
}

void *exposedType erealloc(void *pointer, size_t size) {
	if (pointer == NULL){
		return emalloc(size);
	} else {
		deleteError(pointer);
	}
	if (size > 0){
		pointer = realloc(pointer, size);
		if (pointer == NULL) {
			error(ERR_ALLOC_ERROR, "failed to allocate memory", __POSITION__);
		}
		addError(pointer);
		return pointer;
	} else {
		efree(pointer);
		return NULL;
	}
}

void exposedType eexit(int status) {
	for (size_t i = 0; i < cleanupLength; i++){
		cleanupfuncs[i]();
	}
	ERROR_FREE_ALL();
	exit(status);
}

static char *getErrString(errorType err){
	switch (err) {
	case ERR_ALLOC_ERROR:
		return "ERR_ALLOC_ERROR";
	case ERR_CALLOC_ERROR:
		return "ERR_CALLOC_ERROR";
	case ERR_REALLOC_ERROR:
		return "ERR_REALLOC_ERROR";
	case ERR_FREE_ERROR:
		return "ERR_FREE_ERROR";
	case ERR_INTERN_HASHERROR:
		return "ERR_INTERN_HASHERROR";
	case ERR_MISSING_PARAMETER:
		return "ERR_MISSING_PARAMETER";
	case ERR_TOO_MANY_PARAMETERS:
		return "ERR_TOO_MANY_PARAMETERS";
	case ERR_DLL_LOAD:
		return "ERR_DLL_LOAD";
	case ERR_TYPEERROR:
		return "ERR_TYPEERROR";
	case ERR_MEMORY_LEAK:
		return "ERR_MEMORY_LEAK";
	case ERR_OOM:
		return "ERR_OOM";
	default:
		return "ERR_UNKNOWN_ERROR";
	}
}
