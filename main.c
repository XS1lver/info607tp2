#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct _liste_rec {
    int val;
    struct _liste_rec *suiv; // On utilise le nom "struct node" ici
} liste_rec;

liste_rec* creer_liste(int val){
    liste_rec* l = (liste_rec*)malloc(sizeof(liste_rec));
    l->val = val;
    l->suiv = NULL;
    return l;
}

int premier(liste_rec l){
    return l.val;
}

liste_rec* reste(liste_rec* l){
    return l->suiv;
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
    if (vide(l)){
        return creer_liste(val);
    } 
    else if(l->suiv == NULL){
        l->suiv = creer_liste(val);
    }
    else{
        suffixer(l->suiv, val);
    }
    return l;
}

void affiche_liste(liste_rec* l){
    if (!vide(l)){
        printf("%d", l->val);
        affiche_liste(l->suiv);
    }
    else{
        printf("\n");
    }
}

liste_rec* fusion(liste_rec* l1, liste_rec* l2) {
    if (l1 == NULL) return l2;
    if (l2 == NULL) return l1;

    // On choisit le plus petit élément comme tête de liste
    if (l1->val <= l2->val) {
        l1->suiv = fusion(l1->suiv, l2);
        return l1;
    } else {
        l2->suiv = fusion(l1, l2->suiv);
        return l2;
    }
}

// Définie une liste croissante de la liste récursive l
liste_rec* SSC(liste_rec* l){
    liste_rec* res = creer_liste(l->val);
    if (!vide(l->suiv) && l->val < (l->suiv)->val){
        res -> suiv = SSC(l->suiv);
    }
    return res;
}

// Définie la sous-suite complément de la suite A dans la suite B
liste_rec* comp(liste_rec* A, liste_rec* B){
    if (A == NULL) {
        return B; // Si A est vide on retourne B
    }
    if (B == NULL) {
        return NULL; // Si seulement B est vide, alors A ne commence pas B
    }
    if (A->val == B->val) { // Si les éléments de A et de B sont égaux, on continue la comparaison avec les éléments suivants
        return comp(A->suiv, B->suiv);
    }
    // Si A ne commence pas B, retourne NULL
    return NULL;
}

int main(){
    liste_rec* l1 = creer_liste(7);
    liste_rec* l2 = creer_liste(5);

    suffixer(l1, 9);
    printf("Suffixer l1: ");
    affiche_liste(l1);

    l2 = prefixer(l2, 3);
    printf("\nPrefixer l2: ");
    affiche_liste(l2);

    printf("\nFusion l1 / l2: ");
    liste_rec* l3 = fusion(l1, l2);
    affiche_liste(l3);

    printf("\nSuffixer l3: ");
    suffixer(l3, 1);

    affiche_liste(l3);

    printf("\nSSC: ");
    liste_rec* l4 = SSC(l3);
    affiche_liste(l4);

    printf("\ncomp: ");
    liste_rec* lA = creer_liste(4); // Création de la liste A
    suffixer(lA, 7);
    suffixer(lA, 9);    
    liste_rec* lB = creer_liste(4); // Création de la liste B
    suffixer(lB, 7);
    suffixer(lB, 9);
    suffixer(lB, 1);
    suffixer(lB, 2);
    liste_rec* l5 = comp(lA, lB); // Calcul de la sous-suite complément de A dans B
    affiche_liste(l5);
}