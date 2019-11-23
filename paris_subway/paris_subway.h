//
// Created by Valerio on 23/11/2019.
//

#ifndef TICTACTOE_PARIS_SUBWAY_H
#define TICTACTOE_PARIS_SUBWAY_H

#include "../common/state.h"
#include "../search/state_space_search.h"
#include "subway_map.h"

#define DECLARE_STATION_ACTION(STATION)\
Station GoToStation##STATION(Station state);

int goalStation;

//----------------------------------------------------------------------------------------------------------------------
typedef struct Station {
    int number;
    int previous;
    int previousColor;
    int color;
} Station;

//----------------------------------------------------------------------------------------------------------------------

DECLARE_STATION_ACTION(1);
DECLARE_STATION_ACTION(2);
DECLARE_STATION_ACTION(3);
DECLARE_STATION_ACTION(4);
DECLARE_STATION_ACTION(5);
DECLARE_STATION_ACTION(6);
DECLARE_STATION_ACTION(7);
DECLARE_STATION_ACTION(8);
DECLARE_STATION_ACTION(9);
DECLARE_STATION_ACTION(10);
DECLARE_STATION_ACTION(11);
DECLARE_STATION_ACTION(12);
DECLARE_STATION_ACTION(13);
DECLARE_STATION_ACTION(14);

//----------------------------------------------------------------------------------------------------------------------

DECLARE_STATE_SPACE(Subway, Station,
        GoToStation1,
        GoToStation2,
        GoToStation3,
        GoToStation4,
        GoToStation5,
        GoToStation6,
        GoToStation7,
        GoToStation8,
        GoToStation9,
        GoToStation10,
        GoToStation11,
        GoToStation12,
        GoToStation13,
        GoToStation14)

//----------------------------------------------------------------------------------------------------------------------

/*
 * Verifica se a restrição do número de missionários em relação ao número de canibais está sendo respeitada
 */
int SubwayValidate(Station* state);

/*
 * Verifica se todos os missionários e todos os canibais estão do outro lado do rio.
 */
int SubwayGoal(Station* state);

/*
 * Imprime o estado na tela
 */
void SubwayPrint(Station* state);

/*
 * Imprime a solução
 */
void SubwaySearchFinished(int success, Subway* solution);

/*
 * Custo entre a estação anterior e a atual
 */
float SubwayTimeCost(Station* station);

float SubwayHeuristic(Station* station);

float timeBetween(Station* stationA, int stationB);

#endif //ARTIFICIAL_INTELLIGENCE_PARIS_SUBWAY_H
