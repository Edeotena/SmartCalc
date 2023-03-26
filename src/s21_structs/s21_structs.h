//
// Created by edeotena on 27.03.23.
//

#ifndef SMARTCALC_S21_STRUCTS_H
#define SMARTCALC_S21_STRUCTS_H

typedef struct queue {
  struct queue *next;
  Token op;
  double value;
} queue;

int add(queue **head, Token op, double value);
int get(queue **head, Token *op, double *value);
void free_queue(queue **head);

#endif  // SMARTCALC_S21_STRUCTS_H
