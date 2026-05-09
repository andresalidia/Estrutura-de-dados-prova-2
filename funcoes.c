/******************************************************************************
 * PROJETO: Navegador de Histórico (Lista Duplamente Encadeada)
 * DISCIPLINA: Estrutura de Dados
 * DATA DE ENTREGA: 10/05/2026
 * DESCRIÇÃO: Implementação das funções de manipulação da lista e arquivos.
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "funcoes.h"

No* criar_no(char* url, char* data, bool fav) {
    No* novo = (No*)malloc(sizeof(No));
    if (novo == NULL) {
        printf("Erro Crítico: Falha na alocação de memória!\n");
        exit(1);
    }
    strncpy(novo->dado.url, url, 2083);
    novo->dado.url[2083] = '\0';
    strncpy(novo->dado.data_hora, data, 19);
    novo->dado.data_hora[19] = '\0';
    novo->dado.favorito = fav;
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
    
void editar_endereco(No* atual, char* nova_url, char* nova_data) {
    if (atual != NULL) {
        strncpy(atual->dado.url, nova_url, 2083);
        atual->dado.url[2083] = '\0';
        strncpy(atual->dado.data_hora, nova_data, 19);
        atual->dado.data_hora[19] = '\0';
        printf("\n[Sucesso] Endereço atualizado!\n");
    }
}

No* ir_para_proximo(No* atual) {
    if (atual != NULL && atual->prox != NULL) {
        return atual->prox;
    }
    printf("\n[Aviso] Fim da Lista. Não há um próximo endereço.\n");
    return atual;
}

No* voltar_anterior(No* atual) {
    if (atual != NULL && atual->ant != NULL) {
        return atual->ant;
    }
    printf("\n[Aviso] Início da Lista. Não é possível voltar mais.\n");
    return atual;
}

void salvar_csv(No* cabeca, char* nome_arquivo) {
    FILE* file = fopen(nome_arquivo, "w");
    if (!file) {
        printf("\n[Erro] Não foi possível salvar o arquivo CSV.\n");
        return;
    }
    No* temp = cabeca;
    while (temp) {
        fprintf(file, "%s;%s;%d\n", temp->dado.url, temp->dado.data_hora, temp->dado.favorito ? 1 : 0);
        temp = temp->prox;
    }
    fclose(file);
}

No* carregar_csv(char* nome_arquivo) {
    No *cabeca = NULL, *ultimo = NULL;
    int cont = 0;
    FILE* file = fopen(nome_arquivo, "r");

    if (file) {
        char linha[2200];
        while (fgets(linha, sizeof(linha), file) && cont < 10) {
            linha[strcspn(linha, "\n")] = 0; 
            
            char *url = strtok(linha, ";");
            char *data = strtok(NULL, ";");
            char *fav_str = strtok(NULL, ";");
            
            if (!url) url = "Vazia";
            if (!data) data = "--/--/---- --:--";
            bool fav = (fav_str && atoi(fav_str) == 1) ? true : false;

            No* novo = criar_no(url, data, fav);
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

    while (cont < 10) {
        No* novo = criar_no("Vazia", "--/--/---- --:--", false);
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

void exibir_historico(No* cabeca, No* atual) {
    int pos_atual = 1;
    No* temp_pos = cabeca;
    while (temp_pos && temp_pos != atual) {
        pos_atual++;
        temp_pos = temp_pos->prox;
    }

    int pagina = (pos_atual <= 5) ? 1 : 2;
    int inicio = (pagina == 1) ? 1 : 6;
    int fim = (pagina == 1) ? 5 : 10;

    printf("\n========= Histórico de URLs (Página %d/2) =========\n", pagina);
    
    No* temp = cabeca;
    for (int i = 1; i <= 10; i++) {
        if (i >= inicio && i <= fim) {
            char *marcador = (temp == atual) ? " ->" : "   ";
            char *estrela = (temp->dado.favorito) ? " [\xe2\x98\x85]" : ""; // Estrela Unicode
            
            printf("%s [%d]%s URL: %s\n        Último acesso em: %s\n", 
                   marcador, i, estrela, temp->dado.url, temp->dado.data_hora);
        }
        temp = temp->prox;
    }
    printf("===================================================\n");
}

void pesquisar_historico(No* cabeca) {
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
            printf("Digite a palavra-chave: ");
            ler_texto(termo, sizeof(termo));
            printf("\n--- Resultados (Palavra: %s) ---\n", termo);
            break;
        case 2:
            printf("Digite a data (ex: 09/05/2026): ");
            ler_texto(termo, sizeof(termo));
            printf("\n--- Resultados (Data: %s) ---\n", termo);
            break;
        case 3:
            printf("\n--- Meus Favoritos ---\n");
            break;
        default:
            return;
    }

    while (temp) {
        bool match = false;
        if (strcmp(temp->dado.url, "Vazia") != 0) {
            if (op == 1 && strstr(temp->dado.url, termo)) match = true;
            else if (op == 2 && strstr(temp->dado.data_hora, termo)) match = true;
            else if (op == 3 && temp->dado.favorito) match = true;
        }

        if (match) {
            char *estrela = (temp->dado.favorito) ? " [\xe2\x98\x85]" : "";
            printf("    [%d]%s URL: %s\n        Acesso: %s\n", i, estrela, temp->dado.url, temp->dado.data_hora);
            encontrou = true;
        }
        temp = temp->prox;
        i++;
    }

    if (!encontrou) printf("Nenhum registro encontrado.\n");
    printf("---------------------------------------\n");
}

void limpar_registro(No* no) {
    if (no != NULL) {
        strcpy(no->dado.url, "Vazia");
        strcpy(no->dado.data_hora, "--/--/---- --:--");
        no->dado.favorito = false;
    }
}

void limpar_todo_historico(No* cabeca) {
    No* temp = cabeca;
    while (temp) {
        limpar_registro(temp);
        temp = temp->prox;
    }
}

void alternar_favorito(No* atual) {
    if (atual && strcmp(atual->dado.url, "Vazia") != 0) {
        atual->dado.favorito = !atual->dado.favorito;
        if (atual->dado.favorito) {
            printf("\n[Sucesso] URL marcada como favorita!\n");
        } else {
            printf("\n[Sucesso] URL removida dos favoritos.\n");
        }
    } else {
        printf("\n[Erro] Não é possível favoritar um registro vazio.\n");
    }
}