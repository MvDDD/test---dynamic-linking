#ifndef TYPE_H
#define TYPE_H

#include "dll/dll.h"
#include <stdint.h>

typedef struct Type Type;

typedef enum {
    _int,
    _float,
    _string,
    NONE,
    ANY,
} Types;

typedef struct {
    uint32_t length;
    char *data;
} string_t;

typedef union {
    int _int;
    float _float;
    string_t *_string;
} Type_data;

typedef {
    Types type;
    Type_data data;
} Type;

typedef Type  (exposedType *Type_bin_f) (Type, Type);
typedef Type  (exposedType *Type_un_f) (Type);
typedef Type* (exposedType *Type_lib_f) (Type*, uint32_t);
typedef Type* (exposedType *Type_None_f) (void);

Type create_int(int value);
Type* create_intptr(int value);
Type create_float(float value);
Type create_string(const char* string);
Type parseTypeString(const char* instring);

int cast_int(Type type);
float cast_float(Type type);
uint32_t cast_len(Type type);
char* cast_str(Type type);
char* cast_charptr(Type type);

void destroy_type(Type type);

int print_type(Type type);

#ifdef ERROR_H

#define createFunction(name, numargs, ...)  \
exposed Type *name(Type *argv, uint32_t argc) { \
	{ \
		if (argc < numargs) { \
			char a[100]; \
			sprintf(a, "function expects %u params, but got %u", (unsigned)numargs, (unsigned)argc); \
			error(ERR_MISSING_PARAMETER, a, __POSITION__); \
		} \
		if (argc > numargs) { \
			char a[100]; \
			sprintf(a, "function expects %u params, but got %u", (unsigned)numargs, (unsigned)argc); \
			error(ERR_TOO_MANY_PARAMETERS, a, __POSITION__); \
		} \
		const Types expected_types[numargs] = { __VA_ARGS__ }; \
		int err = 0; \
		char *errors = (char *)emalloc(1); \
		for (uint32_t i = 0; i < numargs; i++) { \
			if (expected_types[i] == ANY){ \
				continue; \
			} \
			if (argv[i].type != expected_types[i]) { \
				errors = (char *)erealloc(errors, err + 100); \
				err += sprintf(errors+err, "type mismatch at argument %u: expected %d, got %d\n", i, expected_types[i], argv[i].type); \
			} \
		} \
		if (err){ \
			errors = (char *)erealloc(errors, err+1); \
			errors[err] = '\0'; \
			error(ERR_TYPEERROR, errors, __POSITION__); \
		} \
	}

#define endfunction {return NULL;}}

#define createDoc(function, footprint)\
	exposed char *__doc##function (){\
		return footprint;\
	}

#endif

#endif // TYPE_H
