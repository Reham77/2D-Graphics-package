#if defined(UNICODE) && !defined(_UNICODE)
#define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
#define UNICODE
#endif


#include <fstream>
#include "PackagesController/WindowController.h"
#include <tchar.h>
#include <windows.h>

WindowController controller; // MY CONTROLLER to control any operation

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

TCHAR szClassName[] = _T("Project");

int WINAPI WinMain(HINSTANCE hThisInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpszArgument,
                   int nCmdShow) {
    HWND hwnd;
    MSG messages;
    WNDCLASSEX wincl;

    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;
    wincl.style = CS_DBLCLKS;
    wincl.cbSize = sizeof(WNDCLASSEX);

/* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor(NULL, IDC_HAND); // changed the mouse cursor
    wincl.lpszMenuName = NULL;
    wincl.cbClsExtra = 0;
    wincl.cbWndExtra = 0;

    wincl.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH); // changed the color of the background into white

    if (!RegisterClassEx(&wincl))
        return 0;

    hwnd = CreateWindowEx(
            0,                   /* Extended possibilites for variation */
            szClassName,         /* Classname */
            _T("Graphics 2D"),       /* Title Text */
            WS_OVERLAPPEDWINDOW, /* default window */
            CW_USEDEFAULT,       /* Windows decides the position */
            CW_USEDEFAULT,       /* where the window ends up on the screen */
            800,                 /* The programs width */
            620,                 /* and height in pixels */
            HWND_DESKTOP,        /* The window is a child-window to desktop */
            NULL,                /* No menu */
            hThisInstance,       /* Program Instance handler */
            NULL                 /* No Window Creation data */
    );

    controller.setHDC(GetDC(hwnd));// Set Window HDC

/* Make the window visible on the screen */
    ShowWindow(hwnd, nCmdShow);

    while (GetMessage(&messages, NULL, 0, 0)) {
        TranslateMessage(&messages);
        DispatchMessage(&messages);
    }
    return messages.wParam;
}


//to create our menu
HMENU createMenuBar() {
    HMENU hMenubar = CreateMenu();
//operations
    HMENU hMenu = CreateMenu();
    AppendMenuW(hMenu, MF_STRING, SAVE, L"&Save");
    AppendMenuW(hMenu, MF_STRING, LOAD, L"&Load");
    AppendMenuW(hMenu, MF_STRING, CLEAR, L"&Clear");

    AppendMenuW(hMenu, MF_SEPARATOR, 0, NULL);

// color
    AppendMenuW(hMenu, MF_STRING, COLORING, L"&Color");

    AppendMenuW(hMenu, MF_SEPARATOR, 0, NULL); //seperator

    //for clipping
    HMENU hClipMenu = CreateMenu();
    AppendMenuW(hMenu, MF_STRING | MF_POPUP, (UINT_PTR) hClipMenu, L"&Clip");
    AppendMenuW(hClipMenu, MF_STRING, USE_CLIPPING_WINDOW, L"&Use Clipping Window");
    CheckMenuItem(hMenu, USE_CLIPPING_WINDOW, MF_UNCHECKED);

    //clipping algorithms
    HMENU hClippingdraw = CreateMenu();
    AppendMenuW(hClipMenu, MF_STRING | MF_POPUP, (UINT_PTR) hClippingdraw, L"&Draw in Clipping Mode");
    AppendMenuW(hClippingdraw, MF_STRING, CLIP_LINE_TO_RECTANGLE, L"&Clip Line to rectangle ");
    CheckMenuItem(hMenu, CLIP_LINE_TO_RECTANGLE, MF_UNCHECKED);
    AppendMenuW(hClippingdraw, MF_STRING, CLIP_CIRCLE_TO_RECTANGLE, L"&Clip circle to rectangle");
    CheckMenuItem(hMenu, CLIP_CIRCLE_TO_RECTANGLE, MF_UNCHECKED);

    AppendMenuW(hMenu, MF_SEPARATOR, 0, NULL); //seperator

    HMENU hDrawMenu = CreateMenu();
    AppendMenuW(hMenu, MF_STRING | MF_POPUP, (UINT_PTR) hDrawMenu, L"&Draw");

    //line algorithms
    HMENU hDrawLineMenu = CreateMenu();
    AppendMenuW(hDrawMenu, MF_STRING | MF_POPUP, (UINT_PTR) hDrawLineMenu, L"&Line");
    AppendMenuW(hDrawLineMenu, MF_STRING, LINE_DDA, L"&DDA");
    CheckMenuItem(hMenu, LINE_DDA, MF_UNCHECKED);
    AppendMenuW(hDrawLineMenu, MF_STRING, LINE_BRESENHAM, L"&Midpoint");
    CheckMenuItem(hMenu, LINE_BRESENHAM, MF_UNCHECKED);
    AppendMenuW(hDrawLineMenu, MF_STRING, LINE_PARAMETRIC, L"&Parametric");
    CheckMenuItem(hMenu, LINE_PARAMETRIC, MF_UNCHECKED);

    //circle algorithms
    HMENU hDrawCircleMenu = CreateMenu(); //circle algorithms
    AppendMenuW(hDrawMenu, MF_STRING | MF_POPUP, (UINT_PTR) hDrawCircleMenu, L"&Circle");
    AppendMenuW(hDrawCircleMenu, MF_STRING, CIRCLE_DIRECT_CARTESIAN, L"&Direct Cartesian method");
    CheckMenuItem(hMenu, CIRCLE_DIRECT_CARTESIAN, MF_UNCHECKED);
    AppendMenuW(hDrawCircleMenu, MF_STRING, CIRCLE_POLAR, L"&Polar");
    CheckMenuItem(hMenu, CIRCLE_POLAR, MF_UNCHECKED);
    AppendMenuW(hDrawCircleMenu, MF_STRING, CIRCLE_IMPROVED_POLAR, L"&Iterative Polar method");
    CheckMenuItem(hMenu, CIRCLE_IMPROVED_POLAR, MF_UNCHECKED);
    AppendMenuW(hDrawCircleMenu, MF_STRING, CIRCLE_BRESENHAM, L"&Midpoint");
    CheckMenuItem(hMenu, CIRCLE_BRESENHAM, MF_UNCHECKED);
    AppendMenuW(hDrawCircleMenu, MF_STRING, CIRCLE_MODFIED_BRESENHAM, L"&Modified Midpoint");
    CheckMenuItem(hMenu, CIRCLE_MODFIED_BRESENHAM, MF_UNCHECKED);
    AppendMenuW(hDrawCircleMenu, MF_STRING, CIRCLE_FILLING, L"&Circle Filling");
    CheckMenuItem(hMenu, CIRCLE_FILLING, MF_UNCHECKED);

    //ellipse alorithms
    HMENU hDrawEllipseMenu = CreateMenu();
    AppendMenuW(hDrawMenu, MF_STRING | MF_POPUP, (UINT_PTR) hDrawEllipseMenu, L"&ellipse");
    AppendMenuW(hDrawEllipseMenu, MF_STRING, ELLIPSE_DIRECT, L"&Direct");
    CheckMenuItem(hMenu, ELLIPSE_DIRECT, MF_UNCHECKED);
    AppendMenuW(hDrawEllipseMenu, MF_STRING, ELLIPSE_POLLAR, L"&Polar");
    CheckMenuItem(hMenu, ELLIPSE_POLLAR, MF_UNCHECKED);
    AppendMenuW(hDrawEllipseMenu, MF_STRING, ELLIPSE_ITERATIVE_POLLAR, L"&Iterative Polar");
    CheckMenuItem(hMenu, ELLIPSE_ITERATIVE_POLLAR, MF_UNCHECKED);

    AppendMenuW(hMenu, MF_SEPARATOR, 0, NULL);

    AppendMenuW(hMenu, MF_STRING, QUIT, L"&Quit");

    AppendMenuW(hMenubar, MF_POPUP, (UINT_PTR) hMenu, L"&Menu");

    return hMenubar;
}

//to convert brush to coloref
COLORREF GetBrushColor(HBRUSH brush) {
    LOGBRUSH lbr;
    if (GetObject(brush, sizeof(lbr), &lbr) != sizeof(lbr)) {
        return CLR_NONE;
    }
    if (lbr.lbStyle != BS_SOLID) {
        return CLR_NONE;
    }
    return lbr.lbColor;
}

// to make a color dialog box
COLORREF coloring(HWND hwnd) {
    CHOOSECOLOR cc;                 // common dialog box structure
    static COLORREF acrCustClr[16];
    HBRUSH hbrush;
    static DWORD rgbCurrent;
    COLORREF clr;

    ZeroMemory(&cc, sizeof(cc));
    cc.lStructSize = sizeof(cc);
    cc.hwndOwner = hwnd;
    cc.lpCustColors = (LPDWORD) acrCustClr;
    cc.rgbResult = rgbCurrent;
    cc.Flags = CC_FULLOPEN | CC_RGBINIT;

    if (ChooseColor(&cc) == TRUE) {
        hbrush = CreateSolidBrush(cc.rgbResult);
        rgbCurrent = cc.rgbResult;
    }

    clr = GetBrushColor(hbrush);
    return clr;
}

HMENU hMenuBar;
int prevID = -1;

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {

    switch (message) {
        case WM_CREATE: {

            //create the menu
            hMenuBar = createMenuBar();
            SetMenu(hwnd, hMenuBar);
            break;
        }
        case WM_COMMAND: {

            //get the command selected
            int ID = LOWORD(wParam);

            //to check and uncheck an item in the menu
            if (prevID != -1) {
                ShowWindow(reinterpret_cast<HWND>(hMenuBar), SW_HIDE);
                CheckMenuItem(hMenuBar, prevID, MF_UNCHECKED);
            }

            ShowWindow(reinterpret_cast<HWND>(hMenuBar), SW_SHOWNA);
            CheckMenuItem(hMenuBar, ID, MF_CHECKED);

            prevID = ID ;

            switch (ID) {
                case SAVE:
                    controller.savingDataHelper();
                    break;
                case LOAD:
                    controller.clear(hwnd);
                    controller.loadingDataHelper();
                    break;
                case CLEAR:
                    controller.clear(hwnd);
                    break;
                case QUIT:
                    SendMessage(hwnd, WM_CLOSE, 0, 0);
                    break;
                case COLORING:
                    controller.setColor(coloring(hwnd));
                    break;
                default:
                    if (ID == USE_CLIPPING_WINDOW)
                        controller.clear(hwnd);
                    controller.receiveMenuID(ID);
                    break;
            }
            break;
        }
        case WM_LBUTTONDBLCLK: {
            Point point(LOWORD(lParam), HIWORD(lParam));
            controller.doubleClick(point);
            break;
        }
        case WM_DESTROY: {
            PostQuitMessage(0);
            break;
        }
        default:
            return DefWindowProc(hwnd, message, wParam, lParam);
    }
    return 0;
}
