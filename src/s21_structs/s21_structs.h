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

typedef struct stack {
  struct stack *next;
  Token op;
  double val;
} stack;

int add(queue **head, Token op, double value);
int get(queue **head, Token *op, double *value);
void free_queue(queue **head);

int pop(stack **head, Token *res);
int push(stack **head, Token tk);
void free_stack(stack **head);

#endif  // SMARTCALC_S21_STRUCTS_H
