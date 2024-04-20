#ifndef COMPRESSION_H
#define COMPRESSION_H

#include <stdio.h>
#include "../headers/map.h"


typedef struct {
	int n;
	int *data;
} CompressedData;



extern void save_to_file(HashMap* table, const char* filename);
extern void compress(const char* input_filename, const char* output_filename);
extern void decompress(const char* input_filename, const char* output_filename);
extern void from_file_to_struct(HashMap *table, const char *filename);

#endif

