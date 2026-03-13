#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct{
    int val;
    struct liste_rec *suiv;
} liste_rec;

liste_rec* creer_liste(int val){
    liste_rec* l = (liste_rec*)malloc(sizeof(liste_rec));
    l->val = val;
    l->suiv = NULL;
    return l;
}

bool vide(liste_rec* l){
    return (l->val == NULL && l->suiv == NULL);
}

int premier(liste_rec l){
    return l.val;
}

liste_rec* reste(liste_rec l){
    return l.suiv;
}

liste_rec* prefixer(liste_rec* l, int val){
    if (l == NULL) {
        return creer_liste(val);
    }
    else{
        liste_rec* l2 = creer_liste(val);
        l2->suiv = l;
        return l2;
    }
    
}

bool vide(liste_rec* l){
    return l == NULL;
}

liste_rec* suffixer(liste_rec* l, int val){
    if (l == NULL) {
        return creer_liste(val);
    }

    liste_rec* temp = l;
    while (temp->suiv != NULL) {
        temp = temp->suiv;
    }
    temp->suiv = creer_liste(val);
    return l;
}