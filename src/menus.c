#include "../include/menus.h"
#include <stdio.h>

#include "../include/usuarios.h"

void menuPrincipal(Usuario* u, Cliente* c, Produto* p, Categoria* cat, Venda* v, int* tv, ItemVenda* i, int* ti, Pagamento* pg, int* tpg, Caixa* cx) {
    int opcao;
    do {
        printf("\n========== MENU PRINCIPAL ==========\n");
        printf("1. Cadastros\n");
        printf("2. Vendas\n");
        printf("3. Abertura de Caixa\n");
        printf("4. Fechamento de Caixa\n");
        printf("5. Relatórios\n");
        printf("7. Sair\n");
        printf("Escolha uma opção: ");

        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                menuCadastros(u, c, p, cat);
                break;
            case 2:
                menuVendas(v, tv, p, c, i, ti);
                break;
            case 3:
                menuAberturaCaixa(cx);
                break;
            case 4:
                menuFechamentoCaixa(cx, pg, *tpg, v->total);
                break;
            case 5:
                menuRelatorios(c, p, v, *tv, cat);
                break;
            case 6:
                printf("Encerrando o sistema...\n");
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (opcao != 6);
}

void menuCadastros(Usuario* u, Cliente* c, Produto* p, Categoria* cat) {
    int opcao;
    do {
        printf("\n========== MENU CADASTROS ==========\n");
        printf("1. Cadastrar Usuário\n");
        printf("2. Cadastrar Cliente\n");
        printf("3. Cadastrar Produto\n");
        printf("4. Cadastrar Categoria\n");
        printf("5. Voltar ao Menu Principal\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarUsuario(&u);
                break;
            case 2:
                cadastrarCliente(&c);
                break;
            case 3:
                cadastrarProduto(&p, cat);
                break;
            case 4:
                cadastrarCategoria(&cat);
                break;
            case 5:
                printf("Voltando ao Menu Principal...\n");
                break;
            default:
                printf("Opção inválida.\n");
        }

    } while (opcao != 5);
}

void menuVendas(Venda* v, int* tv, Produto* p, Cliente* c, ItemVenda* i, int* ti) {
    int opcao;
    do {
        printf("\n========== MENU VENDAS ==========\n");
        printf("1. Nova Venda\n");
        printf("2. Retirada de Caixa (Sangria)\n");
        printf("3. Pagamento\n");
        printf("4. Voltar ao Menu Principal\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                novaVenda(&v, tv, p, c, i, ti);
                break;
            case 2:
                listarVendas(v, *tv);
                break;
            case 3:
                printf("Voltando ao Menu Principal...\n");
                break;
            default:
                printf("Opção inválida.\n");
        }

    } while (opcao != 3);
}

void menuAberturaCaixa(Caixa* caixa) {
    abrirCaixa(caixa);
    printf("Caixa aberto com sucesso! Valor de abertura: %.2f\n", caixa->valor_abertura);
}

void menuFechamentoCaixa(Caixa* caixa, Pagamento* pagamentos, int totalPagamentos, float totalVendas) {
    float pagD = totalPorTipo(pagamentos, totalPagamentos, "d");
    float pagC = totalPorTipo(pagamentos, totalPagamentos, "c");
    float pagDC = totalPorTipo(pagamentos, totalPagamentos, "dc");

    fecharCaixa(caixa);
    mostrarResumoFechamento(*caixa, totalVendas, pagD, pagC, pagDC);
}

// 5.RELATÓRIOS
// 5.1 Listagem dos Clientes
// 5.1.1 Listagem de Clientes (ordenada em ordem alfabética por nome)
// 5.1.2 Listagem dos Clientes que Compraram (em um determinado período)

// 5.2 Listagem dos Produtos
// 5.2.1 Listagem de Produtos (ordenada em ordem alfabética por descrição)
// 5.2.2 Listagem de Produtos com Estoque zero ou Mínimo(ordenada em ordem alfabética por
// descrição)
// 5.2.3 Listagem dos Produtos mais Vendidos (em um determinado período)

// 5.3 Listagem das Vendas
// 5.3.1 Listagem das Vendas (em um determinado período)
// 5.3.2 Faturamento Consolidado – em um período
// Consolidados de valores recebido em dinheiro
// Consolidados de valores recebido em Cartão

// 5.4 Retornar ao Menu Principal
void menuRelatorios(Cliente* c, Produto* p, Venda* v, int totalVendas, Categoria* cat) {
    int opcao;
    do {
        printf("\n========== MENU RELATÓRIOS ==========\n");
        printf("1. Listar Clientes\n");
        printf("2. Listar Produtos\n");
        printf("3. Listar Vendas\n");
        printf("4. Voltar ao Menu Principal\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                menuListarClientes(c);
                break;
            case 2:
                menuListarProduto(p);
                break;
            case 3:
                listarVendas(v, totalVendas);
                break;
            case 4:
                printf("Voltando ao Menu Principal...\n");
                break;
            default:
                printf("Opção inválida.\n");
        }

    } while (opcao != 4);
}