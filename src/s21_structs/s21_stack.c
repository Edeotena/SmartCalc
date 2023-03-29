#include "s21_smart_calc.h"
#include "s21_structs/s21_structs.h"

int pop(stack **head, Token *res, double *val) {
  int code = SUCCESS;
  if (*head != NULL) {
    *res = (*head)->op;
    *val = (*head)->val;
    stack *temp = *head;
    *head = (*head)->next;
    free(temp);
  } else {
    code = FAILURE;
  }

  return code;
}

int push(stack **head, Token tk, double value) {
  int code = SUCCESS;
  if (*head == NULL) {
    *head = (stack *)calloc(1, sizeof(stack));
    if (*head != NULL) {
      (*head)->op = tk;
      (*head)->val = value;
      (*head)->next = NULL;
    } else {
      code = FAILURE;
    }
  } else {
    stack *next = (stack *)calloc(1, sizeof(stack));
    if (next != NULL) {
      next->next = (*head);
      next->op = tk;
      next->val = value;
      (*head) = next;
    } else {
      code = FAILURE;
    }
  }
  return code;
}

void free_stack(stack **head) {
  while (*head != NULL) {
    stack *next = (*head)->next;
    free(*head);
    *head = next;
  }
}