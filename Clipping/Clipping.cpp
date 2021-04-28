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

//clipping window [0] (x left , y top)
// [1] (x right  , y bottom)
bool Clipping::clipped(Point point, vector<Point> clippingWindowPoints) {
    return (point.x >= clippingWindowPoints[0].x &&
            point.x <= clippingWindowPoints[1].x &&
            point.y >= clippingWindowPoints[0].y &&
            point.y <= clippingWindowPoints[1].y);

}
