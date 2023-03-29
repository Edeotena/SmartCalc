#include <math.h>

#include "s21_smart_calc.h"
#include "s21_structs/s21_structs.h"

int produce_un(stack **func, double x, Token op) {
  int code = FAILURE;
  if (op == SIN) {
    code = push(func, VALUE, sin(x));
  } else if (op == COS) {
    code = push(func, VALUE, cos(x));
  } else if (op == ASIN) {
    code = push(func, VALUE, asin(x));
  } else if (op == ACOS) {
    code = push(func, VALUE, acos(x));
  } else if (op == TAN) {
    code = push(func, VALUE, tan(x));
  } else if (op == ATAN) {
    code = push(func, VALUE, cos(x) / sin(x));
  } else if (op == SQRT) {
    code = push(func, VALUE, sqrt(x));
  } else if (op == LN) {
    code = push(func, VALUE, log(x));
  } else if (op == LOG) {
    code = push(func, VALUE, log10(x));
  } else if (op == UNARY_MINUS) {
    code = push(func, VALUE, -x);
  } else if (op == UNARY_PLUS) {
    code = push(func, VALUE, x);
  }

  return code;
}

double double_mod(double a, double b) {
  double mod;
  if (a < 0)
    mod = -a;
  else
    mod = a;
  if (b < 0) b = -b;

  while (mod >= b) mod = mod - b;

  if (a < 0) return -mod;

  return mod;
}

int produce_bin(stack **func, double fir, double sec, Token op) {
  int code = FAILURE;
  if (op == SUBTRACTION) {
    code = push(func, VALUE, sec - fir);
  } else if (op == ADDITION) {
    code = push(func, VALUE, sec + fir);
  } else if (op == MULTIPLICATION) {
    code = push(func, VALUE, sec * fir);
  } else if (op == DIVISION) {
    code = push(func, VALUE, sec / fir);
  } else if (op == MODULUS) {
    code = push(func, VALUE, double_mod(sec, fir));
  } else if (op == POWER) {
    double real_pow = pow(sec, fir);
    if (sec < 0 && fir < 0) {
      real_pow = -real_pow;
    }
    code = push(func, VALUE, real_pow);
  }
  return code;
}

double calculate(queue *func, double x, int *code_error) {
  int code = SUCCESS;
  *code_error = SUCCESS;
  double value;
  Token op;
  stack *temp = NULL;
  code = get(&func, &op, &value);
  while (code != STOP_QUEUE && code != FAILURE) {
    if (op == VALUE) {
      code = push(&temp, VALUE, value);
    } else if (op == X) {
      code = push(&temp, VALUE, x);
    } else {
      double fir;
      Token remove;
      if (temp != NULL) {
        code = pop(&temp, &remove, &fir);
        if (code == SUCCESS) {
          code = produce_un(&temp, fir, op);
        }
      } else {
        code = FAILURE;
      }
      if (code == FAILURE && temp != NULL) {
        double sec;
        code = pop(&temp, &remove, &sec);
        if (code == SUCCESS) {
          code = produce_bin(&temp, fir, sec, op);
        }
      }
    }
    if (code != FAILURE) {
      code = get(&func, &op, &value);
    }
  }
  double res = 0;
  if (temp == NULL || code == FAILURE) {
    free_stack(&temp);
    *code_error = FAILURE;
  } else {
    Token remove;
    code = pop(&temp, &remove, &res);
    if (code != SUCCESS) {
      *code_error = FAILURE;
    }
  }

  return res;
}