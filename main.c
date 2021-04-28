/*
 -----------------------------------------------------------------------------------
 Nom du fichier : main.c
 Auteur(s)      : Guilan Mbayo, Mehdi Sahli, Maxime Chantemargue
 Date creation  : 22.04.2021

 Description    : Programme principal ayant pour objectif de tester toutes les
                  fonctions implémentées dans le fichier listes_dynamiques.c.

 Remarque(s)    : Dans les deux fonctions renvoyant chacune un bool(isPair ainsi qu'isImpair),
                  le premier paramètre position n'est volontairement pas utilisé
                  car il n'est pas nécessaire dans l'exécution de cette fonction.
                  Nous le laissons car il était explicitement demandé de l'implémenter.

 Compilateur    : Mingw-w64 gcc 8.1.0
 -----------------------------------------------------------------------------------
*/
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "listes_dynamiques.h"

/* MEMTEST sert à simuler une mauvaise allocation et un retour de
   pointeur a NULL pour la fonction insererEnQueue
   (il faut aussi l'activer dans listes_dynamiques.c)
 */
#define MEMTEST

/***
 * Teste si l'élément à une position x est pair.
 * @param position position de l'élément dans la chaîne.
 * @param info pointeur sur int.
 * @return true si pair et false si impair.
 */
bool isPair(size_t position, const Info *info) {
   return !(*info % 2);
}

/***
 * Teste si l'élément à une position x est impair.
 * @param position position de l'élément dans la chaîne.
 * @param info pointeur sur int.
 * @return true si info est impair et false si pair.
 */
bool isImpair(size_t position, const Info *info) {
   return (*info % 2);
}

int main(void) {
   int info = 1;
   int info2 = 2;
   int info3 = 3;
   int info4 = 4;
   int info5 = 5;
   int info6 = 6;
   Liste *maList = initialiser();

   // -------------------------------------------------------------------------
   // Test affichage liste vide
   printf("Teste liste\n");
   printf("Affichage liste apres init\n");
   afficher(maList, FORWARD);

   // -------------------------------------------------------------------------
   // Test suppression d'éléments dans une liste vide
   int valSuppr = 0;
   printf(" \nTest suppression element en queue dans une liste vide\n");
   if (supprimerEnQueue(maList, &valSuppr) == LISTE_VIDE) {
      printf("Renvoi \"LISTE_VIDE\" OK ! \n");
   } else {
      printf("Renvoi \"LISTE_VIDE\" PAS OK ! \n");
   }

   printf(" \nTest suppression element en tete dans une liste vide\n");
   if (supprimerEnTete(maList, &valSuppr) == LISTE_VIDE) {
      printf("Renvoi \"LISTE_VIDE\" OK ! \n");
   } else {
      printf("Renvoi \"LISTE_VIDE\" PAS OK ! \n");
   }

   // -------------------------------------------------------------------------
   // Test d'insertion d'éléments dans une liste
   printf("\nAffichage apres ajout 4 en tete et test si retour OK\n");

   if (insererEnTete(maList, &info4) == OK) {
      printf("Retour OK\n");
   }

   afficher(maList, FORWARD);

   printf("\nAffichage apres suppression de %d en queue\n", info4);
   if (supprimerEnQueue(maList, &valSuppr) == OK) {
      printf("Retour OK\n");
   }

   afficher(maList, FORWARD);

#ifdef MEMTEST
   if(insererEnQueue(maList, &info4) == MEMOIRE_INSUFFISANTE) {
      printf("\n## TEST MEMOIRE INSUFFISANTE : OK ##\n");
   }
#endif

   printf("\nAffichage apres ajout %d en queue\n", info4);
   insererEnQueue(maList, &info4);
   afficher(maList, FORWARD);

   printf("\nAffichage apres supression de l'élément en tete\n");
   supprimerEnTete(maList, &valSuppr);
   afficher(maList, FORWARD);

   insererEnTete(maList, &info4);
   printf("\nAffichage apres ajout %d en tete\n", info4);
   afficher(maList, FORWARD);

   printf("\nAffichage apres ajout de %d en tete\n", info3);
   insererEnTete(maList, &info3);
   afficher(maList, FORWARD);

   printf("\nAffichage apres ajout de %d en queue\n", info5);
   insererEnQueue(maList, &info5);
   afficher(maList, FORWARD);

   printf("\nInsertion en queue de %d \n", info6);
   insererEnQueue(maList, &info6);
   afficher(maList, FORWARD);

   printf("\nInsertion en tete de %d \n", info2);
   insererEnTete(maList, &info2);
   afficher(maList, FORWARD);

   printf("\nInsertion en tete de %d\n", info);
   insererEnTete(maList, &info);
   afficher(maList, FORWARD);

   printf("\n");
   printf("\n");

   // -------------------------------------------------------------------------
   // test d'egalité
   printf("Test si deux listes sont egales\n");

   Liste *maList2 = initialiser();
   insererEnQueue(maList2, &info2);
   insererEnQueue(maList2, &info3);
   insererEnQueue(maList2, &info4);
   insererEnQueue(maList2, &info5);
   insererEnQueue(maList2, &info6);
   printf("Liste 1 et 2\n");
   afficher(maList, FORWARD);
   printf("\n");
   afficher(maList2, FORWARD);

   printf("\nSont egales: %d\n", sontEgales(maList, maList2));
   printf("Retest d'egalite apres insertion d'un element dans liste2:");
   insererEnQueue(maList2, &info);
   printf("\nSont egales: %d\n", sontEgales(maList, maList2));
   printf("Retest d'egalite apres suppression du nouvel element dans liste2:");
   supprimerEnQueue(maList2, &info);
   printf("\nSont egales: %d\n", sontEgales(maList, maList2));


   // -------------------------------------------------------------------------
   // Test de suppression selon critère

   printf("\nTest de suppression selon critere:\n");
   printf("Liste originale: \n");
   afficher(maList, FORWARD);
   supprimerSelonCritere(maList, &isPair);
   printf("\nApres suppression des elements paires:\n");
   afficher(maList, FORWARD);
   printf("\nDans l'autre sens: \n");
   afficher(maList, BACKWARD);

   supprimerSelonCritere(maList, &isImpair);
   printf("\nApres suppression des elements impaires:\n");
   afficher(maList, FORWARD);

   //----
   // Test de vider une liste
   printf("\nTest vider liste a partir de 3:\n");
   insererEnQueue(maList2, &info);
   insererEnQueue(maList2, &info2);
   insererEnQueue(maList2, &info3);
   insererEnQueue(maList2, &info4);
   insererEnQueue(maList2, &info5);
   insererEnQueue(maList2, &info6);
   vider(maList2, 3);
   afficher(maList2, FORWARD);
   afficher(maList2, BACKWARD);
   printf("\nTest vider liste a partir de 10 (pos >= taille):\n");
   vider(maList2, 10);
   afficher(maList2, FORWARD);
   afficher(maList2, BACKWARD);
   printf("\nTest vidage liste a partir de 3(taille =4):\n");
   vider(maList2, 3);
   afficher(maList2, FORWARD);
   afficher(maList2, BACKWARD);
   printf("\nTest vidage total:\n");
   vider(maList2, 0);
   afficher(maList2, FORWARD);
   afficher(maList2, BACKWARD);
   printf("\nTest vidage total sur liste vide:\n");
   vider(maList2, 0);
   afficher(maList2, FORWARD);
   afficher(maList2, BACKWARD);

   free(maList);
   free(maList2);

   return EXIT_SUCCESS;
}


