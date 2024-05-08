#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "venda.h"
#include "produto.h"
#include "menu.h"
#include "venda_detalhes.h"

//int listarVendas() {
//    FILE *file;
//    char filename[] = "data/vendas.txt";
//    file = fopen(filename, "r");
//
//    if (file != NULL) {
//        //printf("Arquivo foi aberto com sucesso.\n\n");
//        // Imprimir cabeçalho da tabela
//        printf("|=====================================================|\n");
//        printf("|                  LISTA DAS VENDAS                   |\n");
//        printf("|-----------------------------------------------------|\n");
//        printf("| %-3s | %-20s | %-5s | %-10s |\n", "Cod", "Data", "ID_Evento", "ID_Usuario");
//        printf("|-----|----------------------|-----------|------------|\n");
//
//        Venda venda;
//
//        // Ler e exibir cada linha do arquivo
//        while (fscanf(file, "%d %11s %d %d", &venda.id, venda.data, &venda.id_evento, &venda.id_usuario) != EOF) {
//            printf("| %-3d | %-20s | %-9d | %-10d |\n", venda.id, venda.data, venda.id_evento, venda.id_usuario);
//        }
//        printf("|-----------------------------------------------------|\n");
//
//        fclose(file);
//    } else {
//        printf("Não foi possível abrir o arquivo %s.\n\n", filename);
//    }
//    return 0;
//}

// Função para carregar o último ID do arquivo vendas.txt
int carregarUltimaVenda() {
    FILE *file = NULL;
    char filename[] = "data/vendas.txt";
    file = fopen(filename, "r");

    int contador_linhas = 0;

    if (file != NULL) {
        int c;
        // Percorrer o arquivo caractere por caractere
        while ((c = fgetc(file)) != EOF) {
            if (c == '\n') {
                ++contador_linhas;
            }
        }
        fclose(file);
        //printf("\tRegistro %d\n", contador_linhas);
    } else {
        printf("Erro ao abrir o arquivo %s.\n", filename);
    }

    return contador_linhas+1;
}

// Função para salvar as informações da venda no arquivo vendas.txt
void salvarVenda(Venda venda) {
    FILE *file;
    char filename[] = "data/vendas.txt";
    file = fopen(filename, "a"); // Abrir o arquivo em modo de escrita, acrescentando ao final

    if (file != NULL) {
        fprintf(file, "%d %s %d %d\n", venda.id, venda.data, venda.id_evento, venda.id_usuario);
        fclose(file);
        printf("Venda salva com sucesso!\n");
    } else {
        printf("Erro ao abrir o arquivo %s.\n", filename);
    }
}// Função para salvar as informações da venda no arquivo vendas.txt

void menuVenda() {
    listarProdutos();
    resumoVenda();
    opcoesVenda();
}


struct ResumoVendas {
    int id_produto;
    char descricao_produto[51];
    int quantidade_produto;
    double valor_produto;
};
#define MAX_PRODUTO 100
struct ResumoVendas resumoVendas[MAX_PRODUTO];
int contProduto;

void adicionarProdutoResumo(int codigoProd, int qtde) {
    Produto produto = consultarProdutoPorID(codigoProd);
    int produtoExistente = 0;

    for (int i = 0; i < contProduto; ++i) { // este for é pra verificar se ja existe algum produto com este ai no resumoProdutos, caso tiver, so somatizar a quantidade
        if(resumoVendas[i].id_produto == codigoProd) {
            // Se o produto já existe, atualiza apenas a quantidade
            resumoVendas[i].quantidade_produto += qtde;
            produtoExistente = 1;
            break; // Sai do loop após encontrar o produto
        }
    }
    // Se o produto não existe, insere um novo produto
    if (!produtoExistente) {
        if (contProduto < MAX_PRODUTO) {
            resumoVendas[contProduto].id_produto = codigoProd;
            strcpy(resumoVendas[contProduto].descricao_produto, produto.descricao);
            resumoVendas[contProduto].quantidade_produto = qtde;
            resumoVendas[contProduto].valor_produto = produto.preco;
            contProduto++;
        } else {
            printf("Limite de produtos atingido!");
        }
    }
}

void removerProdutoResumo(int codigoProd, int qtde) {

};

void limparResumo() {
    for (int i = 0; i < MAX_PRODUTO; i++) {
        resumoVendas[i].id_produto = 0; // Limpa o id do produto
        strcpy(resumoVendas[i].descricao_produto, ""); // Limpa a descrição do produto
        resumoVendas[i].quantidade_produto = 0; // Limpa a quantidade do produto
        resumoVendas[i].valor_produto = 0.0; // Limpa o valor do produto
    }
}

void gerarVenda() {
    //TODO - PRECISO GERAR UMA VENDA NOVA E USAR O ID GERADO AQUI NO IDVENDA
}

void opcoesVenda() {
    int opcao = 999;
    int idMax = carregarUltimoProduto();
    int codigoProduto = 0;
    int quantidade=0;
    printf("|=========================================================================|\n");
    printf("|                                  OPCOES                                 |\n");
    printf("|-------------------------------------------------------------------------|\n");
    printf("|\tDigite o codigo um produto para adicionar ao pedido.              |\n");
    printf("|\tDigite '-' e o codigo um produto para remover do pedido.          |\n");
    printf("|\tDigite '100' para limpar o pedido.                                |\n");
    printf("|\tDigite '200' e para sair da tela de pedido.                       |\n");
    printf("|\tDigite '0' e para gerar a venda.                                  |\n");
    printf("|\tEscolha uma opcao: ");
    scanf(" %d",&opcao);
    switch (opcao) {
        case 100 :
            limparResumo();
            system("cls");
            menuVenda();
            break;
        //case 200:
        //    system("cls");
        //    escolherMenu();
        //    break;
        //case 0:
        //    system("cls");
        //    criarVenda();
        //    gerarVenda();
        //    menuVenda();
        //    break;
        default:
            //codigoProduto = atoi(&opcao);

            if (opcao > 0 && opcao <= idMax) {
                printf("|\tDigite quantos produtos deseja adicionar: ");
                scanf("%d", &quantidade);
                adicionarProdutoResumo(opcao, quantidade);
                system("cls");
                menuVenda();
            } else if((opcao < 0 && opcao >= -idMax)) {
                removerProdutoResumo(codigoProduto, quantidade);
                system("cls");
                menuVenda();
            } else {
                printf("|\tOpção inválida. Por favor, escolha um código de produto válido.\n");
            }
    }
}

void resumoVenda() {
    int detalhes_lidos = 0; // Variável para contar quantos detalhes de venda foram lidos
    double totalGeral = 0;
    int totalQtde = 0;

    printf("|=========================================================================|\n");
    printf("|                            RESUMO DA VENDA                              |\n");
    printf("|-------------------------------------------------------------------------|\n");
    printf("| %-38s | %-10s | %-7s | %-7s |\n", "Produto", "Preco", "Qnde", "Total");
    printf("|----------------------------------------|------------|---------|---------|\n");

    for (int i = 0; i < MAX_PRODUTO; i++) {
        // Verifica se o id_produto é zero, caso for nao adiciona mais produtos, so a quantidade
        if (resumoVendas[i].id_produto == 0)
            break;

        detalhes_lidos++; // Incrementa detalhes_lidos para cada entrada
        totalGeral = resumoVendas[i].quantidade_produto * resumoVendas[i].valor_produto + totalGeral;
        totalQtde = totalQtde + resumoVendas[i].quantidade_produto;

        printf("| %-38s | %-10.2f | %-7d | %-7.2f |\n", resumoVendas[i].descricao_produto, resumoVendas[i].valor_produto,
               resumoVendas[i].quantidade_produto, resumoVendas[i].quantidade_produto * resumoVendas[i].valor_produto);
    }
    if (detalhes_lidos != 0) { // Se nenhum detalhe de venda for lido
        printf("|----------------------------------------|--------------------------------|\n");
        printf("|      ---     TOTAL GERAL     ---       |     QTD %-5d |    R$ %7.2f  |\n", totalQtde, totalGeral);
        printf("|----------------------------------------|---------------|----------------|\n");
    }

    if (detalhes_lidos == 0) { // Se nenhum detalhe de venda for lido
        //printf("|-------------------------------------------------------------------------|\n");
        printf("|                            Ainda nao ha nada aqui                       |\n");
        //printf("|-------------------------------------------------------------------------|\n");
    }
}

void criarVenda() {
    Venda venda;
    char dataAtual[11];
    venda.id = carregarUltimaVenda();
    obterDataAtual(dataAtual);
    strcpy(venda.data, dataAtual);
    venda.id_evento = 1; // Preciso receber como parâmetro - TODO
    venda.id_usuario = 2; // Preciso receber como parâmetro - TODO
    salvarVenda(venda);
    // Retorna o id para ser usado na funcao salvarVendaDetalhes(Venda_detalhes venda_detalhes)

}