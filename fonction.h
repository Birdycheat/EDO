#pragma once

typedef struct fonction_st
{
    double * fx;
    double h;
    double a;
    unsigned n;
}fonction;


void init_fonction(fonction * f, double, double, unsigned);

void ecrire_fonction(char *, fonction);

void del_fonction(fonction *);

void afficher_fonction_court(fonction);

void deriver(fonction *, fonction);

double erreur(fonction, fonction);

unsigned comparable(fonction, fonction);

void integrer(fonction *, fonction);
