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
        l->suiv = l2;
        return l;
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
    printf("\n");
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

int main(){
    liste_rec* l1 = creer_liste(7);
    liste_rec* l2 = creer_liste(5);

    suffixer(l1, 9);
    prefixer(l2, 3);

    liste_rec* l3 = fusion(l1, l2);

    affiche_liste(l3);
}