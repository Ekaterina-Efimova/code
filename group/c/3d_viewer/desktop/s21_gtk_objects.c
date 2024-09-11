#include "s21_gtk.h"

void run_3d_viewer(int argc, char *argv[]) {
  ModelInfo *info = modelinfo();
  SettingInfo *setting_info = settinginfo();
  init_setting_info(setting_info);
  char *filename = NULL;
  info->filename = &filename;

  gtk_init(&argc, &argv);

  GtkWidget *window = create_main_window();
  GtkWidget *main_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
  gtk_container_add(GTK_CONTAINER(window), main_box);

  GtkWidget *vertical_right = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  GtkWidget *vertical_left = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

  create_main_vertical_left(vertical_left, &filename);
  create_main_vertical_right(vertical_right);
  create_main_main_box(main_box, vertical_right, vertical_left);

  gtk_widget_show_all(window);
  gtk_main();

  save_settings();
  if (filename) g_free(filename);
  if (setting_info->background_color) g_free(setting_info->background_color);
  if (setting_info->edge_color) g_free(setting_info->edge_color);
  if (setting_info->vertex_color) g_free(setting_info->vertex_color);
  if (get_param()) free_param(get_param());
}
//**************************************************************************//

//****************MAIN WINDOW***********************************************//
GtkWidget *create_main_window() {
  GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(window), "3D Viewer");
  gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
  g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

  return window;
}

void create_main_main_box(GtkWidget *main_box, GtkWidget *vertical_right,
                          GtkWidget *vertical_left) {
  gtk_box_pack_start(GTK_BOX(main_box), vertical_left, TRUE, TRUE, 10);
  gtk_box_pack_start(GTK_BOX(main_box), vertical_right, FALSE, FALSE, 5);
}

void create_main_vertical_left(GtkWidget *vertical_left, char **filename) {
  GtkWidget *filename_entry = create_filename_entry(filename);
  GtkWidget *small_vertical_left = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
  gtk_box_pack_start(GTK_BOX(vertical_left), filename_entry, FALSE, FALSE, 5);
  gtk_box_pack_start(GTK_BOX(vertical_left), small_vertical_left, FALSE, FALSE,
                     5);

  GtkWidget *settings_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
  create_setting_box(settings_box);
  gtk_box_pack_start(GTK_BOX(small_vertical_left), settings_box, TRUE, TRUE, 5);

  GtkWidget **model_area = get_model_area();
  create_model_area(model_area);
  gtk_box_pack_start(GTK_BOX(small_vertical_left), *model_area, TRUE, TRUE, 5);
}

void create_main_vertical_right(GtkWidget *vertical_right) {
  GtkWidget **info_label = label_1();
  *info_label = gtk_label_new("Файл: Выберите файл");
  gtk_box_pack_start(GTK_BOX(vertical_right), *info_label, FALSE, FALSE, 5);

  GtkWidget *trans_x = NULL, *trans_y = NULL, *trans_z = NULL;
  GtkWidget *rotate_x = NULL, *rotate_y = NULL, *rotate_z = NULL;
  GtkWidget *transform_entries = create_transform_entries(
      trans_x, trans_y, trans_z, rotate_x, rotate_y, rotate_z);
  gtk_box_pack_start(GTK_BOX(vertical_right), transform_entries, FALSE, FALSE,
                     5);

  GtkWidget *scale_entry;
  GtkWidget *scale_box = create_scale_entry(&scale_entry);
  gtk_box_pack_start(GTK_BOX(vertical_right), scale_box, FALSE, FALSE, 5);
}
//**************************************************************************//

//********************SETTINGS BOX******************************************//
void create_setting_box(GtkWidget *settings_box) {
  // Кнопка "Цвет фона"
  GtkWidget *background_color_button =
      gtk_button_new_with_label("Выберите цвет");
  create_box(settings_box, background_color_button, NULL, NULL, "Цвет фона",
             SPASE_1, HIGHT, WIGHT);

  // Кнопка "Настройки ребер"
  GtkWidget *thin_button = NULL, *medium_button = NULL, *thick_button = NULL;
  create_edges_setting_box(&settings_box, &thin_button, &medium_button,
                           &thick_button);

  // Кнопка "Сохранить изображение"
  GtkWidget *save_image_button = gtk_button_new_with_label("Сохранить");
  gtk_widget_set_size_request(save_image_button, HIGHT, WIGHT);
  gtk_box_pack_start(GTK_BOX(settings_box), save_image_button, FALSE, FALSE, 0);

  // Кнопка "Записать скринкаст"
  GtkWidget *record_screencast_button = gtk_button_new_with_label("Запись");
  gtk_widget_set_size_request(record_screencast_button, HIGHT, WIGHT);
  gtk_box_pack_start(GTK_BOX(settings_box), record_screencast_button, FALSE,
                     FALSE, 0);

  work_setting_buttons(background_color_button, thin_button, medium_button,
                       thick_button, save_image_button,
                       record_screencast_button);
}

GtkWidget *create_save_gif_dialog() {
  GtkWidget *dialog = gtk_file_chooser_dialog_new(
      "Сохранить скринкаст", NULL, GTK_FILE_CHOOSER_ACTION_SAVE, "Отмена",
      GTK_RESPONSE_CANCEL, "Сохранить", GTK_RESPONSE_ACCEPT, NULL);

  GtkFileFilter *filter = gtk_file_filter_new();
  gtk_file_filter_set_name(filter, "GIF Files");
  gtk_file_filter_add_mime_type(filter, "image/gif");
  gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(dialog), filter);

  return dialog;
}

//_______________EDGE SETTING DIALOG_________________________________________//
void create_edges_setting_box(GtkWidget **box, GtkWidget **thin_button,
                              GtkWidget **medium_button,
                              GtkWidget **thick_button) {
  GtkWidget *label = gtk_label_new("Настройки ребер:");
  gtk_box_pack_start(GTK_BOX(*box), label, FALSE, FALSE, 0);
  create_thickness_box(*box, thin_button, medium_button, thick_button);
}

void create_thickness_box(GtkWidget *box, GtkWidget **thin_button,
                          GtkWidget **medium_button, GtkWidget **thick_button) {
  *thin_button = gtk_button_new_with_label("Тонкие");
  *medium_button = gtk_button_new_with_label("Средние");
  *thick_button = gtk_button_new_with_label("Толстые");

  create_box(box, *thin_button, *medium_button, *thick_button, "Толщина ребер",
             SPASE_2, HIGHT / 3, WIGHT);
}

//**************************************************************************//

//****************3D PRINT BOX***********************************************//
void create_model_area(GtkWidget **model_area) {
  model_area = get_model_area();
  *model_area = gtk_gl_area_new();
  gtk_widget_set_size_request(*model_area, 800, 600);
  main_window(*model_area);
}
//**************************************************************************//

//*******************OPEN FILE BOX*******************************************//
GtkWidget *create_filename_entry(char **filename) {
  GtkWidget *entry_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 4);
  GtkWidget *b_box = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
  GtkWidget *open_button = gtk_button_new_with_label("Поиск файла");
  GtkWidget *file_ok_button = gtk_button_new_with_label("OK");
  GtkWidget **entry_file = filename_entry();
  *entry_file = gtk_entry_new();

  gtk_box_pack_start(GTK_BOX(entry_box), b_box, FALSE, FALSE, 4);
  gtk_widget_set_size_request(open_button, 245, 20);
  gtk_container_add(GTK_CONTAINER(b_box), open_button);
  gtk_widget_set_size_request(*entry_file, 700, 20);
  gtk_box_pack_start(GTK_BOX(entry_box), *entry_file, FALSE, FALSE, 4);
  gtk_box_pack_start(GTK_BOX(entry_box), file_ok_button, FALSE, FALSE, 4);

  print_entry_file_placeholder(filename);

  g_signal_connect(open_button, "clicked", G_CALLBACK(on_open_button_clicked),
                   filename);
  g_signal_connect(*entry_file, "activate", G_CALLBACK(on_file_ok_activate),
                   (gpointer)filename);
  g_signal_connect(file_ok_button, "clicked", G_CALLBACK(on_file_ok_activate),
                   (gpointer)filename);

  return entry_box;
}

void print_entry_file_placeholder(char **filename) {
  GtkWidget **entry = filename_entry();
  char placeholder_text[1000];

  gtk_entry_set_text(GTK_ENTRY(*entry), "");
  sprintf(
      placeholder_text, "%s",
      *filename ? *filename : "Введите путь к файлу с расширением \".obj\"");
  gtk_entry_set_placeholder_text(GTK_ENTRY(*entry), placeholder_text);
}

//**************************************************************************//

//****************MODEL INFO BOX********************************************//
void update_model_info() {
  GtkWidget **info_label = label_1();
  ModelInfo *info = modelinfo();
  SettingInfo *setting_info = settinginfo();
  char info_text[5000] = {0};

  sprintf(info_text, "Файл: %s\nВершины: %d\tРебра: %d\nТолщина ребер: %s",
          *info->filename ? access(*info->filename, F_OK) != -1
                                ? get_filename(*info->filename)
                                : "Файл не найден"
                          : "Файл не выбран",
          info->num_vertices, info->num_edges,
          setting_info->edge_thickness == 2   ? "Толстые"
          : setting_info->edge_thickness == 1 ? "Средние"
                                              : "Тонкие");

  gtk_label_set_text(GTK_LABEL(*info_label), info_text);
}
//**************************************************************************//

//*****************TRANSFORM BOX*******************************************//
GtkWidget *create_transform_entries(GtkWidget *trans_x, GtkWidget *trans_y,
                                    GtkWidget *trans_z, GtkWidget *rotate_x,
                                    GtkWidget *rotate_y, GtkWidget *rotate_z) {
  GtkWidget *transform_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

  trans_x = gtk_entry_new();
  trans_y = gtk_entry_new();
  trans_z = gtk_entry_new();

  gtk_entry_set_input_purpose(GTK_ENTRY(trans_x), GTK_INPUT_PURPOSE_NUMBER);
  gtk_entry_set_input_purpose(GTK_ENTRY(trans_y), GTK_INPUT_PURPOSE_NUMBER);
  gtk_entry_set_input_purpose(GTK_ENTRY(trans_z), GTK_INPUT_PURPOSE_NUMBER);

  static UserData2 userdata1;

  create_translate_xyz_entries(transform_box, trans_x, trans_y, trans_z);
  create_translate_button(
      transform_box, init_user_data2(&userdata1, trans_x, trans_y, trans_z));

  rotate_x = gtk_entry_new();
  rotate_y = gtk_entry_new();
  rotate_z = gtk_entry_new();

  gtk_entry_set_input_purpose(GTK_ENTRY(rotate_x), GTK_INPUT_PURPOSE_NUMBER);
  gtk_entry_set_input_purpose(GTK_ENTRY(rotate_y), GTK_INPUT_PURPOSE_NUMBER);
  gtk_entry_set_input_purpose(GTK_ENTRY(rotate_z), GTK_INPUT_PURPOSE_NUMBER);

  create_rotate_xyz_entries(transform_box, rotate_x, rotate_y, rotate_z);

  static UserData2 userdata2;
  create_rotate_button(
      transform_box, init_user_data2(&userdata2, rotate_x, rotate_y, rotate_z));

  return transform_box;
}

void create_vertical_transform_box(GtkWidget *main_box, GtkWidget *label1,
                                   GtkWidget *box1, GtkWidget *label2,
                                   GtkWidget *box2, GtkWidget *label3,
                                   GtkWidget *box3) {
  gtk_box_pack_start(GTK_BOX(main_box), label1, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(main_box), box1, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(main_box), label2, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(main_box), box2, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(main_box), label3, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(main_box), box3, FALSE, FALSE, 0);
}

//_______________TRANSLATE BOX____________________________________________//
void create_translate_xyz_entries(GtkWidget *box, GtkWidget *x, GtkWidget *y,
                                  GtkWidget *z) {
  // создание кнопок-стрелок
  GtkWidget *arrow_trans_left = gtk_button_new();
  GtkWidget *arrow_trans_right = gtk_button_new();
  GtkWidget *arrow_trans_up = gtk_button_new();
  GtkWidget *arrow_trans_down = gtk_button_new();
  GtkWidget *arrow_trans_diagonal_up = gtk_button_new();
  GtkWidget *arrow_trans_diagonal_down = gtk_button_new();
  create_label_translate_button(
      arrow_trans_left, arrow_trans_right, arrow_trans_up, arrow_trans_down,
      arrow_trans_diagonal_up, arrow_trans_diagonal_down);

  // горизонтальная группировка
  GtkWidget *horizontal_x = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
  line_in_box(horizontal_x, arrow_trans_left, x, arrow_trans_right);
  GtkWidget *horizontal_y = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
  line_in_box(horizontal_y, arrow_trans_down, y, arrow_trans_up);
  GtkWidget *horizontal_z = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
  line_in_box(horizontal_z, arrow_trans_diagonal_down, z,
              arrow_trans_diagonal_up);

  // вертикальная группировка
  create_vertical_transform_box(
      box, gtk_label_new("Перемещение по X:"), horizontal_x,
      gtk_label_new("Перемещение по Y:"), horizontal_y,
      gtk_label_new("Перемещение по Z:"), horizontal_z);

  print_translate_x_placeholder(GTK_ENTRY(x));
  print_translate_y_placeholder(GTK_ENTRY(y));
  print_translate_z_placeholder(GTK_ENTRY(z));

  static UserData2 data;
  work_button_translate(init_user_data2(&data, x, y, z), arrow_trans_left,
                        arrow_trans_right, arrow_trans_up, arrow_trans_down,
                        arrow_trans_diagonal_up, arrow_trans_diagonal_down);
}

void create_translate_button(GtkWidget *transform_box, gpointer data) {
  GtkWidget *button_box = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
  gtk_box_pack_start(GTK_BOX(transform_box), button_box, FALSE, FALSE, 0);
  GtkWidget *translate_button = gtk_button_new_with_label("Переместить");
  gtk_widget_set_size_request(translate_button, 115, 15);
  gtk_container_add(GTK_CONTAINER(button_box), translate_button);

  g_signal_connect(translate_button, "clicked",
                   G_CALLBACK(translate_button_clicked), data);
}

void create_label_translate_button(GtkWidget *arrow_trans_left,
                                   GtkWidget *arrow_trans_right,
                                   GtkWidget *arrow_trans_up,
                                   GtkWidget *arrow_trans_down,
                                   GtkWidget *arrow_trans_diagonal_up,
                                   GtkWidget *arrow_trans_diagonal_down) {
  // создание лэйблов на кнопки
  GtkWidget *arrow_trans_left_label = gtk_label_new(NULL);
  GtkWidget *arrow_trans_right_label = gtk_label_new(NULL);
  GtkWidget *arrow_trans_up_label = gtk_label_new(NULL);
  GtkWidget *arrow_trans_down_label = gtk_label_new(NULL);
  GtkWidget *arrow_trans_diagonal_up_label = gtk_label_new(NULL);
  GtkWidget *arrow_trans_diagonal_down_label = gtk_label_new(NULL);

  // задание значений лэйблов и установка их на кнопки
  gtk_label_set_markup(GTK_LABEL(arrow_trans_left_label),
                       "<span font_desc='15'>&#x2190;</span>");
  gtk_container_add(GTK_CONTAINER(arrow_trans_left), arrow_trans_left_label);

  gtk_label_set_markup(GTK_LABEL(arrow_trans_right_label),
                       "<span font_desc='15'>&#x2192;</span>");
  gtk_container_add(GTK_CONTAINER(arrow_trans_right), arrow_trans_right_label);

  gtk_label_set_markup(GTK_LABEL(arrow_trans_up_label),
                       "<span font_desc='15'>&#x2191;</span>");
  gtk_container_add(GTK_CONTAINER(arrow_trans_up), arrow_trans_up_label);

  gtk_label_set_markup(GTK_LABEL(arrow_trans_down_label),
                       "<span font_desc='15'>&#x2193;</span>");
  gtk_container_add(GTK_CONTAINER(arrow_trans_down), arrow_trans_down_label);

  gtk_label_set_markup(GTK_LABEL(arrow_trans_diagonal_up_label),
                       "<span font_desc='15'>&#x2197;</span>");
  gtk_container_add(GTK_CONTAINER(arrow_trans_diagonal_up),
                    arrow_trans_diagonal_up_label);

  gtk_label_set_markup(GTK_LABEL(arrow_trans_diagonal_down_label),
                       "<span font_desc='15'>&#x2199;</span>");
  gtk_container_add(GTK_CONTAINER(arrow_trans_diagonal_down),
                    arrow_trans_diagonal_down_label);
}

void print_translate_x_placeholder(GtkEntry *entry) {
  char placeholder_text[10];

  gtk_entry_set_alignment(GTK_ENTRY(entry), 0.5);

  gtk_entry_set_text(entry, "");
  sprintf(placeholder_text, "%.2f", count_trans_x(0));
  gtk_entry_set_placeholder_text(entry, placeholder_text);
}

void print_translate_y_placeholder(GtkEntry *entry) {
  char placeholder_text[10];

  gtk_entry_set_alignment(GTK_ENTRY(entry), 0.5);

  gtk_entry_set_text(entry, "");
  sprintf(placeholder_text, "%.2f", count_trans_y(0));
  gtk_entry_set_placeholder_text(entry, placeholder_text);
}

void print_translate_z_placeholder(GtkEntry *entry) {
  char placeholder_text[10];

  gtk_entry_set_alignment(GTK_ENTRY(entry), 0.5);

  gtk_entry_set_text(entry, "");
  sprintf(placeholder_text, "%.2f", count_trans_z(0));
  gtk_entry_set_placeholder_text(entry, placeholder_text);
}

//_______________ROTATE BOX______________________________________________//

void create_rotate_xyz_entries(GtkWidget *box, GtkWidget *x, GtkWidget *y,
                               GtkWidget *z) {
  // создание кнопок-стрелок
  GtkWidget *arrow_rotate_left = gtk_button_new();
  GtkWidget *arrow_rotate_right = gtk_button_new();
  GtkWidget *arrow_rotate_up = gtk_button_new();
  GtkWidget *arrow_rotate_down = gtk_button_new();
  GtkWidget *arrow_rotate_diagonal_up = gtk_button_new();
  GtkWidget *arrow_rotate_diagonal_down = gtk_button_new();
  create_label_rotate_button(
      arrow_rotate_left, arrow_rotate_right, arrow_rotate_up, arrow_rotate_down,
      arrow_rotate_diagonal_up, arrow_rotate_diagonal_down);

  // горизонтальная группировка
  GtkWidget *horizontal_x = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
  line_in_box(horizontal_x, arrow_rotate_left, x, arrow_rotate_right);
  GtkWidget *horizontal_y = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
  line_in_box(horizontal_y, arrow_rotate_down, y, arrow_rotate_up);
  GtkWidget *horizontal_z = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
  line_in_box(horizontal_z, arrow_rotate_diagonal_down, z,
              arrow_rotate_diagonal_up);

  // вертикальная группировка
  create_vertical_transform_box(box, gtk_label_new("Поворот по X:"),
                                horizontal_x, gtk_label_new("Поворот по Y:"),
                                horizontal_y, gtk_label_new("Поворот по Z:"),
                                horizontal_z);

  print_rotate_x_placeholder(GTK_ENTRY(x));
  print_rotate_y_placeholder(GTK_ENTRY(y));
  print_rotate_z_placeholder(GTK_ENTRY(z));

  static UserData2 user;
  work_button_rotate(init_user_data2(&user, x, y, z), arrow_rotate_left,
                     arrow_rotate_right, arrow_rotate_up, arrow_rotate_down,
                     arrow_rotate_diagonal_up, arrow_rotate_diagonal_down);
}

void create_rotate_button(GtkWidget *transform_box, gpointer data) {
  GtkWidget *button_box = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
  gtk_box_pack_start(GTK_BOX(transform_box), button_box, FALSE, FALSE, 0);
  GtkWidget *rotate_button = gtk_button_new_with_label("Повернуть");
  gtk_widget_set_size_request(rotate_button, 115, 15);
  gtk_container_add(GTK_CONTAINER(button_box), rotate_button);

  g_signal_connect(rotate_button, "clicked", G_CALLBACK(rotate_button_clicked),
                   data);
}

void create_label_rotate_button(GtkWidget *arrow_rotate_left,
                                GtkWidget *arrow_rotate_right,
                                GtkWidget *arrow_rotate_up,
                                GtkWidget *arrow_rotate_down,
                                GtkWidget *arrow_rotate_diagonal_up,
                                GtkWidget *arrow_rotate_diagonal_down) {
  // создание лэйблов на кнопки
  GtkWidget *arrow_rotate_left_label = gtk_label_new(NULL);
  GtkWidget *arrow_rotate_right_label = gtk_label_new(NULL);
  GtkWidget *arrow_rotate_up_label = gtk_label_new(NULL);
  GtkWidget *arrow_rotate_down_label = gtk_label_new(NULL);
  GtkWidget *arrow_rotate_diagonal_up_label = gtk_label_new(NULL);
  GtkWidget *arrow_rotate_diagonal_down_label = gtk_label_new(NULL);

  // задание значений лэйблов и установка их на кнопки
  gtk_label_set_markup(GTK_LABEL(arrow_rotate_left_label),
                       "<span font_desc='15'>&#x2190;</span>");
  gtk_container_add(GTK_CONTAINER(arrow_rotate_left), arrow_rotate_left_label);

  gtk_label_set_markup(GTK_LABEL(arrow_rotate_right_label),
                       "<span font_desc='15'>&#x2192;</span>");
  gtk_container_add(GTK_CONTAINER(arrow_rotate_right),
                    arrow_rotate_right_label);

  gtk_label_set_markup(GTK_LABEL(arrow_rotate_up_label),
                       "<span font_desc='15'>&#x2191;</span>");
  gtk_container_add(GTK_CONTAINER(arrow_rotate_up), arrow_rotate_up_label);

  gtk_label_set_markup(GTK_LABEL(arrow_rotate_down_label),
                       "<span font_desc='15'>&#x2193;</span>");
  gtk_container_add(GTK_CONTAINER(arrow_rotate_down), arrow_rotate_down_label);

  gtk_label_set_markup(GTK_LABEL(arrow_rotate_diagonal_up_label),
                       "<span font_desc='15'>&#x2197;</span>");
  gtk_container_add(GTK_CONTAINER(arrow_rotate_diagonal_up),
                    arrow_rotate_diagonal_up_label);

  gtk_label_set_markup(GTK_LABEL(arrow_rotate_diagonal_down_label),
                       "<span font_desc='15'>&#x2199;</span>");
  gtk_container_add(GTK_CONTAINER(arrow_rotate_diagonal_down),
                    arrow_rotate_diagonal_down_label);
}

void print_rotate_x_placeholder(GtkEntry *entry) {
  char placeholder_text[10];

  gtk_entry_set_alignment(GTK_ENTRY(entry), 0.5);

  gtk_entry_set_text(entry, "");
  sprintf(placeholder_text, "%.2f", count_rotate_x(0));
  gtk_entry_set_placeholder_text(entry, placeholder_text);
}

void print_rotate_y_placeholder(GtkEntry *entry) {
  char placeholder_text[10];

  gtk_entry_set_alignment(GTK_ENTRY(entry), 0.5);

  gtk_entry_set_text(entry, "");
  sprintf(placeholder_text, "%.2f", count_rotate_y(0));
  gtk_entry_set_placeholder_text(entry, placeholder_text);
}

void print_rotate_z_placeholder(GtkEntry *entry) {
  char placeholder_text[10];

  gtk_entry_set_alignment(GTK_ENTRY(entry), 0.5);

  gtk_entry_set_text(entry, "");
  sprintf(placeholder_text, "%.2f", count_rotate_z(0));
  gtk_entry_set_placeholder_text(entry, placeholder_text);
}

//**************************************************************************//

//*******************SCALE BOX**********************************************//

GtkWidget *create_scale_entry(GtkWidget **scale_entry) {
  GtkWidget *horizontal = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
  GtkWidget *plus_button = gtk_button_new();
  GtkWidget *minus_button = gtk_button_new();
  *scale_entry = gtk_entry_new();
  gtk_entry_set_input_purpose(GTK_ENTRY(*scale_entry),
                              GTK_INPUT_PURPOSE_NUMBER);
  create_horizontal_scale_box(horizontal, plus_button, *scale_entry,
                              minus_button);

  GtkWidget *vertical = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
  GtkWidget *scale_label = gtk_label_new("Масштаб:");
  GtkWidget *ok_button = gtk_button_new_with_label("OK");
  create_vertical_scale_box(vertical, scale_label, horizontal);

  create_ok_button(vertical, ok_button);
  work_scale_button(scale_entry, ok_button, plus_button, minus_button);

  return vertical;
}

void create_vertical_scale_box(GtkWidget *vertical, GtkWidget *scale_label,
                               GtkWidget *horizontal) {
  gtk_box_pack_start(GTK_BOX(vertical), scale_label, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(vertical), horizontal, FALSE, FALSE, 0);
}

void create_horizontal_scale_box(GtkWidget *horizontal, GtkWidget *plus_button,
                                 GtkWidget *scale_entry,
                                 GtkWidget *minus_button) {
  GtkWidget *plus_label = gtk_label_new("+");
  gtk_container_add(GTK_CONTAINER(plus_button), plus_label);

  GtkWidget *minus_label = gtk_label_new("-");
  gtk_container_add(GTK_CONTAINER(minus_button), minus_label);

  gtk_box_pack_start(GTK_BOX(horizontal), plus_button, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(horizontal), scale_entry, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(horizontal), minus_button, FALSE, FALSE, 0);

  print_scale_placeholder(GTK_ENTRY(scale_entry));
}

void create_ok_button(GtkWidget *box, GtkWidget *ok_button) {
  GtkWidget *button_box = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
  gtk_box_pack_start(GTK_BOX(box), button_box, FALSE, FALSE, 0);
  gtk_widget_set_size_request(ok_button, 115, 15);
  gtk_container_add(GTK_CONTAINER(button_box), ok_button);
}

void print_scale_placeholder(GtkEntry *scale_entry) {
  char placeholder_text[10];

  gtk_entry_set_alignment(GTK_ENTRY(scale_entry), 0.5);

  gtk_entry_set_text(scale_entry, "");
  sprintf(placeholder_text, "%d%%", count_scale(0));
  gtk_entry_set_placeholder_text(scale_entry, placeholder_text);
}

void show_notification(const gchar *message) {
  GtkWidget *dialog = gtk_message_dialog_new(
      NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "%s", message);
  gtk_window_set_title(GTK_WINDOW(dialog), "Уведомление");

  g_signal_connect(dialog, "response", G_CALLBACK(gtk_widget_destroy), NULL);

  gtk_widget_show_all(dialog);
}