#include "../include/clientes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/utils.h"

int maior_id_cliente = 0; // Variável global para armazenar o maior ID de cliente

Cliente* pegarUltimoCliente(Cliente* lista) {
    if (!lista) return NULL;

    while (lista->prox) {
        lista = lista->prox;
    }
    return lista;
}

Cliente* pegarCliente(Cliente* lista, int id) {
    while (lista != NULL) {
        if (lista->id == id) {
            return lista;
        }
        lista = lista->prox;
    }
    return NULL;
}

void cadastrarCliente(Cliente** clientes) {
    printf("\n--- Cadastro de Cliente ---\n");

    Cliente* novo = malloc(sizeof(Cliente));
    if (!novo) {
        printf("Erro ao alocar memória.\n");
        return;
    }

    novo->id = 1;
    Cliente* ultimo = pegarUltimoCliente(*clientes);
    if (ultimo) {
        novo->id = maior_id_cliente + 1; // Incrementa o maior ID já existente
        ultimo->prox = novo;
    } else {
        *clientes = novo;
    }

    maior_id_cliente = novo->id; // Atualiza o maior ID global

    getchar(); // limpa buffer do scanf anterior

    printf("Nome completo: ");
    fgets(novo->nome, sizeof(novo->nome), stdin);
    novo->nome[strcspn(novo->nome, "\n")] = '\0';

    printf("Nome social: ");
    fgets(novo->nome_social, sizeof(novo->nome_social), stdin);
    novo->nome_social[strcspn(novo->nome_social, "\n")] = '\0';

    printf("CPF: ");
    fgets(novo->cpf, sizeof(novo->cpf), stdin);
    novo->cpf[strcspn(novo->cpf, "\n")] = '\0';

    printf("Endereço (Rua e Número): ");
    fgets(novo->endereco, sizeof(novo->endereco), stdin);
    novo->endereco[strcspn(novo->endereco, "\n")] = '\0';

    printf("Celular/WhatsApp: ");
    fgets(novo->telefone, sizeof(novo->telefone), stdin);
    novo->telefone[strcspn(novo->telefone, "\n")] = '\0';

    novo->prox = NULL;

    printf("Cliente cadastrado com sucesso! ID: %d\n", novo->id);
}

void menuListarClientes(Cliente* lista) {
    if (!lista) {
        printf("Nenhum cliente cadastrado.\n");
        return;
    }

    int opcao;
    do {
        printf("\n===== Menu Listar Clientes =====\n");
        printf("1. Listar todos os clientes\n");
        printf("2. Listar clientes (em ordem alfabética por nome)\n");
        printf("3. Listar clientes que compraram (em um período)\n");
        printf("4. Voltar ao menu principal\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // Limpa o buffer

        switch (opcao) {
            case 1:
                listarClientes(lista);
                break;
            case 2: {
                // Ordenar clientes por nome
                Cliente* ordenados = ordenarClientesPorNome(lista);
                listarClientes(ordenados);
                liberarClientes(ordenados); // Libera a memória da lista ordenada
                break;
            }
            case 3:
                printf("Funcionalidade de listar clientes que compraram ainda não implementada.\n");
                break;
            case 4:
                printf("Voltando ao menu principal...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 4);
}

void listarClientes(Cliente* lista) {
    if (!lista) {
        printf("Nenhum cliente cadastrado.\n");
        return;
    }

    printf("\n===== Lista de Clientes =====\n");
    Cliente* atual = lista;
    while (atual) {
        printf("ID: %d\n", atual->id);
        printf("Nome completo: %s\n", atual->nome);
        printf("Nome social: %s\n", atual->nome_social);
        printf("CPF: %s\n", atual->cpf);
        printf("Endereço: %s\n", atual->endereco);
        printf("Telefone: %s\n", atual->telefone);
        printf("-----------------------------\n");
        atual = atual->prox;
    }
}

Cliente* ordenarClientesPorNome(Cliente* lista) {
    if (!lista || !lista->prox) return lista; // Lista vazia ou com apenas um elemento

    // Cria um vetor para armazenar os clientes
    int count = 0;
    Cliente* atual = lista;
    while (atual) {
        count++;
        atual = atual->prox;
    }

    Cliente** vetor = malloc(sizeof(Cliente*) * count);
    if (!vetor) {
        printf("Erro ao alocar memória para ordenar clientes.\n");
        return lista;
    }

    atual = lista;
    for (int i = 0; i < count; i++) {
        vetor[i] = atual;
        atual = atual->prox;
    }

    // Ordena o vetor usando bubble sort
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (strcmp(vetor[j]->nome, vetor[j + 1]->nome) > 0) {
                Cliente* temp = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = temp;
            }
        }
    }

    // Reconstrói a lista ordenada
    for (int i = 0; i < count - 1; i++) {
        vetor[i]->prox = vetor[i + 1];
    }
    vetor[count - 1]->prox = NULL;

    Cliente* novaLista = vetor[0];
    free(vetor);

    return novaLista;
}


void salvarClientes(const char* nomeArquivo, Cliente* lista) {
    FILE* f = fopen(nomeArquivo, "w");
    if (!f) {
        printf("Erro ao salvar clientes. Verifique permissões ou caminho.\n");
        return;
    }

    Cliente* atual = lista;
    int count = 0;
    while (atual) {
        fprintf(f, "%d|%s|%s|%s|%s|%s\n",
                atual->id,
                atual->nome,
                atual->nome_social,
                atual->cpf,
                atual->endereco,
                atual->telefone);
        atual = atual->prox;
        count++;
    }

    fclose(f);
    printf("Clientes salvos com sucesso (%d registrados).\n", count);
}

void liberarClientes(Cliente* lista) {
    while (lista) {
        Cliente* temp = lista;
        lista = lista->prox;
        free(temp);
    }
}
