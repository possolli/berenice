#ifndef RELATORIOS_H
#define RELATORIOS_H

#include "usuarios.h"
#include "clientes.h"
#include "produtos.h"
#include "vendas.h"

void listarUsuarios(Usuario* usuarios, int totalUsuarios);
void listarClientes(Cliente* clientes, int totalClientes);
void listarProdutos(Produto* produtos);
void listarVendas(Venda* vendas, int totalVendas);

#endif
