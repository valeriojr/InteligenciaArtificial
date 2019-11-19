//
// Created by ValérioRodrigues on 19/11/2019.
//
#include <stdio.h>
#include <stdlib.h>
#include "../search/hill_climbing.h"
#include "travelling_salesman.h"


DEFINE_HILL_CLIMBING(Route)

int main() {
    RouteScore = routeDistance;
    RouteValidate = routeValidate;
    RoutePrint = routePrint;

    Route initial = {
            .cities = {0, 3, 7, 2, 9, 5, 4, 8, 6, 1} // Encontrei esse estado inicial válido aplicando os operadores
    };                                               // aleatoriamente no estado [0 1 2 3 4 5 6 7 8 9 0].


    printf("Initial route: ");
    routePrint(&initial);
    printf("cost: %.1f\n", -routeDistance(&initial));

    Route bestRoute = RouteHillClimb(&initial, 1000); // Aparentemente o estado inicial está perto de um
    // máximo local

    printf("Best route: ");
    routePrint(&bestRoute);
    printf("cost: %.1f\n", -routeDistance(&bestRoute));

    return 0;
}