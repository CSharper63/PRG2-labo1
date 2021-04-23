/*
 -----------------------------------------------------------------------------------
 Nom du fichier : main.c
 Auteur(s)      : Guilan Mbayo, Mehdi Sahli, Maxime Chantemargue
 Date creation  : 03.04.2021

 Description    : Programme principal

 Remarque(s)    : -

 Compilateur    : Mingw-w64 gcc 8.1.0
 -----------------------------------------------------------------------------------
*/
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "listes_dynamiques.h"

bool isPair(size_t position, const Info *info){
    if(*info % 2 == 0){
        return true;
    }
    return false;
}

int main(void) {
    int info = 1;
    int info2 = 2;
    int info3 = 3;
    int info4 = 4;
    int info5 = 5;
    int info6 = 6;
    Liste* maList = initialiser();
    Liste* maList1 = initialiser();

    printf("Teste liste\n");
    printf("Affichage liste apres init\n");
    afficher(maList,FORWARD);

    insererEnTete(maList, &info4);
    printf("\nAffichage apres ajout 4\n");
    afficher(maList,FORWARD);

    printf("\nAffichage apres ajout 3 en tete\n");
    insererEnTete(maList, &info3);
    afficher(maList,FORWARD);

    printf("\nAffichage apres ajout 5 en queue\n");
    insererEnQueue(maList, &info5);
    afficher(maList,FORWARD);

    printf("\nInsertion en queue de 6 \n");
    insererEnQueue(maList,&info6);
    afficher(maList,FORWARD);

    printf("\nInsertion en tete de 2 \n");
    insererEnTete(maList,&info2);
    afficher(maList,FORWARD);

    printf("\nInsertion en tete de 1\n");
    insererEnTete(maList,&info);
    afficher(maList,FORWARD);

    printf("\n");
    printf("\n");

    insererEnQueue(maList,&info);
    afficher(maList,FORWARD);



    printf("\nInsertion en tete de 2 puis 1\n");
    insererEnTete(maList, &info2);
    insererEnTete(maList, &info);
    afficher(maList,FORWARD);

    insererEnQueue(maList1,&info);
    insererEnQueue(maList1,&info2);
    insererEnQueue(maList1,&info3);
    insererEnQueue(maList1,&info4);
    insererEnQueue(maList1,&info5);



    afficher(maList1,FORWARD);
    printf("\n");

    afficher(maList,FORWARD);

    printf("\n%d", sontEgales(maList1, maList));

    supprimerSelonCritere(maList, &isPair);

    afficher(maList,FORWARD);
    afficher(maList,BACKWARD);
    return EXIT_SUCCESS;
}


