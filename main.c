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

bool isImpair(size_t position, const Info *info){
    if(*info % 2){
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

    // -------------------------------------------------------------------------
    // Test affichage liste vide
    printf("Teste liste\n");
    printf("Affichage liste apres init\n");
    afficher(maList,FORWARD);

    // -------------------------------------------------------------------------
    // Test suppression d'éléments dans une liste vide
    int valSuppr;
    printf(" \nTest suppression element en queue dans une liste vide\n");
    if(supprimerEnQueue(maList, &valSuppr) == LISTE_VIDE){
        printf("Renvoi \"LISTE_VIDE\" OK ! \n");
    }
    else{
        printf("Renvoi \"LISTE_VIDE\" PAS OK ! \n");
    }

    printf(" \nTest suppression element en tete dans une liste vide\n");
    if(supprimerEnTete(maList, &valSuppr) == LISTE_VIDE){
        printf("Renvoi \"LISTE_VIDE\" OK ! \n");
    }
    else{
        printf("Renvoi \"LISTE_VIDE\" PAS OK ! \n");
    }

    // -------------------------------------------------------------------------
    // Test d'insertion d'éléments dans une liste
    insererEnTete(maList, &info4);
    printf("\nAffichage apres ajout 4 en tete\n");
    afficher(maList,FORWARD);

    printf("\nAffichage apres supression 4 en queue\n");
    supprimerEnQueue(maList, &valSuppr);
    afficher(maList,FORWARD);

    insererEnQueue(maList, &info4);
    printf("\nAffichage apres ajout 4 en queue\n");
    afficher(maList,FORWARD);

    printf("\nAffichage apres supression 4 en tete\n");
    supprimerEnTete(maList, &valSuppr);
    afficher(maList,FORWARD);

    insererEnTete(maList, &info4);
    printf("\nAffichage apres ajout 4 en tete\n");
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

    // -------------------------------------------------------------------------
    // test d'egalité
    printf("Test si deux listes sont egales\n");

    Liste* maList2 = initialiser();
    insererEnQueue(maList2, &info);
    insererEnQueue(maList2, &info2);
    insererEnQueue(maList2, &info3);
    insererEnQueue(maList2, &info4);
    insererEnQueue(maList2, &info5);
    insererEnQueue(maList2, &info6);

    printf("Liste 1 et 2\n");
    afficher(maList,FORWARD);
    printf("\n");
    afficher(maList2,FORWARD);

    printf("\nSont egales: %d\n", sontEgales(maList, maList2));
    printf("Retest d'egalite apres insertion d'un elmt dans liste2:");
    insererEnQueue(maList2, &info);
    printf("\nSont egales: %d\n", sontEgales(maList, maList2));
    printf("Retest d'egalite apres suppression du nouvel elmt dans liste2:");
    supprimerEnQueue(maList2, &info);
    printf("\nSont egales: %d\n", sontEgales(maList, maList2));


    // -------------------------------------------------------------------------
    // Test de suppression selon critère

    printf("\nTest de supression selon critere:\n");
    printf("Liste originale: \n");
    afficher(maList,FORWARD);
    supprimerSelonCritere(maList, &isPair);
    printf("\nApres suppression des elements paires:\n");
    afficher(maList,FORWARD);
    printf("\nDans l'autre sens: \n");
    afficher(maList,BACKWARD);

    supprimerSelonCritere(maList, &isImpair);
    printf("\nApres suppression des elements impaires:\n");
    afficher(maList,FORWARD);
    return EXIT_SUCCESS;
}


