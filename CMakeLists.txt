cmake_minimum_required(VERSION 3.24)
project(SmartCalc C)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

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
        src/s21_calculate/s21_make_rpn.c
        src/s21_calculate/s21_calc_rpn.c src/s21_calculate/s21_draw.c src/s21_gtk_gui/s21_mw_markdown.c src/s21_gtk_gui/s21_gtk_gui.h src/s21_gtk_gui/s21_mw_signals.c src/s21_gtk_gui/s21_mw_callbacks.c)

add_executable(Test
        src/s21_calculate/s21_calculate.h
        src/s21_calculate/s21_parser.c
        src/s21_structs/s21_queue.c
        src/s21_structs/s21_structs.h
        src/tests/s21_tests.h
        src/tests/test_s21_parses.c
        src/tests/test_main.c
        src/tests/test_s21_rpn_calc.c
        src/s21_structs/s21_stack.c
        src/s21_calculate/s21_make_rpn.c
        src/s21_calculate/s21_calc_rpn.c src/s21_calculate/s21_draw.c)

target_link_libraries(SmartCalc ${GTK3_LIBRARIES} check subunit m)
add_definitions(${GTK3_CFLAGS_OTHER})
include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})

target_link_libraries(Test m check subunit)