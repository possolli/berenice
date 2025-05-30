#include "../include/utils.h"

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void pausar() {
    printf("Pressione ENTER para continuar...");
    limparBuffer();
}

int confirmar(const char* mensagem) {
    char resposta;
    printf("%s", mensagem);
    scanf(" %c", &resposta);
    limparBuffer();
    return (resposta == 's' || resposta == 'S');
}

// ✅ Implementação da função reutilizável
FILE* abrirOuCriarArquivoLeitura(const char* nomeArquivo) {
    FILE* f = fopen(nomeArquivo, "r");
    if (!f) {
        f = fopen(nomeArquivo, "w"); // cria o arquivo se não existir
        if (!f) return NULL;         // erro crítico ao tentar criar
        fclose(f);                   // fecha o novo arquivo vazio
        f = fopen(nomeArquivo, "r"); // tenta abrir novamente para leitura
        if (!f) return NULL;         // se ainda falhar, retorna erro
    }
    return f;
}

