all: Flood-It

API_Gene_instance.o: API_Gene_instance.c API_Gene_instance.h
	gcc -c API_Gene_instance.c `sdl2-config --cflags`

API_Grille.o: API_Grille.c API_Grille.h
	gcc -c API_Grille.c `sdl2-config --cflags`

Liste_case.o: Liste_case.c Liste_case.h
	gcc -c Liste_case.c `sdl2-config --cflags`

StructureAcyclique.o: StructureAcyclique.c StructureAcyclique.h Entete_Fonctions.h
	gcc -c StructureAcyclique.c `sdl2-config --cflags`

Graphe.o : Graphe.c Graphe.h
	gcc -c Graphe.c `sdl2-config --cflags`

MaxBordure.o : MaxBordure.c MaxBordure.h
	gcc -c MaxBordure.c `sdl2-config --cflags`

Fonctions_exo1.o: Fonctions_exo1.c Entete_Fonctions.h Liste_case.h
	gcc -c Fonctions_exo1.c `sdl2-config --cflags`

FileParcours.o : FileParcours.c FileParcours.h
	gcc -c FileParcours.c `sdl2-config --cflags`

ParcoursLargeur.o : ParcoursLargeur.c ParcoursLargeur.h
	gcc -c ParcoursLargeur.c `sdl2-config --cflags`

Flood-It.o: Flood-It.c
	gcc -c Flood-It.c `sdl2-config --cflags`

Flood-It: Flood-It.o FileParcours.o ParcoursLargeur.o Liste_case.o MaxBordure.o Graphe.o API_Grille.o API_Gene_instance.o Fonctions_exo1.o StructureAcyclique.o
	gcc -o Flood-It Flood-It.o ParcoursLargeur.o FileParcours.o Liste_case.o MaxBordure.o Graphe.o API_Grille.o API_Gene_instance.o Fonctions_exo1.o StructureAcyclique.o `sdl2-config --libs`

clean:
	rm -f *.o Flood-It



