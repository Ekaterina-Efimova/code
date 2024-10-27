#include "s21_graph_algorithms.h"

void brute_force(Graph *graph, tsm_result *result, int *current_path,
                 int *visited, int current_dist, int depth, long long int t);
long long get_time();

void found_shortest_path_floid(int **result, int graph_size, int k);
void find_shortest_path_prim(Graph *graph, int *used, int i, int *min, int *x,
                             int *y);
void check_path(int path, int *min, int *x, int *y, int i, int j);

void init_matrix(int **matrix, int size, int a);
void copy_matrix(Graph *graph, int **matrix);

void dfs_algoritm(List *s, int *error, int *marked, int *result, int *count,
                  Graph *graph);
void bfs_algoritm(List *q, int *error, int *result, int *count, Graph *graph,
                  int *marked);
void ants_walk_and_pee(Graph *graph, const int n, double like[][n],
                       tsm_result *result);
void one_ant_walk(Graph *graph, const int n, double like[][n], int ant,
                  double tmp_like[][n], tsm_result *result);
double calc_step_prob(const double like, const int dist);
int get_next_step(const int n, double prob_sum, double abs_prob[]);
void check_min_path(tsm_result *result, const int n, int current_path[],
                    int current_dist);
void ant_pee(tsm_result *result, const int n, int current_path[],
             int current_dist, double tmp_like[][n]);

/**
 * Поиск кратчайшего пути между двумя вершинами в графе с использованием
 * алгоритма Дейкстры
 * @param graph Указатель на граф
 * @param vertex1 Начальная вершина
 * @param vertex2 Конечная вершина
 * @return Численный результат, равный наименьшему расстоянию между заданными
 * вершинами, если оно существует, иначе -1
 */
int get_shortest_path_between_vertices(Graph *graph, int vertex1, int vertex2) {
  if (!graph || graph->size <= 0 || vertex1 < 0 || vertex1 >= graph->size ||
      vertex2 < 0 || vertex2 >= graph->size) {
    return -1;
  }

  int distances[graph->size];
  int previous[graph->size];

  for (int i = 0; i < graph->size; i++) {
    distances[i] = INT_MAX;
    previous[i] = -1;
  }
  distances[vertex1] = 0;
  int min_distanse_i;
  int min;

  do {
    min_distanse_i = INT_MAX;
    min = INT_MAX;
    for (int i = 0; i < graph->size; i++) {
      if ((previous[i] == -1) && (distances[i] < min)) {
        min = distances[i];
        min_distanse_i = i;
      }
    }

    if (min_distanse_i != INT_MAX) {
      for (int j = 0; j < graph->size; j++) {
        if (graph->matrix[min_distanse_i][j] > 0) {
          int temp = min + graph->matrix[min_distanse_i][j];
          if (temp < distances[j]) {
            distances[j] = temp;
          }
        }
      }
      previous[min_distanse_i] = 0;
    }
  } while (min_distanse_i < INT_MAX);

  return distances[vertex2];
}

/**
 * Поиск кратчайших путей между всеми парами вершин в графе с использованием
 * алгоритма Флойда-Уоршелла
 * @param graph Указатель на граф
 * @param result Указатель на результирующую матрицу
 * @return EXIT_SUCCESS=0 или EXIT_FAILURE=1
 */
int get_shortest_paths_between_all_vertices(Graph *graph, int **result) {
  int error = EXIT_SUCCESS;

  if (!graph || graph->size < 1 || !result) {
    error = EXIT_FAILURE;

  } else {
    init_matrix(result, graph->size, INT_MAX);
    copy_matrix(graph, result);

    for (int k = 0; k < graph->size; k++)
      found_shortest_path_floid(result, graph->size, k);
  }
  return error;
}

/**
 * Поиск кратчайшего путей между всеми парами вершин в графе с использованием
 * алгоритма Флойда-Уоршелла через заданню вершину
 * @param result Указатель на результирующую матрицу
 * @param graph_size Размер матрицы
 * @param k Номер вершины
 */
void found_shortest_path_floid(int **result, int graph_size, int k) {
  for (int i = 0; i < graph_size; i++)
    for (int j = 0; j < graph_size; j++)
      if (result[i][k] != INT_MAX && result[k][j] != INT_MAX &&
          result[i][j] > result[i][k] + result[k][j])
        result[i][j] = result[i][k] + result[k][j];
}

/**
 * Нерекурентный поиск в глубину в графе от заданной вершины
 * @param graph Указатель на граф
 * @param start_vertex Начальная вершина
 * @param result Указатель на результирующий массив, который будет содержать в
 * себе обойдённые вершины в порядке их обхода. Размер массива должен быть не
 * менее количества вершин в графе
 * @return Количество элементов массива > 0; в случае ошибки - 0
 */
int depth_first_search(Graph *graph, int start_vertex, int *result) {
  int error = EXIT_SUCCESS;
  int count = 0;
  if (graph && graph->size > 0 && graph->size > start_vertex) {
    int marked[graph->size];
    for (int i = 0; i < graph->size; i++) {
      marked[i] = false;
    }
    List *s = NULL;
    if ((error = stack(&s)) == EXIT_SUCCESS) {
      if ((error = push(s, start_vertex)) == EXIT_SUCCESS) {
        while (s->tail && error == EXIT_SUCCESS) {
          dfs_algoritm(s, &error, marked, result, &count, graph);
        }
      }
      destroy(&s);
    }
  } else {
    error = EXIT_FAILURE;
  }
  return count * (1 - error);
}

/**
 * Вспомогательный алгоритм DFS
 * @param s
 * @param error
 * @param marked
 * @param result
 * @param count
 * @param graph
 */
void dfs_algoritm(List *s, int *error, int *marked, int *result, int *count,
                  Graph *graph) {
  int node = pop(s, error);
  if (*error == EXIT_SUCCESS) {
    if (!marked[node]) {
      marked[node] = true;
      result[*count] = node;
      (*count)++;
      for (int i = graph->size - 1; i >= 0; i--) {
        if (graph->matrix[node][i]) {
          *error = push(s, i);
        }
      }
    }
  }
}

/**
 * Поиск в ширину в графе от заданной вершины
 * @param graph Указатель на граф
 * @param start_vertex Начальная вершина
 * @param result Указатель на результирующий массив, который будет содержать в
 * себе обойдённые вершины в порядке их обхода. Размер массива должен быть не
 * менее количества вершин в графе
 * @return Количество элементов массива > 0; в случае ошибки - 0
 */
int breadth_first_search(Graph *graph, int start_vertex, int *result) {
  int error = EXIT_SUCCESS;
  int count = 0;
  if (graph && graph->size > 0 && graph->size > start_vertex) {
    int marked[graph->size];
    for (int i = 0; i < graph->size; i++) {
      marked[i] = false;
    }
    List *q = NULL;
    if ((error = queue(&q)) == EXIT_SUCCESS) {
      if ((error = push(q, start_vertex)) == EXIT_SUCCESS) {
        marked[start_vertex] = true;
        while (q->head && error == EXIT_SUCCESS) {
          bfs_algoritm(q, &error, result, &count, graph, marked);
        }
      }
      destroy(&q);
    }
  } else {
    error = EXIT_FAILURE;
  }
  return count * (1 - error);
}

/**
 * Вспомогательный алгоритм BFS
 * @param q
 * @param error
 * @param result
 * @param count
 * @param graph
 * @param marked
 */
void bfs_algoritm(List *q, int *error, int *result, int *count, Graph *graph,
                  int *marked) {
  int node = pop(q, error);
  if (*error == EXIT_SUCCESS) {
    result[*count] = node;
    (*count)++;
    for (int i = 0; i < graph->size; i++) {
      if (graph->matrix[node][i] && !marked[i]) {
        *error = push(q, i);
        marked[i] = true;
      }
    }
  }
}

/**
 * Поиск наименьшего остовного дерева в графе с помощью алгоритма Прима.
 * @param graph Указатель на граф
 * @param result Указатель на результирующую матрицу смежности для минимального
 * остовного дерева. Матрица должна быть определена и размер её должен быть
 * равен количеству вершин графа
 * @return EXIT_SUCCESS=0 или EXIT_FAILURE=1
 */
int get_least_spanning_tree(Graph *graph, int **result) {
  int error = EXIT_SUCCESS;

  if (!graph || graph->size < 1 || !result) {
    error = EXIT_FAILURE;

  } else {
    init_matrix(result, graph->size, -1);
    int used[graph->size];
    int count_edge = 0;
    int x, y;

    for (int i = 0; i < graph->size; i++) {
      used[i] = 0;
      result[i][i] = 0;
    }

    srand(time(NULL));
    int random = rand() % graph->size;
    used[random] = 1;

    while (count_edge < graph->size - 1) {
      int min = INT_MAX;
      x = 0;
      y = 0;

      for (int i = 0; i < graph->size; i++)
        find_shortest_path_prim(graph, used, i, &min, &x, &y);

      used[y] = 1;
      result[x][y] = min;
      result[y][x] = min;
      count_edge++;
    }
  }

  return error;
}

/**
 * Нахождение кратчайшего пути
 * @param graph Указатель на граф
 * @param used Указатель на массив использованных/неиспользованных вершин в
 * графе
 * @param i текущий индекс used
 * @param min текущий минимальный путь
 * @param x координата для резултирующей матрицы
 * @param y координата для резултирующей матрицы
 *
 */
void find_shortest_path_prim(Graph *graph, int *used, int i, int *min, int *x,
                             int *y) {
  if (used[i])
    for (int j = 0; j < graph->size; j++)
      if (!used[j] && graph->matrix[i][j])
        check_path(graph->matrix[i][j], min, x, y, i, j);
}

/**
 * Проверка и замена кратчайшего пути
 * @param  path вес от вершины до вершины
 * @param min текущий минимальный путь
 * @param x координата для резултирующей матрицы
 * @param y координата для резултирующей матрицы
 * @param i вершина 1
 * @param j вершина 2
 */
void check_path(int path, int *min, int *x, int *y, int i, int j) {
  if (*min > path) {
    *min = path;
    *x = i;
    *y = j;
  }
}

/**
 * Инициализация матрицы смежности заданным значением
 * @param matrix Указатель на результирующую квадратную матрицу
 * @param size Размер матрицы
 * @param a Значение для инициализации
 */
void init_matrix(int **matrix, int size, int a) {
  for (int i = 0; i < size; i++)
    for (int j = 0; j < size; j++) {
      matrix[i][j] = a;
    }
}

/**
 * Копирование матрицы из графа
 * @param graph Указатель на граф
 * @param matrix Указатель на матрицу
 */
void copy_matrix(Graph *graph, int **matrix) {
  for (int i = 0; i < graph->size; i++)
    for (int j = 0; j < graph->size; j++) {
      if (graph->matrix[i][j]) matrix[i][j] = graph->matrix[i][j];
      if (i == j) matrix[i][j] = 0;
    }
}

tsm_result solve_traveling_salesman_problem(Graph *graph) {
  srand(time(NULL));
  const int n = graph->size;

  tsm_result result;
  result.vertices = malloc(sizeof(int) * (n + 1));
  result.distance = INT_MAX;

  double like[n][n];
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      like[i][j] = (graph->matrix[i][j]) ? BASE_LIKE : 0;
    }
  }

  for (int i = 0; i < ITERATIONS; i++) {
    ants_walk_and_pee(graph, n, like, &result);
  }

  if (result.distance == INT_MAX) {
    printf("No solution\n");
  }

  return result;
}

void ants_walk_and_pee(Graph *graph, const int n, double like[][n],
                       tsm_result *result) {
  double tmp_like[n][n];
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      tmp_like[i][j] = 0;
    }
  }

  for (int ant = 0; ant < n; ant++) {
    one_ant_walk(graph, n, like, ant, tmp_like, result);
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (like[i][j]) {
        like[i][j] = like[i][j] * REMAINDER + tmp_like[i][j] + MIN_REMAIN;
      }
    }
  }
}

void one_ant_walk(Graph *graph, const int n, double like[][n], int ant,
                  double tmp_like[][n], tsm_result *result) {
  int error = 0, current_dist = 0, current_path[n + 1], visited[n];
  for (int i = 0; i < n; i++) {
    current_path[i] = -1;
    visited[i] = 0;
  }
  current_path[0] = ant;
  current_path[n] = -1;
  visited[ant] = 1;

  for (int ant_step = 1; ant_step < n && !error; ant_step++) {
    double abs_prob[n], prob_sum = 0;
    for (int i = 0; i < n; i++) abs_prob[i] = 0;
    int start = current_path[ant_step - 1];

    for (int next_step = 0; next_step < n; next_step++) {
      int dist = graph->matrix[start][next_step];
      if (dist && !visited[next_step]) {
        abs_prob[next_step] = calc_step_prob(like[start][next_step], dist);
        prob_sum += abs_prob[next_step];
      }
    }

    if (prob_sum != 0) {
      int next_step = get_next_step(n, prob_sum, abs_prob);

      current_path[ant_step] = next_step;
      visited[next_step] = 1;
      current_dist += graph->matrix[start][next_step];

    } else {
      error = 1;
    }
  }

  if (!error && graph->matrix[current_path[n - 1]][current_path[0]]) {
    current_dist += graph->matrix[current_path[n - 1]][current_path[0]];
    current_path[n] = current_path[0];

    check_min_path(result, n, current_path, current_dist);
    ant_pee(result, n, current_path, current_dist, tmp_like);
  }
}

double calc_step_prob(const double like, const int dist) {
  return pow(like, LIKE_POW) / pow(dist, DIST_POW);
}

int get_next_step(const int n, double prob_sum, double abs_prob[]) {
  double random = rand() / (double)RAND_MAX;

  double one_prob[n];
  for (int i = 0; i < n; i++) {
    one_prob[i] = abs_prob[i] / prob_sum + (i ? one_prob[i - 1] : 0);
  }

  int i = 0;
  while (random > one_prob[i]) i++;

  return i;
}

void check_min_path(tsm_result *result, const int n, int current_path[],
                    int current_dist) {
  if (current_dist < result->distance) {
    result->distance = current_dist;
    for (int i = 0; i <= n; i++) {
      result->vertices[i] = current_path[i];
    }
  }
}

void ant_pee(tsm_result *result, const int n, int current_path[],
             int current_dist, double tmp_like[][n]) {
  for (int i = 0; i < n; i++) {
    int start = current_path[i];
    int end = current_path[i + 1];
    tmp_like[start][end] += ADD * pow((result->distance / current_dist), 2);
  }
}

tsm_result kamen_close_points(Graph *graph) {
  const int n = graph->size;

  int visited[n];
  for (int i = 1; i < n; i++) visited[i] = 0;
  visited[0] = 1;

  tsm_result result;
  result.distance = 0;
  result.vertices = malloc(sizeof(int) * (n + 1));
  for (int i = 1; i < n + 1; i++) result.vertices[i] = -1;
  result.vertices[0] = 0;

  int error = 0;
  for (int i = 0; i < n - 1 && !error; i++) {
    int min = INT_MAX;
    int next_point = -1;

    for (int j = 0; j < n; j++) {
      int path = graph->matrix[i][j];
      if (!visited[j] && path > 0 && path < min) {
        min = path;
        next_point = j;
      }
    }

    if (next_point != -1) {
      visited[next_point] = 1;
      result.vertices[i + 1] = next_point;
      result.distance += min;
    } else {
      result.distance = -1;
      printf("Can't solve\n");
      error = 1;
    }
  }

  if (!error) {
    result.vertices[n] = result.vertices[0];
    result.distance += graph->matrix[n - 1][0];
  }

  return result;
}

tsm_result kamen_brute_force(Graph *graph) {
  const int n = graph->size;

  tsm_result result;
  result.distance = INT_MAX;
  result.vertices = malloc(sizeof(int) * (n + 1));

  int visited[n];
  for (int i = 0; i < n; i++) visited[i] = 0;
  visited[0] = 1;

  int current_path[n + 1];
  for (int i = 0; i < n + 1; i++) current_path[i] = -1;
  current_path[0] = 0;

  long long int t = get_time();
  brute_force(graph, &result, current_path, visited, 0, 1, t);

  if (result.distance == INT_MAX) {
    printf("No solution\n");
  }

  return result;
}

void brute_force(Graph *graph, tsm_result *result, int *current_path,
                 int *visited, int current_dist, int depth, long long int t) {
  if (get_time() - t > 10 * 1000) {
    if (depth == 1) printf("Can't fully solve in 10 sec, return best case.\n");

    return;
  }

  if (depth == graph->size) {
    int path = graph->matrix[current_path[depth - 1]][current_path[0]];

    current_dist = (path) ? current_dist + path : INT_MAX;

    if (current_dist < result->distance) {
      result->distance = current_dist;
      current_path[depth] = current_path[0];
      for (int i = 0; i < graph->size + 1; i++) {
        result->vertices[i] = current_path[i];
      }
    }

  } else {
    for (int i = 0; i < graph->size; i++) {
      if (!visited[i] && (graph->matrix[current_path[depth - 1]][i])) {
        visited[i] = 1;
        current_path[depth] = i;
        current_dist += graph->matrix[current_path[depth - 1]][i];

        brute_force(graph, result, current_path, visited, current_dist,
                    depth + 1, t);

        current_dist -= graph->matrix[current_path[depth - 1]][i];
        visited[i] = 0;
      }
    }
  }
}

long long get_time() {
  struct timeval t;
  gettimeofday(&t, NULL);

  return (long long)t.tv_sec * 1000 + t.tv_usec / 1000;
}