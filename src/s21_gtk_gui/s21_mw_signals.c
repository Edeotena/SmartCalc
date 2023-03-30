#include "s21_gtk_gui.h"

void set_mw_signals(GtkWidget **window, GtkWidget **calc_btn,
                    GtkWidget **build_btn, struct widgets_container *data) {
  g_signal_connect(*calc_btn, "clicked", G_CALLBACK(do_calculate), data);
  g_signal_connect(*build_btn, "clicked", G_CALLBACK(do_build), data);

  g_signal_connect(*window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
}