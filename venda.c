#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "venda.h"
#include "produto.h"
#include "menu.h"
#include "login.h"
#include "venda_detalhes.h"
#include "usuario.h"
#include "variaveis_compartilhadas.h"
#include "components.h"


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
    } else {
        printf("Erro ao abrir o arquivo %s.\n", filename);
    }

    return contador_linhas+1;
}

void menuVenda() {
    listarProdutosVenda();
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
    if(qtde <= 0 ) {
        printf("|\tDigite uma quantidade acima de ZERO!\n");
        system("Pause");
        return;
    } else {
        // Este for é para verificar se ja existe algum produto com este ai no resumoProdutos, caso tiver, so somatizar a quantidade
        for (int i = 0; i < contProduto; ++i) {
            if (resumoVendas[i].id_produto == codigoProd) {
                // Se o produto já existe, atualiza apenas a quantidade
                resumoVendas[i].quantidade_produto += qtde;
                produtoExistente = 1;
                printf("|         ---------      Adicionando o item %-10s     ---------       |\n",produto.descricao);
                //system("PAUSE");
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
                printf("|        ---------      Adicionando o item %-10s      ---------        |\n",produto.descricao);
                //system("PAUSE");
            } else {
                printf("|\tLimite de produtos atingido!\n");
            }
        }
    }
}

void removerProdutoResumo(int codigoProd, int qtde) {
    codigoProd = codigoProd * -1;
    for (int i = 0; i < contProduto; ++i) {
        if (resumoVendas[i].id_produto == codigoProd) {
            if (resumoVendas[i].quantidade_produto > qtde) {
                resumoVendas[i].quantidade_produto -= qtde;
                printf("|       --------      Removendo %d item(s) de %s!      --------       |\n", qtde, resumoVendas[i].descricao_produto);
                //system("PAUSE");
                break; // Sai do loop após atualizar a quantidade do produto
            } else if (resumoVendas[i].quantidade_produto <= qtde) {
                resumoVendas[i].id_produto = 0; // Limpa o id do produto
                strcpy(resumoVendas[i].descricao_produto, ""); // Limpa a descrição do produto
                resumoVendas[i].quantidade_produto = 0; // Limpa a quantidade do produto
                resumoVendas[i].valor_produto = 0.0; // Limpa o valor do produto
                contProduto = contProduto -1;
                printf("|        ---------      Removendo um item da venda!      ---------        |\n");
                //system("PAUSE");
                break; // Sai do loop após atualizar a quantidade do produto
            } else {
                printf("|\tDigite uma quantidade valida!\n");
                system("PAUSE");
                break; // Sai do loop
            }
        }
    }
}
double totalGeral = 0;
void limparResumo() {
    for (int i = 0; i < MAX_PRODUTO; i++) {
        resumoVendas[i].id_produto = 0; // Limpa o id do produto
        strcpy(resumoVendas[i].descricao_produto, ""); // Limpa a descrição do produto
        resumoVendas[i].quantidade_produto = 0; // Limpa a quantidade do produto
        resumoVendas[i].valor_produto = 0.0; // Limpa o valor do produto
    }
    totalGeral = 0.00;
    printf("|       -------      Limpando todos os itens da venda!      -------       |\n");
    system("PAUSE");
    contProduto = 0; // Redefine o contador de produtos para zero
}

void opcoesVenda() {
    int opcao = 999;
    int idMax = carregarUltimoProduto();
    int quantidade=0;

    imprimirTituloCabecario("OPCOES",NULL);

        printf("|\tDigite o codigo um produto para adicionar ao pedido.                                                       |\n");
    if (contProduto > 0) {
        printf("|\tDigite '-' e o codigo um produto para remover do pedido.                                                   |\n");
        printf("|\tDigite 100 e para gerar a venda.                                                                           |\n");
        printf("|\tDigite 200 para limpar o pedido.                                                                           |\n");
    }
    if(strcmp(getUsuarioCompartilhado().tipo, "vendedor")) {
        printf("|\tDigite 0 e para sair da tela de pedido.                                                                    |\n");
    } else {
        printf("|\tDigite 0 e para sair do programa.                                                                          |\n");
    }
    printf("|\tEscolha uma opcao ou codigo do produto: ");
    scanf(" %d",&opcao);

    switch (opcao) {
        case 200 :
            limparResumo();
            system("cls");
            menuVenda();
            break;
        case 0:
            system("cls");
            if(strcmp(getUsuarioCompartilhado().tipo, "vendedor")) {
                escolherMenu();
            } else {
                printf("Logoff feito com sucesso!...\n");
                login();
            }
            break;
        case 100:
            system("cls");
            criarVenda();
            menuVenda();
            break;
        default:
            if (opcao > 0 && opcao <= idMax-1) {
                printf("|\tDigite quantos produtos deseja ADICIONAR: ");
                scanf("%d", &quantidade);
                adicionarProdutoResumo(opcao, quantidade);
                system("cls");
                menuVenda();
            } else if(opcao < 0 && opcao >= -idMax+1) {
                printf("|\tDigite quantos produtos deseja REMOVER: ");
                scanf("%d", &quantidade);
                removerProdutoResumo(opcao, quantidade);
                system("cls");
                menuVenda();
            } else {
                system("cls");
                opcaoInvalida();
                menuVenda();
            }
    }
}


void resumoVenda() {
    int detalhes_lidos = 0; // Variável para contar quantos detalhes de venda foram lidos
    int totalQtde = 0;

    imprimirTituloCabecario("RESUMO DA VENDA", NULL);
    printf("| %-3s | %-67s | %-10s | %-10s | %-10s |\n","Cod", "Produto", "Preco", "Qnde", "Total");
    imprimirLinhaDivisoria();

    for (int i = 0; i < MAX_PRODUTO; i++) {
        // Verifica se o id_produto é zero, caso for nao adiciona mais produtos, so a quantidade
        if (resumoVendas[i].id_produto == 0)
            break;

        detalhes_lidos++; // Incrementa detalhes_lidos para cada entrada
        totalGeral = resumoVendas[i].quantidade_produto * resumoVendas[i].valor_produto + totalGeral;
        totalQtde = totalQtde + resumoVendas[i].quantidade_produto;

        printf("| %-3d | %-67s | %-10.2f | %-10d | %-10.2f |\n", resumoVendas[i].id_produto, resumoVendas[i].descricao_produto, resumoVendas[i].valor_produto,
               resumoVendas[i].quantidade_produto , resumoVendas[i].quantidade_produto * resumoVendas[i].valor_produto);
    }
    if (detalhes_lidos != 0) { // Se nenhum detalhe de venda for lido
        imprimirLinhaDivisoria();
        printf("|                        ---     TOTAL GERAL     ---                        |   QTD %-10d  |   R$ %10.2f  |\n", totalQtde, totalGeral);
        imprimirLinhaDivisoria();
    }

    if (detalhes_lidos == 0) { // Se nenhum detalhe de venda for lido
        printf("|                                              Ainda nao ha nada aqui                                              |\n");
    }
}

// Função para salvar as informações da venda no arquivo vendas.txt
void criarVenda() {
    Venda venda;
    // Faz a verificação se possui algum item no resumoVendas, caso nao, sair e nao gerar a venda
    if (contProduto == 0) {
        printf("Nao ha itens para criar a venda.\n");
        system("PAUSE");
        return; // Sair da função sem criar a venda
    }

    int opcaoPgto = 0;
    while(opcaoPgto == 0) {
        printf("|\tO valor total do pedido eh: %.2lf",totalGeral);
        system("cls");
        imprimirTituloCabecario("Escolha a forma de Pagamento",
                                "1. Credito | 2. Dinheiro | 3. Pix | 4. Debito");
        scanf("%d",&opcaoPgto);
        switch (opcaoPgto) {
            case 1:
                strcpy(venda.formaPgto, "credito");
                break;
            case 2:
                strcpy(venda.formaPgto, "dinheiro");
                break;
            case 3:
                strcpy(venda.formaPgto, "pix");
                break;
            case 4:
                strcpy(venda.formaPgto, "debito");
                break;
            default:
                opcaoInvalida();
                break;
        }
    }

    Usuario usuario = getUsuarioCompartilhado();

    char dataAtual[11];
    venda.id = carregarUltimaVenda();
    obterDataAtual(dataAtual);
    strcpy(venda.data, dataAtual);

    venda.id_evento = usuario.id_evento;
    venda.id_usuario = usuario.id;

    // Retorna o id para ser usado na funcao salvarVendaDetalhes(Venda_detalhes venda_detalhes)
    FILE *file;
    char filename[] = "data/vendas.txt";
    file = fopen(filename, "a"); // Abrir o arquivo em modo de escrita, acrescentando ao final

    if (file != NULL) {
        fprintf(file, "%d %s %d %d '%s'\n", venda.id, venda.data, venda.id_evento, venda.id_usuario , venda.formaPgto);
        fclose(file);
        printf("|         --------        Venda salva com sucesso!        --------        |\n");
    } else {
        printf("Erro ao abrir o arquivo %s.\n", filename);
    }

    int idUltimaVenda = carregarUltimaVenda();
    int idUltimaVendaDetalhes = carregarUltimaVendaDetalhes();
    Venda_detalhes venda_detalhes;

    int contId = 0;
    for (int i = 0; i < contProduto; ++i) {
        venda_detalhes.id = idUltimaVendaDetalhes + contId;
        venda_detalhes.id_venda = idUltimaVenda;
        venda_detalhes.id_produto = resumoVendas[i].id_produto;
        strcpy(venda_detalhes.descricao_produto, resumoVendas[i].descricao_produto);
        venda_detalhes.quantidade_produto = resumoVendas[i].quantidade_produto;
        venda_detalhes.valor_produto = resumoVendas[i].valor_produto;
        venda_detalhes.id_evento = venda.id_evento;

        contId++;
        salvarVendaDetalhes(venda_detalhes);
    }
    limparResumo();
    system("cls");
}