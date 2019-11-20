//
// Created by Valerio on 18/11/2019.
//

#ifndef ARTIFICIAL_INTELLIGENCE_TRAVELLING_SALESMAN_H
#define ARTIFICIAL_INTELLIGENCE_TRAVELLING_SALESMAN_H

#include <math.h>
#include "../common/util.h"
#include "../common/state.h"

#define DECLARE_ROUTE_ACTION(FROM, TO)\
Route exchangeCities##FROM##And##TO(Route route);\


//----------------------------------------------------------------------------------------------------------------------

// Constantes

#define N_CITIES 10

extern float cost[10][10];

//----------------------------------------------------------------------------------------------------------------------

typedef struct Route {
    int cities[N_CITIES];
} Route;

//----------------------------------------------------------------------------------------------------------------------

DECLARE_ROUTE_ACTION(1, 2)

DECLARE_ROUTE_ACTION(2, 3)

DECLARE_ROUTE_ACTION(3, 4)

DECLARE_ROUTE_ACTION(4, 5)

DECLARE_ROUTE_ACTION(5, 6)

DECLARE_ROUTE_ACTION(6, 7)

DECLARE_ROUTE_ACTION(7, 8)

DECLARE_ROUTE_ACTION(8, 9)

//----------------------------------------------------------------------------------------------------------------------

DECLARE_STATE(Route)

//----------------------------------------------------------------------------------------------------------------------

float routeDistance(Route* route);

int routeValidate(Route* route);

void routePrint(Route* route);

#endif //ARTIFICIAL_INTELLIGENCE_TRAVELLING_SALESMAN_H
