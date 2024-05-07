#ifndef VENDA_H
#define VENDA_H

// Definição da estrutura para armazenar as informações de venda
typedef struct {
    int id;
    char data[11];
    int id_evento;
    int id_usuario;
} Venda;

// Protótipo da função para salvar as informações da venda
void criarVenda();

int listarVendas();

int carregarUltimaVenda();

void salvarVenda(Venda venda);

void menuVenda();

void opcoesVenda();

void resumoVenda();

#endif // VENDA_H
