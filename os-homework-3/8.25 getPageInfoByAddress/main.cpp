#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;

#define PAGE_SIZE 4096

int main(int argc, char const *argv[])
{
  if (argc < 2) {
    printf("請帶入一個參數\r\n");
    return -1;
  }

  long address = atol(argv[1]);
  if (address > UINT_MAX) {
    printf("超出最大記憶體範圍\r\n");
    return -1;
  }

  int pageCount = address / PAGE_SIZE;
  int offset = address % PAGE_SIZE;

  printf("The Address %ld contains:\r\n", address);
  printf("page number = %d\r\n", pageCount);
  printf("offset = %d\r\n", offset);

  return 0;
}
