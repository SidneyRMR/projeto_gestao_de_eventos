#ifndef USUARIO_H
#define USUARIO_H

// Define uma estrutura chamada Usuario para armazenar informações sobre um usuário
typedef struct {
    int id;               // Identificador único do usuário (por exemplo, um número de ID)
    char nome[51];        // Nome do usuário, limitado a 50 caracteres (o último byte é para o caractere nulo)
    char login[21];       // Nome de login do usuário, limitado a 20 caracteres (o último byte é para o caractere nulo)
    char senha[11];       // Senha do usuário, limitada a 10 caracteres (o último byte é para o caractere nulo)
    char tipo[15];        // Tipo de usuário (por exemplo, admin, usuário comum), limitado a 14 caracteres (o último byte é para o caractere nulo)
    int status;           // Status do usuário (por exemplo, Ativo, Inativo)
    int id_evento;        // Identificador do evento associado ao usuário (por exemplo, ID do evento em que o usuário está participando)
} Usuario;


/**
 * Função para criar um novo usuário.
 * Solicita informações como nome, login, senha e evento associado.
 * Realiza validação de dados e solicita confirmação antes de salvar.
 */
void criarUsuario();

/**
 * Função para listar todos os usuários cadastrados.
 * Retorna 0 se a listagem for bem-sucedida.
 */
int listarUsuarios();

/**
 * Função para carregar o ID do último usuário cadastrado.
 * Retorna o ID do último usuário + 1.
 */
int carregarUltimoUsuario();

/**
 * Função para salvar um novo usuário no arquivo de usuários.
 * Recebe como parâmetro o usuário a ser salvo.
 */
void salvarUsuario(Usuario usuario);

/**
 * Função para obter o nome de um usuário a partir do seu ID.
 * Recebe como parâmetros o nome do arquivo de usuários e o ID do usuário.
 * Retorna o nome do usuário ou NULL em caso de erro.
 * O chamador é responsável por liberar a memória alocada para o nome do usuário.
 */
char* obterNomeUsuario(const char *nomeArquivo, int idBusca);

/**
 * Função para buscar um usuário pelo seu ID.
 * Recebe como parâmetro o ID do usuário a ser buscado.
 * Retorna o usuário encontrado ou um usuário vazio se não encontrado.
 */
Usuario buscarUsuarioPorId(int id);

/**
 * Função para atualizar as informações de um usuário no arquivo de usuários.
 * Recebe como parâmetro o usuário atualizado.
 */
void atualizarUsuario(Usuario usuario);

#endif // USUARIO_H