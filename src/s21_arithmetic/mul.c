#include "../s21_decimal.h"

int mul_helper(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  *result = init_zero_decimal();
  int res = mul_helper(value_1, value_2, result);
  while (res && (get_exponent(value_1) || get_exponent(value_2))) {
    int exp_check = less_helper(value_1, value_2) ? get_exponent(value_2)
                                                  : get_exponent(value_1);
    s21_decimal *value = less_helper(value_1, value_2) ? &value_2 : &value_1;
    s21_decimal *alt_value =
        !less_helper(value_1, value_2) ? &value_2 : &value_1;
    if (exp_check)
      bank_rnd(value, 1);
    else
      bank_rnd(alt_value, 1);
    res = mul_helper(value_1, value_2, result);
  }
  int exp = get_exponent(value_1) + get_exponent(value_2);
  if (exp < 29)
    set_exponent(result, exp);
  else
    *result = init_zero_decimal();
  return res;
}

int mul_helper(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int status = 0;
  s21_decimal tmp = *result;
  set_sign(&tmp, get_sign(value_1) ^ get_sign(value_2));

  while (!is_zero(value_2) && !status) {
    if (get_gbit(value_2, 0)) {
      status = add_helper(tmp, value_1, &tmp);
    }
    if (get_gbit(value_1, ALL_BIT - 1)) status = 1;
    right_shift(&value_2);
    left_shift(&value_1);
  }

  if (!status)
    *result = tmp;
  else if (get_sign(value_1) ^ get_sign(value_2))
    ++status;
  return status;
}
