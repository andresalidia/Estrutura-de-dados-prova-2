#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
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
void ler_texto(char* url, int tamanho) {
    if (fgets(url, tamanho, stdin)) {
        url[strcspn(url, "\n")] = '\0';
    } else {
        url[0] = '\0';
    }
}

void obter_data_hora_atual(char* data_hora, int tamanho) {
    time_t agora = time(NULL);
    struct tm* momento = localtime(&agora);
    if (momento) {
        strftime(data_hora, tamanho, "%d/%m/%Y %H:%M", momento);
    } else {
        strncpy(data_hora, "--/--/---- --:--", tamanho - 1);
        data_hora[tamanho - 1] = '\0';
    }
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
    printf("\n[Aviso] Fim da Lista. Não há um próximo endereço.\n");
    return atual;
}

// Função: voltar ao endereço anterior
No* voltar_anterior(No* atual) {
    if (atual != NULL && atual->ant != NULL) {
        return atual->ant;
    }
    printf("\n[Aviso] Início da Lista. Não é possível voltar mais.\n");
    return atual;
}

// Grava todos os nós da lista no arquivo CSV
void salvar_csv(No* cabeca, char* nome_arquivo) {
    FILE* file = fopen(nome_arquivo, "w");
    if (!file) {
        printf("\n[Erro] Não foi possível salvar o arquivo CSV.\n");
        return;
    }
    No* temp = cabeca;
    while (temp) {
        fprintf(file, "%s;%s\n", temp->dado.url, temp->dado.data_hora);
        temp = temp->prox;
    }
    fclose(file);
}

// Lê os dados do CSV. Garante que a lista gerada terá sempre 10 posições.
No* carregar_csv(char* nome_arquivo) {
    No *cabeca = NULL, *ultimo = NULL;
    int cont = 0;
    FILE* file = fopen(nome_arquivo, "r");

    if (file) {
        char linha[2200];
        while (fgets(linha, sizeof(linha), file) && cont < 10) {
            linha[strcspn(linha, "\n")] = 0; // Remove quebras de linha indesejadas
            
            char *url = strtok(linha, ";");
            char *data = strtok(NULL, ";");
            
            if (!url) url = "";
            if (!data) data = "";

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
    } else {
        printf("\n[Aviso] Arquivo CSV não encontrado. Criando um histórico novo.\n");
    }

    // Preenche a lista até completar 10 nós caso o arquivo tenha menos ou não exista
    while (cont < 10) {
        No* novo = criar_no("Vazia", "--/--/---- --:--");
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

// Mostra o estado visual da lista e onde o utilizador se encontra
void exibir_historico(No* cabeca, No* atual) {
    No* temp = cabeca;
    int i = 1;
    printf("\n========= Lista de URLs =========\n");
    while (temp) {
        if (temp == atual) {
            printf(" -> [%d] URL: %s \n        Ultimo acesso em: %s\n", i, temp->dado.url, temp->dado.data_hora);
        } else {
            printf("    [%d] URL: %s \n        Ultimo acesso em: %s\n", i, temp->dado.url, temp->dado.data_hora);
        }
        temp = temp->prox;
        i++;
    }
    printf("==========================================\n");
}

// Função Inovação: Pesquisar por palavra-chave no histórico
void pesquisar_historico(No* cabeca) {
    char termo[100];
    printf("\nDigite o termo para pesquisa: ");
    ler_texto(termo, sizeof(termo));
    
    if (strlen(termo) == 0) return;

    printf("\n--- Resultados da Pesquisa por '%s' ---\n", termo);
    No* temp = cabeca;
    int i = 1;
    int encontrou = 0;
    
    while (temp) {
        // strstr procura se "termo" está dentro de "url". Ignora nós vazios.
        if (strstr(temp->dado.url, termo) != NULL && strcmp(temp->dado.url, "Vazia") != 0) {
            printf("    [%d] URL: %s \n        Ultimo acesso em: %s\n", i, temp->dado.url, temp->dado.data_hora);
            encontrou = 1;
        }
        temp = temp->prox;
        i++;
    }
    
    if (!encontrou) {
        printf("Nenhum registro encontrado.\n");
    }
    printf("---------------------------------------\n");
}

// Função Inovação: Limpa (formata) um único registro
void limpar_registro(No* no) {
    if (no != NULL) {
        strcpy(no->dado.url, "Vazia");
        strcpy(no->dado.data_hora, "--/--/---- --:--");
    }
}

// Função Inovação: Limpa todo o histórico de uma vez
void limpar_todo_historico(No* cabeca) {
    No* temp = cabeca;
    while (temp) {
        limpar_registro(temp);
        temp = temp->prox;
    }
}