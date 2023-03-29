cmake_minimum_required(VERSION 3.24)
project(SmartCalc C)

set(CMAKE_C_STANDARD 11)

include_directories(
        src)

add_executable(SmartCalc
        src/s21_calculate/s21_calculate.h
        src/s21_calculate/s21_parser.c
        src/s21_structs/s21_queue.c
        src/s21_structs/s21_structs.h
        src/main.c
        src/s21_structs/s21_stack.c
        src/s21_calculate/s21_rpolish_notation.c
        src/s21_calculate/s21_rpn_calc.c src/s21_calculate/s21_draw.c)

target_link_libraries(SmartCalc m)