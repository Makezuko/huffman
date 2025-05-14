#ifndef TABELA_FREQUENCIA_H
#define TABELA_FREQUENCIA_H

#include "meustiposonlinegdb.h"
#include <stdio.h>

#define TAM_ALFABETO 256

void contar_frequencias(FILE* arquivo, unsigned int frequencias[TAM_ALFABETO]);

#endif
