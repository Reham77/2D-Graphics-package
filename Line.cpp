#include "Line.h"
#include "Clipping.h"


Line::Line(HDC hdc, int ID, COLORREF color) : Shape(hdc, ID, color) {

}

//using parametric equation
void Line::parametricLine(Point startPoint, Point endPoint) {
    double dx = (double) endPoint.x - startPoint.x;
    double dy = (double) endPoint.y - startPoint.y;

    double dt = 1.00 / max(abs(dy), abs(dx));
    for (double t = 0; t <= 1; t += dt) {
        int x = Round(startPoint.x + (t * dx));
        int y = Round(startPoint.y + (t * dy));

        SetPixel(hdc, x, y, color);
    }
}

// y = mx + c
void Line::DDA(Point startPoint, Point endPoint) {
    double dx = endPoint.x - startPoint.x;
    double dy = endPoint.y - startPoint.y;
    double m = 0;
    if (abs(dy) <= abs(dx)) // if slope is less than or equal to one
    {
        m = dy / dx;
        if (startPoint.x > endPoint.x) {
            swap(startPoint.x, endPoint.x);
            swap(startPoint.y, endPoint.y);
        }
        int x = startPoint.x;
        double y = startPoint.y;
        SetPixel(hdc, x, Round(y), color);
        while (x < endPoint.x) {
            x++;
            y += m;
            SetPixel(hdc, x, Round(y), color);
        }
    } else {
        m = dx / dy;
        if (startPoint.y > endPoint.y) {
            swap(startPoint.y, endPoint.y);
            swap(startPoint.x, endPoint.x);
        }
        double x = startPoint.x;
        int y = startPoint.y;
        while (y < endPoint.y) {
            y++;
            x += m;
            SetPixel(hdc, Round(x), y, color);
        }
    }
}

void Line::midpoint(Point startPoint, Point endPoint) {
    double dx = endPoint.x - startPoint.x;
    double dy = endPoint.y - startPoint.y;
    double slope = dy / dx;
    if ((abs(dy) <= abs(dx)) && (slope >= 0)) {
        if (startPoint.x > endPoint.x) {
            swap(startPoint.x, endPoint.x);
            swap(startPoint.y, endPoint.y);
        }
        double d = (endPoint.x - startPoint.x) - 2 * (endPoint.y - startPoint.y); // desicion variable
        double change1 = 2 * (endPoint.x - startPoint.x) - 2 * (endPoint.y - startPoint.y); // under the line
        double change2 = -2 * (endPoint.y - startPoint.y); //above the line
        int x = startPoint.x;
        int y = startPoint.y;
        SetPixel(hdc, x, y, color);
        while (x <= endPoint.x) {
            if (d <= 0) {
                y++;
                d += change1;
            } else {
                d += change2;
            }
            x++;
            SetPixel(hdc, x, y, color);
        }
    } else if ((abs(dy) > abs(dx)) && (slope > 0)) {
        if (startPoint.y > endPoint.y) {
            swap(startPoint.x, endPoint.x);
            swap(startPoint.y, endPoint.y);
        }
        double d = 2 * (endPoint.x - startPoint.x) - (endPoint.y - startPoint.y);
        double change1 = 2 * (endPoint.x - startPoint.x);
        double change2 = 2 * ((endPoint.x - startPoint.x) - (endPoint.y - startPoint.y));
        int x = startPoint.x;
        int y = startPoint.y;
        SetPixel(hdc, x, y, color);
        while (y <= endPoint.y) {
            if (d < 0) {
                d += change1;
            } else {
                x++;
                d += change2;
            }
            y++;
            SetPixel(hdc, x, y, color);
        }
    } else if ((slope < 0) && (abs(dy) <= abs(dx))) {
        if (startPoint.x > endPoint.x) {
            swap(startPoint.x, endPoint.x);
            swap(startPoint.y, endPoint.y);
        }
        int x = startPoint.x;
        int y = startPoint.y;
        double d = -(endPoint.x - startPoint.x) - 2 * (endPoint.y - startPoint.y);
        double change1 = -2 * (endPoint.y - startPoint.y);
        double change2 = -2 * ((endPoint.x - startPoint.x) + (endPoint.y - startPoint.y));
        SetPixel(hdc, x, y, color);
        while (x <= endPoint.x) {
            if (d < 0) {
                d += change1;
            } else {
                y--;
                d += change2;
            }
            x++;
            SetPixel(hdc, x, y, color);
        }
    } else {
        if (startPoint.y > endPoint.y) {
            swap(startPoint.x, endPoint.x);
            swap(startPoint.y, endPoint.y);
        }
        int x = startPoint.x;
        int y = startPoint.y;
        double d = 2 * (endPoint.x - startPoint.x) + (endPoint.y - startPoint.y);
        double change1 = 2 * (endPoint.x - startPoint.x);
        double change2 = 2 * ((endPoint.x - startPoint.x) + (endPoint.y - startPoint.y));
        SetPixel(hdc, x, y, color);
        while (y <= endPoint.y) {
            if (d > 0) {
                d += change1;
            } else {
                d += change2;
                x--;
            }
            y++;
            SetPixel(hdc, x, y, color);

        }
    }

}

void Line::draw(Point start, Point end) {
    if (ID == LINE_DDA) {
        DDA(start, end);
    } else if (ID == LINE_PARAMETRIC) {
        parametricLine(start, end);
    } else midpoint(start, end);
}


