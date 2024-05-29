#ifndef PRODUTO_H
#define PRODUTO_H

typedef struct {
    int id;
    char descricao[51];
    double preco;
    int estoque;
    int id_evento;
    int status;
} Produto;

void criarProduto();
int listarProdutos();
int listarProdutosVenda();
int carregarUltimoProduto();
void salvarProduto(Produto produto);
void atualizarProduto(Produto produto);
Produto buscarProdutoPorID(int id);
int ajustarEstoqueSelecionado(int idProd);

#endif // PRODUTO_H
