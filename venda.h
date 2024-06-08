#ifndef VENDA_H
#define VENDA_H

// Definição da estrutura para armazenar as informações de venda
typedef struct {
    int id;                     // ID da venda
    char data[11];              // Data da venda (formato: YYYY-MM-DD)
    int id_evento;              // ID do evento associado à venda
    int id_usuario;             // ID do usuário responsável pela venda
    char formaPgto[10];         // Forma de pagamento da venda
} Venda;

/**
 * Cria uma nova venda.
 *
 * Esta função solicita ao usuário que escolha a forma de pagamento,
 * verifica o pagamento em dinheiro se necessário, salva as informações
 * da venda no arquivo vendas.txt e atualiza o estoque dos produtos
 * vendidos no arquivo produtos.txt.
 */
void criarVenda();

/**
 * Lista todas as vendas registradas.
 *
 * Esta função lista todas as vendas registradas no arquivo vendas.txt.
 * Para cada venda, exibe o ID da venda, a data, o evento associado,
 * o usuário responsável pela venda e a forma de pagamento.
 */
void listarVendas();

/**
 * Carrega o ID da última venda registrada.
 *
 * Esta função é responsável por carregar o ID da última venda registrada
 * no arquivo vendas.txt. Ela lê o arquivo linha por linha e conta o número
 * total de linhas para determinar o ID da última venda.
 *
 * @return O ID da última venda registrada.
 */
int carregarUltimaVenda();

/**
 * Exibe as opções disponíveis durante o processo de venda.
 *
 * Esta função exibe as opções disponíveis para o usuário durante o processo
 * de venda. O usuário pode adicionar produtos ao pedido, remover produtos
 * do pedido, limpar o pedido, gerar a venda ou sair do programa.
 */
void opcoesVenda();

/**
 * Exibe um resumo detalhado dos itens adicionados ao pedido de venda.
 *
 * Esta função exibe um resumo detalhado dos itens adicionados ao pedido de venda.
 * Mostra o código do produto, a descrição do produto, o preço unitário, a quantidade
 * e o total para cada item no pedido. Além disso, mostra o total geral do pedido.
 */
void resumoVenda();

/**
 * Limpa todos os itens do resumo de venda.
 *
 * Esta função limpa todos os itens do resumo de venda, reiniciando as variáveis
 * globais relacionadas ao resumo de venda e ao total geral.
 */
void limparResumo();

Venda buscarVendaPorId(int id);


#endif // VENDA_H
