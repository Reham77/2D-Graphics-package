#ifndef GRAPHICS_WINDOWCONTROLLER_H
#define GRAPHICS_WINDOWCONTROLLER_H

#include <windows.h>
#include <vector>
#include "../Line/Line.h"
#include "../Circle/Circle.h"
#include "../Circle Filling/CircleFilling.h"
#include "../Shape.h"

using namespace std;

struct info {
    int ID;
    COLORREF color;
    int option;
    vector<Point> points ;
};

class WindowController {
private:

    HDC hdc;
    vector<info> savedData;
    vector<Point> clickedPoints, ClippingWindow;
    int ID;
    COLORREF color;

    void receivePointForLine(Point point);

    void receivePointForCircle(Point point);

    void receivePointForFilling(Point point, int option, bool flag);

    void receivePointForClipping(Point point , vector<Point>clipppingWindow);

    void receivePointForEllipse(Point point);

    void SetClippingWindow(vector<Point>clippingwindow);

public:
    void setHDC(HDC hdc);

    //check functions
    bool isCurrentlyCircle();

    bool isCurrentlyLine();

    bool isCurrentlyEllipse();

    bool isFilling();

    bool isClipping();

    //functions to perform operations
    void doubleClick(Point point);

    void receiveMenuID(int ID);

    void setColor(COLORREF ID);

    //save , load and clear
    void savingData(string name);

    void savingDataHelper();

    void loadData(string name);

    void loadingDataHelper();

    void clear(HWND hwnd);

    void clearClippingWindow();

};

#endif //GRAPHICS_WINDOWCONTROLLER_H
