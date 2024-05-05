
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> 

#include "headers/compression.h"
#include "headers/trie.h"

int main() {
    const char* input_filename = "input.txt";   
    const char* output_filename = "output.txt";   
    const char* decompressed_filename = "decompressed.txt";

    clock_t start, end;
    double cpu_time_used;

    start = clock();

    compress(input_filename, output_filename);


    end = clock();

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("Сжатие завершено за %f секунды. Проверьте файл '%s'.\n", cpu_time_used, output_filename);

    start = clock();
    decompress(output_filename, decompressed_filename);
    end = clock();

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;


    printf("Восстановление завершено за %f секунды. Проверьте файл '%s'.\n", cpu_time_used, decompressed_filename);
    return 0;
}