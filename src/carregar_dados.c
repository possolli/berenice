#include "../include/carregar_dados.h"
#include "../include/utils.h"

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

// Carrega produtos
Produto* carregarProdutos(const char* nomeArquivo, int* total) {
    FILE* f = abrirOuCriarArquivoLeitura(nomeArquivo);
    if (!f) return NULL;
    
    int capacidade = BUFFER_INICIAL;
    Produto* lista = malloc(sizeof(Produto) * capacidade);
    *total = 0;
    
   while (fscanf(f, "%d|%49[^|]|%d|%d|%29[^|]|%f|%f\n",
              &lista[*total].id,
              lista[*total].descricao,
              &lista[*total].estoque,
              &lista[*total].estoque_minimo,
              lista[*total].categoria,
              &lista[*total].preco_compra,
              &lista[*total].preco_venda) == 7) {
        (*total)++;

        if (*total >= capacidade) {
            capacidade *= 2;
            lista = realloc(lista, sizeof(Produto) * capacidade);
        }
    }

    fclose(f);
    return lista;
}

// Carrega categorias
Categoria* carregarCategorias(const char* nomeArquivo, int* total) {
    FILE* f = abrirOuCriarArquivoLeitura(nomeArquivo);
    if (!f) return NULL;

    int capacidade = BUFFER_INICIAL;
    Categoria* lista = malloc(sizeof(Categoria) * capacidade);
    *total = 0;

    while (fscanf(f, "%d|%50[^\n]\n", &lista[*total].id, lista[*total].descricao) == 2) {
        (*total)++;
        if (*total >= capacidade) {
            capacidade *= 2;
            lista = realloc(lista, sizeof(Categoria) * capacidade);
        }
    }

    fclose(f);
    return lista;
}

// Carrega vendas
Venda* carregarVendas(const char* nomeArquivo, int* total) {
    FILE* f = abrirOuCriarArquivoLeitura(nomeArquivo);
    if (!f) return NULL;

    int capacidade = BUFFER_INICIAL;
    Venda* lista = malloc(sizeof(Venda) * capacidade);
    *total = 0;

    while (fscanf(f, "%d|%d|%d|%f|%f|%20[^|]|%20[^\n]\n",
                  &lista[*total].id,
                  &lista[*total].cliente_id,
                  &lista[*total].quantidade,
                  &lista[*total].total,
                  &lista[*total].desconto,
                  lista[*total].tipo_pagamento,
                  lista[*total].status) == 7) {
        (*total)++;
        if (*total >= capacidade) {
            capacidade *= 2;
            lista = realloc(lista, sizeof(Venda) * capacidade);
        }
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