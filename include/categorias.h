#ifndef CATEGORIAS_H
#define CATEGORIAS_H

typedef struct Categoria {
    int id;
    char descricao[50];
    struct Categoria *prox;
} Categoria;

void cadastrarCategoria(Categoria** categorias);
void listarCategorias(Categoria* categorias);
void salvarCategorias(const char* nomeArquivo, Categoria* categorias);
Categoria* pegarUltimaCategoria(Categoria* lista);
Categoria* pegarCategoria(Categoria* lista, int id);
void liberarCategorias(Categoria* lista);

#endif
