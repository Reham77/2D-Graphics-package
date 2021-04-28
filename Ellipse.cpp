#include "Ellipse.h"

Ellipse::Ellipse(HDC hdc, int ID, COLORREF color) :
        Shape(hdc, ID, color) {

}

int Ellipse::getRadius(Point center, Point point) {
    return hypot(center.x - point.x, center.y - point.y);
}

void Ellipse::drawFourPoints(Point center, Point point) {

    SetPixel(hdc, center.x + point.x, center.y + point.y, color);
    SetPixel(hdc, center.x - point.x, center.y + point.y, color);
    SetPixel(hdc, center.x - point.x, center.y - point.y, color);
    SetPixel(hdc, center.x + point.x, center.y - point.y, color);

}

void Ellipse::Polar(Point center, Point a, Point b) {

    int RadiusA = getRadius(center, a);
    int RadiusB = getRadius(center, b);
    double dtheta = 1.0 / max(RadiusA, RadiusB);

    for (double theta = 0; theta <= 6.28; theta += dtheta) {
        int x = Round(RadiusA * cos(theta));
        int y = Round(RadiusB * sin(theta));
        SetPixel(hdc, center.x + x, center.y + y, color);
    }
}


