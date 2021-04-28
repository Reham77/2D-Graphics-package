#ifndef UNTITLED51_ELLIPSE_H
#define UNTITLED51_ELLIPSE_H


#include "../Shape.h"

class ellipse : public Shape {

private:
    int getRadius(Point center , Point point);

    void drawFourPoints(Point center, Point point);

    void Polar(Point center, Point a, Point b);

    void iterativePolar(Point center, Point a, Point b);

    void direct(Point center, Point a, Point b);

public:
    ellipse(HDC hdc, int ID, COLORREF color);

    void draw(Point point , Point a ,Point b);
};


#endif //UNTITLED51_ELIPSE_H
