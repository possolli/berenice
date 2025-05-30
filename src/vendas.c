
#include "../include/vendas.h"
#include <stdio.h>
#include <stdlib.h>

void novaVenda(Venda** vendas, int* totalVendas, Produto* produtos, Cliente* clientes, ItemVenda* itens, int* totalItens) {
    if (!clientes) {
        printf("Nenhum cliente cadastrado. Cadastre um cliente antes de realizar uma venda.\n");
        return;
    }

    if (produtos == NULL) {
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

    Cliente* cliente = NULL;

    while (1) {
        printf("Digite o ID do cliente ou 0 para sair: \n");
        scanf("%d", &v->cliente_id);

        if (v->cliente_id == 0) {
            printf("Retornando ao menu de vendas...\n");
            return;
        }

        cliente = pegarCliente(clientes, v->cliente_id);
        if (!cliente) {
            printf("Cliente não encontrado. Tente novamente.\n");
            v->cliente_id = 0; // Reseta o ID do cliente para tentar novamente
        } else {
            printf("NOVA VENDA PARA: %s\n", cliente->nome);
        }

        v->quantidade = 0; // Inicializa a quantidade de produtos na venda
        v->total = 0.0f; // Inicializa o total da venda
        v->desconto = 0.0f; // Inicializa o desconto da venda
        v->tipo_pagamento[0] = '\0'; // Inicializa o tipo de pagamento
        v->status[0] = '\0'; // Inicializa o status da venda

        while (1) {
            listarProdutos(produtos);
            printf("Digite o ID do produto ou 0 para cancelar a venda: \n");
            int id_produto;
            scanf("%d", &id_produto);

            if (id_produto == 0) {
                if (v->quantidade == 0) {
                    printf("Nenhum produto adicionado. Venda cancelada.\n");
                    return;
                }
                break; // Finaliza a venda
            }

            Produto* produto = pegarProduto(produtos, id_produto);
            if (!produto) {
                printf("Produto não encontrado. Tente novamente.\n");
                continue; // Continua o loop para tentar novamente
            }

            ItemVenda item;
            item.venda_id = v->id;
            item.produto_id = produto->id;
            item.quantidade = 0; // Inicializa a quantidade do item
            item.preco = produto->preco_venda; // Preço do produto
            item.total = 0.0f; // Inicializa o total do item

            while (1) {
                printf("Digite a quantidade do produto %s (estoque: %d) ou 0 para escolher outro: ", produto->descricao, produto->estoque);
                scanf("%d", &item.quantidade);

                if (item.quantidade == 0) {
                    printf("Escolha outro produto ou finalize a venda.\n");
                    break; // Sai do loop de quantidade para escolher outro produto
                }

                if (item.quantidade < 0) {
                    printf("Quantidade inválida. Tente novamente.\n");
                } else if (item.quantidade > produto->estoque) {
                    printf("Quantidade maior que o estoque disponível. Tente novamente.\n");
                } else {
                    item.total = item.quantidade * item.preco; // Calcula o total do item
                    v->quantidade += item.quantidade; // Atualiza a quantidade total da venda
                    v->total += item.total; // Atualiza o total da venda
                    printf("Item adicionado: %s, Quantidade: %d, Preço unitário: R$ %.2f, Total: R$ %.2f\n",
                           produto->descricao, item.quantidade, item.preco, item.total);

                    produto->estoque -= item.quantidade; // Atualiza o estoque do produto
                    break; // Sai do loop de quantidade
                }
            }
        }
    }

}

void listarVendas(Venda* vendas, int total) {
    printf("Função listarVendas chamada\n");
}

void salvarVendas(const char* nomeArquivo, Venda* vendas, int total) {
    printf("Função salvarVendas chamada\n");
}
