#include "s21_gtk.h"

//_______________WORKS SETTING BUTTONS______________________________________//
void work_setting_buttons(GtkWidget *background_color_button,
                          GtkWidget *thin_button, GtkWidget *medium_button,
                          GtkWidget *thick_button, GtkWidget *save_image_button,
                          GtkWidget *record_screencast_button) {
  g_signal_connect(background_color_button, "clicked",
                   G_CALLBACK(show_background_color_dialog), NULL);
  g_signal_connect(thin_button, "clicked", G_CALLBACK(on_thin_button_cliced),
                   NULL);
  g_signal_connect(medium_button, "clicked",
                   G_CALLBACK(on_medium_button_cliced), NULL);
  g_signal_connect(thick_button, "clicked", G_CALLBACK(on_thick_button_cliced),
                   NULL);
  g_signal_connect(save_image_button, "clicked",
                   G_CALLBACK(show_save_image_dialog), NULL);
  g_signal_connect(record_screencast_button, "clicked",
                   G_CALLBACK(record_screencast), NULL);
}

void on_thin_button_cliced(GtkWidget *widget __attribute__((unused)),
                           gpointer data __attribute__((unused))) {
  SettingInfo *setting_info = settinginfo();
  setting_info->edge_thickness = THIN;
  update_model_info();
}

void on_medium_button_cliced(GtkWidget *widget __attribute__((unused)),
                             gpointer data __attribute__((unused))) {
  SettingInfo *setting_info = settinginfo();
  setting_info->edge_thickness = MEDIUM;
  update_model_info();
}

void on_thick_button_cliced(GtkWidget *widget __attribute__((unused)),
                            gpointer data __attribute__((unused))) {
  SettingInfo *setting_info = settinginfo();
  setting_info->edge_thickness = THICK;
  update_model_info();
}

void show_background_color_dialog(GtkWidget *widget __attribute__((unused)),
                                  gpointer data __attribute__((unused))) {
  SettingInfo *setting_info = settinginfo();

  GtkWidget *dialog = gtk_color_chooser_dialog_new(
      "Выберите цвет ребер", GTK_WINDOW(gtk_widget_get_toplevel(widget)));
  gtk_color_chooser_set_use_alpha(GTK_COLOR_CHOOSER(dialog), TRUE);

  if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_OK) {
    GdkRGBA color;
    gtk_color_chooser_get_rgba(GTK_COLOR_CHOOSER(dialog), &color);
    if (setting_info->background_color) free(setting_info->background_color);
    setting_info->background_color = gdk_rgba_to_string(&color);
  }

  gtk_widget_destroy(dialog);
}

void show_save_image_dialog(GtkWidget *widget __attribute__((unused)),
                            gpointer data __attribute__((unused))) {
  save_file_dialog(data);
}

void record_screencast(GtkWidget *widget __attribute__((unused)),
                       gpointer data __attribute__((unused))) {
  GtkWidget *dialog = create_save_gif_dialog();
  gchar *name = NULL;
  char filename[500] = {0};

  if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
    name = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
  }

  gtk_widget_destroy(dialog);

  if (name) {
    sprintf(filename, "%s.gif", name);
    start_record(filename);
    g_free(name);
  }
}

//________________________________________________________________________//

//_______________WORKS FILE BUTTONS______________________________________//

void on_open_button_clicked(GtkWidget *a __attribute__((unused)),
                            gpointer user_data) {
  GtkWidget *dialog;
  dialog = gtk_file_chooser_dialog_new(
      "Открыть файл", NULL, GTK_FILE_CHOOSER_ACTION_OPEN, "Отмена",
      GTK_RESPONSE_CANCEL, "Открыть", GTK_RESPONSE_ACCEPT, NULL);

  GtkFileFilter *filter = gtk_file_filter_new();
  gtk_file_filter_set_name(filter, "OBJ Files");
  gtk_file_filter_add_pattern(filter, "*.obj");
  gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(dialog), filter);

  gint res;
  res = gtk_dialog_run(GTK_DIALOG(dialog));
  if (res == GTK_RESPONSE_ACCEPT) {
    GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
    *(char **)user_data = gtk_file_chooser_get_filename(chooser);
    parce_param(*(char **)user_data);
    zero_model_info();
    update_model_info();
  }

  print_entry_file_placeholder((char **)user_data);
  gtk_widget_destroy(dialog);
}

void on_file_ok_activate(GtkWidget *a __attribute__((unused)),
                         gpointer user_data) {
  GtkWidget **entry = filename_entry();
  const char *temp = gtk_entry_get_text(GTK_ENTRY(*entry));

  size_t len = strlen(temp);
  if (len < 4 || strcmp(&temp[len - 4], ".obj") != 0)
    *(char **)user_data = g_strdup("Некорректный ввод");
  else
    *(char **)user_data = g_strdup(temp);

  print_entry_file_placeholder((char **)user_data);
  parce_param(*(char **)user_data);
  zero_model_info();
  update_model_info();
}

//________________________________________________________________________//

//_______________WORKS TRANSFORM BUTTONS___________________________________//

void work_button_translate(gpointer info, GtkWidget *arrow_trans_left,
                           GtkWidget *arrow_trans_right,
                           GtkWidget *arrow_trans_up,
                           GtkWidget *arrow_trans_down,
                           GtkWidget *arrow_trans_diagonal_up,
                           GtkWidget *arrow_trans_diagonal_down) {
  g_signal_connect(arrow_trans_left, "clicked",
                   G_CALLBACK(arrow_translate_left_clicked), info);
  g_signal_connect(arrow_trans_right, "clicked",
                   G_CALLBACK(arrow_translate_right_clicked), info);
  g_signal_connect(arrow_trans_up, "clicked",
                   G_CALLBACK(arrow_translate_up_clicked), info);
  g_signal_connect(arrow_trans_down, "clicked",
                   G_CALLBACK(arrow_translate_down_clicked), info);
  g_signal_connect(arrow_trans_diagonal_up, "clicked",
                   G_CALLBACK(arrow_translate_diagonal_up_clicked), info);
  g_signal_connect(arrow_trans_diagonal_down, "clicked",
                   G_CALLBACK(arrow_translate_diagonal_down_clicked), info);
}

void arrow_translate_left_clicked(GtkWidget *a __attribute__((unused)),
                                  gpointer info) {
  UserData2 *model = (UserData2 *)info;
  model->info->trans_x = count_trans_x(-0.1);
  print_translate_x_placeholder(GTK_ENTRY(model->x));
}
void arrow_translate_right_clicked(GtkWidget *a __attribute__((unused)),
                                   gpointer info) {
  UserData2 *model = (UserData2 *)info;
  model->info->trans_x = count_trans_x(0.1);
  print_translate_x_placeholder(GTK_ENTRY(model->x));
}
void arrow_translate_up_clicked(GtkWidget *a __attribute__((unused)),
                                gpointer info) {
  UserData2 *model = (UserData2 *)info;
  model->info->trans_y = count_trans_y(0.1);
  print_translate_y_placeholder(GTK_ENTRY(model->y));
}
void arrow_translate_down_clicked(GtkWidget *a __attribute__((unused)),
                                  gpointer info) {
  UserData2 *model = (UserData2 *)info;
  model->info->trans_y = count_trans_y(-0.1);
  print_translate_y_placeholder(GTK_ENTRY(model->y));
}
void arrow_translate_diagonal_up_clicked(GtkWidget *a __attribute__((unused)),
                                         gpointer info) {
  UserData2 *model = (UserData2 *)info;
  model->info->trans_z = count_trans_z(0.1);
  print_translate_z_placeholder(GTK_ENTRY(model->z));
}
void arrow_translate_diagonal_down_clicked(GtkWidget *a __attribute__((unused)),
                                           gpointer info) {
  UserData2 *model = (UserData2 *)info;
  model->info->trans_z = count_trans_z(-0.1);
  print_translate_z_placeholder(GTK_ENTRY(model->z));
}

void translate_button_clicked(GtkWidget *a __attribute__((unused)),
                              gpointer user_data) {
  UserData2 *user = (UserData2 *)user_data;

  const gchar *x_text = gtk_entry_get_text(user->x);
  const gchar *y_text = gtk_entry_get_text(user->y);
  const gchar *z_text = gtk_entry_get_text(user->z);

  user->info->trans_x = count_trans_x(g_strtod(x_text, NULL));
  user->info->trans_y = count_trans_y(g_strtod(y_text, NULL));
  user->info->trans_z = count_trans_z(g_strtod(z_text, NULL));

  print_translate_x_placeholder(user->x);
  print_translate_y_placeholder(user->y);
  print_translate_z_placeholder(user->z);
}

//________________________________________________________________________//

//__________________WORKS ROTATE BUTTONS___________________________________//

void work_button_rotate(gpointer info, GtkWidget *arrow_rotate_left,
                        GtkWidget *arrow_rotate_right,
                        GtkWidget *arrow_rotate_up,
                        GtkWidget *arrow_rotate_down,
                        GtkWidget *arrow_rotate_diagonal_up,
                        GtkWidget *arrow_rotate_diagonal_down) {
  g_signal_connect(arrow_rotate_left, "clicked",
                   G_CALLBACK(arrow_rotate_left_clicked), info);
  g_signal_connect(arrow_rotate_right, "clicked",
                   G_CALLBACK(arrow_rotate_right_clicked), info);
  g_signal_connect(arrow_rotate_up, "clicked",
                   G_CALLBACK(arrow_rotate_up_clicked), info);
  g_signal_connect(arrow_rotate_down, "clicked",
                   G_CALLBACK(arrow_rotate_down_clicked), info);
  g_signal_connect(arrow_rotate_diagonal_up, "clicked",
                   G_CALLBACK(arrow_rotate_diagonal_up_clicked), info);
  g_signal_connect(arrow_rotate_diagonal_down, "clicked",
                   G_CALLBACK(arrow_rotate_diagonal_down_clicked), info);
}

void arrow_rotate_left_clicked(GtkWidget *a __attribute__((unused)),
                               gpointer info) {
  UserData2 *model = (UserData2 *)info;
  model->info->rotate_x = count_rotate_x(-1);
  print_rotate_x_placeholder(model->x);
}
void arrow_rotate_right_clicked(GtkWidget *a __attribute__((unused)),
                                gpointer info) {
  UserData2 *model = (UserData2 *)info;
  model->info->rotate_x = count_rotate_x(1);
  print_rotate_x_placeholder(model->x);
}
void arrow_rotate_up_clicked(GtkWidget *a __attribute__((unused)),
                             gpointer info) {
  UserData2 *model = (UserData2 *)info;
  model->info->rotate_y = count_rotate_y(1);
  print_rotate_y_placeholder(model->y);
}
void arrow_rotate_down_clicked(GtkWidget *a __attribute__((unused)),
                               gpointer info) {
  UserData2 *model = (UserData2 *)info;
  model->info->rotate_y = count_rotate_y(-1);
  print_rotate_y_placeholder(model->y);
}
void arrow_rotate_diagonal_up_clicked(GtkWidget *a __attribute__((unused)),
                                      gpointer info) {
  UserData2 *model = (UserData2 *)info;
  model->info->rotate_z = count_rotate_z(1);
  print_rotate_z_placeholder(model->z);
}
void arrow_rotate_diagonal_down_clicked(GtkWidget *a __attribute__((unused)),
                                        gpointer info) {
  UserData2 *model = (UserData2 *)info;
  model->info->rotate_z = count_rotate_z(-1);
  print_rotate_z_placeholder(model->z);
}

void rotate_button_clicked(GtkWidget *a __attribute__((unused)),
                           gpointer user_data) {
  UserData2 *user = (UserData2 *)user_data;

  const gchar *x_text = gtk_entry_get_text(user->x);
  const gchar *y_text = gtk_entry_get_text(user->y);
  const gchar *z_text = gtk_entry_get_text(user->z);

  user->info->rotate_x = count_rotate_x(g_strtod(x_text, NULL));
  user->info->rotate_y = count_rotate_y(g_strtod(y_text, NULL));
  user->info->rotate_z = count_rotate_z(g_strtod(z_text, NULL));

  print_rotate_x_placeholder(user->x);
  print_rotate_y_placeholder(user->y);
  print_rotate_z_placeholder(user->z);
}

//________________________________________________________________________//

//__________________WORKS ROTATE BUTTONS___________________________________//

void work_scale_button(GtkWidget **scale_entry, GtkWidget *ok_button,
                       GtkWidget *plus_button, GtkWidget *minus_button) {
  static UserData3 data3;
  gpointer data = init_user_data3(&data3, GTK_ENTRY(*scale_entry));

  g_signal_connect(*scale_entry, "activate", G_CALLBACK(on_scale_ok_activate),
                   data);
  g_signal_connect(ok_button, "clicked", G_CALLBACK(on_scale_ok_activate),
                   data);
  g_signal_connect(plus_button, "clicked", G_CALLBACK(on_scale_plus_clicked),
                   data);
  g_signal_connect(minus_button, "clicked", G_CALLBACK(on_scale_minus_clicked),
                   data);
};

void on_scale_ok_activate(GtkWidget *a __attribute__((unused)),
                          gpointer user_data) {
  UserData3 *data = (UserData3 *)user_data;

  if (!GTK_IS_ENTRY(data->entry)) {
    g_print("Error: Not a GtkEntry\n");
    return;
  }

  const gchar *scale_text = gtk_entry_get_text(data->entry);
  count_scale(-data->info->scale);
  data->info->scale = count_scale(atoi(scale_text));

  print_scale_placeholder(data->entry);
}

void on_scale_plus_clicked(GtkWidget *a __attribute__((unused)),
                           gpointer user_data) {
  UserData3 *data = (UserData3 *)user_data;
  data->info->scale = count_scale(1);
  print_scale_placeholder(data->entry);
}

void on_scale_minus_clicked(GtkWidget *a __attribute__((unused)),
                            gpointer user_data) {
  UserData3 *data = (UserData3 *)user_data;
  data->info->scale = count_scale(-1);
  print_scale_placeholder(data->entry);
}
