#pragma once

typedef struct eq_diff_st
{
    double (*f)(double, double, double *, unsigned);    // Fonction de l'équation y' = F(t,y)
    double y0;                                          // Condition initiale
    double a;                                           // Début de l'intervalle
    double T;                                           // Période étudié --> intervalle [a;a+T]
    double * Args;                                      // Arguments constants de la fonction f
    unsigned Nargs;                                     // Nombre de paramètres de la fonction f
    unsigned n;                                         // Nombre de pas de temps
}eq_diff;


void afficher_eq_diff(eq_diff);

void init_eq_diff(eq_diff *, double (*)(double, double, double *, unsigned), char *);

void del_eq_diff(eq_diff *);



