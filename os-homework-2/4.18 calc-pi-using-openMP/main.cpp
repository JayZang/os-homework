#include "stdlib.h"
#include "stdio.h"
#include "omp.h"

int pointInCircleCount = 0;
int pointInRectAmount = 0;

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

  #pragma omp parallel for
  for (int i = 0; i < pointInRectAmount; i++) {
    double x = (double)rand() * 2 / RAND_MAX - 1;
    double y = (double)rand() * 2 / RAND_MAX - 1;

    printf("%d: (x, y) => (%f, %f)\n", i, x, y);
    if ((x * x + y * y) <= 1)
    {
      pointInCircleCount++;
    }
  }

  double pi = 4 * ((double)pointInCircleCount / pointInRectAmount);
  printf("The calculated pi: %f\r\n", pi);

  return 0;
}
