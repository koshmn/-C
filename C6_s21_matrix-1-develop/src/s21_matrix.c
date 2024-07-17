#include "s21_matrix.h"

double **matrix_init(int rows, int columns) {
  double **matrix = (double **)malloc(sizeof(double *) * rows);
  for (int r = 0; r < rows; r++) {
    matrix[r] = (double *)malloc(sizeof(double) * columns);
  }
  return matrix;
}

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int res = 0;
  if ((rows > 0) && (columns > 0) && (result != NULL)) {
    double **matrix = matrix_init(rows, columns);
    result->matrix = matrix;
    result->columns = columns;
    result->rows = rows;
  } else {
    res = 1;
  }
  return res;
}

void free_matrix(double **matrix, int rows) {
  for (int i = 0; i < rows; i++) {
    free(matrix[i]);
    matrix[i] = NULL;
  }
  free(matrix);
  matrix = NULL;
}

void s21_remove_matrix(matrix_t *A) {
  if (A != NULL) {
    if (A->matrix != NULL) {
      free_matrix(A->matrix, A->rows);
    }
    A->columns = 0;
    A->rows = 0;
  }
}

int check_matrix(matrix_t *A) {
  return (A != NULL) && (A->rows > 0) && (A->columns > 0) &&
         (A->matrix != NULL);
}

int eq_matrix_size(matrix_t *A, matrix_t *B) {
  int res = 1;
  if (A->rows == B->rows) {
    if (A->columns != B->columns) {
      res = 0;
    }
  } else {
    res = 0;
  }
  return res;
}

int eq_matrix_value(matrix_t *A, matrix_t *B) {
  int res = 1;
  for (int r = 0; r < A->rows; r++) {
    for (int c = 0; c < A->columns; c++) {
      if (fabs(A->matrix[r][c] - B->matrix[r][c]) > 1e-7) {
        res = 0;
      }
    }
  }
  return res;
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int res = FAILURE;
  if (check_matrix(A) && check_matrix(B) && eq_matrix_size(A, B) &&
      (eq_matrix_value(A, B) == 1)) {
    res = SUCCESS;
  }
  return res;
}

void sum_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result, char type) {
  for (int r = 0; r < A->rows; r++) {
    for (int c = 0; c < A->columns; c++) {
      if (type == '-') {
        result->matrix[r][c] = A->matrix[r][c] - B->matrix[r][c];
      }
      if (type == '+') {
        result->matrix[r][c] = A->matrix[r][c] + B->matrix[r][c];
      }
    }
  }
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = 0;
  if (check_matrix(A) && check_matrix(B)) {
    if (eq_matrix_size(A, B)) {
      s21_create_matrix(A->rows, A->columns, result);
      sum_sub_matrix(A, B, result, '+');
    } else {
      res = 2;
    }
  } else {
    res = 1;
  }
  return res;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = 0;
  if (check_matrix(A) && check_matrix(B)) {
    if (eq_matrix_size(A, B)) {
      s21_create_matrix(A->rows, A->columns, result);
      sum_sub_matrix(A, B, result, '-');
    } else {
      res = 2;
    }
  } else {
    res = 1;
  }
  return res;
}

int mult_matrix_size(matrix_t *A, matrix_t *B) { return A->columns == B->rows; }

double matrix_mult_elem(matrix_t *A, matrix_t *B, int r, int c) {
  double res = 0;
  for (int j = 0; j < B->rows; j++) {
    res += A->matrix[r][j] * B->matrix[j][c];
  }
  return res;
}

void mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  for (int r = 0; r < A->rows; r++) {
    for (int c = 0; c < B->columns; c++) {
      result->matrix[r][c] = matrix_mult_elem(A, B, r, c);
    }
  }
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = 0;
  if (check_matrix(A) && check_matrix(B)) {
    if (mult_matrix_size(A, B)) {
      s21_create_matrix(A->rows, B->columns, result);
      mult_matrix(A, B, result);
    } else {
      res = 2;
    }
  } else {
    res = 1;
  }
  return res;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int res = 0;
  if (check_matrix(A)) {
    s21_create_matrix(A->rows, A->columns, result);
    for (int r = 0; r < A->rows; r++) {
      for (int c = 0; c < A->columns; c++) {
        result->matrix[r][c] = A->matrix[r][c] * number;
      }
    }
  } else {
    res = 1;
  }
  return res;
}

void transpose(matrix_t *A, matrix_t *result) {
  for (int c = 0; c < A->columns; c++) {
    for (int r = 0; r < A->rows; r++) {
      result->matrix[c][r] = A->matrix[r][c];
    }
  }
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int res = 0;
  if (check_matrix(A)) {
    s21_create_matrix(A->columns, A->rows, result);
    transpose(A, result);
  } else {
    res = 1;
  }
  return res;
}

void small_matrix(double **matrix, double **new_matrix, int size, int row,
                  int columnn) {
  int switch_row = 0;
  int switch_column = 0;
  for (int i = 0; i < size - 1; i++) {
    if (i == row) {
      switch_row = 1;
    }
    for (int j = 0; j < size - 1; j++) {
      if (j == columnn) {
        switch_column = 1;
      }
      new_matrix[i][j] = matrix[i + switch_row][j + switch_column];
    }
    switch_column = 0;
  }
}

double determinant(double **matrix, int size) {
  double res = 0;
  int degree = 1;
  if (size == 1) {
    res = matrix[0][0];
  } else if (size == 2) {
    res = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
  } else {
    double **new_matrix = matrix_init(size - 1, size - 1);
    for (int i = 0; i < size; i++) {
      small_matrix(matrix, new_matrix, size, 0, i);
      res += degree * matrix[0][i] * determinant(new_matrix, size - 1);
      degree *= -1;
    }
    free_matrix(new_matrix, size - 1);
  }
  return res;
}

int s21_determinant(matrix_t *A, double *result) {
  int res = 0;
  if (check_matrix(A)) {
    if (A->columns == A->rows) {
      *result = determinant(A->matrix, A->columns);
    } else {
      res = 2;
    }
  } else {
    res = 1;
  }
  return res;
}

double s21_pow(int i, int j) {
  double number = -1;
  for (int k = 0; k <= i + j; k++) {
    number *= -1;
  }
  return number;
}

void calc_complements(matrix_t *A, matrix_t *result, int size) {
  s21_create_matrix(size, size, result);
  if (size > 1) {
    for (int i = 0; i < size; i++) {
      for (int j = 0; j < size; j++) {
        double **new_matrix = matrix_init(size - 1, size - 1);
        small_matrix(A->matrix, new_matrix, size, i, j);
        double determinant_1 = determinant(new_matrix, size - 1);
        free_matrix(new_matrix, size - 1);
        result->matrix[i][j] = determinant_1 * s21_pow(i, j);
      }
    }
  } else {
    result->matrix[0][0] = A->matrix[0][0];
  }
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int res = 0;
  if (check_matrix(A) && (result != NULL)) {
    if (A->columns == A->rows) {
      calc_complements(A, result, A->rows);
    } else {
      res = 2;
    }
  } else {
    res = 1;
  }
  return res;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int res = 0;
  if (check_matrix(A) && (result != NULL)) {
    if (A->columns == A->rows) {
      int size = A->rows;
      double determinant = 0;
      s21_determinant(A, &determinant);
      if (determinant != 0) {
        if (size > 1) {
          matrix_t complement_matrix;
          matrix_t transponse_matrix;
          s21_calc_complements(A, &complement_matrix);
          s21_transpose(&complement_matrix, &transponse_matrix);
          s21_mult_number(&transponse_matrix, (double)1 / determinant, result);
          s21_remove_matrix(&transponse_matrix);
          s21_remove_matrix(&complement_matrix);
        } else {
          s21_create_matrix(1, 1, result);
          result->matrix[0][0] = (double)1 / A->matrix[0][0];
        }
      } else {
        res = 2;
      }
    } else {
      res = 2;
    }
  } else {
    res = 1;
  }
  return res;
}