#ifndef PRODUTO_H
#define PRODUTO_H

// Definição da estrutura para armazenar as informações de produto
typedef struct {
    int id;
    char descricao[51];
    double preco;
    int estoque;
    int id_evento;
    int status;
} Produto;

int ajustarEstoqueSelecionado(int idProd);

void atualizarProduto(Produto produto);

int listarProdutos();

int listarProdutosVenda();

int carregarUltimoProduto();

void salvarProduto(Produto produto);

Produto buscarProdutoPorID(int id);

int ajustarEstoque();

void criarProduto();


#endif // PRODUTO_H
