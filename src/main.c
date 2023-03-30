#include <gtk/gtk.h>
#include <stdio.h>

#include "s21_smart_calc.h"

struct multi_arg_t {
  GtkWidget *data1;
  GtkWidget *data2;
};

void do_calculate(GtkWidget *window, struct multi_arg_t *data) {
  if (window == NULL) {
    return;
  }
  queue *parsed;
  char buffer[255] = "n/a";
  int code = parse_to_tokens((char *)gtk_entry_get_text(GTK_ENTRY(data->data1)),
                             &parsed);
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

  gtk_label_set_text(GTK_LABEL(data->data2), buffer);
}

int main(int argc, char **argv) {
  GtkWidget *window, *grid, *calculate, *number1, *result;
  gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

  grid = gtk_grid_new();
  gtk_container_add(GTK_CONTAINER(window), grid);

  number1 = gtk_entry_new();
  gtk_grid_attach(GTK_GRID(grid), number1, 0, 0, 1, 1);

  result = gtk_label_new("  result  ");
  gtk_grid_attach(GTK_GRID(grid), result, 3, 0, 1, 1);

  calculate = gtk_button_new_with_label("=");
  struct multi_arg_t data;
  data.data1 = number1;
  data.data2 = result;
  g_signal_connect(calculate, "clicked", G_CALLBACK(do_calculate), &data);
  gtk_grid_attach(GTK_GRID(grid), calculate, 2, 0, 1, 1);

  gtk_widget_show_all(window);
  gtk_main();

  return 0;
}