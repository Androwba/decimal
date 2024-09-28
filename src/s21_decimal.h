
#ifndef SRC_S21_DECIMAL_H_
#define SRC_S21_DECIMAL_H_

#include <math.h>
#define s21_NULL (void *)0

typedef struct {
  int bits[4];
} s21_decimal;

int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

// custom
int balance(s21_decimal *a, s21_decimal *b);
int bank_rnd(s21_decimal *a, int n);
int shift(s21_decimal *a, int n);

int add_helper(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int add_check(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int sub_helper(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int mul_helper(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int int_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int mod_helper(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

typedef enum { false, true } bool;

int s21_is_less(s21_decimal a, s21_decimal b);
int less_helper(s21_decimal a, s21_decimal b);
int s21_is_less_or_equal(s21_decimal a, s21_decimal b);
int s21_is_greater(s21_decimal a, s21_decimal b);
int s21_is_greater_or_equal(s21_decimal a, s21_decimal b);
int s21_is_equal(s21_decimal a, s21_decimal b);
int equal_helper(s21_decimal a, s21_decimal b);
int s21_is_not_equal(s21_decimal a, s21_decimal b);

int s21_from_decimal_to_float(s21_decimal src, float *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_int_to_decimal(int src, s21_decimal *dst);
void change_endian(s21_decimal *my_struct);
void set_null(s21_decimal *my_struct);

enum { OK = 0, CONVERTION_ERROR = 1, BIG_VALUE = 1, SMALL_VALUE, DIV_ZERO };
typedef enum { POSITIVE = 0, NEGATIVE = 1 } sign;
#define BITS_IN_INT 32
#define BITS_COUNT 3
#define ALL_BIT (BITS_IN_INT * BITS_COUNT)

#define DECIMAL_INFO 3
#define START_EXP_BIT 16
#define END_EXP_BIT 23
#define SIGN_BIT 31

#define MAX_EXPONENT 28

#define _2(bit) (1 << bit)

sign get_sign(s21_decimal a);
int set_sign(s21_decimal *a, sign new_sign);

// Work with exponent
int get_exponent(s21_decimal a);
int set_exponent(s21_decimal *a, int new_exponent);

void print_decimal(s21_decimal a);
void d_print_decimal(s21_decimal a);

// Work with bit
int on_bit(int bits, int bit);
int off_bit(int bits, int bit);
int is_bit(int bits, int bit);
int get_bit(int bits, int bit);
int get_gbit(s21_decimal a, int gbit);
int set_bit(int bits, int bit, int new_bit);
int get_bits(s21_decimal a, int global_ind);
int *pointer_get_bits(s21_decimal *a, int global_ind);
int is_zero(s21_decimal a);
void s21_set_mask(s21_decimal *number, int sign);

// Shift decimal
int left_shift(s21_decimal *a);
int right_shift(s21_decimal *a);

s21_decimal init_zero_decimal();
s21_decimal init_random_decimal();

#endif  // SRC_S21_DECIMAL_H_
