//
// Created by Valerio on 16/11/2019.
//

/*
 *
 *  Definição do estado para o problema dos missionários e implementação dos operadores e de utilidades (testar se o
 *  estado é um objetivo, testar se o estado é válido e imprimir o estado na tela).
 *
 */

#ifndef ARTIFICIALINTELLIGENCE_MISSIONARIES_H
#define ARTIFICIALINTELLIGENCE_MISSIONARIES_H

#include "../common/util.h"

#define N_MISSIONARIES 3
#define N_CANNIBALS 3

/*
 * side: margem em que o barco está (0: margem esquerda, 1: margem direita)
 * missionaries: número de missionários em cada margem
 * cannibals: número de canibais em cada margem
 */
typedef struct MissionaryState {
    int side;
    int missionaries[2];
    int cannibals[2];
} MissionaryState;

MissionaryState TakeOneMissionary(MissionaryState parent) {
    parent.missionaries[parent.side]--;
    parent.missionaries[!parent.side]++;
    parent.side = !parent.side;

    return parent;
}

MissionaryState TakeOneCannibal(MissionaryState parent) {
    parent.cannibals[parent.side]--;
    parent.cannibals[!parent.side]++;
    parent.side = !parent.side;

    return parent;
}

MissionaryState TakeTwoMissionaries(MissionaryState parent) {
    parent.missionaries[parent.side] -= 2;
    parent.missionaries[!parent.side] += 2;
    parent.side = !parent.side;

    return parent;
}

MissionaryState TakeTwoCannibals(MissionaryState parent) {
    parent.cannibals[parent.side] -= 2;
    parent.cannibals[!parent.side] += 2;
    parent.side = !parent.side;

    return parent;
}

MissionaryState TakeOneMissionaryAndOneCannibal(MissionaryState parent) {
    parent.missionaries[parent.side]--;
    parent.missionaries[!parent.side]++;
    parent.cannibals[parent.side]--;
    parent.cannibals[!parent.side]++;
    parent.side = !parent.side;
    return parent;
}

void MissionaryPrint(MissionaryState* state) {
    printf("|Side: %s\n", state->side ? "right" : "left");
    printf("|Missionaries: left: %d, right: %d\n", state->missionaries[0], state->missionaries[1]);
    printf("|Cannibals: left: %d, right: %d\n", state->cannibals[0], state->cannibals[1]);
}

/*
 * Verifica se a restrição do número de missionários em relação ao número de canibais está sendo respeitada
 */
int MissionaryValidate(MissionaryState* state) {
    return between(0, state->missionaries[0], N_MISSIONARIES) && between(0, state->missionaries[1], N_MISSIONARIES) &&
           between(0, state->cannibals[0], N_CANNIBALS) && between(0, state->cannibals[1], N_CANNIBALS) &&
           ((state->missionaries[0] && state->missionaries[1]) ? (state->missionaries[0] >= state->cannibals[0] &&
                                      state->missionaries[1] >= state->cannibals[1]) : 1);
}

/*
 * Verifica se todos os missionários e todos os canibais estão do outro lado do rio.
 */
int MissionaryGoal(MissionaryState* state) {
    return state->missionaries[1] == N_MISSIONARIES && state->cannibals[1] == N_CANNIBALS;
}

#endif //ARTIFICIALINTELLIGENCE_MISSIONARIES_H
