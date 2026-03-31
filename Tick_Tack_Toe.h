#ifndef TICK_TACK_TOE_H
#define TICK_TACK_TOE_H

typedef struct brett{
    char brettarray[3][3];
    char status;
} brett;

void tegnBrett(brett* brett);
#endif