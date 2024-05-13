#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../structs/headers/compression.h"
#include "../structs/headers/map.h"
#include "../structs/headers/set.h"

enum {
    MAX_LEN = 80,
    STRING_LEN = 100000
}; 

typedef struct Pair {
    char *doc;
    int count;
} Pair;

int 
main(int argc, char *argv[]) {

    clock_t start, end;
    double cpu_time_used;

    start = clock();


    HashMap *table = calloc(1, sizeof(*table)); 
    init(table);
    from_file_to_struct(table, argv[1]);
    int N;
    scanf("%d\n", &N);
    char *word = calloc(MAX_LEN, sizeof(*word));
    char *string = calloc(STRING_LEN, sizeof(*string));
    sL2Node *node;
    TempL2Node *item_node;
    Pair *pairs = calloc(STRING_LEN, sizeof(*pairs));
    int cnt_of_docs = 0;
    int cnt_of_words = 0;
    int is_empty = 0;
    int is_first = 1;
    for (int i = 0; i < N; ++i) {
        fgets(string, STRING_LEN, stdin);
        string[strlen(string) - 1] = '\0';
        word = strtok(string, " ");
        while (word != NULL) {
            ++cnt_of_words;
            node = h_find(table, word);
            if (node != NULL) {
                item_node = node->item_list->head;
                while (item_node != NULL) {
                    int finded = 0;
                    for (int i = 0; i < cnt_of_docs; ++i) {
                        if (strcmp(pairs[i].doc, item_node->data) == 0) {
                            finded = 1;
                            ++pairs[i].count;
                            break;
                        } 
                    }
                    if (!finded) {
                        pairs[cnt_of_docs].doc = item_node->data;
                        pairs[cnt_of_docs].count = 1;
                        ++cnt_of_docs;
                    } 
                    item_node = item_node->next;
                }
            }
            word = strtok(NULL, " ");
        }
        for (int i = 0; i < cnt_of_docs; ++i) {
            if (pairs[i].count == cnt_of_words) {
                printf("%s ", pairs[i].doc);
            }
        }
        printf("\n");
        cnt_of_words = 0;
        cnt_of_docs = 0;
    }

    end = clock();

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("Работа завершена за %f секунды.\n", cpu_time_used);
    

    free(pairs);
    free(word);
    free(string);
    return 0;
}
