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

void Ellipse::direct(Point center, Point a, Point b) {

    int RadiusA = getRadius(center, a);
    int RadiusB = getRadius(center, b);
    double x = 0;
    double y = RadiusB;
    drawFourPoints(center, Point(x, y));
    //check slope less than 1
    while (RadiusB * RadiusB * x <= RadiusA * RadiusA * y) {
        x++;
        y = Round((sqrt(RadiusB * RadiusB * (1 - ((x * x) / (RadiusA * RadiusA))))));
        drawFourPoints(center, Point(x, y));
    }
    x = RadiusA;
    y = 0;
    drawFourPoints(center, Point(x, y));
    //slope greater than one
    while (RadiusB * RadiusB * x > RadiusA * RadiusA * y) {
        y++;
        x = Round((sqrt(RadiusA * RadiusA * (1 - ((y * y) / (RadiusB * RadiusB))))));
        drawFourPoints(center, Point(x, y));
    }
}

//don't calculate sin and cos inside loop
void Ellipse::iterativePolar(Point center, Point a, Point b) {

    int RadiusA = getRadius(center, a);
    int RadiusB = getRadius(center, b);

    double dtheta = 1.0 / max(RadiusA, RadiusB);
    double stheta = sin(dtheta);
    double ctheta = cos(dtheta);
    double x = center.x + RadiusA;
    double y = center.y;
    double x1 = (x - center.x) / RadiusA;
    double y1 = (y - center.y) / RadiusB;
    SetPixel(hdc, Round(x), Round(y), color);

    for (double theta = 0; theta <= 6.28; theta += dtheta) {
        x1 = (x - center.x) / RadiusA;
        y1 = (y - center.y) / RadiusB;
        x = x * ctheta - y1 * RadiusA * stheta;
        y = y * ctheta + x1 * RadiusB * stheta;
        SetPixel(hdc, Round(x), Round(y), color);
    }
}

void Ellipse::draw(Point point, Point a, Point b) {

    if (ID == ELLIPSE_POLLAR)
        Polar(point, b, a);
    else if (ID == ELLIPSE_ITERATIVE_POLLAR)
        iterativePolar(point, b, a);
    else direct(point, b, a);
}


