
#include "../include/categorias.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void cadastrarCategoria(Categoria** categorias, int* total) {
    printf("\n--- Cadastro de Categoria ---\n");

    // Realoca espaço para nova categoria
    Categoria* nova = realloc(*categorias, sizeof(Categoria) * (*total + 1));
    if (!nova) {
        printf("Erro ao alocar memória para a categoria.\n");
        return;
    }
    *categorias = nova;

    Categoria* c = &(*categorias)[*total];

    // ID sequencial
    c->id = (*total == 0) ? 1 : (*categorias)[*total - 1].id + 1;

    getchar(); // limpa buffer do teclado

    printf("Descrição: ");
    fgets(c->descricao, sizeof(c->descricao), stdin);
    c->descricao[strcspn(c->descricao, "\n")] = 0;

    (*total)++;
    printf("Categoria cadastrada com sucesso! ID: %d\n", c->id);
}

void listarCategorias(Categoria* categorias, int total) {
    if (total == 0) {
        printf("Nenhuma categoria cadastrada.\n");
        return;
    }

    printf("\n===== Lista de Categorias =====\n");
    for (int i = 0; i < total; i++) {
        printf("ID: %d\n", categorias[i].id);
        printf("Descrição: %s\n", categorias[i].descricao);
        printf("-----------------------------\n");
    }
}

void salvarCategorias(const char* nomeArquivo, Categoria* categorias, int total) {
    FILE* f = fopen(nomeArquivo, "w");
    if (!f) {
        printf("Erro ao salvar categorias no arquivo '%s'. Verifique se a pasta existe e se há permissão.\n", nomeArquivo);
        return;
    }

    for (int i = 0; i < total; i++) {
        fprintf(f, "%d|%s\n",
                categorias[i].id,
                categorias[i].descricao);
    }

    fclose(f);
    printf("Categorias salvas com sucesso (%d registradas).\n", total);
}
