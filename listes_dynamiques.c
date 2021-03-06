/*
 -----------------------------------------------------------------------------------
 Nom du fichier : listes_dynamiques.h
 Auteur(s)      : Guilan Mbayo, Mehdi Sahli, Maxime Chantemargue
 Date creation  : 22.04.2021

 Description    : Librairie permettant la gestion de listes doublement chaînées
                  non circulaires.

 Remarque(s)    : -

 Compilateur    : Mingw-w64 gcc 8.1.0
 -----------------------------------------------------------------------------------
*/

#include "listes_dynamiques.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

/* MEMTEST sert à simuler une mauvaise allocation
   et un retour de pointeur a NULL pour la fonction insererEnQueue.
   (Il faut aussi définir MEMETEST dans main.c)
*/
//#define MEMTEST

/**
 * Initialise une liste avec les pointeurs tete et queue à NULL.
 * @return la liste initialisée.
 */
Liste *initialiser() {
    // il faut caster explicitement le void*
   Liste *liste = (Liste*) malloc(sizeof(Liste));
   // pas la manière standard d'avertir l'utilisateur. Il faut plutôt retourner NULL. assert(liste != NULL);
   if(liste != NULL) {
       liste->tete = NULL;
       liste->queue = NULL;
   }
   return liste;
}

/**
 * Renvoie true si liste est vide, false sinon.
 * @param liste pointeur sur la liste.
 * @return true si la liste est vide et false sinon.
 */
bool estVide(const Liste *liste) {
   return !liste->tete;
}

/**
 * Renvoie combien il y a d'éléments dans liste.
 * @param liste pointeur sur la liste.
 * @return un compteur indiquant le nombre d'élément dans la liste.
 */
size_t longueur(const Liste *liste) {
   size_t cnt = 0;
   for (Element *currentPtr = liste->tete; currentPtr != NULL; currentPtr = currentPtr->suivant) {
      ++cnt;
   }
   return cnt;
}

/**
 * Affiche le contenu de la liste.
 * @param liste pointeur sur la liste.
 * @param mode mode d'affichage de la liste (forward/backward).
 */
void afficher(const Liste *liste, Mode mode) {
   printf("[");
 // INUTILE : if (!estVide(liste)) {
      switch (mode) {
         case FORWARD:
            for (Element *currentPtr = liste->tete; currentPtr != NULL; currentPtr = currentPtr->suivant) {
               printf("%d", currentPtr->info);
               if (currentPtr->suivant)
                  printf(",");
            }
            break;
         case BACKWARD:
            for (Element *currentPtr = liste->queue; currentPtr != NULL; currentPtr = currentPtr->precedent) {
               printf("%d", currentPtr->info);
               if (currentPtr->precedent)
                  printf(",");
            }
            break;
      }
 //  }
   printf("]");
}

/**
 * Insère un élément en tête de liste.
 * @param liste pointeur sur la liste.
 * @param info pointeur sur une variable contenant l'information à insérer.
 * @return Renvoie OK si l'insertion s'est déroulée avec succès et MEMOIRE_INSUFFISANTE
 * s'il n'y a pas assez de mémoire pour créer le nouvel élément.
 */
Status insererEnTete(Liste *liste, const Info *info) {
   assert(info != NULL);

   Element *nouveau = (Element *) malloc(sizeof(Element));
   if (nouveau == NULL) {
      return MEMOIRE_INSUFFISANTE;
   } // else { // else est inutile et indente inutilement le code.
      nouveau->info = *info;
      // ces deux lignes ne doivent pas être dupliquées dans if...else...
      nouveau->suivant = liste->tete;
      nouveau->precedent = NULL;
      if (!estVide(liste)) {
         liste->tete->precedent = nouveau;
      } else {
         liste->queue = nouveau;
      }
      // cette ligne ne doit pas être dupliquées dans if...else...
      liste->tete = nouveau;
  // }
   return OK;
}

/**
 * Insère un élément à la fin de la liste.
 * @param liste pointeur sur la liste.
 * @param info pointeur sur une variable contenant l'information à insérer.
 * @return Renvoie OK si l'insertion s'est déroulée avec succès et MEMOIRE_INSUFFISANTE
 * s'il n'y a pas assez de mémoire pour créer le nouvel élément.
 */
Status insererEnQueue(Liste *liste, const Info *info) {

   assert(info != NULL);
   Element *nouveau = (Element *) malloc(sizeof(Element));

#ifdef MEMTEST
   nouveau = NULL;
#endif

   if (nouveau == NULL) {
      return MEMOIRE_INSUFFISANTE;
   } else {
      nouveau->info = *info;

       // ces deux lignes ne doivent pas être dupliquées dans if...else...
      nouveau->suivant = NULL;
      nouveau->precedent = liste->queue;
      if (!estVide(liste)) {
         liste->queue->suivant = nouveau;
      } else {
         liste->tete = nouveau;
      }
      // cette ligne ne doit pas être dupliquées dans if...else...
      liste->queue = nouveau;
   }
   return OK;
}

/**
 * Supprime le premier élément de la liste.
 * @param liste pointeur sur la liste.
 * @param info pointeur sur une variable recevant la valeur de l'élément supprimé.
 * @return Renvoie OK si l'élément en tête a été supprimé et le stock dans la variable info. Renvoie
 * LISTE_VIDE si la liste était vide.
 */
Status supprimerEnTete(Liste *liste, Info *info) {
   assert(info != NULL);
   if (estVide(liste)) {
      return LISTE_VIDE;
   } // else { // inutile
       // le code suivant ne semble plus compact / moins dupliqué
      Element* aSupprimer = liste->tete;
      *info = aSupprimer->info;
      liste->tete = aSupprimer->suivant;
      free(aSupprimer);
      if(liste->tete) {
         liste->tete->precedent = NULL;
      } else {
         liste->queue = NULL;
      }
      return OK;
   // }
}

/**
 * Supprime le dernière élément de la liste.
 * @param liste pointeur sur la liste.
 * @param info pointeur sur une variable recevant la valeur de l'élément supprimé.
 * @return Renvoie OK si l'élément en queue a été supprimé et le stock dans la variable info. Renvoie
 * LISTE_VIDE si la liste était vide.
 */
Status supprimerEnQueue(Liste *liste, Info *info) {
   assert(info != NULL);
   if (estVide(liste)) {
      return LISTE_VIDE;
   } else {
       // un peu trop de duplication. voir supprimerEnTete
      *info = liste->queue->info;
      if (liste->queue->precedent) {
         liste->queue = liste->queue->precedent;
         free(liste->queue->suivant);
         liste->queue->suivant = NULL;
      } else {
         free(liste->tete);
         liste->tete = NULL;
         liste->queue = NULL;
      }
      return OK;
   }
}

/**
 * Supprime un/des éléments selon une fonctions critère retournant un boolean(par ex : isPair()).
 * @param liste pointeur sur la liste.
 * @param critere fonction prenant deux paramètres position et pointeur sur le contenu de d'un élément de la liste.
 */
void supprimerSelonCritere(Liste *liste, bool (*critere)(size_t position, const Info *info)) {
   if (estVide(liste))
      return;
   size_t pos = 0;
   //Variable "info" utilisée pour l'appel de supprimerEnTete et
   // supprimeEnQueue
   int info;
   // Pas nécessaire d'utiliser pastPtr, puisqu'il vaut currentPtr->precedent
   // le passage au suivant peut également être simplifié avec un pointeur suivant
//   Element *pastPtr;
   for (Element *currentPtr = liste->tete, *suivant; currentPtr != NULL; currentPtr = suivant, ++pos) {
      suivant = currentPtr->suivant;
      if (critere(pos, &currentPtr->info)) {
         if (currentPtr == liste->tete) {
            supprimerEnTete(liste, &info);
        //    currentPtr = liste->tete;
         } else if (currentPtr == liste->queue) {
            supprimerEnQueue(liste, &info);
        //    currentPtr = NULL;
         } else { //Cas du milieu
             // pastPtr->suivant = currentPtr->suivant;
             currentPtr->precedent->suivant = suivant;
             suivant->precedent = currentPtr->precedent;
             free(currentPtr);
        //    currentPtr = pastPtr->suivant;
        //    currentPtr->precedent = pastPtr;
         }
      } // else {
      //   pastPtr = currentPtr;
      //   currentPtr = currentPtr->suivant;
//      }
   }
}

/**
 * Vide la liste à partir de la position donnée en paramètre.
 * @param liste pointeur sur la liste.
 * @param position index de l'élément dans la liste.
 */
void vider(Liste *liste, size_t position) {
    // Vous êtes sûrs du prototype de cette fonction ? Elle devrait retourner Status pour signaler une
    // position incorrecte, non ?
    //
    // appeler longueur est sale. Cela double le temps d'execution puisqu'il faut parcourir deux fois la liste
    // de manière générale l'approche choisie est un peu boiteuse. Il faudrait parcourir la liste jusqu'à position
    // puis effacer à partir de la. Et traiter à part le cas position == 0

   size_t taille = longueur(liste);
   if (estVide(liste) || position >= taille)
      return;

   if (taille == 1) {
      free(liste->tete);
      liste->tete = NULL;
      liste->queue = NULL;
   } else {
      Element *currentPtr = liste->queue->precedent;
      /* Parcours la boucle depuis la fin en supprimant les éléments jusqu'à
       * l'index position et réaffecte le pointeur sur la queue de liste.
       * */
      for (size_t i = taille - 1; i >= position && i != 0; --i, currentPtr = currentPtr->precedent) {
         free(currentPtr->suivant);
         // les 2 lignes suivantes n'ont rien à faire dans la boucle
         currentPtr->suivant = NULL;
         liste->queue = currentPtr;
      }

      if (!position) {
         free(liste->tete);
// INUTILE         currentPtr = NULL;
         liste->queue = NULL;
         liste->tete = NULL;

      }
   }
}

/**
 * Vérifie si les deux listes passées en paramètres sont égaleschecklist.
 * @param liste1 pointeur sur la première liste.
 * @param liste2 pointeur sur la seconde liste.
 * @return un true si égales ou false si pas égales.
 */
bool sontEgales(const Liste *liste1, const Liste *liste2) {

   Element *currentPtrL1 = liste1->tete;
   Element *currentPtrL2 = liste2->tete;

   while (currentPtrL1 && currentPtrL2) {
      if (currentPtrL1->info != currentPtrL2->info)
         return false;
      currentPtrL1 = currentPtrL1->suivant;
      currentPtrL2 = currentPtrL2->suivant;
   }

   return !currentPtrL1 && !currentPtrL2;
}
