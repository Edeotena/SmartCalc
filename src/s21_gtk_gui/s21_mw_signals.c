#include "s21_gtk_gui.h"

void set_mw_signals(GtkWidget **window, GtkWidget **calc_btn,
                    struct multi_arg_t *data) {
  g_signal_connect(*calc_btn, "clicked", G_CALLBACK(do_calculate), data);

  g_signal_connect(*window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
}