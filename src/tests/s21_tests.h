#ifndef SMARTCALC_S21_TESTS_H
#define SMARTCALC_S21_TESTS_H

#include <check.h>

#include "s21_calculate/s21_calculate.h"
#include "s21_smart_calc.h"
#include "s21_structs/s21_structs.h"
#define EPS 1e-07

Suite *parser_suite();
Suite *rpn_calc_suite();
Suite *draw_suite();

#endif  // SMARTCALC_S21_TESTS_H
