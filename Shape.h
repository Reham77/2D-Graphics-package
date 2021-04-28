#ifndef UNTITLED51_SHAPE_H
#define UNTITLED51_SHAPE_H

#include "bits/stdc++.h"
#include "windows.h"
#include "Point.h"

using namespace std;

class Shape {

protected:
    HDC hdc;
    int ID;
    COLORREF color;

    int Round(double x);


public:

    Shape(HDC hdc, int ID, COLORREF colorName);

    virtual ~Shape() = 0;


};

#endif //UNTITLED51_SHAPE_H
