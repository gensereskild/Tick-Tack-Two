#ifndef TICK_TACK_TOE_H
#define TICK_TACK_TOE_H
#include <stdbool.h>

typedef struct brett{
    char brettarray[3][3];
    char status;
} brett;


typedef struct Superbrett{
    brett brettarray[3][3];
} Superbrett;

extern Superbrett superbrett;

void tegnBrett(brett* brett);

void initSuperbrett(Superbrett*);

void tegnSuperBrett(Superbrett*);

int sjekkTotalSeier(Superbrett*);

void userInput(Superbrett*, bool spillerTur, int musX, int musY);

#endif