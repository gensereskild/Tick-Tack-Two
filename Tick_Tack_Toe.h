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

extern bool spiller1tur;

void tegnBrett(brett* brett);

void initSuperbrett(Superbrett*);

void tegnSuperBrett(Superbrett*);

//Returnerer 0 for ikke ferdig, 1 For spiller X, 2 for spiller O, 3 for TIE.
int sjekkTotalSeier(Superbrett*);

void userInput(Superbrett*, bool *spillerTur, int musX, int musY);

#endif