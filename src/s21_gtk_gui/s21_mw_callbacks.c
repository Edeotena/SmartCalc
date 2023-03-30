#include "s21_gtk_gui.h"
#include "s21_smart_calc.h"

int check_for_x(queue *tokens) {
  int res = FAILURE;

  while (res == FAILURE && tokens != NULL) {
    if (tokens->op == X) {
      res = SUCCESS;
    }
    tokens = tokens->next;
  }

  return res;
}

void do_calculate(GtkWidget *window, struct multi_arg_t *data) {
  if (window == NULL) {
    return;
  }
  char buffer[255] = "Strange error";

  double x = 0;
  char *end;
  int valid_x = SUCCESS;
  char *x_str = (char *)gtk_entry_get_text(GTK_ENTRY(data->x_field));
  if (*x_str != '\0') {
    x = strtod(x_str, &end);
    if (*end != '\0') {
      valid_x = FAILURE;
    }
  } else {
    valid_x = FAILURE;
  }

  queue *parsed;
  int code = parse_to_tokens(
      (char *)gtk_entry_get_text(GTK_ENTRY(data->calc_field)), &parsed);
  if (check_for_x(parsed) == SUCCESS && valid_x == FAILURE && code == SUCCESS) {
    sprintf(buffer, "Invalid X");
    code = FAILURE;
  } else if (code == FAILURE) {
    sprintf(buffer, "Parser error");
  } else {
    queue *rpn = make_rpn(parsed, &code);
    if (code == FAILURE) {
      sprintf(buffer, "RPN making error");
    } else {
      double res = calc_rpn(rpn, x, &code);
      if (code == FAILURE) {
        sprintf(buffer, "RPN calculation error");
      } else {
        sprintf(buffer, "result:\n%.7lf", res);
      }
      free_queue(&rpn);
    }
    free_queue(&parsed);
  }

  gtk_label_set_text(GTK_LABEL(data->result), buffer);
}