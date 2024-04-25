#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> 

#include "../structs/headers/compression.h"
#include "../structs/headers/trie.h"
#include "../structs/headers/map.h"

enum {
    MAX_LEN = 1000000,
    WORD_LEN = 80
};

int main(int argc, char *argv[]) {
    const char *output_filename = "output.txt";
    clock_t start, end;
    double cpu_time_used;
    start = clock();

    HashMap table;
    init(&table);
    char *input_filename = NULL;
    FILE *input;
    for (int i = 1; i < argc; ++i) {
        input_filename = argv[i];
        input = fopen(input_filename, "r");
        if (input == NULL) {
            fprintf(stderr, "error with file %s\n", input_filename);
            fflush(stderr);
            exit(1);
        }
        char *word = calloc(WORD_LEN, sizeof(*word));
        while (fscanf(input, "%s", word) != EOF) {
            insert_item(&table, input_filename, word);
        }
        free(word);
        fclose(input);
    }
    save_to_file(&table, "input.txt");
    compress("input.txt", output_filename);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Сжатие завершено за %f секунды. Проверьте файл '%s'.\n", cpu_time_used, output_filename);
    return 0;
}
