#include "error/error.h"
#include <stdio.h>
#include <string.h>
#include "dll/dll.h"
#include "type/type.h"




dll_t LoadedDlls[100] = {NULL};
dll_t addDLL(dll_t dll){
    for (uint8_t i = 0; i < 100; i++){
        if (LoadedDlls[i] == NULL){
            LoadedDlls[i] = dll;
            return dll;
        }
    }
    error(ERR_DLL_LOAD, "ERR_TOO_MANY_DLLS", __POSITION__);
}

void DLL_cleanup(){
    for (uint8_t i = 0; i < 100; i++){
        if (LoadedDlls[i] != NULL){
            dlclose(LoadedDlls[i]);
        }
    }
}

int main(int argc, char *argv[]) {
    einit();
    eregistercleanup(DLL_cleanup);
    if (argc < 3){
        error(ERR_MISSING_PARAMETER, "not enough arguments", __POSITION__);
    }

    char *name = (char *)ecalloc(1000, sizeof(char));
    size_t offset = 0;
    offset += sprintf(name + offset, "include/");
    offset += sprintf(name + offset, "%s/", argv[1]);
    offset += sprintf(name + offset, "%s", argv[1]);
    #ifdef __UNIX__
    offset += sprintf(name + offset, ".so");
    #else
    offset += sprintf(name + offset, ".dll");
    #endif
    name = (char *)erealloc(name, strlen(name) + 1);

    dll_t main = addDLL(dlopen(name, RTLD_LAZY));
 
    if (main == NULL){
        char a[100];
        sprintf(a, "failed to load dll from %s", name);
        error(ERR_DLL_LOAD, a, __POSITION__);
    }
    efree(name);

    bindCallBack_t bindCallBack = (bindCallBack_t)dlsym(main, "bindCallBack");
    isBound_t isErrBound = (isBound_t)dlsym(main, "bindCallBack");
    if (bindCallBack == NULL || isErrBound == NULL){
        char a[100];
        sprintf(a, "failed to load errorContext of %s\n\tis error_dll.c included?", name);
        error(ERR_DLL_LOAD, a, __POSITION__);
    }
    ebind(bindCallBack);
    if (isErrBound() == 0){
        char a[100];
        sprintf(a, "failed to set errorContext of %s\n\tare error_dll.c and error_main.c the same version? (libver <library / executable / object file>)", name);
        error(ERR_DLL_LOAD, a, __POSITION__);
    }

    Type_lib_f mainfunc = (Type_lib_f)dlsym(main, argv[2]);
    Type *input = emalloc(1 * sizeof(Type));
    input[0] = create_string("hello");
    Type *result = mainfunc(input, 1);
    if (result == NULL){
        printf("returned NULL\n");
    }
    efree(input);
    eexit(0);  
}
