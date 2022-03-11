#ifndef __ParcoursLargeur__
#define __ParcoursLargeur__
#include "Entete_Fonctions.h"
#include "Graphe.h"
#include "FileParcours.h"
#include "MaxBordure.h"

// Fonction qui cherche le plus court chemin entre deux sommets 
// taille chemin sera la taille du plus court chemin
// la fonction retourne un tableau de couleur, le tableau sera range dans l ordre des couleurs qui seront affiche
int *plus_court_chemin(Sommet *depart, Sommet *arrive, int *taille_chemin);
//Fonction qui retourne le tableau de couleur
int *tableauCouleur(Sommet *depart, Sommet *arrive,int taille);
/* Fonction implementant la parcours largeur puis strategie max-bordure*/
int ResoudreParcoursLargeur(int **M, Grille *G, int dim, int nbcl, int aff);
#endif
