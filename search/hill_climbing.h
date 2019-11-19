//
// Created by Valerio on 18/11/2019.
//

#ifndef TICTACTOE_HILL_CLIMBING_H
#define TICTACTOE_HILL_CLIMBING_H

#include <math.h>


typedef struct STATE STATE;

#define DEFINE_HILL_CLIMBING(STATE)\
STATE STATE##HillClimb(STATE* initialSolution, int maxIterations){\
    /*
    * Checa se a função de avaliação está definida
    */\
    \
    if(STATE##Score == NULL || STATE##Validate == NULL){\
        printf("Undefined Score and/or Validate function!\n");\
        return *initialSolution;\
    }\
    \
    STATE currentBestSolution = *initialSolution;\
    float currentBestScore = STATE##Score(initialSolution);\
    \
    while(maxIterations--){\
        /*
        * Gera as soluções vizinhas
        */\
        int i, j;\
        STATE neighbors[STATE##ActionCount];\
        for(i = 0;i < STATE##ActionCount; i++){\
            STATE neighbor = STATE##Actions[i](currentBestSolution);\
            if(STATE##Validate(&neighbor)){\
                neighbors[j++] = neighbor;\
            }\
        }\
        /*
        * Se não houver soluções vizinhas retorna a atual
        */\
        if(!j){\
            return currentBestSolution;\
        }\
        \
        \
        /*
        * Avalia as soluções vizinhas e escolhe a melhor (steepest hill climbing)
        */\
        STATE* nextSolution = NULL;\
        \
        for(i = 0;i < j;i++){\
            float score = STATE##Score(&neighbors[i]);\
            if(score > currentBestScore){\
                currentBestScore = score;\
                nextSolution = neighbors + i;\
            }\
        }\
        \
        if(nextSolution == NULL){\
            return currentBestSolution;\
        }\
        \
        currentBestSolution = *nextSolution;\
    }\
    \
    return currentBestSolution;\
}\

#endif //TICTACTOE_HILL_CLIMBING_H
