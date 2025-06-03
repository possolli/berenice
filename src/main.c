// Bibliotecas padrão
#include <stdio.h>
#include <stdlib.h>

// Headers com definições de structs (tipos de dados)
#include "../include/login.h"
#include "../include/usuarios.h"
#include "../include/clientes.h"
#include "../include/produtos.h"
#include "../include/categorias.h"
#include "../include/itens_venda.h"
#include "../include/vendas.h"
#include "../include/pagamento.h"
#include "../include/caixa.h"
#include "../include/relatorios.h"

// Utilitários e persistência
#include "../include/utils.h"
#include "../include/carregar_dados.h"

// Menus
#include "../include/menus.h"

int e_admin = 0; // Variável global para verificar se o usuário é administrador

int main() {
    Usuario* ptr_usuarios = carregarUsuarios("data/usuarios.txt");
    if (ptr_usuarios == NULL) {
        printf("Erro ao carregar usuários.\n");
        return 1;
    }

    Usuario* usuario_logado = login(ptr_usuarios);
    if (usuario_logado == NULL) {
        free(ptr_usuarios);
        return 1;
    }

    getchar(); // Limpa o buffer após o login

    e_admin = (usuario_logado->tipo == 1); // Verifica se o usuário logado é administrador

    if (e_admin) {
        printf("Seu usuário é um administrador.\n");
    } else {
        printf("Seu usuário é um usuário comum.\n");
    }

    // Agora pode acessar o usuário logado por ponteiro
    printf("Bem-vindo(a), %s!\n", usuario_logado->nome);

    int totalItens = 0;
    int totalPagamentos = 0;

    Cliente* ptr_clientes = carregarClientes("data/clientes.txt");
    Produto* ptr_produtos = carregarProdutos("data/produtos.txt");
    Categoria* ptr_categorias = carregarCategorias("data/categorias.txt");
    Venda* ptr_vendas = carregarVendas("data/vendas.txt");
    ItemVenda* ptr_itens = carregarItensVenda("data/itens_venda.txt", &totalItens);
    Pagamento* ptr_pagamentos = carregarPagamentos("data/pagamentos.txt", &totalPagamentos);
    Caixa caixa = {0.0, 0.0, 0}; // Caixa inicialmente fechado

    menuPrincipal(ptr_usuarios, ptr_clientes, ptr_produtos,
                    ptr_categorias, &ptr_vendas,
                    ptr_itens, &totalItens, ptr_pagamentos, &totalPagamentos, &caixa);

    if (confirmar("Deseja guardar as informações de Clientes, Produtos, Vendas e Pagamentos (s/n)? ")) {
        salvarUsuarios("data/usuarios.txt", ptr_usuarios);
        salvarClientes("data/clientes.txt", ptr_clientes);
        salvarProdutos("data/produtos.txt", ptr_produtos);
        salvarCategorias("data/categorias.txt", ptr_categorias);
        salvarVendas("data/vendas.txt", ptr_vendas);
        salvarPagamentos("data/pagamentos.txt", ptr_pagamentos, totalPagamentos);
        printf("Dados salvos com sucesso!\n");
    }

    liberarClientes(ptr_clientes);
    liberarProdutos(ptr_produtos);
    liberarCategorias(ptr_categorias);
    liberarUsuarios(ptr_usuarios);
    liberarVendas(ptr_vendas);
    free(ptr_itens);
    free(ptr_pagamentos);
    free(usuario_logado);
    return 0;
}
