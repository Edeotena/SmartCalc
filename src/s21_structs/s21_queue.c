#include "s21_structs.h"

void add(queue **head, char op, double value, int *code) {
  if (*head == NULL) {
    *head = (queue *)calloc(1, sizeof(queue));
    if (*head == NULL) {
      *code = ERROR;
    } else {
      (*head)->op = op;
      (*head)->value = value;
      (*head)->next = NULL;
    }
  } else {
    queue *temp = *head;
    while (temp->next != NULL) {
      temp = temp->next;
    }
    temp->next = calloc(1, sizeof(queue));
    if (temp->next == NULL) {
      *code = ERROR;
    } else {
      temp->next->op = op;
      temp->next->value = value;
      temp->next->next = NULL;
    }
  }
}

void get(queue **head, char *op, double *value, int *code) {
  if (*head != NULL) {
    *op = (*head)->op;
    *value = (*head)->value;
    (*head) = (*head)->next;
  } else {
    *code = STOP_QUEUE;
  }
}

void free_queue(queue **head) {
  while (*head != NULL) {
    queue *next = (*head)->next;
    free(*head);
    *head = next;
  }
}