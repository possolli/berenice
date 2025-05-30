#ifndef CATEGORIAS_H
#define CATEGORIAS_H

typedef struct {
    int id;
    char descricao[50];
} Categoria;

void cadastrarCategoria(Categoria** categorias, int* totalCategorias);
void listarCategorias(Categoria* categorias, int totalCategorias);
void salvarCategorias(const char* nomeArquivo, Categoria* categorias, int totalCategorias);

#endif
