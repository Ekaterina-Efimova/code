#ifndef A2_SIMPLENAVIGATOR_V1_0_1_S21_GRAPH_ALGORITHMS_H
#define A2_SIMPLENAVIGATOR_V1_0_1_S21_GRAPH_ALGORITHMS_H

#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

#include "s21_containers.h"
#include "s21_graph.h"

#define ITERATIONS 1000
#define LIKE_POW 1
#define DIST_POW 2
#define BASE_LIKE 200
#define ADD 100
#define REMAINDER 0.6
#define MIN_REMAIN 1

typedef struct tsm_result {
  int *vertices;
  double distance;
} tsm_result;

int depth_first_search(Graph *graph, int start_vertex, int *result);
int breadth_first_search(Graph *graph, int start_vertex, int *result);

int get_shortest_path_between_vertices(Graph *graph, int vertex1, int vertex2);
int get_shortest_paths_between_all_vertices(Graph *graph, int **result);

int get_least_spanning_tree(Graph *graph, int **result);

tsm_result solve_traveling_salesman_problem(Graph *graph);
tsm_result kamen_brute_force(Graph *graph);
tsm_result kamen_close_points(Graph *graph);

#endif  // A2_SIMPLENAVIGATOR_V1_0_1_S21_GRAPH_ALGORITHMS_H