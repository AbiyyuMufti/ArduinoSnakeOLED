#ifndef _SNAKEELEMENT_H_
#define _SNAKEELEMENT_H_

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_WIDTH 128
#define OLED_HIGH 64

enum SnakeDirection {stop, left, right, up, down};
extern Adafruit_SSD1306 display;
extern int duration;
extern int Radius;

class Circle
{
  public:
    Circle(): X(0), Y(0), R(0) {};
    Circle(int x, int y, int r): X(x), Y(y), R(r) {};
    Circle::Circle(const Circle & cCircle);
    void setX(int &x);
    void setY(int &y);
    void getXYR(int &x, int &y, int &r);
    void goUp();
    void goDown();
    void goLeft();
    void goRight();
    void draw();
    bool intersects(Circle &Other);
  private:
    int X, Y, R;

};

class SnakeElement
{
  public:
    SnakeElement();
    SnakeElement(int x, int y, int r);
    ~SnakeElement();
    bool update(SnakeDirection newDir);
    void draw();
    bool elongate();
    bool eating(Circle &Food);

  private:
    static int TailCount;
    int CurrentDirection;
    Circle Head;
    SnakeElement *mTail;
    //    Adafruit_SSD1306 *displayPtr;
};


#endif
