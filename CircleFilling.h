#include "Circle.h"
#include "Line.h"

class CircleFilling : public Shape {

private:

    Circle circle = Circle(hdc, ID, color);

    Line line = Line(hdc, ID, color);

    void fillingFirstQuarter(Point center, Point point);

    void fillingSecondQuarter(Point center, Point point);

    void fillingThirdQuarter(Point center, Point point);

    void fillingForthQuarter(Point center, Point point);

public:

    CircleFilling(HDC hdc, int ID, COLORREF color);

    void draw(int option, Point center, Point point);


};

