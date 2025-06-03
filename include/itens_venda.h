#ifndef ITENS_VENDA_H
#define ITENS_VENDA_H

#include <stdio.h>

typedef struct ItemVenda {
    int venda_id;
    int produto_id;
    int quantidade;
    float preco;
    float total;
    struct ItemVenda* prox; // Ponteiro para o próximo item na lista
} ItemVenda;

void salvarItensVenda(const char* nomeArquivo, int venda_id, ItemVenda* itens);

#endif
