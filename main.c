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
    int info = 2;
    Liste* maList = initialiser();
    printf("%zu\n", longueur(maList));
    printf("%d\n", estVide(maList));
    insererEnQueue(maList, &info);
    printf("%zu\n", longueur(maList));
    afficher(maList, FORWARD);

    return EXIT_SUCCESS;
}
