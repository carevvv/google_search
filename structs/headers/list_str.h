#ifndef LIST_H
#define LIST_H

typedef char* T;
typedef struct sL2 sL2;

typedef struct sL2Node {
    char* data;
    struct sL2Node *prev;
    struct sL2Node *next;
    sL2 *item_list;
} sL2Node;


struct sL2 {
    sL2Node *head;
    sL2Node *tail;
    unsigned long int size;
};


extern void sl2_push_back(sL2 *list, char* elem);
extern void sl2_push_front(sL2 *list, char* elem);
extern void sl2_insert(sL2 *list, char* elem, int pos);
extern void sl2_erase(sL2 *list, int pos);
extern void sl2_update(sL2 *list, char* elem, int pos);
extern char* sl2_get(sL2 *list, int pos);
extern int sl2_find(sL2Node *list, char* elem);
extern void sl2_print(sL2 *list);
//extern int sl2_find_pos(sL2 *list, char* elem);
#endif
