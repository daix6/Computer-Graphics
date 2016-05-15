#include "Point.h"

Point::Point(float xPos, float yPos, float zPos) : x(xPos), y(yPos), z(zPos) {}

float* Point::getPointVector() {
  float* arr = new float[3];
  arr[0] = x;
  arr[1] = y;
  arr[2] = z;
  return arr;
}