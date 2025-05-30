#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>

void limparBuffer();
void pausar();
int confirmar(const char* mensagem);

// ✅ Nova função
FILE* abrirOuCriarArquivoLeitura(const char* nomeArquivo);
void* pegarItem(void* lista, int id);

#endif
