#include "s21_gtk_draw.h"

int main_window(GtkWidget *gl_area) {
  g_signal_connect(gl_area, "realize", G_CALLBACK(on_realize), NULL);
  g_signal_connect(gl_area, "render", G_CALLBACK(on_render), NULL);

  g_timeout_add(16, on_timeout, gl_area);
  return 0;
}

void setup_Shaders() {
  const char *vertex_shader_src =
      "#version 420 core\n"
      "layout(location = 0) in vec3 pos;\n"
      "void main() {\n"
      "   gl_Position = vec4(pos, 1.0);\n"
      "}\n";

  const char *fragment_shader_src =
      "#version 420 core\n"
      "out vec4 ColorEdges;\n"
      "void main() {\n"
      "   ColorEdges = vec4(0.4, 1.0, 0.4, 1.0);\n"
      "}\n";

  GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex_shader, 1, &vertex_shader_src, NULL);
  glCompileShader(vertex_shader);
  check_shader_compile(vertex_shader, "VERTEX");

  GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment_shader, 1, &fragment_shader_src, NULL);
  glCompileShader(fragment_shader);
  check_shader_compile(fragment_shader, "FRAGMENT");

  GLuint *shader_program = get_shader();
  *shader_program = glCreateProgram();
  glAttachShader(*shader_program, vertex_shader);
  glAttachShader(*shader_program, fragment_shader);
  glLinkProgram(*shader_program);
  check_program_link(*shader_program);

  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);
}

void on_realize(GtkGLArea *area) {
  gtk_gl_area_make_current(GTK_GL_AREA(area));
  GdkRGBA color = get_gtk_color();
  glClearColor(color.red, color.green, color.blue, 1.0f);
  setup_Shaders();
}

int on_render(GtkGLArea *area, GdkGLContext *context) {
  // printf("1\n");
  glClear(GL_COLOR_BUFFER_BIT);
  GdkRGBA color = get_gtk_color();
  glClearColor(color.red, color.green, color.blue, 1.0f);

  SettingInfo *settings = settinginfo();
  Parametrs *param = get_param();

  float points[param->count_points * 3];
  normalize(points);
  // printf("%d poits ", param->count_points);
  // for (int i = 0; i < param->count_points * 3; i += 3) {
  //   printf("%.2f %.2f %.2f ", points[i], points[i + 1], points[i + 2]);
  // }
  // printf("\n%d edges ", param->count_edges);
  // for (int i = 0; i < param->count_edges * 2; i += 2) {
  //   printf("%d %d ", param->edges[i], param->edges[i + 1]);
  // }
  // printf("\n");

  GLuint VBO, VAO, EdgeEBO;
  GLuint *ShaderProgramEdges = get_shader();
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EdgeEBO);
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, param->count_points * 3 * sizeof(float), points,
               GL_STATIC_DRAW);
  // glBufferData(GL_ARRAY_BUFFER, param->count_points * 3 * sizeof(float),
  //              param->points, GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EdgeEBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, param->count_edges * 2 * sizeof(int),
               param->edges, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  glUseProgram(*ShaderProgramEdges);
  glLineWidth(settings->edge_thickness);  // только на старых версиях OpenGL
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glDrawElements(GL_LINES, param->count_edges * 2 * sizeof(int),
                 GL_UNSIGNED_INT, 0);
  // printf("2\n");

  return 1;
}

gboolean on_timeout(gpointer data) {
  GtkWidget *gl_area = GTK_WIDGET(data);
  gtk_gl_area_queue_render(GTK_GL_AREA(gl_area));

  return TRUE;
}

void normalize(float *points) {
  Parametrs *model = get_param();
  ModelInfo *info = modelinfo();

  float x_center = (model->min_max_x[1] + model->min_max_x[0]) / 2;
  float y_center = (model->min_max_y[1] + model->min_max_y[0]) / 2;
  float z_center = (model->min_max_z[1] + model->min_max_z[0]) / 2;
  // float x_center = 0;
  // float y_center = 0;
  // float z_center = 0;

  // float normalize = (float)(info->scale == 0 ? 100 : info->scale);
  float normalize = (float)(info->scale == 0 ? 100 : info->scale) / 1.1;
  float x_scale = (model->min_max_x[1] - model->min_max_x[0]) / 2;
  float y_scale = (model->min_max_y[1] - model->min_max_y[0]) / 2;
  float z_scale = (model->min_max_z[1] - model->min_max_z[0]) / 2;
  // float x_scale = 1;
  // float y_scale = 1;
  // float z_scale = 1;
  if (x_scale == 0) x_scale = 999;
  if (y_scale == 0) y_scale = 999;
  if (z_scale == 0) z_scale = 999;
  if (x_scale > y_scale && x_scale > z_scale) normalize /= x_scale;
  if (y_scale > x_scale && y_scale > z_scale) normalize /= y_scale;
  if (z_scale > x_scale && z_scale > y_scale) normalize /= z_scale;

  int n = model->count_points * 3;
  for (int i = 0; i < n; i += 3) {
    Point point = {model->points[i], model->points[i + 1],
                   model->points[i + 2]};
    point = move(point, info->trans_x - x_center, info->trans_y - y_center,
                 info->trans_z - z_center);
    point = rotate(point, info->rotate_x, info->rotate_y, info->rotate_z);
    point = scale(point, normalize);

    points[i] = point.x;
    points[i + 1] = point.y;
    points[i + 2] = point.z;
  }
}

GLuint *get_shader() {
  static GLuint ShaderProgramEdges;

  return &ShaderProgramEdges;
}

void check_shader_compile(GLuint shader, const char *shader_type) {
  GLint success;
  GLchar infoLog[512];

  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(shader, sizeof(infoLog), NULL, infoLog);
    fprintf(stderr, "ERROR::SHADER::%s::COMPILATION_FAILED\n%s\n", shader_type,
            infoLog);
    exit(EXIT_FAILURE);
  }
}

void check_program_link(GLuint program) {
  GLint success;
  GLchar infoLog[512];

  glGetProgramiv(program, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(program, sizeof(infoLog), NULL, infoLog);
    fprintf(stderr, "ERROR::PROGRAM::LINKING_FAILED\n%s\n", infoLog);
    exit(EXIT_FAILURE);
  }
}