//
// Created by Valerio on 23/11/2019.
//

#ifndef TICTACTOE_HEAP_H
#define TICTACTOE_HEAP_H

#include "../common/util.h"

#define PARENT(x) (x >> 1)
#define LEFT_CHILD(x) (x << 1)
#define RIGHT_CHILD(x) ((x << 1) + 1)

#define DECLARE_HEAP(TYPE)\
typedef int(*TYPE##HeapProperty)(TYPE a, TYPE b);\
\
typedef struct TYPE##Heap TYPE##Heap;\
\
TYPE##Heap TYPE##HeapCreate(TYPE##HeapProperty property);\
void TYPE##HeapInsert(TYPE##Heap* heap, TYPE value);\
void TYPE##HeapHeapify(TYPE##Heap* heap, int parent);\
TYPE TYPE##HeapRemove(TYPE##Heap* heap);\
void TYPE##HeapFree(TYPE##Heap* heap);\

#define DEFINE_HEAP(TYPE, MAXIMUM_CAPACITY)\
struct TYPE##Heap {\
    TYPE##HeapProperty property;\
    int size;\
    TYPE* data;\
};\
\
TYPE##Heap TYPE##HeapCreate(TYPE##HeapProperty property){\
    TYPE##Heap heap;\
    heap.size = 0;\
    heap.property = property;\
    heap.data = (TYPE*) malloc(MAXIMUM_CAPACITY * sizeof(TYPE));\
    return heap;\
}\
\
void TYPE##HeapInsert(TYPE##Heap* heap, TYPE value){\
    heap->data[++heap->size] = value;\
    \
    int child = heap->size;\
    int parent = PARENT(child);\
    \
    while(parent >= 1 && !heap->property(heap->data[parent], heap->data[child])){\
        SWAP(TYPE, heap->data[parent], heap->data[child]);\
        child = parent;\
        parent = PARENT(parent);\
    }\
}\
\
void TYPE##HeapHeapify(TYPE##Heap* heap, int parent){\
    int leftChild = LEFT_CHILD(parent);\
    int rightChild = RIGHT_CHILD(parent);\
    int selected = parent;\
    \
    if(leftChild <= heap->size){\
        if(heap->property(heap->data[leftChild], heap->data[parent])){\
            selected = leftChild;\
        }\
    }\
    if(rightChild <= heap->size){\
        if(heap->property(heap->data[rightChild], heap->data[selected])){\
            selected = rightChild;\
        }\
    }\
    \
    if(selected != parent){\
        SWAP(TYPE, heap->data[selected], heap->data[parent]);\
        TYPE##HeapHeapify(heap, selected);\
    }\
}\
\
TYPE TYPE##HeapRemove(TYPE##Heap* heap){\
    TYPE item = heap->data[1];\
    SWAP(TYPE, heap->data[1], heap->data[heap->size]);\
    heap->size--;\
    TYPE##HeapHeapify(heap, 1);\
    return item;\
}\
\
void TYPE##HeapFree(TYPE##Heap* heap){\
    free(heap->data);\
}\

#endif //TICTACTOE_HEAP_H
