//Målet med programmet er bare å ha 3 på rad i terminalen basically
//#pragma once
#include <stdio.h>
#include <stdbool.h>
#include "Vindu.h"
#include "Tick_Tack_Toe.h"
#include <windows.h>


//Status er 0 dersom brettet framleis pågår, 1 dersom X har vunnet, 2 Dersom O har vunnet og 3 dersom tie


// void tegnBrett( brett *brett1){
//     for(int y = 0; y<3; y++){
//         printf("\n%c %c %c", brett1->brettarray[y][0],brett1->brettarray[y][1],brett1->brettarray[y][2]);
//     }
// }

//Hva er den best måten å tegne superbrett på:
//Er nødt til å printe en lang linje

void tegnSuperBrett(Superbrett *Superbrett){
    printf("\n\n\n\n\n\n\n\n");
    for(int brett_rad = 0; brett_rad<3; brett_rad++){
        printf("----------------------------\n");
        for (int rad = 0; rad < 3; rad++)
        {
            for (int brett_kolonne = 0; brett_kolonne <3; brett_kolonne++){
            printf("| %c %c %c |",Superbrett->brettarray[brett_rad][brett_kolonne].brettarray[rad][0],
                Superbrett->brettarray[brett_rad][brett_kolonne].brettarray[rad][1],
                Superbrett->brettarray[brett_rad][brett_kolonne].brettarray[rad][2]);
            }
            printf("\n");
        }
        printf("----------------------------\n");
    }
}

//Hadde vært lettere å spille hvis man velger posisjon 1-9 IMO.
//Når man trykker får man pikser kordinater, gjør om dette til %kordinater kanskje også
//sjekker hvilket brett og hvilken rute pikslene er innom.

void userInput(struct Superbrett *superbrett, bool *spiller1tur, int musX, int musY){
    int valgtBrett = 20;
    for(int i =0; i<9; i++){
        //Det er denne funksjonen vi bruker for brettene, så vi kan bare mappe til piksler og ruter
        //tegnBrettGrafikk(20.0 + 20.0*(i/3), 7.5 + 27.0*(i%3), 17.0, 25.0);
        
        if((musX>(20 + 20*(i%3))*width/100) && (musX<(37 + 20*(i%3))*width/100) && 
        (musY>(7.5+27*(i/3))*height/100) && (musY<(32.5+27*(i/3))*height/100)){
            printf("Du traff første brett %d! \n",i);
            valgtBrett = i;
        }
    }
    if (valgtBrett==20) return;

    int startBrettX = (20 + 20*(valgtBrett%3))*width/100;
    int startBrettY = (7.5 + 27*(valgtBrett/3))*height/100;

    musX -= startBrettX;
    musY -= startBrettY;

    printf("NyVerdi til mus %d, %d \n", musX, musY);
    int valgtRute = 0;
    for(int j = 0; j<9; j++){
        if((musX>(17*width/100)*((float)(j%3)/3)) && (musY>(25*height/100)*((float)(j/3)/3))){
            if(j>valgtRute){
                valgtRute=j;
            }
        }
    }
    printf("Du tryket på rute %d \n", valgtRute);

    brett *brett1 = &(superbrett->brettarray[valgtBrett/3][valgtBrett%3]);


    if(brett1->status!=0){
        printf("Dette Brettet er ugyldig");
        return;
    }

    if(brett1->brettarray[valgtRute/3][valgtRute%3] !='E'){
        printf("Denne posisjonen er opptatt");
        return;
    } 

    if(*spiller1tur){
        brett1->brettarray[valgtRute/3][valgtRute%3]='X';
        *spiller1tur = false;
    }
    else{
        brett1->brettarray[valgtRute/3][valgtRute%3]='O';
        *spiller1tur = true;
    }
    tegnSuperBrett(superbrett);
}

int sjekk3(char a, char b, char c){
    if(a==b && b==c && a != ' ' && a!='E'){
        if(a == 'X') return 1;
        return 2;
    }
    return 0;
}

int sjekkSeier( brett *brett1){
    int returverdi =0;
    for(int i = 0; i<3; i++){
            returverdi = sjekk3(brett1->brettarray[i][0], brett1->brettarray[i][1], brett1->brettarray[i][2]);
            if (returverdi!=0) return returverdi;
            returverdi = sjekk3(brett1->brettarray[0][i], brett1->brettarray[1][i], brett1->brettarray[2][i]);
            if (returverdi!=0) return returverdi;
    }
    returverdi = sjekk3(brett1->brettarray[0][0], brett1->brettarray[1][1], brett1->brettarray[2][2]);
    if (returverdi!=0) return returverdi;
    returverdi = sjekk3(brett1->brettarray[0][2], brett1->brettarray[1][1], brett1->brettarray[2][0]);
    if (returverdi!=0) return returverdi;
    return returverdi;
}

//Returnerer 0 for ikke ferdig, 1 For spiller X, 2 for spiller O, 3 for TIE.

int sjekkTotalSeier(Superbrett *Superbrett){
    for(int i = 0; i<9; i++){
        brett *brett = &(Superbrett->brettarray[i/3][i%3]);
        brett->status=sjekkSeier(brett);
    }
    //Formaterer superbrett som vanlig brett
    brett formatert;
    // = {
    //     .brettarray={{'O','O','E'},{'E','E','E'},{'E','E','E'}},
    //     .status=0
    // };
    for(int i =0; i<9; i++){
        if(Superbrett->brettarray[i/3][i%3].status == 0){
            formatert.brettarray[i/3][i%3]='E';
        }
        else if(Superbrett->brettarray[i/3][i%3].status == 1){
            formatert.brettarray[i/3][i%3]='X';
        }
        else{
            formatert.brettarray[i/3][i%3]='O';
        }
    }
    int Superstatus = sjekkSeier(&formatert);
    //tegnBrett(&formatert);
    //printf("\n %d \n", Superstatus);
    return Superstatus;
}

void initSuperbrett(Superbrett *Superbrett){
    brett tomtBrett = {
        .brettarray={{'E','E','E'},{'E','E','E'},{'E','E','E'}},
        .status = 0
    };

    for(int kolonne = 0; kolonne<3; kolonne++){
        for(int rad = 0; rad<3; rad++){
            Superbrett->brettarray[rad][kolonne] = tomtBrett;
        }
    }
}

//Idéer for store bokstaver
// \ /
//  X
// / \/
//  _
// / \\\//
// \_/

// int main(){
//     Superbrett Superbrett = {
//         .brettarray={{},{},{},}
//     };
//     bool spiller1tur = true;
//     int status=0;
//     //Tur runde
//     InitSuperbrett(&Superbrett);
//     tegnSuperBrett(&Superbrett);

//     while (sjekkTotalSeier(&Superbrett)==0){
//     userInput(&Superbrett, spiller1tur);
//     tegnSuperBrett(&Superbrett);
//     sjekkTotalSeier(&Superbrett);
//     spiller1tur ? (spiller1tur=false) : (spiller1tur = true);
//     }  

// //     while(status==0){
        
// //         spiller1tur ? (spiller1tur=false) : (spiller1tur = true);
// //     }
// }