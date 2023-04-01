#ifndef SMARTCALC_S21_CALCULATE_H
#define SMARTCALC_S21_CALCULATE_H

#include "s21_structs/s21_structs.h"

int parse_to_tokens(const char *str_to_parse, queue **res);
queue *make_rpn(queue *queue_to_rpn, int *code);
double calc_rpn(queue *func, double x, int *code_error);

#endif  // SMARTCALC_S21_CALCULATE_H
