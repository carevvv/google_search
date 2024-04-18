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


extern void avl_insert(Set *tree, char* elem);
extern void avl_print(Set *tree);
extern void avl_erase(Set *tree, char* elem);
extern int  avl_find (Set *tree, char* elem);

#endif