#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/relatorios.h"
#include "../include/vendas.h"

Venda* pegarVendasPorPeriodo(Venda* vendas, const char* data_inicio, const char* data_fim) {
    Venda* resultado = NULL;
    Venda* ultimo = NULL;

    while (vendas != NULL) {
        if (strcmp(vendas->data, data_inicio) >= 0 && strcmp(vendas->data, data_fim) <= 0) {
            // Cria cópia da venda (sem copiar itens)
            Venda* nova = malloc(sizeof(Venda));
            if (!nova) continue;

            *nova = *vendas;
            nova->itens = NULL; // ou copie os itens, se necessário
            nova->prox = NULL;

            if (resultado == NULL) {
                resultado = nova;
                ultimo = nova;
            } else {
                ultimo->prox = nova;
                ultimo = nova;
            }
        }
        vendas = vendas->prox;
    }

    return resultado;
}
