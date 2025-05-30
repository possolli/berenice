#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/usuarios.h"

#define BUFFER_INICIAL 10

void cadastrarUsuario(Usuario** usuarios) {
    Usuario* novo = malloc(sizeof(Usuario));
    if (!novo) {
        printf("Erro ao alocar memória para novo usuário.\n");
        return;
    }

    printf("\n--- Cadastro de Usuário ---\n");

    printf("Nome do usuário: ");
    scanf(" %[^\n]", novo->nome);

    while (1) {
        printf("Login (8 a 12 caracteres): ");
        scanf("%12s", novo->login);
        int len = strlen(novo->login);
        if (len >= 8 && len <= 12) break;
        printf("Login inválido. Tente novamente.\n");
    }

    while (1) {
        printf("Senha (6 a 8 caracteres): ");
        scanf("%8s", novo->senha);
        int len = strlen(novo->senha);
        if (len >= 6 && len <= 8) break;
        printf("Senha inválida. Tente novamente.\n");
    }

    getchar(); // Limpa o buffer após a leitura da senha

    while (1) {
        printf("Tipo de usuário (1 - Administrador | 2 - Usuário): ");
        scanf("%d", &novo->tipo);
        if (novo->tipo == 1 || novo->tipo == 2) break;
        printf("Tipo inválido. Digite 1 para Administrador ou 2 para Usuário.\n");
    }

    getchar(); // Limpa o buffer após a leitura do tipo

    novo->prox = NULL;
    if (*usuarios == NULL) {
        *usuarios = novo;
    } else {
        Usuario* atual = *usuarios;
        while (atual->prox != NULL) {
            atual = atual->prox;
        }
        atual->prox = novo;
    }

    printf("Usuário cadastrado com sucesso.\n");
}

Usuario* pegarUsuario(Usuario* usuarios, char login[12]) {
    Usuario* atual = usuarios;
    while (atual != NULL) {
        if (strcmp(atual->login, login) == 0) {
            return atual;
        }
        atual = atual->prox;
    }
    return NULL;
}

void listarUsuarios(Usuario* usuarios) {
    printf("\n--- Lista de Usuários ---\n");
    Usuario* atual = usuarios;
    while (atual != NULL) {
        printf("Nome: %s | Login: %s | Tipo: %d\n", atual->nome, atual->login, atual->tipo);
        atual = atual->prox;
    }
}

int salvarUsuarios(const char* nomeArquivo, Usuario* usuarios) {
    FILE* f = fopen(nomeArquivo, "w");
    if (!f) return 0;

    Usuario* atual = usuarios;
    while (atual != NULL) {
        fprintf(f, "%s|%s|%s|%d\n",
                atual->nome,
                atual->login,
                atual->senha,
                atual->tipo);
        atual = atual->prox;
    }

    fclose(f);
    return 1;
}

void liberarUsuarios(Usuario* usuarios) {
    Usuario* atual;
    while (usuarios != NULL) {
        atual = usuarios;
        usuarios = usuarios->prox;
        free(atual);
    }
}