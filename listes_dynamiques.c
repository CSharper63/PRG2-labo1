/*
 -----------------------------------------------------------------------------------
 Nom du fichier : listes_dynamiques.h
 Auteur(s)      : Guilan Mbayo, Mehdi Sahli, Maxime Chantemargue
 Date creation  : 22.04.2021

 Description    : Librairie permettant la gestion de listes doublement chaînées
                  non circulaires

 Remarque(s)    : -

 Compilateur    : Mingw-w64 gcc 8.1.0
 -----------------------------------------------------------------------------------
*/

#include "listes_dynamiques.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

// ------------------------------------------------------------------------------
// Initialisation de la liste.
// NB Cette fonction doit obligatoirement être utilisée pour se créer une liste
// car elle garantit la mise à NULL des champs tete et queue de la liste
Liste *initialiser() {
    // setter ptr queue et tete a NULL
    Liste *liste = malloc(sizeof(Liste)); //TODO check si on doit faire un malloc
    assert(liste != NULL);

    liste->tete = NULL;
    liste->queue = NULL;
    return liste;
}
// ------------------------------------------------------------------------------

// ------------------------------------------------------------------------------
// Renvoie true si liste est vide, false sinon.
bool estVide(const Liste *liste) {
    return liste->tete == NULL;
}
// ------------------------------------------------------------------------------

// ------------------------------------------------------------------------------
// Renvoie combien il y a d'éléments dans liste.
size_t longueur(const Liste *liste) {
    size_t idx = 0;
    for (Element *currentPtr = liste->tete; currentPtr != NULL; currentPtr = currentPtr->suivant) {
        ++idx;
    }
    return idx;
}
// ------------------------------------------------------------------------------

// ------------------------------------------------------------------------------
// Affiche le contenu intégral de liste sous la forme : [info_1,info_2,...]
// Dans le cas d'une liste vide, affiche : []
// En mode FORWARD, resp. BACKWARD, l'affichage se fait en parcourant liste
// dans le sens tete -> queue, resp. queue -> tete.
void afficher(const Liste *liste, Mode mode) {
    printf("["); //TODO utiliser une chaine de caractères
    if (!estVide(liste)) {
        switch (mode) {
            case FORWARD:
                for (Element *currentPtr = liste->tete; currentPtr != NULL; currentPtr = currentPtr->suivant) {
                    printf("%d", currentPtr->info);
                }
                break;
            case BACKWARD:
                for (Element *currentPtr = liste->queue; currentPtr != NULL; currentPtr = currentPtr->precedent) {
                    printf("%d", currentPtr->info);
                }
                break;
            default:
                printf("Veuillez selectionner un mode"); //@TODO: Vérifier si nécessaire
                break;
        }
    }
    printf("]");
}
// ------------------------------------------------------------------------------

// ------------------------------------------------------------------------------
// Insère un nouvel élément (contenant info) en tête de liste.
// Renvoie OK si l'insertion s'est déroulée avec succès et MEMOIRE_INSUFFISANTE
// s'il n'y a pas assez de mémoire pour créer le nouvel élément.
Status insererEnTete(Liste *liste, const Info *info) {
    //@TODO: créer variable pour cleanup
    assert(info != NULL);
    if (!estVide(liste)) {
        liste->tete->precedent = malloc(sizeof(Element));
        if (liste->tete->precedent != NULL) {
            liste->tete->precedent->info = *info;
            liste->tete->precedent->suivant = liste->tete;
            liste->tete->precedent->precedent = NULL;
            liste->tete = liste->tete->precedent;
            return OK;
        } else { return MEMOIRE_INSUFFISANTE; }
    } else {
        liste->tete = malloc(sizeof(Element));
        if (liste->tete != NULL) {
            liste->tete->info = *info;
            liste->tete->suivant = liste->tete;
            liste->tete->precedent = NULL;
            liste->queue = liste->tete;
            return OK;
        } else { return MEMOIRE_INSUFFISANTE; }
    }
}
// ------------------------------------------------------------------------------

// ------------------------------------------------------------------------------
// Insère un nouvel élément (contenant info) en queue de liste.
// Renvoie OK si l'insertion s'est déroulée avec succès et MEMOIRE_INSUFFISANTE
// s'il n'y a pas assez de mémoire pour créer le nouvel élément.
Status insererEnQueue(Liste *liste, const Info *info) {
    assert(info != NULL);
    //TODO: créer variable pour cleanup,
    //TODO creer un pointeur en fonction du statut de la liste (vide ou non) et l'utiliser partout dans la fonction
    if (!estVide(liste)) {
        liste->queue->suivant = malloc(sizeof(Element));
        if (liste->queue->suivant != NULL) {
            liste->queue->suivant->info = *info;
            liste->queue->suivant->suivant = NULL;
            liste->queue->suivant->precedent = liste->queue;
            liste->queue = liste->queue->suivant;
            return OK;
        } else { return MEMOIRE_INSUFFISANTE; }
    } else {
        liste->queue = malloc(sizeof(Element));
        if (liste->queue != NULL) {
            liste->queue->info = *info;
            liste->queue->suivant = NULL;
            liste->queue->precedent = liste->tete;
            liste->tete = liste->queue;
            return OK;
        } else { return MEMOIRE_INSUFFISANTE; }
    }
}
// ------------------------------------------------------------------------------

// ------------------------------------------------------------------------------
// Renvoie, via le paramètre info, l'info stockée dans l'élément en tête de liste,
// puis supprime, en restituant la mémoire allouée, ledit élément.
// Renvoie LISTE_VIDE si la liste passée en paramètre est vide, OK sinon.
Status supprimerEnTete(Liste *liste, Info *info) {
    assert(info != NULL);
    if (!estVide(liste)) {
        *info = liste->tete->info;
        if (liste->tete->suivant) {
            liste->tete = liste->tete->suivant;
            free(liste->tete->precedent);
            liste->tete->precedent = NULL;
        } else {
            free(liste->tete);
            liste->tete = NULL;
            liste->queue = NULL;
        }
        return OK;
    } else { return LISTE_VIDE; }
}
// ------------------------------------------------------------------------------

// ------------------------------------------------------------------------------
// Renvoie, via le paramètre info, l'info stockée dans l'élément en queue de liste,
// puis supprime, en restituant la mémoire allouée, ledit élément.
// Renvoie LISTE_VIDE si la liste passée en paramètre est vide, OK sinon.
Status supprimerEnQueue(Liste *liste, Info *info) {
    assert(info != NULL);
    if (!estVide(liste)) {
        *info = liste->queue->info;
        if (liste->queue->precedent) {
            liste->queue = liste->queue->precedent;
            // if(liste->queue->suivant)
            free(liste->queue->suivant);
            liste->queue->suivant = NULL;
        } else {
            free(liste->tete);
            liste->tete = NULL;
            liste->queue = NULL;
        }
        return OK;
    } else { return LISTE_VIDE; }
}
// ------------------------------------------------------------------------------

// ------------------------------------------------------------------------------
// Supprime, en restituant la mémoire allouée, tous les éléments de la liste qui
// vérifient le critère passé en second paramètre.
// Exemple: on souhaite supprimer de la liste tous les éléments dont la position est
// impaire et pour lesquels info est compris dans un certain intervalle de valeurs
void supprimerSelonCritere(Liste *liste, bool (*critere)(size_t position, const Info *info)) {
    if (estVide(liste)) return;
    //TODO pas fonctionnel sigtrap error
    size_t pos = 0;
    for (Element *currentPtr = liste->tete; currentPtr != NULL; currentPtr = currentPtr->suivant, ++pos){
        if(critere(pos, &currentPtr->info)){
            Element* tmp = currentPtr;
            if(currentPtr->precedent != NULL){
                currentPtr->precedent->suivant = currentPtr->suivant;
            }else{
                liste->tete = currentPtr->suivant;
            }
            if(currentPtr->suivant != NULL){
                currentPtr->suivant->precedent = currentPtr->precedent;
            } else{
                liste->queue = currentPtr->precedent;
            }

            free(tmp);
            tmp = NULL;
        }
    }
}
// ------------------------------------------------------------------------------

// ------------------------------------------------------------------------------
// Supprime, en restituant la mémoire allouée, tous les éléments de la liste
// à partir de la position position
// NB Vider à partir de la position 0 signifie vider toute la liste.
void vider(Liste *liste, size_t position) {
    size_t taille = longueur(liste);

    if (estVide(liste) || position > taille) return; //si la liste est vide ou que la position n'est pas dans le range

    Element *currentPtr = liste->queue->precedent;
    if (taille == 1) { //dans le cas où la position entrée est 0 mais qu'il n'y a qu'un élément dans la liste
        free(liste->tete);
        liste->tete = NULL;
        liste->queue = NULL;
    } else {
        /* Parcours la boucle depuis la fin en supprimant les éléments jusqu'à l'index position et réaffecte
         * le pointeur sur la queue de liste.
         * */
        for (size_t i = taille - 1; i >= position; --i, currentPtr = currentPtr->precedent) {
            free(currentPtr->suivant);
            currentPtr->suivant = NULL;
            liste->queue = currentPtr;
        }
    }
}
// ------------------------------------------------------------------------------

// ------------------------------------------------------------------------------
// Renvoie true si liste1 et liste2 sont égales (au sens mêmes infos et infos
// apparaissant dans le même ordre), false sinon.
// NB 2 listes vides sont considérées comme égales.
bool sontEgales(const Liste *liste1, const Liste *liste2) {
    if (longueur(liste1) != longueur(liste2)) return false;

    for (Element *currentPtr1 = liste1->tete, *currentPtr2 = liste2->tete; currentPtr1 != NULL && currentPtr2 != NULL; currentPtr1 = currentPtr1->suivant, currentPtr2 = currentPtr2->suivant) {
        if (currentPtr1->info != currentPtr2->info) return false;
    }
    return true;
}
// ------------------------------------------------------------------------------
