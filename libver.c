#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[]){
    if (argc != 2){
        printf("usage: libver <file>\nprints the versions of the library, object file or executable");
        return 0;
    }
    char a[1000];
    sprintf(a, "strings %s | grep LIBVER | awk '!seen[$0]++'", argv[1]);
    system(a);
    return 0;
}
