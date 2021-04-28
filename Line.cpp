#include "Line.h"
#include "Clipping.h"


Line::Line(HDC hdc, int ID, COLORREF color) :Shape(hdc, ID, color) {

}
//using parametric equation
void Line::parametricLine(Point startPoint, Point endPoint) {
    double dx = (double) endPoint.x - startPoint.x;
    double dy = (double) endPoint.y - startPoint.y;

    double dt = 1.00 / max(abs(dy), abs(dx));
    for (double t = 0; t <= 1; t += dt) {
        int x = Round(startPoint.x + (t * dx));
        int y = Round(startPoint.y + (t * dy));

        SetPixel(hdc , x , y , color);
    }
}
