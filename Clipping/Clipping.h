#include "../Shape.h"
#include "../Line/Line.h"

union OutCode {
    unsigned All: 4;
    struct {
        unsigned left: 1, top: 1, right: 1, bottom: 1;
    };
};


class Clipping : public Shape {
private:

    OutCode GetOutCode(double x , double y , vector<Point>clippingWindow);
    void X_Intersect(double Xstart, double Ystart, double Xend, double Yend, int x, double *xi, double *yi);
    void Y_Intersect(double Xstart, double Ystart, double Xend, double Yend, int y, double *xi, double *yi);
    void drawClippedLine_CohenSuth(Point start, Point end, vector<Point> clippingWindow);


    void drawClippedPoint(Point point, vector<Point> clippingWindow);

    void drawClippedCircle(Point center, Point point, vector<Point> clippingWindow);

    bool clipped(Point point , vector<Point>clippingWindow );

public:

    Clipping(HDC hdc, int ID, COLORREF color);

    vector<Point> drawClippingWindow(Point topLeft, Point bottomRight);

    void draw(Point start, Point end, vector<Point> clippingWindow);


};

