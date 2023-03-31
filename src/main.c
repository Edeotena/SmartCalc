#include "s21_gtk_gui/s21_gtk_gui.h"

int main(int argc, char **argv) {
  GtkWidget *main_window, *grid, *calc_btn, *calc_field, *result, *x_field,
      *st_field, *end_field, *yst_field, *yend_field, *build_button;
  gtk_init(&argc, &argv);

  main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  set_mw_markdown(&main_window, &grid, &calc_field, &result, &calc_btn,
                  &x_field, &st_field, &end_field, &yst_field, &yend_field,
                  &build_button);
  struct widgets_container data;
  data.calc_field = calc_field;
  data.result = result;
  data.x_field = x_field;
  data.end_field = end_field;
  data.st_field = st_field;
  data.yend_field = yend_field;
  data.yst_field = yst_field;
  set_mw_signals(&main_window, &calc_btn, &build_button, &data);

  gtk_widget_show_all(main_window);
  gtk_main();

  return 0;
}
