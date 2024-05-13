#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "temp_list.h"

enum {
      SIZE = 10000
  };

void
temp_push_front(TempL2 *list, char *elem) {
      if (list == NULL) {
          fprintf(stderr, "t_push_front: list is NULL");
          fflush(stderr);
          exit(1);
      }
      if (list->size == 0) {
          list->head = calloc(strlen(elem), sizeof(*list->head));
          list->head->data = elem;
          list->head->next = NULL;
          list->head->prev = NULL;
          list->tail = list->head;
          list->size++;
      } else {
          list->head->prev = calloc(strlen(elem), sizeof(*list->head));
          list->head->prev->data = elem;
          list->head->prev->prev = NULL;
          list->head->prev->next = list->head;
          list->head = list->head->prev;
          list->size++;
      }
  }

void
temp_push_back(TempL2 *list, char *elem) {
      if (list == NULL) {
          fprintf(stderr, "t_push_back: list is NULL");
          fflush(stderr);
          exit(1);
      }
      if (list->size == 0) {
          list->head = calloc(strlen(elem), sizeof(list->head));
          list->head->data = elem;
          list->head->next = NULL;
          list->head->prev = NULL;
          list->tail = list->head;
          list->size++;
      } else {
          list->tail->next = calloc(strlen(elem), sizeof(list->head));
          list->tail->next->data = elem;
          list->tail->next->next = NULL;
          list->tail->next->prev = list->tail;
          list->tail = list->tail->next;
          list->size++;
      }
  }

void
temp_print(TempL2 *list) {
    if (list == NULL) {
        fprintf(stderr, "t_find: list is NULL");
        fflush(stderr);
        exit(1);
    }
    
      TempL2Node *node = list->head;
      while (node != NULL) {
          printf("%s ", node->data);
          node = node->next;
      }
      printf("\n");
  }

void
temp_insert(TempL2 *list, char *elem, int pos) {
      if (pos < 0 || list == NULL || pos > list->size) {
          fprintf(stderr, "t_insert error\n");
          fflush(stderr);
          exit(1);
      }
      if (pos == list->size) {
          temp_push_back(list, elem);
          return;
      } else if (pos == 0) {
          temp_push_front(list, elem);
          return;
      }
      if (pos <= list->size / 2) {
          TempL2Node *node = list->head;
          for (int i = 0; i < pos - 1; ++i) {
              node = node->next;
          }
          TempL2Node *new_node = calloc(1, sizeof(*new_node));
          new_node->data = elem;
          TempL2Node *temp = node->next;
          node->next = new_node;
          new_node->next = temp;
          new_node->prev = node;
      } else {
          TempL2Node *node = list->tail;
          for (int i = list->size - 1; i >= pos; --i) {
              node = node->prev;
          }
          TempL2Node *new = calloc(1, sizeof(*new));
          new->data = elem;
          TempL2Node *temp = node->next;
          node->next = new;
          new->next = temp;
          new->prev = node;
      }
      list->size++;
  }

void
temp_erase(TempL2 *list, int pos) {
    if (pos < 0 || list == NULL || pos >= list->size || list->size == 0) {
        fprintf(stderr, "l2s_erase error\n");
        fflush(stderr);
        exit(1);
    }
    if (pos == 0) {
        TempL2Node *node = list->head;
        list->head = list->head->next;
        list->head->prev = NULL;
        free(node);
        list->size--;
        return;
    } else if (pos == list->size - 1) {
        TempL2Node *node = list->tail;
        list->tail = list->tail->prev;
        list->tail->next = NULL;
        list->size--;
        free(node);
        return;
    }

    TempL2Node *node = list->head;
    for (int i = 0; i < pos - 1; ++i) {
        node = node->next;
    }
    TempL2Node *del_node = node->next;
    node->next = node->next->next;
    node->next->prev = node;
    list->size--;
    free(del_node);
}

void
temp_update(TempL2 *list,char* elem, int pos) {
    TempL2Node *copy = list->head;
    if (pos < 0 || list->head == NULL || pos >= list->size) {
        fprintf(stderr, "l2_update pos error\n");
        fflush(stderr);
        exit(1);
    }
    for (int i = 0; i < pos; ++i) {
        if (copy == NULL) {
            fprintf(stderr, "l2_update pos > size");
            fflush(stderr);
            exit(1);
        }
        copy = copy->next;
    }
    copy->data = elem;
}

int
temp_find(TempL2Node *list, char *elem) {
      if (list == NULL) {
          fprintf(stderr, "l2_find error\n");
          fflush(stderr);
          exit(1);
      }
      int pos = 0;
      TempL2Node *node = list;
      while (node != NULL) {
          if (strcmp(node->data, elem) == 0) {
              return pos;
          }
          ++pos;
          node = node->next;
      }
      return -1;
  }

void
temp_free(TempL2 *list) {
    TempL2 *copy = list;
    while (1) {
        if (list->head == NULL) {
            break;
        }
        copy->head = copy->head->next;
        free(list->head);
    }
}

char*
temp_get(TempL2 *list, int pos) {
    if (pos == 0 || list == NULL || pos >= list->size) {
        fprintf(stderr, "t_get err\n");
        fflush(stderr);
        exit(1);
    }
    TempL2Node *node = list->head;
    for (int i = 0; i < pos; ++i) {
        node = node->next;
    }
    return node->data;
}
