#include "StructureAcyclique.h"
#include <time.h>



S_Zsg *init_Zsg(int dim, int nbcl)
{
    /*allocation de la memoire pour la structure S_Zsg*/
    S_Zsg *Z = (S_Zsg *)malloc(sizeof(S_Zsg));
    /*Test si l'allocation a marche*/
    if (Z == NULL)
    {
        printf("Erreur allocation de Zsg");
    }
    /*Initialisation de dim, nbcl et de la zone Lzsg*/
    Z->dim = dim;
    Z->nbcl = nbcl;
    Z->Lzsg = NULL;

    /*allocation de la memoire pour le tableau de liste correspondant a la bordure*/
    Z->B = malloc(nbcl * sizeof(ListeCase *));
    /*Test si l'allocation a marche*/
    if (Z->B == NULL)
    {
        printf("Erreur allocation de ListeCase (Z->B) ");
    }

    int i, j;
    /*Initialisation de chaque case du tableau comprenant une liste*/
    for (i = 0; i < nbcl; i++)
    {
        Z->B[i] = NULL;
    }

    /*allocation de la memoire pour le double tableau de int correspondant aux appartenances */
    Z->App = (int **)malloc(dim * sizeof(int *));
    /*Test si l'allocation a marche*/
    if (Z->App == NULL)
    {
        printf("Erreur allocation du tableau App ");
    }
    /*Initialisation de chaque case du double tableau a −2 car la case n’appartient ni à Lzsg, ni à la bordure */
    for (i = 0; i < dim; i++)
    {
        Z->App[i] = (int *)malloc(dim * sizeof(int));
        /*Test si l'allocation a marche*/
        if (Z->App[i] == NULL)
        {
            printf("Erreur allocation du tableau App ");
        }
        for (j = 0; j < dim; j++)
        {
            Z->App[i][j] = -2;
        }
    }
    return Z;
}
// 0(dim²)

int ajoute_Zsg(S_Zsg *Z, int i, int j)
{
    return ajoute_en_tete(&(Z->Lzsg), i, j); // adresse pour pouvoir changer directement la valeur 
}

int ajoute_Bordure(S_Zsg *Z, int i, int j, int couleur)
{
    return ajoute_en_tete(&(Z->B[couleur]), i, j);
}

int appartient_Zsg(S_Zsg *Z, int i, int j)
{
    return Z->App[i][j] == -1;
}

int appartient_Bordure(S_Zsg *Z, int i, int j, int couleur)
{
    return Z->App[i][j] == couleur;
}

int agrandit_Zsg(int **M, S_Zsg *Z, int couleur, int i, int j)
{
    int cpt = 0;
    int x, y;
    ListeCase *l = (ListeCase *)malloc(sizeof(ListeCase));
    init_liste(l);
    /* implementation de la case dans la liste dans la bonne couleur de la bordure */
    if (M[i][j] == couleur)
    {
        ajoute_en_tete(l, i, j);
    }

    while (*l)
    {
        // Effet de pile
        enleve_en_tete(l, &x, &y);
        ajoute_Zsg(Z, x, y);

        if (M[x][y] == couleur)
        {
            M[x][y] = -1;
            cpt++;
        }

        // Testes les cases adjacentes
        agrandi_zone(M, Z, x + 1, y, Z->dim, couleur, l, &cpt);
        agrandi_zone(M, Z, x, y + 1, Z->dim, couleur, l, &cpt);
        agrandi_zone(M, Z, x - 1, y, Z->dim, couleur, l, &cpt);
        agrandi_zone(M, Z, x, y - 1, Z->dim, couleur, l, &cpt);
    }
    free(l);
    return cpt;
}
// 0(dim²) : pire cas , la couleur avec le plus de cases , eventuellment toute la grille 

void agrandi_zone(int **M, S_Zsg *Z, int i, int j, int dim, int couleur, ListeCase *L, int *cpt)
{
    // Test coordonne valide
    if (i >= 0 && j >= 0 && i <= (dim - 1) && j <= (dim - 1))
    {
        if (M[i][j] == -1)
        {
            return;
        }
        if (M[i][j] == couleur && appartient_Zsg(Z, i, j) != 1)
        {
            ajoute_en_tete(L, i, j);
            Z->App[i][j] = -1;
        }
        if (M[i][j] != couleur && appartient_Bordure(Z, i, j, couleur) != 1)
        {
            ajoute_Bordure(Z, i, j, M[i][j]);
            Z->App[i][j] = M[i][j];
        }
    }
}
//0(1)
int sequence_aleatoire_rapide(int **M, Grille *G, int dim, int nbcl, int aff)
{
    S_Zsg *Z = init_Zsg(dim, nbcl);
    int taille = 0;
    int cpt = 0;
    int couleur = M[0][0];
    ListeCase temp = NULL;
    taille = agrandit_Zsg(M, Z, M[0][0], 0, 0);
    M[0][0] = couleur;

    while (taille != dim * dim)
    {
        couleur=valide_couleur(couleur,nbcl,M);

        temp = Z->B[couleur];
        while (temp)
        {
            taille += agrandit_Zsg(M, Z, couleur, temp->i, temp->j);
            temp = temp->suiv;
        }

        temp = Z->Lzsg;
        while (temp)
        {
            M[temp->i][temp->j] = couleur;
            temp = temp->suiv;
        }

        detruit_liste(&(Z->B[couleur]));
        cpt++;
    
    /* Affichage de la grille */
    afficheGraphe2(M,G,dim,aff);
    }
    free_Zsg(Z);
    return cpt;
}
//0(dim²)
void free_Zsg(S_Zsg *Z)
{
    if (Z->Lzsg)
    {
        detruit_liste(&(Z->Lzsg));
    }
    int i;
    for (i = 0; i < Z->nbcl; i++)
    {
        if (Z->B[i])
        {
            detruit_liste(&(Z->B[i]));
        }
    }
    free(Z->B);
    for (i = 0; i < Z->dim; i++)
    {
        if (Z->App[i])
        {
            free(Z->App[i]);
        }
    }
    if (Z->App)
    {
        free(Z->App);
    }
    free(Z);
}
/* Exercice 3 Question 5*/
/*
Après avoir fait une multitude de tests (tous les tests ont été effectué avec un niveau de 7 et une graine de 3). 
Tout d’abord, nous avons gardé le même nombre de couleurs à 5 et augmenter progressivement le nombre de cases (dimension : 10 250 323 400 3500). 
De cela, nous avons déduit que le nombre d’essais ne varie pas fortement contrairement au temps d’exécution. 
De plus, la récursivité est ici limitée à une certaine dimension comprise entre 323 et 400. 
Ensuite, nous avons gardé la même dimension, ici à 100, et nous avons augmenté le nombre de couleurs progressivement (5 15 25 50 100). 
Nous avons pu remarquer qu'au premier lieu le nombre d'essais modifie fortement contrairement au temps d’exécution, qui varie peu. 
Aussi si nous augmentons fortement le nombre de couleurs, la limite de la récursivité diminue. 
D’après ces analyses on a montré que la couleur a un impact direct sur le nombre d’essais et la dimension un impact direct sur le temps d’exécution. 
Pour finir, peu importe le nombre de cases ou de couleur, la fonction de l’exercice 3 est la plus performante, ensuite, 
en matière de temps d’exécution s’ensuit la fonction récursive sauf qu’elle est limitée, et enfin la fonction de l’exercice bonus, 
c’est la plus lente mais elle va plus loin que la récursive.
*/