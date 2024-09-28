#include "../s21_decimal.h"

s21_decimal fmod_core(s21_decimal value_1, s21_decimal value_2) {
  s21_decimal divcopy = value_2;
  s21_decimal res;
  s21_decimal temp = {{0, 0, 0, 0}};
  if (equal_helper(value_1, value_2))
    return temp;
  else if (less_helper(value_1, value_2))
    return value_1;

  while ((less_helper(value_2, value_1) || equal_helper(value_2, value_1)) &&
         !get_gbit(value_2, ALL_BIT - 1)) {
    left_shift(&value_2);
  }
  if (less_helper(value_1, value_2)) {
    right_shift(&value_2);
  }
  sub_helper(value_1, value_2, &temp);
  res = fmod_core(temp, divcopy);
  return res;
}

int mod_helper(s21_decimal value_1, s21_decimal value_2, s21_decimal* result) {
  if (is_zero(value_2)) return DIV_ZERO;
  result->bits[0] = 0;
  result->bits[1] = 0;
  result->bits[2] = 0;
  result->bits[3] = 0;
  int sign = get_sign(value_1);
  set_sign(&value_1, 0);
  set_sign(&value_2, 0);
  *result = fmod_core(value_1, value_2);
  set_sign(result, sign);
  return 0;
}

int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal* result) {
  balance(&value_1, &value_2);
  int exp = get_exponent(value_1);
  int res = mod_helper(value_1, value_2, result);
  set_exponent(result, exp);
  return res;
}
