#ifndef CAIXA_H
#define CAIXA_H

// Representa abertura e fechamento de caixa
typedef struct {
    float valor_abertura;
    float valor_total;
    int aberto; // 1 = aberto, 0 = fechado
} Caixa;

void abrirCaixa(Caixa* caixa);
void fecharCaixa(Caixa* caixa);
void mostrarResumoFechamento(Caixa caixa, float totalVendas, float pagD, float pagC, float pagDC);

#endif
