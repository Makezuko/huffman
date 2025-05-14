#include "compressao.h"
#include <string.h>
#include <stdint.h>               /* ←  NOVO  */

void gerar_tabela_codigos(No* raiz, Codigo tabela[TAM_ALFABETO], Codigo atual) {
    if (!raiz->esquerda && !raiz->direita) {
        tabela[raiz->caractere] = atual;
        return;
    }
    if (raiz->esquerda) {
        Codigo esq = atual;
        esq.bits[esq.tamanho / 8] &= ~(1 << (7 - esq.tamanho % 8));
        esq.tamanho++;
        gerar_tabela_codigos(raiz->esquerda, tabela, esq);
    }
    if (raiz->direita) {
        Codigo dir = atual;
        dir.bits[dir.tamanho / 8] |=  (1 << (7 - dir.tamanho % 8));
        dir.tamanho++;
        gerar_tabela_codigos(raiz->direita, tabela, dir);
    }
}

void compactar(const char* nome_entrada, const char* nome_saida) {
    FILE* entrada = fopen(nome_entrada, "rb");
    FILE* saida   = fopen(nome_saida,   "wb");
    if (!entrada || !saida) {
        fprintf(stderr, "Erro ao abrir arquivos!\n");
        exit(1);
    }

    unsigned int frequencias[TAM_ALFABETO];
    contar_frequencias(entrada, frequencias);

    No* raiz = construir_arvore(frequencias);
    if (!raiz) {
        fprintf(stderr, "Falha ao construir árvore de Huffman!\n");
        exit(1);
    }

    Codigo tabela[TAM_ALFABETO] = {0};
    Codigo atual = {0, {0}};
    gerar_tabela_codigos(raiz, tabela, atual);

    /* ----- Cabeçalho ----- */
    fwrite(frequencias, sizeof(unsigned int), TAM_ALFABETO, saida);

    uint64_t total_bits = 0;                 /* ←  AGORA 64 bits */
    long pos_total_bits = ftell(saida);
    fwrite(&total_bits, sizeof(uint64_t), 1, saida);

    /* ----- Codificação ----- */
    U8 buffer = 0;
    int bits_no_buffer = 0;
    int c;
    while ((c = fgetc(entrada)) != EOF) {
        Codigo codigo = tabela[c];
        total_bits += codigo.tamanho;

        for (unsigned int i = 0; i < codigo.tamanho; i++) {
            buffer <<= 1;
            buffer |= (codigo.bits[i / 8] >> (7 - (i % 8))) & 1;
            bits_no_buffer++;

            if (bits_no_buffer == 8) {
                fputc(buffer, saida);
                bits_no_buffer = 0;
                buffer = 0;
            }
        }
    }

    if (bits_no_buffer) {
        buffer <<= (8 - bits_no_buffer);
        fputc(buffer, saida);
    }

    fclose(entrada);
    fclose(saida);

    /* ----- Atualiza total_bits ----- */
    saida = fopen(nome_saida, "rb+");
    fseek(saida, pos_total_bits, SEEK_SET);
    fwrite(&total_bits, sizeof(uint64_t), 1, saida);
    fclose(saida);

    liberar_arvore(raiz);
}
