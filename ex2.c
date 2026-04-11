#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

int bruteForce(char* text, char* motif){
    int i = 0;
    int m = strlen(motif);
    int n = strlen(text);
    bool trouve = false;

    while (!trouve && (i <= (n - m))){
        if (strncmp(&text[i], motif, m) == 0){
            trouve = true;
        }
        else{
            i = i + 1;
        }
    }

    if (trouve){
        return i;
    }
    else{
        return -1;
    }
}

int main(){
    char text[] = "1230495830123";
    char pattern[] = "301";

    printf("Recherche du motif '%s' dans '%s' :\n", pattern, text);
    int result = bruteForce(text, pattern);

    if (result != -1){
        printf("Motif trouvé à l'indice %d\n", result);
    }
    else{
        printf("Motif non trouvé\n");
    }
    return 0;
}