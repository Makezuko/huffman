#ifndef COMPRESSAO_H
#define COMPRESSAO_H

#include "meustiposonlinegdb.h"
#include "arvore.h"
#include "tabela_frequencia.h"
#include <stdio.h>

typedef struct {
    unsigned int tamanho;  
    U8 bits[256];           
} Codigo;

void gerar_tabela_codigos(No* raiz, Codigo tabela[TAM_ALFABETO], Codigo atual);

void compactar(const char* nome_entrada, const char* nome_saida);

#endif
