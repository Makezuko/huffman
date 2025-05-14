#include "descompressao.h"
#include <stdint.h>               /* ←  NOVO  */

void descompactar(const char* nome_entrada, const char* nome_saida) {
    FILE* entrada = fopen(nome_entrada, "rb");
    FILE* saida   = fopen(nome_saida,   "wb");
    if (!entrada || !saida) {
        fprintf(stderr, "Erro ao abrir arquivos!\n");
        exit(1);
    }

    unsigned int frequencias[TAM_ALFABETO];
    fread(frequencias, sizeof(unsigned int), TAM_ALFABETO, entrada);

    uint64_t total_bits;          /* ←  AGORA 64 bits */
    fread(&total_bits, sizeof(uint64_t), 1, entrada);

    No* raiz = construir_arvore(frequencias);
    if (!raiz) {
        fprintf(stderr, "Falha ao reconstruir árvore de Huffman!\n");
        exit(1);
    }

    /* Caso especial – um único caractere no arquivo */
    int num_folhas = 0;
    U8 caractere_unico = 0;
    for (int i = 0; i < TAM_ALFABETO; i++) {
        if (frequencias[i]) {
            num_folhas++;
            caractere_unico = (U8)i;
        }
    }
    if (num_folhas == 1) {
        for (uint64_t i = 0; i < total_bits; i++) fputc(caractere_unico, saida);
        fclose(entrada); fclose(saida); liberar_arvore(raiz);
        return;
    }

    No* atual = raiz;
    uint64_t bits_lidos = 0;
    int byte_lido;

    while (bits_lidos < total_bits && (byte_lido = fgetc(entrada)) != EOF) {
        for (int i = 7; i >= 0 && bits_lidos < total_bits; i--) {
            int bit = (byte_lido >> i) & 1;
            atual = bit ? atual->direita : atual->esquerda;
            bits_lidos++;
            if (!atual->esquerda && !atual->direita) {
                fputc(atual->caractere, saida);
                atual = raiz;
            }
        }
    }

    fclose(entrada);
    fclose(saida);
    liberar_arvore(raiz);
}
