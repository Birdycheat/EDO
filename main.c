#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "fonction.h"
#include "eq_diff.h"
#include "methodes.h"

double standard(double t, double y, double * Args, unsigned n)
{
    if (n != 0)
    {
        fprintf(stderr, "Le nombre d'arguments demandé est de 0 et vous en avez mis %d\n", n);
        exit(EXIT_FAILURE);
    }
    return y;
}

double standard2(double t, double y, double * Args, unsigned n)
{
    if (n != 1)
    {
        fprintf(stderr, "Le nombre d'arguments demandé est de 1 et vous en avez mis %d\n", n);
        exit(EXIT_FAILURE);
    }
    return sin(Args[0]*log(1 + fabs(y)));
}

double riccati(double t, double y, double * Args, unsigned Nargs)
{
    if (Nargs != 3)
    {
        fprintf(stderr, "Le nombre d'arguments demandé est de 1 et non de %d.\n", Nargs);
        exit(EXIT_FAILURE);
    }
    return Args[0] + Args[1]*log(1+t)*y + Args[2]*sin(t)*y*y;
}

int main(void)
{
    fonction Res, Res_int;
    eq_diff E;

    init_eq_diff(&E, standard, "src");
    RK4(&Res, E);
    integrer(&Res_int, Res);
    ecrire_fonction("RK4", Res);
    ecrire_fonction("RK4 primitive", Res_int);
    
    del_fonction(&Res);
    del_fonction(&Res_int);
    del_eq_diff(&E);

    return EXIT_SUCCESS;
}