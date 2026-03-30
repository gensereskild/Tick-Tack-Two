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
            piksler[y*800+x]= 0x00ff0000;
        }
    }
    printf("test før \n");

    HWND hwnd = 0;
    skapeVindu(&hwnd);
    srand(time(NULL));

    MSG msg;

    RECT rect = {0};

   GetUpdateRect(hwnd, &rect, FALSE);
   printf("Bottom: %ld, Top: %ld, Left %ld, Right %ld \n", rect.bottom, rect.top, rect.left, rect.top);

       for(int y = 0; y<600; y++){
        for(int x = 0; x<800; x++){
            piksler[y*800+x]= 0x000000ff;
        }
    }

    int randomx;
    int randomy;
    while(1){
        if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)){
            if(msg.message == WM_QUIT) break;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        } else{
            InvalidateRect(hwnd, NULL, FALSE);
            randomx = rand();
            randomx = randomx%(width);
            randomy = rand();
            randomy = randomy%(height);
            piksler[randomx+ randomy*width]= 0x0000ff00;
        }

        //printf("iaojf");
    }
    printf("Test etter");
    free(piksler);

    return 0;
}