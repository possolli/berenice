#ifndef CARREGAR_DADOS_H
#define CARREGAR_DADOS_H

#include "usuarios.h"
#include "clientes.h"
#include "produtos.h"
#include "categorias.h"
#include "vendas.h"
#include "itens_venda.h"
#include "pagamento.h"

#define BUFFER_INICIAL 10

Usuario* carregarUsuarios(const char* nomeArquivo);
Cliente* carregarClientes(const char* nomeArquivo);
Produto* carregarProdutos(const char* nomeArquivo);
Categoria* carregarCategorias(const char* nomeArquivo);
Venda* carregarVendas(const char* nomeArquivo);
ItemVenda* carregarItensVenda(const char* nomeArquivo, int* total);
Pagamento* carregarPagamentos(const char* nomeArquivo, int* total);

#endif