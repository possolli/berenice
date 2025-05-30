#ifndef CARREGAR_DADOS_H
#define CARREGAR_DADOS_H

#include <stdio.h>
#include <stdlib.h>
#include "clientes.h"
#include "produtos.h"
#include "categorias.h"
#include "vendas.h"
#include "itens_venda.h"
#include "pagamento.h"

#define BUFFER_INICIAL 10

Cliente* carregarClientes(const char* nomeArquivo);
Produto* carregarProdutos(const char* nomeArquivo, int* total);
Categoria* carregarCategorias(const char* nomeArquivo, int* total);
Venda* carregarVendas(const char* nomeArquivo, int* total);
ItemVenda* carregarItensVenda(const char* nomeArquivo, int* total);
Pagamento* carregarPagamentos(const char* nomeArquivo, int* total);

#endif