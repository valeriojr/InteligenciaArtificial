//
// Created by Valerio on 17/11/2019.
//

#ifndef ARTIFICIALINTELLIGENCE_STATE_H
#define ARTIFICIALINTELLIGENCE_STATE_H


/*
 * Define variáveis e funções utilizadas pelos algoritmos de acordo com o tipo passado.
 */
#define DEFINE_STATE(STATE, ...)\
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
STATE##Action STATE##Actions[] = {__VA_ARGS__};\
\
/*
 * Número total de operadores
 */\
int STATE##ActionCount = sizeof(STATE##Actions) / sizeof(STATE##Action);\
\
/*
 * Nomes dos operadores (usado para imprimir solução)
 */\
char STATE##ActionNames[] = #__VA_ARGS__;\
\
/*
 * Função de validação (obrigatória)
 */\
STATE##ValidationFunction STATE##Validate;\
\
/*
 * Função de validação (obrigatória)
 */\
STATE##GoalFunction STATE##Goal;\
\
/*
 * Função de avaliação (obrigatória)
 */\
STATE##ScoreFunction STATE##Score;\
\
/*
 * Função de imprimir estado (opcional)
 */\
STATE##PrintFunction STATE##Print;\
\
\
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

#endif //ARTIFICIALINTELLIGENCE_STATE_H
