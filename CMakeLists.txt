
cmake_minimum_required(VERSION 3.14)

project(Missionaries C)
project(TravellingSalesman C)
project(TicTacToe C)

add_executable(Missionary missionaries/missionaries.c search/hill_climbing.h missionaries/main.c)
add_executable(TravellingSalesman travelling_salesman/travelling_salesman.c travelling_salesman/travelling_salesman.h travelling_salesman/main.c)
add_executable(TicTacToe tic_tac_toe/tic_tac_toe.c tic_tac_toe/main.c)