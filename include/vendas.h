#ifndef VENDAS_H
#define VENDAS_H

#include "clientes.h"
#include "produtos.h"
#include "itens_venda.h"

typedef struct Venda {
    int id;
    int cliente_id;
    int quantidade;
    float total;
    float desconto;
    char tipo_pagamento[20];
    char status[20];
    char data[11]; // Formato "YYYY-MM-DD"
    ItemVenda* itens;
    struct Venda* prox; // Ponteiro para o próximo venda na lista
} Venda;

void novaVenda(Venda** vendas,
               Produto* produtos,
               Cliente* clientes);

void listarVendas(Venda* vendas);
void salvarVendas(const char* nomeArquivo, Venda* vendas);
void liberarVendas(Venda* vendas);
void menuListarVendas(Venda* vendas);

#endif
