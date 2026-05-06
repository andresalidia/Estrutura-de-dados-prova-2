#ifndef MOLDES_H
#define MOLDES_H

// Estrutura dos Itens
typedef struct {
    char url[2084];
    char data_hora[20];
} Item;

// Estrutura do Nó - Lista Duplamente Encadeada
typedef struct no {
    Item dado;
    struct no *ant;
    struct no *prox;
} No;

// Definições das funções
No* criar_no(char* url, char* data);
void editar_endereco(No* atual, char* nova_url, char* nova_data);
No* ir_para_proximo(No* atual);
No* voltar_anterior(No* atual);
void salvar_csv(No* cabeca, char* nome_arquivo);
No* carregar_csv(char* nome_arquivo);

#endif