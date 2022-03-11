#include "ParcoursLargeur.h"

int *plus_court_chemin(Sommet *depart, Sommet *arrive, int *taille_chemin)
{
    Cellule_som *cs;
    Sommet *courant, *temp;
    File F;
    initFile(&F);

    depart->distance = 0; // le debut, la racine
    enfile(&F, depart);
    while (!(estFileVide(&F)))
    {
        //Sommet courant 
        courant = defile(&F); // on enleve le depart 
        //Sommet adjacent
        cs = courant->sommet_adj;
        while (cs != NULL)
        {
            temp = cs->sommet;// sommet de la liste d'adjacence du sommet courant 
            //On test si deja visiter
            if (temp->distance == -1) // distance init a -1
            {
                //Met a jour la distance 
                temp->distance = courant->distance + 1; // a chaque sommet courant distance+1
                //Fait le lien a
                temp->pere = courant; // le pere du sommet adja est le sommet courant 
                enfile(&F, cs->sommet); // adj des adj a l'aide d'une file 
            }
            cs = cs->suiv;
        }
    }

    (*taille_chemin) += arrive->distance; // la distance la plus rapide
    return tableauCouleur(depart, arrive, arrive->distance); // couleur inverse donc on remet en ordre 
}

int *tableauCouleur(Sommet *depart, Sommet *arrive, int taille)
{
    int *couleur = malloc(sizeof(int) * taille);
    int index = taille - 1;
    //Part de la feuille et remonte jusqua la racine et stocke dans le tableau dans le bon indice
    while (arrive != depart)
    {
        couleur[index] = arrive->cl;
        index--;
        arrive = arrive->pere;
    }
    return couleur;
}

int ResoudreParcoursLargeur(int **M, Grille *G, int dim, int nbcl, int aff)
{
    S_Zsg2 *Z = init_Zsg2(dim, nbcl);
    Graphe_zone *g = cree_graphe_zone(M, dim, nbcl);
    int cpt = 0, taille_chemin = 0, couleur, i;
    Sommet *depart = g->mat[0][0];

    //initialise la zsg
    ajoute_Zsg2(Z, depart);
    //initialise la bordure
    mj_bordure(Z, depart);


    int *tab = plus_court_chemin(depart, g->mat[dim - 1][dim - 1], &taille_chemin);
    //Realise le plus court chemin afin d avoir deux zones pour resoudre plus rapidement apres avec max bordure
    for (i = 0; i < taille_chemin; i++)
    {
        couleur = tab[i];
        agrandit_Zsg2(Z, couleur);
        cpt++;
        afficheGraphe(g, G, dim, couleur, aff); 
    }
    
    //strategie de max bordure
    while (fin_jeu(Z->B, nbcl) == 1)
    {

        couleur = max_index(Z->taille, nbcl);
        agrandit_Zsg2(Z, couleur);
        cpt++;

        afficheGraphe(g, G, dim, couleur, aff);
        
    }

    //desalocation des structures
    free(tab);
    free_Zsg2(Z);
    desalloue_graphe(g, dim);
    return cpt;
}
