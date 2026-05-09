#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "moldes.h"




void exibir_menu() {
    printf("\n======= MENU INTERATIVO =======\n");
    printf("1. Avançar para próximo registro\n");
    printf("2. Voltar ao registro anterior\n");
    printf("3. Editar URL atual\n");
    printf("0. Sair\n");
    printf("Escolha uma opção: ");
}

int main() {
    No* cabeca = carregar_csv("historicoURL.csv");
    No* atual = cabeca;
    int opcao = -1;
    char nova_url[2084];
    char nova_data[20];

    printf(">>>>>>>>>> Bem-vindo ao Navegador de Histórico! <<<<<<<<<<\n");
    printf("[importante] Quando tiver \"->\" ao lado de uma URL, significa que é a URL atual.\n");


    while (opcao != 0) {

        exibir_historico(cabeca, atual);
        exibir_menu();
        salvar_csv(cabeca, "historicoURL.csv");

        scanf("%d", &opcao);

        switch (opcao) {
    
            case 1                                                                          :
                if (atual) {
                    atual = ir_para_proximo(atual);
                    if (atual) {
                        obter_data_hora_atual(nova_data, sizeof(nova_data));
                        editar_endereco(atual, atual->dado.url, nova_data);
                    }
                } else {
                    printf("\n[Erro] Não há registro atual para avançar.\n");
                }
                break;
            case 2:
                if (atual) {
                    atual = voltar_anterior(atual);
                        if (atual) {
                            obter_data_hora_atual(nova_data, sizeof(nova_data));
                            editar_endereco(atual, atual->dado.url, nova_data);
                    }
                } else {
                    printf("\n[Erro] Não há registro atual para voltar.\n");
                }
                break;
            case 3:
                if (atual) {
                    printf("Digite a nova URL: ");
                    fgets(nova_url, sizeof(nova_url), stdin); 
                    ler_texto(nova_url, sizeof(nova_url));
                    if (strlen(nova_url) == 0) {
                        printf("\n[Aviso] URL não modificada\n");
                    } else {
                        obter_data_hora_atual(nova_data, sizeof(nova_data));
                        editar_endereco(atual, nova_url, nova_data);
                    }
                } else {
                    printf("\n[Erro] Não há registro atual para editar.\n");
                }
                break;
            case 0:
                printf("\nSaindo... Salvando histórico antes de fechar.\n");
                break;
            default:
                printf("\n[Erro] Opção desconhecida. Tente novamente.\n");
                break;
        }
    }

    return 0;
}
