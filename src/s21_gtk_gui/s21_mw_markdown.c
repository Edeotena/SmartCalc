#include "s21_gtk_gui.h"
void set_mw_markdown(GtkWidget **window, GtkWidget **grid,
                     GtkWidget **calc_field, GtkWidget **result,
                     GtkWidget **calc_btn, GtkWidget **x_field,
                     GtkWidget **st_field, GtkWidget **end_field,
                     GtkWidget **steps_field) {
  *grid = gtk_grid_new();
  gtk_container_add(GTK_CONTAINER(*window), *grid);

  GtkWidget *exp_label = gtk_label_new("expression: ");
  gtk_grid_attach(GTK_GRID(*grid), exp_label, 0, 0, 1, 2);

  *calc_field = gtk_entry_new();
  gtk_grid_attach(GTK_GRID(*grid), *calc_field, 1, 0, 1, 2);

  *result = gtk_label_new("result will be here\n");
  gtk_grid_attach(GTK_GRID(*grid), *result, 0, 4, 3, 2);

  *calc_btn = gtk_button_new_with_label("=");
  gtk_grid_attach(GTK_GRID(*grid), *calc_btn, 2, 0, 1, 2);

  GtkWidget *x_label = gtk_label_new("x: ");
  gtk_grid_attach(GTK_GRID(*grid), x_label, 0, 2, 1, 2);
  *x_field = gtk_entry_new();
  gtk_grid_attach(GTK_GRID(*grid), *x_field, 1, 2, 1, 2);

  GtkWidget *st_label = gtk_label_new("From: ");
  gtk_grid_attach(GTK_GRID(*grid), st_label, 0, 6, 1, 2);

  *st_field = gtk_entry_new();
  gtk_grid_attach(GTK_GRID(*grid), *st_field, 1, 6, 1, 2);

  GtkWidget *end_label = gtk_label_new("To: ");
  gtk_grid_attach(GTK_GRID(*grid), end_label, 0, 8, 1, 2);
  *end_field = gtk_entry_new();
  gtk_grid_attach(GTK_GRID(*grid), *end_field, 1, 8, 1, 2);

  GtkWidget *steps_label = gtk_label_new("Steps: ");
  gtk_grid_attach(GTK_GRID(*grid), steps_label, 0, 10, 1, 2);
  *steps_field = gtk_entry_new();
  gtk_grid_attach(GTK_GRID(*grid), *steps_field, 1, 10, 1, 2);
}