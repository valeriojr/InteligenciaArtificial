#include <stdio.h>
#include <ctype.h>
#include "../data_structures/linked_list.h"
#include "../search/state_space_search.h"
#include "tic_tac_toe.h"
#include "../search/minimax.h"

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

#define DEPTH 10

void TicTacToeMakeMove(int actionIndex, int score, TicTacToeState* state);


TicTacToeState match = {
        .player = X,
        .board = {EMPTY, EMPTY, EMPTY,
                  EMPTY, EMPTY, EMPTY,
                  EMPTY, EMPTY, EMPTY}
};

int main() {
    TicTacToeStateGoal = goalBoard;
    TicTacToeStateValidate = validateBoard;
    TicTacToeStatePrint = print_board;
    TicTacToeStateScore = ticTacToeScore;

    system("cls");
    print_board(&match);
    while (!goalBoard(&match) && !loseBoard(&match) && !drawBoard(&match)) {
        if (match.player == X) {
            int position;
            printf("Select an empty position:");
            scanf("%d", &position);
            position--;
            TicTacToeState next = Mark(position / 3, position % 3, match);

            while (!validateBoard(&next)) {
                puts("Invalid move! Try again");
                printf("Select an empty position:");
                scanf("%d", &position);
                position--;
                next = Mark(position / 3, position % 3, match);
            }

            system("cls");
            print_board(&match);
            match = next;
            TicTacToeCurrentPlayer = match.player;
        } else {
            TicTacToeStateMinimax(&match, DEPTH, TicTacToeMakeMove);
        }
    }

    system("cls");
    print_board(&match);

    if (TicTacToeCurrentPlayer == X) {
        puts("Bolas! Voce perdeu!");
    } else {
        puts("You're pretty good!");
    }

    return 0;
}

void TicTacToeMakeMove(int actionIndex, int score, TicTacToeState* state) {
    match = TicTacToeStateActions[actionIndex](match);
    TicTacToeCurrentPlayer = match.player;

    print_board(&match);
}
