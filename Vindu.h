#ifndef Vindu
#define Vindu

#include <windows.h>
#include "Tick_Tack_Toe.h"
#include <stdbool.h>

//BitMap pointer
extern int *piksler;
extern int width;
extern int height;

LRESULT CALLBACK windowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int skapeVindu(HWND *hwnd);

void brettGrafikk(Superbrett *brett1, int* bitmap);

extern HDC memDC;
extern HBITMAP bitmap;

#endif