#include "screencast.h"

void start_record(char *filename) {
  int error = 0;
  GifFileType *gif = EGifOpenFileName(filename, false, &error);
  if (gif) {
    EGifSetGifVersion(gif, true);
    GtkWidget *model_area = *get_model_area();
    int width = gtk_widget_get_allocated_width(model_area);
    int height = gtk_widget_get_allocated_height(model_area);

    ColorMapObject *color_map = get_color_map();
    EGifPutScreenDesc(gif, width, height, 8, 0, color_map);
    static UserData1 data = {0};
    data.gif = gif;
    data.error = &error;
    data.frame_count = 0;

    g_timeout_add(FRAME_DELAY, record_screencast_loop, &data);
  }
}
gboolean record_screencast_loop(gpointer user_data) {
  UserData1 *data = (UserData1 *)user_data;
  GtkWidget *model_area = *get_model_area();

  GdkPixbuf *frame = get_screenshot(model_area);
  record_frame(data->gif, frame);
  g_object_unref(frame);

  data->frame_count++;
  if (data->frame_count >= DURATION / FRAME_DELAY) {
    if (data->gif) {
      EGifCloseFile(data->gif, data->error);
      show_notification("Запись завершена");
    }
    return G_SOURCE_REMOVE;
  }
  return G_SOURCE_CONTINUE;
}

void initialize_color_buffers(GdkPixbuf *frame, GifByteType **red,
                              GifByteType **green, GifByteType **blue) {
  int width = gdk_pixbuf_get_width(frame);
  int height = gdk_pixbuf_get_height(frame);
  int channels = gdk_pixbuf_get_n_channels(frame);
  int rowstride = gdk_pixbuf_get_rowstride(frame);
  guchar *pixels = gdk_pixbuf_get_pixels(frame);

  *red = malloc(width * height);
  *green = malloc(width * height);
  *blue = malloc(width * height);

  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      int pixel_offset = y * rowstride + x * channels;
      int buffer_offset = y * width + x;
      (*red)[buffer_offset] = pixels[pixel_offset];
      (*green)[buffer_offset] = pixels[pixel_offset + 1];
      (*blue)[buffer_offset] = pixels[pixel_offset + 2];
    }
  }
}

void record_frame(GifFileType *gif, GdkPixbuf *frame) {
  int width = gdk_pixbuf_get_width(frame);
  int height = gdk_pixbuf_get_height(frame);

  GifByteType *red, *green, *blue;
  initialize_color_buffers(frame, &red, &green, &blue);

  GifByteType *output_buffer = malloc(width * height);
  ColorMapObject *color_map = GifMakeMapObject(256, NULL);

  if (output_buffer && color_map) {
    int color_map_size = 256;
    GifQuantizeBuffer(width, height, &color_map_size, red, green, blue,
                      output_buffer, color_map->Colors);

    EGifPutImageDesc(gif, 0, 0, width, height, FALSE, color_map);
    EGifPutLine(gif, output_buffer, width * height);

    free(output_buffer);
    GifFreeMapObject(color_map);
  }

  free(red);
  free(green);
  free(blue);
}

//-----------------------------------------------------------------------
// Egor's part

void save_image(GtkWidget *widget, char *filename, char *format) {
  GdkPixbuf *screen = get_screenshot(widget);
  gdk_pixbuf_save(screen, filename, format, NULL, NULL);
  g_object_unref(screen);
}

void save_file_dialog() {
  GtkWidget *dialog, *entry, *combo;
  GtkFileChooser *chooser;
  GtkFileFilter *filter;
  gint res;
  GtkWidget **widget = get_model_area();

  dialog = gtk_file_chooser_dialog_new(
      "Сохранение", NULL, GTK_FILE_CHOOSER_ACTION_SAVE, "Отмена",
      GTK_RESPONSE_CANCEL, "Сохранить", GTK_RESPONSE_ACCEPT, NULL);

  chooser = GTK_FILE_CHOOSER(dialog);

  filter = gtk_file_filter_new();
  gtk_file_filter_set_name(filter, "JPEG Files");
  gtk_file_filter_add_mime_type(filter, "inode/directory");
  gtk_file_chooser_add_filter(chooser, filter);

  entry = gtk_entry_new();
  gtk_file_chooser_set_current_name(chooser, "untitled");
  gtk_file_chooser_set_do_overwrite_confirmation(chooser, TRUE);

  combo = gtk_combo_box_text_new();
  gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo), "BMP");
  gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo), "JPEG");
  gtk_combo_box_set_active(GTK_COMBO_BOX(combo), 0);

  gtk_file_chooser_set_extra_widget(chooser, entry);
  gtk_file_chooser_set_extra_widget(chooser, combo);

  res = gtk_dialog_run(GTK_DIALOG(dialog));
  if (res == GTK_RESPONSE_ACCEPT) {
    char *filename = NULL;
    char *format = NULL;
    gchar *basename = NULL;
    char *pos = NULL;

    filename = gtk_file_chooser_get_filename(chooser);
    format = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(combo));
    basename = g_strdup(filename);

    // Формируем полный путь с правильным расширением
    if (g_strcmp0(format, "BMP") == 0) {
      pos = g_strrstr(filename, ".bmp");
      if (pos) basename = g_strndup(filename, pos - filename - 1);
      save_image(*widget, basename, "bmp");
    } else {
      pos = g_strrstr(filename, ".jpeg");
      if (pos) basename = g_strndup(filename, pos - filename - 1);
      save_image(*widget, basename, "jpeg");
    }

    if (filename) g_free(filename);
    if (basename) g_free(basename);
    if (format) g_free(format);
  }

  gtk_widget_destroy(dialog);
}

GdkPixbuf *get_screenshot(GtkWidget *widget) {
  GtkStyleContext *context = gtk_widget_get_style_context(widget);
  cairo_surface_t *surface;
  GdkPixbuf *screenshot;

  int width = gtk_widget_get_allocated_width(widget);
  int height = gtk_widget_get_allocated_height(widget);

  surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
  cairo_t *cr = cairo_create(surface);

  gtk_render_background(context, cr, 0, 0, width, height);
  gtk_widget_draw(widget, cr);

  cairo_surface_flush(surface);
  screenshot = gdk_pixbuf_get_from_surface(surface, 0, 0, width, height);

  cairo_destroy(cr);
  cairo_surface_destroy(surface);

  return screenshot;
}
