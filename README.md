PS C:/.../test - dynamic linking> py make.py

main:
        gcc -m32 -std=c99 -O0 -Isrc -DNDEBUG -c src/main/main.c -o build/src/main/main.o
        gcc -m32 -std=c99 -O0 -Isrc -DNDEBUG -c src/type/type.c -o build/src/type.o
        gcc -m32 -std=c99 -O0 -Isrc -DNDEBUG -c src/error/error_main.c -o build/src/error_main.o
        gcc -m32 -std=c99 -O0 -Isrc -DNDEBUG build/src/main/main.o build/src/type.o build/src/error_main.o -o build/build/main.exe
lib -> lib.lib: # main.dll
        gcc -m32 -std=c99 -O0 -Isrc -DNDEBUG -c src/type/type.c -o build/src/type.o
        gcc -m32 -std=c99 -O0 -Isrc -DNDEBUG -c src/error/error_dll.c -o build/src/error.o
        gcc -m32 -std=c99 -O0 -Isrc -DNDEBUG -c src/include/lib/lib.c -o build/src/include/lib/lib.o
        gcc -m32 -std=c99 -O0 -Isrc -DNDEBUG -shared -Wl,--output-def,build/build/include/lib/lib.dll.def -Wl,--kill-at build/src/type.o build/src/error.o build/src/include/lib/lib.o -o build/build/include/lib/lib.dll
lib -> lib.main: # lib.dll
        gcc -m32 -std=c99 -O0 -Isrc -DNDEBUG -c src/type/type.c -o build/src/type.o
        gcc -m32 -std=c99 -O0 -Isrc -DNDEBUG -c src/error/error_dll.c -o build/src/error.o
        gcc -m32 -std=c99 -O0 -Isrc -DNDEBUG -c src/include/main/main.c -o build/src/include/main/main.o
        gcc -m32 -std=c99 -O0 -Isrc -DNDEBUG -shared -Wl,--output-def,build/build/include/main/main.dll.def -Wl,--kill-at build/src/type.o build/src/error.o build/src/include/main/main.o -o build/build/include/main/main.dll
dbg -> dbg.libver: # tool to read lib versions stored by libver.h
        gcc -m32 -std=c99 -O0 -Isrc -DNDEBUG libver.c -o build/build/libver.exe


starting:

main:
In file included from src/main/main.c:5:
src/type/type.h: In function 'eregistercleanup':
src/type/type.h:7:21: error: storage class specified for parameter 'Type'
    7 | typedef struct Type Type;
      |                     ^~~~
src/type/type.h:15:3: error: storage class specified for parameter 'Types'
   15 | } Types;
      |   ^~~~~
src/type/type.h:20:3: error: storage class specified for parameter 'string_t'
   20 | } string_t;
      |   ^~~~~~~~
src/type/type.h:25:5: error: expected specifier-qualifier-list before 'string_t'
   25 |     string_t *_string;
      |     ^~~~~~~~
src/type/type.h:26:3: error: storage class specified for parameter 'Type_data'
   26 | } Type_data;
      |   ^~~~~~~~~
src/type/type.h:28:9: error: expected identifier or '(' before '{' token
   28 | typedef {
      |         ^
src/type/type.h:31:3: error: expected declaration specifiers before 'Type'
   31 | } Type;
      |   ^~~~
src/type/type.h:33:28: error: expected declaration specifiers or '...' before '*' token
   33 | typedef Type  (exposedType *Type_bin_f) (Type, Type);
      |                            ^
src/type/type.h:34:28: error: expected declaration specifiers or '...' before '*' token
   34 | typedef Type  (exposedType *Type_un_f) (Type);
      |                            ^
src/type/type.h:35:13: error: expected '=', ',', ';', 'asm' or '__attribute__' before '*' token
   35 | typedef Type* (exposedType *Type_lib_f) (Type*, uint32_t);
      |             ^
src/type/type.h:36:13: error: expected '=', ',', ';', 'asm' or '__attribute__' before '*' token
   36 | typedef Type* (exposedType *Type_None_f) (void);
      |             ^
src/type/type.h:38:1: error: expected declaration specifiers before 'Type'
   38 | Type create_int(int value);
      | ^~~~
src/type/type.h:39:1: error: expected declaration specifiers before 'Type'
   39 | Type* create_intptr(int value);
      | ^~~~
src/type/type.h:40:1: error: expected declaration specifiers before 'Type'
   40 | Type create_float(float value);
      | ^~~~
src/type/type.h:41:1: error: expected declaration specifiers before 'Type'
   41 | Type create_string(const char* string);
      | ^~~~
src/type/type.h:42:1: error: expected declaration specifiers before 'Type'
   42 | Type parseTypeString(const char* instring);
      | ^~~~
src/type/type.h:44:14: error: expected declaration specifiers or '...' before 'Type'
   44 | int cast_int(Type type);
      |              ^~~~
src/type/type.h:45:18: error: expected declaration specifiers or '...' before 'Type'
   45 | float cast_float(Type type);
      |                  ^~~~
src/type/type.h:46:19: error: expected declaration specifiers or '...' before 'Type'
   46 | uint32_t cast_len(Type type);
      |                   ^~~~
src/type/type.h:47:16: error: expected declaration specifiers or '...' before 'Type'
   47 | char* cast_str(Type type);
      |                ^~~~
src/type/type.h:48:20: error: expected declaration specifiers or '...' before 'Type'
   48 | char* cast_charptr(Type type);
      |                    ^~~~
src/type/type.h:50:19: error: expected declaration specifiers or '...' before 'Type'
   50 | void destroy_type(Type type);
      |                   ^~~~
src/type/type.h:52:16: error: expected declaration specifiers or '...' before 'Type'
   52 | int print_type(Type type);
      |                ^~~~
src/main/main.c:10:1: error: parameter 'LoadedDlls' is initialized
   10 | dll_t LoadedDlls[100] = {NULL};
      | ^~~~~
src/main/main.c:11:24: error: expected '=', ',', ';', 'asm' or '__attribute__' before '{' token
   11 | dll_t addDLL(dll_t dll){
      |                        ^
src/main/main.c:21:19: error: expected '=', ',', ';', 'asm' or '__attribute__' before '{' token
   21 | void DLL_cleanup(){
      |                   ^
src/main/main.c:29:34: error: expected '=', ',', ';', 'asm' or '__attribute__' before '{' token
   29 | int main(int argc, char *argv[]) {
      |                                  ^
In file included from src/main/main.c:1:
src/error/error.h:50:19: error: old-style parameter declarations in prototyped function definition
   50 | void  exposedType eregistercleanup(void (*func)())
      |                   ^~~~~~~~~~~~~~~~
src/main/main.c:81: error: expected '{' at end of input


done with errors
