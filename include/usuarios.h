#ifndef USUARIOS_H
#define USUARIOS_H

typedef struct Usuario {
    char nome[50];    // nome do usuário, até 49 caracteres + null terminator
    char login[13];   // até 12 caracteres + null terminator
    char senha[9];    // até 8 caracteres + null terminator
    int tipo;         // 1 = admin, 2 = usuário
    struct Usuario* prox; // ponteiro para o próximo usuário na lista
} Usuario;

void cadastrarUsuario(Usuario** usuarios);
void listarUsuarios(Usuario* usuarios);
int salvarUsuarios(const char* nomeArquivo, Usuario* usuarios);
void liberarUsuarios(Usuario* usuarios);
Usuario* pegarUsuario(Usuario* usuarios, char login[12]);

#endif