#ifndef SET_H
#define SET_H

typedef struct SetNode {
    char* data;
    int height;
    struct SetNode *left;
    struct SetNode *right;
    struct SetNode *parent;
} SetNode;

typedef struct Set{
    SetNode *root;
} Set;


extern void set_insert(Set *tree, char* elem);
extern void set_print(Set *tree);
extern void set_erase(Set *tree, char* elem);
extern int  set_find (Set *tree, char* elem);

#endif
