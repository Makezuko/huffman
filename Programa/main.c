#include <stdio.h>
#include "compressao.h"
#include "descompressao.h"
#include <string.h>

int main(void) {
    int opcao;
    char entrada[256], saida[256];

    printf("==== CODIFICACAO DE HUFFMAN ====\n");
    printf("1 - Compactar arquivo\n");
    printf("2 - Descompactar arquivo\n");
    printf("Opcao: ");
    if (scanf("%d", &opcao) != 1) {
        fprintf(stderr, "Entrada invalida!\n");
        return 1;
    }

    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);

    printf("Arquivo de entrada: ");
    if (!fgets(entrada, sizeof(entrada), stdin)) return 1;
    entrada[strcspn(entrada, "\n")] = 0;

    printf("Arquivo de saida: ");
    if (!fgets(saida, sizeof(saida), stdin)) return 1;
    saida[strcspn(saida, "\n")] = 0;

    if (opcao == 1) {
        compactar(entrada, saida);
        printf("Compactacao concluida!\n");
    } else if (opcao == 2) {
        descompactar(entrada, saida);
        printf("Descompactacao concluida!\n");
    } else {
        printf("Opcao invalida.\n");
    }
    return 0;
}
