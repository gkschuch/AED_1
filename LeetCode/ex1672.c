#include <stdio.h>
/*
    You are given an m x n integer grid accounts where accounts[i][j] is the
amount of money the i​​​​​​​​​​​th​​​​ customer
has in the j​​​​​​​​​​​th​​​​ bank. Return the
wealth that the richest customer has. A customer's wealth is the amount of money
they have in all their bank accounts. The richest customer is the customer that
has the maximum wealth.
*/
int maximumWealth(int **accounts, int accountsSize, int *accountsColSize) {
  int priorWealth = 0, currentWealth;
  for (int i = 0; i < accountsSize; i++) {
    currentWealth = 0;
    for (int j = 0; j < accountsColSize[i]; j++) {
      currentWealth += accounts[i][j];
    }
    if (currentWealth > priorWealth) {
      priorWealth = currentWealth;
    }
  }
  return priorWealth;
}
int main() {
  int line1[] = {1, 2, 3};
  int line2[] = {1, 2, 3};
  int *accounts[] = {line1, line2};
  int accountsSize = 2;
  int accountsColSize[] = {3, 3};
  int richestWealth = maximumWealth(accounts, accountsSize, accountsColSize);
  printf("%d", richestWealth);
}