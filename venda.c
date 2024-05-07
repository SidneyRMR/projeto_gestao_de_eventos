#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "venda.h"
#include "produto.h"
#include "menu.h"
#include "venda_detalhes.h"

void criarVenda() {
    Venda venda;
    char dataAtual[11];
    venda.id = carregarUltimaVenda();
    obterDataAtual(dataAtual);
    strcpy(venda.data, dataAtual);
    venda.id_evento = 1; // Preciso receber como parâmetro - TODO
    venda.id_usuario = 2; // Preciso receber como parâmetro - TODO
    salvarVenda(venda);
}

int listarVendas() {
    FILE *file;
    char filename[] = "data/vendas.txt";
    file = fopen(filename, "r");

    if (file != NULL) {
        //printf("Arquivo foi aberto com sucesso.\n\n");

        // Imprimir cabeçalho da tabela

        printf("|=====================================================|\n");
        printf("|                  LISTA DAS VENDAS                   |\n");
        printf("|-----------------------------------------------------|\n");
        printf("| %-3s | %-20s | %-5s | %-10s |\n", "Cod", "Data", "ID_Evento", "ID_Usuario");
        printf("|-----|----------------------|-----------|------------|\n");

        Venda venda;

        // Ler e exibir cada linha do arquivo
        while (fscanf(file, "%d %11s %d %d", &venda.id, venda.data, &venda.id_evento, &venda.id_usuario) != EOF) {
            printf("| %-3d | %-20s | %-9d | %-10d |\n", venda.id, venda.data, venda.id_evento, venda.id_usuario);
        }
        printf("|-----------------------------------------------------|\n");

        fclose(file);
    } else {
        printf("Não foi possível abrir o arquivo %s.\n\n", filename);
    }

    return 0;
}

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
    resumoVenda();
    listarProdutos();
    opcoesVenda();

}
void limparResumo() {
    // TODO - Limpa a tela de resumo
}
struct ResumoVendas {
    int id_produto;
    char descricao_produto[21];
    int quantidade_produto;
    float valor_produto;
};

#define MAX_PRODUTO 100
struct ResumoVendas resumoVendas[MAX_PRODUTO];

void gerarVenda() {
    //TODO - PRECISO GERAR UMA VENDA NOVA E USAR O ID GERADO AQUI NO IDVENDA
    Venda_detalhes venda_detalhes[MAX_PRODUTO];
    //ResumoVendas resumoVendas[];
    int idMinParaCadastrar = carregarUltimaVendaDetalhes();
    int numProdutos = sizeof(resumoVendas) / sizeof(resumoVendas[0]); // Calcula o numero de elementos
    // Salva a venda no venda_detalhes.txt
    for (int i = idMinParaCadastrar; idMinParaCadastrar < numProdutos; ++i) {
        venda_detalhes[i].id = idMinParaCadastrar;
        //venda_detalhes.id_venda = //TODO carregar a venda;
        venda_detalhes[i].id_produto = resumoVendas[i].id_produto;
        strcpy(venda_detalhes[i].descricao_produto, resumoVendas[i].descricao_produto);
        venda_detalhes[i].quantidade_produto = resumoVendas[i].quantidade_produto;
        venda_detalhes[i].valor_produto = resumoVendas[i].valor_produto;
        idMinParaCadastrar++;
    }
    //salvarVendaDetalhes(venda_detalhes);
}

void adicionarProdutoResumo(int num, int qnde) {
    int cont = 0;
    Produto produto = consultarProdutoPorID(num);
    Venda_detalhes venda_detalhes[100];
    venda_detalhes[cont].id = carregarUltimaVendaDetalhes();
    venda_detalhes[cont].id_venda = carregarUltimaVenda();
    venda_detalhes[cont].id_produto = num;
    strcpy(venda_detalhes[cont].descricao_produto, produto.descricao);
    venda_detalhes[cont].quantidade_produto = qnde;
    venda_detalhes[cont].valor_produto = produto.preco;
    cont++;
}
void removerProdutoResumo(int num) {
    num = num * -1;
    Venda_detalhes venda_detalhes[100];

    // TODO
};
void opcoesVenda() {
    char opcao;
    int idMax = carregarUltimoProduto();
    int num = 0;
    printf("|=========================================================================|\n");
    printf("|                                  OPCOES                                 |\n");
    printf("|-------------------------------------------------------------------------|\n");
    printf("|\tDigite o codigo um produto para adicionar ao pedido.              |\n");
    printf("|\tDigite '-' e o codigo um produto para remover do pedido.          |\n");
    printf("|\tDigite 'c' e para limpar o pedido.                                |\n");
    printf("|\tDigite 's' e para sair da tela de pedido.                         |\n");
    printf("|\tDigite 'f' e para gerar a venda.                                  |\n");
    printf("|\tEscolha uma opcao: ");
    scanf(" %c",&opcao);
    switch (opcao) {
        case 'c' :
            limparResumo();
            system("cls");
            menuVenda();
            break;
        case 's':
            system("cls");
            escolherMenu();
            break;
        case 'f':
            system("cls");
            gerarVenda();
            menuVenda();
            break;
        default:
            num = atoi(&opcao);
            if (num > 0 || num <= idMax) {
                int quantidade=0;
                printf("|\tDigite quantos produtos deseja adicionar: \n");
                scanf("%d", &quantidade);
                adicionarProdutoResumo(num, quantidade);
            } else if((num < 0 || num >= -idMax)) {
                removerProdutoResumo(num);
            } else {
                printf("|\tOpção inválida. Por favor, escolha um código de produto válido.\n");
            }
    }
}
//struct ResumoVendas {
//    char descricao_produto[21];
//    int quantidade_produto;
//    float valor_produto;
//} ;



void resumoVenda() {
    //ResumoVendas resumoVendas[MAX_PRODUTO];
    int detalhes_lidos = 0; // Variável para contar quantos detalhes de venda foram lidos

    printf("|=========================================================================|\n");
    printf("|                            RESUMO DA VENDA                              |\n");
    printf("|-------------------------------------------------------------------------|\n");
    printf("| %-38s | %-10s | %-7s | %-7s |\n", "Produto", "Preco", "Qnde", "Total");
    printf("|----------------------------------------|------------|---------|---------|\n");

   //while (scanf("%20s %d %f", resumoVendas.descricao_produto, &resumoVendas.quantidade_produto, &resumoVendas.valor_produto) == 3) {
   //    detalhes_lidos++; // Incrementa se um detalhe de venda for lido
   //    printf("| %-20s | %-8.2f | %-5d | %-8.2f |\n", resumoVendas.descricao_produto, resumoVendas.valor_produto, resumoVendas.quantidade_produto,
   //           resumoVendas.quantidade_produto * resumoVendas.valor_produto);
   //}

    if (detalhes_lidos == 0) { // Se nenhum detalhe de venda for lido
        //printf("|-------------------------------------------------------------------------|\n");
        printf("|                            Ainda nao ha nada aqui                       |\n");
        //printf("|-------------------------------------------------------------------------|\n");
    }
}