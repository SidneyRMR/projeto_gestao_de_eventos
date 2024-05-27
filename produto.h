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

int EditarNomeProduto(int idProduto);
int EditarDescricaoProduto(int idProduto);
int DesativarProduto(int idProduto);

int listarProdutos();

int listarProdutosVenda();

int carregarUltimoProduto();

void salvarProduto(Produto produto);

Produto BuscarProdutoPorID(int id);

int ajustarEstoque();

void criarProduto();
void editarProduto(int idProduto, int idEvento);


#endif // PRODUTO_H
