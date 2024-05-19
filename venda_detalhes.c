#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "venda_detalhes.h"
#include "menu.h"
#include "evento.h"
#include "components.h"

void salvarVendaDetalhes(Venda_detalhes venda_detalhes) {
    FILE *file;
    char filename[] = "data/vendas_detalhes.txt";
    file = fopen(filename, "a"); // Abrir o arquivo em modo de escrita, acrescentando ao final

    if (file != NULL) {
        fprintf(file, "%d %d %d %d '%s' %d %f\n", venda_detalhes.id, venda_detalhes.id_venda, venda_detalhes.id_produto, venda_detalhes.id_evento,
                venda_detalhes.descricao_produto, venda_detalhes.quantidade_produto, venda_detalhes.valor_produto);
        fclose(file);
        printf("|         --------        Venda salva com sucesso!        --------        |\n");
    } else {
        printf("Erro ao abrir o arquivo %s.\n", filename);
    }
}

int relatorioVendaEspecificoAux() {
    int escolhaIdRelatorio = 0;
    int idMax = carregarUltimoEvento();

    do {
        system("cls");
        listarEventos();
        printf("|\tEscolha o codigo do evento que deseja ver o relatorio (ou digite 0 para SAIR): ");
        scanf("%d", &escolhaIdRelatorio);

        switch (escolhaIdRelatorio) {
            case 0:
                relatorioVendasAux();
                break;
            default:
                if (escolhaIdRelatorio < 1 || escolhaIdRelatorio >= idMax) {
                    opcaoInvalida();
                } else {
                    relatorioVendaEspecifico("vendas_detalhes.txt", escolhaIdRelatorio, idMax);
                }
        }
    } while (escolhaIdRelatorio != 0 && (escolhaIdRelatorio < 1 || escolhaIdRelatorio >= idMax));

    return 0;
}

void criteriosOrdenacao() {
    char criterio[15];
    char ordem[15];

    imprimirTituloCabecario("ESCOLHA O CRITERIO DE ORDENACAO",NULL);
    printf("|\t1. ID do Produto                                                                                           |\n");
    printf("|\t2. Quantidade de Produtos Vendidos                                                                         |\n");
    int criterioOpcao;
    imprimirLinhaDivisoria();
    printf("|\tEscolha uma opcao: ");
    scanf("%d", &criterioOpcao);
    imprimirLinhaDivisoria();

    if (criterioOpcao == 1) {
        strcpy(criterio, "id");
    } else if (criterioOpcao == 2) {
        strcpy(criterio, "quantidade");
    } else {
        printf("Opcao invalida. Usando 'id' como padrao.\n");
        strcpy(criterio, "id");
        system("PAUSE");
    }

    imprimirTituloCabecario("ESCOLHA A ORDEM DE ORDENACAO",NULL);
    printf("|\t1. Crescente                                                                                               |\n");
    printf("|\t2. Decrescente                                                                                             |\n");
    int ordemOpcao;
    printf("|\tEscolha uma opcao: ");
    scanf("%d", &ordemOpcao);

    if (ordemOpcao == 1) {
        strcpy(ordem, "crescente");
    } else if (ordemOpcao == 2) {
        strcpy(ordem, "decrescente");
    } else {
        printf("Opcao invalida. Usando 'crescente' como padrao.\n");
        strcpy(ordem, "crescente");
        system("PAUSE");
    }
    system("cls");
    relatorioVendasGeral(criterio, ordem);
}

void relatorioVendasAux(){
    int opcaoEvento = 999;
    while(opcaoEvento != 0) {
    system("cls");
        imprimirRodape();
        imprimirTituloCabecario("ESCOLHA UMA OPCAO DE RELATORIO", NULL);
        printf("| Opcao |   Descricao                                                                                              |\n");
        imprimirLinhaDivisoria();
        printf("|   1   |   Relatorio Especifico                                                                                   |\n");
        printf("|   2   |   Relatorio Geral                                                                                        |\n");
        imprimirLinhaDivisoria();
        printf("|   0   |   Menu administrativo                                                                                    |\n");
        imprimirLinhaDivisoria();
        printf("|\tEscolha uma opcao:");

        scanf("%d", &opcaoEvento);
        switch (opcaoEvento) {
            case 1:
                system("cls");
                relatorioVendaEspecificoAux();
                system("PAUSE");
                break;
            case 2: {
                system("cls");
                criteriosOrdenacao();
                break;
            }
            case 0:
                system("cls");
                printf("Saindo da tela de relatorio...\n");
                menuAdministrador();
            default:
                opcaoInvalida();
        }
    }
}


int relatorioVendaEspecifico(const char *nomeArquivo, int opcao, int idMaximo) {

    char caminhoArquivo[100];
    strcpy(caminhoArquivo, "data/");
    strcat(caminhoArquivo, nomeArquivo);
    FILE *file = fopen(caminhoArquivo, "r");

    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        //return 0;
    }

    char *nomeEvento = obterNomeEvento("eventos.txt", opcao);
    if (nomeEvento == NULL) {
        nomeEvento = (char*)malloc(strlen("Nada encontrado") + 1);
        if (nomeEvento != NULL) {
            strcpy(nomeEvento, "Nada encontrado");
        } else {
            perror("Erro ao alocar memória para 'Nada encontrado'");
        }
    }

        Venda_detalhes venda_detalhes;
        double accTotal = 0;
        int accQtd = 0;
        int encontrouVendas = 0;

        // Imprimir cabeçalho da tabela
        system("cls");

    imprimirRodape();
    imprimirTituloCabecario("RELATORIO ESPECIFICO DAS VENDAS", nomeEvento);
        printf("| %-15s | %-63s | %-10s | %-6s | %-6s |\n", "ID_Produto", "Produto", "Quantidade", "Valor", "Total");
        imprimirLinhaDivisoria();

    // Ler e exibir cada linha do arquivo
    while (fscanf(file, "%d %d %d %d '%50[^']' %d %lf", &venda_detalhes.id, &venda_detalhes.id_venda,
                  &venda_detalhes.id_produto, &venda_detalhes.id_evento, venda_detalhes.descricao_produto, &venda_detalhes.quantidade_produto,
                  &venda_detalhes.valor_produto) != EOF) {
        if (venda_detalhes.id_evento == opcao) {
            encontrouVendas = 1;
            accTotal += (venda_detalhes.quantidade_produto * venda_detalhes.valor_produto);
            accQtd += venda_detalhes.quantidade_produto;
            printf("| %-15d | %-63s | %-10d | %-6.2lf | %-6.2lf | \n",
                   venda_detalhes.id_produto, venda_detalhes.descricao_produto, venda_detalhes.quantidade_produto,
                   venda_detalhes.valor_produto,
                   venda_detalhes.quantidade_produto * venda_detalhes.valor_produto);
        }
    }

    if (!encontrouVendas) {
        imprimirLinhaDivisoria();
        printf("| Nenhuma venda encontrada para o evento especificado.                                                   |\n");
        imprimirLinhaDivisoria();
    } else {
        imprimirLinhaDivisoria();
        printf("|                       --------     TOTAL GERAL     --------                       |  QTD   %-3d |  R$     %6.2lf  |\n", accQtd ,accTotal);
        imprimirLinhaDivisoria();

    }
    fclose(file);
    system("PAUSE");
    relatorioVendaEspecificoAux();
}

int compararPorIdCrescente(const void *a, const void *b) {
    return ((Venda_detalhes*)a)->id_produto - ((Venda_detalhes*)b)->id_produto;
}

int compararPorIdDecrescente(const void *a, const void *b) {
    return ((Venda_detalhes*)b)->id_produto - ((Venda_detalhes*)a)->id_produto;
}

int compararPorQuantidadeCrescente(const void *a, const void *b) {
    return ((Venda_detalhes*)a)->quantidade_produto - ((Venda_detalhes*)b)->quantidade_produto;
}

int compararPorQuantidadeDecrescente(const void *a, const void *b) {
    return ((Venda_detalhes*)b)->quantidade_produto - ((Venda_detalhes*)a)->quantidade_produto;
}

int relatorioVendasGeral(char* criterio, char* ordem) {
    FILE *file;
    char filename[] = "data/vendas_detalhes.txt";
    file = fopen(filename, "r");

    if (file != NULL) {
        // Imprimir cabeçalho da tabela
        imprimirRodape();
        imprimirTituloCabecario("RELATORIO GERAL DAS VENDAS", NULL);
        printf("| %-15s | %-63s | %-10s | %-6s | %-6s |\n", "ID_Produto", "Produto", "Quantidade", "Valor", "Total");
        imprimirLinhaDivisoria();

        fseek(file, 0, SEEK_END);
        if (ftell(file) == 0) {
            imprimirLinhaDivisoria();
            printf("|\tNenhuma venda encontrada.                                                                         |\n");
            imprimirLinhaDivisoria();
            fclose(file);
            return 0;
        }
        rewind(file);

        Venda_detalhes vendas[1000];
        int count = 0;

        while (fscanf(file, "%d %d %d %d '%50[^']' %d %lf", &vendas[count].id, &vendas[count].id_venda,
                      &vendas[count].id_produto, &vendas[count].id_evento, vendas[count].descricao_produto,
                      &vendas[count].quantidade_produto, &vendas[count].valor_produto) != EOF) {
            count++;
        }
        fclose(file);

        if (strcmp(criterio, "id") == 0) {
            if (strcmp(ordem, "crescente") == 0) {
                qsort(vendas, count, sizeof(Venda_detalhes), compararPorIdCrescente);
            } else {
                qsort(vendas, count, sizeof(Venda_detalhes), compararPorIdDecrescente);
            }
        } else if (strcmp(criterio, "quantidade") == 0) {
            if (strcmp(ordem, "crescente") == 0) {
                qsort(vendas, count, sizeof(Venda_detalhes), compararPorQuantidadeCrescente);
            } else {
                qsort(vendas, count, sizeof(Venda_detalhes), compararPorQuantidadeDecrescente);
            }
        }

        double accTotal = 0;
        int accQtd = 0;

        for (int i = 0; i < count; i++) {
            accTotal += (vendas[i].quantidade_produto * vendas[i].valor_produto);
            accQtd += vendas[i].quantidade_produto;
            printf("| %-15d | %-63s | %-10d | %-6.2lf | %-6.2lf | \n",
                   vendas[i].id_produto, vendas[i].descricao_produto, vendas[i].quantidade_produto,
                   vendas[i].valor_produto,
                   vendas[i].quantidade_produto * vendas[i].valor_produto);
        }

        imprimirLinhaDivisoria();
        printf("|                       --------     TOTAL GERAL     --------                       |  QTD   %-3d |  R$     %6.2lf  |\n", accQtd ,accTotal);
        imprimirLinhaDivisoria();
        // Opção para alterar a ordenação
        imprimirTituloCabecario("Digite 1 para alterar a ordenacao ou 0 para sair ",NULL);
        int opcaoOrdenacao;
        scanf("%d", &opcaoOrdenacao);
        if (opcaoOrdenacao == 1) {
            system("cls");
            criteriosOrdenacao();
        }
    } else {
        printf("Não foi possível abrir o arquivo %s.\n\n", filename);
    }
    return 0;
}


int carregarUltimaVendaDetalhes() {
    FILE *file;
    char filename[] = "data/vendas_detalhes.txt";
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
        //printf("\tRegisto %d\n", contador_linhas);
    } else {
        printf("Erro ao abrir o arquivo %s.\n", filename);
    }

    return contador_linhas+1;
}

