#include "tabela_frequencia.h"

void contar_frequencias(FILE* arquivo, unsigned int frequencias[TAM_ALFABETO]) {
    for (int i = 0; i < TAM_ALFABETO; i++) {
        frequencias[i] = 0;
    }
    int c;
    while ((c = fgetc(arquivo)) != EOF) {
        frequencias[(U8)c]++;
    }
    rewind(arquivo);
}
