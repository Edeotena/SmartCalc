#include <stdio.h>

#include "s21_calculate/s21_calculate.h"
#include "s21_smart_calc.h"
#include "s21_structs/s21_structs.h"

int main() {
  queue *res;
  char *str = "5 + 6";
  int code = parse_to_tokens(str, &res);

  queue *rpn;
  rpn = make_rpn(res);
  double dres = calculate(rpn, 0, &code);

  free_queue(&res);
}