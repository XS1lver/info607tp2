#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define BASE 10 // Base pour le calcul du hash
#define MODULO 1000003 // Grand nombre premier pour limiter les collisions

int bruteForce(char* text, char* motif){
    int i = 0;
    int m = strlen(motif);
    int n = strlen(text);
    bool trouve = false;

    // Parcours du texte jusqu'à ce que le motif soit trouvé ou que la fin du texte soit atteinte
    while (i <= (n - m)){
        if (strncmp(&text[i], motif, m) == 0){ // Compare les m premiers caractères sur les chaines text[i] et motif
            return i; // On renvoie l'indice où se trouve le motif dans text
        }
        else{
            i = i + 1;
        }
    }
    return -1; // Si le motif n'est pas trouvé, on retourne -1
}

int hash(char* str) {
    int val = 0;
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        val = (val * BASE + (str[i] - '0')) % MODULO; // str[i] - '0' récupère la valeur du chiffre ('0' ayant le code ASCII 48)
    }
    return val;
}

int RabinKarp(char* text, char* motif){
    int i = 0; // Indice de départ pour le parcours du texte
    int m = strlen(motif);
    int n = strlen(text);
    bool trouve = false;
    int hashm = hash(motif); // Calcul du hash du motif à rechercher

    // Initialisation pour le mode de calcul économique
    char premiere_fenetre[m + 1]; // Initialisation de la première fenêtre de texte à comparer avec le motif
    strncpy(premiere_fenetre, text, m); // Copie des m premiers caractères de text dans premiere_fenetre
    premiere_fenetre[m] = '\0'; // Ajout du caractère de fin de chaîne
    int hasht = hash(premiere_fenetre); // Valeur de hachage initiale du sous-motif dans le fichier

    // On calcule le poids pour le caractère de gauche du motif (le plus à gauche) qui sera retiré lors du décalage économique
    int poids = 1;
    for (int j = 0; j < m - 1; j++) {
        poids = (poids * BASE) % MODULO;
    }

    while (i <= n - m){
        if (hashm == hasht && strncmp(&text[i], motif, m) == 0){ // Si les hashs sont égaux, on compare les chaînes de caractères
            return i; // Retourne l'indice où se trouve le motif dans text
        }
        else {
            // Décalage économique du hash pour le sous-motif suivant (un cran vers la droite)
            if (i < n - m) {
                // Calcul du nouveau hash en retirant le caractère de gauche et en ajoutant le caractère de droite
                hasht = (BASE * (hasht - (text[i] - '0') * poids) + (text[i + m] - '0')) % MODULO; 
                if (hasht < 0) {
                    hasht += MODULO; // Assurer que le hash reste positif
                }
            }
            i = i + 1; // Avancement dans le texte
        }
    } 

    return -1; // Si le motif n'est pas trouvé, on retourne -1

}

int main(){
    int n = 100000000; // Taille du texte à générer
    char* text = malloc(n + 1); 
    char motif[] = "534872941";
    int m = strlen(motif);

    // Génération d'un texte aléatoire
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        text[i] = (rand() % BASE) + '0';
    }
    text[n] = '\0';

    strcpy(&text[n - m], motif); // Motif placé à la fin pour forcer le pire cas de l'algo

    printf("\nTest de performance pour Brute force:\n");
    clock_t start_brute_force = clock();
    int result = bruteForce(text, motif);
    clock_t end_brute_force = clock();
    double time_brute_force = ((double)(end_brute_force - start_brute_force)) / CLOCKS_PER_SEC;
    printf("Motif trouvé à l'indice %d\n", result);
    printf("Temps: %f\n\n", time_brute_force);


    printf("Test de performance pour Rabin Karp:\n");
    clock_t start_RK = clock();
    int result_RK = RabinKarp(text, motif);
    clock_t end_RK = clock();
    double time_RK = ((double)(end_RK - start_RK)) / CLOCKS_PER_SEC;
    printf("Motif trouvé à l'indice %d\n", result_RK);
    printf("Temps: %f\n", time_RK);


    free(text);
    return 0;
}