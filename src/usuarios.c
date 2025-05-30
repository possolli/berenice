#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/usuarios.h"

#define BUFFER_INICIAL 10

void cadastrarUsuario(Usuario** usuarios, int* total) {
    Usuario novo;
    printf("\n--- Cadastro de Usuário ---\n");

    printf("Nome do usuário: ");
    scanf(" %[^\n]", novo.nome); // Lê até a nova linha para permitir nomes com espaços

    while (1) {
        printf("Login (8 a 12 caracteres): ");
        fscanf(stdin, "%12s", novo.login);
        int len = strlen(novo.login);
        if (len >= 8 && len <= 12) break;
        printf("Login inválido. Tente novamente.\n");
    }
    getchar(); // limpa o \n que ficou no buffer

    while (1) {
        printf("Senha (6 a 8 caracteres): ");
        fscanf(stdin, "%8s", novo.senha);
        int len = strlen(novo.senha);
        if (len >= 6 && len <= 8) break;
        printf("Senha inválida. Tente novamente.\n");
    }
    getchar(); // limpa o \n que ficou no buffer

    while (1) {
        printf("Tipo de usuário (1 - Administrador | 2 - Usuário): ");
        fscanf(stdin, "%d", &novo.tipo);
        if (novo.tipo == 1 || novo.tipo == 2) break;
        printf("Tipo inválido. Digite 1 para Administrador ou 2 para Usuário.\n");
    }

    Usuario* temp = realloc(*usuarios, sizeof(Usuario) * (*total + 1));
    if (!temp) {
        printf("Erro ao alocar memória para novo usuário.\n");
        return;
    }

    *usuarios = temp;
    (*usuarios)[*total] = novo;
    (*total)++;
    printf("Usuário cadastrado com sucesso.\n");
}

void listarUsuarios(Usuario* usuarios, int total) {
    printf("\n--- Lista de Usuários ---\n");
    for (int i = 0; i < total; i++) {
        printf("Nome: %s | Login: %s | Tipo: %d\n", usuarios[i].nome, usuarios[i].login, usuarios[i].tipo);
    }
}

int salvarUsuarios(const char* nomeArquivo, Usuario* usuarios, int total) {
    FILE* f = fopen(nomeArquivo, "w");
    if (!f) return 0;

    for (int i = 0; i < total; i++) {
        fprintf(f, "%s|%s|%s|%d\n", usuarios[i].nome,
                usuarios[i].login,
                usuarios[i].senha,
                usuarios[i].tipo);
    }

    fclose(f);
    return 1;
}

Usuario* carregarUsuarios(const char* nomeArquivo, int* total) {
    FILE* f = fopen(nomeArquivo, "r");
    if (!f) {
        f = fopen(nomeArquivo, "w");
        if (!f) return NULL;
        fclose(f);
        f = fopen(nomeArquivo, "r");
        if (!f) return NULL;
    }

    int capacidade = BUFFER_INICIAL;
    Usuario* lista = malloc(sizeof(Usuario) * capacidade);
    *total = 0;

    while (fscanf(f, "%49[^|]|%12[^|]|%8[^|]|%d\n",
        lista[*total].nome,
        lista[*total].login,
        lista[*total].senha,
        &lista[*total].tipo) == 4) {

        (*total)++;
        if (*total >= capacidade) {
            capacidade *= 2;
            lista = realloc(lista, sizeof(Usuario) * capacidade);
        }
    }

    fclose(f);
    return lista;
}