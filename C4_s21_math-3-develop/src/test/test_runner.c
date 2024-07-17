#include "test_runner.h"

int main(void) {
  Suite *array_tests[] = {s21_fabs_cases(), s21_exp_cases(),  s21_floor_cases(),
                          s21_abs_cases(),  s21_acos_cases(), s21_asin_cases(),
                          s21_sin_cases(),  s21_sqrt_cases(), s21_tan_cases(),
                          s21_ceil_cases(), s21_cos_cases(),  s21_atan_cases(),
                          s21_log_cases(),  s21_pow_cases(),  s21_fmod_cases()};

  int size = 15;

  for (int i = 0; i < size; i++) {
    printf("%s\n", SEP);
    printf("TEST NUMBER: %d \n", i + 1);

    SRunner *runner = srunner_create(array_tests[i]);

    srunner_set_fork_status(runner, CK_NOFORK);
    srunner_run_all(runner, CK_NORMAL);
    srunner_free(runner);
  }

  return 0;
}
