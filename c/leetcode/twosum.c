#import <stdio.h>
#import <stdlib.h>

int *twoSum(int *nums, int numsSize, int target, int *returnSize) {
  int *answer = malloc(2 * sizeof(int));
  *returnSize = 2;

  for (int i = 0; i < numsSize; i++) {
    for (int j = i + 1; j < numsSize; j++) {
      if ((nums[i] + nums[j]) == target) {
        answer[0] = i;
        answer[1] = j;
        break;
      }
    }
  }
  return answer;
}

int main() {
  int numbers[] = {3, 13, 11, 15, 1, 4, 8};
  int size = 7;
  int target = 9;
  int returnedSize = 0;

  int *result = twoSum(numbers, size, target, &returnedSize);

  printf("result: %d, %d", result[0], result[1]);
  free(result);
}
