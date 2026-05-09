#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>

typedef struct {
    char url[2084];
    char data_hora[20];
    bool favorito;
    int acessos;
    char tags[3][50];
} Item;

typedef struct no {
    Item dado;
    struct no *ant;
    struct no *prox;
} No;

No* criar_no(char* url, char* data, bool fav);
void editar_endereco(No* atual, char* nova_url, char* nova_data);
No* ir_para_proximo(No* atual);
No* voltar_anterior(No* atual);
void limpar_registro(No* no);
void limpar_todo_historico(No* cabeca);

#endif