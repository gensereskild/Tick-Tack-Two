//Poenget med denne er å oppdatere pikslerpen til å endre grafikken.
//Tar inn pointer til brett, og pointer til piksler.
//man tegner fra øvre venstre hjørnet og nedover

#include "Tick_Tack_Toe.h"
#include "vindu.h"
#include <stdio.h>

const int hvit = 0x00ffffff;
const int rood = 0x00ff0000;
const int blaa = 0x000000ff;
const unsigned int groon = 0x0000ff00;

//Argumenter: start, stopp, bredde, horisontal/vertikal
//Start og stopp er oppgitt som % av hele skjermen.
// void stripe(int start, int stopp, int bredde, char retning)

void stripe(float xStart, float yStart, float xStopp, float yStopp, int bredde, int farge, int* piksler){
    //Kan kode slik at man bytter plass, men tror ikke jeg gidder
    xStart = xStart*width/100;
    xStopp = xStopp*width/100;
    yStart = yStart*height/100;
    yStopp = yStopp*height/100;


    //Høyt stigningstall = bratt linje == Tegne få piksler langs x aksen
    float stigningstall = 0.0;

    if((int) xStopp - (int)xStart!=0){
        stigningstall = (yStopp-yStart)/(xStopp-xStart);
    }
    //currentX er x verdien til pikslen man maler
    int currentX = xStart;
    int currentY = yStart;

    if((int) yStart== (int) yStopp){
        for (; currentX < xStopp; currentX++)
        {
            //piksler[((int) yStart) * width + x] = farge;
            //Tegner bredden
            for(int i = 0; i<(bredde+1)/2; i++){
                //Tegner ikke utenfor piksler fyfy
                if((((int)yStart +i) >= height) || (((int)yStart -i) <= 0)) continue;
                piksler[((int)yStart + i)*width + currentX] = farge;
                piksler[((int)yStart - i)*width + currentX] = farge;
            }
        }
    }
    else if((int) xStart==(int) xStopp){
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
    else if((stigningstall <=1) && (stigningstall != 0.0)){
        for (float y = yStart; y < yStopp; y+=stigningstall)
        {
            // for(float x = xStart; x<xStopp;){

            // }
            //Tegner bredden
            for(int i = 0; i<(bredde+1)/2; i++){
                //Tegner ikke utenfor pikslerpen fyfy
                if((((int)y +i) >= height) || (((int)y -i) <= 0)) continue;
                printf("Stigninstall verdi %f \n", stigningstall);
                // printf("Verdi til bredden %d \n", (int) width);
                // printf("Verdi til y %d \n", (int) y +i);
                // fflush(0);
                //piksler[((int)y + i)*width + currentX] = farge;
                //piksler[((int)y - i)*width + currentX] = farge;
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

void tegnBrettGrafikk(float x_start, float y_start, float breddeBrett, float hooydeBrett, unsigned int farge){

    float strekBredde = 4;
    float indreStrekBredde = 3;
    //må gjøre om strekbredde i piksler til % bredde av skjermen
    //strekBredde / width * 100
    //Det ble feil...
    
    float breddeProsent = (strekBredde/4.0)/((float)width)*100.0;
    //Firkant
    stripe(x_start , y_start, x_start+breddeBrett + breddeProsent ,y_start, strekBredde,farge,piksler);
    stripe(x_start, y_start, x_start, y_start+hooydeBrett + breddeProsent, strekBredde,farge,piksler);
    stripe(x_start+breddeBrett, y_start, x_start+breddeBrett, y_start+hooydeBrett +breddeProsent, strekBredde,farge,piksler);
    stripe(x_start, y_start+hooydeBrett, x_start+breddeBrett, y_start+hooydeBrett, strekBredde, farge,piksler);

    // for(int i =0; i<9; i++){
        
    // }
    //Horisontale linjer
    stripe(x_start,y_start + 1.0/3.0*hooydeBrett,x_start + breddeBrett, y_start+(((float)(1))/3)*hooydeBrett,indreStrekBredde,farge,piksler);
    stripe(x_start,y_start + 2.0/3.0*hooydeBrett,x_start + breddeBrett, y_start+(2.0/3.0)*hooydeBrett,indreStrekBredde,farge,piksler);
    //Vertiakle linjer
    stripe(x_start + 1.0/3.0*breddeBrett, y_start, x_start + 1.0/3.0*breddeBrett, y_start+hooydeBrett, indreStrekBredde, farge, piksler);
    stripe(x_start + 2.0/3.0*breddeBrett, y_start, x_start + 2.0/3.0*breddeBrett, y_start+hooydeBrett, indreStrekBredde, farge, piksler);

    return;
}

void brettGrafikk(Superbrett* superBrett, int* piksler){

    
    for(int i =0; i<9; i++){
        unsigned int farge = hvit;
        if(i==aktivtBrett || aktivtBrett==10){
            farge = groon;
        }
        if(superBrett->brettarray[i/3][i%3].status==1){
            farge = rood;
        }
        else if(superBrett->brettarray[i/3][i%3].status==2){
            farge = blaa;
        }
        tegnBrettGrafikk(20.0 + 20.0*(i%3), 7.5 + 27.0*(i/3), 17.0, 25.0, farge);
    }
    
    BITMAPINFO bmi = {0};
        bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        bmi.bmiHeader.biWidth = width;
        bmi.bmiHeader.biHeight = -height;
        bmi.bmiHeader.biPlanes = 1;
        bmi.bmiHeader.biBitCount = 32;
        bmi.bmiHeader.biCompression = BI_RGB;

    SetDIBitsToDevice(memDC, 0,0,width, height,
    0,0,0,height,
    piksler, &bmi, DIB_RGB_COLORS);
    
    HFONT font = CreateFont(20,0,0,0,FW_BOLD,FALSE,FALSE,FALSE,ANSI_CHARSET,
            OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH, "Arial");

    SelectObject(memDC, font);
    SetBkMode(memDC, TRANSPARENT);
    SetTextColor(memDC, RGB(0,255,0));
    
    //TextOut(memDC, 200, 200, "int", 3);
    
    //Tegner alle karakterene på brettet.
    char streng[2];
    streng[1] = '\0';

    for(int i = 0; i< 9; i++){
        int startX=((i%3)*width/100)*21.5 +22*width/100;
        int startY=((i/3)*height/100)*27.5 + 9*height/100;
        for(int j = 0; j<9; j++){
            streng[0] = superBrett->brettarray[i/3][i%3].brettarray[j/3][j%3];

            if(superBrett->brettarray[i/3][i%3].status==1){
                streng[0] = 'X';
            }
            else if (superBrett->brettarray[i/3][i%3].status==2){
                streng[0] = 'O';
            }

            //Endrer farge
            SetTextColor(memDC, RGB(0,255,0));
            if(streng[0]=='X'){
                SetTextColor(memDC, RGB(255,0,0));
            }
            else if(streng[0]=='O'){
                SetTextColor(memDC, RGB(0,0,255));
            }

            TextOut(memDC, (((j%3)*width/100)*6)+startX, (((j/3)*height/100)*9.5)+startY, streng, 2);
            SetTextColor(memDC, RGB(0,255,0));
        }
    }

    DeleteObject(font);

    //char symbol[2] = {0};
    // for(int i = 0; i<9; i++){
    //     symbol[0] = (*(brett1)).brettarray[i/3][i%3];
    //     TextOut(memDC, ((i%3)*250)+150, ((i/3)*150)+150, symbol,1);
    // }
}
