#ifndef VENDA_DETALHES_H
#define VENDA_DETALHES_H

// Definição da estrutura para armazenar as informações de detalhes das vendas
typedef struct {
    int id;                         // ID do detalhe da venda
    int id_venda;                   // ID da venda relacionada
    int id_produto;                 // ID do produto vendido
    char descricao_produto[51];     // Descrição do produto vendido
    int quantidade_produto;         // Quantidade do produto vendido
    double valor_produto;           // Valor unitário do produto vendido
    int id_evento;                  // ID do evento relacionado à venda
} Venda_detalhes;

/**
 * Salva os detalhes de uma venda no arquivo de vendas detalhadas.
 *
 * @param venda_detalhes Estrutura contendo os detalhes da venda a serem salvos.
 */
void salvarVendaDetalhes(Venda_detalhes venda_detalhes);

/**
 * Exibe as opções de relatório de vendas.
 */
void relatorioVendasAux();

/**
 * Exibe um relatório geral de vendas, permitindo a escolha de critérios de ordenação.
 *
 * @param criterio Critério de ordenação escolhido pelo usuário.
 * @param ordem Ordem de ordenação escolhida pelo usuário.
 * @return 0 se a operação for bem-sucedida.
 */
int relatorioVendasGeral(char* criterio, char* ordem);

/**
 * Exibe um relatório detalhado para uma venda específica.
 *
 * @param nomeArquivo Nome do arquivo de vendas detalhadas.
 * @param opcao ID da venda a ser analisada.
 * @return 0 se a operação for bem-sucedida.
 */
int relatorioVendaEspecifico(const char *nomeArquivo, int opcao);

/**
 * Exibe um relatório detalhado para um evento específico.
 *
 * @param nomeArquivo Nome do arquivo de vendas detalhadas.
 * @param opcao ID do evento a ser analisado.
 * @return 0 se a operação for bem-sucedida.
 */
int relatorioEventoEspecifico(const char *nomeArquivo, int opcao);

/**
 * Carrega o ID da última venda detalhada registrada.
 *
 * @return O ID da última venda detalhada registrada.
 */
int carregarUltimaVendaDetalhes();

#endif // VENDA_DETALHES_H
