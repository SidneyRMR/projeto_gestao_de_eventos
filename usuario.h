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

// TODO
int EditarNomeUsuario(int idUsuario);
int EditarDescricaoUsuario(int idUsuario);
int DesativarUsuario(int idUsuario);

void alterarStatusUsuario();

void criarUsuario();

void alterarStatusDoUsuario(int idUsuario);

int listarUsuarios();

int carregarUltimoUsuario();

void salvarUsuario(Usuario usuario);

Usuario buscarUsuarioPorId(int id);

char* obterNomeUsuario(const char *nomeArquivo, int idBusca);

#endif // USUARIO_H