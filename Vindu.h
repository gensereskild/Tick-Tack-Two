#ifndef Vindu
#define Vindu

#include <windows.h>

//BitMap pointer
extern int *piksler;
extern int width;
extern int height;


LRESULT CALLBACK windowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int skapeVindu(HWND *hwnd);

#endif