//
// Created by Valerio on 17/11/2019.
//

#ifndef ARTIFICIAL_INTELLIGENCE_MINIMAX_H
#define ARTIFICIAL_INTELLIGENCE_MINIMAX_H

#include <limits.h>
#include "state.h"
#include "util.h"

enum {
    MIN,
    MAX
};

#define DEFINE_MINIMAX(STATE, ...)\
DEFINE_STATE(STATE, __VA_ARGS__)\
typedef int (*STATE##ScoreFunction)(STATE*);\
\
STATE##ScoreFunction STATE##Score;\
int STATE##MinimaxSearch(STATE* current_state, int turn, int depth, int* child){\
    if(!depth){\
        return STATE##Score(current_state);\
    }\
    int alpha;\
    int child_count = 0;\
    \
    if(turn == MAX){\
        alpha = INT_MIN;\
        \
        int i;\
        for(i = 0;i < STATE##ActionCount;i++){\
            STATE child_state = STATE##Actions[i](*current_state);\
            if(!STATE##Validate(&child_state)){\
                continue;\
            }\
            child_count++;\
            int score = STATE##MinimaxSearch(&child_state, !turn, depth - 1, child);\
            if(score > alpha){\
                alpha = score;\
                *child = i;\
            }\
        }\
        return child_count ? alpha : STATE##Score(current_state);\
    }\
    else {\
        alpha = INT_MAX;\
        \
        int i;\
        for(i = 0;i < STATE##ActionCount;i++){\
            STATE child_state = STATE##Actions[i](*current_state);\
            if(!STATE##Validate(&child_state)){\
                continue;\
            }\
            child_count++;\
            int score = STATE##MinimaxSearch(&child_state, !turn, depth - 1, child);\
            if(score < alpha){\
                alpha = score;\
                *child = i;\
            }\
        }\
        return child_count ? alpha : STATE##Score(current_state);\
    }\
}\
\
void STATE##Minimax(STATE* current_state, int depth, void(*callback)(int, int, STATE*)){\
    if(STATE##Score == NULL){\
        printf("Undefined GOAL and/or VALIDATION function(s)!\n");\
        if(callback) callback(-1, INT_MIN, NULL);\
        return;\
    }\
    int actionIndex = -1;\
    \
    int score = STATE##MinimaxSearch(current_state, MAX, depth, &actionIndex);\
    getchar();\
    if(actionIndex >= 0){\
        callback(actionIndex, score, current_state);\
    }\
}\
\


#endif //ARTIFICIAL_INTELLIGENCE_MINIMAX_H
