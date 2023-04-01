#include <math.h>

#include "s21_gtk_gui.h"
#include "s21_smart_calc.h"

int check_for_x(queue *tokens) {
  int res = FAILURE;

  while (res == FAILURE && tokens != NULL) {
    if (tokens->op == X) {
      res = SUCCESS;
    }
    tokens = tokens->next;
  }

  return res;
}

int get_double_from_entry(GtkWidget *entry, double *res) {
  int valid = SUCCESS;
  char *val_str = (char *)gtk_entry_get_text(GTK_ENTRY(entry));
  if (*val_str != '\0') {
    char *end;
    *res = strtod(val_str, &end);
    if (*end != '\0') {
      valid = FAILURE;
    }
  } else {
    valid = FAILURE;
  }

  return valid;
}

int get_int_from_entry(GtkWidget *entry, int *res) {
  int valid = SUCCESS;
  char *val_str = (char *)gtk_entry_get_text(GTK_ENTRY(entry));
  if (*val_str != '\0') {
    char *end;
    *res = (int)strtol(val_str, &end, 10);
    if (*end != '\0') {
      valid = FAILURE;
    }
  } else {
    valid = FAILURE;
  }

  return valid;
}

void do_calculate(const GtkWidget *window, struct widgets_container *data) {
  if (window == NULL) {
    return;
  }
  char buffer[255] = "Strange error\n";

  double x = 0;
  int valid_x = get_double_from_entry(data->x_field, &x);

  queue *parsed;
  int code = parse_to_tokens(
      (char *)gtk_entry_get_text(GTK_ENTRY(data->calc_field)), &parsed);
  if (check_for_x(parsed) == SUCCESS && valid_x == FAILURE && code == SUCCESS) {
    sprintf(buffer, "Invalid X\n");
  } else if (code == FAILURE) {
    sprintf(buffer, "Parser error\n");
  } else {
    queue *rpn = make_rpn(parsed, &code);
    if (code == FAILURE) {
      sprintf(buffer, "RPN making error\n");
    } else {
      double res = calc_rpn(rpn, x, &code);
      if (code == FAILURE) {
        sprintf(buffer, "RPN calculation error\n");
      } else {
        if (isnan(res)) {
          sprintf(buffer, "result: NOT A NUMBER(probably root of negative)\n");
        } else if (isinf(res)) {
          sprintf(buffer, "result: INFINITY(probably zero-division)\n");
        } else {
          sprintf(buffer, "result: %.7lf\n", res);
        }
      }
      free_queue(&rpn);
    }
    free_queue(&parsed);
  }

  gtk_label_set_text(GTK_LABEL(data->result), buffer);
}

int create_points_file(struct widgets_container *data, char *buffer,
                       double start, double end, int steps) {
  queue *parsed;
  int code = parse_to_tokens(
      (char *)gtk_entry_get_text(GTK_ENTRY(data->calc_field)), &parsed);
  if (code == SUCCESS) {
    queue *rpn = make_rpn(parsed, &code);
    if (code == SUCCESS) {
      double *values = get_values(rpn, start, end, steps);
      if (values != NULL) {
        double step = (end - start) / (steps - 1);
        double x = start;
        FILE *function = fopen("function.txt~", "w");
        if (function != NULL) {
          for (int i = 0; i < steps; ++i) {
            fprintf(function, "%lf %lf\n", x, values[i]);
            x += step;
          }
          fclose(function);
        } else {
          code = FAILURE;
        }
        free(values);
      } else {
        code = FAILURE;
      }
      free_queue(&rpn);
    } else {
      sprintf(buffer, "RPN making error\n");
    }
    free_queue(&parsed);
  } else {
    sprintf(buffer, "Parser error\n");
  }

  return code;
}

int create_function_image(struct widgets_container *data, double y_end,
                          double y_start, double x_end, double x_start) {
  int code = SUCCESS;
  char x[40], y[40], plot[70];
  sprintf(x, "set xrange [%s: %s]",
          gtk_entry_get_text(GTK_ENTRY(data->st_field)),
          gtk_entry_get_text(GTK_ENTRY(data->end_field)));
  sprintf(y, "set yrange [%s: %s]",
          gtk_entry_get_text(GTK_ENTRY(data->yst_field)),
          gtk_entry_get_text(GTK_ENTRY(data->yend_field)));
  sprintf(plot, "plot \"function.txt~\" title \"scaling: %lf\" ps 0.5",
          (y_end - y_start) / (x_end - x_start));
  FILE *gnu_plot = popen("gnuplot -persistent", "w");
  if (gnu_plot != NULL) {
    char *commands_gnu_plot[] = {"set terminal png enhanced truecolor",
                                 "set output \"function.png~\"",
                                 "set decimalsign locale",
                                 "set xlabel \"x\"",
                                 "set ylabel \"y\"",
                                 x,
                                 y,
                                 plot,
                                 "set out"};
    int i;

    for (i = 0; i < 9; i++) {
      fprintf(gnu_plot, "%s \n", commands_gnu_plot[i]);
    }
    pclose(gnu_plot);
  } else {
    code = FAILURE;
  }
  return code;
}

void build_image_window() {
  GtkWidget *pic = gtk_image_new_from_file("function.png~");
  if (pic != NULL) {
    GtkWidget *func_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    GtkWidget *grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(func_window), grid);

    gtk_grid_attach(GTK_GRID(grid), pic, 0, 0, 1, 2);

    gtk_widget_show_all(func_window);
  }
}

void do_build(const GtkWidget *window, struct widgets_container *data) {
  if (window == NULL) {
    return;
  }

  char buffer[25] = "function built\n";

  double x_start = 0, x_end = 0;
  int valid_start = get_double_from_entry(data->st_field, &x_start);
  int valid_end = get_double_from_entry(data->end_field, &x_end);
  double y_start = 0, y_end = 0;
  int yvalid_start = get_double_from_entry(data->yst_field, &y_start);
  int yvalid_end = get_double_from_entry(data->yend_field, &y_end);
  int steps;
  int valid_steps = get_int_from_entry(data->steps_field, &steps);

  int code = SUCCESS;

  if (valid_steps == FAILURE || valid_start == FAILURE ||
      yvalid_end == FAILURE || yvalid_start == FAILURE ||
      valid_end == FAILURE || x_end <= x_start || steps < 2) {
    code = FAILURE;
    sprintf(buffer, "Wrong params\n");
  }

  if (code == SUCCESS) {
    code = create_points_file(data, buffer, x_start, x_end, steps);
  }

  if (code == SUCCESS) {
    code = create_function_image(data, y_end, y_start, x_end, x_start);
  }

  if (code == SUCCESS) {
    build_image_window();
  }

  gtk_label_set_text(GTK_LABEL(data->result), buffer);
}
