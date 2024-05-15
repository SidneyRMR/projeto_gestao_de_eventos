#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "venda_detalhes.h"
#include "menu.h"
#include "evento.h"

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
                    printf("|\tOpção inválida. Por favor, escolha um código de evento válido.\n");
                } else {
                    relatorioVendaEspecifico("vendas_detalhes.txt", escolhaIdRelatorio, idMax);
                }
        }
    } while (escolhaIdRelatorio != 0 && (escolhaIdRelatorio < 1 || escolhaIdRelatorio >= idMax));

    return 0;
}


void relatorioVendasAux(){
    int opcaoEvento = 999;
    while(opcaoEvento != 0) {
    system("cls");
        printf("|--------------------------------------------------------------------------------------------------------|\n");
        printf("|                                     ESCOLHA UMA OPCAO DE RELATORIO                                     |\n");
        printf("|--------------------------------------------------------------------------------------------------------|\n");
        printf("| Opcao |   Descricao                                                                                    |\n");
        printf("|--------------------------------------------------------------------------------------------------------|\n");
        printf("|    1  |   Relatorio Especifico                                                                         |\n");
        printf("|    2  |   Relatorio Geral                                                                              |\n");
        printf("|--------------------------------------------------------------------------------------------------------|\n");
        printf("|    0  |   Menu administrativo                                                                          |\n");
        printf("|--------------------------------------------------------------------------------------------------------|\n");
        printf("|\tEscolha uma opcao:");

        scanf("%d", &opcaoEvento);
        switch (opcaoEvento) {
            case 1:
                system("cls");
                relatorioVendaEspecificoAux();
                system("PAUSE");
                break;
            case 2:
                system("cls");
                relatorioVendasGeral();
                system("PAUSE");
                break;
            case 0:
                system("cls");
                printf("Saindo da tela de relatorio...\n");
                menuAdministrador();
            default:
                printf("Opcao invalida.\n");
        }
    }
}

// TODO - ajustar layout
int relatorioVendaEspecifico(const char *nomeArquivo, int opcao, int idMaximo) {
    char caminhoArquivo[100]; // Ajuste o tamanho conforme necessário
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
        printf("|--------------------------------------------------------------------------------------------------------|\n");
        printf("|                          RELATORIO ESPECIFICO DAS VENDAS - %-15s                             |\n", nomeEvento);
        printf("|--------------------------------------------------------------------------------------------------------|\n");
        printf("| %-3s | %-7s | %-7s | %-5s | %-29s | %-10s | %-6s | %-6s |\n", "Cod", "ID_Venda", "ID_Produto", "ID_Evento", "Produto", "Quantidade", "Valor", "Total");
        printf("|-----|----------|------------|-----------|-------------------------------|------------|--------|--------|\n");

    // Ler e exibir cada linha do arquivo
    while (fscanf(file, "%d %d %d %d '%50[^']' %d %lf", &venda_detalhes.id, &venda_detalhes.id_venda,
                  &venda_detalhes.id_produto, &venda_detalhes.id_evento, venda_detalhes.descricao_produto, &venda_detalhes.quantidade_produto,
                  &venda_detalhes.valor_produto) != EOF) {
        if (venda_detalhes.id_evento == opcao) {
            encontrouVendas = 1;
            accTotal += (venda_detalhes.quantidade_produto * venda_detalhes.valor_produto);
            accQtd += venda_detalhes.quantidade_produto;
            printf("| %-3d | %-8d | %-10d | %-9d | %-29s | %-10d | %-6.2lf | %-6.2lf | \n",
                   venda_detalhes.id, venda_detalhes.id_venda, venda_detalhes.id_produto, venda_detalhes.id_evento,
                   venda_detalhes.descricao_produto, venda_detalhes.quantidade_produto,
                   venda_detalhes.valor_produto,
                   venda_detalhes.quantidade_produto * venda_detalhes.valor_produto);
        }
    }

    if (!encontrouVendas) {
        printf("|--------------------------------------------------------------------------------------------------------|\n");
        printf("| Nenhuma venda encontrada para o evento especificado.                                                   |\n");
        printf("|--------------------------------------------------------------------------------------------------------|\n");
    } else {
        printf("|--------------------------------------------------------------------------------------------------------|\n");
        printf("|                    ------     TOTAL GERAL     ------                   |  QTD   %-3d |     R$   %6.2lf  |\n", accQtd ,accTotal);
        printf("|--------------------------------------------------------------------------------------------------------|\n");

    }
    fclose(file);
    system("PAUSE");
    relatorioVendaEspecificoAux();
}

// TODO - ajustar layout
int relatorioVendasGeral() {
    FILE *file;
    char filename[] = "data/vendas_detalhes.txt";
    file = fopen(filename, "r");

    if (file != NULL) {
        // Imprimir cabeçalho da tabela
        printf("|--------------------------------------------------------------------------------------------------------|\n");
        printf("|                                       RELATORIO GERAL DAS VENDAS                                       |\n");
        printf("|--------------------------------------------------------------------------------------------------------|\n");
        printf("| %-3s | %-7s | %-7s | %-5s | %-29s | %-10s | %-6s | %-6s |\n", "Cod", "ID_Venda", "ID_Produto", "ID_Evento", "Produto", "Quantidade", "Valor", "Total");
        printf("|-----|----------|------------|-----------|-------------------------------|------------|--------|--------|\n");

        fseek(file, 0, SEEK_END);
        if (ftell(file) == 0) {
            printf("|--------------------------------------------------------------------------------------------------------|\n");
            printf("|\tNenhuma venda encontrada.                                                                         |\n");
            printf("|--------------------------------------------------------------------------------------------------------|\n");
            fclose(file);
            return 0;
        }
        rewind(file);

        Venda_detalhes venda_detalhes;
        double accTotal = 0;
        int accQtd = 0;

        // Ler e exibir cada linha do arquivo
        while (fscanf(file, "%d %d %d %d '%50[^']' %d %lf", &venda_detalhes.id, &venda_detalhes.id_venda,
                      &venda_detalhes.id_produto, &venda_detalhes.id_evento, venda_detalhes.descricao_produto,
                      &venda_detalhes.quantidade_produto, &venda_detalhes.valor_produto) != EOF) {
            accTotal += (venda_detalhes.quantidade_produto * venda_detalhes.valor_produto);
            accQtd += venda_detalhes.quantidade_produto;
            printf("| %-3d | %-8d | %-10d | %-9d | %-29s | %-10d | %-6.2lf | %-6.2lf | \n",
                   venda_detalhes.id, venda_detalhes.id_venda, venda_detalhes.id_produto, venda_detalhes.id_evento,
                   venda_detalhes.descricao_produto, venda_detalhes.quantidade_produto, venda_detalhes.valor_produto,
                   venda_detalhes.quantidade_produto * venda_detalhes.valor_produto);
        }
        printf("|--------------------------------------------------------------------------------------------------------|\n");
        printf("|                    ------     TOTAL GERAL     ------                   |  QTD   %-3d |     R$   %6.2lf  |\n", accQtd ,accTotal);
        printf("|--------------------------------------------------------------------------------------------------------|\n");

        fclose(file);
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

