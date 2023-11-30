#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    char data[100];
    file = fopen("data.txt", "w");
    if (file == NULL) {
        printf("Unable to create file.\n");
        return 1;
    }
    printf("Enter data to write to the file: ");
    fgets(data, sizeof(data), stdin);
    fprintf(file, "%s", data);
    fclose(file);
    file = fopen("data.txt", "r");
    if (file == NULL) {
        printf("Unable to open file.\n");
        return 1;
    }
    printf("Data read from the file:\n");
    while (fgets(data, sizeof(data), file) != NULL) {
        printf("%s", data);
    }
    fclose(file);

    return 0;
}
