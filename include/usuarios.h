#ifndef USUARIOS_H
#define USUARIOS_H

typedef struct {
    char nome[50];    // nome do usuário, até 49 caracteres + null terminator
    char login[13];   // até 12 caracteres + null terminator
    char senha[9];    // até 8 caracteres + null terminator
    int tipo;         // 1 = admin, 2 = usuário
} Usuario;

void cadastrarUsuario(Usuario** usuarios, int* total);
void listarUsuarios(Usuario* usuarios, int total);
int salvarUsuarios(const char* nomeArquivo, Usuario* usuarios, int total);
Usuario* carregarUsuarios(const char* nomeArquivo, int* total);

#endif