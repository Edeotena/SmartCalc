#include "tests/s21_tests.h"

START_TEST(parser_1) {
  int size = 7;
  const Token tokens[] = {SIN,
                          OPENING_BRACKET,
                          COS,
                          OPENING_BRACKET,
                          X,
                          CLOSING_BRACKET,
                          CLOSING_BRACKET};
  queue *res = NULL, *cp = NULL;
  char *str = "sin(cos(x))";
  int code = parse_to_tokens(str, &res);
  cp = res;

  ck_assert_int_eq(code, SUCCESS);
  for (int i = 0; i < size; ++i) {
    Token tk = UNRECOGNIZED;
    double val = 0;
    get(&cp, &tk, &val);
    ck_assert_int_eq(tk, tokens[i]);
  }

  free_queue(&res);
}
END_TEST

START_TEST(parser_2) {
  queue *res = NULL;
  char *str = "sin(coc)";
  int code = parse_to_tokens(str, &res);
  ck_assert_int_eq(code, FAILURE);
  ck_assert_ptr_eq(res, NULL);
}
END_TEST

START_TEST(parser_3) {
  int size = 14;
  const Token tokens[] = {SIN,
                          OPENING_BRACKET,
                          COS,
                          OPENING_BRACKET,
                          X,
                          MULTIPLICATION,
                          SIN,
                          OPENING_BRACKET,
                          COS,
                          OPENING_BRACKET,
                          X,
                          CLOSING_BRACKET,
                          CLOSING_BRACKET,
                          CLOSING_BRACKET};
  queue *res = NULL, *cp = NULL;
  char *str = "sin    (cos   ( x   * sin( cos (  x ))  )";
  int code = parse_to_tokens(str, &res);
  cp = res;

  ck_assert_int_eq(code, SUCCESS);
  for (int i = 0; i < size; ++i) {
    Token tk = UNRECOGNIZED;
    double val = 0;
    get(&cp, &tk, &val);
    ck_assert_int_eq(tk, tokens[i]);
  }

  free_queue(&res);
}
END_TEST

START_TEST(wr_parser_1) {
  queue *res = NULL;
  char *str = "sin    (cos   ( a   * sin( cos (  x ))  )";
  int code = parse_to_tokens(str, &res);

  ck_assert_int_eq(code, FAILURE);

  // free_queue(&res);
}
END_TEST

Suite *parser_suite() {
  Suite *suite = suite_create("parser_suite");
  TCase *tcase = tcase_create("parser_case");

  tcase_add_test(tcase, parser_1);
  tcase_add_test(tcase, parser_2);
  tcase_add_test(tcase, parser_3);

  tcase_add_test(tcase, wr_parser_1);

  suite_add_tcase(suite, tcase);
  return suite;
}