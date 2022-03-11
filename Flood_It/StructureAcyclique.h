#ifndef __StructureAcyclique__
#define __StructureAcyclique__
#include "Entete_Fonctions.h"

typedef struct
{
    int dim;        /* dimension de la grille */
    int nbcl;       /* nombre de couleurs */
    ListeCase Lzsg; /* Liste des cases de la zone Zsg */
    ListeCase *B;   /* Tableau de listes de cases de la bordure*/
    int **App;      /* Tableau a double entree des appartenances */
} S_Zsg;

/* Initialise une structure zsg en fonction de sa dimension et de son nombre de couleur*/
S_Zsg *init_Zsg(int dim,int nbcl);

/* Ajoute une case dans la liste Lzsg  */
int ajoute_Zsg(S_Zsg *Z, int i, int j);

/* Ajoute une case dans la bordure d’une couleur  donnee */
int ajoute_Bordure(S_Zsg *Z, int i, int j,int couleur);

/*  Retourne 1 si une case est dans LZsg et retourne 0 sinon*/
int appartient_Zsg(S_Zsg *Z, int i, int j);

/* Retourne 1 si une case est dans la bordure de couleur donnee et retourne 0 sinon*/
int appartient_Bordure(S_Zsg *Z, int i, int j,int couleur);

/* Met a jour les champs Lzsg et B d’une S_Zsg lorsque qu’une case k,l de couleur cl, qui est dans la bordure B[cl],
   doit basculer dans Lzsg */
int agrandit_Zsg(int **M, S_Zsg *Z, int couleur, int i, int j);
void agrandi_zone(int **M,S_Zsg *Z, int i, int j, int dim, int couleur, ListeCase *L,int *cpt);

/*fonction qui accélére considérablement le jeu par rapport à l’exercice précédent.*/
int sequence_aleatoire_rapide(int **M, Grille *G, int dim,int nbcl, int aff);

void affiche_liste(ListeCase L);
void affiche_matrice(int **M, int dim);

void free_Zsg(S_Zsg *Z);


#endif