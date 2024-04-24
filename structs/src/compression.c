#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/compression.h"
#include "../headers/trie.h"
#include "../headers/map.h"


unsigned long bit_buffer = 0;
unsigned long bit_buffer_length = 0;


void
outputBits(FILE *output,  unsigned long code,  unsigned long bit_count) {
    bit_buffer = (bit_buffer << bit_count) | code;
    bit_buffer_length += bit_count;

    while (bit_buffer_length >= 8) {
        unsigned char byte_to_write = (unsigned char)(bit_buffer >> (bit_buffer_length - 8));
        fwrite(&byte_to_write, 1, 1, output);
        bit_buffer_length -= 8;
    }
}


void 
flushBits(FILE *output) {
    if (bit_buffer_length > 0) {
        unsigned char byte_to_write = (unsigned char)(bit_buffer << (8 - bit_buffer_length));
        fwrite(&byte_to_write, 1, 1, output);
        bit_buffer_length = 0;
        bit_buffer = 0;
    }
}


int 
inputBits(FILE *input,  unsigned long bit_count) {
    static unsigned long input_buffer = 0;
    static unsigned long input_bits_left = 0;
    unsigned long result = 0;

    while (input_bits_left < bit_count) {
        unsigned char byte_read;
        if (!fread(&byte_read, 1, 1, input)) {
            if (input_bits_left == 0) {
                return -1; 
            }
            break;
        }
        input_buffer = (input_buffer << 8) | byte_read;
        input_bits_left += 8;
    }

    if (input_bits_left >= bit_count) {
        result = (unsigned long)(input_buffer >> (input_bits_left - bit_count)) & ((1 << bit_count) - 1);
        input_bits_left -= bit_count;
    } else {
        result = -1;
    }

    return result;
}


void 
save_to_file(HashMap *table, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Failed to open file");
        return;
    }

    for (unsigned int i = 0; i < (1 << 16); ++i) {
        sL2 *list = &table->arr[i];
        
        if (list->head != NULL) {
            sL2Node *node = list->head;

            fprintf(file, "%d\n", i);
            while (node) {
                fprintf(file, " %s;", node->data);
                node = node->next;
            }
            fprintf(file, "\n");
        }
    }

    fclose(file);
}


void 
compress(const char* input_filename, const char* output_filename) {
    FILE *input = fopen(input_filename, "r");
    FILE *output = fopen(output_filename, "wb");

    if (!input || !output) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    TrieNode *root = createTrieNode();

    int next_code = 0;
    for (int i = 0; i < 256; i++) {
        char c = (char)i;
        insert_string(root, &c, next_code++);
    }

    char current_seq[4096] = {0}; 
    char current_char;
    int current_seq_len = 0;
    int last_code = -1;

    while ((current_char = fgetc(input)) != EOF) {
        current_seq[current_seq_len] = current_char;
        current_seq_len++;
        current_seq[current_seq_len] = '\0';
        
        int code = search_string(root, current_seq);

        if (code == -1) {
            outputBits(output, last_code, 12);

            if (next_code < 4096) {
                insert_string(root, current_seq, next_code++);
            }

            current_seq[0] = current_char;
            current_seq[1] = '\0'; 
            current_seq_len = 1;
            last_code = search_string(root, current_seq);
        } else {
            last_code = code;
        }
    }

    if (current_seq_len > 0) {
        outputBits(output, last_code, 12);
    }
    flushBits(output);
    fclose(input);
    fclose(output);
    free_trie(root);
}


void 
decompress(const char* input_filename, const char* output_filename) {
    FILE *input = fopen(input_filename, "rb");
    FILE *output = fopen(output_filename, "w");

    if (!input || !output) {
        perror("Failed to open file");
        if (input) fclose(input);
        if (output) fclose(output);
        exit(EXIT_FAILURE);
    }

    char *dictionary[4096];
    int dict_size = 256;
    for (int i = 0; i < dict_size; i++) {
        dictionary[i] = (char*) malloc(2);
        dictionary[i][0] = (char)i;
        dictionary[i][1] = '\0';
    }
    
    int previous_code = inputBits(input, 12);
    if (previous_code == -1) {
        fclose(input);
        fclose(output);
        return;
    }
    fprintf(output, "%s", dictionary[previous_code]);

    int current_code;
    char *decoded_string;
    while ((current_code = inputBits(input, 12)) != -1) {
        if (current_code >= dict_size) {
            decoded_string = (char*)malloc(strlen(dictionary[previous_code]) + 2);
            strcpy(decoded_string, dictionary[previous_code]);
            decoded_string[strlen(decoded_string) + 1] = '\0';
            decoded_string[strlen(decoded_string)] = dictionary[previous_code][0];
        } else if (current_code < dict_size) {
            decoded_string = strdup(dictionary[current_code]);
        } else {
            fclose(input);
            fclose(output);
            return;
        }

        fprintf(output, "%s", decoded_string);
        
        if (dict_size < 4096) {
            dictionary[dict_size] = (char*) malloc(strlen(dictionary[previous_code]) + 2);
            sprintf(dictionary[dict_size], "%s%c", dictionary[previous_code], decoded_string[0]);
            dict_size++;
        }
        
        free(decoded_string);
        previous_code = current_code;
    }
    
    for (int i = 0; i < dict_size; i++) {
        free(dictionary[i]);
    }

    fclose(input);
    fclose(output);
}


void 
from_file_to_struct(HashMap *table, const char *filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file");
        return;
    }

    while (!feof(file)) {
        int index;
        if (fscanf(file, "%d\n", &index) == 1) {
            sL2* list = &table->arr[index];
            sL2Node* node = list->head;
            
            while (node && fscanf(file, "%[^;]", node->data) == 1) {
                node = node->next;
            }
            fscanf(file, "\n");
        }
    }

    fclose(file);
}
