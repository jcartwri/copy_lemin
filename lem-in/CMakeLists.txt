cmake_minimum_required(VERSION 3.13)
project(lem_in C)

set(CMAKE_C_STANDARD 99)

include_directories(lib)

file(GLOB lib/printf
#        "lib/printf/*.c"
        "lib/printf/libft/*.c"
        "checker/*.c"
        )



add_executable(lem_in main.c
        lem-in.h
        lib/printf/libft/libft.h
        lib/printf/libft/get_next_line.h
        ${lib/printf} checker/checker.c checker/create_list.c checker/free_graph.c checker/record_coord_room.c checker/record_links.c checker/work_with_arms.c checker/built_int_graph.c checker/built_int_mas_links.c search_for_ways/bfs.c search_for_ways/queue.c search_for_ways/ft_creat_list_pyth.c search_for_ways/work_horse.c search_for_ways/check_repeat_pyth.c search_for_ways/creat_finish_pyths.c search_for_ways/clean_all_memory.c)
