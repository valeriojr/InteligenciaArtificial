#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "../data_structures/linked_list.h"
#include "../search/state_space_search.h"
#include "tic_tac_toe.h"
#include "../search/minimax.h"

#define DEFINE_TIC_TAC_TOE_MOVE(ROW, COLUMN)\
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

int TicTacToeCurrentPlayer = X;
TicTacToeState match = {
        .player = X,
        .board = {EMPTY, EMPTY, EMPTY,
                  EMPTY, EMPTY, EMPTY,
                  EMPTY, EMPTY, EMPTY}
};

DEFINE_MINIMAX(TicTacToeState,
               MarkTopLeft,
               MarkTopCenter,
               MarkTopRight,
               MarkCenterLeft,
               MarkCenterCenter,
               MarkCenterRight,
               MarkBottomLeft,
               MarkBottomCenter,
               MarkBottomRight)

void TicTacToeMakeMove(int actionIndex, int score, TicTacToeState* state) {
    match = TicTacToeStateActions[actionIndex](match);
    TicTacToeCurrentPlayer = match.player;

    char action[256];
    TicTacToeStateGetActionName(action, actionIndex);
    printf("Player %d:", (!TicTacToeCurrentPlayer) + 1);
    prettyPrint(action);
    printf("\n");
}

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

void printBoard(TicTacToeState* state) {
    int i, j;

    printf("\n");
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            char s = ' ';
            switch (state->board[i][j]) {
                case X:
                    s = 'X';
                    break;
                case O:
                    s = 'O';
                    break;
                case EMPTY:
                    if(printNumbers){
                        s = '0' + 3 * i + j + 1;
                    }
                    else {
                        s = ' ';
                    }
                    break;
            }
            if (i <= 1) {
                printf("_%c_", s);
            } else {
                printf(" %c ", s);
            }
            if (j <= 1) {
                printf("|");
            }
        }
        printf("\n");
    }
    printf("\n");
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

    return !goalBoard(state) || !loseBoard(state);
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
        return INFINITY;
    }

    if (loseBoard(state)) {
        return -INFINITY;
    }

    int i, j;
    int points[3][3] = {
            {1, 1, 1},
            {1, 2, 1},
            {1, 1, 1}
    };
    /*
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (state->board[i][j] == TicTacToeCurrentPlayer) {
                score += points[i][j];
            } else if (state->board[i][j] == !TicTacToeCurrentPlayer) {
                score -= points[i][j];
            }
        }
    }
    */
    for(i = 0;i < 3;i++){
        score += rowScore(state, i, TicTacToeCurrentPlayer);
        score += colScore(state, i, TicTacToeCurrentPlayer);

        score -= rowScore(state, i, !TicTacToeCurrentPlayer);
        score -= colScore(state, i, !TicTacToeCurrentPlayer);
    }

    score += diagScore(state, 0, TicTacToeCurrentPlayer);
    score += diagScore(state, 1, TicTacToeCurrentPlayer);

    score -= diagScore(state, 0, !TicTacToeCurrentPlayer);
    score -= diagScore(state, 1, !TicTacToeCurrentPlayer);

    return score;
}

int loseBoard(TicTacToeState* state) {
    TicTacToeCurrentPlayer = !TicTacToeCurrentPlayer;
    int r = goalBoard(state);
    TicTacToeCurrentPlayer = !TicTacToeCurrentPlayer;
    return r;
}

DEFINE_TIC_TAC_TOE_MOVE(Top, Left);

DEFINE_TIC_TAC_TOE_MOVE(Top, Center);

DEFINE_TIC_TAC_TOE_MOVE(Top, Right);

DEFINE_TIC_TAC_TOE_MOVE(Center, Left);

DEFINE_TIC_TAC_TOE_MOVE(Center, Center);

DEFINE_TIC_TAC_TOE_MOVE(Center, Right);

DEFINE_TIC_TAC_TOE_MOVE(Bottom, Left);

DEFINE_TIC_TAC_TOE_MOVE(Bottom, Center);

DEFINE_TIC_TAC_TOE_MOVE(Bottom, Right);