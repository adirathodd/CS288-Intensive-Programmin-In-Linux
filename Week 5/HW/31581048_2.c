#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>

void count_lines_in_file(const char *filepath, int *total_lines) {
    FILE *file = fopen(filepath, "r");
    if (file == NULL) {
        perror("Failed to open file");
        return;
    }

    int lines = 0;
    char ch;
    char prev = '\0';
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            lines++;
        }
        prev = ch;
    }

    if (prev != '\n' && prev != '\0') {
        lines++;
    }

    fclose(file);
    *total_lines += lines;
}

void traverse_directory(const char *dirpath, int *total_lines) {
    struct dirent *entry;
    DIR *dp = opendir(dirpath);

    if (dp == NULL) {
        perror("Failed to open directory");
        return;
    }

    while ((entry = readdir(dp)) != NULL) {
       	
	if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }
	
	char path[1000];
    snprintf(path, sizeof(path), "%s/%s", dirpath, entry->d_name);

    struct stat statbuf;
    if (stat(path, &statbuf) == -1) {
        perror("Failed to get file status");
        continue;
    }

    if (S_ISDIR(statbuf.st_mode)) {
        traverse_directory(path, total_lines);
    } else if (S_ISREG(statbuf.st_mode) && strstr(entry->d_name, ".txt")) {
        count_lines_in_file(path, total_lines);
    }
}

    closedir(dp);
}

int main() {
    char dirpath[1000];
    printf("Enter the directory path: ");
    scanf("%s", dirpath);

    int total_lines = 0;
    traverse_directory(dirpath, &total_lines);

    printf("Total number of lines in .txt files: %d\n", total_lines);
    return 0;
}