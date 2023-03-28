#include "s21_tests.h"

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
  for (int i = 0; i < size; ++i, cp = cp->next) {
    ck_assert_int_eq(cp->op, tokens[i]);
  }

  free_queue(&res);
}
END_TEST

Suite *parser_suite() {
  Suite *suite = suite_create("parser_suite");
  TCase *tcase = tcase_create("parser_suite");

  tcase_add_test(tcase, parser_1);

  suite_add_tcase(suite, tcase);
  return suite;
}