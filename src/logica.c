#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/logica.h"
#include "../include/ui.h"

void pesquisar_historico(No *cabeca) {
    int op;
    printf("\n--- BUSCA E FILTROS INTELIGENTES ---\n");
    printf("1. Buscar por palavra-chave\n");
    printf("2. Filtrar por data (DD/MM/AAAA)\n");
    printf("3. Ver apenas Favoritos\n");
    printf("0. Voltar\n");
    printf("Escolha uma opção: ");
    if (scanf("%d", &op) != 1) op = 0;
    while (getchar() != '\n');
    if (op == 0) return;
    char termo[100];
    bool encontrou = false;
    No* temp = cabeca;
    int i = 1;
    switch (op) {
        case 1:
            printf("Digite a palavra-chave: "); ler_texto(termo, sizeof(termo));
            break;
        case 2:
            printf("Digite a data: "); ler_texto(termo, sizeof(termo));
            break;
    }
    while (temp) {
        bool match = false;
        if (strcmp(temp->dado.url, "Vazia") != 0) {
            if (op == 1 && strstr(temp->dado.url, termo)) match = true;
            else if (op == 2 && strstr(temp->dado.data_hora, termo)) match = true;
            else if (op == 3 && temp->dado.favorito) match = true;
        }
        if (match) {
            printf("    [%d] URL: %s\n", i, temp->dado.url);
            encontrou = true;
        }
        temp = temp->prox; i++;
    }
    if (!encontrou) printf("Nenhum registro encontrado.\n");
}

void exibir_historico_ordenado(No *cabeca, int tipo) {
    No *itens[10];
    No *temp = cabeca;
    for (int i = 0; i < 10; i++) {
        itens[i] = temp;
        temp = temp->prox;
    }
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9 - i; j++) {
            bool trocar = false;
            if (tipo == 1) { if (strcmp(itens[j]->dado.url, itens[j+1]->dado.url) > 0) trocar = true; }
            else if (tipo == 2) { if (itens[j]->dado.acessos < itens[j+1]->dado.acessos) trocar = true; }
            if (trocar) { No *aux = itens[j]; itens[j] = itens[j+1]; itens[j+1] = aux; }
        }
    }
    printf("\n========= Histórico Ordenado =========\n");
    for (int i = 0; i < 10; i++) {
        if (strcmp(itens[i]->dado.url, "Vazia") != 0)
            printf("[%d] URL: %s | Visitas: %d\n", i + 1, itens[i]->dado.url, itens[i]->dado.acessos);
    }
}

void alternar_favorito(No *atual) {
    if (atual && strcmp(atual->dado.url, "Vazia") != 0) {
        atual->dado.favorito = !atual->dado.favorito;
        printf("\n[Sucesso] Status de favorito alterado!\n");
    }
}

void serializar_tags(Item *item, char *tags_str) {
    tags_str[0] = '\0';
    for (int i = 0; i < 3; i++) {
        strcat(tags_str, item->tags[i]);
        if (i < 2) strcat(tags_str, "|");
    }
}

void desserializar_tags(char *tags_str, Item *item) {
    char temp[200]; strncpy(temp, tags_str, 199); temp[199] = '\0';
    char *token = strtok(temp, "|");
    int idx = 0;
    while (token != NULL && idx < 3) {
        strncpy(item->tags[idx], token, 49);
        token = strtok(NULL, "|"); idx++;
    }
    while (idx < 3) item->tags[idx++][0] = '\0';
}