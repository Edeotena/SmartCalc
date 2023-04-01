#include <stdlib.h>

#include "s21_calculate/s21_calculate.h"
#include "s21_smart_calc.h"
#include "s21_structs/s21_structs.h"

double *get_values(queue *func, double left, double right, int steps) {
  double step = (right - left) / (steps - 1);
  double x = left;
  double *res = (double *)calloc(steps, sizeof(double));
  int code = SUCCESS;
  if (res == NULL) {
    code = FAILURE;
  }

  for (int i = 0; i < steps && code == SUCCESS; ++i) {
    double temp = calc_rpn(func, x, &code);
    if (code == SUCCESS) {
      res[i] = temp;
      x += step;
    }
  }

  if (code != SUCCESS) {
    free(res);
    res = NULL;
  }

  return res;
}
