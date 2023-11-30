#include <stdio.h>
#include <string.h>

#define MAX_LINE_LENGTH 1000

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <pattern> <filename>\n", argv[0]);
        return 1;
    }

    char pattern[MAX_LINE_LENGTH];
    strcpy(pattern, argv[1]);

    FILE *file;
    char line[MAX_LINE_LENGTH];

    file = fopen(argv[2], "r");
    if (file == NULL) {
        printf("Unable to open file: %s\n", argv[2]);
        return 1;
    }

    printf("Lines containing '%s' in file '%s':\n", pattern, argv[2]);

    while (fgets(line, sizeof(line), file) != NULL) {
        if (strstr(line, pattern) != NULL) {
            printf("%s", line);
        }
    }

    fclose(file);

    return 0;
}
