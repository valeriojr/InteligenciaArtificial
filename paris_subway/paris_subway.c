//
// Created by Valerio on 23/11/2019.
//

#include <stdio.h>
#include "paris_subway.h"

#define DEFINE_STATION_ACTION(STATION)\
Station GoToStation##STATION(Station state){\
    state.previousColor = state.color;\
    state.color = subwayLines[state.number][STATION - 1].color;\
    state.previous = state.number;\
    state.number = STATION-1;\
    return state;\
}\

SubwayLine subwayLines[][14] = {
        {{0,  Invalid}, {11, Blue},    {20, Invalid}, {27, Invalid}, {40, Invalid}, {43, Invalid}, {39, Invalid},
         {28, Invalid}, {18, Invalid}, {10, Invalid}, {18, Invalid}, {30, Invalid}, {30, Invalid}, {32, Invalid}},
        {{11, Blue},    {0,  Invalid}, {9,  Blue},    {16, Invalid}, {29, Invalid}, {32, Invalid}, {28, Invalid},
         {19, Invalid}, {11, Yellow},  {4,  Yellow},  {17, Invalid}, {23, Invalid}, {21, Invalid}, {24, Invalid}},
        {{20, Invalid}, {9,  Blue},    {0,  Invalid}, {7,  Blue},    {20, Invalid}, {22, Invalid}, {19, Invalid},
         {15, Invalid}, {10, Red},     {11, Invalid}, {21, Invalid}, {21, Invalid}, {13, Red},     {18, Invalid}},
        {{27, Invalid}, {16, Invalid}, {7,  Blue},    {0,  Invalid}, {13, Blue},    {16, Invalid}, {12, Invalid},
         {13, Green},   {13, Invalid}, {18, Invalid}, {26, Invalid}, {21, Invalid}, {11, Green},   {17, Invalid}},
        {{40, Invalid}, {29, Invalid}, {20, Invalid}, {13, Blue},    {0,  Invalid}, {3,  Blue},    {2,  Yellow},
         {21, Yellow},  {25, Invalid}, {31, Invalid}, {38, Invalid}, {27, Invalid}, {16, Invalid}, {20, Invalid}},
        {{43, Invalid}, {32, Invalid}, {22, Invalid}, {16, Invalid}, {3,  Blue},    {0,  Invalid}, {4,  Invalid},
         {23, Invalid}, {28, Invalid}, {33, Invalid}, {41, Invalid}, {30, Invalid}, {17, Invalid}, {20, Invalid}},
        {{39, Invalid}, {28, Invalid}, {19, Invalid}, {12, Invalid}, {2,  Yellow},  {4,  Invalid}, {0,  Invalid},
         {22, Invalid}, {25, Invalid}, {29, Invalid}, {38, Invalid}, {28, Invalid}, {13, Invalid}, {17, Invalid}},
        {{28, Invalid}, {19, Invalid}, {15, Invalid}, {13, Green},   {21, Yellow},  {23, Invalid}, {22, Invalid},
         {0,  Invalid}, {9,  Yellow},  {22, Invalid}, {18, Invalid}, {7,  Green},   {25, Invalid}, {30, Invalid}},
        {{18, Invalid}, {11, Yellow},  {10, Red},     {13, Invalid}, {25, Invalid}, {28, Invalid}, {25, Invalid},
         {9,  Yellow},  {0,  Invalid}, {13, Invalid}, {12, Red},     {12, Invalid}, {23, Invalid}, {28, Invalid}},
        {{10, Invalid}, {4,  Yellow},  {11, Invalid}, {18, Invalid}, {31, Invalid}, {33, Invalid}, {29, Invalid},
         {22, Invalid}, {13, Invalid}, {0,  Invalid}, {20, Invalid}, {27, Invalid}, {20, Invalid}, {23, Invalid}},
        {{18, Invalid}, {17, Invalid}, {21, Invalid}, {26, Invalid}, {38, Invalid}, {41, Invalid}, {38, Invalid},
         {18, Invalid}, {12, Red},     {20, Invalid}, {0,  Invalid}, {15, Invalid}, {35, Invalid}, {39, Invalid}},
        {{30, Invalid}, {23, Invalid}, {21, Invalid}, {21, Invalid}, {27, Invalid}, {30, Invalid}, {28, Invalid},
         {7,  Green},   {12, Invalid}, {27, Invalid}, {15, Invalid}, {0,  Invalid}, {31, Invalid}, {37, Invalid}},
        {{30, Invalid}, {21, Invalid}, {13, Red},     {11, Green},   {16, Invalid}, {17, Invalid}, {13, Invalid},
         {25, Invalid}, {23, Invalid}, {20, Invalid}, {35, Invalid}, {31, Invalid}, {0,  Invalid}, {5,  Green}},
        {{32, Invalid}, {24, Invalid}, {18, Invalid}, {17, Invalid}, {20, Invalid}, {20, Invalid}, {17, Invalid},
         {30, Invalid}, {28, Invalid}, {23, Invalid}, {39, Invalid}, {37, Invalid}, {5,  Green},   {0,  Invalid}}
};

DEFINE_STATE_SPACE(Subway, Station,
                   GoToStation1,
                   GoToStation2,
                   GoToStation3,
                   GoToStation4,
                   GoToStation5,
                   GoToStation6,
                   GoToStation7,
                   GoToStation8,
                   GoToStation9,
                   GoToStation10,
                   GoToStation11,
                   GoToStation12,
                   GoToStation13,
                   GoToStation14)


DEFINE_STATION_ACTION(1);

DEFINE_STATION_ACTION(2);

DEFINE_STATION_ACTION(3);

DEFINE_STATION_ACTION(4);

DEFINE_STATION_ACTION(5);

DEFINE_STATION_ACTION(6);

DEFINE_STATION_ACTION(7);

DEFINE_STATION_ACTION(8);

DEFINE_STATION_ACTION(9);

DEFINE_STATION_ACTION(10);

DEFINE_STATION_ACTION(11);

DEFINE_STATION_ACTION(12);

DEFINE_STATION_ACTION(13);

DEFINE_STATION_ACTION(14);


void SubwaySearchFinished(int success, Subway* solution) {
    if (success) {
        StationPrintSolution(solution);
        printf("Total time: %.1f minutes\n", solution->cost);
    } else {
        puts("Solution not found :c");
    }
}

void SubwayPrint(struct Station* state) {
    printf("Current station: %d\n", state->number + 1);
    char colors[][10] = {"Blue", "Green", "Red", "Yellow"};
    printf("Current line: %s\n", colors[state->color]);
}

int SubwayValidate(Station* state) {
    return state->color != Invalid;

}

int SubwayGoal(Station* state) {
    return state->number == goalStation;
}

float SubwayTimeCost(Station* station) {
    if (station->previous == -1) {
        return 0.0f;
    }
    float time = 60 * (subwayLines[station->previous][station->number].distance / 30.0f);
    if(station->previousColor != Invalid){
        time += 4 * (subwayLines[station->previous][station->number].color == station->color);
    }

    return time;
}

float SubwayHeuristic(Station* station) {
    return (subwayLines[station->number][goalStation].distance / 30.0f) * 60;
}

