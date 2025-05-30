#ifndef ITENS_VENDA_H
#define ITENS_VENDA_H

typedef struct {
    int venda_id;
    int produto_id;
    int quantidade;
    float preco;
    float total;
} ItemVenda;

void salvarItensVenda(const char* nomeArquivo, ItemVenda* itens, int totalItens);

#endif
