#include "s21_gtk_gui.h"
void set_mw_markdown(GtkWidget **window, GtkWidget **grid,
                     GtkWidget **calc_field, GtkWidget **result,
                     GtkWidget **calc_btn) {
  *grid = gtk_grid_new();
  gtk_container_add(GTK_CONTAINER(*window), *grid);

  *calc_field = gtk_entry_new();
  gtk_grid_attach(GTK_GRID(*grid), *calc_field, 0, 0, 1, 1);

  *result = gtk_label_new("  result  ");
  gtk_grid_attach(GTK_GRID(*grid), *result, 3, 0, 1, 1);

  *calc_btn = gtk_button_new_with_label("=");
  gtk_grid_attach(GTK_GRID(*grid), *calc_btn, 2, 0, 1, 1);
}