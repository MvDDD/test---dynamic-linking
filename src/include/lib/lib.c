// mylib.c
#include "dll/dll.h"
#include "type/type.h"
#include <stdio.h>

exposed Type *main(){
    printf("hello from DLL\n");
    return NULL;
}


createDoc(Iadd, "(int a, int b) -> int a + b")
createFunction(Iadd, 2, _int, _int)
    int a = cast_int(argv[0]);
    int b = cast_int(argv[1]);
    return create_intptr(a + b);
endfunction

createDoc(Isub, "(int a, int b) -> int a - b")
createFunction(Isub, 2, _int, _int)
    int a = cast_int(argv[0]);
    int b = cast_int(argv[1]);
    return create_intptr(a - b);
endfunction


createDoc(Imult, "(int a, int b) -> int a * b")
createFunction(Imult, 2, _int, _int)
    int a = cast_int(argv[0]);
    int b = cast_int(argv[1]);
    return create_intptr(a * b);
endfunction


createDoc(Idiv, "(int a, int b) -> int a * b")
createFunction(Idiv, 2, _int, _int)
    int a = cast_int(argv[0]);
    int b = cast_int(argv[1]);
    if (b == 0) return create_intptr(-1);
    return create_intptr(a / b);
endfunction
