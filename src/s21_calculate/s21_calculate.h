#include "../s21_structs/s21_structs.h"

#ifndef SMARTCALC_S21_CALCULATE_H
#define SMARTCALC_S21_CALCULATE_H

#include <stdlib.h>

#define SUCCESS 1
#define FAILURE 0

int parse_to_tokens(const char* str, queue** res);

#endif  // SMARTCALC_S21_CALCULATE_H
