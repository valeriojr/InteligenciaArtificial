//
// Created by Valerio on 16/11/2019.
//

#ifndef ARTIFICIALINTELLIGENCE_LINKED_LIST_H
#define ARTIFICIALINTELLIGENCE_LINKED_LIST_H

#include <stdlib.h>
#include "../common/util.h"

#define DEFINE_LINKED_LIST(TYPE)\
\
typedef struct TYPE##ListNode {\
    TYPE value;\
    struct TYPE##ListNode* next;\
} TYPE##ListNode;\
\
typedef struct TYPE##List {\
    TYPE##ListNode* head;\
    TYPE##ListNode* tail;\
    int size;\
} TYPE##List;\
\
\
TYPE##ListNode* TYPE##ListNodeCreate(TYPE value){\
    TYPE##ListNode* node = malloc(sizeof(TYPE##ListNode));\
    node->value = value;\
    node->next = NULL;\
    \
    return node;\
}\
\
void TYPE##ListFree(TYPE##List* list){\
    TYPE##ListNode* head = list->head;\
    \
    while(head){\
        TYPE##ListNode* next = head->next;\
        free(head);\
        head = next;\
    }\
}\
\
void TYPE##ListMap(TYPE##List* list, void (*f)(TYPE*)){\
    TYPE##ListNode* head = list->head;\
    \
    while(head){\
        f(&head->value);\
        head = head->next;\
    }\
}\
\
TYPE##ListNode* TYPE##ListAppend(TYPE##List* list, TYPE value){\
    TYPE##ListNode* node = TYPE##ListNodeCreate(value);\
    if(list->head == NULL){\
        list->head = node;\
        list->tail = node;\
    }\
    else {\
        list->tail->next = node;\
    }\
    list->tail = node;\
    list->size++;\
    return node;\
}\
\
TYPE* TYPE##ListFront(TYPE##List* list){\
    return &list->head->value;\
}\
\
TYPE* TYPE##ListBack(TYPE##List* list){\
    return &list->tail->value;\
}\
\
void TYPE##ListPopFront(TYPE##List* list){\
    TYPE##ListNode* node = list->head;\
    list->head = node->next;\
    node->next = NULL;\
    free(node);\
    list->size--;\
}\
\
TYPE##List TYPE##ListCreate(){\
    TYPE##List list;\
    list.head = NULL;\
    list.tail = NULL;\
    list.size = 0;\
    return list;\
}\

#endif //ARTIFICIALINTELLIGENCE_LINKED_LIST_H
