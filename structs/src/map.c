#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "list_str.h"
#include "map.h"

unsigned short MurmurHash(char* key, unsigned long len) {
      const unsigned int m = 0x5bd1e995;
      const unsigned int seed = 0;
      const int r = 24;

      unsigned int h = seed ^ len;

      const unsigned char* data = (const unsigned char*)key;
      unsigned int k = 0;

      while (len >= 4) {
          k = data[0];
          k |= data[1] << 8;
          k |= data[2] << 16;
          k |= data[3] << 24;

          k *= m;
          k ^= k >> r;
          k *= m;

          h *= m;
          h ^= k;

          data += 4;
          len -= 4;
      }

      switch (len) {
          case 3:
              h ^= data[2] << 16;
          case 2:
              h ^= data[1] << 8;
          case 1:
              h ^= data[0];
              h *= m;
      };

      h ^= h >> 13;
      h *= m;
      h ^= h >> 15;

      return h % (1 << 16);
  }

sL2Node* h_find(HashMap *table, char *str) {
        unsigned short index = table->hash(str, strlen(str));
        sL2 *list = &(table->arr[index]);
        sL2Node* current = list->head;
        sL2Node* prev = NULL;
         while (current != NULL) {
            if (strcmp(current->data, str) == 0) {
                return current;
            }
            prev = current;
            current = current->next;
        }
        return NULL;
    }

void h_insert(HashMap *table, char *str) {
    unsigned short index = table->hash(str, strlen(str));
    sL2* list = &table->arr[index];

    if (h_find(table, str) == NULL) {
        sL2Node* new_node = malloc(sizeof(sL2Node));
        if (new_node == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(1);
        }
        new_node->data = strdup(str);
        if (new_node->data == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(1);
        }
        new_node->item_list = malloc(sizeof(sL2));
        if (new_node->item_list == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(1);
        }
        new_node->item_list->head = NULL;
        new_node->item_list->tail = NULL;
        new_node->item_list->size = 0;

        if (list->head == NULL) {
            list->head = new_node;
            list->tail = new_node;
        } else {
            list->tail->next = new_node;
            new_node->prev = list->tail;
            list->tail = new_node;
        }
        list->size++;
    } else {
        //printf("Element '%s' already exists\n", str);
    }
}


void init(HashMap *table) {
      //table->arr = calloc (1 << 16, sizeof(table->arr));
    for (int i = 0; i < (1 << 16); ++i) {
        table->arr[i].head = NULL;
        table->arr[i].tail = NULL;
        table->arr[i].size = 0;
    }
    table->hash = MurmurHash;
}

void
h_erase (HashMap *table, char *str) {
      unsigned short index = table->hash(str, strlen(str));
      sL2* list = &table->arr[index];

      sL2Node* current = list->head;
      sL2Node* prev = NULL;

      while (current != NULL) {
          if (strcmp(current->data, str) == 0) {
              if (prev == NULL) {
                  list->head = current->next;
              } else {
                  prev->next = current->next;
              }
              free(current->data);
              free(current);
              return;
          }
          prev = current;
          current = current->next;
      }
  }



void 
insert_item(HashMap *table, char* item, char* key) {
    sL2Node* elem = h_find(table, key);

    if (elem != NULL) {
        if (sl2_find(elem->item_list->head, item) == -1) {
            sl2_push_back(elem->item_list, item);
            //printf("Item '%s' inserted for key '%s'\n", item, key);
        } else {
            //printf("Item '%s' already exists for key '%s'\n", item, key);
        }
    } else {
        elem = malloc(sizeof(sL2Node));
        if (elem == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(1);
        }
        elem->data = strdup(key);
        if (elem->data == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(1);
        }
        elem->item_list = malloc(sizeof(sL2));
        if (elem->item_list == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(1);
        }
        elem->item_list->head = NULL;
        elem->item_list->tail = NULL;
        elem->item_list->size = 0;
        h_insert(table, key);
        elem = h_find(table, key);
        sl2_push_back(elem->item_list, item);
        //printf("Item '%s' inserted for key '%s'\n", item, key);
    }
}

void 
erase_item(HashMap *table, char* item, char* key ) {
    sL2Node* elem = h_find(table, key);
    
    if (elem != NULL) {
        int item_pos = sl2_find(elem->item_list->head, item);
        if (item_pos != -1) {
            sl2_erase(elem->item_list, item_pos);
            //printf("Item '%s' erased for key '%s'\n", item, key);
        } else {
            //printf("Item '%s' does not exist for key '%s'\n", item, key);
        }
    } else {
        //printf("Key '%s' does not exist in the hash table\n", key);
    }
}

sL2* find_array(HashMap *table, char* key) {
    sL2Node* elem = h_find(table, key);

    if (elem != NULL) {
        return elem->item_list;
    } else {
        //printf("Key '%s' not found in the hash table\n", key);
        return NULL;
    }
}
