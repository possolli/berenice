
#include "../include/itens_venda.h"
#include <stdio.h>

void salvarItensVenda(const char* nomeArquivo, int venda_id, ItemVenda* itens) {
    FILE* f = fopen(nomeArquivo, "a"); // <-- modo append
    if (!f) {
        printf("Erro ao abrir o arquivo de itens de venda.\n");
        return;
    }

    ItemVenda* atual = itens;
    while (atual != NULL) {
        fprintf(f, "%d|%d|%d|%.2f|%.2f\n",
                venda_id,
                atual->produto_id,
                atual->quantidade,
                atual->preco,
                atual->total);
        atual = atual->prox;
    }

    fclose(f);
}
