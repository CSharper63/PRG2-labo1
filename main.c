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

int main(void) {
    int info = 1;
    int info2 = 2;
    int info3 = 3;
    int info4 = 4;
    int info5 = 5;
    int info6 = 6;
    Liste* maList = initialiser();


    insererEnQueue(maList,&info);
    insererEnQueue(maList,&info2);
    insererEnQueue(maList,&info3);
    insererEnQueue(maList,&info4);
    insererEnQueue(maList,&info5);
    insererEnQueue(maList,&info6);
    afficher(maList,FORWARD);
    printf("\n");
    vider(maList,3);
    afficher(maList,FORWARD);
    return EXIT_SUCCESS;
}
