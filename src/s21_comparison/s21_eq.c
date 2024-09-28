#include "../s21_decimal.h"

int equal_helper(s21_decimal a, s21_decimal b) {
  bool res = get_sign(a) == get_sign(b);
  bool alt_res = is_zero(a) && is_zero(b);
  res = res && get_exponent(a) == get_exponent(b);
  res = res && a.bits[0] == b.bits[0];
  res = res && a.bits[1] == b.bits[1];
  res = res && a.bits[2] == b.bits[2];

  return res || alt_res;
}

int s21_is_equal(s21_decimal a, s21_decimal b) {
  balance(&a, &b);
  return equal_helper(a, b);
}
