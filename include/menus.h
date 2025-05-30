#ifndef MENUS_H
#define MENUS_H

#include "usuarios.h"
#include "clientes.h"
#include "produtos.h"
#include "vendas.h"
#include "itens_venda.h"
#include "pagamento.h"
#include "caixa.h"
#include "categorias.h"

// Menu principal
void menuPrincipal(Usuario* u, int* tu, Cliente* c, int* tc, Produto* p, int* tp, Categoria* cat, int* totalCategorias, Venda* v, int* tv,
                   ItemVenda* i, int* ti, Pagamento* pg, int* tpg, Caixa* cx);

// Submenus
void menuCadastros(Usuario* u, int* tu, Cliente* c, int* tc, Produto* p, int* tp, Categoria* cat, int* totalCategorias);
void menuVendas(Venda* v, int* tv, Produto* p, int* tp, Cliente* c, int totalClientes, ItemVenda* i, int* ti);
void menuAberturaCaixa(Caixa* caixa);
void menuFechamentoCaixa(Caixa* caixa, Pagamento* pagamentos, int totalPagamentos, float totalVendas);
void menuRelatorios(Cliente* c, int totalClientes, Produto* p, int totalProdutos, Venda* v, int totalVendas, Categoria* cat, int totalCategorias);

#endif