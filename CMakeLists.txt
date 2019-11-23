
cmake_minimum_required(VERSION 3.14)

project(Missionaries C)
project(ParisSubway C)
project(TravellingSalesman C)
project(TicTacToe C)

add_executable(Missionary missionaries/missionaries.c missionaries/main.c common/util.c)
add_executable(ParisSubway paris_subway/main.c paris_subway/paris_subway.c common/util.c)
add_executable(TravellingSalesman travelling_salesman/main.c travelling_salesman/travelling_salesman.c common/util.c)
add_executable(TicTacToe tic_tac_toe/main.c tic_tac_toe/tic_tac_toe.c common/util.c)