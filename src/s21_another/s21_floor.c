#include "../s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  s21_decimal one, mod_res;
  s21_from_int_to_decimal(1, &one);

  s21_mod(value, one, &mod_res);
  s21_truncate(value, result);
  if (get_sign(value) && !is_zero(value) && !is_zero(mod_res)) {
    add_helper(*result, one, result);
  }

  return OK;
}
