#include <stdio.h>
#include <unistd.h>


int main(int argc, char *argv[]) {
    int opt;

    opterr = 0;

    while ((opt = getopt(argc, argv, ":cduf:s:")) != -1) {
        switch (opt) {
            case 'c':
            case 'd':
            case 'u':
                printf("Option -%c is set\n", opt); break;
            case 'f':
            	if(optarg == NULL || optarg[0] == '-'){
            		printf("Option -f missing a required argument\n");
            		if (optarg != NULL) optind--;
            	} else {
                	printf("Option -f is set with argument '%s'\n", optarg);
                }
                break;
            case 's':
                if(optarg == NULL || optarg[0] == '-'){
            		printf("Option -s missing a required argument\n");
            		if (optarg != NULL) optind--;
            	} else {
                	printf("Option -s is set with argument '%s'\n", optarg);
                }
                break;
            case ':':
            	printf("Option -%c missing a required argument\n", optopt);
                break;
            case '?':
            	printf("Unknown option '-%c'.\n", optopt);
 		break;
        }
    }

    if (optind < argc) {
        printf("Operands:\n");
        for (int index = optind; index < argc; index++)
            printf("%s\n", argv[index]);
    }
}