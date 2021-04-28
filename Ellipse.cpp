#include "Ellipse.h"

Ellipse::Ellipse(HDC hdc, int ID, COLORREF color) :
        Shape(hdc, ID, color) {

}

int Ellipse::getRadius(Point center, Point point) {
    return hypot(center.x - point.x, center.y - point.y);
}
