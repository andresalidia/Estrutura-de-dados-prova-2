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

#include "moldes.h"

// Função auxiliar para limpar a tela de forma multiplataforma
void limpar_tela() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Função auxiliar para pausar a execução até o usuário pressionar Enter
void pausar() {
    printf("\n[Pressione ENTER para continuar...]");
    while (getchar() != '\n'); // Consome o Enter
}


void exibir_menu() {
    printf("\n==========================================\n");
    printf("            MENU INTERATIVO               \n");
    printf("==========================================\n");
    printf(" [1] Avançar para próximo registro\n");
    printf(" [2] Voltar ao registro anterior\n");
    printf(" [3] Editar URL atual\n");
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
            opcao = -1; // Trata entrada inválida (ex: letras)
        }
        while (getchar() != '\n'); // Limpa o buffer para evitar problemas

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