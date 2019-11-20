//
// Created by Valerio on 17/11/2019.
//

#ifndef ARTIFICIAL_INTELLIGENCE_MINIMAX_H
#define ARTIFICIAL_INTELLIGENCE_MINIMAX_H

#include <limits.h>
#include "../common/state.h"
#include "../common/util.h"

enum {
    MIN,
    MAX
};

#define DECLARE_MINIMAX(STATE, ...)\
DECLARE_STATE(STATE)\
int STATE##MinimaxSearch(STATE* currentState, int turn, int depth, int* child);\
\
void STATE##Minimax(STATE* currentState, int depth, void(*callback)(int, int, STATE*));\

#define DEFINE_MINIMAX(STATE, ...)\
DEFINE_STATE(STATE, __VA_ARGS__)\
int STATE##MinimaxSearch(STATE* currentState, int turn, int depth, int* child){\
    if(!depth){\
        return STATE##Score(currentState);\
    }\
    int alpha;\
    int childCount = 0;\
    \
    if(turn == MAX){\
        alpha = INT_MIN;\
        \
        int i;\
        for(i = 0;i < STATE##ActionCount;i++){\
            STATE childState = STATE##Actions[i](*currentState);\
            if(!STATE##Validate(&childState)){\
                continue;\
            }\
            childCount++;\
            int score = STATE##MinimaxSearch(&childState, !turn, depth - 1, child);\
            if(score > alpha){\
                alpha = score;\
                *child = i;\
            }\
        }\
        return childCount ? alpha : STATE##Score(currentState);\
    }\
    else {\
        alpha = INT_MAX;\
        \
        int i;\
        for(i = 0;i < STATE##ActionCount;i++){\
            STATE childState = STATE##Actions[i](*currentState);\
            if(!STATE##Validate(&childState)){\
                continue;\
            }\
            childCount++;\
            int score = STATE##MinimaxSearch(&childState, !turn, depth - 1, child);\
            if(score < alpha){\
                alpha = score;\
                *child = i;\
            }\
        }\
        return childCount ? alpha : STATE##Score(currentState);\
    }\
}\
\
void STATE##Minimax(STATE* currentState, int depth, void(*callback)(int, int, STATE*)){\
    if(STATE##Score == NULL){\
        printf("Undefined GOAL and/or VALIDATION function(s)!\n");\
        if(callback) callback(-1, INT_MIN, NULL);\
        return;\
    }\
    int actionIndex = -1;\
    \
    int score = STATE##MinimaxSearch(currentState, MAX, depth, &actionIndex);\
    getchar();\
    if(actionIndex >= 0){\
        callback(actionIndex, score, currentState);\
    }\
}\
\


#endif //ARTIFICIAL_INTELLIGENCE_MINIMAX_H
