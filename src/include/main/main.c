#include <stdio.h>

#include "dll/dll.h"
#include "error/error.h"
#include "type/type.h"


exposed Type *main(Type *argv, uint32_t argc){
    printf("%d\n", argc);
    printf("%d\n", argv[0].type);
    char *string = cast_str(argv[0]);
    printf("%s\n", string);
    return NULL;
}