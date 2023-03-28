#ifndef SMARTCALC_S21_STRUCTS_H
#define SMARTCALC_S21_STRUCTS_H

typedef enum {
  OPENING_BRACKET,
  CLOSING_BRACKET,
  ADDITION,
  SUBTRACTION,
  MULTIPLICATION,
  DIVISION,
  POWER,
  MODULUS,
  UNARY_PLUS,
  UNARY_MINUS,
  COS,
  SIN,
  TAN,
  ACOS,
  ASIN,
  ATAN,
  SQRT,
  LN,
  LOG,
  UNRECOGNIZED,
  X,
  VALUE
} Token;

typedef struct queue {
  struct queue *next;
  Token op;
  double value;
} queue;

int add(queue **head, Token op, double value);
int get(queue **head, Token *op, double *value);
void free_queue(queue **head);

#endif  // SMARTCALC_S21_STRUCTS_H
