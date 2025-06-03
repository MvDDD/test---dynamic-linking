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
        gcc -m32 -std=c99 -O0 -Isrc -DNDEBUG -c src/main/main.c -o build/src/main/main.o
        gcc -m32 -std=c99 -O0 -Isrc -DNDEBUG -c src/type/type.c -o build/src/type.o
        gcc -m32 -std=c99 -O0 -Isrc -DNDEBUG -c src/error/error_main.c -o build/src/error_main.o
        gcc -m32 -std=c99 -O0 -Isrc -DNDEBUG build/src/main/main.o build/src/type.o build/src/error_main.o -o build/build/main.exe
lib -> lib.lib:
        gcc -m32 -std=c99 -O0 -Isrc -DNDEBUG -c src/error/error_dll.c -o build/src/error.o
        gcc -m32 -std=c99 -O0 -Isrc -DNDEBUG -c src/include/lib/lib.c -o build/src/include/lib/lib.o
        gcc -m32 -std=c99 -O0 -Isrc -DNDEBUG -shared -Wl,--output-def,build/build/include/lib/lib.dll.def -Wl,--kill-at build/src/type.o build/src/error.o build/src/include/lib/lib.o -o build/build/include/lib/lib.dll
lib -> lib.main:
        gcc -m32 -std=c99 -O0 -Isrc -DNDEBUG -c src/include/main/main.c -o build/src/include/main/main.o
        gcc -m32 -std=c99 -O0 -Isrc -DNDEBUG -shared -Wl,--output-def,build/build/include/main/main.dll.def -Wl,--kill-at build/src/type.o build/src/error.o build/src/include/main/main.o -o build/build/include/main/main.dll
dbg -> dbg.libver:
        gcc -m32 -std=c99 -O0 -Isrc -DNDEBUG libver.c -o build/build/libver.exe


done!

```
