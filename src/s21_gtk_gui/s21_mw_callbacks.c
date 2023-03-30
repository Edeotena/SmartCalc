#include <math.h>

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

int get_double_from_entry(GtkWidget *entry, double *res) {
  int valid = SUCCESS;
  char *val_str = (char *)gtk_entry_get_text(GTK_ENTRY(entry));
  if (*val_str != '\0') {
    char *end;
    *res = strtod(val_str, &end);
    if (*end != '\0') {
      valid = FAILURE;
    }
  } else {
    valid = FAILURE;
  }

  return valid;
}

int get_int_from_entry(GtkWidget *entry, long *res) {
  int valid = SUCCESS;
  char *val_str = (char *)gtk_entry_get_text(GTK_ENTRY(entry));
  if (*val_str != '\0') {
    char *end;
    *res = strtol(val_str, &end, 10);
    if (*end != '\0') {
      valid = FAILURE;
    }
  } else {
    valid = FAILURE;
  }

  return valid;
}

void do_calculate(GtkWidget *window, struct widgets_container *data) {
  if (window == NULL) {
    return;
  }
  char buffer[255] = "Strange error";

  double x = 0;
  int valid_x = get_double_from_entry(data->calc_field, &x);

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
        if (isnan(res)) {
          sprintf(buffer, "result: NOT A NUMBER(probably root of negative)");
        } else if (isinf(res)) {
          sprintf(buffer, "result: INFINITY(probably zero-division)");
        } else {
          sprintf(buffer, "result: s%.7lf", res);
        }
      }
      free_queue(&rpn);
    }
    free_queue(&parsed);
  }

  gtk_label_set_text(GTK_LABEL(data->result), buffer);
}

void do_build(GtkWidget *window, struct widgets_container *data) {
  if (window == NULL) {
    return;
  }

  long steps = 0;
  int valid_steps = get_int_from_entry(data->steps_field, &steps);
  double start = 0, end = 0;
  int valid_start = get_double_from_entry(data->st_field, &start);
  int valid_end = get_double_from_entry(data->end_field, &end);

  int code = SUCCESS;

  if (valid_steps == FAILURE || valid_start == FAILURE ||
      valid_end == FAILURE || end <= start || steps < 2) {
    code = FAILURE;
  } else {
    code = SUCCESS;
  }
}