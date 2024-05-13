#ifndef TEMP_LIST_H
#define TEMP_LIST_H

typedef char* T;


typedef struct TempL2Node {
    char* data;
    struct TempL2Node *prev;
    struct TempL2Node *next;
} TempL2Node;


typedef struct TempL2 {
    TempL2Node *head;
    TempL2Node *tail;
    int size;
} TempL2;



extern void temp_push_back(TempL2 *list, char* elem);
extern void temp_push_front(TempL2 *list, char* elem);
extern void temp_insert(TempL2 *list, char* elem, int pos);
extern void temp_erase(TempL2 *list, int pos);
extern void temp_update(TempL2 *list, char* elem, int pos);
extern char* temp_get(TempL2 *list, int pos);
extern int temp_find(TempL2Node *list, char* elem);
extern void temp_print(TempL2 *list);
//extern int sl2_find_pos(sL2 *list, char* elem);
#endif
