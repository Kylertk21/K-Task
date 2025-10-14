cmake_minimum_required(VERSION 4.0.2)
project(K_Task)

set(CMAKE_CXX_STANDARD 20)

add_executable(K_Task
        main.cpp
        linked_list.h
        data.h
        )

add_executable(K_Task_Tests
        tests.cpp
        catch_amalgamated.hpp
        data.h
        linked_list.h
    )