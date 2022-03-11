#include "Entete_Fonctions.h"

/* Exercice 1 */
/* ---------------------------------------------------------------------------------------- */

/* Question 1 */
/* ---------------------------------------------------------------------------------------- */
/*permet de chosir une nouvelle couleur aleatoirement*/
int valide_couleur(int couleur,int nbcl,int **M){
  do
    {
      couleur = rand() % nbcl;
    } while (couleur == M[0][0]);
    return couleur;
}
// 1/nbcl

/*une fois la nouvelle couleur choisis , on dois mettre a jour la zone avec cette couleur*/
void mj_couleur_matrice(ListeCase temp,ListeCase *L,int **M,int couleur){
    temp=*L;
    while (temp)
    {
      M[temp->i][temp->j] = couleur;
      temp = temp->suiv;
    }
}
//0(L)

/*Trouve la zone d'une case recursivement*/
void trouve_zone_rec(int **M, int dim, int i, int j, int *taille, ListeCase *L, int couleur)
{
  // Test coordonne valide
  if (i < 0 || j < 0 || i > (dim - 1) || j > (dim - 1))
    return;
  /*une fois la case visite , sa couleur passe a -1 pour dire qu'elle a deja ete visite */
  // Verifie si la case a deja etait verifie
  if (M[i][j] == -1)
    return;

  // Test si la case est de la bonne couleur
  if (M[i][j] == couleur)
  {
    M[i][j] = -1;
    ajoute_en_tete(L, i, j);
    (*taille)++; //nombre de cases dans la zone 

    // Appel recursif sur les cases adjacentes
    trouve_zone_rec(M, dim, i - 1, j, taille, L, couleur);
    trouve_zone_rec(M, dim, i + 1, j, taille, L, couleur);
    trouve_zone_rec(M, dim, i, j - 1, taille, L, couleur);
    trouve_zone_rec(M, dim, i, j + 1, taille, L, couleur);
  }
}
//meilleur cas omega(1), pire cas en O(dim²), complexite en 0(dim²)

/* Question 2 */
/* Recursif - Recursif */
/* ---------------------------------------------------------------------------------------- */
int sequence_aleatoire_rec1(int **M, Grille *G, int dim, int nbcl, int aff)
{
   ListeCase *l = (ListeCase *)malloc(sizeof(ListeCase));
   ListeCase temp=NULL;
  // Appel recursif en inialisant le compteur et la taille a 0
  return sequence_aleatoire_rec1_(M, G, dim, nbcl, 0, 0, aff,l,temp);
}
// pour eviter de recreer a chaque etape recursivement ligne 60 et 61 

int sequence_aleatoire_rec1_(int **M, Grille *G, int dim, int nbcl, int cpt, int taille, int aff,ListeCase *L,ListeCase temp)
{
  // Test si toute la grille est uniforme
  if (taille == dim * dim) //cas d'arret 
  {
    free(L);
    return cpt;
  }
  else
  {
    taille = 0;
    init_liste(L);
    int couleur = M[0][0];
    // Change la couleur jusqu'a avoir une couleur differente que la case de la matrice(0,0)
    couleur=valide_couleur(couleur,nbcl,M);
    // Appel a la fonction recursive pour avoir dans la liste L les cases de la meme couleur
    trouve_zone_rec(M, dim, 0, 0, &taille, L, M[0][0]);
    // On remet les cases dans la grille a la couleur correspondante car elles ont etaient mise a -1
    mj_couleur_matrice(temp,L,M,couleur);

    detruit_liste(L);
    
    /* Affichage de la grille */
    afficheGraphe2(M,G,dim,aff);
    return sequence_aleatoire_rec1_(M, G, dim, nbcl, cpt + 1, taille, aff,L,temp);
  }
}
// 0(dim⁴) car somme de 1 a dim²



/* Exercice 2 */
/* ---------------------------------------------------------------------------------------- */

/* Question 1 */
/* ---------------------------------------------------------------------------------------- */
void test_case_couleur(int **M, int i, int j, int dim, int couleur, ListeCase *L)
{
  // Test coordonne valide
  if (i >= 0 && j >= 0 && i <= (dim - 1) && j <= (dim - 1))
  {
    // Test si la case est de la bonne couleur
    if (M[i][j] == couleur)
    {
      ajoute_en_tete(L, i, j);
    }
  }
}
// 0(1)

void trouve_zone_imp(int **M, int dim, int i, int j, int *taille, ListeCase *L, int couleur)
{
  ListeCase *l = (ListeCase *)malloc(sizeof(ListeCase));
  init_liste(l);
  int x, y;

  // Test si la case est de la bonne couleur
  if (M[i][j] == couleur)
  {
    ajoute_en_tete(l, i, j);
  }

  while (*l)
  {
    // Effet de pile
    enleve_en_tete(l, &x, &y);
    ajoute_en_tete(L, x, y);

    if (M[x][y] == couleur) // deja visite 
    {
      M[x][y] = -1;
      (*taille) += 1;
    }

    // Testes les cases adjacentes
    test_case_couleur(M, x + 1, y, dim, couleur, l);
    test_case_couleur(M, x, y + 1, dim, couleur, l);
    test_case_couleur(M, x - 1, y, dim, couleur, l);
    test_case_couleur(M, x, y - 1, dim, couleur, l);
  }
  free(l);
}
// 0(l²)

/* Question 2 */
/* Iteratif - Iteratif */
int sequence_aleatoire_imp2(int **M, Grille *G, int dim, int nbcl, int aff){
  int taille = 0;
  int cpt = 0;
  int couleur = M[0][0];
  ListeCase *L = (ListeCase *)malloc(sizeof(ListeCase));
  ListeCase temp=NULL;
  while (taille != dim * dim)
  {
    taille = 0;
    init_liste(L);
    // Change la couleur jusqu'a avoir une couleur differente que la case de la matrice(0,0)
    couleur=valide_couleur(couleur,nbcl,M); 
    cpt++; //a chaque fois qu'on change de couleur
    // Appel a la fonction iteratif pour avoir dans la liste L les cases de la meme couleur
    trouve_zone_imp(M, dim, 0, 0, &taille, L, M[0][0]);
    // On remet les cases dans la grille a la couleur correspondante car elles ont etaient mise a -1
    mj_couleur_matrice(temp,L,M,couleur);

    detruit_liste(L);
     /* Affichage de la grille */
    afficheGraphe2(M,G,dim,aff);
 
  }
  free(L); // car detruit : detruit les elements de la liste mais pas L 
  return cpt;
}
/* ---------------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------------- */

/* Iteratif - Recursif */
int sequence_aleatoire_rec2(int **M, Grille *G, int dim, int nbcl, int aff)
{
  int taille = 0;
  int cpt = 0;
  int couleur = M[0][0];
  ListeCase *L = (ListeCase *)malloc(sizeof(ListeCase));
  ListeCase temp=NULL;

  while (taille != dim * dim)
  {
    taille = 0;
    init_liste(L);
    // Change la couleur jusqu'a avoir une couleur differente que la case de la matrice(0,0)
    couleur=valide_couleur(couleur,nbcl,M);
    cpt++;
    // Appel a la fonction recursive pour avoir dans la liste L les cases de la meme couleur
    trouve_zone_rec(M, dim, 0, 0, &taille, L, M[0][0]);
    // On remet les cases dans la grille a la couleur correspondante car elles ont etaient mise a -1
     mj_couleur_matrice(temp,L,M,couleur);

    detruit_liste(L);

    /* Affichage de la grille */
     afficheGraphe2(M,G,dim,aff);
  }
  free(L);
  return cpt;
}

/* recursif - iteratif */

int sequence_aleatoire_imp1(int **M, Grille *G, int dim, int nbcl, int aff)
{
  ListeCase *l = (ListeCase *)malloc(sizeof(ListeCase));
  ListeCase temp=NULL;
  // Appel recursif en inialisant le compteur et la taille a 0
  return sequence_aleatoire_imp1_(M, G, dim, nbcl, 0, 0, aff,l,temp);
}

int sequence_aleatoire_imp1_(int **M, Grille *G, int dim, int nbcl, int cpt, int taille, int aff,ListeCase *L,ListeCase temp)
{

  // Test si toute la grille est uniforme
  if (taille == dim * dim)
  {
    free(L);
    return cpt;
  }
  else
  {
    taille = 0;
    init_liste(L); // on reemunere a chaque fois les elements de la zsg 
    int couleur = M[0][0];
    // Change la couleur jusqu'a avoir une couleur differente que la case de la matrice(0,0)
    couleur=valide_couleur(couleur,nbcl,M);
    // Appel a la fonction iterative pour avoir dans la liste L les cases de la meme couleur
    trouve_zone_imp(M, dim, 0, 0, &taille, L, M[0][0]);

    temp=*L;
    // On remet les cases dans la grille a la couleur correspondante car elles ont etaient mise a -1
    mj_couleur_matrice(temp,L,M,couleur);

    detruit_liste(L);

    /* Affichage de la grille */
     afficheGraphe2(M,G,dim,aff);

    return sequence_aleatoire_imp1_(M, G, dim, nbcl, cpt + 1, taille, aff,L,temp);
  }
}
void afficheGraphe2(int **M,Grille *G,int dim,int aff){
     /* Affichage de la grille */
    if (aff == 1)
    {
      int i, j;
      for (i = 0; i < dim; i++)
        for (j = 0; j < dim; j++)
        {
          Grille_attribue_couleur_case(G, i, j, M[i][j]);
        }

      Grille_redessine_Grille(G);
      SDL_Delay(100);
      //Grille_attente_touche();
    }
}

/* Exercice 2 --> Question 2  */
/* ---------------------------------------------------------------------------------------- */
/* Exercice 1 --> Question 3  */
/*
Comme nous avons pu le remarquer apres avoir fais plusieurs test.

1/ Nous avons observé que lorsque la dimension est la meme et que nous changeons le niveau de peu, 
il y a le meme nombre d'essai, or lorsque nous augmentons fortmeent le niveau, il ya moins d'essais.

2/ nous avons pu aussi remarquer que avec la recursivite , le programme est limite et au bout d'une certaine dimension, il ya erreur de segmentation, contrairement a la fonction de l'exo 2 (derecursification) 
qui permet d'obtenir des resultats pour des dimensions beaucoup plus grandes.

3/ De plus, lorsque nous avons comparé les fonctions des 2 exercices(exo 1 et 2), 
on obtiens le meme nombre d'essai et la recursivite est plus rapide.
*/
