#include <stdio.h>
#include <stdlib.h>

int *runningSum(int *nums, int numsSize, int *returnSize) {
  *returnSize = numsSize;
  int *result = (int *)malloc(sizeof(int) * numsSize);
  result[0] = nums[0];
  for (int i = 1; i < numsSize; i++) {
    result[i] = nums[i] + result[i - 1];
  }
  return result;
}
int main() {
  int test_nums[] = {1, 2, 3, 4};

  int nums_size = sizeof(test_nums) / sizeof(test_nums[0]);
  int return_size;
  int *result_array = runningSum(test_nums, nums_size, &return_size);

  for (int i = 0; i < return_size; i++) {
    printf("%d ", result_array[i]);
  }

  free(result_array);
  return 0;
}
