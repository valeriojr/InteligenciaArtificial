//
// Created by ValérioRodrigues on 19/11/2019.
//

#include "missionaries.h"
#include "../search/state_space_search.h"


// Node name, State type, Actions ...
DEFINE_STATE_SPACE(MissionaryState,
        TakeOneMissionary,
        TakeOneCannibal,
        TakeTwoMissionaries,
        TakeTwoCannibals,
        TakeOneMissionaryAndOneCannibal)


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