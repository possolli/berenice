
#include "../include/pagamento.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void salvarPagamentos(const char* nomeArquivo, Pagamento* pagamentos, int total) {
    printf("Função salvarPagamentos chamada\n");
}

float totalPorTipo(Pagamento* pagamentos, int total, const char* tipo) {
    printf("Função totalPorTipo chamada para tipo: %s\n", tipo);
    return 0.0;
}
