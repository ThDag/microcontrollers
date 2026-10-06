#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void *a, const void *b) {
  int x = *(const int *)a;
  int y = *(const int *)b;

  if (x < y)
    return -1;
  if (x == y)
    return 0;
  return 1;
}

bool containsDuplicate(int *nums, int numsSize) {

  qsort(nums, numsSize, sizeof(nums[0]), compare);

  printf("List sorted\n");
  for (int i = 0; i < numsSize; i++) {
    printf("%d - ", nums[i]);
  }
  printf("\n");

  for (int i = 0; i < numsSize - 1; i++) {
    if (nums[i] == nums[i + 1])
      return 1;
  }
  return 0;
}

int main() {

  int nums[] = {0, 5, 34, 7, 91, 21, 56, 12, 8, 45, 0, 6, 7};
  int numsSize = 12;

  bool result = containsDuplicate(nums, numsSize);
  printf("%d\n", result);
}
