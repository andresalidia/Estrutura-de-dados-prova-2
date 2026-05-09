/******************************************************************************
 * PROJETO: Navegador de Histórico (Lista Duplamente Encadeada)
 * DISCIPLINA: Estrutura de Dados
 * DATA DE ENTREGA: 10/05/2026
 * DESCRIÇÃO: Implementação de um histórico de navegação com 10 registros
 *             utilizando uma lista duplamente encadeada e persistência em CSV.
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "funcoes.h"

void limpar_tela() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pausar() {
    printf("\n[Pressione ENTER para continuar...]");
    while (getchar() != '\n'); 
}


void exibir_menu() {
    printf("\n==========================================\n");
    printf("            MENU INTERATIVO               \n");
    printf("==========================================\n");
    printf(" [1] Avançar para próximo registro\n");
    printf(" [2] Voltar ao registro anterior\n");
    printf(" [3] Editar URL atual\n");
    printf(" [4] Pesquisar\n");
    printf(" [5] Excluir registro (Atual ou Todos)\n");
    printf(" [6] Favoritar / Desfavoritar atual\n");
    printf(" [0] Sair do Navegador\n");
    printf("==========================================\n");
    printf("Escolha uma opção: ");
}

int main() {
    No* cabeca = carregar_csv("historicoURL.csv");
    No* atual = cabeca;
    int opcao = -1;
    char nova_url[2084];
    char nova_data[20];

    while (opcao != 0) {
        limpar_tela();
        printf("\n>>>>>>>>>> BEM-VINDO AO NAVEGADOR DE HISTÓRICO <<<<<<<<<<\n");
        printf("A URL com a seta '->' indica sua posição atual na lista.\n");

        exibir_historico(cabeca, atual);
        exibir_menu();
        salvar_csv(cabeca, "historicoURL.csv");

        if (scanf("%d", &opcao) != 1) {
            opcao = -1; 
        }
        while (getchar() != '\n'); 

        switch (opcao) {
    
            case 1:
                if (atual) {
                    No* proximo = ir_para_proximo(atual);
                    if (proximo != atual) {
                        atual = proximo;
                        obter_data_hora_atual(nova_data, sizeof(nova_data));
                        editar_endereco(atual, atual->dado.url, nova_data);
                        printf("\n[Info] Avançou para o próximo registro.\n");
                    }
                } else {
                    printf("\n[Erro] Não há registro atual para avançar.\n");
                }
                pausar();
                break;
            case 2:
                if (atual) {
                    No* anterior = voltar_anterior(atual);
                    if (anterior != atual) {
                        atual = anterior;
                        obter_data_hora_atual(nova_data, sizeof(nova_data));
                        editar_endereco(atual, atual->dado.url, nova_data);
                        printf("\n[Info] Voltou para o registro anterior.\n");
                    }
                } else {
                    printf("\n[Erro] Não há registro atual para voltar.\n");
                }
                pausar();
                break;
            case 3:
                if (atual) {
                    printf("\nDigite a nova URL: ");
                    ler_texto(nova_url, sizeof(nova_url));
                    if (strlen(nova_url) == 0) {
                        printf("\n[Aviso] URL não modificada.\n");
                    } else {
                        obter_data_hora_atual(nova_data, sizeof(nova_data));
                        editar_endereco(atual, nova_url, nova_data);
                    }
                } else {
                    printf("\n[Erro] Não há registro atual para editar.\n");
                }
                pausar();
                break;
            case 4:
                pesquisar_historico(cabeca);
                pausar();
                break;
            case 5:
                printf("\n--- Opções de Exclusão ---\n");
                printf("1. Excluir registro atual\n");
                printf("2. Limpar todo o histórico\n");
                printf("0. Cancelar\n");
                printf("Escolha uma opção: ");
                
                int op_excluir;
                if (scanf("%d", &op_excluir) != 1) op_excluir = -1;
                while (getchar() != '\n'); 
                
                if (op_excluir == 1) {
                    if (atual) {
                        limpar_registro(atual);
                        printf("\n[Sucesso] Registro atual limpo!\n");
                    }
                } else if (op_excluir == 2) {
                    limpar_todo_historico(cabeca);
                    printf("\n[Sucesso] Todo o histórico foi apagado!\n");
                } else if (op_excluir == 0) {
                    printf("\n[Info] Ação cancelada.\n");
                } else {
                    printf("\n[Erro] Opção inválida.\n");
                }
                pausar();
                break;
            case 6:
                alternar_favorito(atual);
                pausar();
                break;
            case 0:
                printf("\nSaindo... Salvando histórico antes de fechar.\n");
                pausar();
                break;
            default:
                printf("\n[Erro] Opção inválida. Tente novamente.\n");
                pausar();
                break;
        }
    }

    return 0;
}