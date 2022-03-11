#ifndef __MaxBordure__
#define __MaxBordure__
#include "API_Gene_instance.h"
#include "Graphe.h"

typedef struct
{
    int dim;
    int nbcl;       /* nombre de couleurs */
    int *taille ;    /* Tableau de la taille de chaque couleur */
    Cellule_som *L ; /* Liste des Sommet de la zone Zsg */
    Cellule_som **B;   /* Tableau de Cellule_som de cases de la bordure*/
} S_Zsg2;

/* Initialise une structure zsg en fonction de sa dimension et de son nombre de couleur*/
S_Zsg2 *init_Zsg2(int dim,int nbcl);

/* Ajoute une case dans la bordure d’une couleur  donnee */
void ajoute_Bordure2(S_Zsg2 *Z, Sommet *s);
/*ajoute une case dans la zsg*/
void ajoute_Zsg2(S_Zsg2 *Z,Sommet *s);

/*  Retourne 1 si une case est dans LZsg et retourne 0 sinon*/
int appartient_Zsg2(Sommet *s);
/* Retourne 1 si une case est dans la bordure de couleur donnee et retourne 0 sinon*/
int appartient_Bordure2(Sommet *s);


/*mise a jour de la bordure */
void mj_bordure(S_Zsg2 *Z, Sommet *s);
/* Met a jour les champs Lzsg et B d’une S_Zsg lorsque qu’une case k,l de couleur cl, qui est dans la bordure B[cl],doit basculer dans Lzsg */
void agrandit_Zsg2(S_Zsg2 *Z, int couleur);

/*renvoi le max */
int max_index(int *taille, int nbcl);
/*le jeu s’arrete quand la bordure est vide pour toute couleur*/
int fin_jeu(Cellule_som **B,int nbcl);

/* la fonction implementant la strategie max-bordure*/
int maxBordure(int **M, Grille *G, int dim, int nbcl, int aff);

/*Libere la zsg*/
void free_Zsg2(S_Zsg2 *Z);

/*Affiche la bordure */
void affiche_bordure(Cellule_som **cs,int nbcl);

#endif