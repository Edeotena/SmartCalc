#include "tests/s21_tests.h"

START_TEST(draw_1) {
  char *str = "cos(0)";
  int code = SUCCESS;
  queue *lex, *rpn;
  code = parse_to_tokens(str, &lex);
  ck_assert_int_eq(code, SUCCESS);
  rpn = make_rpn(lex, &code);
  ck_assert_int_eq(code, SUCCESS);
  double *values = get_values(rpn, 1, 1, 1);
  ck_assert_double_eq_tol(*values, cos(0), EPS);
  free(values);
  free_queue(&rpn);
  free_queue(&lex);
}
END_TEST

Suite *draw_suite() {
  Suite *suite = suite_create("draw_suite");
  TCase *tcase = tcase_create("draw_case");

  tcase_add_test(tcase, draw_1);

  suite_add_tcase(suite, tcase);
  return suite;
}