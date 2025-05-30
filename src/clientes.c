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
