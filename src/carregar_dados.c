#include "../include/carregar_dados.h"
#include "../include/utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Usuario* carregarUsuarios(const char* nomeArquivo) {
    FILE* f = fopen(nomeArquivo, "r");
    if (!f) {
        f = fopen(nomeArquivo, "w");
        if (!f) return NULL;
        fclose(f);
        f = fopen(nomeArquivo, "r");
        if (!f) return NULL;
    }

    Usuario* inicio = NULL;
    Usuario* fim = NULL;

    char nome[50], login[13], senha[9];
    int tipo;

    while (fscanf(f, "%49[^|]|%12[^|]|%8[^|]|%d\n", nome, login, senha, &tipo) == 4) {
        Usuario* novo = malloc(sizeof(Usuario));
        if (!novo) continue;

        strcpy(novo->nome, nome);
        strcpy(novo->login, login);
        strcpy(novo->senha, senha);
        novo->tipo = tipo;
        novo->prox = NULL;

        if (inicio == NULL) {
            inicio = novo;
            fim = novo;
        } else {
            fim->prox = novo;
            fim = novo;
        }
    }

    fclose(f);
    return inicio;
}

// Carrega clientes
Cliente* carregarClientes(const char* nomeArquivo) {
    FILE* f = fopen(nomeArquivo, "r");
    if (!f) return NULL;

    Cliente* lista = NULL;
    Cliente temp;

    maior_id_cliente = 0; // Reseta o maior ID ao carregar clientes
    while (fscanf(f, "%d|%99[^|]|%99[^|]|%19[^|]|%99[^|]|%19[^\n]",
                  &temp.id,
                  temp.nome,
                  temp.nome_social,
                  temp.cpf,
                  temp.endereco,
                  temp.telefone) == 6) {

        Cliente* novo = malloc(sizeof(Cliente));
        if (!novo) continue;
        *novo = temp;
        novo->prox = NULL;

        if (!lista) {
            lista = novo;
        } else {
            Cliente* atual = lista;
            while (atual->prox) atual = atual->prox;
            atual->prox = novo;
        }

        if (temp.id > maior_id_cliente) {
            maior_id_cliente = temp.id; // Atualiza o maior ID encontrado
        }
    }

    fclose(f);
    return lista;
}

Produto* carregarProdutos(const char* nomeArquivo) {
    FILE* f = abrirOuCriarArquivoLeitura(nomeArquivo);
    if (!f) return NULL;

    Produto* inicio = NULL;
    Produto* fim = NULL;

    while (1) {
        Produto* novo = malloc(sizeof(Produto));
        if (!novo) break;

        int lidos = fscanf(f, "%d|%49[^|]|%d|%d|%29[^|]|%f|%f\n",
                           &novo->id,
                           novo->descricao,
                           &novo->estoque,
                           &novo->estoque_minimo,
                           novo->categoria,
                           &novo->preco_compra,
                           &novo->preco_venda);
        if (lidos != 7) {
            free(novo);
            break;
        }

        novo->prox = NULL;

        if (inicio == NULL) {
            inicio = novo;
            fim = novo;
        } else {
            fim->prox = novo;
            fim = novo;
        }
    }

    fclose(f);
    return inicio;
}

Categoria* carregarCategorias(const char* nomeArquivo) {
    FILE* f = fopen(nomeArquivo, "r");
    if (!f) {
        f = fopen(nomeArquivo, "w");
        if (!f) return NULL;
        fclose(f);
        f = fopen(nomeArquivo, "r");
        if (!f) return NULL;
    }

    Categoria *inicio = NULL, *fim = NULL;
    int id;
    char descricao[50];

    while (fscanf(f, "%d|%49[^\n]\n", &id, descricao) == 2) {
        Categoria* nova = malloc(sizeof(Categoria));
        if (!nova) continue;

        nova->id = id;
        strcpy(nova->descricao, descricao);
        nova->prox = NULL;

        if (!inicio) {
            inicio = nova;
            fim = nova;
        } else {
            fim->prox = nova;
            fim = nova;
        }
    }

    fclose(f);
    return inicio;
}

// Carrega vendas
Venda* carregarVendas(const char* nomeArquivo) {
    FILE* f = abrirOuCriarArquivoLeitura(nomeArquivo);
    if (!f) return NULL;

    Venda* lista = NULL;
    Venda* ultimo = NULL;

    Venda temp;
    while (fscanf(f, "%d|%d|%d|%f|%f|%20[^|]|%20[^|]|%10[^\n]\n",
                  &temp.id,
                  &temp.cliente_id,
                  &temp.quantidade,
                  &temp.total,
                  &temp.desconto,
                  temp.tipo_pagamento,
                  temp.status,
                  temp.data) == 8) {
        Venda* nova = malloc(sizeof(Venda)
            );
        if (!nova) break;

        *nova = temp;
        nova->itens = NULL; // ou carregarItensVenda(nova->id) se for o caso
        nova->prox = NULL;

        if (lista == NULL) {
            lista = nova;
        } else {
            ultimo->prox = nova;
        }

        ultimo = nova;
    }

    fclose(f);
    return lista;
}

// Carrega itens de venda
ItemVenda* carregarItensVenda(const char* nomeArquivo, int* total) {
    FILE* f = abrirOuCriarArquivoLeitura(nomeArquivo);
    if (!f) return NULL;

    int capacidade = BUFFER_INICIAL;
    ItemVenda* lista = malloc(sizeof(ItemVenda) * capacidade);
    *total = 0;

    while (fscanf(f, "%d|%d|%d|%f|%f\n",
                  &lista[*total].venda_id,
                  &lista[*total].produto_id,
                  &lista[*total].quantidade,
                  &lista[*total].preco,
                  &lista[*total].total) == 5) {
        (*total)++;
        if (*total >= capacidade) {
            capacidade *= 2;
            lista = realloc(lista, sizeof(ItemVenda) * capacidade);
        }
    }

    fclose(f);
    return lista;
}

Pagamento* carregarPagamentos(const char* nomeArquivo, int* total) {
    FILE* f = abrirOuCriarArquivoLeitura(nomeArquivo);
    if (!f) return NULL;

    int capacidade = 10;
    Pagamento* lista = malloc(sizeof(Pagamento) * capacidade);
    *total = 0;

    while (fscanf(f, "%d|%f|%2s\n", &lista[*total].venda_id, &lista[*total].valor_pago, lista[*total].tipo) == 3) {
        (*total)++;
        if (*total >= capacidade) {
            capacidade *= 2;
            lista = realloc(lista, sizeof(Pagamento) * capacidade);
        }
    }

    fclose(f);
    return lista;
}