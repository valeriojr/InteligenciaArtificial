//
// Created by Valerio on 05/11/2019.
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
            {0, 3, 7, 2, 9, 5, 4, 8, 6, 1} // Encontrei esse estado inicial válido aqui aplicando os operadores
    };                                     // aleatoriamente no estado [0 1 2 3 4 5 6 7 8 9 0].


    printf("Initial route: ");
    routePrint(&initial);
    printf("cost: %.1f\n", -routeDistance(&initial));

    Route bestRoute = RouteHillClimb(&initial, 1000); // Aparentemente o estado inicial está perto de um máximo local

    printf("Best route: ");
    routePrint(&bestRoute);
    printf("cost: %.1f\n", -routeDistance(&bestRoute));

    return 0;
}

/*
 * Calcula a distância total percorrida na rota. A função retorna um valor negativo porque o hill climbing vai tentar
 * maximizar esse valor.
 */
float routeDistance(Route* route) {
    float d = 0.0f;
    int i;

    for(i = 0;i < N_CITIES - 1;i++){
        d += cost[route->cities[i]][route->cities[i+1]];
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
    for(i = 0;i < N_CITIES;i++){
        visited[route->cities[i]] = 1;
    }
    for(i = 0;i < N_CITIES;i++){
        if(!visited[i]){
            return 0;
        }
    }

    float d = -routeDistance(route);

    return d < inf;
}

void routePrint(Route* route) {
    int i;
    for (i = 0; i < N_CITIES; i++) {
        printf("%d ", route->cities[i]);
    }
    printf("%d\n", route->cities[0]);
}
