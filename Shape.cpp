#include "Shape.h"
#include "Clipping.h"


int Shape::Round(double x) {
    return (int) (0.5 + x);
}

Shape::Shape(HDC hdc, int ID, COLORREF color) {
    this->hdc = hdc;
    this->ID = ID;
    this->color = color;

}

Shape::~Shape() {}


