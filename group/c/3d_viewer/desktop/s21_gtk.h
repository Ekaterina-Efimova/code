#ifndef S21_GTK_H
#define S21_GTK_H
// #include <gdk/gdk.h>  // вроде не нужно
#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>

#include "../gtk/screencast.h"
#include "../gtk/s21_gtk_draw.h"

#define SPASE_1 2
#define SPASE_2 0
#define HIGHT 250
#define WIGHT 20

// структура информации о модели
typedef struct {
  char **filename;
  int num_vertices;
  int num_edges;
  float trans_x, trans_y, trans_z;
  float rotate_x, rotate_y, rotate_z;
  int scale;
} ModelInfo;

// структура информации о настройки
typedef struct {
  int projection_type;
  int edges_type;
  char *edge_color;
  int edge_thickness;
  char *background_color;
  int vetrtex_type_print;
  char *vertex_color;
  int vertex_size;
} SettingInfo;

// перечисление для типа проекции
typedef enum { PARALLEL, CENTER } ProjectionType;

// перечисление для типа отрисовки ребер
typedef enum { SOLID_EDGE, DASHED_EDGE } EdgeType;

// перечисление для цвета
typedef enum { WHITE, BLACK, RED, GREEN, BLUE, YELLOW } COLOR;

// перечисление для толщины ребер
typedef enum { THIN, MEDIUM, THICK } EdgeThickness;

// перечисление для типа отрисовки вершин
typedef enum { ZERO, CERCLE, SQUARE } VertexType;

// перечисление для типа отрисовки вершин
typedef enum { ONE, TWO, THREE } VertexSize;

// вспомогательная структура 1
typedef struct {
  GifFileType *gif;
  int *error;
  guint frame_count;
} UserData1;

// вспомогательная структура 2
typedef struct {
  GtkEntry *x, *y, *z;
  GtkWidget *label;
  ModelInfo *info;
} UserData2;

// вспомогательная структура 3
typedef struct {
  GtkEntry *entry;
  GtkWidget *label;
  ModelInfo *info;
} UserData3;

//**************************************************************************//
void run_3d_viewer(int argc, char *argv[]);
//****************MAIN WINDOW***********************************************//
// Функция для создания главного окна
GtkWidget *create_main_window();

// Функция для создания главной горизонтали
void create_main_main_box(GtkWidget *two_verticals, GtkWidget *vertical_right,
                          GtkWidget *vertical_left);

// Функция для создания главной левой вертикали
void create_main_vertical_left(GtkWidget *vertical_left, char **filename);

// Функция для создания главной правой вертикали
void create_main_vertical_right(GtkWidget *vertical_right);
//**************************************************************************//

//********************SETTINGS BOX******************************************//

// Функция для создания малой левой вертикали
void create_setting_box(GtkWidget *settings_box);

// Функция распределения работы кнопок настройки
void work_setting_buttons(GtkWidget *background_color_button,
                          GtkWidget *thin_button, GtkWidget *medium_button,
                          GtkWidget *thick_button, GtkWidget *save_image_button,
                          GtkWidget *record_screencast_button);

// Функция для создания кнопки записи gif
GtkWidget *create_save_gif_dialog();

//_______________EDGE SETTING DIALOG_________________________________________//

// создает меню настроек ребер=
void create_edges_setting_box(GtkWidget **box, GtkWidget **thin_button,
                              GtkWidget **medium_button,
                              GtkWidget **thick_button);

// создает кнопки толщины
void create_thickness_box(GtkWidget *box, GtkWidget **thin_button,
                          GtkWidget **medium_button, GtkWidget **thick_button);

//_______________WORKS SETTING BUTTONS______________________________________//

void on_thin_button_cliced(GtkWidget *widget __attribute__((unused)),
                           gpointer data __attribute__((unused)));

void on_medium_button_cliced(GtkWidget *widget __attribute__((unused)),
                             gpointer data __attribute__((unused)));

void on_thick_button_cliced(GtkWidget *widget __attribute__((unused)),
                            gpointer data __attribute__((unused)));

void show_background_color_dialog(GtkWidget *widget __attribute__((unused)),
                                  gpointer data __attribute__((unused)));

void show_save_image_dialog(GtkWidget *widget __attribute__((unused)),
                            gpointer data __attribute__((unused)));

void record_screencast(GtkWidget *widget __attribute__((unused)),
                       gpointer data __attribute__((unused)));

//**************************************************************************//

//****************3D PRINT BOX********************************************//

// Функция для создания области визуализации модели
void create_model_area(GtkWidget **model_area);
//**************************************************************************//

//*******************OPEN FILE BOX*******************************************//

// Функция для создания поля ввода названия файла
GtkWidget *create_filename_entry(char **filename);

// Функция создания placeholder для  filename
void print_entry_file_placeholder(char **filename);

// Функция поиска файла через менеджер файлов и обработка нажатия кнопки поиска
void on_open_button_clicked(GtkWidget *a __attribute__((unused)),
                            gpointer user_data);

// Функция для считывания самостоятельного ввода пути к файлу
void on_file_ok_activate(GtkWidget *a __attribute__((unused)),
                         gpointer user_data);
//**************************************************************************//

//****************MODEL INFO BOX********************************************//

// Функция для обновления информации о модели
void update_model_info();
//**************************************************************************//

//*****************TRANSFORM BOX*******************************************//

// Функция для создания кнопки переремещения и кнопки поворота
GtkWidget *create_transform_entries(GtkWidget *trans_x, GtkWidget *trans_y,
                                    GtkWidget *trans_z, GtkWidget *rotate_x,
                                    GtkWidget *rotate_y, GtkWidget *rotate_z);
// Функция создания вертикальноориентированных окон в
// transform_box
void create_vertical_transform_box(GtkWidget *main_box, GtkWidget *label1,
                                   GtkWidget *box1, GtkWidget *label2,
                                   GtkWidget *box2, GtkWidget *label3,
                                   GtkWidget *box3);

//_______________TRANSLATE BOX____________________________________________//

// Функция для создания поля ввода перемещения
void create_translate_xyz_entries(GtkWidget *box, GtkWidget *x, GtkWidget *y,
                                  GtkWidget *z);

// функция создания кнопки перемещения
void create_translate_button(GtkWidget *transform_box, gpointer data);

// Функция для создания стрелок поворота
void create_label_translate_button(GtkWidget *arrow_rotate_left,
                                   GtkWidget *arrow_rotate_right,
                                   GtkWidget *arrow_rotate_up,
                                   GtkWidget *arrow_rotate_down,
                                   GtkWidget *arrow_rotate_diagonal_up,
                                   GtkWidget *arrow_rotate_diagonal_down);

// Функция создания placeholder для translate_x
void print_translate_x_placeholder(GtkEntry *entry);

// Функция создания placeholder для translate_y
void print_translate_y_placeholder(GtkEntry *entry);

// Функция создания placeholder для translate_z
void print_translate_z_placeholder(GtkEntry *entry);

// Функция распределения работы кнопок перемщения
void work_button_translate(gpointer info, GtkWidget *arrow_rotate_left,
                           GtkWidget *arrow_rotate_right,
                           GtkWidget *arrow_rotate_up,
                           GtkWidget *arrow_rotate_down,
                           GtkWidget *arrow_rotate_diagonal_up,
                           GtkWidget *arrow_rotate_diagonal_down);

// Функция увеличения перемещения по x
void arrow_translate_left_clicked(GtkWidget *a __attribute__((unused)),
                                  gpointer info);

// Функция уменьшения перемещения по x
void arrow_translate_right_clicked(GtkWidget *a __attribute__((unused)),
                                   gpointer info);

// Функция увеличения перемещения по y
void arrow_translate_up_clicked(GtkWidget *a __attribute__((unused)),
                                gpointer info);

// Функция уменьшения перемещения по y
void arrow_translate_down_clicked(GtkWidget *a __attribute__((unused)),
                                  gpointer info);

// Функция увеличения перемещения по z
void arrow_translate_diagonal_up_clicked(GtkWidget *a __attribute__((unused)),
                                         gpointer info);

// Функция уменьшения перемещения по z
void arrow_translate_diagonal_down_clicked(GtkWidget *a __attribute__((unused)),
                                           gpointer info);

// Функция для записи данных о перемещение в структуру
void translate_button_clicked(GtkWidget *a __attribute__((unused)),
                              gpointer user_data);

//_______________ROTATE BOX______________________________________________//

// Функция для создания поля ввода поворота
void create_rotate_xyz_entries(GtkWidget *box, GtkWidget *x, GtkWidget *y,
                               GtkWidget *z);

// функция создания кнопки поворота
void create_rotate_button(GtkWidget *transform_box, gpointer data);

// Функция для создания стрелок поворота
void create_label_rotate_button(GtkWidget *arrow_rotate_left,
                                GtkWidget *arrow_rotate_right,
                                GtkWidget *arrow_rotate_up,
                                GtkWidget *arrow_rotate_down,
                                GtkWidget *arrow_rotate_diagonal_up,
                                GtkWidget *arrow_rotate_diagonal_down);

// Функция создания placeholder для rotate_x
void print_rotate_x_placeholder(GtkEntry *entry);

// Функция создания placeholder для rotate_y
void print_rotate_y_placeholder(GtkEntry *entry);

// Функция создания placeholder для rotate_z
void print_rotate_z_placeholder(GtkEntry *entry);

// Функция распределения работы кнопок поворота
void work_button_rotate(gpointer info, GtkWidget *arrow_rotate_left,
                        GtkWidget *arrow_rotate_right,
                        GtkWidget *arrow_rotate_up,
                        GtkWidget *arrow_rotate_down,
                        GtkWidget *arrow_rotate_diagonal_up,
                        GtkWidget *arrow_rotate_diagonal_down);

// Функция увеличения поворота по x
void arrow_rotate_left_clicked(GtkWidget *a __attribute__((unused)),
                               gpointer info);

// Функция уменьшения поворота по x
void arrow_rotate_right_clicked(GtkWidget *a __attribute__((unused)),
                                gpointer info);

// Функция увеличения поворота по y
void arrow_rotate_up_clicked(GtkWidget *a __attribute__((unused)),
                             gpointer info);

// Функция уменьшения поворота по y
void arrow_rotate_down_clicked(GtkWidget *a __attribute__((unused)),
                               gpointer info);

// Функция увеличения поворота по z
void arrow_rotate_diagonal_up_clicked(GtkWidget *a __attribute__((unused)),
                                      gpointer info);

// Функция уменьшения поворота по z
void arrow_rotate_diagonal_down_clicked(GtkWidget *a __attribute__((unused)),
                                        gpointer info);

// Функция для записи данных о повороте в структуру
void rotate_button_clicked(GtkWidget *a __attribute__((unused)),
                           gpointer user_data);

//**************************************************************************//

//*******************SCALE BOX**********************************************//

// Функция для создания поля ввода масштабирования
// модели
GtkWidget *create_scale_entry(GtkWidget **scale_entry);

// Функция создания вертикальноориентированных окон в
// scale_box
void create_vertical_scale_box(GtkWidget *vertical, GtkWidget *scale_label,
                               GtkWidget *horizontal);

// Функция создания горизонтальноориентированных окон в
// scale_box
void create_horizontal_scale_box(GtkWidget *horizontal, GtkWidget *plus_button,
                                 GtkWidget *scale_entry,
                                 GtkWidget *minus_button);
// Функция создания кнопки ОК
void create_ok_button(GtkWidget *box, GtkWidget *ok_button);

// Функция распределения работы кнопок масштаба
void work_scale_button(GtkWidget **scale_entry, GtkWidget *ok_button,
                       GtkWidget *plus_button, GtkWidget *minus_button);

// Функция создания placeholder для scale
void print_scale_placeholder(GtkEntry *scale_entry);

// Функция записи масштаба
void on_scale_ok_activate(GtkWidget *a __attribute__((unused)),
                          gpointer user_data);

// Функция увеличения масштаба
void on_scale_plus_clicked(GtkWidget *a __attribute__((unused)),
                           gpointer user_data);

// Функция уменьшения масштаба
void on_scale_minus_clicked(GtkWidget *a __attribute__((unused)),
                            gpointer user_data);

//**************************************************************************//

//*****************HELPERS***************************************************//

// Фуекция расположения box
void line_in_box(GtkWidget *box, GtkWidget *widget1, GtkWidget *widget2,
                 GtkWidget *widget3);

// Функция создаия box
void create_box(GtkWidget *box, GtkWidget *button1, GtkWidget *button2,
                GtkWidget *button3, char *str, int a, int b, int c);

// Функция для передачи указателя на Label
GtkWidget **label_1();

// Функция для передачи указателя на filename_entry
GtkWidget **filename_entry();

// Функция для передачи указателя на model_area
GtkWidget **get_model_area();

// функция для передачи структуры ModelInfo
ModelInfo *modelinfo();

// функция для передачи структуры SettingInfo
SettingInfo *settinginfo();

// Функция инициализации SettingInfo
void init_setting_info(SettingInfo *info);

// функция подсчета масштаба
int count_scale(int a);

// функция подсчета поворот по x
double count_rotate_x(double a);

// функция подсчета поворот по y
double count_rotate_y(double a);

// функция подсчета поворот по z
double count_rotate_z(double a);

// функция подсчета перемещение по x
double count_trans_x(double a);

// функция подсчета перемещение по y
double count_trans_y(double a);

// функция подсчета перемещение по z
double count_trans_z(double a);

// Функция для получения имени файла
char *get_filename(const char *path);

// Инициализация UserData2
gpointer init_user_data2(UserData2 *data, GtkWidget *x, GtkWidget *y,
                         GtkWidget *z);

// Инициализация UserData3
gpointer init_user_data3(UserData3 *data, GtkEntry *entry);

// Инициализация RGBA
GdkRGBA init_rgba(double r, double g, double b, double a);

// Функция получения карты цвета
ColorMapObject *get_color_map();

GifFileType **get_gif_fle();

// Функция для записи настроек в файл
void save_settings();

// Функция показыввания уведомление
void show_notification(const gchar *message);
// обратная конвертация цвета
GdkRGBA get_gtk_color();
// зануление ModelInfo
void zero_model_info();
#endif