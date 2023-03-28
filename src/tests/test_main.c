#include "tests/s21_tests.h"

int main() {
  Suite* suites[] = {
      parser_suite(),
  };

  for (int i = 0; i < 1; ++i) {
    SRunner* srunner = srunner_create(suites[i]);
    srunner_run_all(srunner, CK_NORMAL);
    srunner_free(srunner);
  }

  return 0;
}