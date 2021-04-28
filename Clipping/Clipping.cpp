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
    linedrawer->parametricEquationLine(topLeft, Point(bottomRight.x, topLeft.y));
    linedrawer->parametricEquationLine(Point(topLeft.x, bottomRight.y), bottomRight);
    linedrawer->parametricEquationLine(topLeft, Point(topLeft.x, bottomRight.y));
    linedrawer->parametricEquationLine(Point(bottomRight.x, topLeft.y), bottomRight);

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

void Clipping::drawClippedPoint(Point point, vector<Point> clippingWindow) {

    if (clipped(point, clippingWindow))
        SetPixel(hdc, point.x, point.y, color);
}

void Clipping::drawClippedCircle(Point center, Point point, vector<Point> clippingWindow) {

    int radius = hypot(center.x - point.x, center.y - point.y);
    double dtheta = 1.0 / radius;
    double ctheta = cos(dtheta);
    double stheta = sin(dtheta);
    double x = radius;
    double y = 0.0;
    drawClippedPoint(Point(x, y), clippingWindow);

    for (double theta = 0; theta <= 6.28; theta += dtheta) {
        double x1 = x * ctheta - y * stheta;
        y = x * stheta + y * ctheta;
        x = x1;
        if (clipped(point, clippingWindow)) {
            drawClippedPoint(Point(Round(x + center.x), Round(y + center.y)), clippingWindow);
        }
    }
}


OutCode Clipping::GetOutCode(double x, double y, vector<Point> clippingWindow) {
    OutCode out;
    out.All = 0;

    if (x < clippingWindow[0].x)
        out.left = 1;
    else if (x > clippingWindow[1].x)
        out.right = 1;
    if (y < clippingWindow[0].y)
        out.top = 1;
    else if (y > clippingWindow[1].y)
        out.bottom = 1;
    return out;

}
void Clipping::X_Intersect(double Xstart, double Ystart, double Xend, double Yend, int x, double *xi, double *yi) {
    *xi = x;
    *yi = Ystart + (x - Xstart) * (Yend - Ystart) / (Xend - Xstart);
}

void Clipping::Y_Intersect(double Xstart, double Ystart, double Xend, double Yend, int y, double *xi, double *yi) {
    *yi = y;
    *xi = Xstart + (y - Ystart) * (Xend - Xstart) / (Yend - Ystart);
}
