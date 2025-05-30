#ifndef PAGAMENTO_H
#define PAGAMENTO_H

typedef struct {
    int venda_id;
    float valor_pago;
    char tipo[3]; // "d", "c", "dc"
} Pagamento;

Pagamento* carregarPagamentos(const char* nomeArquivo, int* totalPagamentos);
void registrarPagamento(Pagamento** pagamentos, int* totalPagamentos, int venda_id, float valor, const char* tipo);
void salvarPagamentos(const char* nomeArquivo, Pagamento* pagamentos, int totalPagamentos);
float totalPorTipo(Pagamento* pagamentos, int total, const char* tipo);

#endif
