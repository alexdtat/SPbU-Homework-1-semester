cmake_minimum_required(VERSION 3.17)
project(spbu_c_homeworks C)

set(CMAKE_C_STANDARD 11)

set(SOURCE_LIB
    library/commonUtils/numericOperations.c
)
add_library(library ${SOURCE_LIB})
add_library(DoublyLinkedList STATIC ../library/DoublyLinkedList/DoublyLinkedList.c)
add_library(LinkedList STATIC ../library/LinkedList/LinkedList.c)
add_library(LinkedMap STATIC ../library/LinkedMap/LinkedMap.c)
add_library(binaryIntegers STATIC ../library/binaryIntegers/binaryIntegers.c)

add_executable(test_1_task_2 test1/task_2.c)
target_link_libraries(test_1_task_2 LinkedList)

add_executable(hw_1_task_1 ../homework1/task_1.c)
target_link_libraries(hw_1_task_1 PRIVATE m)
add_executable(hw_1_task_2 ../homework1/task_2.c)
add_executable(hw_1_task_3 ../homework1/task_3.c)
add_executable(hw_1_task_4 ../homework1/task_4.c)
target_link_libraries(hw_1_task_4 PRIVATE m)
add_executable(hw_1_task_5 ../homework1/task_5.c)

add_executable(hw_2_task_1 ../homework2/task_1.c)
target_link_libraries(hw_2_task_1 LinkedMap)
add_executable(hw_2_task_2 ../homework2/task_2.c)
target_link_libraries(hw_2_task_2 DoublyLinkedList)

add_executable(hw_3_task_1 ../homework3/task_1.c)
target_link_libraries(hw_3_task_1 binaryIntegers)

