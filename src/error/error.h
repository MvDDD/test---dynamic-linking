#ifndef ERROR_H
#define ERROR_H

#include "dll/dll.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "libver.h"
LIBVER_H(ERROR_H, ERROR_MAIN_C, "1.6.3")
LIBVER_H(ERROR_H, ERROR_DLL_C, "1.6.3")

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define __POSITION__ (__FILE__ ":" TOSTRING(__LINE__))

typedef void(*voidfunc)(void);

typedef enum {
    ERR_ALLOC_ERROR = 0,
    ERR_CALLOC_ERROR,
    ERR_REALLOC_ERROR,
    ERR_FREE_ERROR,
    ERR_INTERN_HASHERROR,
    ERR_MISSING_PARAMETER,
    ERR_TOO_MANY_PARAMETERS,
    ERR_DLL_LOAD,
    ERR_TYPEERROR,
    ERR_MEMORY_LEAK,
    ERR_OOM,
} errorType;


typedef void *(exposedType *emalloc_t)(size_t);
typedef void *(exposedType *ecalloc_t)(size_t, size_t);
typedef void *(exposedType *erealloc_t)(void *, size_t);
typedef void  (exposedType *efree_t)(void *);
typedef void  (exposedType *error_t)(errorType, const char *msg, const char *position);
typedef void  (exposedType *eexit_t)(int);
typedef void  (exposedType *eregistercleanup_t)(voidfunc);
typedef void  (exposedType *bindCallBack_t)(emalloc_t, ecalloc_t, erealloc_t, efree_t, error_t, eexit_t, eregistercleanup_t);
typedef int   (exposedType *isBound_t)();

void ebind(bindCallBack_t bindCallBack);
void einit();

void *exposedType emalloc(size_t size);
void *exposedType ecalloc(size_t num, size_t size);
void *exposedType erealloc(void *pointer, size_t size); // fixed from realloc
void  exposedType efree(void *pointer);
void  exposedType error(errorType, const char *msg, const char *position);
void  exposedType eexit(int status);
void  exposedType eregistercleanup(voidfunc func);
/*
#define malloc emalloc
#define calloc ecalloc
#define realloc erealloc
#define free efree
#define exit eexit
*/
#endif // ERROR_H
