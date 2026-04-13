#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

typedef struct _liste_rec {
    int val;
    struct _liste_rec *suiv; 
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

// Tri fusion dérécursifié
liste_rec* fusion_derec(liste_rec* l1, liste_rec* l2){
    if (l1 == NULL) return l2;
    if (l2 == NULL) return l1;

    liste_rec temp; // Liste temporaire pour stocker le résultat de la fusion
    liste_rec* courant = &temp; // Pointeur pour parcourir la liste temporaire
    temp.suiv = NULL; // Initialisation de la liste temporaire

    // Parcours des deux listes tant qu'elles ne sont pas vides
    while(!vide(l1) && !vide(l2)){
        if (l1->val <= l2->val){
            courant->suiv = l1; // Ajout de l'élément de l1 à la liste temporaire
            l1 = l1->suiv; // Avancement dans la liste l1
        }
        else{
            courant->suiv = l2; // Ajout de l'élément de l2 à la liste temporaire
            l2 = l2->suiv; // Avancement dans la liste l2
        }
        courant = courant->suiv; // Avancement du pointeur courant dans la liste temporaire
    }

    if (l1 != NULL) { // Si la liste l1 est NULL 
        courant->suiv = l1; // On raccroche le reste de l1 à la liste temporaire
    } else {
        courant->suiv = l2; // Sinon, on raccroche le reste de l2 à la liste temporaire
    }

    return temp.suiv; // Retourne la tête de la liste fusionnée
}

// Définie une liste croissante de la liste récursive l
liste_rec* SSC(liste_rec* l){
    liste_rec* res = creer_liste(l->val);
    if (!vide(l->suiv) && l->val < (l->suiv)->val){
        res -> suiv = SSC(l->suiv);
    }
    return res;
}

liste_rec* SSC_derec(liste_rec* l){
    liste_rec* res = creer_liste(l->val); // On crée la nouvelle liste
    liste_rec* courant = res; // On crée un pointeur courant

    // Tant que la liste l n'est pas vide et que les éléments sont dans l'ordre croissant
    while (!vide(l->suiv) && l->val < (l->suiv)->val){
            courant->suiv = creer_liste(l->suiv->val); // On crée l'élément suivant
            courant = courant->suiv; // On avance le pointeur courant 
            l = l -> suiv; // On avance dans la liste l
        }
    return res; // Retourne la liste croissante
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

liste_rec* comp_derec(liste_rec* A, liste_rec* B){

    // Tant que les listes ne sont pas vides et le premier élément de chaque liste sont égaux
    while (!vide(A->suiv) && !vide(B->suiv) && A->val == B->val){
        A = A->suiv; // On avance dans A
        B = B->suiv; // On avance dans B
    }

    // Si A est NULL alors A correspondait parfaitement au début de B
    if (vide(A)){
        return B; // Donc on renvoie la liste complément (B)
    }

    return NULL; // Si la liste B est finie trop tôt par rapport à A.
}

// Tri une liste récursive 
liste_rec* tri(liste_rec* A){
    if (vide(A)) return NULL; // Si la liste est vide elle est déjà triée

    // Fusionne le premier élément de la liste A avec le reste de la liste trié récursivement par tri fusion
    return fusion( creer_liste( premier(*A) ), tri( reste(A) ) ); 
}

liste_rec* tri_derec(liste_rec* A){
    if (vide(A)) return NULL; // Si la liste est vide elle est déjà triée

    liste_rec* liste_triee = NULL; // On crée la liste contenant le résultat

    liste_rec* courant = A; // On crée un pointeur courant 

    // Tant que la liste n'est pas vide 
    while (!vide(courant)){
        liste_rec* nouveau = creer_liste(courant->val); // On crée une nouvelle liste avec l'élément à trier 
        liste_triee = fusion(nouveau, liste_triee); // On trie l'élément en l'insérant dans la nouvelle liste triée
        courant = courant->suiv; // On passe à l'élément suivant 
    }
    return liste_triee; // Renvoie la liste triée 
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

    printf("\nComp: ");
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


    printf("\nTri: ");
    liste_rec* l6 = tri(l3);
    affiche_liste(l6);

    // ----------------------------------------------------------------------------------
    // Question 1.7

    printf("\nTest de performance des différents tris:\n");
    int taille = 10000;
    liste_rec* l = NULL;

    for (int i = 0; i < taille; i++){
        l = prefixer(l, i); // On force le pire cas en mettant tout les éléments dans l'ordre décroissant
    }

    // Test récursif
    clock_t start_rec = clock();
    liste_rec* res_rec = tri(l);
    clock_t end_rec = clock();
    double time_rec = ((double)(end_rec - start_rec)) / CLOCKS_PER_SEC;

    // Test itératif
    clock_t start_iter = clock();
    liste_rec* res_iter = tri_derec(l);
    clock_t end_iter = clock();
    double time_iter = ((double)(end_iter - start_iter)) / CLOCKS_PER_SEC;

    printf("Pour %d elements :\n", taille);
    printf("Version récursif : %f secondes\n", time_rec);
    printf("Version itératif : %f secondes\n", time_iter);

    return 0;
}