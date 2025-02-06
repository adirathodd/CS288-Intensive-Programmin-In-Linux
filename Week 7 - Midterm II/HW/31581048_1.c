#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void print_addr_formatted(void *ptr) {
    unsigned char *bytePtr = (unsigned char *)&ptr;
    
    for (int i = sizeof(ptr) - 1; i >= 0; i--) {
        printf("%02x ", bytePtr[i]);
    }
    printf("| ");
}

int main(int argc, char **argv)
{
    int i, j;

    printf("argv\t| ");
    print_addr_formatted(argv);
    printf("%p\n", (void *)&argv);
    printf("\n");

    for (i = 0; i < argc; i++){
        printf("argv[%d]\t| ", i);
        print_addr_formatted(*(argv+i));
        printf("%p\n", (void *)(argv+i));
    }

    printf("\n");


    unsigned long addr = (unsigned long)argv[0];
    addr &= ~0x7UL;
    unsigned char *p = (unsigned char *)addr;

    unsigned char *end = (unsigned char *)argv[argc - 1] + strlen(argv[argc - 1]) + 1;
    unsigned long end_addr = (unsigned long)end;
    if (end_addr % 8 != 0) {
        end_addr = (end_addr + 8) & ~0x7UL;
        end = (unsigned char *)end_addr;
    }

    for (; p < end; p += 8) {
        printf("| ");
        for (i = 7; i >= 0; i--) {
            unsigned char c = *(p + i);
            printf("%02hhx", c);
            if (isprint(c)) {
                printf("(%c) ", c);
            } else if (c == '\0') {
                printf("(\\0) ");
            } else {
                printf("(.) ");
            }
        }
        printf("\t| %p\n", (void *)p);
    }
    
    return 0;
}