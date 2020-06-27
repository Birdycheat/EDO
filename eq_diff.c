#include <stdio.h>
#include <stdlib.h>
#include "eq_diff.h"

void afficher_eq_diff(const eq_diff E)
{
    printf("fonction n°%p\ny0 = %lf\nAmplitude : %lf\nDébut de l'intervalle : %lf\nNombre de pas : %d\n\nNombre d'arguments : %d\n", E.f, E.y0, E.T, E.a, E.n, E.Nargs);
    printf("[%lf", E.Args[0]);
    for (unsigned i = 1; i < E.Nargs; ++i)
    {
        printf(" ,%lf", E.Args[i]);
    }
    printf("]\n");
}

void init_eq_diff(eq_diff * F, const double (*f)(double, double, const double *, unsigned), const char * src)
{
    FILE * SRC = fopen(src, "r");
    if (SRC == NULL)
    {
        fprintf(stderr, "Le fichier %s n'existe pas.\n", src);
        exit(EXIT_FAILURE);
    }
    fscanf(SRC, "%d", &(F->Nargs));     // Lecture du nombres de constantes
    if((F->Args = malloc(sizeof(double)*F->Nargs)) == NULL)
    {
        fprintf(stderr, "Erreur d'allocation dans la fonction init_eq_diff\n.");
        exit(EXIT_FAILURE);
    }
    for (unsigned i = 0; i < F->Nargs; ++i)
    {
        fscanf(SRC, "%lf", &(F->Args[i]));
    }
    fscanf(SRC, "%d", &(F->n));          // Lecture du nombre de pas
    fscanf(SRC, "%lf", &(F->T));         // Lecture de la taille de la période
    fscanf(SRC, "%lf", &(F->a));         // Lecture du début de la période
    fscanf(SRC, "%lf", &(F->y0));        // Lecture de la condition initiale
    
    fclose(SRC);

    F->f = f;
}

void del_eq_diff(eq_diff * F)
{
    F->Nargs = 0;
    F->n = 0;
    F->T = 0;
    F->a = 0;
    F->y0 = 0;
    F->f = NULL;
    free(F->Args);
}