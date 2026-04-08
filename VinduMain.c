#include <windows.h>
#include <stdio.h>
#include "Vindu.h"
#include <time.h>
#include "Tick_Tack_Toe.h"

int width;
int height;
int* piksler = NULL;
Superbrett superbrett = {
        .brettarray = {{},{},{}}
};

int main(int argc, char* argv[]){
    width = GetSystemMetrics(SM_CXSCREEN);
    height = GetSystemMetrics(SM_CYSCREEN);
    //Initialiserer eksternt bitmap heter for piksler
    piksler = malloc(sizeof(unsigned int) * width * height);

    for(int y = 0; y<height; y++){
        for(int x = 0; x<width; x++){
            piksler[y*width+x]= 0x00000000;
        }
    }
    printf("test før \n");

    HWND hwnd = 0;
    skapeVindu(&hwnd);
    srand(time(NULL));

    //Eksempel Superbrett;
    initSuperbrett(&superbrett);
    tegnSuperBrett(&superbrett);
    //Eksempel brett bare for å kunne tegne det
    // brett brett1 = {
    //     .brettarray={{'E','E','E'},{'E','E','E'},{'E','E','E'}},
    //     .status = '0',
    // };

    MSG msg;
    while(1){
        if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)){
            if(msg.message == WM_QUIT) break;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        } else{
            InvalidateRect(hwnd, NULL, FALSE);
            brettGrafikk(&superbrett, piksler);
            // printf("Bitmap Verdi %p \n", bitmap);
        }
    }
    printf("Test etter");
    free(piksler);

    return 0;
}