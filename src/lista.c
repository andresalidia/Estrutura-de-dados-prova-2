#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/lista.h"

No *criar_no(char *url, char *data, bool fav) {
    No *novo = (No *)malloc(sizeof(No));
    if (novo == NULL) {
        printf("Erro Crítico: Falha na alocação de memória!\n");
        exit(1);
    }
    strncpy(novo->dado.url, url, 2083);
    novo->dado.url[2083] = '\0';
    strncpy(novo->dado.data_hora, data, 19);
    novo->dado.data_hora[19] = '\0';
    novo->dado.favorito = fav;
    novo->dado.acessos = (strcmp(url, "Vazia") == 0) ? 0 : 1;

    for (int i = 0; i < 3; i++) {
        novo->dado.tags[i][0] = '\0';
    }

    novo->ant = NULL;
    novo->prox = NULL;
    return novo;
}

void editar_endereco(No *atual, char *nova_url, char *nova_data) {
    if (atual != NULL) {
        strncpy(atual->dado.url, nova_url, 2083);
        atual->dado.url[2083] = '\0';
        strncpy(atual->dado.data_hora, nova_data, 19);
        atual->dado.data_hora[19] = '\0';
        atual->dado.acessos++;
        printf("\n[Sucesso] Endereço atualizado!\n");
    }
}

No *ir_para_proximo(No *atual) {
    if (atual != NULL && atual->prox != NULL) {
        atual->prox->dado.acessos++;
        return atual->prox;
    }
    printf("\n[Aviso] Fim da Lista. Não há um próximo endereço.\n");
    return atual;
}

No *voltar_anterior(No *atual) {
    if (atual != NULL && atual->ant != NULL) {
        atual->ant->dado.acessos++;
        return atual->ant;
    }
    printf("\n[Aviso] Início da Lista. Não é possível voltar mais.\n");
    return atual;
}

void limpar_registro(No *no) {
    if (no != NULL) {
        strcpy(no->dado.url, "Vazia");
        strcpy(no->dado.data_hora, "--/--/---- --:--");
        no->dado.favorito = false;
        no->dado.acessos = 0;
        for (int i = 0; i < 3; i++) {
            no->dado.tags[i][0] = '\0';
        }
    }
}

void limpar_todo_historico(No *cabeca) {
    No *temp = cabeca;
    while (temp) {
        limpar_registro(temp);
        temp = temp->prox;
    }
}