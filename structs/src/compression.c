#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/compression.h"
#include "../headers/trie.h"
#include "../headers/map.h"



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
        current_seq[current_seq_len++] = current_char;
        current_seq[current_seq_len] = '\0';
        
        int code = search_string(root, current_seq);

        if (code == -1) {
            fprintf(output, "%d ", last_code);
            insert_string(root, current_seq, next_code++); 

            current_seq[0] = current_char;
            current_seq[1] = '\0'; 
            current_seq_len = 1;
            last_code = search_string(root, current_seq);
        } else {
            last_code = code;
        }
    }

    if (current_seq_len > 0) {
        fprintf(output, "%d ", last_code);
    }

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
        exit(EXIT_FAILURE);
    }


    char *dictionary[4096];
    for (int i = 0; i < 256; i++) {
        dictionary[i] = (char*) malloc(sizeof(char) * 2);
        dictionary[i][0] = (char) i;
        dictionary[i][1] = '\0';
    }
    int dict_size = 256;

    char decoded_string[1024];
    int previous_code, current_code;

    if (fscanf(input, "%d", &previous_code) != 1) {
        fclose(input);
        fclose(output);
        return;
    }
    fprintf(output, "%s", dictionary[previous_code]); 

    while (fscanf(input, "%d", &current_code) == 1) {
        if (current_code >= dict_size) {
            strcpy(decoded_string, dictionary[previous_code]);
            decoded_string[strlen(decoded_string) + 1] = '\0';
            decoded_string[strlen(decoded_string)] = decoded_string[0];
        } else {
            strcpy(decoded_string, dictionary[current_code]);
        }

        fprintf(output, "%s", decoded_string);


        if (dict_size < 4096) {
            dictionary[dict_size] = (char*) malloc(sizeof(char) * (strlen(dictionary[previous_code]) + 2));
            sprintf(dictionary[dict_size], "%s%c", dictionary[previous_code], decoded_string[0]);
            dict_size++;
        }

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
