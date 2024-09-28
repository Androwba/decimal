#include "../s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  *result = value;

  s21_decimal one, mod_res;
  s21_from_int_to_decimal(1, &one);

  s21_mod(*result, one, &mod_res);

  balance(&mod_res, result);

  sub_helper(*result, mod_res, result);

  bank_rnd(result, get_exponent(*result));

  set_sign(result, get_sign(value));
  return OK;
}
