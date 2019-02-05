cmake_minimum_required(VERSION 3.13)
project(Lem_in C)

set(CMAKE_C_STANDARD 99)

AUX_SOURCE_DIRECTORY(libft LIBA)

AUX_SOURCE_DIRECTORY(ftprintf PRINTF)

add_executable(lem-in src/main.c ${LIBA} ${PRINTF} src/data_reading.c src/data_validation.c src/dfs_traversal.c src/auxilliary.c src/bfs_traversal.c src/print_moves.c src/routes_optimization.c src/print_routes.c src/routes_intersections.c)

