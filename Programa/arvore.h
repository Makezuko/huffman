#ifndef ARVORE_H
#define ARVORE_H

#include "meustiposonlinegdb.h"

#define TAM_ALFABETO 256

typedef struct No {
    U8 caractere;
    unsigned int frequencia;
    struct No *esquerda, *direita;
} No;

typedef struct {
    No* nos[TAM_ALFABETO];
    int tamanho;
} FilaPrioridade;

No* criar_no(U8 caractere, unsigned int frequencia, No* esquerda, No* direita);

No* construir_arvore(unsigned int frequencias[TAM_ALFABETO]);

void liberar_arvore(No* raiz);

#endif
