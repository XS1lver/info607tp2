#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define BASE 10
#define MODULO 1000003 // Grand nombre premier pour limiter les collisions

int bruteForce(char* text, char* motif){
    int i = 0;
    int m = strlen(motif);
    int n = strlen(text);
    bool trouve = false;

    while (!trouve && (i <= (n - m))){
        if (strncmp(&text[i], motif, m) == 0){ // Compare les m premiers caractères sur les chaines text[i] et motif
            trouve = true;
        }
        else{
            i = i + 1;
        }
    }

    if (trouve){
        return i; // On renvoie l'indice où se trouve le motif dans text
    }
    else{
        return -1;
    }
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
    int i = 0;
    int m = strlen(motif);
    int n = strlen(text);
    bool trouve = false;
    int hashm = hash(motif);

    char sous_chaine[m + 1]; // Pour contenir une chaine de caractères de la même taille que le motif

    while (!trouve && i <= n - m){
        strncpy(sous_chaine, &text[i], m); // On copie dans sous_chaine la chaine de taille m à partir de text[i]
        sous_chaine[m] = '\0'; // Fin de la chaine de caractères

        if (hashm == hash(sous_chaine)){ // Si les hashs du motif et de la chaine de caractère extraite sont identiques 
            if (strncmp(&text[i], motif, m) == 0) { // On compare les 2 chaines de caractères
                trouve = true;
            }
            else{
                i = i + 1;
            }
        }
        else{
            i = i + 1;
        }
    }    
}

int main(){
    int n = 10000000;
    char* text = malloc(n + 1);
    char motif[] = "534872941";
    int m = strlen(motif);

    // Génération d'un texte aléatoire
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        text[i] = (rand() % 10) + '0';
    }
    text[n] = '\0';

    strcpy(&text[n - m], motif); // Motif placé à la fin pour forcer le pire cas de l'algo

    printf("\nTest de performance pour Brute force:\n");
    clock_t start_brute_force = clock();
    int result = bruteForce(text, motif);
    clock_t end_brute_force = clock();
    double time_brute_force = ((double)(end_brute_force - start_brute_force)) / CLOCKS_PER_SEC;
    printf("Motif trouvé à l'indice %d\n", result);
    printf("Temps: %f\n", time_brute_force);


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