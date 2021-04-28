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

void WindowController::receivePointForLine(Point point) {
    if (clickedPoints.size() == 0) {
        clickedPoints.push_back(point);
    } else {
        Line lineDrawer = Line(hdc, ID, color);
        lineDrawer.draw(clickedPoints[0], point);
        clickedPoints.push_back(point);
        savedData.push_back({ID, color, 0, clickedPoints}); //vector to save data
        clickedPoints.clear();
    }
}

void WindowController::receivePointForCircle(Point point) {
    if (clickedPoints.size() == 0) {
        clickedPoints.push_back(point);
    } else {
        Circle circleDrawer = Circle(hdc, ID, color);
        circleDrawer.draw(clickedPoints[0], point);
        clickedPoints.push_back(point);
        savedData.push_back({ID, color, 0, clickedPoints});
        clickedPoints.clear();
    }
}

void WindowController::receivePointForEllipse(Point point) {
    ellipse ellipseDrawer = ellipse(hdc, ID, color);
    if (clickedPoints.size() < 2) {
        clickedPoints.push_back(point);
    } else {
        ellipseDrawer.draw(clickedPoints[0], clickedPoints[1], point);
        clickedPoints.push_back(point);
        savedData.push_back({ID, color, 0, clickedPoints});
        clickedPoints.clear();
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

void WindowController::receivePointForClipping(Point point, vector<Point> clipppingWindow) {

    if (clickedPoints.size() == 0) {
        clickedPoints.push_back(point);
    } else {
        Clipping clip = Clipping(hdc, ID, color);

        if (ID == USE_CLIPPING_WINDOW) {
            clearClippingWindow();//clear old window then create a new one
            //clipping vector has two points (topleft - buttomright)

            ClippingWindow = clip.drawClippingWindow(clickedPoints[0], point);

            //then set this->clipping window with clipping window
            SetClippingWindow(ClippingWindow);
        } else {

            clip.draw(clickedPoints[0], point, ClippingWindow);
        }

        clickedPoints.push_back(point);
        savedData.push_back({ID, color, 0, clickedPoints});
        clickedPoints.clear();
    }
}


bool WindowController::isCurrentlyLine() {
    return (ID >= 1 && ID <= 3);
}

bool WindowController::isCurrentlyCircle() {
    return (ID >= 4 && ID <= 8);
}

bool WindowController::isFilling() {
    return (ID == CIRCLE_FILLING);
}

bool WindowController::isClipping() {
    return (ID >= 13 && ID <= 15);
}

bool WindowController::isCurrentlyEllipse() {
    return (ID >= 10 && ID <= 12);
}

