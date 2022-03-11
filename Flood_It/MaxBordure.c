#include "MaxBordure.h"

S_Zsg2 *init_Zsg2(int dim, int nbcl)
{
    /*allocation de la memoire pour la structure S_Zsg2*/
    S_Zsg2 *Z = (S_Zsg2 *)malloc(sizeof(S_Zsg2));
    /*Test si l'allocation a marche*/
    if (Z == NULL)
    {
        printf("Erreur allocation de Zsg");
    }
    /*nbcl*/
    Z->nbcl = nbcl;

    /*dim*/
    Z->dim = dim;

    /*taille: tableau*/
    Z->taille = (int *)malloc(nbcl * sizeof(int));
    int i;
    for (i = 0; i < nbcl; i++)
    {
        Z->taille[i] = 0;
    }

    /*L : liste chaine*/
    Z->L = NULL;
    /*allocation de la memoire pour le tableau de liste correspondant a la bordure*/
    /*B*/
    Z->B = (Cellule_som **)malloc(nbcl * sizeof(Cellule_som *));
    /*Test si l'allocation a marche*/
    if (Z->B == NULL)
    {
        printf("Erreur allocation de ListeCase (Z->B) ");
    }
    for (i = 0; i < nbcl; i++)
    {
        Z->B[i] = NULL;
    }
    return Z;
}


void ajoute_Bordure2(S_Zsg2 *Z, Sommet *s)
{
    ajoute_liste_sommet(&(Z->B[s->cl]), s); // ajoute le sommet a la cellule_som
    Z->taille[s->cl] += s->nbcase_som;      // augmente le nombre de case de chaque couleur
    s->marque = 1;                          // marque pass a 1 : present dans la bordure
}

void ajoute_Zsg2(S_Zsg2 *Z, Sommet *s)
{
    ajoute_liste_sommet(&(Z->L), s); //ajoute le sommet a la zsg
    s->marque = 0;                   // marque a 0 : present dans la zsg
}

int appartient_Zsg2(Sommet *s)
{
    return (s->marque) == 0;
}

int appartient_Bordure2(Sommet *s)
{
    return (s->marque) == 1;
}

void mj_bordure(S_Zsg2 *Z, Sommet *s)
{ // quand on va changer de couleur de la zsg on va faire la maj de la bordure avec cette nv couleur 
    Cellule_som *temp3 = s->sommet_adj; // correpond aux sommets adjacents
    while (temp3)
    {
        if (temp3->sommet->marque == 2) //sommet non visite
        {
            ajoute_Bordure2(Z, temp3->sommet); // on l'ajoute a la bordure
        }
        temp3 = temp3->suiv;
    }
}


void agrandit_Zsg2(S_Zsg2 *Z, int couleur)
{
    Cellule_som *temp = Z->B[couleur]; // on va parcourir le cellule_som correpondant a cette couleur
    while (temp)
    {
        ajoute_Zsg2(Z, temp->sommet); // on l'ajoute a la zsg
        mj_bordure(Z, temp->sommet);  // on met a jour la bordure , la bordure de la bordure
        temp = temp->suiv;
    }
    detruit_liste_somme(Z->B[couleur]); // on detruit la cellule_som parcouru
    Z->B[couleur] = NULL;
    Z->taille[couleur] = 0; // on remet a 0 sa taille
}

int max_index(int *taille, int nbcl)
{
    int i, max = 0, indice = 0;
    for (i = 0; i < nbcl; i++)
    {
        if (taille[i] > max) // on cherche le maximum
        {
            max = taille[i]; //le max prend la valeur renvoye par la case du tableau taille[i]
            indice = i;
        }
    }
    return indice;
}

int fin_jeu(Cellule_som **B, int nbcl)
{
    int i;
    for (i = 0; i < nbcl; i++)
    {
        if (B[i] != NULL) // tant que il ya une case dans le tableau qui est different de null, on continue
        {
            return 1;
        }
    }
    /*quand la bordure ne contient plus aucune case alors le jeu est terminé*/
    return 0;
}

int maxBordure(int **M, Grille *G, int dim, int nbcl, int aff)
{
    S_Zsg2 *Z = init_Zsg2(dim, nbcl); //init la structure
    Graphe_zone *g = cree_graphe_zone(M, dim, nbcl);// on cree le graphe zone correspondant
    int cpt = 0;
    int couleur;

    ajoute_Zsg2(Z, g->mat[0][0]);// on commence avec le sommet correspondant a mat[0][0]
    mj_bordure(Z, g->mat[0][0]);  // on met a jour la bordure avec cette zsg
    while (fin_jeu(Z->B, nbcl) == 1)//tant qu'il ya une case dans la bordure , on continue
    {
        couleur = max_index(Z->taille, nbcl); // on prend la couleur ou il ya le plus de sommet adjacent a la bordure
        agrandit_Zsg2(Z, couleur); // on met a jour la zsg avec cette couleur
        cpt++;

        /* Affichage de la grille */
        afficheGraphe(g, G, dim, couleur, aff);
    }

    free_Zsg2(Z);
    desalloue_graphe(g, dim);
    return cpt;
}


void free_Zsg2(S_Zsg2 *Z)
{
    free(Z->taille);
    detruit_liste_somme(Z->L);
    int i;
    for (i = 0; i < Z->nbcl; i++)
    {
        if (Z->B[i])
        {
            detruit_liste_somme(Z->B[i]);
        }
    }
    free(Z->B);
    free(Z);
}

void affiche_bordure(Cellule_som **cs, int nbcl)
{
    int i;
    Cellule_som *s, *s2;
    for (i = 0; i < nbcl; i++)
    {
        printf("couleur : %d\n", i);
          /*on affiche chaque liste chaine de cellule_som presente dans chaque case du tableau*/
        if (cs[i])
        {
            affiche_cellule_som(cs[i]);
        }
    }
}
