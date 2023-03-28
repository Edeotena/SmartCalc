#include "s21_smart_calc.h"
#include "s21_structs/s21_structs.h"

int pop(stack **head, Token *res) {
  int code = SUCCESS;
  if (head != NULL) {
    *res = (*head)->op;
    stack *temp = *head;
    *head = (*head)->next;
    if (*head == NULL) {
      code = FAILURE;
    }
    free(temp);
  } else {
    code = FAILURE;
  }

  return code;
}

int push(stack **head, Token tk) {
  int code = SUCCESS;
  if (*head == NULL) {
    *head = (stack *)calloc(1, sizeof(stack));
    if (*head != NULL) {
      (*head)->op = tk;
      (*head)->next = NULL;
    } else {
      code = FAILURE;
    }
  } else {
    stack *next = (stack *)calloc(1, sizeof(stack));
    if (next != NULL) {
      next->next = (*head);
      next->op = tk;
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