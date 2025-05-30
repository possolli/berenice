#ifndef VENDAS_H
#define VENDAS_H

#include "clientes.h"
#include "produtos.h"
#include "itens_venda.h"  // <- ESSENCIAL

typedef struct {
    int id;
    int cliente_id;
    int quantidade;
    float total;
    float desconto;
    char tipo_pagamento[20];
    char status[20];
    ItemVenda itens;
} Venda;

void novaVenda(Venda** vendas, int* totalVendas,
               Produto* produtos,
               Cliente* clientes,
               ItemVenda* itens, int* totalItens);

void listarVendas(Venda* vendas, int totalVendas);
void salvarVendas(const char* nomeArquivo, Venda* vendas, int totalVendas);

#endif
