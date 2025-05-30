#include "../include/login.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

void lerSenhaOculta(char *senha, int max) {
    struct termios oldt, newt;

    // Salva configuração atual do terminal
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    // Desativa o echo (para esconder os caracteres digitados)
    newt.c_lflag &= ~(ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    // Lê a senha
    fgets(senha, max, stdin);
    senha[strcspn(senha, "\n")] = '\0'; // remove o \n

    // Restaura as configurações
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    printf("\n");
}

// Funcao de Login e autenticação
Usuario* login(Usuario* usuarios, int totalUsuarios) {
    char login[13], senha[9];
    int encontrado = 0, tentativas = 0;

    Usuario* usuario_logado = NULL;

    while (!encontrado) {
        printf("Digite seu login: ");
        scanf("%12s", login);
        getchar();

        for (int i = 0; i < totalUsuarios; i++) {
            if (strcmp(usuarios[i].login, login) == 0) {
                usuario_logado = (Usuario*)malloc(sizeof(Usuario));
                if (usuario_logado == NULL) {
                    printf("Erro ao alocar memória para o usuário logado.\n");
                    return NULL;
                }
                *usuario_logado = usuarios[i];
                encontrado = 1;
                break;
            }
        }

        if (!encontrado) {
            printf("Login de usuário não encontrado. Tente novamente.\n");
        }
    }

    while (tentativas < 3) {
        printf("Digite sua senha: ");
        lerSenhaOculta(senha, sizeof(senha));

        if (strcmp(usuario_logado->senha, senha) == 0) {
            printf("Login realizado com sucesso!\n");
            return usuario_logado;
        } else {
            tentativas++;
            printf("Senha incorreta. Tentativa %d de 3.\n", tentativas);
        }
    }

    printf("Número máximo de tentativas excedido. Encerrando o programa.\n");
    free(usuario_logado);
    return NULL;
}
