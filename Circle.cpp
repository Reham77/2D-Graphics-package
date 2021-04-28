#include "Circle.h"

Circle::Circle(HDC hdc, int ID, COLORREF color) : Shape(hdc, ID, color) {

}

int Circle::getRadius(Point center, Point point) {
    return hypot(point.x - center.x, point.y - center.y);
}

void Circle::drawEightPoints(Point center, Point point) {

    SetPixel(hdc, center.x + point.x, center.y + point.y, color);
    SetPixel(hdc, center.x - point.x, center.y + point.y, color);
    SetPixel(hdc, center.x - point.x, center.y - point.y, color);
    SetPixel(hdc, center.x + point.x, center.y - point.y, color);
    SetPixel(hdc, center.x + point.y, center.y + point.x, color);
    SetPixel(hdc, center.x - point.y, center.y + point.x, color);
    SetPixel(hdc, center.x - point.y, center.y - point.x, color);
    SetPixel(hdc, center.x + point.y, center.y - point.x, color);
}

/