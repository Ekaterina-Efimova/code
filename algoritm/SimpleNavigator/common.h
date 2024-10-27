#ifndef A2_SIMPLENAVIGATOR_V1_0_1_COMMON_H
#define A2_SIMPLENAVIGATOR_V1_0_1_COMMON_H

#include <errno.h>
#include <string.h>

#include "common.h"
#include "s21_containers.h"
#include "s21_graph.h"
#include "s21_graph_algorithms.h"

int load_matrix_a_from_file(Graph* result, FILE* file);
void print_vertex_name(FILE* file, int i);
int s21_create_graph(int size, Graph* result);
void s21_remove_graph(Graph* graph);

long long get_time();

#endif  // A2_SIMPLENAVIGATOR_V1_0_1_COMMON_H
