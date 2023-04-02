#include "tests/s21_tests.h"

START_TEST(rpn_calc_1) {
  queue *res;
  char *str = "5 + 6";
  int code = parse_to_tokens(str, &res);

  ck_assert_int_eq(code, SUCCESS);
  queue *rpn;
  rpn = make_rpn(res, &code);
  ck_assert_int_eq(code, SUCCESS);
  double dres = calc_rpn(rpn, 0, &code);
  ck_assert_int_eq(code, SUCCESS);

  ck_assert_double_eq_tol(dres, 11, EPS);

  free_queue(&res);
  free_queue(&rpn);
}
END_TEST

START_TEST(rpn_calc_2) {
  queue *res;
  char *str = "5 * 10 / 4";
  int code = parse_to_tokens(str, &res);

  ck_assert_int_eq(code, SUCCESS);
  queue *rpn;
  rpn = make_rpn(res, &code);
  ck_assert_int_eq(code, SUCCESS);
  double dres = calc_rpn(rpn, 0, &code);
  ck_assert_int_eq(code, SUCCESS);

  ck_assert_double_eq_tol(dres, 12.5, EPS);

  free_queue(&res);
  free_queue(&rpn);
}
END_TEST

START_TEST(rpn_calc_3) {
  queue *res;
  char *str = "sin(asin(1))";
  int code = parse_to_tokens(str, &res);

  ck_assert_int_eq(code, SUCCESS);
  queue *rpn;
  rpn = make_rpn(res, &code);
  ck_assert_int_eq(code, SUCCESS);
  double dres = calc_rpn(rpn, 0, &code);
  ck_assert_int_eq(code, SUCCESS);

  ck_assert_double_eq_tol(dres, sin(asin(1)), EPS);

  free_queue(&res);
  free_queue(&rpn);
}
END_TEST

START_TEST(rpn_calc_4) {
  queue *res;
  char *str = "sin(asin(sin(asin(sin(asin(sin(asin(1))))))))";
  int code = parse_to_tokens(str, &res);

  ck_assert_int_eq(code, SUCCESS);
  queue *rpn;
  rpn = make_rpn(res, &code);
  ck_assert_int_eq(code, SUCCESS);
  double dres = calc_rpn(rpn, 0, &code);
  ck_assert_int_eq(code, SUCCESS);

  ck_assert_double_eq_tol(dres, 1, EPS);

  free_queue(&res);
  free_queue(&rpn);
}
END_TEST

START_TEST(rpn_calc_5) {
  queue *res;
  char *str = "log(10 ^ 7)      ";
  int code = parse_to_tokens(str, &res);

  ck_assert_int_eq(code, SUCCESS);
  queue *rpn;
  rpn = make_rpn(res, &code);
  ck_assert_int_eq(code, SUCCESS);
  double dres = calc_rpn(rpn, 0, &code);
  ck_assert_int_eq(code, SUCCESS);

  ck_assert_double_eq_tol(dres, log10(pow(10, 7)), EPS);

  free_queue(&res);
  free_queue(&rpn);
}
END_TEST

START_TEST(rpn_calc_6) {
  queue *res;
  char *str = "cos(5)";
  int code = parse_to_tokens(str, &res);

  ck_assert_int_eq(code, SUCCESS);
  queue *rpn;
  rpn = make_rpn(res, &code);
  ck_assert_int_eq(code, SUCCESS);
  double dres = calc_rpn(rpn, 0, &code);
  ck_assert_int_eq(code, SUCCESS);

  ck_assert_double_eq_tol(dres, cos(5), EPS);

  free_queue(&res);
  free_queue(&rpn);
}
END_TEST

START_TEST(rpn_calc_7) {
  queue *res;
  char *str = "-3 * (+5)";
  int code = parse_to_tokens(str, &res);

  ck_assert_int_eq(code, SUCCESS);
  queue *rpn;
  rpn = make_rpn(res, &code);
  ck_assert_int_eq(code, SUCCESS);
  double dres = calc_rpn(rpn, 0, &code);
  ck_assert_int_eq(code, SUCCESS);

  ck_assert_double_eq_tol(dres, -3 * (+5), EPS);

  free_queue(&res);
  free_queue(&rpn);
}
END_TEST

START_TEST(rpn_calc_8) {
  queue *res;
  char *str = "1 + 2 - 3 * 4 / 5 ^ 6";
  int code = parse_to_tokens(str, &res);

  ck_assert_int_eq(code, SUCCESS);
  queue *rpn;
  rpn = make_rpn(res, &code);
  ck_assert_int_eq(code, SUCCESS);
  double dres = calc_rpn(rpn, 0, &code);
  ck_assert_int_eq(code, SUCCESS);

  ck_assert_double_eq_tol(dres, 1 + 2 - 3 * 4 / pow(5, 6), EPS);

  free_queue(&res);
  free_queue(&rpn);
}
END_TEST

START_TEST(rpn_calc_10) {
  queue *res;
  char *str = "5 mod 2";
  int code = parse_to_tokens(str, &res);

  ck_assert_int_eq(code, SUCCESS);
  queue *rpn;
  rpn = make_rpn(res, &code);
  ck_assert_int_eq(code, SUCCESS);
  double dres = calc_rpn(rpn, 0, &code);
  ck_assert_int_eq(code, SUCCESS);

  ck_assert_double_eq_tol(dres, 5 % 2, EPS);

  free_queue(&res);
  free_queue(&rpn);
}
END_TEST

START_TEST(rpn_calc_11) {
  queue *res;
  char *str = "tan(sqrt(3) / 2)";
  int code = parse_to_tokens(str, &res);

  ck_assert_int_eq(code, SUCCESS);
  queue *rpn;
  rpn = make_rpn(res, &code);
  ck_assert_int_eq(code, SUCCESS);
  double dres = calc_rpn(rpn, 0, &code);
  ck_assert_int_eq(code, SUCCESS);

  ck_assert_double_eq_tol(dres, tan(sqrt(3) / 2), EPS);

  free_queue(&res);
  free_queue(&rpn);
}
END_TEST

START_TEST(rpn_calc_12) {
  queue *res;
  char *str = "5 ^ 6";
  int code = parse_to_tokens(str, &res);

  ck_assert_int_eq(code, SUCCESS);
  queue *rpn;
  rpn = make_rpn(res, &code);
  ck_assert_int_eq(code, SUCCESS);
  double dres = calc_rpn(rpn, 0, &code);
  ck_assert_int_eq(code, SUCCESS);

  ck_assert_double_eq_tol(dres, pow(5, 6), EPS);

  free_queue(&res);
  free_queue(&rpn);
}
END_TEST

START_TEST(rpn_calc_13) {
  queue *res;
  char *str = "-3 + (-(3-5)) / 2";
  int code = parse_to_tokens(str, &res);

  ck_assert_int_eq(code, SUCCESS);
  queue *rpn;
  rpn = make_rpn(res, &code);
  ck_assert_int_eq(code, SUCCESS);
  double dres = calc_rpn(rpn, 0, &code);
  ck_assert_int_eq(code, SUCCESS);

  ck_assert_double_eq_tol(dres, -3 + (-(3 - 5)) / 2, EPS);

  free_queue(&res);
  free_queue(&rpn);
}
END_TEST

START_TEST(rpn_calc_14) {
  queue *res;
  char *str = "sin(acos(1/2))";
  int code = parse_to_tokens(str, &res);

  ck_assert_int_eq(code, SUCCESS);
  queue *rpn;
  rpn = make_rpn(res, &code);
  ck_assert_int_eq(code, SUCCESS);
  double dres = calc_rpn(rpn, 0, &code);
  ck_assert_int_eq(code, SUCCESS);

  ck_assert_double_eq_tol(dres, sin(acos(1. / 2)), EPS);

  free_queue(&res);
  free_queue(&rpn);
}
END_TEST

START_TEST(rpn_calc_15) {
  queue *res;
  char *str = "log(100)/log(10)";
  int code = parse_to_tokens(str, &res);

  ck_assert_int_eq(code, SUCCESS);
  queue *rpn;
  rpn = make_rpn(res, &code);
  ck_assert_int_eq(code, SUCCESS);
  double dres = calc_rpn(rpn, 0, &code);
  ck_assert_int_eq(code, SUCCESS);

  ck_assert_double_eq_tol(dres, log(100) / log(10), EPS);

  free_queue(&res);
  free_queue(&rpn);
}
END_TEST

START_TEST(wr_rpn_calc_1) {
  queue *res;
  char *str = "3 + 5 5";
  int code = parse_to_tokens(str, &res);

  ck_assert_int_eq(code, SUCCESS);
  queue *rpn;
  rpn = make_rpn(res, &code);
  ck_assert_int_eq(code, SUCCESS);
  calc_rpn(rpn, 0, &code);
  ck_assert_int_eq(code, FAILURE);

  free_queue(&res);
}
END_TEST

Suite *rpn_calc_suite() {
  Suite *suite = suite_create("prn_calc_suite");
  TCase *tcase = tcase_create("prn_calc_case");

  tcase_add_test(tcase, rpn_calc_1);
  tcase_add_test(tcase, rpn_calc_2);
  tcase_add_test(tcase, rpn_calc_3);
  tcase_add_test(tcase, rpn_calc_4);
  tcase_add_test(tcase, rpn_calc_5);
  tcase_add_test(tcase, rpn_calc_6);
  tcase_add_test(tcase, rpn_calc_7);
  tcase_add_test(tcase, rpn_calc_8);
  tcase_add_test(tcase, rpn_calc_10);
  tcase_add_test(tcase, rpn_calc_11);
  tcase_add_test(tcase, rpn_calc_12);
  tcase_add_test(tcase, rpn_calc_13);
  tcase_add_test(tcase, rpn_calc_14);
  tcase_add_test(tcase, rpn_calc_15);

  tcase_add_test(tcase, wr_rpn_calc_1);

  suite_add_tcase(suite, tcase);
  return suite;
}