#include "s21_calculate/s21_calculate.h"
#include "s21_smart_calc.h"
#include "s21_structs/s21_structs.h"

void skip_spaces(const char** str) {
  while (**str == ' ') {
    ++(*str);
  }
}

int is_lex(const char* str, const char* lex, size_t* shift) {
  int code = SUCCESS;
  const char* start = lex;

  for (; *str != '\0' && *str == *lex; ++str, ++lex)
    ;

  if (*lex != '\0') {
    code = FAILURE;
  }

  *shift = lex - start;

  return code;
}

Token get_lex(const char* str, size_t* shift) {
  Token res = UNRECOGNIZED;

  if (is_lex(str, "(", shift) == SUCCESS) {
    res = OPENING_BRACKET;
  } else if (is_lex(str, ")", shift) == SUCCESS) {
    res = CLOSING_BRACKET;
  } else if (is_lex(str, "+", shift) == SUCCESS) {
    res = ADDITION;
  } else if (is_lex(str, "-", shift) == SUCCESS) {
    res = SUBTRACTION;
  } else if (is_lex(str, "*", shift) == SUCCESS) {
    res = MULTIPLICATION;
  } else if (is_lex(str, "/", shift) == SUCCESS) {
    res = DIVISION;
  } else if (is_lex(str, "^", shift) == SUCCESS) {
    res = POWER;
  } else if (is_lex(str, "mod", shift) == SUCCESS) {
    res = MODULUS;
  } else if (is_lex(str, "cos", shift) == SUCCESS) {
    res = COS;
  } else if (is_lex(str, "sin", shift) == SUCCESS) {
    res = SIN;
  } else if (is_lex(str, "tan", shift) == SUCCESS) {
    res = TAN;
  } else if (is_lex(str, "acos", shift) == SUCCESS) {
    res = ACOS;
  } else if (is_lex(str, "asin", shift) == SUCCESS) {
    res = ASIN;
  } else if (is_lex(str, "atan", shift) == SUCCESS) {
    res = ATAN;
  } else if (is_lex(str, "sqrt", shift) == SUCCESS) {
    res = SQRT;
  } else if (is_lex(str, "ln", shift) == SUCCESS) {
    res = LN;
  } else if (is_lex(str, "log", shift) == SUCCESS) {
    res = LOG;
  } else if (is_lex(str, "x", shift) == SUCCESS) {
    res = X;
  }

  return res;
}

int parse_to_tokens(const char* str, queue** res) {
  *res = NULL;
  int code = str != NULL ? SUCCESS : FAILURE;

  Token previous = UNRECOGNIZED;

  for (const char* str_cp = str; code == SUCCESS && *str_cp != '\0';) {
    skip_spaces(&str_cp);
    size_t shift = 0;
    Token next = get_lex(str_cp, &shift);
    if (next != UNRECOGNIZED) {
      if ((next == SUBTRACTION || next == ADDITION) &&
          (previous == OPENING_BRACKET || str == str_cp)) {
        code = add(res, next == SUBTRACTION ? UNARY_MINUS : UNARY_PLUS, 0);
      } else {
        code = add(res, next, 0);
      }
      previous = next;
    } else {
      char* value_end;
      double value = strtod(str_cp, &value_end);
      if (str_cp == value_end) {
        code = FAILURE;
      } else {
        shift = value_end - str_cp;
        previous = UNRECOGNIZED;
        code = add(res, VALUE, value);
      }
    }

    if (code == SUCCESS) {
      str_cp += shift;
      skip_spaces(&str_cp);
    }
  }

  if (code != SUCCESS) {
    free_queue(res);
  }

  return code;
}