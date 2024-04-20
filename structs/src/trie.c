#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../headers/trie.h"

TrieNode
*createTrieNode(void) {
    TrieNode *newNode = calloc(1, sizeof(TrieNode));
    if (!newNode) {
       fprintf(stderr, "Memory allocation failed\n");
       exit(EXIT_FAILURE);
    }
    
    if (newNode) {
        for (int i = 0; i < MAX_CHILDREN; i++)
            newNode->children[i] = NULL;
        newNode->isEndOfWord = 0;
    }
    return newNode;
}

void 
insert_string(TrieNode *root, const char *key, int sequenceID) {
    TrieNode *node = root;
    
    while(*key) {
        int index = (unsigned char)(*key);
        if (node->children[index] == NULL) {
            node->children[index] = createTrieNode();
        }
        node = node->children[index];
        key++;
    }
    node->isEndOfWord = sequenceID;
}

int 
search_string(TrieNode *root, const char *key) {
    TrieNode *node = root;
    
    while(*key) {
        int index = (unsigned char)(*key);
        if (!node->children[index]) {
            return -1;
        }
        node = node->children[index];
        key++;
    }
    return node->isEndOfWord; 
}



void 
free_trie(TrieNode *root) {
    int i;
    for (i = 0; i < MAX_CHILDREN; i++) {
        if (root->children[i]) {
            free_trie(root->children[i]);
        }
    }
    free(root);
}

