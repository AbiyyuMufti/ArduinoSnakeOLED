#include "SnakeElement.h"

int SnakeElement::TailCount = 0;

SnakeElement::SnakeElement(): Head() {
  CurrentDirection = stop;
  mTail = NULL;
}

SnakeElement::SnakeElement(int x, int y, int r): Head(x, y, r) {
  CurrentDirection = stop;
  mTail = NULL;
}

SnakeElement::~SnakeElement() {
  if (NULL != mTail) {
    delete mTail;
  }
}

bool SnakeElement::update(SnakeDirection newDir) {
  switch (newDir) {
    case left:
      Head.goLeft();
      break;
    case right:
      Head.goRight();
      break;
    case up:
      Head.goUp();
      break;
    case down:
      Head.goDown();
      break;
    case stop:
      break;
  }
  if (NULL != mTail) {
    mTail->update(CurrentDirection);
  }
  CurrentDirection = newDir;
  return true;

}

void SnakeElement::draw() {
  Head.draw();
  //Serial.println("display");
  if (NULL != mTail) {
    mTail->draw();
  }
}

bool SnakeElement::elongate() {
  if (TailCount >= 64) {
    return false;
  }
  if (NULL == mTail) { // New tail direct with head
    SnakeElement *newTail;
    int x, y, r;
    Head.getXYR(x, y, r);
    switch (CurrentDirection) {
      case left:
        newTail = new SnakeElement(x + 2 * r, y, r);
        break;
      case right:
        newTail = new SnakeElement(x - 2 * r, y, r);
        break;
      case up:
        newTail = new SnakeElement(x, y + 2 * r, r);
        break;
      case down:
        newTail = new SnakeElement(x, y - 2 * r, r);
        break;
    }
    mTail = newTail;
    TailCount++;
    return true;
  } else {
    mTail->elongate();
  }
}

bool SnakeElement::eating(Circle &Food) {
  return Head.intersects(Food);
}
