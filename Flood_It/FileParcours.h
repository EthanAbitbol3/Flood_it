#ifndef __FileParcours__
#define __FileParcours__

#include "Entete_Fonctions.h"
#include "Graphe.h"

typedef struct
cell{
    Sommet *s;
    struct cell *suivant;
} Cell;
// pour dissocier, cellule de la file 
typedef struct
{

    Cell *first;
    Cell *last;
} File;

//Pour etre en 0(1), on a les elements du premier et du dernier pour pouvoir ajouter et sup rapidement. 
//Initialise la file
void initFile(File *F);
//Test si la file est vide
int estFileVide(File *F);
//Ajoute un element de la file
void enfile(File *F,Sommet *s);
//Enleve un element de la file
Sommet *defile(File *F);
//Afficher les valeurs de la file : du plus ancien au plus recent
void afficheFile(File F);
#endif
