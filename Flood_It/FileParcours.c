#include "FileParcours.h"

void initFile(File *F)
{
    F->first = NULL;
    F->last = NULL;
}

int estFileVide(File *F)
{
    return (F->first == NULL && F->last == NULL);
}

void enfile(File *F,Sommet *s)
{
    Cell *c;
    c = (Cell *)malloc(sizeof(Cell));
    c->s = s;
    c->suivant = NULL;
    if (estFileVide(F))
    { // Le cas particulier
        F->first = c;
        F->last = c;
    }
    else
    {
        F->last->suivant = c;
        F->last = c;
    }
}

Sommet *defile(File *F)
{
    Sommet *sommet;
    if (!estFileVide(F))
    {
        sommet= F->first->s;
        Cell *cell=F->first;
        F->first = F->first->suivant;
        free(cell);
        if (F->first == NULL) // Le cas particulier
            F->last = NULL;
        return sommet;
    }
}


void afficheFile(File F)
{
    Cell *c = F.first;
    printf("[");
    while (c != NULL)
    {
        printf("(%d)", c->s->num);
        c = c->suivant;
    }
    printf("]\n");
}