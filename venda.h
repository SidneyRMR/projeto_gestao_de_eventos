#ifndef VENDA_H
#define VENDA_H

// Definição da estrutura para armazenar as informações de venda
typedef struct {
    int id;
    char data[11];
    int id_evento;
    int id_usuario;
    char formaPgto[10];
} Venda;

void criarVenda();

void listarVendas();

int carregarUltimaVenda();

void opcoesVenda();

void resumoVenda();

void limparResumo();

#endif // VENDA_H
