#include "stdlib.h"
#include "stdio.h"
#include "stdbool.h"
#include "pthread/pthread.h"

#define ROWS  9
#define COLS  9

bool result = true;

void *process(void *point);

int main(int argc, char const *argv[])
{
  pthread_t threads[ROWS][COLS];
  int sudoku[ROWS][COLS] = {
    {6, 2, 4, 5, 3, 9, 1, 8, 7},
    {5, 1, 9, 7, 2, 8, 6, 3, 4},
    {8, 3, 7, 6, 1, 4, 2, 9, 5},
    {1, 4, 3, 8, 6, 5, 7, 2, 9},
    {9, 5, 8, 2, 4, 7, 3, 6, 1},
    {7, 6, 2, 3, 2, 1, 4, 5, 8},
    {3, 7, 1, 9, 5, 6, 8, 4, 2},
    {4, 9, 6, 1, 8, 2, 1, 7, 3},
    {2, 8, 5, 4, 7, 3, 9, 1, 0}};

  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      pthread_create(&threads[i][j], NULL, process, (void *)&sudoku[i][j]);
    }
  }

  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      pthread_join(threads[i][j], NULL);
    }
  }

  if (result) {
    printf("Result: true\r\n");
  } else {
    printf("Result: false\r\n");
  }

  return 0;
}

void *process(void *val) {
  if (*((int *)val) == 0) {
    result = false;
  }

  return NULL;
}