//
// Created by ValérioRodrigues on 19/11/2019.
//
#include <stdio.h>
#include "../search/minimax.h"
#include "tic_tac_toe.h"


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

int main() {
    TicTacToeStateGoal = goalBoard;
    TicTacToeStateValidate = validateBoard;
    TicTacToeStatePrint = print_board;
    TicTacToeStateScore = ticTacToeScore;

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

            print_board(&match);
            match = next;
            TicTacToeCurrentPlayer = match.player;
        } else {
            TicTacToeStateMinimax(&match, DEPTH, TicTacToeMakeMove);
        }
    }

    print_board(&match);

    if (TicTacToeCurrentPlayer == X) {
        puts("Bolas! Voce perdeu!");
    } else {
        puts("You're pretty good!");
    }

    return 0;
}