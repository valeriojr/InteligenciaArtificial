//
// Created by ValérioRodrigues on 19/11/2019.
//

#include "missionaries.h"
#include "../search/state_space_search.h"

static float score(MissionaryState* state){
    return 1.0f;
}

static float heuristic(MissionaryState* state){
    return 1.0f;
}


int main() {
    MissionaryState initial = {
            .side = 0,
            .missionaries = {N_MISSIONARIES, 0},
            .cannibals = {N_CANNIBALS, 0}
    };
    
    MissionaryStateGoal = MissionaryGoal;
    MissionaryStateValidate = MissionaryValidate;
    MissionaryStatePrint = MissionaryPrint;
    MissionaryStateHeuristic = heuristic;
    MissionaryStateScore = score;

    MissionaryStateAStar(initial, MissionarySearchFinished); // prints the solution

    return 0;
}