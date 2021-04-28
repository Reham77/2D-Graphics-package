#include "Clipping.h"


Clipping::Clipping(HDC hdc, int ID, COLORREF color) : Shape(hdc, ID, color) {

}

vector<Point> Clipping::drawClippingWindow(Point topLeft, Point bottomRight) {

    vector<Point> clippingWindowPoints;
    Line *linedrawer = new Line(hdc, ID, color);

    clippingWindowPoints.clear();

    //push the new points in vector
    clippingWindowPoints.push_back(topLeft);
    clippingWindowPoints.push_back(bottomRight);

    //draw the rectangle
    linedrawer->parametricLine(topLeft, Point(bottomRight.x, topLeft.y));
    linedrawer->parametricLine(Point(topLeft.x, bottomRight.y), bottomRight);
    linedrawer->parametricLine(topLeft, Point(topLeft.x, bottomRight.y));
    linedrawer->parametricLine(Point(bottomRight.x, topLeft.y), bottomRight);

    return clippingWindowPoints;
}
