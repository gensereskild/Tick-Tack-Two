#ifndef TICK_TACK_TOE_H
#define TICK_TACK_TOE_H

typedef struct brett{
    char brettarray[3][3];
    char status;
} brett;


typedef struct Superbrett{
    brett brettarray[3][3];
} Superbrett;

void tegnBrett(brett* brett);

void initSuperbrett(Superbrett*);

void tegnSuperBrett(Superbrett*);

int sjekkTotalSeier(Superbrett*);

#endif