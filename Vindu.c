#include <stdio.h>
#include <windows.h>
#include <wingdi.h>
#include <stdbool.h>
#include "Vindu.h"

LRESULT CALLBACK windowProc(HWND window_handle, UINT message, WPARAM wParam, LPARAM lParam){
    switch(message){
        case WM_QUIT:
        case WM_DESTROY: {
            PostQuitMessage(0);
            return 0;
        }break;
    case WM_PAINT: {
        PAINTSTRUCT paint;
        HDC hdc = BeginPaint(window_handle, &paint);

        HDC memDC = CreateCompatibleDC(hdc);
        HBITMAP bitmap = CreateCompatibleBitmap(hdc, 800, 600);
        SelectObject(memDC, bitmap);

        //Get aaccess to pixel data
        BITMAPINFO bmi = {0};
        bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        bmi.bmiHeader.biWidth = 800;
        bmi.bmiHeader.biHeight = -600;
        bmi.bmiHeader.biPlanes = 1;
        bmi.bmiHeader.biBitCount = 32;
        bmi.bmiHeader.biCompression = BI_RGB;

        //Kopierer buffer til vindu
        SetDIBitsToDevice(hdc, 0,0,800, 600,
            0,0,0,600,
            piksler, &bmi, DIB_RGB_COLORS);

        DeleteObject(bitmap);
        DeleteDC(memDC);

        EndPaint(window_handle, &paint);
        return 0;
    }
    default:
    return DefWindowProc(window_handle, message, wParam, lParam);
}
}


int skapeVindu(HWND *hwnd){
    HINSTANCE hInstance = GetModuleHandle(NULL);

    WNDCLASS wc = {0};
    wc.lpfnWndProc = windowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "MyWindowClass";
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW +1);

    if(!RegisterClass(&wc)) return -1;

    *hwnd = CreateWindowEx(
        0,
        "MyWindowClass",
        "My First Window",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
    NULL, NULL, hInstance, NULL);

    if(!*hwnd) return -1;

    //Viser og Oppdaterer vinduet
    //Første argument HandleWindow, andre argument modus for å visie vinduet når det blir åpnet av andre
    //prosseser tror jeg 5 åpner det alltid eller no.
    ShowWindow(*hwnd, SW_SHOW);
    UpdateWindow(*hwnd);

    return 0;
}