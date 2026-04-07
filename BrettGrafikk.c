//Poenget med denne er å oppdatere pikslerpen til å endre grafikken.
//Tar inn pointer til brett, og pointer til piksler.
//man tegner fra øvre venstre hjørnet og nedover

#include "Tick_Tack_Toe.h"
#include "vindu.h"
#include <stdio.h>

const int hvit = 0x00ffffff;

const int rood = 0x00ff0000;

enum{
    horisontal =1,
    vertikal = 2
};

void stripe(float xStart, float yStart, float xStopp, float yStopp, int bredde, int farge, int* piksler){
    //Kan kode slik at man bytter plass, men tror ikke jeg gidder
    xStart = xStart*width/100;
    xStopp = xStopp*width/100;
    yStart = yStart*height/100;
    yStopp = yStopp*height/100;


    //Høyt stigningstall = bratt linje == Tegne få piksler langs x aksen
    float stigningstall = (yStopp-yStart)/(xStopp-xStart);
    //currentX er x verdien til pikslen man maler
    int currentX = xStart;

    if(yStart==yStopp){
        for (; currentX < xStopp; currentX++)
        {
            //piksler[((int) yStart) * width + x] = farge;
            //Tegner bredden
            for(int i = 0; i<(bredde+1)/2; i++){
                //Tegner ikke utenfor pikslerpen fyfy
                if((((int)yStart +i) >= height) || (((int)yStart -i) <= 0)) continue;
                piksler[((int)yStart + i)*width + currentX] = farge;
                piksler[((int)yStart - i)*width + currentX] = farge;
            }
        }
    }
    int currentY = yStart;
    if(xStart==xStopp){
        for (; currentY < yStopp; currentY++)
        {
            for(int i = 0; i<(bredde+1)/2; i++){
                //Tegner ikke utenfor pikslerpen fyfy
                if((((int)xStart +i) >= width) || (((int)xStart -i) <= 0)) continue;
                piksler[(currentY)*width + ((int)xStart)+i] = farge;
                piksler[(currentY)*width +((int) xStart)-i] = farge;
            }
        }
    }
    if(stigningstall <=1){
        for (float y = yStart; y < yStopp; y+=stigningstall)
        {
            // for(float x = xStart; x<xStopp;){

            // }
            //Tegner bredden
            for(int i = 0; i<(bredde+1)/2; i++){
                //Tegner ikke utenfor pikslerpen fyfy
                if((((int)y +i) >= height) || (((int)y -i) <= 0)) continue;
                piksler[((int)y + i)*width + currentX] = farge;
                piksler[((int)y - i)*width + currentX] = farge;
            }

            //piksler[((int)y)*width + currentX] = farge;
            currentX++;
        }
    }
    //Når stigningstallet er større enn 1 er vi nødt til å iterere over alle kolonnene på skjermen
    else if(stigningstall>1){
        int currentY = yStart;
        for(float x = xStart; x<xStopp; x+=(1/stigningstall)){
            for(int i = 0; i<(bredde+1)/2; i++){
                //Tegner ikke utenfor pikslerpen fyfy
                if((((int)x +i) >= width) || (((int)x -i) <= 0)) continue;
                piksler[(currentY)*width + ((int)x)+i] = farge;
                piksler[(currentY)*width +((int) x)-i] = farge;
            }
            currentY++;
        }
    }
}


void brettGrafikk(brett* brett1, int* piksler){
    
    // stripe(20, 20, 60, 40, 1, hvit, piksler);
    // stripe(0,0,100,100,10,hvit,piksler);
    // stripe(10,10,100,10,50,hvit,piksler);
    // stripe(20,20,30,90,20,hvit,piksler);
    // stripe(50,0,50,100,25,hvit,piksler);

    //Firkant
    stripe(10,10,10,90,10,hvit,piksler);
    stripe(10,10,90,10,10,hvit,piksler);
    stripe(10,90,90,90,10,hvit,piksler);
    stripe(90,10,90,90,10,hvit,piksler);

    stripe(35,10,35,90,10,hvit,piksler);
    stripe(60,10,60,90,10,hvit,piksler);
    stripe(10,35,90,35,10,hvit,piksler);
    stripe(10,60,90,60,10,hvit,piksler);

    BITMAPINFO bmi = {0};
        bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        bmi.bmiHeader.biWidth = 800;
        bmi.bmiHeader.biHeight = -600;
        bmi.bmiHeader.biPlanes = 1;
        bmi.bmiHeader.biBitCount = 32;
        bmi.bmiHeader.biCompression = BI_RGB;

    SetDIBitsToDevice(memDC, 0,0,800, 600,
    0,0,0,600,
    piksler, &bmi, DIB_RGB_COLORS);
    
    HFONT font = CreateFont(40,0,0,0,FW_BOLD,FALSE,FALSE,FALSE,ANSI_CHARSET,
            OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH, "Arial");

    SelectObject(memDC, font);
    SetBkMode(memDC, TRANSPARENT);
    SetTextColor(memDC, RGB(0,255,0));

    char symbol[2] = {0};
    for(int i = 0; i<9; i++){
        symbol[0] = (*(brett1)).brettarray[i/3][i%3];
        TextOut(memDC, ((i%3)*250)+150, ((i/3)*150)+150, symbol,1);
    }
}

//Argumenter: start, stopp, bredde, horisontal/vertikal
//Start og stopp er oppgitt som % av hele skjermen.
// void stripe(int start, int stopp, int bredde, char retning)

