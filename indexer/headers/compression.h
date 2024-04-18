#ifndef COMPRESSION_H
#define COMPRESSION_H

#include <stdio.h>



typedef struct {
	int n;
	int *data;
} CompressedData;

typedef struct {
    char* key;
    char** pairs; // Массив пар строк
    int num_pairs; // Количество пар
} HashTableEntry;


typedef struct {
    HashTableEntry* entries;
    int num_entries;
} HashTable;


extern void save_to_file(HashTable* table, const char* filename);
extern void compress(const char* input_filename, const char* output_filename);
extern void decompress(const char* input_filename, const char* output_filename);


#endif

