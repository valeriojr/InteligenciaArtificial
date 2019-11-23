//
// Created by Valerio on 22/11/2019.
//

#ifndef TICTACTOE_SUBWAY_MAP_H
#define TICTACTOE_SUBWAY_MAP_H

enum Colors {
    Invalid = -1,
    Blue,
    Green,
    Red,
    Yellow
};

typedef struct SubwayLine {
    int distance;
    int color;
} SubwayLine;

extern SubwayLine subwayLines[14][14];

#endif //TICTACTOE_SUBWAY_MAP_H
