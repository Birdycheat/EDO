#pragma once

typedef struct fonction_st
{
    double * fx;
    double h;
    double a;
    unsigned n;
}fonction;


void init_fonction(fonction * f, double, double, unsigned);

void ecrire_fonction(const char *, const fonction);

void del_fonction(fonction *);

void afficher_fonction_court(const fonction);

void deriver(fonction *, const fonction);

double erreur(const fonction, const fonction);

unsigned comparable(const fonction, const fonction);

void integrer(fonction *, const fonction);
