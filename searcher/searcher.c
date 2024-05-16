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
    printf("decompressing...\n");
    from_file_to_struct(table, argv[1]);
    printf("searcher is ready\n");
    int N;
    scanf("%d\n", &N);
    char *word = calloc(MAX_LEN, sizeof(*word));
    char *string = calloc(STRING_LEN, sizeof(*string));
    sL2Node *node;
    TempL2Node *item_node;
    int cnt_of_docs = 0;
    int cnt_of_words = 0;
    int is_empty = 0;
    int is_first = 1;
    for (int i = 0; i < N; ++i) {
        int hashes[(1 << 16)];
        HashMap docs;
        init(&docs);
        fgets(string, STRING_LEN, stdin);
        string[strlen(string) - 1] = '\0';
        word = strtok(string, " ");
        while (word != NULL) {
            ++cnt_of_words;
            node = h_find(table, word);
            if (node != NULL) {
                item_node = node->item_list->head;
                while (item_node != NULL) {
                    sL2Node *doc_node;
                    doc_node = h_find(&docs, item_node->data);
                    if (doc_node == NULL) {
                        hashes[cnt_of_docs] = docs.hash(item_node->data, strlen(item_node->data));
                        ++cnt_of_docs;
                        insert_item(&docs, item_node->data, item_node->data);
                        doc_node = h_find(&docs, item_node->data);
                        doc_node->item_list = calloc(1, sizeof(doc_node->item_list));
                        doc_node->item_list->size = 1;
                    } else {
                        doc_node->item_list->size++;
                    }
                    item_node = item_node->next;
                }
            }
            word = strtok(NULL, " ");
        }
        printf("this words contain in:\n");
        for (int i = 0; i < cnt_of_docs; ++i) {
            sL2Node *nod = docs.arr[hashes[i]].head;
            while (nod != NULL) {
                if (nod->item_list->size == cnt_of_words) {
                    printf("%s ", nod->data);
                }
                nod = nod->next;
            }
        }
        printf("\n");
        cnt_of_words = 0;
        cnt_of_docs = 0;
    }

    end = clock();

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("Работа завершена за %f секунды.\n", cpu_time_used);
    

    free(word);
    free(string);
    return 0;
}
