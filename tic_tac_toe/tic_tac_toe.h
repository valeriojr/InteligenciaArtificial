//
// Created by Valerio on 16/11/2019.
//

#ifndef ARTIFICIAL_INTELLIGENCE_TIC_TAC_TOE_H
#define ARTIFICIAL_INTELLIGENCE_TIC_TAC_TOE_H

#include <limits.h>
#include "../common/util.h"
#include "../search/minimax.h"

#define DECLARE_TIC_TAC_TOE_MOVE(ROW, COLUMN) TicTacToeState Mark##ROW##COLUMN (TicTacToeState parent);

//----------------------------------------------------------------------------------------------------------------------

// Constantes

#define DEPTH 2
enum {
    INVALID = -2, EMPTY = -1, X, O
};
enum {
    Top = 0, Left = 0, Center = 1, Bottom = 2, Right = 2
};

//----------------------------------------------------------------------------------------------------------------------

typedef struct TicTacToeState {
    int player;
    char board[3][3];
} TicTacToeState;

//----------------------------------------------------------------------------------------------------------------------

extern int TicTacToeCurrentPlayer;
extern TicTacToeState match;
int printNumbers;

//----------------------------------------------------------------------------------------------------------------------

DECLARE_TIC_TAC_TOE_MOVE(Top, Left);

DECLARE_TIC_TAC_TOE_MOVE(Top, Center);

DECLARE_TIC_TAC_TOE_MOVE(Top, Right)

DECLARE_TIC_TAC_TOE_MOVE(Center, Left)

DECLARE_TIC_TAC_TOE_MOVE(Center, Center)

DECLARE_TIC_TAC_TOE_MOVE(Center, Right)

DECLARE_TIC_TAC_TOE_MOVE(Bottom, Left)

DECLARE_TIC_TAC_TOE_MOVE(Bottom, Center)

DECLARE_TIC_TAC_TOE_MOVE(Bottom, Right)

//----------------------------------------------------------------------------------------------------------------------

DECLARE_MINIMAX(TicTacToeState,
        MarkTopLeft,
        MarkTopCenter,
        MarkTopRight,
        MarkCenterLeft,
        MarkCenterCenter,
        MarkCenterRight,
        MarkBottomLeft,
        MarkBottomCenter,
        MarkBottomRight);

//----------------------------------------------------------------------------------------------------------------------

void TicTacToeMakeMove(int actionIndex, int score, TicTacToeState* state);

TicTacToeState Mark(int row, int col, TicTacToeState state);

int validateBoard(TicTacToeState* state);

int goalBoard(TicTacToeState* state);

void printBoard(TicTacToeState* state);

int loseBoard(TicTacToeState* state);

int drawBoard(TicTacToeState* state);

float ticTacToeScore(TicTacToeState* state);

#endif //ARTIFICIAL_INTELLIGENCE_TIC_TAC_TOE_H
