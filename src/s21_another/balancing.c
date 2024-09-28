#include "../s21_decimal.h"

int shift(s21_decimal *a, int n) {
  /// Multiply the number by 10 and increase the exponent by 1 thereby shifting
  /// the number to the left
  s21_decimal ten;
  s21_from_int_to_decimal(10, &ten);

  s21_decimal tmp_result = init_zero_decimal();

  int exp = get_exponent(*a);
  int status = exp == MAX_EXPONENT;

  while (!status && n--) {
    status = mul_helper(*a, ten, &tmp_result);
    if (!status) {
      *a = tmp_result;
      tmp_result = init_zero_decimal();
      status = (++exp == MAX_EXPONENT);
    }
  }

  set_exponent(a, exp);
  return status;
}

int balance(s21_decimal *a, s21_decimal *b) {
  int diff = get_exponent(*a) - get_exponent(*b);

  if (diff) {
    if (diff > 0)
      shift(b, diff);
    else
      shift(a, -diff);

    diff = get_exponent(*a) - get_exponent(*b);
    if (diff) {
      if (diff > 0)
        bank_rnd(a, diff);
      else
        bank_rnd(b, -diff);
    }
  }

  return OK;
}
