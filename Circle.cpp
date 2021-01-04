#include "SnakeElement.h"

void Circle::setX(int &x) {
  X = x;
}

void Circle::setY(int &y) {
  Y = y;
}

void Circle::getXYR(int &x, int &y, int &r) {
  x = X;
  y = Y;
  r = R;
}

void Circle::goUp() {
  if (Y < 0) {
    Y = 64;
  }
  Y -= 2 * R;
}
void Circle::goDown() {
  if (Y > 64) {
    Y = 0;
  }
  Y += 2 * R;
}
void Circle::goLeft() {
  if (X < 0) {
    X = 128;
  }
  X -= 2 * R;
}
void Circle::goRight() {
  if (X > 128) {
    X = 0;
  }
  X += 2 * R;
}

void Circle::draw() {
  display.fillCircle(X, Y, R, WHITE);
  //display.drawCircle(X, Y, R, BLACK);
}

bool Circle::intersects(Circle &Other) {
  int xOther, yOther, rOther;
  Other.getXYR(xOther, yOther, rOther);
  int distance = ((X - xOther) ^ 2 + (Y - yOther) ^ 2);
  return distance < ((R + rOther) ^ 2);
}
