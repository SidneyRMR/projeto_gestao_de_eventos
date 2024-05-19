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

int carregarUltimaVenda();

void menuVenda();

void opcoesVenda();

void resumoVenda();

#endif // VENDA_H
