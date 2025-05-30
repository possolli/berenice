#include "../include/login.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Usuario* login(Usuario* usuarios) {
    char login[13], senha[9];
    int tentativas = 0;
    Usuario* atual = usuarios;

    while (1) {
        printf("Digite seu login: ");
        scanf("%12s", login);

        atual = pegarUsuario(usuarios, login);

        if (atual) break;
        printf("Login de usuário não encontrado. Tente novamente.\n");
    }

    while (tentativas < 3) {
        printf("Digite sua senha: ");
        scanf("%8s", senha);

        if (strcmp(atual->senha, senha) == 0) {
            printf("Login realizado com sucesso!\n");
            return atual;
        } else {
            tentativas++;
            printf("Senha incorreta. Tentativa %d de 3.\n", tentativas);
        }
    }

    printf("Número máximo de tentativas excedido. Encerrando o programa.\n");
    return NULL;
}
