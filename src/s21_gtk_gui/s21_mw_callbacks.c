#include "s21_gtk_gui.h"
#include "s21_smart_calc.h"

void do_calculate(GtkWidget *window, struct multi_arg_t *data) {
  if (window == NULL) {
    return;
  }
  queue *parsed;
  char buffer[255] = "n/a";
  int code = parse_to_tokens(
      (char *)gtk_entry_get_text(GTK_ENTRY(data->calc_field)), &parsed);
  if (code == FAILURE) {
    sprintf(buffer, "n/a");
  } else {
    queue *rpn = make_rpn(parsed, &code);
    if (code == FAILURE) {
      sprintf(buffer, "n/a");
    } else {
      double res = calc_rpn(rpn, 0, &code);
      if (code == FAILURE) {
        sprintf(buffer, "n/a");
      } else {
        sprintf(buffer, "%.7lf", res);
      }
      free_queue(&rpn);
    }
    free_queue(&parsed);
  }

  gtk_label_set_text(GTK_LABEL(data->result), buffer);
}