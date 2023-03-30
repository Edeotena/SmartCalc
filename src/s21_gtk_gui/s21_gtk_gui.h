#ifndef SMARTCALC_S21_GTK_GUI_H
#define SMARTCALC_S21_GTK_GUI_H

#include <gtk/gtk.h>

struct multi_arg_t {
  GtkWidget *calc_field;
  GtkWidget *result;
  GtkWidget *x_field;
};

void set_mw_markdown(GtkWidget **window, GtkWidget **grid,
                     GtkWidget **calc_field, GtkWidget **result,
                     GtkWidget **calc_btn, GtkWidget **x_field);
void set_mw_signals(GtkWidget **window, GtkWidget **calc_btn,
                    struct multi_arg_t *data);
void do_calculate(GtkWidget *window, struct multi_arg_t *data);

#endif  // SMARTCALC_S21_GTK_GUI_H
