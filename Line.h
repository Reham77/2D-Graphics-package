#ifndef UNTITLED51_LINE_H
#define UNTITLED51_LINE_H

#include "Shape.h"


using namespace std;

class Line : public Shape {
private:
    void DDA(Point startPoint, Point endPoint);

    void midpoint(Point startPoint, Point endPoint);


public:

    Line(HDC hdc, int ID, COLORREF color);

    void parametricLine(Point startPoint, Point endPoint);

    void draw(Point start, Point end);

};

#endif //UNTITLED51_LINE_H
