#ifndef SRC_S21_MATRIX_H_
#define SRC_S21_MATRIX_H_
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 1
#define FAILURE 0

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;
int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);
int s21_eq_matrix(matrix_t *A, matrix_t *B);
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_transpose(matrix_t *A, matrix_t *result);
int s21_determinant(matrix_t *A, double *result);
int s21_calc_complements(matrix_t *A, matrix_t *result);
int s21_inverse_matrix(matrix_t *A, matrix_t *result);
double s21_pow(int i, int j);
void calc_complements(matrix_t *A, matrix_t *result, int size);
double determinant(double **matrix, int size);
void free_matrix(double **matrix, int rows);
void small_matrix(double **matrix, double **new_matrix, int size, int row,
                  int columnn);
void transpose(matrix_t *A, matrix_t *result);
void mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
double matrix_mult_elem(matrix_t *A, matrix_t *B, int r, int c);
int mult_matrix_size(matrix_t *A, matrix_t *B);
int check_matrix(matrix_t *A);
double **matrix_init(int rows, int columns);
int eq_matrix_size(matrix_t *A, matrix_t *B);
int eq_matrix_value(matrix_t *A, matrix_t *B);
void sum_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result, char type);

#endif  // SRC_S21_MATRIX_H_