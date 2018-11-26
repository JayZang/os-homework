#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;

#define FRAME_COUNT 3
#define REFERENCE_COUNT 10
#define MIN_PAGE_REFERENCE_NUMBER 0
#define MAX_PAGE_REFERENCE_NUMBER 9

int *generateRandomPageReference(int count);
int fifoAlgorithms(int *pageReference);
int lruAlgorithms(int *pageReference);
int optimalAlgorithms(int *pageReference);

int main(int argc, char const *argv[])
{
  int *pageRefernces = generateRandomPageReference(REFERENCE_COUNT);

  printf("Page frames: %d\r\n", FRAME_COUNT);
  printf("Page-Reference String: ");
  for (int i = 0; i < REFERENCE_COUNT; i++) {
    printf("%d ", pageRefernces[i]);
  }
  printf("\r\n");

  int fifoPageFaults = fifoAlgorithms(pageRefernces);
  printf("FIFO page faults: %d\r\n", fifoPageFaults);

  int lruPageFault = lruAlgorithms(pageRefernces);
  printf("LRU page faults: %d\r\n", lruPageFault);

  int optimalPageFault = optimalAlgorithms(pageRefernces);
  printf("optimal page faults: %d\r\n", optimalPageFault);

  return 0;
}

int *generateRandomPageReference(int count) {
  // 設置隨機數種子
  srand((unsigned)time(NULL));

  int *pageReferences = (int *)malloc(count);
  for (int i = 0; i < count; i++) {
    pageReferences[i] = rand() % (MAX_PAGE_REFERENCE_NUMBER - MIN_PAGE_REFERENCE_NUMBER + 1) + MIN_PAGE_REFERENCE_NUMBER;
  }

  return pageReferences;
}

int fifoAlgorithms(int *pageReference) {
  int frames[FRAME_COUNT];
  int pageFaultCount = 0;
  int frameIndexToReplacement = 0;
  bool isPageFault = true;

  fill_n(frames, FRAME_COUNT, -1);
  for (int i = 0; i < REFERENCE_COUNT; i++) {
    isPageFault = true;

    for (int frameIndex = 0; frameIndex < FRAME_COUNT; frameIndex++) {
      if (frames[frameIndex] == pageReference[i]) {
        isPageFault = false;
        break;
      }
    }

    if (!isPageFault) {
      continue;
    } else {
      if (frames[frameIndexToReplacement] != -1) {
        pageFaultCount++;
      }

      frames[frameIndexToReplacement] = pageReference[i];

      if (++frameIndexToReplacement >= FRAME_COUNT) {
        frameIndexToReplacement = 0;
      }
    }
  }

  return pageFaultCount;
}

int lruAlgorithms(int *pageReference) {
  int frames[FRAME_COUNT];
  int framesTrace[FRAME_COUNT] = {0};   // 計數次數，當 page 已存在或需要被替換時，此 frame 次數紀錄會歸 0
  int pageFaultCount = 0;
  bool isPageFault = true;

  fill_n(frames, FRAME_COUNT, -1);
  for (int i = 0; i < REFERENCE_COUNT; i++) {
    isPageFault = true;

    for (int frameIndex = 0; frameIndex < FRAME_COUNT; frameIndex++) {
      if (frames[frameIndex] == pageReference[i]) {
        isPageFault = false;
        framesTrace[frameIndex] = 0;
      } else if (frames[frameIndex] != -1) {
        framesTrace[frameIndex]++;
      }
    }

    if (!isPageFault) {
      continue;
    } else {
      int indexToReplacement = 0;
      int maxRecord = 0;
      int isEmptyFrame = false;

      for (int frameIndex = 0; frameIndex < FRAME_COUNT; frameIndex++) {
        if (frames[frameIndex] == -1) {
          indexToReplacement = frameIndex;
          isEmptyFrame = true;
          break;
        } else if (framesTrace[frameIndex] > maxRecord) {
          indexToReplacement = frameIndex;
          maxRecord = framesTrace[frameIndex];
        }
      }

      !isEmptyFrame && pageFaultCount++;
      frames[indexToReplacement] = pageReference[i];
      framesTrace[indexToReplacement] = 0;
    }
  }

  return pageFaultCount;
}

int optimalAlgorithms(int *pageReference) {
  int frames[FRAME_COUNT];
  int framesTrace[FRAME_COUNT];     // 儲存該 frame 內之 page 下次出現的 index
  int pageFaultCount = 0;

  fill_n(frames, FRAME_COUNT, -1);
  fill_n(framesTrace, FRAME_COUNT, -1);
  for (int i = 0; i < REFERENCE_COUNT; i++) {
    bool isPageFault = true;
    int indexToReplacement = 0;
    int pageValue = pageReference[i];

    for (int frameIndex = 0; frameIndex < FRAME_COUNT; frameIndex++) {
      if (frames[frameIndex] == -1 || frames[frameIndex] == pageReference[i]) {
        isPageFault = false;
        indexToReplacement = frameIndex;
        break;
      }
    }

    if (isPageFault) {
      pageFaultCount++;

      int maxValue = -1;
      for (int frameIndex = 0; frameIndex < FRAME_COUNT; frameIndex++) {
        if (framesTrace[frameIndex] > maxValue) {
          maxValue = framesTrace[frameIndex];
          indexToReplacement = frameIndex;
        } else if (framesTrace[frameIndex] == -1) {
          indexToReplacement = frameIndex;
          break;
        }
      }
    }

    for (int j = (i + 1); j < REFERENCE_COUNT; j++) {
      if (pageReference[j] == pageValue) {
        framesTrace[indexToReplacement] = j;
        break;
      } else if (j == REFERENCE_COUNT - 1) {
        framesTrace[indexToReplacement] = -1;
      }
    }

    frames[indexToReplacement] = pageValue;
  }

  return pageFaultCount;
}