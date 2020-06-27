#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "eq_diff.h"
#include "fonction.h"

void euler_explicite(fonction * Ret, const eq_diff E)
{
    if (Ret == NULL)
    {
        fprintf(stderr, "Le paramètre de retour de la fonction euler_explicite est invalide.\n");
    }
    double h = E.T/E.n;
    init_fonction(Ret, E.a, h, E.n + 1);
    Ret->fx[0] = E.y0;
    for (unsigned i = 1; i <= E.n; ++i) // On prend un point en plus pour compléter l'intervalle
    {
        Ret->fx[i] = Ret->fx[i-1] + h*E.f(h*(i-1), Ret->fx[i-1], E.Args, E.Nargs);
    }
}

void euler_implicite(fonction * Ret, const eq_diff E)
{
    if (Ret == NULL)
    {
        fprintf(stderr, "Le paramètre de retour de la fonction euler_implicite est invalide.\n");
    }
    double h, tmp, pt_fixe;
    unsigned iter = 0;

    h = E.T/E.n;
    init_fonction(Ret, E.a, h, E.n + 1);
    Ret->fx[0] = E.y0;
    for (unsigned i = 1; i <= E.n; ++i) // On prend un point en plus pour compléter l'intervalle
    {
        pt_fixe = Ret->fx[i-1];
        do
        {
            tmp = pt_fixe;
            pt_fixe = Ret->fx[i-1] + h*E.f(h*i, pt_fixe, E.Args, E.Nargs);
        }while(fabs(tmp - pt_fixe)/(1 + fabs(pt_fixe)) > 10e-3 && iter < 100);
        if (iter == 100)
        {
            fprintf(stderr, "La méthode du point fixe ne converge pas en ce point %lf pour la méthode d'Euler implicite\n", i*h);
            exit(EXIT_FAILURE);
        }
        Ret->fx[i] = pt_fixe;
    }
}

void crank_nicolson(fonction * Ret, const eq_diff E)
{
    if (Ret == NULL)
    {
        fprintf(stderr, "Le paramètre de retour de la fonction crank_nicolson est invalide.\n");
    }
    double h, tmp, pt_fixe;
    unsigned iter = 0;

    h = E.T/E.n;
    init_fonction(Ret, E.a, h, E.n + 1);
    Ret->fx[0] = E.y0;
    for (unsigned i = 1; i <= E.n; ++i) // On prend un point en plus pour compléter l'intervalle
    {
        pt_fixe = Ret->fx[i-1];
        do
        {
            tmp = pt_fixe;
            pt_fixe = Ret->fx[i-1] + h/2*(E.f(h*i, pt_fixe, E.Args, E.Nargs) + E.f(h*(i-1), Ret->fx[i-1], E.Args, E.Nargs));
        }while(fabs(tmp - pt_fixe)/(1 + fabs(pt_fixe)) > 10e-3 && iter < 100);
        if (iter == 100)
        {
            fprintf(stderr, "La méthode du point fixe ne converge pas en ce point %lf pour la méthode de Crank Nicolson\n", i*h);
            exit(EXIT_FAILURE);
        }
        Ret->fx[i] = pt_fixe;
    }
}

void RK4(fonction * Ret, const eq_diff E)
{
    if (Ret == NULL)
    {
        fprintf(stderr, "Le paramètre de retour de la fonction RK4 est invalide.\n,");
        exit(EXIT_FAILURE);
    }

    double h, k1, k2, k3, k4;
    h = E.T/E.n;
    init_fonction(Ret, E.a, h, E.n + 1);
    Ret->fx[0] = E.y0;
    for (unsigned i = 1; i <= E.n; ++i)
    {
        k1 = E.f(h*(i-1), Ret->fx[i-1], E.Args, E.Nargs);
        k2 = E.f(h*(i-0.5), Ret->fx[i-1] + h*k1/2, E.Args, E.Nargs);
        k3 = E.f(h*(i-0.5), Ret->fx[i-1] + h*k2/2, E.Args, E.Nargs);
        k4 = E.f(h*i, Ret->fx[i-1] + h*k3, E.Args, E.Nargs);
        Ret->fx[i] = Ret->fx[i-1] + h*(k1+2*k2+2*k3+k4)/6;
    }
}