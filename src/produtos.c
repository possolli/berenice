
#include "../include/produtos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void cadastrarProduto(Produto** produtos, int* total, Categoria* categorias, int totalCategorias) {
    printf("\n--- Cadastro de Produto ---\n");

    // Realoca espaço para novo produto
    Produto* novo = realloc(*produtos, sizeof(Produto) * (*total + 1));
    if (!novo) {
        printf("Erro ao alocar memória para o produto.\n");
        return;
    }
    *produtos = novo;

    Produto* p = &(*produtos)[*total];

    // ID sequencial
    p->id = (*total == 0) ? 1 : (*produtos)[*total - 1].id + 1;

    getchar(); // limpa buffer do teclado

    printf("Descrição: ");
    fgets(p->descricao, sizeof(p->descricao), stdin);
    p->descricao[strcspn(p->descricao, "\n")] = 0;

    printf("Estoque atual: ");
    scanf("%d", &p->estoque);

    printf("Estoque mínimo: ");
    scanf("%d", &p->estoque_minimo);

    getchar(); // limpa buffer após scanf

    while (1) {
        int categoriaId;
        int categoriaEncontrada = 0;
        printf("Categoria (ID): ");
        for (int i = 0; i < totalCategorias; i++) {
            printf("%d - %s\n", categorias[i].id, categorias[i].descricao);
        }
        scanf("%d", &categoriaId);
        for (int i = 0; i < totalCategorias; i++) {
            if (categorias[i].id == categoriaId) {
                strcpy(p->categoria, categorias[i].descricao);
                categoriaEncontrada = 1;
                break;
            }
        }
        if (categoriaEncontrada) {
            break;
        } else {
            printf("Categoria não encontrada. Tente novamente.\n");
        }
    }

    printf("Preço de compra: ");
    scanf("%f", &p->preco_compra);

    printf("Preço de venda: ");
    scanf("%f", &p->preco_venda);

    (*total)++;
    printf("Produto cadastrado com sucesso! ID: %d\n", p->id);
}

void listarProdutos(Produto* produtos, int total) {
    if (total == 0) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }

    printf("\n===== Lista de Produtos =====\n");
    for (int i = 0; i < total; i++) {
        printf("ID: %d\n", produtos[i].id);
        printf("Descrição: %s\n", produtos[i].descricao);
        printf("Estoque: %d\n", produtos[i].estoque);
        printf("Estoque mínimo: %d\n", produtos[i].estoque_minimo);
        printf("Categoria: %s\n", produtos[i].categoria);
        printf("Preço de compra: R$ %.2f\n", produtos[i].preco_compra);
        printf("Preço de venda: R$ %.2f\n", produtos[i].preco_venda);
        printf("-----------------------------\n");
    }
}

void salvarProdutos(const char* nomeArquivo, Produto* produtos, int total) {
    FILE* f = fopen(nomeArquivo, "w");
    if (!f) {
        printf("Erro ao salvar produtos no arquivo '%s'. Verifique se a pasta existe e se há permissão.\n", nomeArquivo);
        return;
    }

    for (int i = 0; i < total; i++) {
        fprintf(f, "%d|%s|%d|%d|%s|%.2f|%.2f\n",
                produtos[i].id,
                produtos[i].descricao,
                produtos[i].estoque,
                produtos[i].estoque_minimo,
                produtos[i].categoria,
                produtos[i].preco_compra,
                produtos[i].preco_venda);
    }

    fclose(f);
    printf("Produtos salvos com sucesso (%d registrados).\n", total);
}

