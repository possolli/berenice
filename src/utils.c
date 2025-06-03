#include "../include/utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

int validarData(const char* data) {
    if (strlen(data) != 10) return 0;
    if (data[4] != '-' || data[7] != '-') return 0;

    for (int i = 0; i < 10; i++) {
        if (i == 4 || i == 7) continue;
        if (!isdigit(data[i])) return 0;
    }

    return 1;
}

void solicitarPeriodo(Periodo* periodo) {
    while (1) {
        printf("Digite a data de início (YYYY-MM-DD): ");
        printf("Ex: 2025-01-01\n");
        scanf("%10s", periodo->inicio);

        if (!validarData(periodo->inicio)) {
            printf("Data de início inválida. Formato esperado: YYYY-MM-DD\n");
            continue;
        }

        break;
    }

    while (1) {
        printf("Digite a data de fim (YYYY-MM-DD): ");
        printf("Ex: 2025-01-31\n");
        scanf("%10s", periodo->fim);

        if (!validarData(periodo->fim)) {
            printf("Data de fim inválida. Formato esperado: YYYY-MM-DD\n");
            continue;
        }

        break;
    }
}
