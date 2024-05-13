#ifndef MAP_H
#define MAP_H

#include "list_str.h"

typedef struct HashMap {
          unsigned short (*hash)(char* str, unsigned long len);  //hash//;
          sL2 arr[1<<16];
} HashMap;

extern void insert_item(HashMap *table, char* item, char* key);
extern void erase_item(HashMap *table, char* item, char* key );
extern sL2Node* h_find(HashMap *table, char *str);
extern void init(HashMap *table);
extern TempL2* find_array(HashMap *table, char* key);
#endif
