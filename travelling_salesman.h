//
// Created by Valerio on 18/11/2019.
//

#ifndef ARTIFICIAL_INTELLIGENCE_TRAVELLING_SALESMAN_H
#define ARTIFICIAL_INTELLIGENCE_TRAVELLING_SALESMAN_H

#include "util.h"
#include "state.h"

#define N_CITIES 10


const float inf = 1000000.0f;

float cost[10][10] = {
        {0.0f,  30.0f, 84.0f,  56.0f,  inf,    inf,   inf,    75.0f,  inf,    80.0f},
        {30.0f, 0.0f,  65.0f,  inf,    inf,    inf,   70.0f,  inf,    inf,    40.0f},
        {84.0f, 65.0f, 0.0f,   74.0f,  52.0f,  55.0f, inf,    60.0f,  143.0f, 48.0f},
        {56.0f, inf,   74.0f,  0.0f,   135.0f, inf,   inf,    20.0f,  inf,    inf},
        {inf,   inf,   52.0f,  135.0f, 0.0f,   70.0f, inf,    122.0f, 98.0f,  80.0f},
        {70.0f, inf,   55.0f,  inf,    70.0f,  0.0f,  63.0f,  inf,    82.0f,  35.0f},
        {inf,   70.0f, inf,    inf,    inf,    63.0f, 0.0f,   inf,    120.0f, 57.0f},
        {75.0f, inf,   135.0f, 20.0f,  122.0f, inf,   inf,    0.0f,   inf,    inf},
        {inf,   inf,   143.0f, inf,    98.0f,  82.0f, 120.0f, inf,    0.0f,   inf},
        {80.0f, 40.0f, 48.0f,  inf,    80.0f,  35.0f, 57.0f,  inf,    inf,    0.0f}
};

typedef struct Route {
    int cities[N_CITIES];
} Route;

#define ROUTE_ACTION(FROM, TO)\
Route exchangeCities##FROM##And##TO(Route route){\
    SWAP(int, route.cities[FROM], route.cities[TO]);\
    return route;\
}\

ROUTE_ACTION(1, 2)
ROUTE_ACTION(2, 3)
ROUTE_ACTION(3, 4)
ROUTE_ACTION(4, 5)
ROUTE_ACTION(5, 6)
ROUTE_ACTION(6, 7)
ROUTE_ACTION(7, 8)
ROUTE_ACTION(8, 9)

DEFINE_STATE(Route, exchangeCities1And2, exchangeCities2And3, exchangeCities3And4, exchangeCities4And5,
             exchangeCities5And6, exchangeCities6And7, exchangeCities7And8, exchangeCities8And9)

float routeDistance(Route* route);

int routeValidate(Route* route);

void routePrint(Route* route);

#endif //ARTIFICIAL_INTELLIGENCE_TRAVELLING_SALESMAN_H
