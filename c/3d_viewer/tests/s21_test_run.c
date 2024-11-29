#include "s21_tests.h"

int main() {
  int failed = 0;
  int total = 0;

  Suite *s[] = {test_parce(), NULL};
  Suite *s1[] = {test_matrix(), NULL};

  for (int i = 0; s[i] != NULL; i++) {
    SRunner *sr = srunner_create(s[i]);
    srunner_run_all(sr, CK_NORMAL);
    failed += srunner_ntests_failed(sr);
    total += srunner_ntests_run(sr);
    srunner_free(sr);
  }
  for (int i = 0; s1[i] != NULL; i++) {
    SRunner *sr = srunner_create(s1[i]);
    srunner_run_all(sr, CK_NORMAL);
    failed += srunner_ntests_failed(sr);
    total += srunner_ntests_run(sr);
    srunner_free(sr);
  }
  printf("\033[41m FAILED : %d \033[0m\n", failed);
  printf("\033[42m SUCCESS: %d \033[0m\n", total - failed);
  printf("\033[42m TOTAL  :%d \033[0m\n", total);
  return 0;
}