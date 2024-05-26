#ifndef EVENTO_H
#define EVENTO_H

typedef struct {
    int id;
    char evento[21];
    char descricao[51];
    char data[11];
    int status;
} Evento;
int EditarNomeEvento(int idEvento);
int EditarDescricaoEvento(int idEvento);
int DesativarEvento(int idEvento);
void criarEvento();

void listarEventos();

int carregarUltimoEvento();

void salvarEvento(Evento evento);

void listarEventosCadastro();

Evento carregarEventoPorID(int id);

#endif // EVENTO_H