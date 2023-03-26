//
// Created by edeotena on 27.03.23.
//

#ifndef SMARTCALC_S21_STRUCTS_H
#define SMARTCALC_S21_STRUCTS_H

typedef struct queue {
  struct queue *next;
  char op;
  double value;
} queue;

void add(queue **head, char op, double value, int *code);
void get(queue **head, char *op, double *value, int *code);
void free_queue(queue **head);

#endif  // SMARTCALC_S21_STRUCTS_H
