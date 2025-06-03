#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>

typedef struct {
    char inicio[11]; // Formato "YYYY-MM-DD"
    char fim[11];   // Formato "YYYY-MM-DD"
} Periodo;

FILE* abrirOuCriarArquivoLeitura(const char* nomeArquivo);

void solicitarPeriodo(Periodo* periodo);
int validarData(const char* data);

int confirmar(const char* mensagem);

void limparBuffer();
void pausar();

#endif
