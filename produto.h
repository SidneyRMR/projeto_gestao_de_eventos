#ifndef PRODUTO_H
#define PRODUTO_H

// Definição da estrutura para armazenar as informações de produto
typedef struct {
    int id;
    char descricao[51];
    double preco;
    int estoque;
    int id_evento;
} Produto;

void criarProduto();

int listarProdutos();

int carregarUltimoProduto();

void salvarProduto(Produto produto);

Produto consultarProdutoPorID(int id);

#endif // PRODUTO_H
