#include "CircleFilling.h"

CircleFilling::CircleFilling(HDC hdc, int ID, COLORREF color) : Shape(hdc, ID, color) {

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
        line.parametricEquationLine(center, Point(center.x + x, center.y - y));
        line.parametricEquationLine(center, Point(center.x + y, center.y - x));
    }
}

void CircleFilling::fillingSecondQuarter(Point center, Point point) {

    int radius = circle.getRadius(center, point);
    int x = radius;
    int y = 0;
    circle.drawEightPoints(center, Point(x, y));

    while (y < x) {
        y++;
        x = Round(sqrt(radius * radius - y * y));
        circle.drawEightPoints(center, Point(x, y));
        line.parametricEquationLine(center, Point(center.x - x, center.y - y));
        line.parametricEquationLine(center, Point(center.x - y, center.y - x));
    }
}

void CircleFilling::fillingThirdQuarter(Point center, Point point) {
    int radius = circle.getRadius(center, point);
    int x = radius;
    int y = 0;
    circle.drawEightPoints(center, Point(x, y));

    while (y < x) {
        y++;
        x = Round(sqrt(radius * radius - y * y));
        circle.drawEightPoints(center, Point(x, y));
        line.parametricEquationLine(center, Point(center.x - x, center.y + y));
        line.parametricEquationLine(center, Point(center.x - y, center.y + x));

    }
}

void CircleFilling::fillingForthQuarter(Point center, Point point) {
    int radius = circle.getRadius(center, point);
    int x = radius;
    int y = 0;
    circle.drawEightPoints(center, Point(x, y));

    while (y < x) {
        y++;
        x = Round(sqrt(radius * radius - y * y));
        circle.drawEightPoints(center, Point(x, y));
        line.parametricEquationLine(center, Point(center.x + x, center.y + y));
        line.parametricEquationLine(center, Point(center.x + y, center.y + x));
    }
}

void CircleFilling::draw(int option, Point center, Point point) {

    if (option == 1) {
        fillingFirstQuarter(center, point);
    } else if (option == 2) {
        fillingSecondQuarter(center, point);
    } else if (option == 3) {
        fillingThirdQuarter(center, point);
    } else fillingForthQuarter(center, point);
}