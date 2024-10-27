#ifndef A2_SIMPLENAVIGATOR_V1_0_1_S21_GRAPH_H
#define A2_SIMPLENAVIGATOR_V1_0_1_S21_GRAPH_H

typedef struct graph {
  int size;
  int **matrix;
} Graph;

int load_graph_from_file(char *filename, Graph *result);
int export_graph_to_dot(char *filename, Graph *graph);

#endif  // A2_SIMPLENAVIGATOR_V1_0_1_S21_GRAPH_H