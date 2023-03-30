#include "s21_gtk_gui/s21_gtk_gui.h"

int main(int argc, char **argv) {
  GtkWidget *main_window, *grid, *calc_btn, *calc_field, *result, *x_field,
      *st_field, *end_field, *step_field;
  gtk_init(&argc, &argv);

  main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  set_mw_markdown(&main_window, &grid, &calc_field, &result, &calc_btn,
                  &x_field, &st_field, &end_field, &step_field);
  struct multi_arg_t data;
  data.calc_field = calc_field;
  data.result = result;
  data.x_field = x_field;
  set_mw_signals(&main_window, &calc_btn, &data);

  gtk_widget_show_all(main_window);
  gtk_main();

  return 0;
}