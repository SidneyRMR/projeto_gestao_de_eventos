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
#include "components/components.h"


#define MAX_PRODUTO 100
#define MAX_RESUMO_VENDA 100

void limparResumo();

double totalGeral = 0;
int contProduto;

struct ResumoVendas {
    int id_produto;
    char descricao_produto[51];
    int quantidade_produto;
    double valor_produto;
};
struct ResumoVendas resumoVendas[MAX_PRODUTO];

void listarVendas() {
    FILE *file;
    char filename[] = "data/vendas.txt";
    file = fopen(filename, "r");

    if (file != NULL) {
        imprimirTituloCabecarioDuplo("LISTA DE VENDAS", NULL);

        printf("| %-4s | %-10s | %-46s | %-25s | %-15s |\n", "Cod", "Data", "Evento", "Usuario", "Forma Pgto");
        imprimirLinhaDivisoria();

        Venda venda;

        while (fscanf(file, "%d %10s %d %d '%15[^']'", &venda.id, venda.data, &venda.id_evento, &venda.id_usuario, venda.formaPgto) != EOF) {
            // Suponha que você tenha uma função para obter o nome do evento com base no id do evento
            char evento[10];
            char* nomeEvento = obterNomeEvento("eventos.txt", venda.id_evento);
            char* nomeUsuario = obterNomeUsuario("usuarios.txt", venda.id_usuario);

            printf("| %-4d | %-10s | %-46s | %-25s | %-15s |\n", venda.id, venda.data, nomeEvento, nomeUsuario, venda.formaPgto);
        }

        imprimirLinhaDivisoria();
        fclose(file);
    } else {
        centralizarFrase("Não foi possível abrir o arquivo.","error");
    }
}
void listarVendasComFiltro() {
    FILE *file;
    char filename[] = "data/vendas.txt";
    file = fopen(filename, "r");

    if (file != NULL) {
        imprimirTituloCabecarioDuplo("LISTA DE VENDAS", NULL);

        printf("| %-4s | %-10s | %-46s | %-25s | %-15s |\n", "Cod", "Data", "Evento", "Usuario", "Forma Pgto");
        imprimirLinhaDivisoria();

        Venda venda;

        while (fscanf(file, "%d %10s %d %d '%15[^']'", &venda.id, venda.data, &venda.id_evento, &venda.id_usuario, venda.formaPgto) != EOF) {
            // Suponha que você tenha uma função para obter o nome do evento com base no id do evento
            char evento[10];
            char* nomeEvento = obterNomeEvento("eventos.txt", venda.id_evento);
            char* nomeUsuario = obterNomeUsuario("usuarios.txt", venda.id_usuario);

            printf("| %-4d | %-10s | %-46s | %-25s | %-15s |\n", venda.id, venda.data, nomeEvento, nomeUsuario, venda.formaPgto);
        }

        imprimirLinhaDivisoria();
        fclose(file);
    } else {
        centralizarFrase("Não foi possível abrir o arquivo.","error");
    }
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
    } else {
        centralizarFrase("Não foi possível abrir o arquivo.","error");
    }

    return contador_linhas+1;
}

void adicionarProdutoResumo(int codigoProd, int qtde) {
    Produto produto = buscarProdutoPorID(codigoProd);
    int produtoExistente = 0;
    if(qtde <= 0 ) {
        centralizarFrase("Digite uma quantidade acima de ZERO!", "warning");
        system("Pause");
        return;
    } else {
        // Este for é para verificar se ja existe algum produto com este ai no resumoProdutos, caso tiver, so somatizar a quantidade
        for (int i = 0; i < contProduto; ++i) {
            if (resumoVendas[i].id_produto == codigoProd) {
                // Se o produto já existe, atualiza apenas a quantidade
                resumoVendas[i].quantidade_produto += qtde;
                produtoExistente = 1;
                centralizarFrase("---------      Adicionando um item      ---------", "success");
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
                centralizarFrase("---------      Adicionando um item       ---------", "success");
            } else {
                centralizarFrase("---------      Limite de produtos atingido!      ---------", "error");
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
                centralizarFrase("Removendo items da venda!", "success");
                break; // Sai do loop após atualizar a quantidade do produto
            } else if (resumoVendas[i].quantidade_produto <= qtde) {
                resumoVendas[i].id_produto = 0; // Limpa o id do produto
                strcpy(resumoVendas[i].descricao_produto, ""); // Limpa a descrição do produto
                resumoVendas[i].quantidade_produto = 0; // Limpa a quantidade do produto
                resumoVendas[i].valor_produto = 0.0; // Limpa o valor do produto
                contProduto = contProduto -1;
                centralizarFrase("Removendo um item da venda!", "success");
                break; // Sai do loop após atualizar a quantidade do produto
            } else {
                centralizarFrase("Digite uma quantidade valida!", "warning");
                break; // Sai do loop
            }
        }
    }
}

void limparResumo() {
    if (contProduto != 0){

    for (int i = 0; i < MAX_PRODUTO; i++) {
        resumoVendas[i].id_produto = 0; // Limpa o id do produto
        strcpy(resumoVendas[i].descricao_produto, ""); // Limpa a descrição do produto
        resumoVendas[i].quantidade_produto = 0; // Limpa a quantidade do produto
        resumoVendas[i].valor_produto = 0.0; // Limpa o valor do produto
    }
    totalGeral = 0.00;
    centralizarFrase("-------            Limpando todos os itens da venda!           -------", "success");
    //system("PAUSE");
    contProduto = 0; // Redefine o contador de produtos para zero
    //itensPedido = 0;
    }
    //else {
    //    centralizarFrase("-------            Nao possui itens na venda ainda!           -------", "error");
    //}
}


void opcoesVenda() {
    int idMax = carregarUltimoProduto();

    imprimirTituloCabecario("OPCOES",NULL);

        centralizarFrase(" Cod  |  Digite o codigo de um produto para adicionar ao pedido.  ", "default");
    if (contProduto > 0) {
        centralizarFrase("-Cod  |  Digite '-' e o codigo um produto para remover do pedido. ", "default");
        imprimirLinhaDivisoria();
        centralizarFrase(" 100  |  Digite 100 e para gerar a venda.                         ", "default");
        centralizarFrase(" 200  |  Digite 200 para limpar o pedido.                         ", "default");
    }
        centralizarFrase("   0  |  Digite 0 e para sair do programa.                        ", "default");
    imprimirLinhaDivisoria();
    int opcao = centralizarEObterValorInt("Escolha uma opcao ou codigo do produto:");

    switch (opcao) {
        case 0:
            if(strcmp(getUsuarioCompartilhado().tipo, "vendedor")) {
                escolherMenu();
            } else {
                centralizarFrase("Logoff feito com sucesso!...", "success");
                login();
            }
            break;
        case 100:
            criarVenda();
            menuVenda();
            break;
        case 200 :
            limparResumo();
            menuVenda();
            break;
        default:
            if (opcao > 0 && opcao <= idMax-1) {
                int quantidade;
                Produto produto = buscarProdutoPorID(opcao);
                if(produto.id_evento == getUsuarioCompartilhado().id_evento) {
                    quantidade = centralizarEObterValorInt("Digite quantos produtos deseja ADICIONAR:");
                    adicionarProdutoResumo(opcao, quantidade);
                    menuVenda();
                } else {
                    opcaoInvalida();
                    menuVenda();
                }
            } else if(opcao < 0 && opcao >= -idMax+1 && contProduto > 0) {
                int quantidade;
                Produto produto = buscarProdutoPorID(opcao);
                if(produto.id_evento == getUsuarioCompartilhado().id) {
                    quantidade = centralizarEObterValorInt("Digite quantos produtos deseja REMOVER:");
                    removerProdutoResumo(opcao, quantidade);
                    menuVenda();
                } else {
                    opcaoInvalida();
                    menuVenda();
                }
            } else {
                opcaoInvalida();
                menuVenda();
            }
    }
}

void resumoVenda() {
    int detalhes_lidos = 0; // Variável para contar quantos detalhes de venda foram lidos
    int totalQtde = 0;

    if (contProduto != 0){
        imprimirTituloCabecario("RESUMO DA VENDA", NULL);
        printf("| %-3s | %-67s | %-10s | %-10s | %-10s |\n","Cod", "Produto", "Preco", "Qnde", "Total");
        imprimirLinhaDivisoria();
    }

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

}

int verificaValorPago(double valorVenda) {
    double valorPago = 0;
    valorPago = centralizarEObterValorDouble("Digite o valor que sera pago: ");

    if(valorPago < totalGeral) {
        double diferenca =  totalGeral - valorPago;
        char diferencaStr[50];
        sprintf(diferencaStr, "R$ %.2f", diferenca);
        centralizarFrase("Valor a ser pago deve ser maior ou igual a: ", "warning");
        imprimirTituloCabecario("Valor a ser pago deve ser maior ou igual a: ", diferencaStr);
        verificaValorPago(valorVenda);
    } else if((valorPago > totalGeral) && ((valorPago - totalGeral) < 100.00)) {
        centralizarFrase("Devolver o troco de:", "warning");
        double troco =  valorPago - totalGeral;

        char trocoStr[50];
        sprintf(trocoStr, "R$ %.2f", troco);
        imprimirTituloCabecario(trocoStr, NULL);
    } else if((valorPago > totalGeral) && ((valorPago - totalGeral) > 100.00)) {
        centralizarFrase("Troco a voltar nao pode ser maior que R$ 100,00.", "error");
        verificaValorPago(valorVenda);
    }
    return 0;
}

// Função para salvar as informações da venda no arquivo vendas.txt
void criarVenda() {
    Venda venda;
    if (contProduto == 0) {
        centralizarFrase("Nao ha itens para criar a venda.", "error");
        return;
    }

    int opcaoPgto = 0;
    while(opcaoPgto == 0) {
        system("cls");

        char totalGeralStr[50];
        sprintf(totalGeralStr, "O valor total do pedido eh: %.2lf", totalGeral);

        imprimirTituloCabecario(totalGeralStr, NULL);
        imprimirTituloCabecario("Escolha a forma de Pagamento", "1. Credito | 2. Dinheiro | 3. Pix | 4. Debito");
        opcaoPgto = centralizarEObterValorInt("Digite uma opcao: ");

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
                opcaoPgto = 0; // Continua no loop
                break;
        }
        if(strcmp(venda.formaPgto, "dinheiro") == 0) {
            verificaValorPago(totalGeral);
        }
    }

    Usuario usuario = getUsuarioCompartilhado();
    char dataAtual[11];
    venda.id = carregarUltimaVenda();
    obterDataAtual(dataAtual);
    strcpy(venda.data, dataAtual);

    venda.id_evento = usuario.id_evento;
    venda.id_usuario = usuario.id;

    FILE *file;
    char filename[] = "data/vendas.txt";
    file = fopen(filename, "a");

    if (file != NULL) {
        fprintf(file, "%d %s %d %d '%s'\n", venda.id, venda.data, venda.id_evento, venda.id_usuario, venda.formaPgto);
        fclose(file);
        centralizarFrase("--------        Venda salva com sucesso!        --------", "success");
    } else {
        centralizarFrase("Não foi possível abrir o arquivo.","error");
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

    // Atualizar o estoque no arquivo produto.txt
    FILE *fileProdutos;
    char filenameProdutos[] = "data/produtos.txt";
    fileProdutos = fopen(filenameProdutos, "r+");

    if (fileProdutos == NULL) {
        centralizarFrase("Não foi possível abrir o arquivo.","error");
        return;
    }

    Produto produtos[MAX_PRODUTO];
    int count = 0;

    // Ler os produtos do arquivo para a memória
    while (fscanf(fileProdutos, "%d '%[^']' %lf %d %d %d", &produtos[count].id, produtos[count].descricao, &produtos[count].preco, &produtos[count].estoque, &produtos[count].id_evento, &produtos[count].status) != EOF) {
        count++;
    }

    // Atualizar o estoque dos produtos vendidos
    for (int i = 0; i < contProduto; i++) {
        for (int j = 0; j < count; j++) {
            if (resumoVendas[i].id_produto == produtos[j].id) {
                produtos[j].estoque -= resumoVendas[i].quantidade_produto;
                break;
            }
        }
    }

    // Reescrever o arquivo com os novos estoques
    freopen(filenameProdutos, "w", fileProdutos);
    for (int i = 0; i < count; i++) {
        fprintf(fileProdutos, "%d '%s' %.2f %d %d %d\n", produtos[i].id, produtos[i].descricao, produtos[i].preco, produtos[i].estoque, produtos[i].id_evento, produtos[i].status);
    }
    fclose(fileProdutos);
    limparResumo();
    system("cls");
}

int listarProdutosVenda() {
    FILE *file;
    char filename[] = "data/produtos.txt";
    file = fopen(filename, "r");
    Produto produto;

    if (file == NULL) {
        centralizarFrase("Não foi possível abrir o arquivo.","error");
        return -1;
    }

    imprimirTituloCabecario("LISTA DE PRODUTOS", NULL);
    imprimirUsuarioEData();
    printf("| %-3s | %-75s | %-10s | %-15s |\n", "Cod", "Descricao", "Preco", "Estoque");
    imprimirLinhaDivisoria();

    for (int i = 0; i < MAX_PRODUTO; i++) {
        if (fscanf(file, "%d '%[^']' %lf %d %d %d", &produto.id, produto.descricao, &produto.preco, &produto.estoque, &produto.id_evento, &produto.status) != EOF) {
            int quantidade_vendida = 0;
            if (produto.id_evento == getUsuarioCompartilhado().id_evento && produto.status == 1) {

            for (int j = 0; j < MAX_RESUMO_VENDA; j++) {
                if (resumoVendas[j].id_produto == produto.id ) {
                    quantidade_vendida += resumoVendas[j].quantidade_produto;
                }
            }
            printf("| %-3d | %-75s | %-10.2f | %-15d |\n", produto.id, produto.descricao, produto.preco, produto.estoque - quantidade_vendida);
            };
        } else {
            break; // Se não houver mais produtos no arquivo, termina o loop
        }
    }
    imprimirLinhaDivisoria();
    fclose(file);
    return 0;
}