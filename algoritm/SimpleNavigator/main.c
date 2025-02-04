#include "main.h"

int main() {
  Data data = {0};
  main_loop(&data);
  return data.error;
}

/**
 * Основной цикл программы
 * @param data Указатель на набор данных
 */
void main_loop(Data* data) {
  while (print_main_menu() &&
         (data->user_choice = get_user_input_int(0, 9)) != 9) {
    data->state = data->state * 10 + data->user_choice;
    fsm_func fsm_table[9] = {paint_tyan, load_graph, export_graph, bfs,  dfs,
                             deikstra,   floid,      prim,         kamen};
    fsm_func fsm_action = fsm_table[data->state];
    if (fsm_action) {
      fsm_action(data);
    }
  }
  if (data->graph.matrix) {
    s21_remove_graph(&data->graph);
  }
}

/**
 * Печать массива
 * @param count количество элементов
 * @param array указатель на массив
 */
void print_array(int count, int* array) {
  int shift = 1;
  for (int i = 0; i < count; i++) {
    printf("%d ", array[i] + shift);
  }
  printf("\n");
}

/**
 * Считывание числа из консоли ввода пользователя в диапазоне от start до end
 * @param start Начало диапазона
 * @param end Конец диапазона
 * @return введенное значение в диапазоне start < x < end
 */
int get_user_input_int(int start, int end) {
  int user_choice = 0;
  char s[256] = {0};
  scanf("%s", s);
  while (sscanf(s, "%d", &user_choice) != 1 || user_choice < start ||
         user_choice > end) {
    printf("Incorrect input. Try again: ");
    scanf("%s", s);
  }
  return user_choice;
}

/**
 * Печать main menu
 * @return true
 */
int print_main_menu() {
  printf("\nWhat do you want to do?\n");
  printf("1. Load the original graph from a file\n");
  printf("2. Export graph to DOT format\n");
  printf("3. Traverse the graph in breadth (BFS)\n");
  printf("4. Traverse the graph in depth (DFS)\n");
  printf(
      "5. Find the shortest path between any two vertices (Dijkstra's "
      "algorithm)\n");
  printf(
      "6. Find the shortest paths between all pairs of vertices in the graph "
      "(Floyd-Warshall algorithm)\n");
  printf(
      "7. Search for the minimum spanning tree in the graph (Prim's "
      "algorithm)\n");
  printf(
      "8. Solve the Salesman problem (Ant colony, Brute-Force, Close "
      "points)\n");
  printf("9. Exit\n");
  printf("> ");
  return true;
}

/**
 * Выводит размер графа и матрицу смежности на экран
 * @param graph указатель на граф
 */
void print_matrix(const Graph* graph) {
  printf("%+d\n", graph->size);
  for (int i = 0; i < graph->size; i++) {
    for (int j = 0; j < graph->size; j++) {
      printf(graph->matrix[i][j] == -1 ? " -- " : "%3d ", graph->matrix[i][j]);
    }
    printf("\n");
  }
}

/**
 * Запуск решения задачи коммивояжёра
 * @param data указатель на граф
 */
void kamen(Data* data) {
  if (data->graph.matrix) {
    printf("Enter number of iterations:\n> ");
    int iter = get_user_input_int(1, INT_MAX);

    long long int t = get_time();
    tsm_result result_ant;
    for (int i = 0; i < ((iter > 100) ? 100 : iter); i++) {
      result_ant = solve_traveling_salesman_problem(&data->graph);
      free(result_ant.vertices);
    }
    double td =
        (double)(get_time() - t) / 1000 * ((iter > 100) ? iter / 100 : 1);
    printf("         Ant time: %.3lf s\n", td);
    printf("      path length: %.0f\n", result_ant.distance);

    t = get_time();
    tsm_result result_brute = kamen_brute_force(&data->graph);
    td = (double)(get_time() - t) / 1000 * iter;
    printf(" Brute-force time: %.3lf s\n", td);
    printf("      path length: %.0f\n", result_brute.distance);
    free(result_brute.vertices);

    t = get_time();
    tsm_result result_close;
    for (int i = 0; i < iter; i++) {
      result_close = kamen_close_points(&data->graph);
      free(result_close.vertices);
    }
    td = (double)(get_time() - t) / 1000;
    printf("Close points time: %.3lf s\n", td);
    printf("      path length: %.0f\n", result_close.distance);
  } else {
    printf(
        "\nThe graph is not initialized. Please load the graph from file "
        "first.\n");
  }
  data->state = 0;
}

/**
 * Применяет алгоритм Дэйкстры
 * @param data Указатель на набор данных
 */
void deikstra(Data* data) {
  if (data->graph.matrix) {
    printf("Enter START vertex and END vertex:\n> ");
    int vertex_1 = get_user_input_int(1, data->graph.size) - 1;
    int vertex_2 = get_user_input_int(1, data->graph.size) - 1;
    printf(
        "Shortest path distance: %d\n",
        get_shortest_path_between_vertices(&data->graph, vertex_1, vertex_2));
  } else {
    printf(
        "\nThe graph is not initialized. Please load the graph from file "
        "first.\n");
  }
  data->state = 0;
}

/**
 * Применяет алгоритм Флойда-Уоршалла
 * @param data Указатель на набор данных
 */
void floid(Data* data) {
  Graph tmp = {0};
  if (s21_create_graph(data->graph.size, &tmp) == EXIT_SUCCESS) {
    get_shortest_paths_between_all_vertices(&data->graph, tmp.matrix);
    print_matrix(&tmp);
    s21_remove_graph(&tmp);
  } else {
    printf(
        "\nThe graph is not initialized. Please load the graph from file "
        "first.\n");
  }
  data->state = 0;
}

/**
 * Применяет алгоритм Прима
 * @param data Указатель на набор данных
 */
void prim(Data* data) {
  putchar('a');
  Graph tmp = {0};
  if (s21_create_graph(data->graph.size, &tmp) == EXIT_SUCCESS) {
    get_least_spanning_tree(&data->graph, tmp.matrix);
    print_matrix(&tmp);
    s21_remove_graph(&tmp);
  } else {
    printf(
        "\nThe graph is not initialized. Please load the graph from file "
        "first.\n");
  }
  data->state = 0;
}

/**
 * Запуск DFS
 * @param data указатель на граф
 */
void dfs(Data* data) {
  if (data->graph.matrix) {
    int result[data->graph.size];
    printf("Enter START vertex:\n> ");
    print_array(
        depth_first_search(&data->graph,
                           get_user_input_int(1, data->graph.size) - 1, result),
        result);
  } else {
    printf(
        "\nThe graph is not initialized. Please load the graph from file "
        "first.\n");
  }
  data->state = 0;
}

/**
 * Запуск BFS
 * @param data указатель на граф
 */
void bfs(Data* data) {
  if (data->graph.matrix) {
    int result[data->graph.size];
    printf("Enter START vertex:\n> ");
    print_array(
        breadth_first_search(
            &data->graph, get_user_input_int(1, data->graph.size) - 1, result),
        result);
  } else {
    printf(
        "\nThe graph is not initialized. Please load the graph from file "
        "first.\n");
  }
  data->state = 0;
}

/**
 * Запуск загрузки графа
 * @param data указатель на граф
 */
void load_graph(Data* data) {
  if (data->graph.matrix) {
    s21_remove_graph(&data->graph);
  }
  char filename[256] = {0};
  printf("\nEnter graph filename:\n> ");
  scanf("%s", filename);
  FILE* file = NULL;
  if ((file = fopen(filename, "r")) != NULL) {
    fclose(file);
  } else {
    printf("%s: %s\n", filename, strerror(errno));
    filename[0] = '\0';
    printf(
        "The following graph will be loaded: "
        "../data-samples/true_graph_3.txt\n");
  }
  if ((data->state = load_graph_from_file(
           filename[0] ? filename : "../data-samples/true_graph_3.txt",
           &data->graph)) == EXIT_SUCCESS) {
    printf("\nGraph loaded successfully\n");
    print_matrix(&data->graph);
    data->state = 0;
  } else {
    printf("An error occurred while load_graph a graph from a file.\n");
  }
  data->state = 0;
}

/**
 * Запуск экспорта графа
 * @param data указатель на граф
 */
void export_graph(Data* data) {
  if (data->graph.matrix) {
    if ((data->error = export_graph_to_dot("export.dot", &data->graph)) ==
        EXIT_SUCCESS) {
      printf("\nGraph exported successfully in export.dot\n");
    } else {
      printf("\nAn error occurred while export_graph a graph from a file.\n");
    }
  } else {
    printf(
        "\nThe graph is not initialized. Please load the graph from file "
        "first.\n");
  }
  data->state = 0;
}

void paint_tyan(Data* data) {
  printf("\033[48;5;93m\033[1;37m  ⠀⠀⠀⠀⠀⣀⡀⠀⠀⠀⠀⠀⡠⢴⣴⣾⣿⡿⠓⡠⠀⠀⠀⠀⠠⢄⠁⢀\033[0m\n");
  printf("\033[48;5;93m\033[1;37m⠀⠀⠀⠀⠀⠳⣽⡽⠀⠀⡠⢊⣴⣿⣿⣿⣡⠖⠁⣀⡤⢖⠟⠁⡠⠀⡙⢿⣷⣄\033[0m\n");
  printf("\033[48;5;93m\033[1;37m⠀⠀⠐⡀⠀⠀⠀⠀⢠⣾⣿⣿⢽⣿⣿⣿⣥⠖⣻⣯⡾⠃⠀⡔⡀⠀⣷⢸⢿⣿\033[0m\n");
  printf("\033[48;5;93m\033[1;37m⠀⠀⠀⢰⠀⠀⠀⢠⢟⣿⠃⢀⣾⣿⠟⠋⢀⡾⢋⣾⠃⣠⡾⢰⡇⡇⣿⣿⡞⣿\033[0m\n");
  printf("\033[48;5;93m\033[1;37m⠀⠀⡤⣈⡀⠀⢀⠏⣼⣧⡴⣼⠟⠁⠀⠀⡾⠁⣾⡇⣰⢿⠃⢾⣿⣷⣿⣿⣇⢿\033[0m\n");
  printf("\033[48;5;93m\033[1;37m⠀⠀⠱⠼⠊⠀⠄⡜⣿⣿⡿⠃⠈⠁⠀⢸⠁⢠⡿⣰⢯⠃⠀⠘⣿⣿⣿⣿⣿⠸\033[0m\n");
  printf("\033[48;5;93m\033[1;37m⠀⠀⠀⠀⠀⠀⡘⡀⣸⣿⣱⡤⢴⣄⠀⠈⠀⠘⣷⠏⠌⠢⡀⠀⢿⣿⣿⣿⡟⡄\033[0m\n");
  printf("\033[48;5;93m\033[1;37m⠀⠀⠀⠀⢀⣌⠌⣴⣿⣿⠃⣴⣿⣟⡇⠀⠀⠀⠟⠀⠀⠀⠈⠢⢈⣿⡟⣿⡗⡇\033[0m\n");
  printf("\033[48;5;93m\033[1;37m⠀⠀⢀⡴⡻⣡⣾⠟⢹⡇⠀⡇⢄⢿⠇⠀⠀⠀⠀⠀⠀⣽⣶⣄⡀⠘⢷⡹⣿⣿\033[0m\n");
  printf("\033[48;5;93m\033[1;37m⠀⠀⣧⣾⡿⠋⠁⢀⡜⠙⡄⠓⠐⠁⠀⠀⠀⠀⠀⠀⡼⠛⠻⣟⠛⣆⠈⢷⣿⣿\033[0m\n");
  printf("\033[48;5;93m\033[1;37m⣴⣾⣟⣵⣿⣿⣿⣁⢇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡧⠠⠔⡹⠀⢸⠀⣼⣿⣿\033[0m\n");
  printf("\033[48;5;93m\033[1;37m⠿⡽⢫⡉⠀⣠⠔⠁⡀⠕⠠⡀⠀⠀⠀⠀⠀⠀⠀⠀⠘⠖⠊⠀⠀⢊⣾⢿⡿⠉\033[0m\n");
  printf("\033[48;5;93m\033[1;37m⠀⠁⠀⡹⢨⠁⠐⠈⢀⡠⠐⠁⠄⠡⡀⡀⠀⠀⠀⠀⠀⠀⠀⠠⠶⢛⡨⠊⠀⠀\033[0m\n");
  printf("\033[48;5;93m\033[1;37m⠀⠀⡜⠀⠈⣂⠀⠀⠀⠀⡠⠐⠉⡆⠀⣀⢀⣀⣀⣀⡀⠀⠀⣀⠴⣁⡀⠤⠀⠀\033[0m\n");
  printf("\033[48;5;93m\033[1;37m⠀⠈⠀⠀⠀⡇⠑⢄⠀⠀⠀⠀⣲⢥⡎⠀⢰⠀⢸⠀⢀⠉⠙⣿⣧⣀⣀⣂⣤⣼\033[0m\n");
  printf("\033[48;5;93m\033[1;37m⠀⠀⠀⠆⠁⠃⠀⠀⠈⠒⠒⠊⣸⠚⠁⠀⠀⠀⠀⠀⠀⠀⡜⠁⠀⠀⠀⠀⠈⠚\033[0m\n");
  printf("\033[48;5;93m\033[1;37m⠀⠀⠀⠀⠀⠂⠀⠀⠀⠀⠀⢀⠋⢆⠀⠀⠀⠀⠀⠀⠀⡘⠀⠀⠀⠀⠀⠀⠀⠀\033[0m\n");
  printf("\033[48;5;93m\033[1;37m⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠒⠂⠀⠀⠐⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀\033[0m\n");
  printf("\033[42m\033[1;37m   YOU'RE AWESOME!  \\(^.^)/   \033[0m\n");
  data->state = 0;
}