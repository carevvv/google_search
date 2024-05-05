#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/compression.h"
#include "../headers/trie.h"

void 
save_to_file(HashTable* table, const char* filename) {

    FILE* file = fopen(filename, "w");
    if (!file) {
        perror("Failed to open file");
        return;
    }

    for (int i = 0; i < table->num_entries; ++i) {
        fprintf(file, "%s|", table->entries[i].key);
        for (int j = 0; j < table->entries[i].num_pairs; ++j) {
            fprintf(file, "%s;%s;", table->entries[i].pairs[2 * j], table->entries[i].pairs[2 * j + 1]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
}


void 
compress(const char* input_filename, const char* output_filename) {
    FILE* fin = fopen(input_filename, "rb");
    FILE* fout = fopen(output_filename, "wb");
    
    if (!fin || !fout) {
        perror("Failed to open file");
        return;
    }

    TrieNode *root = createTrieNode();
    int next_code = 256;

    for (int i = 0; i < 256; i++) {
        char c = (char)i;
        insert_string(root, &c, i);
    }

    int current_code;
    int size;
    char current_char = fgetc(fin);
    char *sequence = malloc(2);
    sequence[0] = current_char;
    sequence[1] = '\0';
    current_code = (unsigned char)current_char;

    while ((current_char = fgetc(fin)) != EOF) {
        char *new_sequence = realloc(sequence, strlen(sequence) + 2);
        sprintf(new_sequence, "%s%c", sequence, current_char);
        
        if (search_string(root, new_sequence) != 0) {
            sequence = new_sequence;
            current_code = search_string(root, sequence);
        } else {
            size = (current_code < 256) ? 1 : 2;
            fwrite(&current_code, size, 1, fout);
            insert_string(root, new_sequence, next_code++);
            free(sequence);
            sequence = malloc(2);
            sequence[0] = current_char;
            sequence[1] = '\0';
            current_code = (unsigned char)current_char;
        }
    }
    size = (current_code < 256) ? 1 : 2;
    fwrite(&current_code, size, 1, fout);

    free(sequence);
    fclose(fin);
    fclose(fout);
    free_trie(root);
}

void 
decompress(const char* input_filename, const char* output_filename) {
	return;
}