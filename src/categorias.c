#include "../include/categorias.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Categoria* pegarUltimaCategoria(Categoria* lista) {
    if (!lista) return NULL;

    while (lista->prox != NULL)
        lista = lista->prox;

    return lista;
}

Categoria* pegarCategoria(Categoria* lista, int id) {
    while (lista != NULL) {
        if (lista->id == id) return lista;
        lista = lista->prox;
    }
    return NULL;
}

void cadastrarCategoria(Categoria** categorias) {
    Categoria* nova = malloc(sizeof(Categoria));
    if (!nova) {
        printf("Erro ao alocar memória para a nova categoria.\n");
        return;
    }

    nova->prox = NULL;

    Categoria* ultima = pegarUltimaCategoria(*categorias);
    nova->id = (ultima == NULL) ? 1 : ultima->id + 1;

    getchar(); // limpar buffer

    printf("Descrição: ");
    fgets(nova->descricao, sizeof(nova->descricao), stdin);
    nova->descricao[strcspn(nova->descricao, "\n")] = 0;

    if (*categorias == NULL) {
        *categorias = nova;
    } else {
        ultima->prox = nova;
    }

    printf("Categoria cadastrada com sucesso! ID: %d\n", nova->id);
}

void listarCategorias(Categoria* categorias) {
    if (!categorias) {
        printf("Nenhuma categoria cadastrada.\n");
        return;
    }

    printf("\n===== Lista de Categorias =====\n");
    Categoria* atual = categorias;
    while (atual) {
        printf("ID: %d\n", atual->id);
        printf("Descrição: %s\n", atual->descricao);
        printf("-----------------------------\n");
        atual = atual->prox;
    }
}

void salvarCategorias(const char* nomeArquivo, Categoria* categorias) {
    FILE* f = fopen(nomeArquivo, "w");
    if (!f) {
        printf("Erro ao salvar categorias no arquivo '%s'. Verifique permissões.\n", nomeArquivo);
        return;
    }

    Categoria* atual = categorias;
    while (atual) {
        fprintf(f, "%d|%s\n", atual->id, atual->descricao);
        atual = atual->prox;
    }

    fclose(f);
    printf("Categorias salvas com sucesso.\n");
}

void liberarCategorias(Categoria* lista) {
    Categoria* atual;
    while (lista != NULL) {
        atual = lista;
        lista = lista->prox;
        free(atual);
    }
}