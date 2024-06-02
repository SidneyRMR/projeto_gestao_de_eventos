/**
 * @brief Direciona o usuário para o menu adequado com base no tipo de usuário.
 *
 * Esta função verifica o tipo de usuário (administrador ou não) e redireciona
 * para o menu apropriado (menu administrativo ou menu de vendas).
 * Dependendo do tipo de usuário, diferentes funcionalidades serão acessíveis.
 */
int escolherMenu();


/**
 * @brief Exibe o menu administrativo e permite ao administrador acessar várias funcionalidades do sistema.
 *
 * Este menu permite que o administrador realize diversas operações administrativas,
 * como visualizar, criar e editar eventos, usuários, produtos e gerar relatórios de vendas.
 * O administrador pode escolher entre diferentes opções e navegar pelo sistema conforme necessário.
 */
int menuAdministrador();

/**
 * @brief Exibe o menu de vendas para usuários não administradores.
 *
 * Este menu permite aos usuários não administradores realizar operações relacionadas à venda de produtos,
 * como listar produtos disponíveis, adicionar produtos ao carrinho, finalizar vendas e gerar relatórios.
 */
void menuVenda();


/**
 * @brief Exibe o menu de edição de eventos e permite ao usuário realizar operações de edição.
 *
 * Este menu permite ao usuário editar os detalhes de um evento específico,
 * como nome, descrição e status de ativação.
 * O usuário pode escolher entre diferentes opções e realizar as edições necessárias.
 */
int menuEditarEvento();

/**
 * @brief Exibe o menu de edição de usuários e permite ao usuário realizar operações de edição.
 *
 * Este menu permite ao usuário editar os detalhes de um usuário específico,
 * como nome, login, senha, evento associado e status de ativação.
 * O usuário pode escolher entre diferentes opções e realizar as edições necessárias.
 */
int menuEditarUsuario();


/**
 * @brief Exibe o menu de edição de produtos e permite ao usuário realizar operações de edição.
 *
 * Este menu permite ao usuário editar os detalhes de um produto específico,
 * como nome, preço, estoque, evento associado e status de ativação.
 * O usuário pode escolher entre diferentes opções e realizar as edições necessárias.
 */
int menuEditarProduto();

/**
 * @brief Obtém a data atual do sistema.
 *
 * @param dataAtual Uma string onde a data atual será armazenada.
 *
 * Esta função obtém a data atual do sistema e a formata como uma string no formato "DD/MM/AAAA".
 */
void obterDataAtual(char *dataAtual);

/**
 * @brief Obtém o nome de um evento com base no seu ID.
 *
 * @param nomeArquivo O nome do arquivo que contém os eventos.
 * @param idEventoBusca O ID do evento que se deseja obter o nome.
 * @return O nome do evento correspondente ao ID fornecido.
 *
 * Esta função busca o nome de um evento específico com base no seu ID,
 * lendo o arquivo que contém os eventos e retornando o nome correspondente.
 */
char* obterNomeEvento(const char *nomeArquivo, int idEventoBusca);
int listarProdutosVenda();
int verificarLoginExistente(const char *login);