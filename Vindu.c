#include <stdio.h>
#include <windows.h>
#include <wingdi.h>
#include <stdbool.h>
#include "Vindu.h"

HDC memDC = NULL;
HBITMAP bitmap= NULL;

LRESULT CALLBACK windowProc(HWND window_handle, UINT message, WPARAM wParam, LPARAM lParam){
    switch(message){
        case WM_QUIT:
        case WM_DESTROY: {
            DeleteObject(bitmap);
            DeleteDC(memDC);
            PostQuitMessage(0);
            return 0;
        }break;
        case WM_CREATE: {
            HDC hdc = GetDC(window_handle);
            //Peker til memDC
            memDC = CreateCompatibleDC(hdc);

            BITMAPINFO bmi = {0};
            bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
            bmi.bmiHeader.biWidth = width;
            bmi.bmiHeader.biHeight = -height;
            bmi.bmiHeader.biPlanes = 1;
            bmi.bmiHeader.biBitCount = 32;
            bmi.bmiHeader.biCompression = BI_RGB;

            void *pixels;
            bitmap = CreateDIBSection(memDC, &bmi, DIB_RGB_COLORS, pixels, NULL, 0);
            SelectObject(memDC, bitmap);

            printf("Test at vi aktiverer WM_create");
            return 0;
        }
    case WM_PAINT: {
        PAINTSTRUCT paint;
        HDC hdc = BeginPaint(window_handle, &paint);
        
        BitBlt(hdc, 0, 0, width, height, memDC, 0, 0, SRCCOPY);


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