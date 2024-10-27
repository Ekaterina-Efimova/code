#include <check.h>

#include "../common.h"
void init_matrix(int **matrix, int size, int a);

Suite *queue_cases(void);
Suite *stack_cases(void);
Suite *breadth_first_search_cases(void);
Suite *depth_first_search_cases(void);
Suite *load_graph_from_file_cases(void);
Suite *export_graph_to_dot_cases(void);
Suite *get_shortest_path_between_vertices_cases(void);
Suite *get_shortest_path_between_all_vertices_cases(void);
Suite *get_least_spanning_tree_cases(void);
Suite *huldades_cases(void);

int main(void) {
  int failed = 0;
  int success = 0;
  Suite *simple_navigator[] = {queue_cases(),
                               stack_cases(),
                               breadth_first_search_cases(),
                               depth_first_search_cases(),
                               load_graph_from_file_cases(),
                               export_graph_to_dot_cases(),
                               get_shortest_path_between_vertices_cases(),
                               get_shortest_path_between_all_vertices_cases(),
                               get_least_spanning_tree_cases(),
                               huldades_cases(),
                               NULL};

  for (int i = 0; simple_navigator[i] != NULL; i++) {
    SRunner *sr = srunner_create(simple_navigator[i]);
    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_run_all(sr, CK_NORMAL);
    failed += srunner_ntests_failed(sr);
    success += srunner_ntests_run(sr);
    srunner_free(sr);
  }
  printf("\033[41m========= FAILED : %-3d =========\033[0m\n", failed);
  printf("\033[42m\033[30m========= SUCCESS: %-3d =========\033[0m\n", success);
  return failed == 0 ? 0 : 1;
}

START_TEST(q0) {
  List *list = NULL;
  ck_assert(push(list, 1) == EXIT_FAILURE);
}
END_TEST

START_TEST(q1) {
  List *list = NULL;
  ck_assert(queue(&list) == EXIT_SUCCESS);
  ck_assert_ptr_nonnull(list);
  destroy(&list);
  ck_assert_ptr_null(list);
}
END_TEST

START_TEST(q2) {
  List *list = NULL;
  ck_assert(queue(&list) == EXIT_SUCCESS);
  ck_assert_ptr_nonnull(list);
  ck_assert(push(list, 1) == EXIT_SUCCESS);
  int error = EXIT_SUCCESS;
  ck_assert(front(list, &error) == 1);
  ck_assert(error == EXIT_SUCCESS);
  error = EXIT_SUCCESS;
  ck_assert(back(list, &error) == 1);
  ck_assert(error == EXIT_SUCCESS);
  destroy(&list);
  ck_assert_ptr_null(list);
}
END_TEST

START_TEST(q3) {
  List *list = NULL;
  ck_assert(queue(&list) == EXIT_SUCCESS);
  ck_assert_ptr_nonnull(list);
  ck_assert(push(list, 1) == EXIT_SUCCESS);
  int error = EXIT_SUCCESS;
  ck_assert(front(list, &error) == 1);
  ck_assert(error == EXIT_SUCCESS);
  error = EXIT_SUCCESS;
  ck_assert(back(list, &error) == 1);
  ck_assert(push(list, 2) == EXIT_SUCCESS);
  error = EXIT_SUCCESS;
  ck_assert(front(list, &error) == 1);
  ck_assert(error == EXIT_SUCCESS);
  error = EXIT_SUCCESS;
  ck_assert(back(list, &error) == 2);
  destroy(&list);
  ck_assert_ptr_null(list);
}
END_TEST

START_TEST(q4) {
  List *list = NULL;
  ck_assert(queue(&list) == EXIT_SUCCESS);
  ck_assert_ptr_nonnull(list);
  ck_assert(push(list, 1) == EXIT_SUCCESS);
  int error = EXIT_SUCCESS;
  ck_assert(front(list, &error) == 1);
  ck_assert(error == EXIT_SUCCESS);
  error = EXIT_SUCCESS;
  ck_assert(back(list, &error) == 1);
  ck_assert(push(list, 2) == EXIT_SUCCESS);
  error = EXIT_SUCCESS;
  ck_assert(front(list, &error) == 1);
  ck_assert(error == EXIT_SUCCESS);
  error = EXIT_SUCCESS;
  ck_assert(back(list, &error) == 2);
  ck_assert(push(list, 3) == EXIT_SUCCESS);
  error = EXIT_SUCCESS;
  ck_assert(front(list, &error) == 1);
  ck_assert(error == EXIT_SUCCESS);
  error = EXIT_SUCCESS;
  ck_assert(back(list, &error) == 3);
  destroy(&list);
  ck_assert_ptr_null(list);
}
END_TEST

START_TEST(q5) {
  List *list = NULL;
  int error = EXIT_SUCCESS;
  ck_assert(pop(list, &error) == 0);
  ck_assert(error == EXIT_FAILURE);
}
END_TEST

START_TEST(q6) {
  List *list = NULL;
  ck_assert(queue(&list) == EXIT_SUCCESS);
  ck_assert_ptr_nonnull(list);
  int error = EXIT_SUCCESS;
  ck_assert(pop(list, &error) == 0);
  ck_assert(error == EXIT_FAILURE);
  destroy(&list);
  ck_assert_ptr_null(list);
}
END_TEST

START_TEST(q7) {
  List *list = NULL;
  ck_assert(queue(&list) == EXIT_SUCCESS);
  ck_assert_ptr_nonnull(list);
  ck_assert(push(list, 1) == EXIT_SUCCESS);
  int error = EXIT_SUCCESS;
  ck_assert(front(list, &error) == 1);
  ck_assert(error == EXIT_SUCCESS);
  error = EXIT_SUCCESS;
  ck_assert(back(list, &error) == 1);
  ck_assert(error == EXIT_SUCCESS);
  error = EXIT_SUCCESS;
  ck_assert(pop(list, &error) == 1);
  ck_assert(error == EXIT_SUCCESS);
  error = EXIT_SUCCESS;
  ck_assert(pop(list, &error) == 0);
  ck_assert(error == EXIT_FAILURE);
  destroy(&list);
  ck_assert_ptr_null(list);
}
END_TEST

START_TEST(q8) {
  List *list = NULL;
  ck_assert(queue(&list) == EXIT_SUCCESS);
  ck_assert_ptr_nonnull(list);
  ck_assert(push(list, 1) == EXIT_SUCCESS);
  int error = EXIT_SUCCESS;
  ck_assert(front(list, &error) == 1);
  ck_assert(error == EXIT_SUCCESS);
  error = EXIT_SUCCESS;
  ck_assert(back(list, &error) == 1);
  ck_assert(push(list, 2) == EXIT_SUCCESS);
  error = EXIT_SUCCESS;
  ck_assert(front(list, &error) == 1);
  ck_assert(error == EXIT_SUCCESS);
  error = EXIT_SUCCESS;
  ck_assert(back(list, &error) == 2);
  error = EXIT_SUCCESS;
  ck_assert(pop(list, &error) == 1);
  ck_assert(error == EXIT_SUCCESS);
  error = EXIT_SUCCESS;
  ck_assert(pop(list, &error) == 2);
  ck_assert(error == EXIT_SUCCESS);
  error = EXIT_SUCCESS;
  ck_assert(pop(list, &error) == 0);
  ck_assert(error == EXIT_FAILURE);
  destroy(&list);
  ck_assert_ptr_null(list);
}
END_TEST

START_TEST(q9) {
  List *list = NULL;
  ck_assert(queue(&list) == EXIT_SUCCESS);
  ck_assert_ptr_nonnull(list);
  ck_assert(push(list, 1) == EXIT_SUCCESS);
  int error = EXIT_SUCCESS;
  ck_assert(front(list, &error) == 1);
  ck_assert(error == EXIT_SUCCESS);
  error = EXIT_SUCCESS;
  ck_assert(back(list, &error) == 1);
  ck_assert(push(list, 2) == EXIT_SUCCESS);
  error = EXIT_SUCCESS;
  ck_assert(front(list, &error) == 1);
  ck_assert(error == EXIT_SUCCESS);
  error = EXIT_SUCCESS;
  ck_assert(back(list, &error) == 2);
  ck_assert(push(list, 3) == EXIT_SUCCESS);
  error = EXIT_SUCCESS;
  ck_assert(front(list, &error) == 1);
  ck_assert(error == EXIT_SUCCESS);
  error = EXIT_SUCCESS;
  ck_assert(back(list, &error) == 3);
  error = EXIT_SUCCESS;
  ck_assert(pop(list, &error) == 1);
  ck_assert(error == EXIT_SUCCESS);
  error = EXIT_SUCCESS;
  ck_assert(pop(list, &error) == 2);
  ck_assert(error == EXIT_SUCCESS);
  error = EXIT_SUCCESS;
  ck_assert(pop(list, &error) == 3);
  ck_assert(error == EXIT_SUCCESS);
  error = EXIT_SUCCESS;
  ck_assert(pop(list, &error) == 0);
  ck_assert(error == EXIT_FAILURE);
  destroy(&list);
  ck_assert_ptr_null(list);
}
END_TEST

START_TEST(q10) {
  List *list = NULL;
  ck_assert(queue(&list) == EXIT_SUCCESS);
  ck_assert_ptr_nonnull(list);
  int error = EXIT_SUCCESS;
  ck_assert(front(list, &error) == 0);
  ck_assert(error == EXIT_FAILURE);
  destroy(&list);
  ck_assert_ptr_null(list);
}
END_TEST

Suite *queue_cases(void) {
  Suite *s = suite_create("queue_cases");
  TCase *tc = tcase_create("queue");
  tcase_add_test(tc, q0);
  tcase_add_test(tc, q1);
  tcase_add_test(tc, q2);
  tcase_add_test(tc, q3);
  tcase_add_test(tc, q4);
  tcase_add_test(tc, q5);
  tcase_add_test(tc, q6);
  tcase_add_test(tc, q7);
  tcase_add_test(tc, q8);
  tcase_add_test(tc, q9);
  tcase_add_test(tc, q10);
  suite_add_tcase(s, tc);
  return s;
}

START_TEST(s1) {
  List *list = NULL;
  ck_assert(stack(&list) == EXIT_SUCCESS);
  ck_assert_ptr_nonnull(list);
  destroy(&list);
  ck_assert_ptr_null(list);
}
END_TEST

START_TEST(s2) {
  List *list = NULL;
  ck_assert(stack(&list) == EXIT_SUCCESS);
  ck_assert_ptr_nonnull(list);
  ck_assert(push(list, 1) == EXIT_SUCCESS);
  int error = EXIT_SUCCESS;
  ck_assert(top(list, &error) == 1);
  ck_assert(error == EXIT_SUCCESS);
  destroy(&list);
  ck_assert_ptr_null(list);
}
END_TEST

START_TEST(s3) {
  List *list = NULL;
  ck_assert(stack(&list) == EXIT_SUCCESS);
  ck_assert_ptr_nonnull(list);
  ck_assert(push(list, 1) == EXIT_SUCCESS);
  int error = EXIT_SUCCESS;
  ck_assert(top(list, &error) == 1);
  ck_assert(error == EXIT_SUCCESS);
  ck_assert(push(list, 2) == EXIT_SUCCESS);
  error = EXIT_SUCCESS;
  ck_assert(top(list, &error) == 2);
  ck_assert(error == EXIT_SUCCESS);
  destroy(&list);
  ck_assert_ptr_null(list);
}
END_TEST

START_TEST(s4) {
  List *list = NULL;
  ck_assert(stack(&list) == EXIT_SUCCESS);
  ck_assert_ptr_nonnull(list);
  ck_assert(push(list, 1) == EXIT_SUCCESS);
  int error = EXIT_SUCCESS;
  ck_assert(top(list, &error) == 1);
  ck_assert(error == EXIT_SUCCESS);
  ck_assert(push(list, 2) == EXIT_SUCCESS);
  error = EXIT_SUCCESS;
  ck_assert(top(list, &error) == 2);
  ck_assert(error == EXIT_SUCCESS);
  ck_assert(push(list, 3) == EXIT_SUCCESS);
  error = EXIT_SUCCESS;
  ck_assert(top(list, &error) == 3);
  ck_assert(error == EXIT_SUCCESS);
  destroy(&list);
  ck_assert_ptr_null(list);
}
END_TEST

START_TEST(s5) {
  List *list = NULL;
  ck_assert(stack(&list) == EXIT_SUCCESS);
  ck_assert_ptr_nonnull(list);
  int error = EXIT_SUCCESS;
  ck_assert(pop(list, &error) == 0);
  ck_assert(error == EXIT_FAILURE);
  destroy(&list);
  ck_assert_ptr_null(list);
}
END_TEST

START_TEST(s6) {
  List *list = NULL;
  ck_assert(stack(&list) == EXIT_SUCCESS);
  ck_assert_ptr_nonnull(list);
  ck_assert(push(list, 1) == EXIT_SUCCESS);
  int error = EXIT_SUCCESS;
  ck_assert(top(list, &error) == 1);
  ck_assert(error == EXIT_SUCCESS);
  error = EXIT_SUCCESS;
  ck_assert(pop(list, &error) == 1);
  ck_assert(error == EXIT_SUCCESS);
  error = EXIT_SUCCESS;
  ck_assert(pop(list, &error) == 0);
  ck_assert(error == EXIT_FAILURE);
  destroy(&list);
  ck_assert_ptr_null(list);
}
END_TEST

START_TEST(s7) {
  List *list = NULL;
  ck_assert(stack(&list) == EXIT_SUCCESS);
  ck_assert_ptr_nonnull(list);
  ck_assert(push(list, 1) == EXIT_SUCCESS);
  int error = EXIT_SUCCESS;
  ck_assert(top(list, &error) == 1);
  ck_assert(error == EXIT_SUCCESS);
  ck_assert(push(list, 2) == EXIT_SUCCESS);
  error = EXIT_SUCCESS;
  ck_assert(top(list, &error) == 2);
  ck_assert(error == EXIT_SUCCESS);
  error = EXIT_SUCCESS;
  ck_assert(pop(list, &error) == 2);
  ck_assert(error == EXIT_SUCCESS);
  error = EXIT_SUCCESS;
  ck_assert(pop(list, &error) == 1);
  ck_assert(error == EXIT_SUCCESS);
  error = EXIT_SUCCESS;
  ck_assert(pop(list, &error) == 0);
  ck_assert(error == EXIT_FAILURE);
  destroy(&list);
  ck_assert_ptr_null(list);
}
END_TEST

START_TEST(s8) {
  List *list = NULL;
  ck_assert(stack(&list) == EXIT_SUCCESS);
  ck_assert_ptr_nonnull(list);
  ck_assert(push(list, 1) == EXIT_SUCCESS);
  int error = EXIT_SUCCESS;
  ck_assert(top(list, &error) == 1);
  ck_assert(error == EXIT_SUCCESS);
  ck_assert(push(list, 2) == EXIT_SUCCESS);
  error = EXIT_SUCCESS;
  ck_assert(top(list, &error) == 2);
  ck_assert(error == EXIT_SUCCESS);
  ck_assert(push(list, 3) == EXIT_SUCCESS);
  error = EXIT_SUCCESS;
  ck_assert(top(list, &error) == 3);
  ck_assert(error == EXIT_SUCCESS);
  error = EXIT_SUCCESS;
  ck_assert(pop(list, &error) == 3);
  ck_assert(error == EXIT_SUCCESS);
  error = EXIT_SUCCESS;
  ck_assert(pop(list, &error) == 2);
  ck_assert(error == EXIT_SUCCESS);
  error = EXIT_SUCCESS;
  ck_assert(pop(list, &error) == 1);
  ck_assert(error == EXIT_SUCCESS);
  error = EXIT_SUCCESS;
  ck_assert(pop(list, &error) == 0);
  ck_assert(error == EXIT_FAILURE);
  destroy(&list);
  ck_assert_ptr_null(list);
}
END_TEST

START_TEST(s9) {
  List *list = NULL;
  ck_assert(stack(&list) == EXIT_SUCCESS);
  ck_assert_ptr_nonnull(list);
  int error = EXIT_SUCCESS;
  ck_assert(top(list, &error) == 0);
  ck_assert(error == EXIT_FAILURE);
  destroy(&list);
  ck_assert_ptr_null(list);
}
END_TEST

Suite *stack_cases(void) {
  Suite *s = suite_create("stack_cases");
  TCase *tc = tcase_create("stack");
  tcase_add_test(tc, s1);
  tcase_add_test(tc, s2);
  tcase_add_test(tc, s3);
  tcase_add_test(tc, s4);
  tcase_add_test(tc, s5);
  tcase_add_test(tc, s6);
  tcase_add_test(tc, s7);
  tcase_add_test(tc, s8);
  tcase_add_test(tc, s9);
  suite_add_tcase(s, tc);
  return s;
}

START_TEST(bfc1) {
  Graph graph = {0};
  s21_create_graph(4, &graph);
  graph.matrix[0][1] = 1;
  graph.matrix[0][2] = 1;
  graph.matrix[0][3] = 1;
  graph.matrix[1][0] = 1;
  graph.matrix[2][0] = 1;
  graph.matrix[3][0] = 1;
  int result[4] = {0};
  ck_assert_int_eq(4, breadth_first_search(&graph, 0, result));
  ck_assert_int_eq(0, result[0]);
  ck_assert_int_eq(1, result[1]);
  ck_assert_int_eq(2, result[2]);
  ck_assert_int_eq(3, result[3]);
  s21_remove_graph(&graph);
}
END_TEST

START_TEST(bfc2) {
  Graph graph = {0};
  s21_create_graph(6, &graph);
  graph.matrix[0][1] = 1;
  graph.matrix[0][2] = 1;
  graph.matrix[1][2] = 1;
  graph.matrix[1][3] = 1;
  graph.matrix[2][3] = 1;
  graph.matrix[3][4] = 1;
  graph.matrix[4][0] = 1;
  graph.matrix[4][1] = 1;
  graph.matrix[4][5] = 1;
  int result[6] = {0};
  ck_assert_int_eq(6, breadth_first_search(&graph, 0, result));
  ck_assert_int_eq(0, result[0]);
  ck_assert_int_eq(1, result[1]);
  ck_assert_int_eq(2, result[2]);
  ck_assert_int_eq(3, result[3]);
  ck_assert_int_eq(4, result[4]);
  ck_assert_int_eq(5, result[5]);
  s21_remove_graph(&graph);
}
END_TEST

START_TEST(bfc3) {
  Graph graph = {0};
  s21_create_graph(6, &graph);
  graph.matrix[0][1] = 1;
  graph.matrix[0][2] = 1;
  graph.matrix[1][2] = 1;
  graph.matrix[1][3] = 1;
  graph.matrix[2][3] = 1;
  graph.matrix[3][4] = 1;
  graph.matrix[4][0] = 1;
  graph.matrix[4][1] = 1;
  graph.matrix[4][5] = 1;
  int result[6] = {0};
  ck_assert_int_eq(6, breadth_first_search(&graph, 1, result));
  ck_assert_int_eq(1, result[0]);
  ck_assert_int_eq(2, result[1]);
  ck_assert_int_eq(3, result[2]);
  ck_assert_int_eq(4, result[3]);
  ck_assert_int_eq(0, result[4]);
  ck_assert_int_eq(5, result[5]);
  s21_remove_graph(&graph);
}
END_TEST

START_TEST(bfc4) {
  Graph graph = {0};
  s21_create_graph(6, &graph);
  graph.matrix[0][1] = 1;
  graph.matrix[0][2] = 1;
  graph.matrix[1][2] = 1;
  graph.matrix[1][3] = 1;
  graph.matrix[2][3] = 1;
  graph.matrix[3][4] = 1;
  graph.matrix[4][0] = 1;
  graph.matrix[4][1] = 1;
  graph.matrix[4][5] = 1;
  int result[6] = {0};
  ck_assert_int_eq(6, breadth_first_search(&graph, 2, result));
  ck_assert_int_eq(2, result[0]);
  ck_assert_int_eq(3, result[1]);
  ck_assert_int_eq(4, result[2]);
  ck_assert_int_eq(0, result[3]);
  ck_assert_int_eq(1, result[4]);
  ck_assert_int_eq(5, result[5]);
  s21_remove_graph(&graph);
}
END_TEST

START_TEST(bfc5) {
  Graph graph = {0};
  s21_create_graph(6, &graph);
  graph.matrix[0][1] = 1;
  graph.matrix[0][2] = 1;
  graph.matrix[1][2] = 1;
  graph.matrix[1][3] = 1;
  graph.matrix[2][3] = 1;
  graph.matrix[3][4] = 1;
  graph.matrix[4][0] = 1;
  graph.matrix[4][1] = 1;
  graph.matrix[4][5] = 1;
  int result[6] = {0};
  ck_assert_int_eq(6, breadth_first_search(&graph, 3, result));
  ck_assert_int_eq(3, result[0]);
  ck_assert_int_eq(4, result[1]);
  ck_assert_int_eq(0, result[2]);
  ck_assert_int_eq(1, result[3]);
  ck_assert_int_eq(5, result[4]);
  ck_assert_int_eq(2, result[5]);
  s21_remove_graph(&graph);
}
END_TEST

START_TEST(bfc6) {
  Graph graph = {0};
  s21_create_graph(6, &graph);
  graph.matrix[0][1] = 1;
  graph.matrix[0][2] = 1;
  graph.matrix[1][2] = 1;
  graph.matrix[1][3] = 1;
  graph.matrix[2][3] = 1;
  graph.matrix[3][4] = 1;
  graph.matrix[4][0] = 1;
  graph.matrix[4][1] = 1;
  graph.matrix[4][5] = 1;
  int result[6] = {0};
  ck_assert_int_eq(6, breadth_first_search(&graph, 4, result));
  ck_assert_int_eq(4, result[0]);
  ck_assert_int_eq(0, result[1]);
  ck_assert_int_eq(1, result[2]);
  ck_assert_int_eq(5, result[3]);
  ck_assert_int_eq(2, result[4]);
  ck_assert_int_eq(3, result[5]);
  s21_remove_graph(&graph);
}
END_TEST

START_TEST(bfc7) {
  Graph graph = {0};
  s21_create_graph(6, &graph);
  graph.matrix[0][1] = 1;
  graph.matrix[0][2] = 1;
  graph.matrix[1][2] = 1;
  graph.matrix[1][3] = 1;
  graph.matrix[2][3] = 1;
  graph.matrix[3][4] = 1;
  graph.matrix[4][0] = 1;
  graph.matrix[4][1] = 1;
  graph.matrix[4][5] = 1;
  int result[6] = {0};
  ck_assert_int_eq(1, breadth_first_search(&graph, 5, result));
  ck_assert_int_eq(5, result[0]);
  s21_remove_graph(&graph);
}
END_TEST

START_TEST(bfc8) {
  Graph graph = {0};
  s21_create_graph(6, &graph);
  int result[6] = {0};
  ck_assert_int_eq(0, breadth_first_search(&graph, 8, result));
  s21_remove_graph(&graph);
}
END_TEST

Suite *breadth_first_search_cases(void) {
  Suite *s = suite_create("breadth_first_search_cases");
  TCase *tc = tcase_create("breadth_first_search");
  tcase_add_test(tc, bfc1);
  tcase_add_test(tc, bfc2);
  tcase_add_test(tc, bfc3);
  tcase_add_test(tc, bfc4);
  tcase_add_test(tc, bfc5);
  tcase_add_test(tc, bfc6);
  tcase_add_test(tc, bfc7);
  tcase_add_test(tc, bfc8);
  suite_add_tcase(s, tc);
  return s;
}

START_TEST(huldades1) {
  Graph graph;
  s21_create_graph(6, &graph);

  graph.matrix[0][1] = 7;
  graph.matrix[0][2] = 9;
  graph.matrix[0][5] = 14;

  graph.matrix[1][0] = 7;
  graph.matrix[1][2] = 10;
  graph.matrix[1][3] = 15;

  graph.matrix[2][0] = 9;
  graph.matrix[2][1] = 10;
  graph.matrix[2][3] = 11;
  graph.matrix[2][4] = 9;
  graph.matrix[2][5] = 2;

  graph.matrix[3][1] = 15;
  graph.matrix[3][2] = 11;
  graph.matrix[3][4] = 6;

  graph.matrix[4][2] = 9;
  graph.matrix[4][3] = 6;
  graph.matrix[4][5] = 9;

  graph.matrix[5][0] = 14;
  graph.matrix[5][2] = 2;
  graph.matrix[5][4] = 9;

  tsm_result result = solve_traveling_salesman_problem(&graph);
  ck_assert_int_eq(48, result.distance);
  free(result.vertices);
  s21_remove_graph(&graph);
}
END_TEST

START_TEST(huldades2) {
  Graph graph;
  load_graph_from_file("../data-samples/true_graph_3.txt", &graph);

  tsm_result result = solve_traveling_salesman_problem(&graph);
  ck_assert_int_le(result.distance, 256);

  free(result.vertices);
  s21_remove_graph(&graph);
}
END_TEST

START_TEST(huldades3) {
  Graph graph;
  load_graph_from_file("../data-samples/true_graph_3.txt", &graph);

  long long int t = get_time();
  tsm_result ant_result = solve_traveling_salesman_problem(&graph);
  printf("         Ant time: %.3lf ms\n", (double)(get_time() - t) / 1000);
  // printf("path length: %.0f\n", result.distance);

  // t = get_time();
  tsm_result brute_result = kamen_brute_force(&graph);
  // printf(" Brute-force time: %.3lf ms\n", (double)(get_time() - t) / 1000);
  // printf("path length: %.0f\n", result.distance);

  // t = get_time();
  tsm_result close_result = kamen_close_points(&graph);
  // printf("Close points time: %.3lf ms\n", (double)(get_time() - t) / 1000);
  // printf("path length: %.0f\n", result.distance);

  free(ant_result.vertices);
  free(brute_result.vertices);
  free(close_result.vertices);
  s21_remove_graph(&graph);
}
END_TEST

Suite *huldades_cases(void) {
  Suite *s = suite_create("huldades_cases");
  TCase *tc = tcase_create("breadth_first_search");
  tcase_add_test(tc, huldades1);
  tcase_add_test(tc, huldades2);
  tcase_add_test(tc, huldades3);
  suite_add_tcase(s, tc);

  return s;
}

START_TEST(dfc1) {
  Graph graph = {0};
  s21_create_graph(4, &graph);
  graph.matrix[0][1] = 1;
  graph.matrix[0][2] = 1;
  graph.matrix[0][3] = 1;
  graph.matrix[1][0] = 1;
  graph.matrix[2][0] = 1;
  graph.matrix[3][0] = 1;
  int result[4] = {0};
  ck_assert_int_eq(4, depth_first_search(&graph, 0, result));
  ck_assert_int_eq(0, result[0]);
  ck_assert_int_eq(1, result[1]);
  ck_assert_int_eq(2, result[2]);
  ck_assert_int_eq(3, result[3]);
  s21_remove_graph(&graph);
}
END_TEST

START_TEST(dfc2) {
  Graph graph = {0};
  s21_create_graph(6, &graph);
  graph.matrix[0][1] = 1;
  graph.matrix[0][2] = 1;
  graph.matrix[1][2] = 1;
  graph.matrix[1][3] = 1;
  graph.matrix[2][3] = 1;
  graph.matrix[3][4] = 1;
  graph.matrix[4][0] = 1;
  graph.matrix[4][1] = 1;
  graph.matrix[4][5] = 1;
  int result[6] = {0};
  ck_assert_int_eq(6, depth_first_search(&graph, 0, result));
  ck_assert_int_eq(0, result[0]);
  ck_assert_int_eq(1, result[1]);
  ck_assert_int_eq(2, result[2]);
  ck_assert_int_eq(3, result[3]);
  ck_assert_int_eq(4, result[4]);
  ck_assert_int_eq(5, result[5]);
  s21_remove_graph(&graph);
}
END_TEST

START_TEST(dfc3) {
  Graph graph = {0};
  s21_create_graph(6, &graph);
  graph.matrix[0][1] = 1;
  graph.matrix[0][2] = 1;
  graph.matrix[1][2] = 1;
  graph.matrix[1][3] = 1;
  graph.matrix[2][3] = 1;
  graph.matrix[3][4] = 1;
  graph.matrix[4][0] = 1;
  graph.matrix[4][1] = 1;
  graph.matrix[4][5] = 1;
  int result[6] = {0};
  ck_assert_int_eq(6, depth_first_search(&graph, 1, result));
  ck_assert_int_eq(1, result[0]);
  ck_assert_int_eq(2, result[1]);
  ck_assert_int_eq(3, result[2]);
  ck_assert_int_eq(4, result[3]);
  ck_assert_int_eq(0, result[4]);
  ck_assert_int_eq(5, result[5]);
  s21_remove_graph(&graph);
}
END_TEST

START_TEST(dfc4) {
  Graph graph = {0};
  s21_create_graph(6, &graph);
  graph.matrix[0][1] = 1;
  graph.matrix[0][2] = 1;
  graph.matrix[1][2] = 1;
  graph.matrix[1][3] = 1;
  graph.matrix[2][3] = 1;
  graph.matrix[3][4] = 1;
  graph.matrix[4][0] = 1;
  graph.matrix[4][1] = 1;
  graph.matrix[4][5] = 1;
  int result[6] = {0};
  ck_assert_int_eq(6, depth_first_search(&graph, 2, result));
  ck_assert_int_eq(2, result[0]);
  ck_assert_int_eq(3, result[1]);
  ck_assert_int_eq(4, result[2]);
  ck_assert_int_eq(0, result[3]);
  ck_assert_int_eq(1, result[4]);
  ck_assert_int_eq(5, result[5]);
  s21_remove_graph(&graph);
}
END_TEST

START_TEST(dfc5) {
  Graph graph = {0};
  s21_create_graph(6, &graph);
  graph.matrix[0][1] = 1;
  graph.matrix[0][2] = 1;
  graph.matrix[1][2] = 1;
  graph.matrix[1][3] = 1;
  graph.matrix[2][3] = 1;
  graph.matrix[3][4] = 1;
  graph.matrix[4][0] = 1;
  graph.matrix[4][1] = 1;
  graph.matrix[4][5] = 1;
  int result[6] = {0};
  ck_assert_int_eq(6, depth_first_search(&graph, 3, result));
  ck_assert_int_eq(3, result[0]);
  ck_assert_int_eq(4, result[1]);
  ck_assert_int_eq(0, result[2]);
  ck_assert_int_eq(1, result[3]);
  ck_assert_int_eq(2, result[4]);
  ck_assert_int_eq(5, result[5]);
  s21_remove_graph(&graph);
}
END_TEST

START_TEST(dfc6) {
  Graph graph = {0};
  s21_create_graph(6, &graph);
  graph.matrix[0][1] = 1;
  graph.matrix[0][2] = 1;
  graph.matrix[1][2] = 1;
  graph.matrix[1][3] = 1;
  graph.matrix[2][3] = 1;
  graph.matrix[3][4] = 1;
  graph.matrix[4][0] = 1;
  graph.matrix[4][1] = 1;
  graph.matrix[4][5] = 1;
  int result[6] = {0};
  ck_assert_int_eq(6, depth_first_search(&graph, 4, result));
  ck_assert_int_eq(4, result[0]);
  ck_assert_int_eq(0, result[1]);
  ck_assert_int_eq(1, result[2]);
  ck_assert_int_eq(2, result[3]);
  ck_assert_int_eq(3, result[4]);
  ck_assert_int_eq(5, result[5]);
  s21_remove_graph(&graph);
}
END_TEST

START_TEST(dfc7) {
  Graph graph = {0};
  s21_create_graph(6, &graph);
  graph.matrix[0][1] = 1;
  graph.matrix[0][2] = 1;
  graph.matrix[1][2] = 1;
  graph.matrix[1][3] = 1;
  graph.matrix[2][3] = 1;
  graph.matrix[3][4] = 1;
  graph.matrix[4][0] = 1;
  graph.matrix[4][1] = 1;
  graph.matrix[4][5] = 1;
  int result[6] = {0};
  ck_assert_int_eq(1, depth_first_search(&graph, 5, result));
  ck_assert_int_eq(5, result[0]);
  s21_remove_graph(&graph);
}
END_TEST

START_TEST(dfc8) {
  Graph graph = {0};
  s21_create_graph(6, &graph);
  int result[6] = {0};
  ck_assert_int_eq(0, depth_first_search(&graph, 8, result));
  s21_remove_graph(&graph);
}
END_TEST

Suite *depth_first_search_cases(void) {
  Suite *s = suite_create("depth_first_search_cases");
  TCase *tc = tcase_create("depth_first_search");
  tcase_add_test(tc, dfc1);
  tcase_add_test(tc, dfc2);
  tcase_add_test(tc, dfc3);
  tcase_add_test(tc, dfc4);
  tcase_add_test(tc, dfc5);
  tcase_add_test(tc, dfc6);
  tcase_add_test(tc, dfc7);
  tcase_add_test(tc, dfc8);
  suite_add_tcase(s, tc);
  return s;
}

START_TEST(lgff1) {
  Graph graph = {0};
  ck_assert_int_eq(
      EXIT_FAILURE,
      load_graph_from_file("../data-samples/false_graph_1.txt", &graph));
}
END_TEST

START_TEST(lgff2) {
  Graph graph = {0};
  ck_assert_int_eq(
      EXIT_FAILURE,
      load_graph_from_file("../data-samples/false_graph_2.txt", &graph));
}
END_TEST

START_TEST(lgff3) {
  Graph graph = {0};
  ck_assert_int_eq(
      EXIT_FAILURE,
      load_graph_from_file("../data-samples/false_graph_3.txt", &graph));
}
END_TEST

START_TEST(lgff4) {
  Graph graph = {0};
  ck_assert_int_eq(
      EXIT_FAILURE,
      load_graph_from_file("../data-samples/false_graph_4.txt", &graph));
}
END_TEST

START_TEST(lgff5) {
  Graph graph = {0};
  ck_assert_int_eq(
      EXIT_FAILURE,
      load_graph_from_file("../data-samples/false_graph_5.txt", &graph));
}
END_TEST

START_TEST(lgff6) {
  Graph graph = {0};
  ck_assert_int_eq(
      EXIT_SUCCESS,
      load_graph_from_file("../data-samples/true_graph_1.txt", &graph));
  free(graph.matrix);
}
END_TEST

START_TEST(lgff7) {
  Graph graph = {0};
  ck_assert_int_eq(
      EXIT_SUCCESS,
      load_graph_from_file("../data-samples/true_graph_2.txt", &graph));
  free(graph.matrix);
}
END_TEST

START_TEST(lgff8) {
  Graph graph = {0};
  ck_assert_int_eq(
      EXIT_SUCCESS,
      load_graph_from_file("../data-samples/true_graph_3.txt", &graph));
  free(graph.matrix);
}
END_TEST

START_TEST(lgff9) {
  Graph graph = {0};
  ck_assert_int_eq(
      EXIT_FAILURE,
      load_graph_from_file("../data-samples/none_graph_1.txt", &graph));
}
END_TEST

Suite *load_graph_from_file_cases(void) {
  Suite *s = suite_create("load_graph_from_file_cases");
  TCase *tc = tcase_create("load_graph_from_file");
  tcase_add_test(tc, lgff1);
  tcase_add_test(tc, lgff2);
  tcase_add_test(tc, lgff3);
  tcase_add_test(tc, lgff4);
  tcase_add_test(tc, lgff5);
  tcase_add_test(tc, lgff6);
  tcase_add_test(tc, lgff7);
  tcase_add_test(tc, lgff8);
  tcase_add_test(tc, lgff9);
  suite_add_tcase(s, tc);
  return s;
}

int check_export(char *filename) {
  int result = EXIT_SUCCESS;
  FILE *f_origin = NULL;
  FILE *f_export = NULL;
  if ((f_origin = fopen(filename, "rt")) != NULL) {
    if ((f_export = fopen("../data-samples/export.dot", "rt")) != NULL) {
      int c_origin = 0;
      int c_export = 0;
      while (result == EXIT_SUCCESS && c_origin != EOF && c_export != EOF) {
        if ((c_origin = fgetc(f_origin)) != (c_export = fgetc(f_export))) {
          result = EXIT_FAILURE;
        }
      }
      fclose(f_export);
    } else {
      result = EXIT_FAILURE;
    }
    fclose(f_origin);
  } else {
    result = EXIT_FAILURE;
  }
  return result;
}

START_TEST(egtd1) {
  Graph graph = {0};
  s21_create_graph(4, &graph);
  graph.matrix[0][1] = 1;
  graph.matrix[1][0] = 1;
  graph.matrix[1][2] = 1;
  graph.matrix[1][3] = 1;
  graph.matrix[2][1] = 1;
  graph.matrix[3][1] = 1;
  ck_assert_int_eq(EXIT_SUCCESS,
                   export_graph_to_dot("../data-samples/export.dot", &graph));
  ck_assert_int_eq(EXIT_SUCCESS,
                   check_export("../data-samples/true_dot_1.dot"));
  s21_remove_graph(&graph);
}
END_TEST

START_TEST(egtd2) {
  Graph graph = {0};
  s21_create_graph(4, &graph);
  graph.matrix[0][1] = 1;
  graph.matrix[1][2] = 1;
  graph.matrix[1][3] = 1;
  ck_assert_int_eq(EXIT_SUCCESS,
                   export_graph_to_dot("../data-samples/export.dot", &graph));
  ck_assert_int_eq(EXIT_SUCCESS,
                   check_export("../data-samples/true_dot_2.dot"));
  s21_remove_graph(&graph);
}
END_TEST

START_TEST(egtd3) {
  Graph graph = {0};
  s21_create_graph(4, &graph);
  graph.matrix[0][1] = 1;
  graph.matrix[1][0] = 1;
  graph.matrix[1][2] = 1;
  graph.matrix[1][3] = 1;
  graph.matrix[2][1] = 1;
  graph.matrix[3][1] = 1;
  ck_assert_int_eq(EXIT_SUCCESS,
                   export_graph_to_dot("../data-samples/export.dot", &graph));
  ck_assert_int_eq(EXIT_FAILURE,
                   check_export("../data-samples/false_dot_1.dot"));
  s21_remove_graph(&graph);
}
END_TEST

START_TEST(egtd4) {
  Graph graph = {0};
  s21_create_graph(4, &graph);
  graph.matrix[0][1] = 1;
  graph.matrix[1][2] = 1;
  graph.matrix[1][3] = 1;
  ck_assert_int_eq(EXIT_SUCCESS,
                   export_graph_to_dot("../data-samples/export.dot", &graph));
  ck_assert_int_eq(EXIT_FAILURE,
                   check_export("../data-samples/false_dot_2.dot"));
  s21_remove_graph(&graph);
}
END_TEST

START_TEST(egtd5) {
  Graph graph = {0};
  s21_create_graph(4, &graph);
  graph.matrix[0][1] = 1;
  graph.matrix[1][2] = 1;
  graph.matrix[1][3] = 1;
  graph.size = 0;
  ck_assert_int_eq(EXIT_FAILURE,
                   export_graph_to_dot("../data-samples/export.dot", &graph));
  ck_assert_int_eq(EXIT_FAILURE,
                   check_export("../data-samples/false_dot_2.dot"));
  s21_remove_graph(&graph);
}
END_TEST

START_TEST(egtd6) {
  Graph graph = {0};
  s21_create_graph(27, &graph);
  ck_assert_int_eq(EXIT_SUCCESS,
                   export_graph_to_dot("../data-samples/export.dot", &graph));
  ck_assert_int_eq(EXIT_SUCCESS,
                   check_export("../data-samples/true_dot_3.dot"));
  s21_remove_graph(&graph);
}
END_TEST

START_TEST(egtd7) {
  Graph graph = {0};
  s21_create_graph(29, &graph);
  graph.matrix[26][27] = 1;
  graph.matrix[26][28] = 1;
  graph.matrix[27][28] = 1;
  ck_assert_int_eq(EXIT_SUCCESS,
                   export_graph_to_dot("../data-samples/export.dot", &graph));
  ck_assert_int_eq(EXIT_SUCCESS,
                   check_export("../data-samples/true_dot_4.dot"));
  s21_remove_graph(&graph);
}
END_TEST

Suite *export_graph_to_dot_cases(void) {
  Suite *s = suite_create("export_graph_to_dot_cases");
  TCase *tc = tcase_create("export_graph_to_dot");
  tcase_add_test(tc, egtd1);
  tcase_add_test(tc, egtd2);
  tcase_add_test(tc, egtd3);
  tcase_add_test(tc, egtd4);
  tcase_add_test(tc, egtd5);
  tcase_add_test(tc, egtd6);
  tcase_add_test(tc, egtd7);
  suite_add_tcase(s, tc);
  return s;
}

START_TEST(deikstra_1) {
  Graph graph = {0};
  graph.size = 6;
  s21_create_graph(graph.size, &graph);

  graph.matrix[0][1] = 7;
  graph.matrix[0][2] = 9;
  graph.matrix[0][5] = 14;
  graph.matrix[1][2] = 10;
  graph.matrix[1][3] = 15;
  graph.matrix[2][3] = 11;
  graph.matrix[2][4] = 9;
  graph.matrix[2][5] = 2;
  graph.matrix[3][4] = 6;
  graph.matrix[4][5] = 9;

  graph.matrix[1][0] = 7;
  graph.matrix[2][0] = 9;
  graph.matrix[5][0] = 14;
  graph.matrix[2][1] = 10;
  graph.matrix[3][1] = 15;
  graph.matrix[3][2] = 11;
  graph.matrix[4][2] = 9;
  graph.matrix[5][2] = 2;
  graph.matrix[4][3] = 6;
  graph.matrix[5][4] = 9;

  ck_assert_int_eq(13, get_shortest_path_between_vertices(&graph, 3, 5));

  s21_remove_graph(&graph);
}
END_TEST

START_TEST(deikstra_2) {
  Graph graph = {0};
  graph.size = 6;
  s21_create_graph(graph.size, &graph);

  graph.matrix[0][1] = 7;
  graph.matrix[0][2] = 9;
  graph.matrix[0][5] = 14;
  graph.matrix[1][2] = 10;
  graph.matrix[1][3] = 15;
  graph.matrix[2][3] = 11;
  graph.matrix[2][4] = 9;
  graph.matrix[2][5] = 2;
  graph.matrix[3][4] = 6;
  graph.matrix[4][5] = 9;

  graph.matrix[1][0] = 7;
  graph.matrix[2][0] = 9;
  graph.matrix[5][0] = 14;
  graph.matrix[2][1] = 10;
  graph.matrix[3][1] = 15;
  graph.matrix[3][2] = 11;
  graph.matrix[4][2] = 9;
  graph.matrix[5][2] = 2;
  graph.matrix[4][3] = 6;
  graph.matrix[5][4] = 9;

  ck_assert_int_eq(7, get_shortest_path_between_vertices(&graph, 0, 1));

  s21_remove_graph(&graph);
}
END_TEST

START_TEST(deikstra_3) {
  Graph graph = {0};
  graph.size = 9;
  s21_create_graph(graph.size, &graph);

  graph.matrix[0][1] = 2;
  graph.matrix[0][2] = 6;
  graph.matrix[0][3] = 8;
  graph.matrix[0][6] = 3;
  graph.matrix[1][2] = 9;
  graph.matrix[1][3] = 3;
  graph.matrix[1][5] = 4;
  graph.matrix[1][6] = 9;
  graph.matrix[2][3] = 7;
  graph.matrix[3][4] = 5;
  graph.matrix[3][5] = 5;
  graph.matrix[4][7] = 9;
  graph.matrix[5][7] = 6;
  graph.matrix[5][8] = 4;
  graph.matrix[7][8] = 1;

  graph.matrix[1][0] = 2;
  graph.matrix[2][0] = 6;
  graph.matrix[3][0] = 8;
  graph.matrix[6][0] = 3;
  graph.matrix[2][1] = 9;
  graph.matrix[3][1] = 3;
  graph.matrix[5][1] = 4;
  graph.matrix[6][1] = 9;
  graph.matrix[3][2] = 7;
  graph.matrix[4][3] = 5;
  graph.matrix[5][3] = 5;
  graph.matrix[7][4] = 9;
  graph.matrix[7][5] = 6;
  graph.matrix[8][5] = 4;
  graph.matrix[8][7] = 1;

  ck_assert_int_eq(2, get_shortest_path_between_vertices(&graph, 0, 1));

  s21_remove_graph(&graph);
}
END_TEST

START_TEST(deikstra_4) {
  Graph graph = {0};
  graph.size = 9;
  s21_create_graph(graph.size, &graph);

  graph.matrix[0][1] = 2;
  graph.matrix[0][2] = 6;
  graph.matrix[0][3] = 8;
  graph.matrix[0][6] = 3;
  graph.matrix[1][2] = 9;
  graph.matrix[1][3] = 3;
  graph.matrix[1][5] = 4;
  graph.matrix[1][6] = 9;
  graph.matrix[2][3] = 7;
  graph.matrix[3][4] = 5;
  graph.matrix[3][5] = 5;
  graph.matrix[4][7] = 9;
  graph.matrix[5][7] = 6;
  graph.matrix[5][8] = 4;
  graph.matrix[7][8] = 1;

  graph.matrix[1][0] = 2;
  graph.matrix[2][0] = 6;
  graph.matrix[3][0] = 8;
  graph.matrix[6][0] = 3;
  graph.matrix[2][1] = 9;
  graph.matrix[3][1] = 3;
  graph.matrix[5][1] = 4;
  graph.matrix[6][1] = 9;
  graph.matrix[3][2] = 7;
  graph.matrix[4][3] = 5;
  graph.matrix[5][3] = 5;
  graph.matrix[7][4] = 9;
  graph.matrix[7][5] = 6;
  graph.matrix[8][5] = 4;
  graph.matrix[8][7] = 1;

  ck_assert_int_eq(6, get_shortest_path_between_vertices(&graph, 0, 5));

  s21_remove_graph(&graph);
}
END_TEST

START_TEST(deikstra_5) {
  Graph graph = {0};
  graph.size = 9;
  s21_create_graph(graph.size, &graph);

  graph.matrix[0][1] = 2;
  graph.matrix[0][2] = 6;
  graph.matrix[0][3] = 8;
  graph.matrix[0][6] = 3;
  graph.matrix[1][2] = 9;
  graph.matrix[1][3] = 3;
  graph.matrix[1][5] = 4;
  graph.matrix[1][6] = 9;
  graph.matrix[2][3] = 7;
  graph.matrix[3][4] = 5;
  graph.matrix[3][5] = 5;
  graph.matrix[4][7] = 9;
  graph.matrix[5][7] = 6;
  graph.matrix[5][8] = 4;
  graph.matrix[7][8] = 1;

  graph.matrix[1][0] = 2;
  graph.matrix[2][0] = 6;
  graph.matrix[3][0] = 8;
  graph.matrix[6][0] = 3;
  graph.matrix[2][1] = 9;
  graph.matrix[3][1] = 3;
  graph.matrix[5][1] = 4;
  graph.matrix[6][1] = 9;
  graph.matrix[3][2] = 7;
  graph.matrix[4][3] = 5;
  graph.matrix[5][3] = 5;
  graph.matrix[7][4] = 9;
  graph.matrix[7][5] = 6;
  graph.matrix[8][5] = 4;
  graph.matrix[8][7] = 1;

  ck_assert_int_eq(0, get_shortest_path_between_vertices(&graph, 1, 1));

  s21_remove_graph(&graph);
}
END_TEST

START_TEST(deikstra_6) {
  Graph graph = {0};
  load_graph_from_file("../data-samples/true_graph_1.txt", &graph);
  ck_assert_int_eq(0, get_shortest_path_between_vertices(&graph, 0, 0));
  s21_remove_graph(&graph);
}
END_TEST

START_TEST(deikstra_7) {
  Graph graph = {0};
  load_graph_from_file("../data-samples/true_graph_2.txt", &graph);
  ck_assert_int_eq(0, get_shortest_path_between_vertices(&graph, 1, 1));
  s21_remove_graph(&graph);
}
END_TEST

START_TEST(deikstra_8) {
  Graph graph = {0};
  load_graph_from_file("../data-samples/true_graph_3.txt", &graph);
  ck_assert_int_eq(0, get_shortest_path_between_vertices(&graph, 1, 1));
  s21_remove_graph(&graph);
}
END_TEST

START_TEST(deikstra_9) {
  Graph graph = {0};
  s21_create_graph(6, &graph);
  graph.matrix[0][1] = 6;
  graph.matrix[0][2] = 2;
  graph.matrix[1][2] = 4;
  graph.matrix[1][3] = 2;
  graph.matrix[2][3] = 8;
  graph.matrix[3][4] = 1;
  graph.matrix[4][0] = 5;
  graph.matrix[4][1] = 3;
  graph.matrix[4][5] = 7;
  ck_assert_int_eq(16, get_shortest_path_between_vertices(&graph, 0, 5));
  s21_remove_graph(&graph);
}
END_TEST

START_TEST(deikstra_10) {
  Graph graph = {0};
  s21_create_graph(6, &graph);
  graph.matrix[0][1] = 6;
  graph.matrix[0][2] = 2;
  graph.matrix[1][2] = 4;
  graph.matrix[1][3] = 2;
  graph.matrix[2][3] = 8;
  graph.matrix[3][4] = 1;
  graph.matrix[4][0] = 5;
  graph.matrix[4][1] = 3;
  graph.matrix[4][5] = 7;
  ck_assert_int_eq(7, get_shortest_path_between_vertices(&graph, 4, 2));
  s21_remove_graph(&graph);
}
END_TEST

START_TEST(deikstra_11) {
  Graph graph = {0};
  s21_create_graph(6, &graph);
  graph.matrix[0][1] = 6;
  graph.matrix[0][2] = 2;
  graph.matrix[1][2] = 4;
  graph.matrix[1][3] = 2;
  graph.matrix[2][3] = 8;
  graph.matrix[3][4] = 1;
  graph.matrix[4][0] = 5;
  graph.matrix[4][1] = 3;
  graph.matrix[4][5] = 7;
  ck_assert_int_eq(5, get_shortest_path_between_vertices(&graph, 4, 3));
  s21_remove_graph(&graph);
}
END_TEST

START_TEST(deikstra_12) {
  Graph graph = {0};
  s21_create_graph(6, &graph);
  graph.matrix[0][1] = 6;
  graph.matrix[0][2] = 2;
  graph.matrix[1][2] = 4;
  graph.matrix[1][3] = 2;
  graph.matrix[2][3] = 8;
  graph.matrix[3][4] = 1;
  graph.matrix[4][0] = 5;
  graph.matrix[4][1] = 3;
  graph.matrix[4][5] = 7;
  ck_assert_int_eq(16, get_shortest_path_between_vertices(&graph, 2, 5));
  s21_remove_graph(&graph);
}
END_TEST

START_TEST(deikstra_13) {
  Graph graph = {0};
  s21_create_graph(6, &graph);
  graph.matrix[0][1] = 6;
  graph.matrix[0][2] = 2;
  graph.matrix[1][2] = 4;
  graph.matrix[1][3] = 2;
  graph.matrix[2][3] = 8;
  graph.matrix[3][4] = 1;
  graph.matrix[4][0] = 5;
  graph.matrix[4][1] = 3;
  graph.matrix[4][5] = 7;
  ck_assert_int_eq(6, get_shortest_path_between_vertices(&graph, 3, 0));
  s21_remove_graph(&graph);
}
END_TEST

Suite *get_shortest_path_between_vertices_cases(void) {
  Suite *s = suite_create("get_shortest_path_between_vertices_cases");
  TCase *tc = tcase_create("get_shortest_path_between_vertices");

  tcase_add_test(tc, deikstra_1);
  tcase_add_test(tc, deikstra_2);
  tcase_add_test(tc, deikstra_3);
  tcase_add_test(tc, deikstra_4);
  tcase_add_test(tc, deikstra_5);
  tcase_add_test(tc, deikstra_6);
  tcase_add_test(tc, deikstra_7);
  tcase_add_test(tc, deikstra_8);
  tcase_add_test(tc, deikstra_9);
  tcase_add_test(tc, deikstra_10);
  tcase_add_test(tc, deikstra_11);
  tcase_add_test(tc, deikstra_12);
  tcase_add_test(tc, deikstra_13);

  suite_add_tcase(s, tc);

  return s;
}

START_TEST(floid_1) {
  Graph graph = {0};
  graph.size = 9;
  s21_create_graph(graph.size, &graph);

  graph.matrix[0][1] = 2;
  graph.matrix[0][2] = 6;
  graph.matrix[0][3] = 8;
  graph.matrix[0][6] = 3;
  graph.matrix[1][2] = 9;
  graph.matrix[1][3] = 3;
  graph.matrix[1][5] = 4;
  graph.matrix[1][6] = 9;
  graph.matrix[2][3] = 7;
  graph.matrix[3][4] = 5;
  graph.matrix[3][5] = 5;
  graph.matrix[4][6] = 8;
  graph.matrix[4][7] = 9;
  graph.matrix[5][7] = 6;
  graph.matrix[5][8] = 4;
  graph.matrix[7][8] = 1;

  graph.matrix[1][0] = 2;
  graph.matrix[2][0] = 6;
  graph.matrix[3][0] = 8;
  graph.matrix[6][0] = 3;
  graph.matrix[2][1] = 9;
  graph.matrix[3][1] = 3;
  graph.matrix[5][1] = 4;
  graph.matrix[6][1] = 9;
  graph.matrix[3][2] = 7;
  graph.matrix[4][3] = 5;
  graph.matrix[5][3] = 5;
  graph.matrix[6][4] = 8;
  graph.matrix[7][4] = 9;
  graph.matrix[7][5] = 6;
  graph.matrix[8][5] = 4;
  graph.matrix[8][7] = 1;
  Graph check = {0};
  check.size = graph.size;
  s21_create_graph(graph.size, &check);

  check.matrix[0][1] = 2;
  check.matrix[0][2] = 6;
  check.matrix[0][3] = 5;
  check.matrix[0][4] = 10;
  check.matrix[0][5] = 6;
  check.matrix[0][6] = 3;
  check.matrix[0][7] = 11;
  check.matrix[0][8] = 10;
  check.matrix[1][2] = 8;
  check.matrix[1][3] = 3;
  check.matrix[1][4] = 8;
  check.matrix[1][5] = 4;
  check.matrix[1][6] = 5;
  check.matrix[1][7] = 9;
  check.matrix[1][8] = 8;
  check.matrix[2][3] = 7;
  check.matrix[2][4] = 12;
  check.matrix[2][5] = 12;
  check.matrix[2][6] = 9;
  check.matrix[2][7] = 17;
  check.matrix[2][8] = 16;
  check.matrix[3][4] = 5;
  check.matrix[3][5] = 5;
  check.matrix[3][6] = 8;
  check.matrix[3][7] = 10;
  check.matrix[3][8] = 9;
  check.matrix[4][5] = 10;
  check.matrix[4][6] = 8;
  check.matrix[4][7] = 9;
  check.matrix[4][8] = 10;
  check.matrix[5][6] = 9;
  check.matrix[5][7] = 5;
  check.matrix[5][8] = 4;
  check.matrix[6][7] = 14;
  check.matrix[6][8] = 13;
  check.matrix[7][8] = 1;

  check.matrix[1][0] = 2;
  check.matrix[2][0] = 6;
  check.matrix[3][0] = 5;
  check.matrix[4][0] = 10;
  check.matrix[5][0] = 6;
  check.matrix[6][0] = 3;
  check.matrix[7][0] = 11;
  check.matrix[8][0] = 10;
  check.matrix[2][1] = 8;
  check.matrix[3][1] = 3;
  check.matrix[4][1] = 8;
  check.matrix[5][1] = 4;
  check.matrix[6][1] = 5;
  check.matrix[7][1] = 9;
  check.matrix[8][1] = 8;
  check.matrix[3][2] = 7;
  check.matrix[4][2] = 12;
  check.matrix[5][2] = 12;
  check.matrix[6][2] = 9;
  check.matrix[7][2] = 17;
  check.matrix[8][2] = 16;
  check.matrix[4][3] = 5;
  check.matrix[5][3] = 5;
  check.matrix[6][3] = 8;
  check.matrix[7][3] = 10;
  check.matrix[8][3] = 9;
  check.matrix[5][4] = 10;
  check.matrix[6][4] = 8;
  check.matrix[7][4] = 9;
  check.matrix[8][4] = 10;
  check.matrix[6][5] = 9;
  check.matrix[7][5] = 5;
  check.matrix[8][5] = 4;
  check.matrix[7][6] = 14;
  check.matrix[8][6] = 13;
  check.matrix[8][7] = 1;

  Graph result = {0};
  s21_create_graph(graph.size, &result);
  result.size = graph.size;

  int error = get_shortest_paths_between_all_vertices(&graph, result.matrix);

  ck_assert_int_eq(0, error);
  for (int i = 0; i < graph.size; i++)
    for (int j = 0; j < graph.size; j++) {
      ck_assert_int_eq(check.matrix[i][j], result.matrix[i][j]);
    }

  s21_remove_graph(&graph);
  s21_remove_graph(&result);
  s21_remove_graph(&check);
}
END_TEST

START_TEST(floid_2) {
  Graph graph = {0};
  graph.size = 6;
  s21_create_graph(graph.size, &graph);

  graph.matrix[0][1] = 7;
  graph.matrix[0][2] = 9;
  graph.matrix[0][5] = 14;
  graph.matrix[1][2] = 10;
  graph.matrix[1][3] = 15;
  graph.matrix[2][3] = 11;
  graph.matrix[2][4] = 9;
  graph.matrix[2][5] = 2;
  graph.matrix[3][4] = 6;
  graph.matrix[4][5] = 9;

  graph.matrix[1][0] = 7;
  graph.matrix[2][0] = 9;
  graph.matrix[5][0] = 14;
  graph.matrix[2][1] = 10;
  graph.matrix[3][1] = 15;
  graph.matrix[3][2] = 11;
  graph.matrix[4][2] = 9;
  graph.matrix[5][2] = 2;
  graph.matrix[4][3] = 6;
  graph.matrix[5][4] = 9;

  Graph check = {0};
  check.size = graph.size;
  s21_create_graph(graph.size, &check);

  check.matrix[0][1] = 7;
  check.matrix[0][2] = 9;
  check.matrix[0][3] = 20;
  check.matrix[0][4] = 18;
  check.matrix[0][5] = 11;
  check.matrix[1][2] = 10;
  check.matrix[1][3] = 15;
  check.matrix[1][4] = 19;
  check.matrix[1][5] = 12;
  check.matrix[2][3] = 11;
  check.matrix[2][4] = 9;
  check.matrix[2][5] = 2;
  check.matrix[3][4] = 6;
  check.matrix[3][5] = 13;
  check.matrix[4][5] = 9;

  check.matrix[1][0] = 7;
  check.matrix[2][0] = 9;
  check.matrix[3][0] = 20;
  check.matrix[4][0] = 18;
  check.matrix[5][0] = 11;
  check.matrix[2][1] = 10;
  check.matrix[3][1] = 15;
  check.matrix[4][1] = 19;
  check.matrix[5][1] = 12;
  check.matrix[3][2] = 11;
  check.matrix[4][2] = 9;
  check.matrix[5][2] = 2;
  check.matrix[4][3] = 6;
  check.matrix[5][3] = 13;
  check.matrix[5][4] = 9;

  Graph result = {0};
  s21_create_graph(graph.size, &result);
  result.size = graph.size;

  int error = get_shortest_paths_between_all_vertices(&graph, result.matrix);

  ck_assert_int_eq(0, error);
  for (int i = 0; i < graph.size; i++)
    for (int j = 0; j < graph.size; j++)
      ck_assert_int_eq(check.matrix[i][j], result.matrix[i][j]);

  s21_remove_graph(&graph);
  s21_remove_graph(&result);
  s21_remove_graph(&check);
}
END_TEST

START_TEST(floid_3) {
  Graph graph = {0};
  graph.size = 4;
  s21_create_graph(graph.size, &graph);

  int error = get_shortest_paths_between_all_vertices(&graph, NULL);
  ck_assert_int_eq(1, error);

  s21_remove_graph(&graph);
}

START_TEST(floid_4) {
  Graph graph = {0};
  graph.size = 4;
  s21_create_graph(graph.size, &graph);

  int error = get_shortest_paths_between_all_vertices(NULL, graph.matrix);
  ck_assert_int_eq(1, error);

  s21_remove_graph(&graph);
}
END_TEST

START_TEST(floid_5) {
  Graph graph = {0};
  load_graph_from_file("../data-samples/true_graph_1.txt", &graph);
  Graph result = {0};
  s21_create_graph(graph.size, &result);

  int error = get_shortest_paths_between_all_vertices(&graph, result.matrix);
  ck_assert_int_eq(0, error);
  ck_assert_int_eq(0, result.matrix[0][0]);

  s21_remove_graph(&graph);
  s21_remove_graph(&result);
}
END_TEST

START_TEST(floid_6) {
  Graph graph = {0};
  load_graph_from_file("../data-samples/true_graph_2.txt", &graph);
  Graph result = {0};
  s21_create_graph(graph.size, &result);

  int error = get_shortest_paths_between_all_vertices(&graph, result.matrix);
  ck_assert_int_eq(0, error);
  ck_assert_int_eq(0, result.matrix[0][0]);
  ck_assert_int_eq(29, result.matrix[0][1]);
  ck_assert_int_eq(29, result.matrix[1][0]);
  ck_assert_int_eq(0, result.matrix[1][1]);

  s21_remove_graph(&graph);
  s21_remove_graph(&result);
}
END_TEST

START_TEST(floid_7) {
  Graph graph = {0};
  load_graph_from_file("../data-samples/true_graph_3.txt", &graph);
  Graph result = {0};
  s21_create_graph(graph.size, &result);

  int error = get_shortest_paths_between_all_vertices(&graph, result.matrix);
  ck_assert_int_eq(0, error);

  s21_remove_graph(&graph);
  s21_remove_graph(&result);
}
END_TEST

Suite *get_shortest_path_between_all_vertices_cases(void) {
  Suite *s = suite_create("get_shortest_path_between_all_vertices_cases");
  TCase *tc = tcase_create("get_shortest_path_between_all_vertices");

  tcase_add_test(tc, floid_1);
  tcase_add_test(tc, floid_2);
  tcase_add_test(tc, floid_3);
  tcase_add_test(tc, floid_4);
  tcase_add_test(tc, floid_5);
  tcase_add_test(tc, floid_6);
  tcase_add_test(tc, floid_7);

  suite_add_tcase(s, tc);

  return s;
}

START_TEST(prim_1) {
  Graph graph = {0};
  graph.size = 9;
  s21_create_graph(graph.size, &graph);

  graph.matrix[0][1] = 2;
  graph.matrix[0][2] = 6;
  graph.matrix[0][3] = 8;
  graph.matrix[0][6] = 3;
  graph.matrix[1][2] = 9;
  graph.matrix[1][3] = 3;
  graph.matrix[1][5] = 4;
  graph.matrix[1][6] = 9;
  graph.matrix[2][3] = 7;
  graph.matrix[3][4] = 5;
  graph.matrix[3][5] = 5;
  graph.matrix[4][7] = 9;
  graph.matrix[5][7] = 6;
  graph.matrix[5][8] = 4;
  graph.matrix[7][8] = 1;

  graph.matrix[1][0] = 2;
  graph.matrix[2][0] = 6;
  graph.matrix[3][0] = 8;
  graph.matrix[6][0] = 3;
  graph.matrix[2][1] = 9;
  graph.matrix[3][1] = 3;
  graph.matrix[5][1] = 4;
  graph.matrix[6][1] = 9;
  graph.matrix[3][2] = 7;
  graph.matrix[4][3] = 5;
  graph.matrix[5][3] = 5;
  graph.matrix[7][4] = 9;
  graph.matrix[7][5] = 6;
  graph.matrix[8][5] = 4;
  graph.matrix[8][7] = 1;

  Graph check = {0};
  check.size = graph.size;
  s21_create_graph(graph.size, &check);
  init_matrix(check.matrix, graph.size, -1);
  for (int i = 0; i < graph.size; i++) check.matrix[i][i] = 0;

  check.matrix[0][1] = 2;
  check.matrix[0][2] = 6;
  check.matrix[0][6] = 3;
  check.matrix[1][3] = 3;
  check.matrix[1][5] = 4;
  check.matrix[3][4] = 5;
  check.matrix[5][8] = 4;
  check.matrix[7][8] = 1;

  check.matrix[1][0] = 2;
  check.matrix[2][0] = 6;
  check.matrix[6][0] = 3;
  check.matrix[3][1] = 3;
  check.matrix[4][3] = 5;
  check.matrix[5][1] = 4;
  check.matrix[8][5] = 4;
  check.matrix[8][7] = 1;

  Graph result = {0};
  s21_create_graph(graph.size, &result);
  result.size = graph.size;

  int error = get_least_spanning_tree(&graph, result.matrix);
  ck_assert_int_eq(0, error);
  for (int i = 0; i < graph.size; i++)
    for (int j = 0; j < graph.size; j++)
      ck_assert_int_eq(check.matrix[i][j], result.matrix[i][j]);

  s21_remove_graph(&graph);
  s21_remove_graph(&result);
  s21_remove_graph(&check);
}
END_TEST

START_TEST(prim_2) {
  Graph graph = {0};
  graph.size = 6;
  s21_create_graph(graph.size, &graph);

  graph.matrix[0][1] = 7;
  graph.matrix[0][2] = 9;
  graph.matrix[0][5] = 14;
  graph.matrix[1][2] = 10;
  graph.matrix[1][3] = 15;
  graph.matrix[2][3] = 11;
  graph.matrix[2][4] = 9;
  graph.matrix[2][5] = 2;
  graph.matrix[3][4] = 6;
  graph.matrix[4][5] = 9;

  graph.matrix[1][0] = 7;
  graph.matrix[2][0] = 9;
  graph.matrix[5][0] = 14;
  graph.matrix[2][1] = 10;
  graph.matrix[3][1] = 15;
  graph.matrix[3][2] = 11;
  graph.matrix[4][2] = 9;
  graph.matrix[5][2] = 2;
  graph.matrix[4][3] = 6;
  graph.matrix[5][4] = 9;

  Graph check = {0};
  check.size = graph.size;
  s21_create_graph(graph.size, &check);
  init_matrix(check.matrix, graph.size, -1);
  for (int i = 0; i < graph.size; i++) check.matrix[i][i] = 0;

  check.matrix[0][1] = 7;
  check.matrix[0][2] = 9;
  check.matrix[2][4] = 9;
  check.matrix[2][5] = 2;
  check.matrix[3][4] = 6;

  check.matrix[1][0] = 7;
  check.matrix[2][0] = 9;
  check.matrix[4][2] = 9;
  check.matrix[5][2] = 2;
  check.matrix[4][3] = 6;

  Graph result = {0};
  s21_create_graph(graph.size, &result);
  result.size = graph.size;

  int error = get_least_spanning_tree(&graph, result.matrix);

  ck_assert_int_eq(0, error);
  for (int i = 0; i < graph.size; i++)
    for (int j = 0; j < graph.size; j++)
      ck_assert_int_eq(check.matrix[i][j], result.matrix[i][j]);

  s21_remove_graph(&graph);
  s21_remove_graph(&result);
  s21_remove_graph(&check);
}
END_TEST

START_TEST(prim_3) {
  Graph graph = {0};
  graph.size = 4;
  s21_create_graph(graph.size, &graph);

  int error = get_least_spanning_tree(&graph, NULL);
  ck_assert_int_eq(1, error);

  s21_remove_graph(&graph);
}
END_TEST

START_TEST(prim_4) {
  Graph graph = {0};
  graph.size = 4;
  s21_create_graph(graph.size, &graph);

  int error = get_least_spanning_tree(NULL, graph.matrix);
  ck_assert_int_eq(1, error);

  s21_remove_graph(&graph);
}
END_TEST

START_TEST(prim_5) {
  Graph graph = {0};
  load_graph_from_file("../data-samples/true_graph_1.txt", &graph);
  Graph result = {0};
  s21_create_graph(graph.size, &result);

  int error = get_least_spanning_tree(&graph, result.matrix);
  ck_assert_int_eq(0, error);
  ck_assert_int_eq(0, result.matrix[0][0]);

  s21_remove_graph(&graph);
  s21_remove_graph(&result);
}
END_TEST

START_TEST(prim_6) {
  Graph graph = {0};
  load_graph_from_file("../data-samples/true_graph_2.txt", &graph);
  Graph result = {0};
  s21_create_graph(graph.size, &result);

  int error = get_least_spanning_tree(&graph, result.matrix);
  ck_assert_int_eq(0, error);
  ck_assert_int_eq(0, result.matrix[0][0]);
  ck_assert_int_eq(29, result.matrix[0][1]);
  ck_assert_int_eq(29, result.matrix[1][0]);
  ck_assert_int_eq(0, result.matrix[1][1]);

  s21_remove_graph(&graph);
  s21_remove_graph(&result);
}
END_TEST

START_TEST(prim_7) {
  Graph graph = {0};
  load_graph_from_file("../data-samples/true_graph_3.txt", &graph);
  Graph result = {0};
  s21_create_graph(graph.size, &result);

  int error = get_least_spanning_tree(&graph, result.matrix);
  ck_assert_int_eq(0, error);

  s21_remove_graph(&graph);
  s21_remove_graph(&result);
}
END_TEST

Suite *get_least_spanning_tree_cases(void) {
  Suite *s = suite_create("get_least_spanning_tree_cases");
  TCase *tc = tcase_create("get_least_spanning_tree");

  tcase_add_test(tc, prim_1);
  tcase_add_test(tc, prim_2);
  tcase_add_test(tc, prim_3);
  tcase_add_test(tc, prim_4);
  tcase_add_test(tc, prim_5);
  tcase_add_test(tc, prim_6);
  tcase_add_test(tc, prim_7);

  suite_add_tcase(s, tc);

  return s;
}