#include <stdio.h>
#include <string.h>

#define LIMITE 20

void main () {
    char palavra[LIMITE], reverso[LIMITE];
    int contador = 0;

    printf("\nPalavra (max 20 caracteres): ");
    fgets(palavra, LIMITE, stdin);
    palavra[strlen(palavra)-1] = '\0';  //delete \n at end
    
    for (int i = strlen(palavra)-1; i >= 0; i--) {
        reverso[contador] = palavra[i];
        contador++;
    }

    printf("Normal '%s' | Reverso: '%s'", palavra, reverso);
    if (strcmp(palavra, reverso) == 0) {
        printf("\nEh um palindromo\n\n");
    } else {
        printf("\nNao eh palindromo\n\n");
    }
}