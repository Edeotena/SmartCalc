#include "s21_gtk_gui.h"
#include "s21_smart_calc.h"

void do_calculate(GtkWidget *window, struct multi_arg_t *data) {
  if (window == NULL) {
    return;
  }
  char buffer[255] = "Invalid X";

  double x = 0;
  char *end;
  int code = SUCCESS;
  char *xstr = (char *)gtk_entry_get_text(GTK_ENTRY(data->x_field));
  if (*xstr != '\0') {
    x = strtod(xstr, &end);
    if (*end != '\0') {
      code = FAILURE;
    }
  } else {
    code = FAILURE;
  }

  if (code == SUCCESS) {
    queue *parsed;
    code = parse_to_tokens(
        (char *)gtk_entry_get_text(GTK_ENTRY(data->calc_field)), &parsed);
    if (code == FAILURE) {
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
          sprintf(buffer, "%.7lf", res);
        }
        free_queue(&rpn);
      }
      free_queue(&parsed);
    }
  }

  gtk_label_set_text(GTK_LABEL(data->result), buffer);
}