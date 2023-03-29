#include "s21_smart_calc.h"
#include "s21_structs/s21_structs.h"

int add(queue **head, Token op, double value) {
  int res = SUCCESS;
  if (*head == NULL) {
    *head = (queue *)calloc(1, sizeof(queue));
    if (*head == NULL) {
      res = FAILURE;
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
      res = FAILURE;
    } else {
      temp->next->op = op;
      temp->next->value = value;
      temp->next->next = NULL;
    }
  }

  return res;
}

int get(queue **head, Token *op, double *value) {
  int res = SUCCESS;
  if (*head != NULL) {
    *op = (*head)->op;
    *value = (*head)->value;
    (*head) = (*head)->next;
  } else {
    res = STOP_QUEUE;
  }

  return res;
}

void free_queue(queue **head) {
  while (*head != NULL) {
    queue *next = (*head)->next;
    free(*head);
    *head = next;
  }
}