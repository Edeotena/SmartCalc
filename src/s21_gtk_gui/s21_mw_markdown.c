#include "s21_gtk_gui.h"
void set_mw_markdown(GtkWidget **window, GtkWidget **grid,
                     GtkWidget **calc_field, GtkWidget **result,
                     GtkWidget **calc_btn, GtkWidget **x_field) {
  *grid = gtk_grid_new();
  gtk_container_add(GTK_CONTAINER(*window), *grid);

  GtkWidget *exp_label = gtk_label_new("expression: ");
  gtk_grid_attach(GTK_GRID(*grid), exp_label, 0, 0, 1, 1);

  *calc_field = gtk_entry_new();
  gtk_grid_attach(GTK_GRID(*grid), *calc_field, 1, 0, 1, 1);

  *result = gtk_label_new("result will be here");
  gtk_grid_attach(GTK_GRID(*grid), *result, 3, 0, 1, 1);

  *calc_btn = gtk_button_new_with_label("=");
  gtk_grid_attach(GTK_GRID(*grid), *calc_btn, 2, 0, 1, 1);

  GtkWidget *x_label = gtk_label_new("x: ");
  gtk_grid_attach(GTK_GRID(*grid), x_label, 0, 1, 1, 1);
  *x_field = gtk_entry_new();
  gtk_grid_attach(GTK_GRID(*grid), *x_field, 1, 1, 1, 1);
}