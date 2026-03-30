#include <stdio.h>
#include "Tick_Tack_Toe.h"

void tegnBrett( brett *brett1){
    for(int y = 0; y<3; y++){
        printf("\n%c %c %c", brett1->brettarray[y][0],brett1->brettarray[y][1],brett1->brettarray[y][2]);
    }
}