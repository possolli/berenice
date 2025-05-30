#ifndef CLIENTES_H
#define CLIENTES_H

typedef struct Cliente {
    int id;
    char nome[21];
    char nome_social[21];
    char cpf[21];
    char endereco[21];
    char telefone[21];
    struct Cliente* prox;
} Cliente;

extern int maior_id_cliente;

void cadastrarCliente(Cliente** lista);
void listarClientes(Cliente* lista);
void salvarClientes(const char* nomeArquivo, Cliente* lista);
Cliente* carregarClientes(const char* nomeArquivo);
void liberarClientes(Cliente* lista);
Cliente* pegarUltimoCliente(Cliente* lista);

#endif