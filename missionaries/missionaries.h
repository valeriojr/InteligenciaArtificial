//
// Created by Valerio on 16/11/2019.
//

/*
 *
 *  Definição do estado para o problema dos missionários e implementação dos operadores e de utilidades (testar se o
 *  estado é um objetivo, testar se o estado é válido e imprimir o estado na tela).
 *
 */

#ifndef ARTIFICIAL_INTELLIGENCE_MISSIONARIES_H
#define ARTIFICIAL_INTELLIGENCE_MISSIONARIES_H


#include <stdio.h>
#include "../search/state_space_search.h"
#include "../common/util.h"

//----------------------------------------------------------------------------------------------------------------------

// Constantes

#define N_MISSIONARIES 3
#define N_CANNIBALS 3

//----------------------------------------------------------------------------------------------------------------------

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

//----------------------------------------------------------------------------------------------------------------------

MissionaryState TakeOneMissionary(MissionaryState parent);

MissionaryState TakeOneCannibal(MissionaryState parent);

MissionaryState TakeTwoMissionaries(MissionaryState parent);

MissionaryState TakeTwoCannibals(MissionaryState parent);

MissionaryState TakeOneMissionaryAndOneCannibal(MissionaryState parent);

//----------------------------------------------------------------------------------------------------------------------

DECLARE_STATE_SPACE(Missionary, MissionaryState,
                    TakeOneMissionary,
                    TakeOneCannibal,
                    TakeTwoMissionaries,
                    TakeTwoCannibals,
                    TakeOneMissionaryAndOneCannibal);

//----------------------------------------------------------------------------------------------------------------------

/*
 * Verifica se a restrição do número de missionários em relação ao número de canibais está sendo respeitada
 */
int MissionaryValidate(MissionaryState* state);

/*
 * Verifica se todos os missionários e todos os canibais estão do outro lado do rio.
 */
int MissionaryGoal(MissionaryState* state);

/*
 * Imprime o estado na tela
 */
void MissionaryPrint(MissionaryState* state);

/*
 * Imprime a solução
 */
void MissionarySearchFinished(int success, Missionary* missionary);

#endif //ARTIFICIALINTELLIGENCE_MISSIONARIES_H
