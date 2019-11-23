//
// Created by Valerio on 17/11/2019.
//

#ifndef ARTIFICIAL_INTELLIGENCE_STATE_H
#define ARTIFICIAL_INTELLIGENCE_STATE_H

#include <ctype.h>


/*
 * Define variáveis e funções utilizadas pelos algoritmos de acordo com o tipo passado.
 */
#define DECLARE_STATE(STATE)\
/*
 * Interface para os operadores
 * Entrada: estado atual
 * Saída: próximo estado
 */\
typedef STATE (*STATE##Action)(STATE);\
\
/*
 * Interface para validação do estado
 * Entrada: endereço do estado
 * Saída: 1 se o estado for válido, 0 caso contrário
 */\
typedef int (*STATE##ValidationFunction)(STATE*);\
\
/*
 * Interface para verificação de estados objetivo
 * Entrada: endereço do estado
 * Saída: 1 se o estado for objetivo, 0 caso contrário
 */\
typedef int (*STATE##GoalFunction)(STATE*);\
\
/*
 * Interface para imprimir o estado
 * Entrada: endereço do estado
 * Saída: nada
 */\
typedef void (*STATE##PrintFunction)(STATE*);\
\
/*
 * Interface para avaliação de estados
 * Entrada: endereço do estado
 * Saída: avaliação do estado
 */\
typedef float (*STATE##ScoreFunction)(STATE*);\
\
\
/*
 * Lista dos operadores
 */\
extern STATE##Action STATE##Actions[];\
\
/*
 * Número total de operadores
 */\
extern int STATE##ActionCount;\
\
/*
 * Nomes dos operadores (usado para imprimir solução)
 */\
extern char STATE##ActionNames[];\
\
/*
 * Função de validação (obrigatória)
 */\
extern STATE##ValidationFunction STATE##Validate;\
\
/*
 * Função de validação (obrigatória)
 */\
extern STATE##GoalFunction STATE##Goal;\
\
/*
 * Função de avaliação
 */\
extern STATE##ScoreFunction STATE##Score;\
\
/*
 * Função de heurística (A*)
 */\
extern STATE##ScoreFunction STATE##Heuristic;\
\
/*
 * Função de imprimir estado (opcional)
 */\
extern STATE##PrintFunction STATE##Print;\
\
void STATE##GetActionName(char* dest, int index);\
\
float STATE##UniformCost(STATE* state);\

#define DEFINE_STATE(STATE, ...)\
STATE##Action STATE##Actions[] = {__VA_ARGS__};\
int STATE##ActionCount = sizeof(STATE##Actions) / sizeof(STATE##Action);\
char STATE##ActionNames[] = #__VA_ARGS__;\
\
STATE##ValidationFunction STATE##Validate = NULL;\
STATE##GoalFunction STATE##Goal = NULL;\
STATE##ScoreFunction STATE##Score = STATE##UniformCost;\
STATE##ScoreFunction STATE##Heuristic = NULL;\
STATE##PrintFunction STATE##Print = NULL;\
/*
 * Copia o nome do operador com índice index para o endereço dest
 */\
void STATE##GetActionName(char* dest, int index){\
    char* names = STATE##ActionNames;\
    \
    for(;*names;names++){\
        if(!index){\
            break;\
        }\
        if(*names == ','){\
            index--;\
        }\
    }\
    for(;*names;names++){\
        if(*names == ','){\
            break;\
        }\
        *dest = *names;\
        dest++;\
    }\
    \
    *dest = '\0';\
}\
float STATE##UniformCost(STATE* state){\
    return 1.0f;\
}\

#endif //ARTIFICIALINTELLIGENCE_STATE_H
