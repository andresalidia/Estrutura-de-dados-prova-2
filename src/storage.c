#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/storage.h"
#include "../include/logica.h"

void salvar_csv(No *cabeca, char *nome_arquivo) {
    char path[150];
    snprintf(path, sizeof(path), "data/%s", nome_arquivo);
    
    FILE *file = fopen(path, "w");
    if (!file) {
        return;
    }
    No *temp = cabeca;
    while (temp) {
        char tags_str[200] = "";
        serializar_tags(&temp->dado, tags_str);

        fprintf(file, "%s;%s;%d;%d;%s\n",
                temp->dado.url,
                temp->dado.data_hora,
                temp->dado.favorito ? 1 : 0,
                temp->dado.acessos,
                tags_str);
        temp = temp->prox;
    }
    fclose(file);
}

No *carregar_csv(char *nome_arquivo) {
    char path[150];
    snprintf(path, sizeof(path), "data/%s", nome_arquivo);
    
    No *cabeca = NULL, *ultimo = NULL;
    int cont = 0;
    FILE *file = fopen(path, "r");

    if (file) {
        char linha[2200];
        while (fgets(linha, sizeof(linha), file) && cont < 10) {
            linha[strcspn(linha, "\n")] = 0;

            char *url = strtok(linha, ";");
            char *data = strtok(NULL, ";");
            char *fav_str = strtok(NULL, ";");
            char *acessos_str = strtok(NULL, ";");
            char *tags_str = strtok(NULL, ";");

            if (!url) url = "Vazia";
            if (!data) data = "--/--/---- --:--";
            bool fav = (fav_str && atoi(fav_str) == 1) ? true : false;
            int ac = (acessos_str) ? atoi(acessos_str) : 0;

            No *novo = criar_no(url, data, fav);
            novo->dado.acessos = ac;

            if (tags_str && strlen(tags_str) > 0) {
                desserializar_tags(tags_str, &novo->dado);
            }

            if (!cabeca) {
                cabeca = novo;
            } else {
                ultimo->prox = novo;
                novo->ant = ultimo;
            }
            ultimo = novo;
            cont++;
        }
        fclose(file);
    }

    while (cont < 10) {
        No *novo = criar_no("Vazia", "--/--/---- --:--", false);
        if (!cabeca) {
            cabeca = novo;
        } else {
            ultimo->prox = novo;
            novo->ant = ultimo;
        }
        ultimo = novo;
        cont++;
    }

    return cabeca;
}

No *carregar_sessao(char *nome_sessao) {
    char nome_arquivo[100];
    snprintf(nome_arquivo, sizeof(nome_arquivo), "history_%s.csv", nome_sessao);
    return carregar_csv(nome_arquivo);
}

void salvar_sessao(No *cabeca, char *nome_sessao) {
    char nome_arquivo[100];
    snprintf(nome_arquivo, sizeof(nome_arquivo), "history_%s.csv", nome_sessao);
    salvar_csv(cabeca, nome_arquivo);
}