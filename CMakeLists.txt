cmake_minimum_required(VERSION 3.14)

project(Missionaries C)
project(TravellingSalesman C)
project(TicTacToe C)

add_executable(Missionary missionaries.c hill_climbing.h)
add_executable(TravellingSalesman travelling_salesman.c travelling_salesman.h)
add_executable(TicTacToe tic_tac_toe.c)