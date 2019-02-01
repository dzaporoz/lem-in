cmake_minimum_required(VERSION 3.13)
project(Lem_in C)

set(CMAKE_C_STANDARD 99)

AUX_SOURCE_DIRECTORY(libft LIBA)

AUX_SOURCE_DIRECTORY(ftprintf PRINTF)


add_executable(lem-in main.c ${LIBA} ${PRINTF} data_reading.c data_validation.c dfs_traversal.c auxilliary.c bfs_traversal.c print_moves.c routes_optimization.c prepare_graph.c print_routes.c)

