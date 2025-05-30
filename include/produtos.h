#ifndef PRODUTOS_H
#define PRODUTOS_H

#include "categorias.h"

typedef struct Produto {
    int id;
    char descricao[50];
    int estoque;
    int estoque_minimo;
    char categoria[30];
    float preco_compra;
    float preco_venda;
    struct Produto *prox;
} Produto;

void menuListarProduto(Produto* produtos);
void cadastrarProduto(Produto** produtos, Categoria* categorias);
void listarProdutos(Produto* produtos);
void salvarProdutos(const char* nomeArquivo, Produto* produtos);
void listarProdutosEstoqueZeroOuMinimo(Produto* produtos);
void exibirProduto(Produto* p);
Produto* pegarProduto(Produto* lista, int id);
void liberarProdutos(Produto* lista);

#endif
