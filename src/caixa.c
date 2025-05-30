
#include "../include/caixa.h"
#include <stdio.h>

void abrirCaixa(Caixa* caixa) {
    printf("Função abrirCaixa chamada\n");
    caixa->aberto = 1;
    caixa->valor_abertura = 100.0;
}

void fecharCaixa(Caixa* caixa) {
    printf("Função fecharCaixa chamada\n");
    caixa->aberto = 0;
}

void mostrarResumoFechamento(Caixa caixa, float totalVendas, float pagD, float pagC, float pagDC) {
    printf("Função mostrarResumoFechamento chamada\n");
}
