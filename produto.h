#ifndef PRODUTO_H
#define PRODUTO_H

// Define uma estrutura chamada Produto para armazenar informações sobre um produto
typedef struct {
    int id;                // Identificador único do produto (por exemplo, um número de ID)
    char descricao[51];    // Descrição do produto, limitado a 50 caracteres (o último byte é para o caractere nulo)
    double preco;          // Preço do produto (valor em ponto flutuante)
    int estoque;           // Quantidade em estoque do produto (um número inteiro)
    int id_evento;         // Identificador do evento associado ao produto (por exemplo, ID do evento em que o produto será vendido)
    int status;            // Status do evento (por exemplo, 1 - Ativo, 0 - Inativo.)
} Produto;


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "produto.h" // Inclui a definição da estrutura Produto e os protótipos das funções relacionadas a produtos
#include "components.h" // Inclui funções auxiliares para interface de usuário
#include "evento.h" // Inclui funções relacionadas a eventos
#include "menu.h" // Inclui funções relacionadas a menus
#include "variaveis_compartilhadas.h" // Inclui variáveis compartilhadas

/**
 * Função para exibir uma mensagem de erro ao abrir um arquivo.
 */
void erroAoAbrirArquivo();

/**
 * Função para criar um novo produto.
 */
void criarProduto();

/**
 * Função para listar todos os produtos cadastrados.
 * Retorna 0 se a listagem for bem-sucedida.
 */
int listarProdutos();

/**
 * Função para carregar o ID do último produto cadastrado.
 * Retorna o ID do último produto + 1.
 */
int carregarUltimoProduto();

/**
 * Função para salvar um novo produto no arquivo de produtos.
 * Recebe como parâmetro o produto a ser salvo.
 */
void salvarProduto(Produto produto);

/**
 * Função para buscar um produto pelo seu ID.
 * Recebe como parâmetro o ID do produto a ser buscado.
 * Retorna o produto encontrado ou um produto vazio se não encontrado.
 */
Produto buscarProdutoPorID(int id);

/**
 * Função para atualizar as informações de um produto no arquivo de produtos.
 * Recebe como parâmetro o produto atualizado.
 */
void atualizarProduto(Produto produto);

/**
 * Função para carregar um produto pelo seu ID.
 * Recebe como parâmetro o ID do produto a ser carregado.
 * Retorna o produto encontrado ou um produto vazio se não encontrado.
 */
Produto carregarProdutoPorID(int id);

/**
 * Função para adicionar uma quantidade específica de produtos ao estoque.
 * Recebe como parâmetros o ID do produto e a quantidade a ser adicionada.
 */
void adicionarEstoque(int id, int quantidade);

/**
 * Função para remover uma quantidade específica de produtos do estoque.
 * Recebe como parâmetros o ID do produto e a quantidade a ser removida.
 */
void removerEstoque(int id, int quantidade);

/**
 * Função para ajustar o estoque de um produto selecionado.
 * Recebe como parâmetro o ID do produto.
 * Retorna 0 após ajustar o estoque.
 */
int ajustarEstoqueSelecionado(int idProd);


#endif // PRODUTO_H
