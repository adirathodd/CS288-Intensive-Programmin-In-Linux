#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[], char *envp[]) {
    int envc = 0;
    while (envp[envc] != NULL) {
        envc++;
    }

    int equals_positions[envc];

    for (int i = 0; i < envc; i++) {
        char *equal_sign = strchr(envp[i], '=');
        if (equal_sign != NULL) {
            equals_positions[i] = equal_sign - envp[i];
            *equal_sign = '\0';
        } else {
            equals_positions[i] = -1;
        }
    }


    for (int i = 0; i < envc - 1; i++) {
        for (int j = 0; j < envc - i - 1; j++) {
            int cmp = strcmp(envp[j], envp[j + 1]);
            if (cmp > 0) {
                char *temp_env = envp[j];
                envp[j] = envp[j + 1];
                envp[j + 1] = temp_env;


                int temp_pos = equals_positions[j];
                equals_positions[j] = equals_positions[j + 1];
                equals_positions[j + 1] = temp_pos;
            }
        }
    }


    for (int i = 0; i < envc; i++) {
        if (equals_positions[i] != -1) {
            envp[i][equals_positions[i]] = '='; // Restore '='
        }
    }


    for (int i = 0; i < envc; i++) {
        printf("%s\n", envp[i]);
    }

    return 0;
}