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
```
