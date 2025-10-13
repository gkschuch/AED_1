#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool checkStraightLine(int **coordinates, int coordinatesSize,
                       int *coordinatesColSize) {
  if (coordinatesSize == 2)
    return true;
  int x0 = coordinates[0][0];
  int y0 = coordinates[0][1];
  int x1 = coordinates[1][0];
  int y1 = coordinates[1][1];

  int dx_ref = x1 - x0;
  int dy_ref = y1 - y0;

  for (int i = 2; i < coordinatesSize; i++) {
    int xi = coordinates[i][0];
    int yi = coordinates[i][1];

    int dx_curr = xi - x0;
    int dy_curr = yi - y0;

    if (dy_ref * dx_curr != dx_ref * dy_curr)
      return false;
  }
  return true;
}

int main() {
  int coordinates[][2] = {{1, 1}, {-23, 2}, {4, 4}, {9, 9}};

  int size = sizeof(coordinates) / sizeof(coordinates[0]);

  int *coordPointer[size];
  for (int i = 0; i < size; i++) {
    coordPointer[i] = coordinates[i];
  }

  bool result = checkStraightLine(coordPointer, size, NULL);

  printf(" %s\n", result ? "true" : "false");

  return 0;
}