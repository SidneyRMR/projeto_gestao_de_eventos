#ifndef VENDA_DETALHES_H
#define VENDA_DETALHES_H

// Definição da estrutura para armazenar as informações de detalhes das vendas
typedef struct {
    int id;
    int id_venda;
    int id_produto;
    char descricao_produto[51];
    int quantidade_produto;
    double valor_produto;
    int id_evento;
} Venda_detalhes;

// Protótipo da função para salvar as informações da venda
void salvarVendaDetalhes(Venda_detalhes venda_detalhes);

void relatorioVendasAux();

int relatorioVendasGeral(char* criterio, char* ordem);

int relatorioVendaEspecifico(const char *nomeArquivo, int opcao, int idMaximo);

void salvarVendaDetalhes(Venda_detalhes venda_detalhes);

int carregarUltimaVendaDetalhes();
#endif // VENDA_DETALHES_H