#ifndef USUARIO_H
#define USUARIO_H


typedef struct Usuario {
    int id;
    char nome[51];
    char login[21];
    char senha[11];
    char tipo[15];
    int status;
    int id_evento;
} Usuario;

void criarUsuario();

int listarUsuarios();

int carregarUltimoUsuario();

void salvarUsuario(Usuario usuario);

#endif // USUARIO_H