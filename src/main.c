#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/lista.h"
#include "../include/storage.h"
#include "../include/ui.h"
#include "../include/logica.h"

char sessao_ativa[50] = "PADRÃO";

void menu_selecionar_sessao_local() {
    limpar_tela();
    printf("\n====== SELEÇÃO DE SESSÃO ======\n");
    printf("Escolha a sessão desejada:\n\n");
    printf("[1] TRABALHO\n");
    printf("[2] ESTUDO\n");
    printf("[3] LAZER\n");
    printf("[4] NOVA SESSÃO\n");
    printf("[0] Usar PADRÃO\n");
    printf("Opção: ");
    int opcao;
    if (scanf("%d", &opcao) != 1) opcao = 0;
    while (getchar() != '\n');
    char nova_sessao[50];
    switch(opcao) {
        case 1: strcpy(sessao_ativa, "TRABALHO"); break;
        case 2: strcpy(sessao_ativa, "ESTUDO"); break;
        case 3: strcpy(sessao_ativa, "LAZER"); break;
        case 4:
            printf("Digite o nome da nova sessão: ");
            ler_texto(nova_sessao, sizeof(nova_sessao));
            if (strlen(nova_sessao) > 0) strcpy(sessao_ativa, nova_sessao);
            else strcpy(sessao_ativa, "PADRÃO");
            break;
        default: strcpy(sessao_ativa, "PADRÃO"); break;
    }
    printf("[✓] Sessão '%s' carregada.\n", sessao_ativa);
    pausar();
}

int main() {
    menu_selecionar_sessao_local();
    No* cabeca = carregar_sessao(sessao_ativa);
    No* atual = cabeca;
    int opcao = -1;
    char nova_url[2084], nova_data[20];

    while (opcao != 0) {
        limpar_tela();
        printf("\n>>>>>>>>>> NAVEGADOR DE HISTÓRICO | Sessão: %s <<<<<<<<<<\n", sessao_ativa);
        exibir_historico(cabeca, atual);
        exibir_menu();
        salvar_sessao(cabeca, sessao_ativa);

        if (scanf("%d", &opcao) != 1) opcao = -1;
        while (getchar() != '\n');

        switch (opcao) {
            case 1: 
                if (atual) {
                    No* prox = ir_para_proximo(atual);
                    if (prox != atual) {
                        atual = prox;
                        obter_data_hora_atual(nova_data, 20);
                        editar_endereco(atual, atual->dado.url, nova_data);
                    }
                }
                pausar(); break;
            case 2:
                if (atual) {
                    No* ant = voltar_anterior(atual);
                    if (ant != atual) {
                        atual = ant;
                        obter_data_hora_atual(nova_data, 20);
                        editar_endereco(atual, atual->dado.url, nova_data);
                    }
                }
                pausar(); break;
            case 3:
                if (atual) {
                    printf("\nDigite a nova URL: "); ler_texto(nova_url, 2084);
                    if (strlen(nova_url) > 0) {
                        obter_data_hora_atual(nova_data, 20);
                        editar_endereco(atual, nova_url, nova_data);
                    }
                }
                pausar(); break;
            case 4: pesquisar_historico(cabeca); pausar(); break;
            case 5:
                printf("\n1. Limpar atual\n2. Limpar tudo\nEscolha: ");
                int ex; scanf("%d", &ex); while (getchar() != '\n');
                if (ex == 1) limpar_registro(atual);
                else if (ex == 2) limpar_todo_historico(cabeca);
                pausar(); break;
            case 6: alternar_favorito(atual); pausar(); break;
            case 7: menu_gerenciar_tags(atual); pausar(); break;
            case 8:
                salvar_sessao(cabeca, sessao_ativa);
                while(cabeca) { No* t = cabeca->prox; free(cabeca); cabeca = t; }
                menu_selecionar_sessao_local();
                cabeca = carregar_sessao(sessao_ativa);
                atual = cabeca;
                break;
            case 9: {
                printf("\n--- Painel de Ordenação ---\n");
                printf("1. Ordenar por Ordem Alfabética\n");
                printf("2. Ordenar por Mais Visitados (Frequência)\n");
                printf("0. Voltar\n");
                printf("Escolha: ");
                int op_ord;
                if (scanf("%d", &op_ord) != 1) op_ord = 0;
                while (getchar() != '\n');
                if (op_ord > 0) {
                    exibir_historico_ordenado(cabeca, op_ord);
                    pausar();
                }
                break;
            }
            case 0: printf("\nSaindo...\n"); pausar(); break;
        }
    }
    return 0;
}