//
// Created by Valerio on 16/11/2019.
//

#ifndef ARTIFICIAL_INTELLIGENCE_TIC_TAC_TOE_H
#define ARTIFICIAL_INTELLIGENCE_TIC_TAC_TOE_H

#include <limits.h>
#include "../common/util.h"

#define DEPTH 10


enum {
    INVALID = -2, EMPTY = -1, X, O
};

enum {
    Top = 0, Left = 0, Center = 1, Bottom = 2, Right = 2
};

typedef struct TicTacToeState {
    int player;
    char board[3][3];
} TicTacToeState;

int TicTacToeCurrentPlayer = X;
TicTacToeState match = {
        .player = X,
        .board = {EMPTY, EMPTY, EMPTY,
                  EMPTY, EMPTY, EMPTY,
                  EMPTY, EMPTY, EMPTY}
};


#define TIC_TAC_TOE_MOVE(ROW, COLUMN)\
TicTacToeState Mark##ROW##COLUMN (TicTacToeState parent){\
    if(parent.board[ROW][COLUMN] == EMPTY){\
        parent.board[ROW][COLUMN] = parent.player;\
    }\
    else {\
        parent.board[ROW][COLUMN] = INVALID;\
    }\
    \
    parent.player = !parent.player;\
    \
    return parent;\
}\

TIC_TAC_TOE_MOVE(Top, Left);

TIC_TAC_TOE_MOVE(Top, Center);

TIC_TAC_TOE_MOVE(Top, Right)

TIC_TAC_TOE_MOVE(Center, Left)

TIC_TAC_TOE_MOVE(Center, Center)

TIC_TAC_TOE_MOVE(Center, Right)

TIC_TAC_TOE_MOVE(Bottom, Left)

TIC_TAC_TOE_MOVE(Bottom, Center)

TIC_TAC_TOE_MOVE(Bottom, Right)

void TicTacToeMakeMove(int actionIndex, int score, TicTacToeState *state);

TicTacToeState Mark(int row, int col, TicTacToeState state);

int validateBoard(TicTacToeState *state);

int goalBoard(TicTacToeState *state);

void print_board(TicTacToeState *state);

int loseBoard(TicTacToeState *state);

int drawBoard(TicTacToeState *state);

int rowScore(TicTacToeState *state, int row, int p);


int colScore(TicTacToeState *state, int col, int p);

int diagScore(TicTacToeState *state, int diag, int p);

float ticTacToeScore(TicTacToeState *state);

#endif //ARTIFICIAL_INTELLIGENCE_TIC_TAC_TOE_H
