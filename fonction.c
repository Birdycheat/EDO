#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "fonction.h"

void afficher_fonction_court(fonction F)
{
    printf("Début de la période : %lf\nPrécision : %lf\nNombre de pas : %d\n", F.a, F.h, F.n);
}

void init_fonction(fonction * F, double a, double h, unsigned n)
{
    if ((F->fx = malloc(sizeof(double)*n)) == NULL)
    {
        fprintf(stderr, "L'allocation dans init_fonction a échoué.\n");
        exit(EXIT_FAILURE);
    }
    F->a = a;
    F->h = h;
    F->n = n;
}

void ecrire_fonction(char * dest, fonction F)
{
    FILE * fdest;
    if ((fdest = fopen(dest, "w")) == NULL)
    {
        fprintf(stderr, "Le fichier %s dans la fonction ecrire_fonction n'a pas pu s'ouvrir correctement.\n", dest);
        exit(EXIT_FAILURE);
    }
    double t = F.a;
    for (unsigned i = 0; i < F.n; ++i)
    {
        fprintf(fdest, "%lf\t%lf\n", t, F.fx[i]);
        t+=F.h;
    }
    fclose(fdest);
}

void deriver(fonction * f_der, fonction f)
{
    if (f_der == NULL)
    {
        fprintf(stderr, "Pointeur invalide dans la fonction deriver.\n");
        exit(EXIT_FAILURE);
    }
    if (f.n == 0)
    {
        fprintf(stderr, "Votre fonction doit avoir au moins un point pour être dérivée.\n");
        exit(EXIT_FAILURE);
    }
    init_fonction(f_der, f.a, f.h, f.n);
    if (f.n == 1)
    {
        f_der->fx[0] = 0;
    }
    else
    {
        f_der->fx[0] = (f.fx[1] - f.fx[0])/f.h;
        for (unsigned i = 1; i < f.n - 1; ++i)
        {
            f_der->fx[i] = (f.fx[i+1] - f.fx[i-1])/(2*f_der->h);
        }
        f_der->fx[f.n - 1] = (f.fx[f.n-1] - f.fx[f.n-2])/f.h;
    }
}

void integrer(fonction * f_int, fonction f)
{
    if (f_int == NULL)
    {
        fprintf(stderr, "Pointeur invalide dans la fonction integrer.\n");
        exit(EXIT_FAILURE);
    }
    if (f.n == 0)
    {
        fprintf(stderr, "Votre fonction doit avoir au moins un point pour être intégrée.\n");
        exit(EXIT_FAILURE);
    }
    init_fonction(f_int, f.a, f.h, f.n);
    if (f.n == 1)
    {
        f_int->fx[0] = 0;
    }
    else
    {
        f_int->fx[0] = 0;
        f_int->fx[1] = f.h/2*(f.fx[0] + f.fx[1]);
        for (unsigned i = 2; i < f.n; ++i)
        {
            f_int->fx[i] = f_int->fx[i-2] + f.h/3*(f.fx[i-2] + 4*f.fx[i-1] + f.fx[i]);
        }
    }
}

unsigned comparable(fonction f1, fonction f2)
{
    return (f1.a == f2.a)*(f1.h == f2.h)*(f1.n == f2.n);
}

double erreur(fonction f1, fonction f2)
{
    if (!comparable(f1, f2))
    {
        fprintf(stderr, "Vos fonctions ne sont pas de même dimension.\n");
        exit(EXIT_FAILURE);
    }
    double Ret = 0;
    for (unsigned i = 0; i < f1.n; ++i)
    {
        Ret += (f1.fx[i] - f2.fx[i])*(f1.fx[i] - f2.fx[i]);
    }
    return sqrt(Ret*f1.h);
}

void del_fonction(fonction * F)
{
    F->a = 0;
    F->h = 0;
    F->n = 0;
    free(F->fx);
}