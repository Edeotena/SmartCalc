#include <math.h>
#include <stdlib.h>

#include "s21_smart_calc.h"
#include "s21_structs/s21_structs.h"

int get_priority(Token op) {
  int res = 0;
  if (op == ADDITION || op == SUBTRACTION) {
    res = 1;
  } else if (op == MULTIPLICATION || op == DIVISION || op == MODULUS) {
    res = 2;
  } else if (op == POWER) {
    res = 3;
  } else if (op == SIN || op == COS || op == TAN || op == ACOS || op == ASIN ||
             op == ATAN || op == SQRT || op == LN || op == LOG ||
             op == UNARY_PLUS || op == UNARY_MINUS) {
    res = 4;
  }
  return res;
}

int handle_bin(queue **res, stack **operations, char op, int *operands) {
  int code = SUCCESS;
  while (*operations != NULL &&
         get_priority((*operations)->op) >= get_priority(op) &&
         code == SUCCESS) {
    Token p;
    double temp;
    code = pop(operations, &p, &temp);
    if (code == SUCCESS) {
      if (p == ADDITION || p == SUBTRACTION || p == MULTIPLICATION ||
          p == DIVISION || p == POWER || p == MODULUS) {
        --(*operands);
      }
      code = add(res, p, 0);
    }
  }

  if (code == SUCCESS) {
    code = push(operations, op, 0);
  }

  return code;
}

int handle_bracket(queue **res, stack **operations, int *operands) {
  int code = SUCCESS;
  while (*operations != NULL && (*operations)->op != OPENING_BRACKET &&
         code != STOP_QUEUE) {
    Token p;
    code = pop(operations, &p, 0);
    if (code == SUCCESS) {
      if (p == '+' || p == '-' || p == '*' || p == '/' || p == '^') {
        --(*operands);
      }
      code = add(res, p, 0);
    }
  }
  if (code == SUCCESS) {
    if (*operations == NULL || (*operations)->op != OPENING_BRACKET) {
      code = FAILURE;
    } else {
      Token remove;
      double temp;
      code = pop(operations, &remove, &temp);
    }
  }
  return code;
}

int flush_stack(queue **res, stack **operations, Token op, int *operands) {
  int code = SUCCESS;
  double temp;
  while (*operations != NULL && code == SUCCESS) {
    code = pop(operations, &op, &temp);
    if (code == SUCCESS) {
      if (op != OPENING_BRACKET) {
        if (op == ADDITION || op == SUBTRACTION || op == MULTIPLICATION ||
            op == DIVISION || op == POWER || op == MODULUS) {
          --(*operands);
        }
        code = add(res, op, 0);
      } else {
        code = FAILURE;
      }
    }
  }

  return code;
}

queue *make_rpn(queue *queue_to_rpn) {
  int code = SUCCESS, operands = 0, scope_open = 1;
  double value;
  Token op;
  code = get(&queue_to_rpn, &op, &value);
  queue *res = NULL;
  stack *operations = NULL;
  while (code != FAILURE && code != STOP_QUEUE) {
    if (op == VALUE || op == X) {
      code = add(&res, op, value);
      ++operands;
      scope_open = 0;
    } else if (op == SIN || op == COS || op == TAN || op == ACOS ||
               op == ASIN || op == ATAN || op == SQRT || op == LOG ||
               op == LN || op == OPENING_BRACKET || op == UNARY_PLUS ||
               op == UNARY_MINUS) {
      code = push(&operations, op, 0);
      scope_open = (op == OPENING_BRACKET ? 1 : 0);
    } else if (op == CLOSING_BRACKET) {
      if (scope_open != 1) {
        code = handle_bracket(&res, &operations, &operands);
        scope_open = 0;
      } else {
        code = FAILURE;
      }
    } else if (op == ADDITION || op == SUBTRACTION || op == MULTIPLICATION ||
               op == DIVISION || op == POWER || op == MODULUS) {
      code = handle_bin(&res, &operations, op, &operands);
      scope_open = 0;
    }
    if (code != FAILURE) {
      code = get(&queue_to_rpn, &op, &value);
    }
  }
  if (code == STOP_QUEUE) {
    code = flush_stack(&res, &operations, op, &operands);
  }
  if (code == FAILURE || operands != 1) {
    free_queue(&res);
    free_stack(&operations);
  }

  return res;
}

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
  } else if (op == LOG || op == LN) {
    code = push(func, VALUE, log(x));
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
  int code = 0;
  *code_error = 0;
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
      if (code == 0 && temp != NULL) {
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