
#include "../include/vendas.h"
#include <stdio.h>
#include <stdlib.h>

void novaVenda(Venda** vendas, int* totalVendas, Produto* produtos, int* totalProdutos, Cliente* clientes, int totalClientes, ItemVenda* itens, int* totalItens) {
    if (!totalClientes) {
        printf("Nenhum cliente cadastrado. Cadastre um cliente antes de realizar uma venda.\n");
        return;
    }

    if (*totalProdutos == 0) {
        printf("Nenhum produto cadastrado. Cadastre um produto antes de realizar uma venda.\n");
        return;
    }

    printf("\n--- Nova Venda ---\n");
    Venda* novaVenda = realloc(*vendas, sizeof(Venda) * (*totalVendas + 1));
    if (!novaVenda) {
        printf("Erro ao alocar memória para nova venda.\n");
        return;
    }
    *vendas = novaVenda;
    Venda* v = &(*vendas)[*totalVendas];
    v->id = (*totalVendas == 0) ? 1 : (*vendas)[*totalVendas - 1].id + 1;
    printf("ID do Cliente: ");
    scanf("%d", &v->cliente_id);
}

void listarVendas(Venda* vendas, int total) {
    printf("Função listarVendas chamada\n");
}

void salvarVendas(const char* nomeArquivo, Venda* vendas, int total) {
    printf("Função salvarVendas chamada\n");
}
