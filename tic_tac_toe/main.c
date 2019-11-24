//
// Created by ValérioRodrigues on 19/11/2019.
//
#include <stdio.h>
#include "tic_tac_toe.h"

typedef void(*TicTacToePlayer)(int);

void humanMove(int difficulty){
    printNumbers = 1;
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
}
void cpuMove(int difficulty){
    printNumbers = 0;
    TicTacToeStateMinimax(&match, difficulty, TicTacToeMakeMove);
}


TicTacToePlayer selectPlayer(int p){
    int player = 0;
    while(!between(1, player, 2)){
        printf("Select player %d:\n1 - Human\n2 - CPU\n", p + 1);
        scanf("%d", &player);
    }

    if(player == 1){
        return humanMove;
    }
    else {
        return cpuMove;
    }
}

int selectDifficulty(int player){
    int difficulty = 0;
    while(!between(1, difficulty, 9)){
        printf("Select player %d's difficulty level (1 ~ 9):\n", player + 1);
        scanf("%d", &difficulty);
    }

    return difficulty;
}

int main() {
    TicTacToeStateGoal = goalBoard;
    TicTacToeStateValidate = validateBoard;
    TicTacToeStatePrint = printBoard;
    TicTacToeStateScore = ticTacToeScore;

    TicTacToePlayer players[2];
    int difficulties[2] = {0, 0};

    int i;
    for(i = 0;i < 2;i++){
        players[i] = selectPlayer(i);
        if(players[i] == cpuMove){
            difficulties[i] = selectDifficulty(i);
        }
    }

    printBoard(&match);

    while (!goalBoard(&match) && !loseBoard(&match) && !drawBoard(&match)) {
        players[TicTacToeCurrentPlayer](difficulties[TicTacToeCurrentPlayer]);

        printBoard(&match);
    }

    if(drawBoard(&match)){
        printf("Draw!");
    }
    else {
        printf("Player %d won!\n", !TicTacToeCurrentPlayer + 1);
    }

    return 0;
}