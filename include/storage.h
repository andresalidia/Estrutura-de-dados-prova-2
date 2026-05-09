#ifndef STORAGE_H
#define STORAGE_H

#include "lista.h"

typedef struct {
    char nome_sessao[50];
} Sessao;

void salvar_csv(No* cabeca, char* nome_arquivo);
No* carregar_csv(char* nome_arquivo);
No* carregar_sessao(char* nome_sessao);
void salvar_sessao(No* cabeca, char* nome_sessao);

#endif