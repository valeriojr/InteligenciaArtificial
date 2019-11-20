//
// Created by Valerio on 17/11/2019.
//

/*
 *
 * 1. Problema dos missionários e canibais
 *
 *
 *      Três missionários e três canibais estão em um lado do rio, juntamente com um barco que pode conter uma ou duas
 * pessoas. Descubra um meio de fazer todos atravessarem o rio, sem deixar que um grupo de missionários de um lado fique
 * em número menor que o número de canibais nesse lado do rio.
 *      Implemente e resolva o problema de forma ótima, utilizando um algoritmo de busca apropriado. É boa ideia
 * verificar a existência de estados repetidos?
 *
 */

#include <stdio.h>
#include <ctype.h>
#include "missionaries.h"


DEFINE_STATE_SPACE(Missionary, MissionaryState,
                   TakeOneCannibal,
                   TakeTwoCannibals,
                   TakeOneMissionary,
                   TakeTwoMissionaries,
                   TakeOneMissionaryAndOneCannibal)

void MissionarySearchFinished(int success, Missionary* missionary) {
    if (success) {
        MissionaryStatePrintSolution(missionary);
    } else {
        puts("Solution not found :c");
    }
}

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

int MissionaryValidate(MissionaryState* state) {
    return between(0, state->missionaries[0], N_MISSIONARIES) && between(0, state->missionaries[1], N_MISSIONARIES) &&
           between(0, state->cannibals[0], N_CANNIBALS) && between(0, state->cannibals[1], N_CANNIBALS) &&
           ((state->missionaries[0] && state->missionaries[1]) ? (state->missionaries[0] >= state->cannibals[0] &&
                                                                  state->missionaries[1] >= state->cannibals[1]) : 1);
}

int MissionaryGoal(MissionaryState* state) {
    return state->missionaries[1] == N_MISSIONARIES && state->cannibals[1] == N_CANNIBALS;
}
