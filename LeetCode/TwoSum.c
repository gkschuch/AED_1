#include <stdio.h>
#include <stdlib.h>
/**
 Given an array of integers nums and an integer target, return indices of the
two numbers such that they add up to target.
You may assume that each input would have exactly one solution, and you may not
use the same element twice.
You can return the answer in any order.
 */
int *twoSum(int *nums, int numsSize, int target, int *returnSize) {
  *returnSize = 2;
  int i;
  int j;
  int *result = (int *)malloc(sizeof(int) * 2);
  for (i = 0; i < numsSize; i++)
    for (j = i + 1; j < numsSize; j++)
      if (nums[i] + nums[j] == target) {
        result[0] = i;
        result[1] = j;
        return result;
      }
  *returnSize = 0;

  return NULL;
}
int main() {
  int input[] = {2, 7, 11, 15};
  int numsSize = 4;
  int target = 30;
  int returnSize;
  int *result;
  result = twoSum(input, numsSize, target, &returnSize);
  for (int i = 0; i < returnSize; i++) {
    printf("%d ", result[i]);
  }
  free(result);
}