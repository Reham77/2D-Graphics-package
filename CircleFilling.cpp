#include "CircleFilling.h"

CircleFilling::CircleFilling(HDC hdc, int ID, COLORREF color): Shape(hdc, ID, color) {

}

void CircleFilling::fillingFirstQuarter(Point center, Point point) {

    int radius = circle.getRadius(center, point);
    int x = radius;
    int y = 0;

    circle.drawEightPoints(center, Point(x, y));
    while (y < x) {
        y++;
        x = Round(sqrt(radius * radius - y * y));
        circle.drawEightPoints(center, Point(x, y));
        line.parametricLine(center, Point(center.x + x, center.y - y));
        line.parametricLine(center, Point(center.x + y, center.y - x));
    }
}
