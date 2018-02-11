#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <string.h>

struct sucursal{
    char nombre[30];
    sucursal *prox;
};

struct subrubros{
    char nombre[30];
    subrubros *abajo;
};

struct rubros{
    char nombre[30];
    rubros *prox;
    subrubros *abajo;
};

struct lote {
    char codigo[30];
    char sucursal[30];
    char rubro[30];
    char subcategoria[30];
    int unidades;
    int exitencia;
    float peso;
    double costo;
    lote *prox;
};

struct cliente{
    char nombre[30];
    cliente *prox;
};