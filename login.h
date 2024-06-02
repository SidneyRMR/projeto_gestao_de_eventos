#ifndef PROJETO_GESTAO_DE_EVENTOS_LOGIN_H
#define PROJETO_GESTAO_DE_EVENTOS_LOGIN_H

/**
 * @brief Função principal para realizar o login.
 *
 * Esta função é responsável por coordenar o processo de login do usuário,
 * carregando os usuários do arquivo, gerenciando as tentativas de login
 * e exibindo mensagens de erro caso o login falhe.
 */
void login();


/**
 * @brief Realiza o processo de autenticação do usuário.
 *
 * @return Retorna 1 se o login for bem-sucedido, 0 caso contrário.
 *
 * Esta função solicita ao usuário suas credenciais de login (usuário e senha),
 * verifica se as credenciais fornecidas são válidas e, se sim, permite o acesso
 * ao sistema de gestão de eventos.
 */
int loginAux();


#endif //PROJETO_GESTAO_DE_EVENTOS_LOGIN_H
