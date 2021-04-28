#ifndef UNTITLED51_CIRCLE_H
#define UNTITLED51_CIRCLE_H

#include "../Shape.h"
#include "../Clipping/Clipping.h"

using namespace std;

class Circle : public Shape {
private:


    void DirectCartesian(Point center, Point point);

    void Polar(Point center, Point point);


    void midpoint(Point center, Point point);

    void modifiedMidpoint(Point center, Point point);


public:
    Circle(HDC hdc, int ID, COLORREF color);

    static int getRadius(Point center, Point point);

    void drawEightPoints(Point center, Point point);

    void IterativePolar(Point center, Point point);

    void draw(Point center, Point point);

};


#endif //UNTITLED51_CIRCLE_H
