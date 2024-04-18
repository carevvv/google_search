#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "set.h"

int
max_f(int a, int b) {
    return a > b ? a : b;
}

char
h(SetNode *node) {
    if (node == NULL) {
        return 0;
    } else {
        return node->height;
    }
}

  char
  balance(SetNode *node) {
      return h(node->left) - h(node->right);
  }

  SetNode*
  rotate_left(SetNode *root) {
      if(root == NULL) {
          fprintf(stderr, "rotate left: root is NULL\n");
          fflush(stderr);
          exit(1);
      }
      SetNode *right_left_son = root->right->left;
      SetNode *res = root->right;
      res->parent = root->parent;
      if (root->parent != NULL) {
          if (root->parent->left == root) {
              root->parent->left = res;
          } else {
              root->parent->right = res;
          }
      }
      root->parent = res;
      res->left = root;
      res->left->right = right_left_son;
      res->left->height = max_f(h(res->left->left), h(res->left->right)) + 1;
      res->height = max_f(h(res->right), h(res->left)) + 1;
      return res;
  }

  SetNode *
  rotate_right(SetNode *root) {
      if(root == NULL) {
          fprintf(stderr, "rotate right: root is NULL\n");
          fflush(stderr);
          exit(1);
      }
      SetNode *left_right_son = root->left->right;
      SetNode *res = root->left;
      res->parent = root->parent;
      if (root->parent != NULL) {
          if (root->parent->right == root) {
              root->parent->right = res;
          } else {
              root->parent->left = res;
          }
      }
      root->parent = res;
      res->right = root;
      res->right->left = left_right_son;
      res->right->height = max_f(h(res->right->right), h(res->right->left)) + 1;
      res->height = max_f(h(res->left), h(res->right)) + 1;
      return res;
    }

  SetNode *
  big_rotate_left(SetNode *root) {
      rotate_right(root->right);
      return rotate_left(root);;
  }

  SetNode *
  big_rotate_right(SetNode *root) {
      rotate_left(root->left);
      return rotate_right(root);
  }

  SetNode *
init_node (SetNode *new, char *elem) {
    new->parent = NULL;
    new->left = NULL;
    new->right = NULL;
    new->data = strdup(elem);
    new->height = 1;
    return new;
}


void
set_insert(Set *tree, char *elem) {
    if (tree == NULL) {
        fprintf(stderr, "avl_insert: tree is NULL");
        fflush(stderr);
        exit(1);
    }
    if (set_find(tree, elem)) {
        printf("Element already exists in the set\n");
        return;
    }
    if (tree->root == NULL) {
        SetNode *current = calloc(1, sizeof(*current));
        current = init_node(current, elem);
        tree->root = current;
        return;
    }
    SetNode *new = calloc(1, sizeof(*new));
    new = init_node(new, elem);
    SetNode *current = tree->root;
    while (1) {
        int cmp_res = strcmp(current->data, new->data);
        if (cmp_res >= 0 && current->left == NULL) {
            new->parent = current;
            current->left = new;
            break;
        } else if (cmp_res < 0 && current->right == NULL) {
            new->parent = current;
            current->right = new;
            break;
        } else if (cmp_res >= 0) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    while (new->parent != NULL) {
        if (new->height == new->parent->height) {
            new->parent->height++;
            new = new->parent;
        } else {
            break;
        }
    }
    while (abs(balance(current)) != 2 && current->parent != NULL) {
        current = current->parent;
    }
    if (balance(current) == -2 && (balance(current->right) == -1 ||
                balance(current->right) == 0)) {
        current = rotate_left(current);
    } else if (balance(current) == 2 && (balance(current->left) == 1 ||
                balance(current->left) == 0)) {
        current = rotate_right(current);
    } else if (balance(current) == -2 && balance(current->right) == 1 &&
                abs(balance(current->right->left)) < 2) {
        current = big_rotate_left(current);
    } else if (balance(current) == 2 && balance(current->left) == 1 &&
                abs(balance(current->left->right)) < 2) {
        current = big_rotate_right(current);
    }
    if (current->parent == NULL) {
        tree->root = current;
    }
    return;
}

int
set_find(Set *tree, char *elem) {
    if (tree == NULL) {
        fprintf(stderr, "avl_find: tree is NULL");
        fflush(stderr);
        exit(1);
    }
    SetNode *current = tree->root;
    while (current != NULL) {
        int cmp_res = strcmp(current->data, elem);
        if (cmp_res > 0) {
            current = current->left;
        } else if (cmp_res < 0) {
            current = current->right;
        } else {
            return 1;
        }
    }
    return 0;
}

void
set_delete(Set *tree, char *elem) {
    if (tree == NULL) {
        fprintf(stderr, "avl_erase: tree is NULL");
        fflush(stderr);
        exit(1);
    }
    if (!set_find(tree, elem)) {
        printf("element hasn't been found in tree\n");
        return;
    }
      SetNode *deleted_p = NULL;
      SetNode *current = tree->root;
      int side_from_parent = -1;

      while (current->data != elem) {
          side_from_parent = (elem > current->data) ? 1 : 0;
          current = (elem > current->data) ? current->right : current->left;
      }

      if (current->left == NULL || current->right == NULL) {
          SetNode *child = (current->left == NULL) ? current->right : current->left;
          if (current->parent == NULL)
              tree->root = child;
          else if (side_from_parent == 0)
              current->parent->left = child;
          else
              current->parent->right = child;
          if (child != NULL)
              child->parent = current->parent;
          deleted_p = current->parent;
          free(current);
      } else {
          SetNode *min_right_node = current->right;
          while (min_right_node->left != NULL)
              min_right_node = min_right_node->left;
          current->data = min_right_node->data;
          deleted_p = min_right_node->parent;
          if (min_right_node->parent != current)
              min_right_node->parent->left = NULL;
          else
              current->right = NULL;
          free(min_right_node);
      }

      while (deleted_p != NULL) {
          if (balance(deleted_p) == 0)
              deleted_p = deleted_p->parent;
          else if (balance(deleted_p) == -2 && (balance(deleted_p->right) <= 0))
              deleted_p = rotate_left(deleted_p);
          else if (balance(deleted_p) == 2 && (balance(deleted_p->left) >= 0))
              deleted_p = rotate_right(deleted_p);
          else if (balance(deleted_p) == -2 && (balance(deleted_p->right) == 1) && abs(balance(deleted_p->right->left)) < 2)
              deleted_p = big_rotate_left(deleted_p);
          else if (balance(deleted_p) == 2 && (balance(deleted_p->left) == -1) && abs(balance(deleted_p->left->right)) < 2)
              deleted_p = big_rotate_right(deleted_p);
          if (deleted_p != NULL && balance(deleted_p) == 0 && deleted_p->parent != NULL)
              deleted_p = deleted_p->parent;
      }
      if (deleted_p == NULL)
          return;
      tree->root = deleted_p;
  }

  void print_spaces(int spaces) {
      for (int i = 0; i < spaces; i++) {
          printf(" ");
      }
  }

void
set_print_helper(SetNode *node, int level, int indent) {
    if (node == NULL) {
        return;
    }
    set_print_helper(node->right, level + 1, indent + 5);
    //print_spaces(indent);
    printf("%s\n", node->data);
    set_print_helper(node->left, level + 1, indent + 5);
}

void
set_print(Set *tree) {
    if (tree == NULL || tree->root == NULL) {
        printf("Tree is empty\n");
        return;
    }
    set_print_helper(tree->root, 0, 0);
}
