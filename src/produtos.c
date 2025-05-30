#include "../include/produtos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void cadastrarProduto(Produto** produtos, Categoria* categorias) {
    printf("\n--- Cadastro de Produto ---\n");

    Produto* novo = malloc(sizeof(Produto));
    if (!novo) {
        printf("Erro ao alocar memória para o produto.\n");
        return;
    }

    novo->id = 1;
    Produto* atual = *produtos;
    while (atual && atual->prox) {
        atual = atual->prox;
    }
    if (atual) novo->id = atual->id + 1;

    getchar(); // limpa buffer do teclado

    printf("Descrição: ");
    fgets(novo->descricao, sizeof(novo->descricao), stdin);
    novo->descricao[strcspn(novo->descricao, "\n")] = 0;

    printf("Estoque atual: ");
    scanf("%d", &novo->estoque);

    printf("Estoque mínimo: ");
    scanf("%d", &novo->estoque_minimo);

    getchar();

    while (1) {
        int categoriaId;
        printf("Categoria (ID): ");
        listarCategorias(categorias);
        scanf("%d", &categoriaId);
        Categoria *categoria = pegarCategoria(categorias, categoriaId);
        if (!categoria) {
            printf("Categoria não encontrada. Tente novamente.\n");
            continue;
        }
        strcpy(novo->categoria, categoria->descricao);
        break;
    }

    printf("Preço de compra: ");
    scanf("%f", &novo->preco_compra);

    printf("Preço de venda: ");
    scanf("%f", &novo->preco_venda);

    novo->prox = NULL;
    if (!*produtos) *produtos = novo;
    else atual->prox = novo;

    printf("Produto cadastrado com sucesso! ID: %d\n", novo->id);
}

Produto* pegarProduto(Produto* lista, int id) {
    while (lista) {
        if (lista->id == id) return lista;
        lista = lista->prox;
    }
    return NULL;
}

void listarProdutos(Produto* produtos) {
    if (!produtos) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }
    printf("\n===== Lista de Produtos =====\n");
    while (produtos) {
        exibirProduto(produtos);
        produtos = produtos->prox;
    }
}

void listarProdutosEstoqueZeroOuMinimo(Produto* produtos) {
    int encontrou = 0;
    while (produtos) {
        if (produtos->estoque <= produtos->estoque_minimo) {
            exibirProduto(produtos);
            encontrou = 1;
        }
        produtos = produtos->prox;
    }
    if (!encontrou) {
        printf("Nenhum produto com estoque zero ou mínimo encontrado.\n");
    }
}

void exibirProduto(Produto* p) {
    printf("ID: %d\n", p->id);
    printf("Descrição: %s\n", p->descricao);
    printf("Estoque: %d\n", p->estoque);
    printf("Estoque mínimo: %d\n", p->estoque_minimo);
    printf("Categoria: %s\n", p->categoria);
    printf("Preço de compra: R$ %.2f\n", p->preco_compra);
    printf("Preço de venda: R$ %.2f\n", p->preco_venda);
    printf("-----------------------------\n");
}

void salvarProdutos(const char* nomeArquivo, Produto* produtos) {
    FILE* f = fopen(nomeArquivo, "w");
    if (!f) {
        printf("Erro ao salvar produtos no arquivo '%s'. Verifique se a pasta existe e se há permissão.\n", nomeArquivo);
        return;
    }

    while (produtos) {
        fprintf(f, "%d|%s|%d|%d|%s|%.2f|%.2f\n",
                produtos->id,
                produtos->descricao,
                produtos->estoque,
                produtos->estoque_minimo,
                produtos->categoria,
                produtos->preco_compra,
                produtos->preco_venda);
        produtos = produtos->prox;
    }

    fclose(f);
    printf("Produtos salvos com sucesso.\n");
}

void menuListarProduto(Produto* produtos) {
    if (!produtos) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }

    int opcao;
    do {
        printf("\n===== Menu Listar Produtos =====\n");
        printf("1. Listar todos os produtos\n");
        printf("2. Listar produtos com estoque zero ou mínimo\n");
        printf("3. Listar produtos mais vendidos (em um período)\n");
        printf("4. Voltar ao menu principal\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                listarProdutos(produtos);
                break;
            case 2:
                listarProdutosEstoqueZeroOuMinimo(produtos);
                break;
            case 3:
                printf("Funcionalidade de listar produtos mais vendidos ainda não implementada.\n");
                break;
            case 4:
                printf("Voltando ao menu principal...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 4);
}

void liberarProdutos(Produto* lista) {
    while (lista) {
        Produto* temp = lista;
        lista = lista->prox;
        free(temp);
    }
}