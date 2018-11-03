#include "stdlib.h"
#include "stdio.h"
#include "pthread/pthread.h"

int pointInCircleCount = 0;
int pointInRectAmount = 0;

void *process();

int main(int argc, char const *argv[])
{
  // 設置隨機數種子
  srand((unsigned)time(NULL));

  pthread_t thread1;

  printf("Enter total point amount: ");
  scanf("%d", &pointInRectAmount);
  if (pointInRectAmount <= 0) {
    printf("Please enter the number greater than 0\r\n");
    return 1;
  }

  pthread_create(&thread1, NULL, process, NULL);
  pthread_join(thread1, NULL);

  double pi = 4 * ((double)pointInCircleCount / pointInRectAmount);
  printf("The calculated pi: %f\r\n", pi);

  return 0;
}

void *process() {
  for (int i = 0; i < pointInRectAmount; i++) {
    double x = (double)rand() * 2 / RAND_MAX - 1;
    double y = (double)rand() * 2 / RAND_MAX - 1;

    printf("%d: (x, y) => (%f, %f)\n", i, x, y);
    if ((x * x + y * y) <= 1) {
      pointInCircleCount++;
    }
  }

  return NULL;
}
