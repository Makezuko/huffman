#include "arvore.h"
#include <stdlib.h>

static void inicializar_fila(FilaPrioridade* fila, unsigned int frequencias[TAM_ALFABETO]) {
    fila->tamanho = 0;
    for (int i = 0; i < TAM_ALFABETO; i++) {
        if (frequencias[i] > 0) {
            fila->nos[fila->tamanho++] = criar_no((U8)i, frequencias[i], NULL, NULL);
        }
    }
}

static No* remover_minimo(FilaPrioridade* fila) {
    int indice_menor = 0;
    for (int i = 1; i < fila->tamanho; i++) {
        if (fila->nos[i]->frequencia < fila->nos[indice_menor]->frequencia) {
            indice_menor = i;
        }
    }
    No* minimo = fila->nos[indice_menor];
    for (int i = indice_menor; i < fila->tamanho - 1; i++) {
        fila->nos[i] = fila->nos[i + 1];
    }
    fila->tamanho--;
    return minimo;
}

No* criar_no(U8 caractere, unsigned int frequencia, No* esquerda, No* direita) {
    No* novo = (No*)malloc(sizeof(No));
    if (!novo) return NULL;
    novo->caractere  = caractere;
    novo->frequencia = frequencia;
    novo->esquerda   = esquerda;
    novo->direita    = direita;
    return novo;
}

No* construir_arvore(unsigned int frequencias[TAM_ALFABETO]) {
    FilaPrioridade fila;
    inicializar_fila(&fila, frequencias);

    if (fila.tamanho == 1) {
        No* folha = remover_minimo(&fila);
        No* raiz  = criar_no(0, folha->frequencia, folha, NULL);
        return raiz;
    }

    while (fila.tamanho > 1) {
        No* esq = remover_minimo(&fila);
        No* dir = remover_minimo(&fila);
        No* pai = criar_no(0, esq->frequencia + dir->frequencia, esq, dir);
        fila.nos[fila.tamanho++] = pai;
    }
    return fila.tamanho ? fila.nos[0] : NULL;
}

void liberar_arvore(No* raiz) {
    if (!raiz) return;
    liberar_arvore(raiz->esquerda);
    liberar_arvore(raiz->direita);
    free(raiz);
}
