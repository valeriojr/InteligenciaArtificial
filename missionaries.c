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
#include "state_space_search.h"
#include "missionaries.h"


// Node name, State type, Actions ...
DEFINE_STATE_SPACE(Missionary, MissionaryState,
                   TakeOneMissionary,
                   TakeOneCannibal,
                   TakeTwoMissionaries,
                   TakeTwoCannibals,
                   TakeOneMissionaryAndOneCannibal)

void MissionarySearchFinished(int success, Missionary* missionary);


int main() {
    MissionaryState initial = {
            .side = 0,
            .missionaries = {N_MISSIONARIES, 0},
            .cannibals = {N_CANNIBALS, 0}
    };

    MissionaryStateGoal = MissionaryGoal;
    MissionaryStateValidate = MissionaryValidate;
    MissionaryStatePrint = MissionaryPrint;

    MissionaryStateSearch(initial, MissionarySearchFinished); // prints the solution

    return 0;
}

void MissionarySearchFinished(int success, Missionary* missionary) {
    if (success) {
        MissionaryStatePrintSolution(missionary);
    } else {
        puts("Solution not found :c");
    }
}
