//
// Created by Valerio on 16/11/2019.
//

#ifndef ARTIFICIALINTELLIGENCE_TICTACTOE_H
#define ARTIFICIALINTELLIGENCE_TICTACTOE_H

#include <limits.h>
#include "../common/util.h"

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

TicTacToeState Mark(int row, int col, TicTacToeState state) {
    if (!between(Top, row, Bottom) || !between(Left, col, Right)) {
        state.board[0][0] = INVALID;
    } else {
        if (state.board[row][col] == EMPTY) {
            state.board[row][col] = state.player;
        } else {
            state.board[row][col] = INVALID;
        }
    }
    state.player = !state.player;

    return state;
}

TIC_TAC_TOE_MOVE(Top, Left);

TIC_TAC_TOE_MOVE(Top, Center);

TIC_TAC_TOE_MOVE(Top, Right)

TIC_TAC_TOE_MOVE(Center, Left)

TIC_TAC_TOE_MOVE(Center, Center)

TIC_TAC_TOE_MOVE(Center, Right)

TIC_TAC_TOE_MOVE(Bottom, Left)

TIC_TAC_TOE_MOVE(Bottom, Center)

TIC_TAC_TOE_MOVE(Bottom, Right)

int goalBoard(TicTacToeState* state);

int validateBoard(TicTacToeState* state) {
    int i, j;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (state->board[i][j] == INVALID) {
                return 0;
            }
        }
    }

    return 1;
}


int goalBoard(TicTacToeState* state) {
    int i, j;

    int won = 0;

    for (i = Top; i <= Bottom; i++) {
        won = won ||
              ((state->board[i][Left] == TicTacToeCurrentPlayer) &&
               (state->board[i][Center] == TicTacToeCurrentPlayer) &&
               (state->board[i][Right] == TicTacToeCurrentPlayer))
              ||
              ((state->board[Top][i] == TicTacToeCurrentPlayer) &&
               (state->board[Center][i] == TicTacToeCurrentPlayer) &&
               (state->board[Bottom][i] == TicTacToeCurrentPlayer));
    }

    won = won || ((state->board[Top][Left] == TicTacToeCurrentPlayer) &&
                  (state->board[Center][Center] == TicTacToeCurrentPlayer) &&
                  (state->board[Bottom][Right] == TicTacToeCurrentPlayer))
          ||
          ((state->board[Top][Right] == TicTacToeCurrentPlayer) &&
           (state->board[Center][Center] == TicTacToeCurrentPlayer) &&
           (state->board[Bottom][Left] == TicTacToeCurrentPlayer));


    return won;
}

void print_board(TicTacToeState* state) {
    int i, j;

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            char s[6];
            switch (state->board[i][j]) {
                case X:
                    strcpy(s, "  X  ");
                    break;
                case O:
                    strcpy(s, "  O  ");
                    break;
                case EMPTY:
                    sprintf(s, "  %d  ", 3 * i + j + 1);
                    break;
                case INVALID:
                    strcpy(s, " X-O ");
                    break;
            }
            printf("%s", s);
        }
        printf("\n");
    }
}

int loseBoard(TicTacToeState* state) {
    TicTacToeCurrentPlayer = !TicTacToeCurrentPlayer;
    int r = goalBoard(state);
    TicTacToeCurrentPlayer = !TicTacToeCurrentPlayer;
    return r;
}

int drawBoard(TicTacToeState* state) {
    int i, j;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (state->board[i][j] == EMPTY) {
                return 0;
            }
        }
    }

    return goalBoard(state) || loseBoard(state);
}

int rowScore(TicTacToeState* state, int row, int p) {
    int score = 1;
    int count = 0;
    int i;
    if (state->board[row][Left] != !p && state->board[row][Center] != !p && state->board[row][Right] != !p) {
        for (i = 0; i < 3; i++) count += state->board[row][i] == p;
    } else {
        return 0;
    }
    for (i = 0; i < count - 1; i++) score += 1;

    return score;
}


int colScore(TicTacToeState* state, int col, int p) {
    int score = 1;
    int count = 0;
    int i;
    if (state->board[Top][col] != !p && state->board[Center][col] != !p && state->board[Bottom][col] != !p) {
        for (i = 0; i < 3; i++) count += state->board[i][col] == p;
    } else {
        return 0;
    }
    for (i = 0; i < count - 1; i++) score += 1;

    return score;
}

int diagScore(TicTacToeState* state, int diag, int p) {
    int score = 1;
    int count = 0;
    int i;
    if (state->board[Top][diag * Right + !diag * Left] != !p && state->board[Center][Center] != !p &&
        state->board[Bottom][diag * Left + !diag * Right] != !p) {
        for (i = 0; i < 3; i++) count += state->board[i][abs(i - 2 * diag)] == p;
    } else {
        return 0;
    }
    for (i = 0; i < count - 1; i++) score += 1;

    return score;
}

float ticTacToeScore(TicTacToeState* state) {
    float score = 0;

    if (goalBoard(state)) {
        return INT_MAX;
    } else {
        if (loseBoard(state)) {
            score = INT_MIN;
        } else {
            int i, j;
            int points[3][3] = {
                    {1, 1, 1},
                    {1, 2, 1},
                    {1, 1, 1}
            };
            for (i = 0; i < 3; i++) {
                for (j = 0; j < 3; j++) {
                    score += (points[i][j] * (state->board[i][j] == TicTacToeCurrentPlayer)) -
                             (points[i][j] * (state->board[i][j] == !TicTacToeCurrentPlayer));
                }
            }
        }
    }

    return score;
}

#endif //ARTIFICIALINTELLIGENCE_TICTACTOE_H
