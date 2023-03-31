#ifndef SMARTCALC_S21_GTK_GUI_H
#define SMARTCALC_S21_GTK_GUI_H

#include <gtk/gtk.h>

struct widgets_container {
  GtkWidget *calc_field;
  GtkWidget *result;
  GtkWidget *x_field;
  GtkWidget *st_field;
  GtkWidget *end_field;
  GtkWidget *yst_field;
  GtkWidget *yend_field;
  GtkWidget *steps_field;
};

void set_mw_markdown(GtkWidget **window, GtkWidget **grid,
                     GtkWidget **calc_field, GtkWidget **result,
                     GtkWidget **calc_btn, GtkWidget **x_field,
                     GtkWidget **st_field, GtkWidget **end_field,
                     GtkWidget **yst_field, GtkWidget **yend_field,
                     GtkWidget **build_button);
void set_mw_signals(GtkWidget **window, GtkWidget **calc_btn,
                    GtkWidget **build_btn, struct widgets_container *data);
void do_calculate(GtkWidget *window, struct widgets_container *data);
void do_build(GtkWidget *window, struct widgets_container *data);

#endif  // SMARTCALC_S21_GTK_GUI_H
