#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "moldes.h"

// Função interna para alocar um nó na memória
No* criar_no(char* url, char* data) {
    No* novo = (No*)malloc(sizeof(No));
    if (novo == NULL) {
        printf("Erro Crítico: Falha na alocação de memória!\n");
        exit(1);
    }
    strncpy(novo->dado.url, url, 2083);
    novo->dado.url[2083] = '\0';
    strncpy(novo->dado.data_hora, data, 19);
    novo->dado.data_hora[19] = '\0';
    novo->ant = NULL;
    novo->prox = NULL;
    return novo;
}

// Cria uma lista inicial padrão com 10 posições vazias
No* inicializar_lista_vazia() {
    No* cabeca = criar_no("[Vazio]", "--/--/---- --:--");
    No* atual = cabeca;
    for (int i = 1; i < 10; i++) {
        No* novo = criar_no("[Vazio]", "--/--/---- --:--");
        atual->prox = novo;
        novo->ant = atual;
        atual = novo;
    }
    return cabeca;
}

// Função: editar endereço
void editar_endereco(No* atual, char* nova_url, char* nova_data) {
    if (atual != NULL) {
        strncpy(atual->dado.url, nova_url, 2083);
        atual->dado.url[2083] = '\0';
        strncpy(atual->dado.data_hora, nova_data, 19);
        atual->dado.data_hora[19] = '\0';
        printf("\n[Sucesso] Endereço atualizado!\n");
    }
}

// Função: ir para o endereço (Avançar para o próximo)
No* ir_para_proximo(No* atual) {
    if (atual != NULL && atual->prox != NULL) {
        return atual->prox;
    }
    printf("\n[Aviso] Fim do histórico. Não há um próximo endereço.\n");
    return atual;
}

// Função: voltar ao endereço anterior
No* voltar_anterior(No* atual) {
    if (atual != NULL && atual->ant != NULL) {
        return atual->ant;
    }
    printf("\n[Aviso] Início do histórico. Não é possível voltar mais.\n");
    return atual;
}

// Grava exatamente os 10 nós atuais da lista no arquivo CSV
void salvar_csv(No* cabeca, char* nome_arquivo) {
    FILE* file = fopen(nome_arquivo, "w");
    if (!file) {
        printf("\n[Erro] Não foi possível salvar o arquivo CSV.\n");
        return;
    }
    No* temp = cabeca;
    int cont = 0;
    while (temp && cont < 10) {
        fprintf(file, "%s;%s\n", temp->dado.url, temp->dado.data_hora);
        temp = temp->prox;
        cont++;
    }
    fclose(file);
    printf("\n[Histórico guardado com sucesso em '%s']\n", nome_arquivo);
}

// Lê os dados do CSV. Garante que a lista gerada terá sempre 10 posições.
No* carregar_csv(char* nome_arquivo) {
    FILE* file = fopen(nome_arquivo, "r");
    if (!file) {
        // Se o arquivo não existir, gera um histórico limpo com 10 slots
        return inicializar_lista_vazia();
    }

    No *cabeca = NULL, *ultimo = NULL;
    char linha[2200];
    int cont = 0;

    while (fgets(linha, sizeof(linha), file) && cont < 10) {
        linha[strcspn(linha, "\n")] = 0; // Remove quebras de linha indesejadas
        
        char *url = strtok(linha, ";");
        char *data = strtok(NULL, ";");
        
        if (!url) url = "[Vazio]";
        if (!data) data = "--/--/---- --:--";

        No* novo = criar_no(url, data);
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

    // Se o arquivo CSV tiver menos de 10 registros, preenche o restante até completar 10
    while (cont < 10) {
        No* novo = criar_no("[Vazio]", "--/--/---- --:--");
        if (!cabeca) {
            cabeca = novo;
            ultimo = novo;
        } else {
            ultimo->prox = novo;
            novo->ant = ultimo;
            ultimo = novo;
        }
        cont++;
    }

    return cabeca;
}

// Mostra o estado visual da lista e onde o utilizador se encontra
void exibir_historico(No* cabeca, No* atual) {
    No* temp = cabeca;
    int i = 1;
    printf("\n========= HISTÓRICO DE NAVEGAÇÃO (MÁX 10) =========\n");
    while (temp) {
        if (temp == atual) {
            printf(" -> [%d] URL: %s \n        Acesso em: %s (VOCÊ ESTÁ AQUI)\n", i, temp->dado.url, temp->dado.data_hora);
        } else {
            printf("    [%d] URL: %s \n        Acesso em: %s\n", i, temp->dado.url, temp->dado.data_hora);
        }
        temp = temp->prox;
        i++;
    }
    printf("===================================================\n");
}