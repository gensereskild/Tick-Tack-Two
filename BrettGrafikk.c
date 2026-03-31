//Poenget med denne er å oppdatere bitmappen til å endre grafikken.
//Tar inn pointer til brett, og pointer til bitmap.
//man tegner fra øvre venstre hjørnet og nedover

#include "Tick_Tack_Toe.h"
#include "vindu.h"
#include <stdio.h>

const int hvit = 0x00ffffff;

enum{
    horisontal =1,
    vertikal = 2
};

void stripe(float xStart, float yStart, float xStopp, float yStopp, int bredde, int farge, int* bitmap){
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
            //bitmap[((int) yStart) * width + x] = farge;
            //Tegner bredden
            for(int i = 0; i<(bredde+1)/2; i++){
                //Tegner ikke utenfor bitmappen fyfy
                if((((int)yStart +i) >= height) || (((int)yStart -i) <= 0)) continue;
                bitmap[((int)yStart + i)*width + currentX] = farge;
                bitmap[((int)yStart - i)*width + currentX] = farge;
            }
        }
    }
    int currentY = yStart;
    if(xStart==xStopp){
        for (; currentY < yStopp; currentY++)
        {
            for(int i = 0; i<(bredde+1)/2; i++){
                //Tegner ikke utenfor bitmappen fyfy
                if((((int)xStart +i) >= width) || (((int)xStart -i) <= 0)) continue;
                bitmap[(currentY)*width + ((int)xStart)+i] = farge;
                bitmap[(currentY)*width +((int) xStart)-i] = farge;
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
                //Tegner ikke utenfor bitmappen fyfy
                if((((int)y +i) >= height) || (((int)y -i) <= 0)) continue;
                bitmap[((int)y + i)*width + currentX] = farge;
                bitmap[((int)y - i)*width + currentX] = farge;
            }

            //bitmap[((int)y)*width + currentX] = farge;
            currentX++;
        }
    }
    //Når stigningstallet er større enn 1 er vi nødt til å iterere over alle kolonnene på skjermen
    else if(stigningstall>1){
        int currentY = yStart;
        for(float x = xStart; x<xStopp; x+=(1/stigningstall)){
            for(int i = 0; i<(bredde+1)/2; i++){
                //Tegner ikke utenfor bitmappen fyfy
                if((((int)x +i) >= width) || (((int)x -i) <= 0)) continue;
                bitmap[(currentY)*width + ((int)x)+i] = farge;
                bitmap[(currentY)*width +((int) x)-i] = farge;
            }
            currentY++;
        }
    }
}


void brettGrafikk(brett* brett1, int* bitmap){
    
    // stripe(20, 20, 60, 40, 1, hvit, bitmap);
    // stripe(0,0,100,100,10,hvit,bitmap);
    // stripe(10,10,100,10,50,hvit,bitmap);
    // stripe(20,20,30,90,20,hvit,bitmap);
    // stripe(50,0,50,100,25,hvit,bitmap);

    //Firkant
    stripe(10,10,10,90,10,hvit,bitmap);
    stripe(10,10,90,10,10,hvit,bitmap);
    stripe(10,90,90,90,10,hvit,bitmap);
    stripe(90,10,90,90,10,hvit,bitmap);

    stripe(35,10,35,90,10,hvit,bitmap);
    stripe(60,10,60,90,10,hvit,bitmap);
    stripe(10,35,90,35,10,hvit,bitmap);
    stripe(10,60,90,60,10,hvit,bitmap);
}

//Argumenter: start, stopp, bredde, horisontal/vertikal
//Start og stopp er oppgitt som % av hele skjermen.
// void stripe(int start, int stopp, int bredde, char retning)

