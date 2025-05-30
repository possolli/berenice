#ifndef PRODUTOS_H
#define PRODUTOS_H

#include "categorias.h"

typedef struct {
    int id;
    char descricao[50];
    int estoque;
    int estoque_minimo;
    char categoria[30];
    float preco_compra;
    float preco_venda;
} Produto;

void cadastrarProduto(Produto** produtos, int* totalProdutos, Categoria* categorias, int totalCategorias);
void listarProdutos(Produto* produtos, int totalProdutos);
void salvarProdutos(const char* nomeArquivo, Produto* produtos, int totalProdutos);

#endif
