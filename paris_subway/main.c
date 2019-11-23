//
// Created by Valerio on 23/11/2019.
//

#include <stdio.h>
#include <stdlib.h>
#include "paris_subway.h"
#include "../search/state_space_search.h"

int main(){
    int initialStation = -1;
    while(!between(1, initialStation, 14)){
        puts("Select the initial station:");
        scanf("%d", &initialStation);
    }
    while(!between(1, goalStation, 14)){
        puts("Select the final station:");
        scanf("%d", &goalStation);
    }

    goalStation -= 1;

    Station initial = {
            .number = initialStation - 1,
            .color = Invalid,
            .previous = -1,
            .previousColor = Invalid
    };

    StationPrint = SubwayPrint;
    StationValidate = SubwayValidate;
    StationGoal = SubwayGoal;
    StationScore = SubwayTimeCost;
    StationHeuristic = SubwayHeuristic;

    StationAStar(initial, SubwaySearchFinished);

    return 0;
}