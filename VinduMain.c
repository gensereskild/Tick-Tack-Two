#include <windows.h>
#include <stdio.h>
#include "Vindu.h"
#include <time.h>

int width = 800;
int height = 600;
int* piksler = NULL;

int main(int argc, char* argv[]){
    //Initialiserer eksternt bitmap heter for piksler
    piksler = malloc(sizeof(unsigned int) * width * height);

    for(int y = 0; y<600; y++){
        for(int x = 0; x<800; x++){
            piksler[y*800+x]= 0x00000000;
        }
    }
    printf("test før \n");

    HWND hwnd = 0;
    skapeVindu(&hwnd);
    srand(time(NULL));

    MSG msg;

    while(1){
        if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)){
            if(msg.message == WM_QUIT) break;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        } else{
            InvalidateRect(hwnd, NULL, FALSE);
            brettGrafikk(NULL, piksler);
        }
    }
    printf("Test etter");
    free(piksler);

    return 0;
}