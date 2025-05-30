#include "../include/menus.h"
#include <stdio.h>

#include "../include/usuarios.h"

void menuPrincipal(Usuario* u, int* tu, Cliente* c, int* tc, Produto* p, int* tp, Categoria* cat, int* totalCategorias,
                   Venda* v, int* tv, ItemVenda* i, int* ti, Pagamento* pg, int* tpg, Caixa* cx) {
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
                menuCadastros(u, tu, c, tc, p, tp, cat, totalCategorias);
                break;
            case 2:
                menuVendas(v, tv, p, tp, c, *tc, i, ti);
                break;
            case 3:
                menuAberturaCaixa(cx);
                break;
            case 4:
                menuFechamentoCaixa(cx, pg, *tpg, v->total);
                break;
            case 5:
                menuRelatorios(c, *tc, p, *tp, v, *tv, cat, *totalCategorias);
                break;
            case 7:
                printf("Encerrando o sistema...\n");
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (opcao != 7);
}

void menuCadastros(Usuario* u, int* tu, Cliente* c, int* tc, Produto* p, int* tp, Categoria* cat, int* totalCategorias) {
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
                cadastrarUsuario(&u, tu);
                break;
            case 2:
                cadastrarCliente(&c);
                break;
            case 3:
                cadastrarProduto(&p, tp, cat, *totalCategorias);
                break;
            case 4:
                cadastrarCategoria(&cat, totalCategorias);
                break;
            case 5:
                printf("Voltando ao Menu Principal...\n");
                break;
            default:
                printf("Opção inválida.\n");
        }

    } while (opcao != 5);
}

void menuVendas(Venda* v, int* tv, Produto* p, int* tp, Cliente* c, int totalClientes, ItemVenda* i, int* ti) {
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
                novaVenda(&v, tv, p, tp, c, totalClientes, i, ti);
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

void menuRelatorios(Cliente* c, int totalClientes, Produto* p, int totalProdutos, Venda* v, int totalVendas, Categoria* cat, int totalCategorias) {
    int opcao;
    do {
        printf("\n========== MENU RELATÓRIOS ==========\n");
        printf("1. Listar Clientes\n");
        printf("2. Listar Produtos\n");
        printf("3. Listar Vendas\n");
        printf("4. Listar Categorias\n");
        printf("5. Voltar ao Menu Principal\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                listarClientes(c);
                break;
            case 2:
                listarProdutos(p, totalProdutos);
                break;
            case 3:
                listarVendas(v, totalVendas);
                break;
            case 4:
                listarCategorias(cat, totalCategorias);
                break;
            case 5:
                printf("Voltando ao Menu Principal...\n");
                break;
            default:
                printf("Opção inválida.\n");
        }

    } while (opcao != 5);
}