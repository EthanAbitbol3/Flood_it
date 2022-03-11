#ifndef __Graphe__
#define __Graphe__
#include "Entete_Fonctions.h"

typedef struct sommet Sommet;

/* Element d’une liste cha\^in\’ee de pointeurs sur Sommets */
typedef struct cellule_som
{
    Sommet *sommet;
    struct cellule_som *suiv;
} Cellule_som;

struct sommet
{
    int num;         /* Numero du sommet (sert uniquement a l’affichage) */
    int cl;          /* Couleur d’origine du sommet-zone */
    int marque ;      /* Indique le statut d'un sommet : 0 si dans Zsg, 1 si dans bordure, 2 si non visite */
    ListeCase cases; /* Listes des cases du sommet-zone */
    int nbcase_som;  /* Nombre de cases de cette liste */
    int distance; /* Nombre d’aretes reliant ce sommet a la racine du parcours en largeur */ 
    Sommet *pere; /* Pere du sommet dans l’arborescence du parcours en largeur */
    Cellule_som *sommet_adj; /* Liste des ar\eteses pointeurs sur les sommets
adjacents */
};

typedef struct graphe_zone
{
    int nbsom;        /* Nombre de sommets dans le graphe */
    Cellule_som *som; /* Liste chainee des sommets du graphe */
    Sommet ***mat;    /* Matrice de pointeurs sur les sommets indiquant a quel sommet appartient une case (i,j) de la grille */
} Graphe_zone;


/*ajoute un pointeur sur Sommet a une liste chaˆın ́ee de Cellule_som passee en parametre*/
void ajoute_liste_sommet(Cellule_som **cs ,Sommet *s);
/* detruit une liste chaınee de Cellule_som SANS detruire les sommet pointees par cette liste.*/
void detruit_liste_somme(Cellule_som *cs);
/*met a jour deux sommet s1 et s2 en indiquant qu’ils sont adjacents l’un de l’autre*/
void ajoute_voisin(Sommet *s1, Sommet *s2);
/*test si deux sommets sont adjacents*/
int test_adjacent(Sommet *s1, Sommet *s2);

/*initialise la structure d'un graphe*/
Graphe_zone *init_graphe_zone(int dim);
/*initialise la structure d'un sommet*/
Sommet *init_sommet(int num,int cl);
/*mise a jour de la matrice */
void mj_matrice(ListeCase *L,int **M,Sommet ***mat,int couleur,Sommet *s);
/*On cree le graphe entier*/
Graphe_zone *cree_graphe_zone(int **M,int dim,int nbcl);

/*affiche la liste chaine cellule_som*/
void affiche_cellule_som(Cellule_som *cs);
/*affiche le graphe entier en mode texte*/
void affiche_graphe(Graphe_zone *g,int dim);

/*free le graphe */
void desalloue_graphe(Graphe_zone *g,int dim );
/* free le sommet */
void desalloue_sommet(Sommet *s);
/* free la matrice */
void dessalloue_matrice(Graphe_zone *g,int dim);

/*affiche graphiquement la grille */
void afficheGraphe(Graphe_zone *g,Grille *G,int dim,int couleur,int aff);

#endif
