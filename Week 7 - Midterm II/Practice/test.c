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
    printf("%p\n", &argv);
    printf("\n");

    for(int i = 0; i < argc;i++){
        printf("argv[%d]\t| ", i);
        print_addr_formatted(*(argv+i));
        printf("%p\n", argv+i);
    }

    printf("\n");

    uintptr_t addr = (uintptr_t)argv[0];
    addr &= ~0x7;
    unsigned char *p = (unsigned char *)addr;
    unsigned char *end = (unsigned char *)argv[argc - 1] + strlen(argv[argc - 1]) + 1;
    intptr_t end_addr = (uintptr_t)end;
    if (end_addr % 8 != 0) {
        end_addr = (end_addr + 8) & ~0x7;
        end = (unsigned char *)end_addr;
    }

    for (; p <= end; p += 8) {
        printf("| ");
        for (i = 7; i >= 0; i--) {
            printf("%02hhx(%c) ", *(p + i), (unsigned char)*(p+i));
        }
        printf("\t| %p\n", p);
    }
}