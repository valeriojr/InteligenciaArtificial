//
// Created by Valerio on 05/11/2019.
//

#include <stdio.h>
#include "travelling_salesman.h"

#define DEFINE_ROUTE_ACTION(FROM, TO)\
Route exchangeCities##FROM##And##TO(Route route){\
    SWAP(int, route.cities[FROM], route.cities[TO]);\
    return route;\
}\


float cost[N_CITIES][N_CITIES] = {
        {0.0f,     30.0f,    84.0f,  56.0f,    INFINITY, INFINITY, INFINITY, 75.0f,  INFINITY, 80.0f},
        {30.0f,    0.0f,     65.0f,  INFINITY, INFINITY, INFINITY, 70.0f,  INFINITY, INFINITY, 40.0f},
        {84.0f,    65.0f,    0.0f,   74.0f,    52.0f,    55.0f,    INFINITY, 60.0f,  143.0f,   48.0f},
        {56.0f,    INFINITY, 74.0f,  0.0f,     135.0f,   INFINITY, INFINITY, 20.0f,  INFINITY, INFINITY},
        {INFINITY, INFINITY, 52.0f,  135.0f,   0.0f,     70.0f,    INFINITY, 122.0f, 98.0f,    80.0f},
        {70.0f,    INFINITY, 55.0f,  INFINITY, 70.0f,    0.0f,     63.0f,  INFINITY, 82.0f,    35.0f},
        {INFINITY, 70.0f, INFINITY,  INFINITY, INFINITY, 63.0f,    0.0f,   INFINITY, 120.0f,   57.0f},
        {75.0f,    INFINITY, 135.0f, 20.0f,    122.0f,   INFINITY, INFINITY, 0.0f,   INFINITY, INFINITY},
        {INFINITY, INFINITY, 143.0f, INFINITY, 98.0f,    82.0f,    120.0f, INFINITY, 0.0f,     INFINITY},
        {80.0f,    40.0f,    48.0f,  INFINITY, 80.0f,    35.0f,    57.0f,  INFINITY, INFINITY, 0.0f}
};


DEFINE_ROUTE_ACTION(1, 2);

DEFINE_ROUTE_ACTION(2, 3);

DEFINE_ROUTE_ACTION(3, 4);

DEFINE_ROUTE_ACTION(4, 5);

DEFINE_ROUTE_ACTION(5, 6);

DEFINE_ROUTE_ACTION(6, 7);

DEFINE_ROUTE_ACTION(7, 8);

DEFINE_ROUTE_ACTION(8, 9);

DEFINE_STATE(Route,
             exchangeCities1And2,
             exchangeCities2And3,
             exchangeCities3And4,
             exchangeCities4And5,
             exchangeCities5And6,
             exchangeCities6And7,
             exchangeCities7And8,
             exchangeCities8And9)

/*
 * Calcula a distância total percorrida na rota. A função retorna um valor negativo porque o hill climbing vai tentar
 * maximizar esse valor.
 */
float routeDistance(Route* route) {
    float d = 0.0F;
    int i;

    for (i = 0; i < N_CITIES - 1; i++) {
        d += cost[route->cities[i]][route->cities[i + 1]];
    }

    d += cost[route->cities[N_CITIES - 1]][route->cities[0]];

    return -d;
}

/*
 * Primeiro verifica se todas as cidade apareceram na rota, depois se a distância é menor que infinito (se for maior é
 * porque a rota faz um caminho que não existe)
 */
int routeValidate(Route* route) {
    int visited[N_CITIES] = {0};
    int i;
    for (i = 0; i < N_CITIES; i++) {
        visited[route->cities[i]] = 1;
    }
    for (i = 0; i < N_CITIES; i++) {
        if (!visited[i]) {
            return 0;
        }
    }

    float d = -routeDistance(route);

    return d < INFINITY;
}

void routePrint(Route* route) {
    int i;
    for (i = 0; i < N_CITIES; i++) {
        printf("%d ", route->cities[i]);
    }
    printf("%d\n", route->cities[0]);
}
