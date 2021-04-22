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

    insererEnQueue(maList,&info);
    insererEnQueue(maList,&info2);
    insererEnQueue(maList,&info3);
    insererEnQueue(maList,&info4);
    insererEnQueue(maList,&info5);
    insererEnQueue(maList,&info6);

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
    return EXIT_SUCCESS;
}


