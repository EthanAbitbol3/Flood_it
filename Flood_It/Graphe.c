#include "Graphe.h"


void ajoute_liste_sommet(Cellule_som **cs, Sommet *s)
{
  /*On parcourt la liste chainee de pointeur sur sommet*/
    Cellule_som *temp = (Cellule_som *)malloc(sizeof(Cellule_som));
    temp->sommet = s;
    temp->suiv = *cs; // on ajoute en tete
    *cs = temp;
}
//0(1)

void ajoute_voisin(Sommet *s1, Sommet *s2)
{
    ajoute_liste_sommet(&(s1->sommet_adj), s2);// adjacent pour s1
    ajoute_liste_sommet(&(s2->sommet_adj), s1);// adjacent pour s2
}

int test_adjacent(Sommet *s1, Sommet *s2)
{
    Cellule_som *temp = s1->sommet_adj;
    while (temp)
    {
        if (temp->sommet == s2)// on fais le test que pour un sommet, pas besoin pour les deux 
        {
            return 1;
        }
        temp = temp->suiv;
    }
    return 0;
}
//0(s1->sommet_adj) degre de s1, nb de voisin de s1
Graphe_zone *init_graphe_zone(int dim)
{
    int i, j;
    /*allocation de la memoire pour la structure graphe_zone*/
    Graphe_zone *G = (Graphe_zone *)malloc(sizeof(Graphe_zone)); 
    /*nbsom*/
    G->nbsom = 0;

    /*som*/
    G->som = NULL;

    /*mat*/
    G->mat = (Sommet ***)malloc(dim * sizeof(Sommet **));
    /*Test si l'allocation a marche*/
    if (G->mat == NULL)
    {
        printf("Erreur allocation du tableau Mat ");
    }
    for (i = 0; i < dim; i++)
    {
        G->mat[i] = (Sommet **)malloc(dim * sizeof(Sommet *));
        /*Test si l'allocation a marche*/
        if (G->mat[i] == NULL)
        {
            printf("Erreur allocation du tableau App ");
        }
        for (j = 0; j < dim; j++)
        {
            G->mat[i][j] = NULL;
        }
    }
    return G;
}
//0(dim²)

Sommet *init_sommet(int num, int cl)
{
    Sommet *s = (Sommet *)malloc(sizeof(Sommet));
    s->num = num;
    s->cl = cl;
    s->marque = 2;
    s->cases = NULL;
    s->nbcase_som = 0;
    s->sommet_adj = NULL;
    s->distance= -1;
    s->pere=NULL;
    return s;
}

void mj_matrice(ListeCase *L, int **M, Sommet ***mat, int couleur, Sommet *s)
{
    ListeCase temp = *L; // pour pas perdre la tete 
    while (temp)
    {
        mat[temp->i][temp->j] = s;// on va faire pointe vers le sommet 
        temp = temp->suiv;
    }
}

Graphe_zone *cree_graphe_zone(int **M, int dim, int nbcl)
{
 
    Graphe_zone *G = init_graphe_zone(dim);//init le graphe
    int i, j, couleur = M[0][0];
    ListeCase temp;
    Sommet *s, *s1, *s2;
    /*On cree les sommets sans les aretes*/
    for (i = 0; i < dim; i++)
    {
        for (j = 0; j < dim; j++)
        {
            if (G->mat[i][j] == NULL)// pour toute cases null
            {
               
                couleur = M[i][j];
                s = init_sommet(G->nbsom, couleur);
                trouve_zone_imp(M, dim, i, j, &(s->nbcase_som), &(s->cases), couleur);// on cherche la zone de cette case
                mj_matrice(&(s->cases), M, G->mat, couleur, s); // on pointe tous les sommets vers un sommet zone 
                //G->mat[i][j] = s; erreur , sert a rien 
                ajoute_liste_sommet(&(G->som), s);
                (G->nbsom)++;
            }
        }
    }
     /*on cree les aretes */
    for (i = 0; i < dim ; i++)
    {
        for (j = 0; j < dim ; j++)
        {
            s = G->mat[i][j]; // pour eviter davoir acces a cette case plusieurs fois car on va faire plusierus test 
            if (i < dim - 1)
            {
                s1 = G->mat[i + 1][j]; // case du dessous
                if (s!=s1 /*2 sommet different*/ && test_adjacent(s, s1) == 0)// si non adjacent 
                {
                    ajoute_voisin(s, s1);//on ajoute l'arete 
                }
            }

            if (j < dim - 1 )
            {
                s2 = G->mat[i][j + 1];
                if (s!=s2 && test_adjacent(s, s2) == 0)// si non adjacent 
                {
                    ajoute_voisin(s, s2);//on ajoute l'arete 
                }
            }
        }
    }
    
    return G;
}
// 0(dim²)

// Detruit tous les pointeurs sur sommets
void detruit_liste_somme(Cellule_som *cs)
{
    Cellule_som *cour, *temp;
    cour = cs;
    while (cour != NULL)
    {
        temp = cour;
        cour = cour->suiv;
        free(temp);
    }
    cs = NULL;
}
//0(n(taille de cs))

void desalloue_sommet(Sommet *s)
{
    detruit_liste(&(s->cases));//detruit la liste cases
    detruit_liste_somme(s->sommet_adj);// detruit la liste des aretes pointants sur les sommets 
    free(s);
}
// detruit la matrice de pointeur sur sommet

void dessalloue_matrice(Graphe_zone *g,int dim){
    int i;
    for (i = 0; i < dim; i++)
    {
        if (g->mat[i])
            free(g->mat[i]);
    }
    if (g->mat)
        free(g->mat);
}
// 0(dim)

void desalloue_graphe(Graphe_zone *g, int dim)
{
    Cellule_som *temp = g->som, *cell;
    //detruit la liste des sommets
    while (temp)
    {
        cell=temp;
        desalloue_sommet(temp->sommet);
        temp = temp->suiv;
        free(cell);
    }
    dessalloue_matrice(g,dim);
    free(g);
}

void affiche_cellule_som(Cellule_som *cs)
{
    /*on affiche le num, la couleur et le nb de cases de sommets dans chaque cellule_som*/
    Cellule_som *s, *s2;
    s = cs;
    while (s)
    {
        printf(" numero %d | couleur %d | nbcase %d \n", s->sommet->num, s->sommet->cl, s->sommet->nbcase_som);
        s = s->suiv;
    }
}

void affiche_graphe(Graphe_zone *g, int dim)
{
    int i, j;
    printf("Nombre de sommet dans le graphe : %d \n", g->nbsom);
    Cellule_som *temp = g->som;
     /*som: Liste chaine des sommets sur graphe*/
    while (temp)
    {
        printf("Numero : %d | %d couleur | %d nb case liste | \n", temp->sommet->num,temp->sommet->cl,temp->sommet->nbcase_som);
        affiche_liste(temp->sommet->cases);
        affiche_cellule_som(temp->sommet->sommet_adj);
        temp = temp->suiv;
        printf("\n");
    }
     /*mat: Matrice de pointeurs sur les sommets indiquant a quel sommet appartient une case (i,j) de la grille*/
    Sommet *s;
    printf("\n");
    printf("Affiche matrice pointeur sommet \n");
    for (i = 0; i < dim; i++)
    {
        for (j = 0; j < dim; j++)
        {
            s = g->mat[i][j];
            printf("%d,%d \t",s->cl,s->num);
        }
        printf("\n");
    }
    printf("\n");
}
void afficheGraphe(Graphe_zone *g,Grille *G,int dim,int couleur,int aff){
 if (aff == 1)
    {
        int i, j;
        for (i = 0; i < dim; i++)
            for (j = 0; j < dim; j++)
            {
                if(g->mat[i][j]->marque !=0){//si il est pas dans la zsg
                     Grille_attribue_couleur_case(G, i, j, g->mat[i][j]->cl);
                }else{//il est de la couleur courante 
                     Grille_attribue_couleur_case(G, i, j,couleur);
                }
               
            }

        Grille_redessine_Grille(G);
        SDL_Delay(100);
    }
}
