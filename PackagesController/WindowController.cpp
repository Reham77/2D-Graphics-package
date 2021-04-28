#include "WindowController.h"
#include "../Ellipse/ellipse.h"

void WindowController::setHDC(HDC hdc) {
    this->hdc = hdc;
}

void WindowController::receiveMenuID(int ID) {
    this->ID = ID;
}

void WindowController::setColor(COLORREF ID) {
    this->color = ID;
}

void WindowController::SetClippingWindow(vector<Point> Clippingwindow) {
    this->ClippingWindow = Clippingwindow;
}

void WindowController::doubleClick(Point point) {
    if (isCurrentlyLine()) {
        receivePointForLine(point);
    } else if (isCurrentlyCircle()) {
        receivePointForCircle(point);
    } else if (isFilling()) {
        int option = 0;
        receivePointForFilling(point, option, true);
    } else if (isClipping()) {
        vector<Point> clippingWindow;
        receivePointForClipping(point, clippingWindow);
    } else if (isCurrentlyEllipse()) {
        receivePointForEllipse(point);
    }
}

void WindowController::receivePointForFilling(Point point, int option, bool flag) {
    if (clickedPoints.size() == 0) {
        clickedPoints.push_back(point);
    } else {
        CircleFilling circlefilling = CircleFilling(hdc, ID, color);
        if (flag) {
            cout << "ENTER THE QUARTER NUMBER" << endl;
            cin >> option;
        }
        circlefilling.draw(option, clickedPoints[0], point);
        clickedPoints.push_back(point);
        savedData.push_back({ID, color, option, clickedPoints});
        clickedPoints.clear();
    }
}

bool WindowController::isCurrentlyLine() {
    return (ID >= 1 && ID <= 3);
}
