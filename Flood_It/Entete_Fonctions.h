#ifndef __ENTETE_FONCTIONS__
#define __ENTETE_FONCTIONS__
#include <stdio.h>
#include <stdlib.h>
#include "API_Grille.h"
#include "Liste_case.h"


/* Algorithme qui fait un appel recursif sur les cases adjacentes a la case (i,j) */
/* Retourne dans L la liste des cases de meme couleur que la case i,j */
/* Met -1 dans ces cases */
void trouve_zone_rec(int **M, int dim, int i, int j, int *taille, ListeCase *L, int couleur);

/* Algorithme qui fait un parcour iteratif sur les cases adjacentes a la case (i,j) */
/* Retourne dans L la liste des cases de meme couleur que la case i,j */
/* Met -1 dans ces cases */
void trouve_zone_imp(int **M, int dim, int i, int j, int *taille, ListeCase *L, int couleur);

/* Algorithme qui va retourne le nombre de changements de couleurs necessaires pour que la zone soit uniforme */
/* Les couleurs sont choisit aleatoirement */ /*Recursif - Recursif*/ 
/* Fait appel a sequence_aleatoire_rec2 */
int sequence_aleatoire_rec1(int **M, Grille *G, int dim, int nbcl,int aff);
int sequence_aleatoire_rec1_(int **M, Grille *G, int dim, int nbcl,int cpt,int taille, int aff,ListeCase *L,ListeCase temp);

/* Algorithme qui va retourne le nombre de changements de couleurs necessaires pour que la zone soit uniforme */
/* Les couleurs sont choisit aleatoirement */ /*Recursif - Iteratif */ 
/* Fait appel a sequence_aleatoire_imp2 */
int sequence_aleatoire_imp1(int **M, Grille *G, int dim, int nbcl, int aff);
int sequence_aleatoire_imp1_(int **M, Grille *G, int dim, int nbcl, int cpt, int taille, int aff,ListeCase *L,ListeCase temp);

/* Algorithme qui va retourne le nombre de changements de couleurs necessaires pour que la zone soit uniforme */
/* Les couleurs sont choisit aleatoirement */ /*Iteratif - Recursif */ 
int sequence_aleatoire_rec2(int **M, Grille *G, int dim, int nbcl, int aff);

/* Algorithme qui va retourne le nombre de changements de couleurs necessaires pour que la zone soit uniforme */
/* Les couleurs sont choisit aleatoirement */ /*Iteratif - Iteratif */ 
int sequence_aleatoire_imp2(int **M, Grille *G, int dim, int nbcl, int aff);

/* Fonction qui affiche matrice --> Aide au debug */
void affiche_matrice(int **M, int dim);

/* Fonction qui test que la case(i,j) est entre les dimensions de la matrice*/
/* Test si la couleur de la case coincide avec la couleur et ajoute alors la case a la liste*/
void test_case_couleur(int **M,int i,int j,int dim,int couleur,ListeCase *L);

/* Retourne une couleur differente de la couleur precedente */
int valide_couleur(int couleur,int nbcl,int **M);

/* Met a jour les couleurs precedemment modifie dans la matrice M*/
void mj_couleur_matrice(ListeCase temp,ListeCase *L,int **M,int couleur);

/* Affiche la grille graphiquement */
void afficheGraphe2(int **M,Grille *G,int dim,int aff);
#endif  /* __ENTETE_FONCTIONS__ */