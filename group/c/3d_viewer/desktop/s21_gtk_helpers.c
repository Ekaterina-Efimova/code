#include "s21_gtk.h"

void line_in_box(GtkWidget *box, GtkWidget *widget1, GtkWidget *widget2,
                 GtkWidget *widget3) {
  if (widget1) gtk_box_pack_start(GTK_BOX(box), widget1, FALSE, FALSE, 0);
  if (widget2) gtk_box_pack_start(GTK_BOX(box), widget2, FALSE, FALSE, 0);
  if (widget3) gtk_box_pack_start(GTK_BOX(box), widget3, FALSE, FALSE, 0);
}

void create_box(GtkWidget *box, GtkWidget *button1, GtkWidget *button2,
                GtkWidget *button3, char *str, int a, int b, int c) {
  GtkWidget *label = NULL;
  if (str) label = gtk_label_new(str);
  GtkWidget *b_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, a);

  if (button1) gtk_widget_set_size_request(button1, b, c);
  if (button2) gtk_widget_set_size_request(button2, b, c);
  if (button3) gtk_widget_set_size_request(button3, b, c);

  line_in_box(b_box, button1, button2, button3);
  line_in_box(box, label, b_box, NULL);
}

void init_setting_info(SettingInfo *info) {
  FILE *f = fopen("setting.txt", "r");

  if (f) {
    int num_read;

    num_read = fscanf(f, "%d\n", &info->projection_type);
    if (num_read != 1) info->projection_type = 0;

    num_read = fscanf(f, "%d\n", &info->edges_type);
    if (num_read != 1) info->edges_type = 0;

    info->edge_color = malloc(sizeof(char) * 100);
    num_read = fscanf(f, "%s\n", info->edge_color);
    if (num_read != 1) {
      free(info->edge_color);
      info->edge_color = NULL;
    }

    num_read = fscanf(f, "%d\n", &info->edge_thickness);
    if (num_read != 1) info->edge_thickness = 0;

    info->background_color = malloc(sizeof(char) * 100);
    num_read = fscanf(f, "%s\n", info->background_color);
    if (num_read != 1) {
      free(info->background_color);
      info->background_color = NULL;
    }

    num_read = fscanf(f, "%d\n", &info->vetrtex_type_print);
    if (num_read != 1) info->vetrtex_type_print = 0;

    info->vertex_color = malloc(sizeof(char) * 100);
    num_read = fscanf(f, "%s\n", info->vertex_color);
    if (num_read != 1) {
      free(info->vertex_color);
      info->vertex_color = NULL;
    }

    num_read = fscanf(f, "%d\n", &info->vertex_size);
    if (num_read != 1) info->vertex_size = 0;

    fclose(f);
  }
}

void save_settings() {
  SettingInfo *info = settinginfo();
  FILE *f = fopen("setting.txt", "w");

  if (f) {
    fprintf(f, "%d\n%d\n%s\n%d\n%s\n%d\n%s\n%d", info->projection_type,
            info->edges_type, info->edge_color ? info->edge_color : "",
            info->edge_thickness,
            info->background_color ? info->background_color : "",
            info->vetrtex_type_print,
            info->vertex_color ? info->vertex_color : "", info->vertex_size);
    fclose(f);
  }
}

GdkRGBA get_gtk_color() {
  GdkRGBA color;
  SettingInfo *setting_info = settinginfo();
  const char *color_string = setting_info->background_color;
  gdk_rgba_parse(&color, color_string);

  return color;
}

void zero_model_info() {
  ModelInfo *info = modelinfo();
  Parametrs *p = get_param();

  count_scale(-info->scale);
  count_rotate_x(-info->rotate_x);
  count_rotate_y(-info->rotate_y);
  count_rotate_z(-info->rotate_z);
  count_trans_x(-info->trans_x);
  count_trans_y(-info->trans_y);
  count_trans_z(-info->trans_z);

  info->rotate_x = 0;
  info->rotate_y = 0;
  info->rotate_z = 0;
  info->scale = 0;
  info->trans_x = 0;
  info->trans_y = 0;
  info->trans_z = 0;
  info->num_vertices = p->count_points;
  info->num_edges = p->count_edges;
}