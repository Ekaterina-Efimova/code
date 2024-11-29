#include "s21_gtk.h"

GtkWidget **label_1() {
  static GtkWidget info_label = {0};
  static GtkWidget *info_label_ptr = &info_label;
  return &info_label_ptr;
}

GtkWidget **filename_entry() {
  static GtkWidget file = {0};
  static GtkWidget *file_ptr = &file;
  return &file_ptr;
}

GtkWidget **get_model_area() {
  static GtkWidget area = {0};
  static GtkWidget *area_ptr = &area;
  return &area_ptr;
}

ModelInfo *modelinfo() {
  static ModelInfo info = {0};
  return &info;
}

SettingInfo *settinginfo() {
  static SettingInfo info = {0};
  return &info;
}

int count_scale(int a) {
  static int scale = 100;
  return scale += a;
}

double count_rotate_x(double a) {
  static double rotate = 0.0;
  return rotate += a;
}
double count_rotate_y(double a) {
  static double rotate = 0.0;
  return rotate += a;
}
double count_rotate_z(double a) {
  static double rotate = 0.0;
  return rotate += a;
}

double count_trans_x(double a) {
  static double trans = 0.0;
  return trans += a;
}
double count_trans_y(double a) {
  static double trans = 0.0;
  return trans += a;
}
double count_trans_z(double a) {
  static double trans = 0.0;
  return trans += a;
}

char *get_filename(const char *path) {
  char *filename = strrchr(path, '/');
  if (filename == NULL) {
    filename = strrchr(path, '\\');
  }
  if (filename != NULL) {
    filename++;
  } else {
    filename = (char *)path;
  }
  return filename;
}

gpointer init_user_data2(UserData2 *data, GtkWidget *x, GtkWidget *y,
                         GtkWidget *z) {
  GtkWidget **label = label_1();
  data->x = GTK_ENTRY(x);
  data->y = GTK_ENTRY(y);
  data->z = GTK_ENTRY(z);
  data->info = modelinfo();
  data->label = *label;

  return (gpointer)data;
}

gpointer init_user_data3(UserData3 *data, GtkEntry *entry) {
  GtkWidget **label = label_1();
  data->entry = entry;
  data->info = modelinfo();
  data->label = *label;

  return (gpointer)data;
}

GdkRGBA init_rgba(double r, double g, double b, double a) {
  GdkRGBA color;
  color.red = r;
  color.green = g;
  color.blue = b;
  color.alpha = a;
  return color;
}

ColorMapObject *get_color_map() {
  static ColorMapObject color;
  static GifColorType colors[256] = {0};
  for (int i = 0; i < 256; i++) {
    colors[i].Red = (i * 255) / 255;
    colors[i].Green = (i * 255) / 255;
    colors[i].Blue = (i * 255) / 255;
  }

  color.ColorCount = 256;
  color.Colors = colors;
  return &color;
}
