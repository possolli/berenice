#include "../include/vendas.h"
#include "../include/utils.h"
#include "../include/relatorios.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Venda* pegarUltimaVenda(Venda* vendas) {
    if (vendas == NULL) {
        printf("pegarUltimaVenda recebeu NULL\n");
        return NULL;
    }

    Venda* atual = vendas;
    while (atual->prox != NULL) {
        atual = atual->prox;
    }
    return atual;
}

void adicionarProdutoNaVenda(Venda* v, Produto* produtos) {
    listarProdutos(produtos);
    printf("Digite o ID do produto para adicionar: ");
    int id_produto;
    scanf("%d", &id_produto);

    Produto* produto = pegarProduto(produtos, id_produto);
    if (!produto) {
        printf("Produto não encontrado.\n");
        return;
    }

    ItemVenda item;
    item.venda_id = v->id;
    item.produto_id = produto->id;
    item.quantidade = 0;
    item.preco = produto->preco_venda;
    item.total = 0.0f;
    item.prox = NULL;

    while (1) {
        printf("Digite a quantidade do produto %s (estoque: %d): ", produto->descricao, produto->estoque);
        scanf("%d", &item.quantidade);

        if (item.quantidade <= 0) {
            printf("Item cancelado.\n");
            return;
        }

        if (item.quantidade > produto->estoque) {
            printf("Estoque insuficiente. Tente novamente.\n");
        } else {
            item.total = item.quantidade * item.preco;

            ItemVenda* novo = malloc(sizeof(ItemVenda));
            if (!novo) {
                printf("Erro ao alocar memória.\n");
                return;
            }
            *novo = item;

            if (v->itens == NULL) {
                v->itens = novo;
            } else {
                ItemVenda* atual = v->itens;
                while (atual->prox != NULL) {
                    atual = atual->prox;
                }
                atual->prox = novo;
            }

            v->quantidade += item.quantidade;
            v->total += item.total;
            produto->estoque -= item.quantidade;

            printf("Item adicionado: %s | Quantidade: %d | Total: R$ %.2f\n",
                   produto->descricao, item.quantidade, item.total);
            return;
        }
    }
}

int confirmarVenda(Venda* v, Cliente* cliente, Produto* produtos) {
    if (v->quantidade == 0) {
        printf("Nenhum item na venda. Adicione ao menos um item antes de confirmar.\n");
        return 0;
    }

    printf("Digite a data da venda (YYYY-MM-DD): \n");
    printf("Ex: 2025-01-31 \n");
    scanf("%s", v->data);

    strcpy(v->status, "NP");
    strcpy(v->tipo_pagamento, "-");

    printf("\n--- Venda Confirmada ---\n");
    printf("ID da Venda: %d\n", v->id);
    printf("Cliente: %s\n", cliente->nome);
    printf("Quantidade de Itens: %d\n", v->quantidade);
    printf("Total: R$ %.2f\n", v->total);
    printf("Desconto: R$ %.2f\n", v->desconto);
    printf("Tipo de Pagamento: %s\n", v->tipo_pagamento);
    printf("Status: %s\n", v->status);
    printf("Data: %s\n", v->data);
    printf("Itens da Venda:\n");

    ItemVenda* atual = v->itens;
    while (atual != NULL) {
        Produto* produto = pegarProduto(produtos, atual->produto_id);
        if (produto) {
            printf("Produto ID: %d | Descrição: %s | Quantidade: %d | Preço Unitário: R$ %.2f | Total: R$ %.2f\n",
                   produto->id, produto->descricao, atual->quantidade, atual->preco, atual->total);
        }
        atual = atual->prox;
    }

    printf("-------------------------\n");
    printf("Venda confirmada com sucesso!\n");
    printf("Retornando ao menu de vendas...\n");

    return 1;
}

void cancelarVenda(Venda* v, Produto* produtos, Venda** vendas) {
    printf("Cancelando venda...\n");

    // Devolve estoque
    ItemVenda* atual = v->itens;
    while (atual != NULL) {
        Produto* produto = pegarProduto(produtos, atual->produto_id);
        if (produto) {
            produto->estoque += atual->quantidade;
        }

        ItemVenda* temp = atual;
        atual = atual->prox;
        free(temp);
    }

    // Remover v da lista ligada de vendas
    Venda* atualVenda = *vendas;
    Venda* anterior = NULL;

    while (atualVenda != NULL) {
        if (atualVenda == v) {
            if (anterior == NULL) {
                *vendas = atualVenda->prox;
            } else {
                anterior->prox = atualVenda->prox;
            }
            free(atualVenda);
            printf("Venda cancelada com sucesso.\n");
            return;
        }

        anterior = atualVenda;
        atualVenda = atualVenda->prox;
    }
}

void printarVendasExistentesTeste(Venda** vendas) {
    if (*vendas == NULL) {
        printf("Nenhuma venda cadastrada.\n");
        return;
    }

    printf("\n--- Vendas Existentes ---\n");
    Venda* atual = *vendas;
    while (atual != NULL) {
        printf("ID: %d | Cliente ID: %d | Quantidade: %d | Total: R$ %.2f | Desconto: R$ %.2f | Tipo de Pagamento: %s | Status: %s | Data: %s\n",
               atual->id, atual->cliente_id, atual->quantidade, atual->total, atual->desconto,
               atual->tipo_pagamento, atual->status, atual->data);
        atual = atual->prox;
    }
}

void novaVenda(Venda** vendas, Produto* produtos, Cliente* clientes) {
    printarVendasExistentesTeste(vendas);
    if (!clientes) {
        printf("Nenhum cliente cadastrado. Cadastre um cliente antes de realizar uma venda.\n");
        return;
    }

    if (produtos == NULL) {
        printf("Nenhum produto cadastrado. Cadastre um produto antes de realizar uma venda.\n");
        return;
    }

    printf("\n--- Nova Venda ---\n");
    // Aloca nova venda
    Venda* nova = malloc(sizeof(Venda));
    if (!nova) {
        printf("Erro ao alocar memória para nova venda.\n");
        return;
    }

    nova->prox = NULL;
    nova->itens = NULL;
    nova->quantidade = 0;
    nova->total = 0.0f;
    nova->desconto = 0.0f;
    nova->tipo_pagamento[0] = '\0';
    nova->status[0] = '\0';
    nova->data[0] = '\0';

    if (*vendas == NULL) {
        nova->id = 1;
        *vendas = nova; // Primeira venda da lista
    } else {
        Venda* ultimaVenda = pegarUltimaVenda(*vendas);
        nova->id = ultimaVenda->id + 1;
        ultimaVenda->prox = nova;
        // NÃO atualiza *vendas aqui!
    }

    Cliente* cliente = NULL;
    Venda* v = nova;

    while (1) {
        printf("Digite o ID do cliente ou 0 para sair: \n");
        scanf("%d", &v->cliente_id);

        if (v->cliente_id == 0) {
            printf("Retornando ao menu de vendas...\n");
            return;
        }

        cliente = pegarCliente(clientes, v->cliente_id);
        if (!cliente) {
            printf("Cliente não encontrado. Tente novamente.\n");
            continue;
        } else {
            printf("NOVA VENDA PARA: %s\n", cliente->nome);
        }

        v->quantidade = 0; // Inicializa a quantidade de produtos na venda
        v->total = 0.0f; // Inicializa o total da venda
        v->desconto = 0.0f; // Inicializa o desconto da venda
        v->tipo_pagamento[0] = '\0'; // Inicializa o tipo de pagamento
        v->status[0] = '\0'; // Inicializa o status da venda
        v->itens = NULL; // Inicializa a lista de itens da venda

        while (1) {
            printf("\n--- MENU DA VENDA ---\n");
            printf("1 - Adicionar produto\n");
            printf("2 - Confirmar venda\n");
            printf("3 - Cancelar venda\n");
            printf("Escolha uma opção: ");

            int opcao;
            scanf("%d", &opcao);
            getchar(); // limpa buffer

            switch (opcao) {
                case 1:
                    adicionarProdutoNaVenda(v, produtos);
                    break;

                case 2:
                    if (confirmarVenda(v, cliente, produtos)) return;
                    break;

                case 3:
                    cancelarVenda(v, produtos, vendas);
                    return;

                default:
                    printf("Opção inválida. Tente novamente.\n");
            }
        }
    }
}

void listarVendas(Venda* vendas) {
    if (vendas == NULL) {
        printf("Nenhuma venda cadastrada.\n");
        return;
    }

    printf("\n===== Lista de Vendas =====\n");
    Venda* atual = vendas;
    while (atual != NULL) {
        printf("ID: %d | Cliente ID: %d | Quantidade: %d | Total: R$ %.2f | Desconto: R$ %.2f | Tipo de Pagamento: %s | Status: %s | Data: %s\n",
               atual->id, atual->cliente_id, atual->quantidade, atual->total, atual->desconto,
               atual->tipo_pagamento, atual->status, atual->data);
        printf("-------------------------\n");
        atual = atual->prox;
    }
}

void salvarVendas(const char* nomeArquivo, Venda* vendas) {
    FILE* f = fopen(nomeArquivo, "w");

    if (!f) {
        printf("Erro ao abrir os arquivos para salvar vendas.\n");
        fclose(f);
        return;
    }

    while (vendas) {
        fprintf(f, "%d|%d|%d|%.2f|%.2f|%s|%s|%s\n",
                vendas->id,
                vendas->cliente_id,
                vendas->quantidade,
                vendas->total,
                vendas->desconto,
                vendas->tipo_pagamento,
                vendas->status,
                vendas->data);

        salvarItensVenda("data/itens_venda.txt", vendas->id, vendas->itens);
        vendas = vendas->prox;
    }

    fclose(f);
}

void liberarVendas(Venda* vendas) {
    Venda* atual = vendas;
    while (atual != NULL) {
        Venda* temp = atual;
        atual = atual->prox;

        // Liberar itens da venda
        ItemVenda* itemAtual = temp->itens;
        while (itemAtual != NULL) {
            ItemVenda* itemTemp = itemAtual;
            itemAtual = itemAtual->prox;
            free(itemTemp);
        }

        free(temp);
    }
}

void menuListarVendas(Venda* vendas) {
    if (!vendas) {
        printf("Nenhuma venda cadastrada.\n");
        return;
    }

    int opcao;
    do {
        printf("\n===== Menu Listar Vendas =====\n");
        printf("1. Listagem das Vendas\n");
        printf("2. Listagem das Vendas (em um determinado período)\n");
        printf("3. Faturamento Consolidado\n");
        printf("4. Voltar ao menu principal\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();

        Periodo periodo;

        switch (opcao) {
            case 1:
                listarVendas(vendas);
                break;
            case 2:
                solicitarPeriodo(&periodo);
                Venda* resultado = pegarVendasPorPeriodo(vendas, periodo.inicio, periodo.fim);
                listarVendas(resultado);
                break;
            case 3:
                solicitarPeriodo(&periodo);
                printf("Faturamento Consolidado ainda não implementada.\n");
                break;
            case 4:
                printf("Voltando ao menu principal...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 4);
}