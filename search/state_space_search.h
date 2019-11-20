//
// Created by Valerio on 16/11/2019.
//

#ifndef ARTIFICIAL_INTELLIGENCE_STATE_SPACE_SEARCH_H
#define ARTIFICIAL_INTELLIGENCE_STATE_SPACE_SEARCH_H

#include "../data_structures/linked_list.h"
#include "../common/state.h"

#define DECLARE_NODE(NAME, STATE)\
typedef struct NAME NAME;\
DECLARE_LINKED_LIST(NAME)\

/*
* Nó da fronteira/visitados. A estrutura de dados (nó) que a busca usa é separada do estado
* state: estado do nó
* parent: ponteiro para o nó que guarda o passo anterior da solução
* index: índice do operador utilizado no estado do nó pai para gerar esse estado
* depth: profundidade do nó na árvore de busca
* cost: custo para chegar até este nó na árvore de busca
*/
#define DEFINE_NODE(NAME, STATE_TYPE)\
typedef struct NAME{\
    STATE_TYPE state;\
    struct NAME* parent;\
    int index;\
    int depth;\
    float cost;\
} NAME;\
DEFINE_LINKED_LIST(NAME)\


#define DECLARE_STATE_SPACE(NODE, STATE, ...)\
DECLARE_NODE(NODE, STATE)\
DECLARE_STATE(STATE, __VA_ARGS__)\
\
void STATE##Search(STATE initial,  void(*callback)(int, NODE*));\
\
void STATE##PrintSolution(NODE* node);\

/*
* Define o nó e o espaço de estados
*/
#define DEFINE_STATE_SPACE(NODE, STATE, ...)\
DEFINE_NODE(NODE, STATE)\
DEFINE_STATE(STATE, __VA_ARGS__)\
\
/*
 * Realiza a busca no espaço de estados a partir de inicial e chama a função callback indicando se a solução foi
 * encontrada e o último nó da solução
 */\
void STATE##Search(STATE initial,  void(*callback)(int, NODE*)) {\
    /*
    * Verifica se as funções de validação e de objetivo foram definidas
    */\
    if(!STATE##Goal || !STATE##Validate){\
        printf("Undefined GOAL and/or VALIDATION function(s)!\n");\
        if(callback) callback(0, NULL);\
        return;\
    }\
    /*
    * Fronteira e lista de nós visitados
    */\
    NODE##List boundary = NODE##ListCreate();\
    NODE##List visited = NODE##ListCreate();\
    \
    /*
    * Nó inicial
    */\
    NODE s = {\
            .state = initial,\
            .cost = 0,\
            .depth = 0,\
            .index = -1,\
            .parent = NULL\
    };\
    NODE##ListAppend(&boundary, s);\
    \
    NODE* currentNode = NODE##ListFront(&boundary);\
    \
    int success = 0;\
    \
    while (currentNode && !success) {\
        /*
        * Retira o próximo nó da fronteira
        */\
        currentNode = NODE##ListFront(&boundary);\
        if(!currentNode) break;\
        /*
        * Verifica se ele é solução
        */\
        if (STATE##Goal(&currentNode->state)) {\
            if(callback){\
                callback(1, currentNode);\
            }\
            success = 1;\
            break;\
        }\
        \
        /*
        * Coloca na lista de visitados (cria uma cópia do nó que estava na fronteira para poder construir o caminho da
        * solução)
        */\
        NODE##ListAppend(&visited, *currentNode);\
        currentNode = NODE##ListBack(&visited);\
        \
        /*
        * Gera os filhos
        */\
        int i;\
        for(i = 0;i < STATE##ActionCount;i++){\
            NODE child = *currentNode;\
            STATE childState = STATE##Actions[i](child.state);\
            if (STATE##Validate(&childState)) {\
                child.state = childState;\
                child.index = i;\
                /*
                * O pai é o nó da lista de visitados, não o da fronteira
                */\
                child.parent = currentNode;\
                child.depth++;\
                child.cost++;\
                NODE##ListAppend(&boundary, child);\
            }\
        }\
        \
        /*
        * O nó que foi tirado da fronteira é destruído
        */\
        NODE##ListPopFront(&boundary);\
    }\
    \
    /*
    * Solução não encontrada
    */\
    if(callback && !success){callback(0, NULL);}\
    \
    /*
    * Libera os nós visitados e a fronteira da memória
    */\
    NODE##ListFree(&boundary);\
    NODE##ListFree(&visited);\
}\
\
/*
* Imprime a solução em pré-ordem (do estado inicial ao estado final)
*/\
void STATE##PrintSolution(NODE* node) {\
    if(!STATE##Print){\
        printf("Undefined PRINT function!\n");\
        return;\
    }\
    if (!node) {\
        return;\
    }\
    if (node->parent) {\
        STATE##PrintSolution(node->parent);\
    } else {\
        puts("Initial State:");\
        STATE##Print(&node->state);\
        printf("\n");\
    }\
    if (node->index >= 0) {\
        char actionName[256] = "";\
        STATE##GetActionName(actionName, node->index);\
        int i;\
        for (i = 0; isspace(actionName[i]); i++);\
        printf("*%s\n", actionName + i);\
        STATE##Print(&node->state);\
        printf("\n");\
    }\
}\

#endif //ARTIFICIAL_INTELLIGENCE_STATE_SPACE_SEARCH_H
