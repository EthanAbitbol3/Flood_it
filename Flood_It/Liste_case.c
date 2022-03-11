#include<stdlib.h>
#include "Liste_case.h"

 /* Initialise une liste vide */

void init_liste(ListeCase *L){
  *(L)=NULL;
}

/* Ajoute un element en tete de liste */
int ajoute_en_tete(ListeCase *L, int i, int j){
  Elnt_liste *elnt;
  elnt=(Elnt_liste*) malloc(sizeof(Elnt_liste));
  if (elnt==NULL) 
    return 0;
  elnt->suiv=*L;
  elnt->i=i;
  elnt->j=j;
  (*L)=elnt;
}

void affiche_matrice(int **M, int dim)
{
    printf("\n");
    int i, j;
    for (i = 0; i < dim; i++)
    {
        for (j = 0; j < dim; j++)
        {
            printf("%d \t", M[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void affiche_liste(ListeCase L)
{
    ListeCase temp = L;
    while (temp)
    {
        printf("Case (%d,%d) \t ", temp->i, temp->j);
        temp = temp->suiv;
    }
    printf("\n");
}

/* teste si une liste est vide */
int test_liste_vide(ListeCase *L){
  return (*L)==NULL;
}

/* Supprime l element de tete et retourne les valeurs en tete */
/* Attention: il faut que la liste soit non vide */
void enleve_en_tete(ListeCase *L, int *i, int *j){
  Elnt_liste *temp;
  *i=(*L)->i;
  *j=(*L)->j;
  temp=*L;
  *L=(*L)->suiv;
  free(temp);
}

/* Detruit tous les elements de la liste */
void detruit_liste(ListeCase *L){
 Elnt_liste *cour,*temp;
  cour=(*L);
  while (cour!=NULL){
    temp=cour;
    cour=cour->suiv;
    free(temp);
  }

  *L=NULL;
}
