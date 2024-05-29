#ifndef USUARIO_H
#define USUARIO_H

//todo erro do atualizar usuario pode
typedef struct {
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
void atualizarUsuario(Usuario usuario);
char* obterNomeUsuario(const char *nomeArquivo, int idBusca);
Usuario buscarUsuarioPorId(int id);

#endif // USUARIO_H