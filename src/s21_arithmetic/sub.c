#include "../s21_decimal.h"

int sub_helper(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  *result = init_zero_decimal();
  balance(&value_1, &value_2);
  int exp = get_exponent(value_1);
  set_exponent(result, exp);

  int sign_1 = get_sign(value_1);
  int sign_2 = get_sign(value_2);

  int status = 0;
  if (sign_1 && sign_2) {
    set_sign(&value_1, !sign_1);
    set_sign(&value_2, !sign_2);
    status = s21_sub(value_2, value_1, result);
  } else if (sign_1) {
    set_sign(&value_1, !sign_1);
    status = add_helper(value_1, value_2, result);
    set_sign(result, NEGATIVE);
  } else if (sign_2) {
    set_sign(&value_2, !sign_2);
    status = add_helper(value_1, value_2, result);
  } else if (s21_is_less(value_1, value_2)) {
    status = sub_helper(value_2, value_1, result);
    set_sign(result, NEGATIVE);
  } else {
    sub_helper(value_1, value_2, result);
  }
  return status;
}

int sub_helper(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int status = 0;

  for (int i = 0; i < ALL_BIT; i++) {
    int a = get_gbit(value_1, i);
    int b = get_gbit(value_2, i);
    if (b && !a) {
      int j;
      for (j = i + 1; !get_gbit(value_1, j) && j < ALL_BIT;) j++;

      *pointer_get_bits(&value_1, j) = set_bit(get_bits(value_1, j), j, 0);
      for (j--; j != i; j--) {
        *pointer_get_bits(&value_1, j) = set_bit(get_bits(value_1, j), j, 1);
      }
      *pointer_get_bits(result, i) = set_bit(get_bits(*result, i), i, 1);
    } else {
      *pointer_get_bits(result, i) = set_bit(get_bits(*result, i), i, a ^ b);
    }
  }
  return status;
}
