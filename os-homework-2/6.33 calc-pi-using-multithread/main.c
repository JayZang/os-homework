#include "stdlib.h"
#include "stdio.h"
#include "pthread/pthread.h"

int pointInCircleCount = 0;
int pointInRectAmount = 0;
pthread_mutex_t mutex;

void *process();

int main(int argc, char const *argv[])
{
  // 設置隨機數種子
  srand((unsigned)time(NULL));

  printf("Enter total point amount: ");
  scanf("%d", &pointInRectAmount);
  if (pointInRectAmount <= 0) {
    printf("Please enter the number greater than 0\r\n");
    return 1;
  }

  pthread_mutex_init(&mutex, NULL);
  pthread_t threads[pointInRectAmount];
  for (int i = 0; i < pointInRectAmount; i++) {
    pthread_create(&threads[i], NULL, process, NULL);
  }

  for (int i = 0; i < pointInRectAmount; i++) {
    pthread_join(threads[i], NULL);
  }
  pthread_mutex_destroy(&mutex);

  double pi = 4 * ((double)pointInCircleCount / pointInRectAmount);
  printf("The calculated pi: %f\r\n", pi);

  return 0;
}

void *process() {
  double x = (double)rand() * 2 / RAND_MAX - 1;
  double y = (double)rand() * 2 / RAND_MAX - 1;

  printf("(x, y) => (%f, %f)\n", x, y);
  if ((x * x + y * y) <= 1) {
    pthread_mutex_lock(&mutex);
    pointInCircleCount++;
    pthread_mutex_unlock(&mutex);
  }

  return NULL;
}
