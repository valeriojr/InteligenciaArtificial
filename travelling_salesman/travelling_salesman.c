//
// Created by Valerio on 05/11/2019.
//

#include <stdio.h>
#include "travelling_salesman.h"


/*
 * Calcula a distância total percorrida na rota. A função retorna um valor negativo porque o hill climbing vai tentar
 * maximizar esse valor.
 */
float routeDistance(Route* route) {
    float d = 0.0F;
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
