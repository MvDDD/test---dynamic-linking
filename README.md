```
PS C:/.../test - dynamic linking> py make.py
main:
        gcc -m32 -std=c99 -O0 -Isrc -DNDEBUG -c src/main/main.c -o build/src/main/main.o
        gcc -m32 -std=c99 -O0 -Isrc -DNDEBUG -c src/type/type.c -o build/src/type.o
        gcc -m32 -std=c99 -O0 -Isrc -DNDEBUG -c src/error/error_main.c -o build/src/error_main.o
        gcc -m32 -std=c99 -O0 -Isrc -DNDEBUG build/src/main/main.o build/src/type.o build/src/error_main.o -o build/build/main.exe
lib -> lib.lib:
        gcc -m32 -std=c99 -O0 -Isrc -DNDEBUG -c src/type/type.c -o build/src/type.o
        gcc -m32 -std=c99 -O0 -Isrc -DNDEBUG -c src/error/error_dll.c -o build/src/error.o
        gcc -m32 -std=c99 -O0 -Isrc -DNDEBUG -c src/include/lib/lib.c -o build/src/include/lib/lib.o
        gcc -m32 -std=c99 -O0 -Isrc -DNDEBUG -shared -Wl,--output-def,build/build/include/lib/lib.dll.def -Wl,--kill-at build/src/type.o build/src/error.o build/src/include/lib/lib.o -o build/build/include/lib/lib.dll
lib -> lib.main:
        gcc -m32 -std=c99 -O0 -Isrc -DNDEBUG -c src/type/type.c -o build/src/type.o
        gcc -m32 -std=c99 -O0 -Isrc -DNDEBUG -c src/error/error_dll.c -o build/src/error.o
        gcc -m32 -std=c99 -O0 -Isrc -DNDEBUG -c src/include/main/main.c -o build/src/include/main/main.o
        gcc -m32 -std=c99 -O0 -Isrc -DNDEBUG -shared -Wl,--output-def,build/build/include/main/main.dll.def -Wl,--kill-at build/src/type.o build/src/error.o build/src/include/main/main.o -o build/build/include/main/main.dll
dbg -> dbg.libver:
        gcc -m32 -std=c99 -O0 -Isrc -DNDEBUG libver.c -o build/build/libver.exe


starting:

main:
In file included from src/main/main.c:5:
src/type/type.h:28:9: error: expected identifier or '(' before '{' token
   28 | typedef {
      |         ^
src/type/type.h:31:1: warning: useless type name in empty declaration
   31 | } Type;
      | ^
src/main/main.c: In function 'main':
src/main/main.c:72:38: error: invalid application of 'sizeof' to incomplete type 'Type'
   72 |     Type *input = emalloc(1 * sizeof(Type));
      |                                      ^~~~
src/main/main.c:73:10: error: invalid use of undefined type 'struct Type'
   73 |     input[0] = create_string("hello");
      |          ^
src/main/main.c:73:16: error: invalid use of incomplete typedef 'Type'
   73 |     input[0] = create_string("hello");
      |                ^~~~~~~~~~~~~
src/main/main.c:73:14: error: invalid use of incomplete typedef 'Type'
   73 |     input[0] = create_string("hello");
      |              ^


done with errors
PS C:\Users\markv\OneDrive\Desktop\git\singleFileProjects\C\test - dynamic linking> py make.py
main:
        gcc -m32 -std=c99 -O0 -Isrc -DNDEBUG -c src/main/main.c -o build/src/main/main.o
        gcc -m32 -std=c99 -O0 -Isrc -DNDEBUG -c src/type/type.c -o build/src/type.o
        gcc -m32 -std=c99 -O0 -Isrc -DNDEBUG -c src/error/error_main.c -o build/src/error_main.o
        gcc -m32 -std=c99 -O0 -Isrc -DNDEBUG build/src/main/main.o build/src/type.o build/src/error_main.o -o build/build/main.exe
lib -> lib.lib:
        gcc -m32 -std=c99 -O0 -Isrc -DNDEBUG -c src/type/type.c -o build/src/type.o
        gcc -m32 -std=c99 -O0 -Isrc -DNDEBUG -c src/error/error_dll.c -o build/src/error.o
        gcc -m32 -std=c99 -O0 -Isrc -DNDEBUG -c src/include/lib/lib.c -o build/src/include/lib/lib.o
        gcc -m32 -std=c99 -O0 -Isrc -DNDEBUG -shared -Wl,--output-def,build/build/include/lib/lib.dll.def -Wl,--kill-at build/src/type.o build/src/error.o build/src/include/lib/lib.o -o build/build/include/lib/lib.dll
lib -> lib.main:
        gcc -m32 -std=c99 -O0 -Isrc -DNDEBUG -c src/type/type.c -o build/src/type.o
        gcc -m32 -std=c99 -O0 -Isrc -DNDEBUG -c src/error/error_dll.c -o build/src/error.o
        gcc -m32 -std=c99 -O0 -Isrc -DNDEBUG -c src/include/main/main.c -o build/src/include/main/main.o
        gcc -m32 -std=c99 -O0 -Isrc -DNDEBUG -shared -Wl,--output-def,build/build/include/main/main.dll.def -Wl,--kill-at build/src/type.o build/src/error.o build/src/include/main/main.o -o build/build/include/main/main.dll
dbg -> dbg.libver:
        gcc -m32 -std=c99 -O0 -Isrc -DNDEBUG libver.c -o build/build/libver.exe


starting:

main:
In file included from src/main/main.c:5:
src/type/type.h:31:3: error: conflicting types for 'Type'
   31 | } Type;
      |   ^~~~
src/type/type.h:7:21: note: previous declaration of 'Type' was here
    7 | typedef struct Type Type;
      |                     ^~~~


done with errors
PS C:\Users\markv\OneDrive\Desktop\git\singleFileProjects\C\test - dynamic linking> py make.py
main:
        gcc -m32 -std=c99 -O0 -Isrc -DNDEBUG -c src/main/main.c -o build/src/main/main.o
        gcc -m32 -std=c99 -O0 -Isrc -DNDEBUG -c src/type/type.c -o build/src/type.o
        gcc -m32 -std=c99 -O0 -Isrc -DNDEBUG -c src/error/error_main.c -o build/src/error_main.o
        gcc -m32 -std=c99 -O0 -Isrc -DNDEBUG build/src/main/main.o build/src/type.o build/src/error_main.o -o build/build/main.exe
lib -> lib.lib:
        gcc -m32 -std=c99 -O0 -Isrc -DNDEBUG -c src/type/type.c -o build/src/type.o
        gcc -m32 -std=c99 -O0 -Isrc -DNDEBUG -c src/error/error_dll.c -o build/src/error.o
        gcc -m32 -std=c99 -O0 -Isrc -DNDEBUG -c src/include/lib/lib.c -o build/src/include/lib/lib.o
        gcc -m32 -std=c99 -O0 -Isrc -DNDEBUG -shared -Wl,--output-def,build/build/include/lib/lib.dll.def -Wl,--kill-at build/src/type.o build/src/error.o build/src/include/lib/lib.o -o build/build/include/lib/lib.dll
lib -> lib.main:
        gcc -m32 -std=c99 -O0 -Isrc -DNDEBUG -c src/type/type.c -o build/src/type.o
        gcc -m32 -std=c99 -O0 -Isrc -DNDEBUG -c src/error/error_dll.c -o build/src/error.o
        gcc -m32 -std=c99 -O0 -Isrc -DNDEBUG -c src/include/main/main.c -o build/src/include/main/main.o
        gcc -m32 -std=c99 -O0 -Isrc -DNDEBUG -shared -Wl,--output-def,build/build/include/main/main.dll.def -Wl,--kill-at build/src/type.o build/src/error.o build/src/include/main/main.o -o build/build/include/main/main.dll
dbg -> dbg.libver:
        gcc -m32 -std=c99 -O0 -Isrc -DNDEBUG libver.c -o build/build/libver.exe


starting:

main:
In file included from src/main/main.c:5:
src/type/type.h:31:3: error: 'Type' redeclared as different kind of symbol
   31 | } Type;
      |   ^~~~
src/type/type.h:7:13: note: previous declaration of 'Type' was here
    7 | struct Type Type;
      |             ^~~~
src/type/type.h:7:13: error: storage size of 'Type' isn't known


done with errors
PS C:\Users\markv\OneDrive\Desktop\git\singleFileProjects\C\test - dynamic linking> py make.py
main:
        gcc -m32 -std=c99 -O0 -Isrc -DNDEBUG -c src/main/main.c -o build/src/main/main.o
        gcc -m32 -std=c99 -O0 -Isrc -DNDEBUG -c src/type/type.c -o build/src/type.o
        gcc -m32 -std=c99 -O0 -Isrc -DNDEBUG -c src/error/error_main.c -o build/src/error_main.o
        gcc -m32 -std=c99 -O0 -Isrc -DNDEBUG build/src/main/main.o build/src/type.o build/src/error_main.o -o build/build/main.exe
lib -> lib.lib:
        gcc -m32 -std=c99 -O0 -Isrc -DNDEBUG -c src/type/type.c -o build/src/type.o
        gcc -m32 -std=c99 -O0 -Isrc -DNDEBUG -c src/error/error_dll.c -o build/src/error.o
        gcc -m32 -std=c99 -O0 -Isrc -DNDEBUG -c src/include/lib/lib.c -o build/src/include/lib/lib.o
        gcc -m32 -std=c99 -O0 -Isrc -DNDEBUG -shared -Wl,--output-def,build/build/include/lib/lib.dll.def -Wl,--kill-at build/src/type.o build/src/error.o build/src/include/lib/lib.o -o build/build/include/lib/lib.dll
lib -> lib.main:
        gcc -m32 -std=c99 -O0 -Isrc -DNDEBUG -c src/type/type.c -o build/src/type.o
        gcc -m32 -std=c99 -O0 -Isrc -DNDEBUG -c src/error/error_dll.c -o build/src/error.o
        gcc -m32 -std=c99 -O0 -Isrc -DNDEBUG -c src/include/main/main.c -o build/src/include/main/main.o
        gcc -m32 -std=c99 -O0 -Isrc -DNDEBUG -shared -Wl,--output-def,build/build/include/main/main.dll.def -Wl,--kill-at build/src/type.o build/src/error.o build/src/include/main/main.o -o build/build/include/main/main.dll
dbg -> dbg.libver:
        gcc -m32 -std=c99 -O0 -Isrc -DNDEBUG libver.c -o build/build/libver.exe


starting:

main:
src/type/type.c: In function 'create_intptr':
src/type/type.c:57:17: warning: implicit declaration of function 'emalloc'; did you mean 'malloc'? [-Wimplicit-function-declaration]
   57 |     Type *val = emalloc(sizeof(Type));
      |                 ^~~~~~~
      |                 malloc
src/type/type.c:57:17: warning: initialization of 'Type *' from 'int' makes pointer from integer without a cast [-Wint-conversion]
src/type/type.c: In function 'create_string':
src/type/type.c:74:22: warning: assignment to 'string_t *' from 'int' makes pointer from integer without a cast [-Wint-conversion]
   74 |     val.data._string = emalloc(sizeof(string_t));
      |                      ^
src/type/type.c:81:28: warning: assignment to 'char *' from 'int' makes pointer from integer without a cast [-Wint-conversion]
   81 |     val.data._string->data = emalloc(len + 1);
      |                            ^
src/type/type.c: In function 'destroy_type':
src/type/type.c:97:9: warning: implicit declaration of function 'efree'; did you mean 'free'? [-Wimplicit-function-declaration]
   97 |         efree(type.data._string->data);
      |         ^~~~~
      |         free
src/type/type.c: In function 'cast_charptr':
src/type/type.c:120:20: warning: initialization of 'char *' from 'int' makes pointer from integer without a cast [-Wint-conversion]
  120 |     char *string = emalloc(length + 1);
      |                    ^~~~~~~
src/type/type.c: In function 'print_type':
src/type/type.c:142:16: warning: implicit declaration of function 'printf' [-Wimplicit-function-declaration]
  142 |         return printf("%d\n", type.data._int);
      |                ^~~~~~
src/type/type.c:142:16: warning: incompatible implicit declaration of built-in function 'printf'
src/type/type.c:7:1: note: include '<stdio.h>' or provide a declaration of 'printf'
    6 | #include "libver.h"
  +++ |+#include <stdio.h>
    7 |
src/error/error_main.c:21:6: error: conflicting types for 'eregistercleanup'
   21 | void eregistercleanup(voidfunc func){
      |      ^~~~~~~~~~~~~~~~
In file included from src/error/error_main.c:1:
src/error/error.h:52:19: note: previous declaration of 'eregistercleanup' was here
   52 | void  exposedType eregistercleanup(voidfunc func);
      |                   ^~~~~~~~~~~~~~~~
src/error/error_main.c: In function 'eregistercleanup':
src/error/error_main.c:23:9: error: 'ERR_OOM' undeclared (first use in this function)
   23 |   error(ERR_OOM, "too many cleanups", __POSITION__);
      |         ^~~~~~~
src/error/error_main.c:23:9: note: each undeclared identifier is reported only once for each function it appears in
src/error/error_main.c: In function 'ebind':
src/error/error_main.c:118:64: warning: passing argument 7 of 'bindCallBack' from incompatible pointer type [-Wincompatible-pointer-types]
  118 |  bindCallBack(emalloc, ecalloc, erealloc, efree, error, eexit, eregistercleanup);
      |                                                                ^~~~~~~~~~~~~~~~
      |                                                                |
      |                                                                void (*)(void (*)(void))
src/error/error_main.c:118:64: note: expected 'eregistercleanup_t' {aka 'void (__attribute__((stdcall)) *)()'} but argument is of type 'void (*)(void (*)(void))'
src/error/error_main.c: In function 'getErrString':
src/error/error_main.c:192:7: error: 'ERR_OOM' undeclared (first use in this function)
  192 |  case ERR_OOM:
      |       ^~~~~~~


done with errors
```
