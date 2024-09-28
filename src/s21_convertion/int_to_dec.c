#include "../s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int exit_status = OK;

  if (dst == s21_NULL) {
    exit_status = CONVERTION_ERROR;
  } else {
    dst->bits[0] = 0;
    dst->bits[1] = 0;
    dst->bits[2] = 0;
    dst->bits[3] = 0;

    if (src < 0) {
      src *= -1;
      s21_set_mask(dst, 1);
    }

    dst->bits[0] = src;
  }

  return exit_status;
}
