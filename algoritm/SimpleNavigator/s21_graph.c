#include "common.h"

int load_matrix_a_from_file(Graph* result, FILE* file);

/**
 * Загрузка графа из файла в формате матрицы смежности
 * @param filename имя файла
 * @param result указатель на результирующую матрицу смежности
 * @return EXIT_SUCCESS 0, EXIT_FAILURE 1
 */
int load_graph_from_file(char* filename, Graph* result) {
  int error = EXIT_SUCCESS;
  FILE* file = NULL;
  if ((file = fopen(filename, "rt")) != NULL) {
    if (fscanf(file, "%d", &result->size) == 1 && result->size > 0) {
      error = load_matrix_a_from_file(result, file);
    } else {
      error = EXIT_FAILURE;
    }
    fclose(file);
  } else {
    printf("%s\n", strerror(errno));
    error = EXIT_FAILURE;
  }
  return error;
}

/**
 * Дополнительная функция считывания матрицы смежности из файла
 * @param result указатель на структуру матрицы
 * @param file указатель на открытый файл
 * @return EXIT_SUCCESS 0, EXIT_FAILURE 1
 */
int load_matrix_a_from_file(Graph* result, FILE* file) {
  int error = EXIT_SUCCESS;
  if ((result->matrix = calloc(
           result->size, result->size * sizeof(int) + sizeof(int*))) != NULL) {
    result->matrix[0] = (int*)(result->matrix + result->size);
    for (int i = 1; i < result->size; i++) {
      result->matrix[i] = result->matrix[0] + (i * result->size);
    }
    for (int i = 0; i < result->size && error == EXIT_SUCCESS; i++) {
      for (int j = 0; j < result->size && error == EXIT_SUCCESS; j++) {
        if (!(fscanf(file, "%d", &result->matrix[i][j]) == 1 &&
              result->matrix[i][j] >= 0)) {
          error = EXIT_FAILURE;
        }
      }
    }
    char c;
    if (fscanf(file, "%c", &c) == 1) {
      error = EXIT_FAILURE;
    }
    if (error == EXIT_FAILURE) {
      free(result->matrix);
      result->matrix = NULL;
    }
  } else {
    printf("%s\n", strerror(errno));
    error = EXIT_FAILURE;
  }
  return error;
}

void print_vertex_name(FILE* file, int i) {
  fprintf(file, "%c", i % 26 + 'a');
  if (i / 26 > 0) {
    fprintf(file, "%d", i / 26);
  }
}

/**
 * Выгрузка графа в файл в формате dot
 * @param filename имя экспортируемого файла
 * @param graph указатель на граф
 * @return EXIT_SUCCESS 0, EXIT_FAILURE 1
 */
int export_graph_to_dot(char* filename, Graph* graph) {
  int error = EXIT_SUCCESS;
  if (graph && graph->matrix && graph->size > 0) {
    FILE* file = NULL;
    if ((file = fopen(filename, "wt")) != NULL) {
      bool digraph = false;
      for (int i = 0; i < graph->size; i++) {
        for (int j = i; j < graph->size; j++) {
          if (graph->matrix[i][j] != graph->matrix[j][i]) {
            digraph = true;
          }
        }
      }
      fprintf(file, "%s%s", digraph ? "di" : "", "graph graphname {\n");
      for (int i = 0; i < graph->size; i++) {
        fprintf(file, "    ");
        print_vertex_name(file, i);
        fprintf(file, ";\n");
      }
      for (int i = 0; i < graph->size; i++) {
        for (int j = digraph ? 0 : i; j < graph->size; j++) {
          if (graph->matrix[i][j]) {
            fprintf(file, "    ");
            print_vertex_name(file, i);
            fprintf(file, " %s ", digraph ? "->" : "--");
            print_vertex_name(file, j);
            fprintf(file, ";\n");
          }
        }
      }
      fprintf(file, "}");
      fclose(file);
    }
  } else {
    error = EXIT_FAILURE;
  }
  return error;
}

/**
 * Инициализация графа
 * @param size размер матрицы
 * @param result указатель на граф
 * @return EXIT_SUCCESS 0, EXIT_FAILURE 1
 */
int s21_create_graph(int size, Graph* result) {
  int status = EXIT_SUCCESS;
  if (size > 0 && result != NULL) {
    if ((result->matrix = (int**)calloc(
             1, size * sizeof(int*) + size * size * sizeof(int))) == NULL) {
      status = EXIT_FAILURE;
    } else {
      result->size = size;
      result->matrix[0] = (int*)(result->matrix + size);
      for (int i = 1; i < size; i++) {
        result->matrix[i] = result->matrix[0] + i * size;
      }
    }
  } else {
    status = EXIT_FAILURE;
  }
  return status;
}

/**
 * Удаление графа
 * @param graph указатель на граф
 */
void s21_remove_graph(Graph* graph) {
  if (graph != NULL) {
    if (graph->matrix != NULL) {
      free(graph->matrix);
      graph->matrix = NULL;
    }
    graph->size = 0;
  }
}