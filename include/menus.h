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
void menuPrincipal(Usuario* u, Cliente* c, Produto* p, Categoria** cat, Venda** v,
                   ItemVenda* i, int* ti, Pagamento* pg, int* tpg, Caixa* cx);

// Submenus
void menuCadastros(Usuario* u, Cliente* c, Produto* p, Categoria** cat);
void menuVendas(Venda** v, Produto* p, Cliente* c, ItemVenda* i, int* ti);
void menuAberturaCaixa(Caixa* caixa);
void menuFechamentoCaixa(Caixa* caixa, Pagamento* pagamentos, int totalPagamentos, float totalVendas);
void menuRelatorios(Cliente* c, Produto* p, Venda* v, Categoria** cat);

#endif