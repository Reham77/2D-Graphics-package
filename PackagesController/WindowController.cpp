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


void WindowController::savingData(string name) {

    ofstream MyWriteFile(name);

    for (int i = 0; i < savedData.size(); i++) {
        MyWriteFile << savedData[i].ID << "-" << savedData[i].color << "-";

        if (savedData[i].ID == CIRCLE_FILLING) {
            MyWriteFile << savedData[i].option << "-";
        }

        for (int j = 0; j < savedData[i].points.size(); j++) {
            MyWriteFile << savedData[i].points[j].x << "-" << savedData[i].points[j].y;
            if (j != savedData[i].points.size() - 1) MyWriteFile << "-";
            else MyWriteFile << "\n";
        }
    }
    MyWriteFile.close();
}

void WindowController::savingDataHelper() {
    //to choose the path you want
    OPENFILENAME ofn;
    char szFileName[MAX_PATH] = "";
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFilter = "Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0";
    ofn.lpstrFile = szFileName;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
    ofn.lpstrDefExt = "txt";

    GetSaveFileName(&ofn);

    string file_name = ofn.lpstrFile;
    savingData(file_name);
}

void WindowController::loadData(string name) {

    vector<Point> clippingWindow;
    string iter;
    ifstream MyreadFile(name);
    while (getline(MyreadFile, iter)) {
        info curr;
        string temp = "";
        vector<string> result;
        for (int i = 0; i < iter.size(); i++) {
            if (iter[i] == '-') {
                result.push_back(temp);
                temp = "";
            } else temp += iter[i];
        }

        result.push_back(temp);

        //convert string to int
        curr.ID = stoi(result[0]);
        curr.color = stoi(result[1]);

        receiveMenuID(curr.ID);
        setColor(curr.color);

        int begIdx = 2;
        if (isFilling())begIdx = 3;

        for (int i = begIdx; i < result.size(); i += 2) {
            curr.points.push_back({stoi(result[i]), stoi(result[i + 1])});
        }

        if (isFilling()) {
            for (int i = 0; i < curr.points.size(); i++) {
                receivePointForFilling(curr.points[i], stoi(result[2]), false);
            }
        } else if (isCurrentlyLine()) {
            for (int i = 0; i < curr.points.size(); i++) {
                receivePointForLine(curr.points[i]);
            }
        } else if (isCurrentlyCircle()) {
            for (int i = 0; i < curr.points.size(); i++) {
                receivePointForCircle(curr.points[i]);
            }
        } else if (isClipping()) {

            for (int i = 0; i < curr.points.size(); i++)
                receivePointForClipping(curr.points[i], clippingWindow);

            if (curr.ID == USE_CLIPPING_WINDOW)
                clippingWindow.clear(), clippingWindow = curr.points;

        } else if (isCurrentlyEllipse()) {
            for (int i = 0; i < curr.points.size(); i++) {
                receivePointForEllipse(curr.points[i]);
            }
        }
    }
}

void WindowController::loadingDataHelper() {

    savedData.clear();

    OPENFILENAME ofn;
    char szFileName[MAX_PATH] = "";
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFilter = "Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0";
    ofn.lpstrFile = szFileName;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
    ofn.lpstrDefExt = "txt";

    GetOpenFileName(&ofn);

    string file_name = ofn.lpstrFile;
    loadData(file_name);
}

void WindowController::clear(HWND hwnd) {
    savedData.clear();
    InvalidateRect(hwnd, NULL, true);
}

void WindowController::clearClippingWindow() {
    this->ClippingWindow.clear();
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

