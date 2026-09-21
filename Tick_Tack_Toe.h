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

//Verdien til AktivtBrett er det brettet som man er nødt til å spille på nå.
//Har Verdi fra 0-8, har verdi 10 hvis man kan velge brett (Når noen blir ferdig med et brett eller drar til et ferdig brett)
extern int aktivtBrett;

void tegnBrett(brett* brett);

void initSuperbrett(Superbrett*);

void tegnSuperBrett(Superbrett*);

//Returnerer 0 for ikke ferdig, 1 For spiller X, 2 for spiller O, 3 for TIE.
int sjekkTotalSeier(Superbrett*);

void userInput(Superbrett*, bool *spillerTur, int musX, int musY);

#endif