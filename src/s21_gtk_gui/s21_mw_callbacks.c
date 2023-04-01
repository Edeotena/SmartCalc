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

int get_int_from_entry(GtkWidget *entry, long *res) {
  int valid = SUCCESS;
  char *val_str = (char *)gtk_entry_get_text(GTK_ENTRY(entry));
  if (*val_str != '\0') {
    char *end;
    *res = strtol(val_str, &end, 10);
    if (*end != '\0') {
      valid = FAILURE;
    }
  } else {
    valid = FAILURE;
  }

  return valid;
}

void do_calculate(GtkWidget *window, struct widgets_container *data) {
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
    code = FAILURE;
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

void do_build(GtkWidget *window, struct widgets_container *data) {
  if (window == NULL) {
    return;
  }

  char buffer[25] = "function built\n";

  long start = 0, end = 0;
  int valid_start = get_int_from_entry(data->st_field, &start);
  int valid_end = get_int_from_entry(data->end_field, &end);
  long ystart = 0, yend = 0;
  int yvalid_start = get_int_from_entry(data->yst_field, &ystart);
  int yvalid_end = get_int_from_entry(data->yend_field, &yend);

  int code = SUCCESS;

  if (valid_start == FAILURE || yvalid_end == FAILURE ||
      yvalid_start == FAILURE || valid_end == FAILURE || end <= start) {
    code = FAILURE;
    sprintf(buffer, "Wrong params\n");
  }

  if (code == SUCCESS) {
    queue *parsed;
    code = parse_to_tokens(
        (char *)gtk_entry_get_text(GTK_ENTRY(data->calc_field)), &parsed);
    if (code == SUCCESS) {
      queue *rpn = make_rpn(parsed, &code);
      if (code == SUCCESS) {
        free_queue(&rpn);
      } else {
        sprintf(buffer, "RPN making error\n");
      }
      free_queue(&parsed);
    } else {
      sprintf(buffer, "Parser error\n");
    }
  }

  char *line = (char *)gtk_entry_get_text(GTK_ENTRY(data->calc_field));
  char gnu_str[400] = "plot ";
  for (int i = 0, skip = 5; i < 255; ++i) {
    gnu_str[i + skip] = line[i];
    if (line[i] == '^') {
      gnu_str[i + skip] = '*';
      ++skip;
      gnu_str[i + skip] = '*';
    }
  }

  if (code == SUCCESS) {
    char x[40], y[40];
    sprintf(x, "set xrange [%ld: %ld]", start, end);
    sprintf(y, "set yrange [%ld: %ld]", ystart, yend);
    char *commands_gnu_plot[] = {"set terminal png enhanced truecolor",
                                 "set output \"function.png\"",
                                 x,
                                 y,
                                 gnu_str,
                                 "set out"};
    FILE *gnu_plot = popen("gnuplot -persistent", "w");
    int i;

    for (i = 0; i < 6; i++) {
      fprintf(gnu_plot, "%s \n", commands_gnu_plot[i]);
    }
    pclose(gnu_plot);
  }

  if (code == SUCCESS) {
    GtkWidget *pic = gtk_image_new_from_file("function.png");
    if (pic != NULL) {
      GtkWidget *func_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
      GtkWidget *grid = gtk_grid_new();
      gtk_container_add(GTK_CONTAINER(func_window), grid);

      gtk_grid_attach(GTK_GRID(grid), pic, 0, 0, 1, 2);

      gtk_widget_show_all(func_window);
    }
  }

  gtk_label_set_text(GTK_LABEL(data->result), buffer);
}
