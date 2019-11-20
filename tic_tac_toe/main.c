//
// Created by ValérioRodrigues on 19/11/2019.
//
#include <stdio.h>
#include "tic_tac_toe.h"


int main() {
    TicTacToeStateGoal = goalBoard;
    TicTacToeStateValidate = validateBoard;
    TicTacToeStatePrint = printBoard;
    TicTacToeStateScore = ticTacToeScore;

    printBoard(&match);

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

            match = next;
            TicTacToeCurrentPlayer = match.player;
            printBoard(&match);
        } else {
            TicTacToeStateMinimax(&match, DEPTH, TicTacToeMakeMove);
        }
    }

    if (TicTacToeCurrentPlayer == X) {
        puts("Bolas! Voce perdeu!");
    } else {
        puts("You're pretty good!");
    }

    return 0;
}