#ifndef EVENTO_H
#define EVENTO_H

// Define uma estrutura chamada Evento para armazenar informações sobre um evento
typedef struct {
    int id;               // Identificador único do evento (por exemplo, um número de ID)
    char evento[21];      // Nome do evento, limitado a 20 caracteres (o último byte é para o caractere nulo)
    char descricao[51];   // Descrição do evento, limitado a 50 caracteres (o último byte é para o caractere nulo)
    char data[11];        // Data do evento no formato "dd/mm/aaaa" (10 caracteres mais um byte para o caractere nulo)
    int status;           // Status do evento (por exemplo, 1 - Ativo, 0 - Inativo.)
} Evento;

/**
 * @brief Cria um novo evento.
 *
 * Esta função permite ao usuário criar um novo evento, fornecendo informações
 * como nome, descrição, data e status do evento.
 */
void criarEvento();


/**
 * @brief Lista todos os eventos cadastrados.
 *
 * Esta função exibe uma lista de todos os eventos cadastrados, mostrando informações
 * como nome, descrição, data e status de cada evento.
 */
void listarEventos();


/**
 * @brief Carrega o ID do último evento cadastrado.
 *
 * @return O ID do último evento cadastrado.
 *
 * Esta função recupera o ID do último evento cadastrado no sistema,
 * permitindo uma continuidade na numeração dos eventos.
 */
int carregarUltimoEvento();


/**
 * @brief Salva um evento no sistema.
 *
 * @param evento O evento a ser salvo.
 *
 * Esta função salva um evento no sistema, armazenando informações como
 * nome, descrição, data e status do evento em um repositório persistente.
 */
void salvarEvento(Evento evento);


/**
 * @brief Lista os eventos para cadastro.
 *
 * Esta função exibe uma lista de eventos cadastrados,
 * facilitando a seleção de eventos para edição ou atualização.
 */
void listarEventosCadastro();


/**
 * @brief Busca um evento pelo seu ID.
 *
 * @param id O ID do evento a ser buscado.
 * @return O evento correspondente ao ID fornecido.
 *
 * Esta função busca um evento pelo seu ID e retorna todas as informações
 * relacionadas a esse evento, como nome, descrição, data e status.
 */
Evento buscarEventoPorID(int id);


/**
 * @brief Atualiza as informações de um evento.
 *
 * @param evento O evento com as novas informações.
 *
 * Esta função atualiza as informações de um evento existente, como nome,
 * descrição, data e status, com base nos dados fornecidos pelo usuário.
 */
void atualizarEvento(Evento evento);

#endif // EVENTO_H