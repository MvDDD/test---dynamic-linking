#include "error.h"


#include "libver.h"

LIBVER_C(ERROR_DLL_C, "1.6.3")

// Global function pointers
emalloc_t   p_emalloc  = NULL;
ecalloc_t   p_ecalloc  = NULL;
erealloc_t  p_erealloc = NULL;
efree_t     p_efree    = NULL;
error_t     p_error    = NULL;
eexit_t     p_eexit    = NULL;


static int isErrBound = 0;

exposed int getIsErrBound(){
	return isErrBound;
}

exposed void bindCallBack(emalloc_t MALLOC, ecalloc_t CALLOC, erealloc_t REALLOC, efree_t FREE, error_t ERR, eexit_t EXIT) {
	p_emalloc  = MALLOC;
	p_ecalloc  = CALLOC;
	p_erealloc = REALLOC;
	p_efree    = FREE;
	p_error    = ERR;
	p_eexit    = EXIT;
	isErrBound = 1;
}



void exposedType error(errorType err, const char *msg, const char *position){
	p_error(err, msg, position);
}
void exposedType efree(void *pointer){
	p_efree(pointer);
}
void * exposedType emalloc(size_t size){
	return p_emalloc(size);
}
void * exposedType ecalloc(size_t num, size_t size){
	return p_ecalloc(num, size);
}
void * exposedType erealloc(void *pointer, size_t size){
	return p_erealloc(pointer,size);
}
void exposedType eexit(int status){
	p_eexit(status);
}