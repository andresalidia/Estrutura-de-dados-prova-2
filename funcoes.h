/******************************************************************************
 * PROJETO: Navegador de Histórico (Lista Duplamente Encadeada)
 * DISCIPLINA: Estrutura de Dados
 * DATA DE ENTREGA: 10/05/2026
 * DESCRIÇÃO: Definições de estruturas e protótipos de funções.
 ******************************************************************************/

#ifndef FUNCOES_H
#define FUNCOES_H

typedef struct {
    char url[2084];
    char data_hora[20];
} Item;

typedef struct no {
    Item dado;
    struct no *ant;
    struct no *prox;
} No;

No* criar_no(char* url, char* data);
void editar_endereco(No* atual, char* nova_url, char* nova_data);
No* ir_para_proximo(No* atual);
No* voltar_anterior(No* atual);
void salvar_csv(No* cabeca, char* nome_arquivo);
No* carregar_csv(char* nome_arquivo);
void exibir_historico(No* cabeca, No* atual);
void ler_texto(char* texto, int tamanho);
void obter_data_hora_atual(char* data_hora, int tamanho);
void pesquisar_historico(No* cabeca);
void limpar_registro(No* no);
void limpar_todo_historico(No* cabeca);

#endif