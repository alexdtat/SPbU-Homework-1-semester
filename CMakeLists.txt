cmake_minimum_required(VERSION 3.17)
project(spbu_c_homeworks C)

set(CMAKE_C_STANDARD 11)

set(SOURCE_LIB
    library/commonUtils/numericOperations.c
)
add_library(library ${SOURCE_LIB})

add_executable(task_1 homework1/task_1.c)
target_link_libraries(task_1 PRIVATE m)
add_executable(task_2 homework1/task_2.c)
add_executable(task_3 homework1/task_3.c)
add_executable(task_4 homework1/task_4.c)
target_link_libraries(task_4 PRIVATE m)
add_executable(task_5 homework1/task_5.c)
add_executable(hw_3_task_1 homework3/task_1.c)
target_link_libraries(hw_3_task_1 PRIVATE m)
