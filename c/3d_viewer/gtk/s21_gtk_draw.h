#ifndef S21_GTK_DRAW_H
#define S21_GTK_DRAW_H

#include <epoxy/gl.h>
#include <epoxy/glx.h>
#include <gtk/gtk.h>

#include "../desktop/s21_gtk.h"
#include "s21_matrix.h"
#include "s21_parce.h"

int main_window(GtkWidget *gl_area);
void on_realize(GtkGLArea *area);
int on_render(GtkGLArea *area, GdkGLContext *context);
void setup_Shaders();
gboolean on_timeout(gpointer data);
GLuint *get_shader();
void check_shader_compile(GLuint, const char *);
void check_program_link(GLuint program);
void normalize(float *points);

#endif