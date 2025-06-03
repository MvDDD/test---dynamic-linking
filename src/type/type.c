#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "type.h"

#include "libver.h"

LIBVER_C(TYPE_C, "1.6.3")

static bool is_int(const char *s) {
    if (!s || !*s) return false;
    char *p = (char *)s;
    while (*p) {
        if (!isdigit(*p)) return false;
        p++;
    }
    return true;
}

static bool is_float(const char *s) {
    if (!s || !*s) return false;
    bool seen_dot = false;
    char *p = (char *)s;
    while (*p) {
        if (*p == '.') {
            if (seen_dot) return false;
            seen_dot = true;
        } else if (!isdigit(*p)) {
            return false;
        }
        p++;
    }
    return seen_dot;
}

static bool is_identifier(const char *s) {
    if (!s || !*s) return false;
    if (!isalpha(*s) && *s != '_') return false;
    char *p = (char *)(s + 1);
    while (*p) {
        if (!isalnum(*p) && *p != '_') return false;
        p++;
    }
    return true;
}


Type create_int(int value) {
    Type val = {
        .type = _int,
        .data = { ._int = value }
    };
    return val;
}

Type *create_intptr(int value) {
    Type *val = emalloc(sizeof(Type));
    val->type = _int;
    val->data._int = value;
    return val;
}

Type create_float(float value) {
    Type val = {
        .type = _float,
        .data = { ._float = value }
    };
    return val;
}

Type create_string(const char *string) {
    Type val = { .type = _string, .data._string = NULL };

    val.data._string = emalloc(sizeof(string_t));
    if (!val.data._string) {
        val.type = ANY;
        return val;
    }

    uint32_t len = (uint32_t)strlen(string);
    val.data._string->data = emalloc(len + 1);
    if (!val.data._string->data) {
        free(val.data._string);
        val.data._string = NULL;
        val.type = ANY;
        return val;
    }

    strcpy(val.data._string->data, string);
    val.data._string->length = len;
    return val;
}


void destroy_type(Type type) {
    if (type.type == _string && type.data._string) {
        efree(type.data._string->data);
        efree(type.data._string);
    }
}

int cast_int(Type type) {
    return type.data._int;
}

float cast_float(Type type) {
    return type.data._float;
}

uint32_t cast_len(Type type) {
    return type.data._string ? type.data._string->length : 0;
}

char *cast_str(Type type) {
    return type.data._string ? type.data._string->data : NULL;
}

char *cast_charptr(Type type) {
    uint32_t length = cast_len(type);
    char *string = emalloc(length + 1);
    memcpy(string, type.data._string->data, length);
    string[length] = '\0';
    return string;
}

Type parseTypeString(const char *instring) {
    if (is_int(instring)) {
        return create_int(atoi(instring));
    } else if (is_float(instring)) {
        return create_float((float)atof(instring));
    } else if (is_identifier(instring)) {
        return create_string(instring);
    } else {
        Type t = { .type = ANY };
        return t;
    }
}

int print_type(Type type) {
    switch (type.type) {
    case _int:
        return printf("%d\n", type.data._int);
    case _float:
        return printf("%f\n", type.data._float);
    case _string:
        return printf("%s\n", type.data._string->data);
    }
}