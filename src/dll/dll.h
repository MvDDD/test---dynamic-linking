#ifndef DLL_TYPES_H
#define DLL_TYPES_H

#ifdef _WIN32
    #include <windows.h>
    typedef HMODULE dll_t;

    #ifdef __GNUC__
        #define exposed __declspec(dllexport) __stdcall
        #define exposedType __stdcall
    #elif defined (__TINYC__)
        #define exposed
        #define exposedType __stdcall
    #else
        #define exposed __declspec(dllexport) __stdcall
        #define exposedType __stdcall
    #endif

    #define dlopen(p, a) LoadLibraryA(p)
    #define dlclose(p) FreeLibrary(p)
    #define dlsym(p, f) GetProcAddress(p, f)
    #define RTLD_LAZY
    #define RTLD_NOW

#elif defined(__unix__) || defined(__unix) || defined(unix) || defined(linux) || defined(__linux__)
    #include <dlfcn.h>
    typedef void* dll_t;

    #ifndef __stdcall
      #define __stdcall
    #endif

    #define exposed
    #define exposedType __stdcall

#else
    #error unsupported os
#endif

#endif // DLL_TYPES_H
