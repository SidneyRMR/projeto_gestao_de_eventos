#include <stdio.h>
#include <string.h>
#include "evento.h"
#include "menu.h"
#include "components.h"

// Definição da estrutura para armazenar os dados do evento
void criarEvento() {
    Evento evento;
    char dataAtual[11];
    int p_status = 1;

    // Solicitar ao usuário que insira os dados do evento
    imprimirTituloCabecarioDuplo("TELA DE CADASTRO DE EVENTOS",NULL);

    char *p_evento = centralizarEObterValorChar("Digite o nome do evento: ", 21);
    char *p_descricao = centralizarEObterValorChar("Digite uma descricao para o evento: ", 51);

    imprimirLinhaDivisoria();

    // Preencher a estrutura do evento com os dados inseridos
    evento.id = carregarUltimoEvento() ; // Incrementar o ID do último evento
    strcpy(evento.evento, p_evento);
    strcpy(evento.descricao, p_descricao);
    obterDataAtual(dataAtual);
    strcpy(evento.data, dataAtual);
    evento.status = p_status;

    salvarEvento(evento);
}

void listarEventos() {
    FILE *file;
    char filename[] = "data/eventos.txt";
    file = fopen(filename, "r");

    if (file != NULL) {

        imprimirTituloCabecarioDuplo("LISTA DE EVENTOS", NULL);
        imprimirUsuarioEData();

        printf("| %-3s | %-20s | %-57s | %-10s | %-10s |\n", "Cod", "Evento", "Descricao", "Data", "Status");
        imprimirLinhaDivisoria();

        // Variável para armazenar cada registro lido do arquivo
        Evento evento;

        // Ler e exibir cada linha do arquivo
        while (fscanf(file, "%d '%[^']' '%[^']' %s %d", &evento.id, evento.evento, evento.descricao, evento.data, &evento.status) != EOF) {
            char status[10];
            if(evento.id == 0) continue;
            if(evento.status == 1){
                strcpy(status, "Ativo");
            } else {
                strcpy(status, "Desativo");
            }
            printf("| %-3d | %-20s | %-57s | %-10s | %-10s |\n", evento.id, evento.evento, evento.descricao, evento.data, status);
        }
        imprimirLinhaDivisoria();
        fclose(file);
    } else {
        printf("Não foi possível abrir o arquivo %s.\n\n", filename);
    }
}

void listarEventosCadastro() {
    FILE *file;
    char filename[] = "data/eventos.txt";
    file = fopen(filename, "r");

    if (file != NULL) {
        imprimirTituloCabecarioLista("LISTA DE EVENTOS", NULL);
        char linha[80];  // Buffer para armazenar a linha completa
        snprintf(linha, sizeof(linha), "| %-4s | %-21s |", "Cod", "Evento");
        centralizarFraseSemBorda(linha);
        imprimirLinhaDivisoriaLista();

        // Variável para armazenar cada registro lido do arquivo
        Evento evento;

        // Ler e exibir cada linha do arquivo
        while (fscanf(file, "%d '%[^']' '%[^']' %s %d", &evento.id, evento.evento, evento.descricao, evento.data, &evento.status) != EOF) {
            if (evento.id == 0 || evento.status == 0) {
                continue;
            }
              // Buffer para armazenar a linha completa
            snprintf(linha, sizeof(linha), "| %-4d | %-21s |", evento.id, evento.evento);
            centralizarFraseSemBorda(linha);
        }

        imprimirLinhaDivisoriaLista();
        fclose(file);
    } else {
        printf("Não foi possível abrir o arquivo %s.\n\n", filename);
    }
}

int carregarUltimoEvento() {
    FILE *file;
    char filename[] = "data/eventos.txt";
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
        //printf("|\tRegistro(s): %d\n", contador_linhas);
    } else {
        printf("Erro ao abrir o arquivo %s.\n", filename);
    }

    return contador_linhas;
}

void salvarEvento(Evento evento) {
    FILE *file;
    char filename[] = "data/eventos.txt";
    file = fopen(filename, "a"); // Abrir o arquivo em modo de escrita, acrescentando ao final

    if (file != NULL) {
        fprintf(file, "%d '%s' '%s' %s %d\n", evento.id, evento.evento, evento.descricao, evento.data, evento.status);
        fclose(file);
        centralizarFrase("Evento salvo com sucesso!");
    } else {
        printf("Erro ao abrir o arquivo %s.\n", filename);
    }
}

Evento carregarEventoPorID(int id) {
    FILE *file;
    char filename[] = "data/eventos.txt";
    Evento evento;

    file = fopen(filename, "r");
    if (file != NULL) {
        while (fscanf(file, "%d '%[^']' '%[^']' %s %d", &evento.id, evento.evento, evento.descricao, evento.data, &evento.status) != EOF) {
            if (evento.id == id) {
                fclose(file);
                return evento;
            }
        }
        fclose(file);
    } else {
        printf("Erro ao abrir o arquivo %s.\n", filename);
    }

    // Retornar um produto vazio caso não seja encontrado
    Evento eventoNaoEncontrado = {0, "", "", "", 0};
    return eventoNaoEncontrado;
}