#include "Circle.h"

Circle::Circle(HDC hdc, int ID, COLORREF color) : Shape(hdc, ID, color) {

}

int Circle::getRadius(Point center, Point point) {
    return hypot(point.x - center.x, point.y - center.y);
}

