#ifndef __SCREENCAST_H__
#define __SCREENCAST_H__
#include <cairo.h>
#include <gif_lib.h>
#include "../desktop/s21_gtk.h"

#define FRAME_DELAY 100  // Задержка между кадрами в миллисекундах (10 кадров/с)
#define DURATION 5000  // Продолжительность записи в миллисекундах (5 секунд)

// Запускает запись
void start_record(char *filename);

// Запускает цикл записи
gboolean record_screencast_loop(gpointer user_data);

// Записывает кадр в файл
void record_frame(GifFileType *writer, GdkPixbuf *frame);

//инициализация цветовых буферов
void initialize_color_buffers(GdkPixbuf *frame, GifByteType **red, GifByteType **green, GifByteType **blue);

// Делает скрин экрана
GdkPixbuf *get_screenshot(GtkWidget *widget); 

// Диалог на сохранение
void save_file_dialog();

// Сохранение изображения
void save_image(GtkWidget *widget, char *filename, char *format);

#endif