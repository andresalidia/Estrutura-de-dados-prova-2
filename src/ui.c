#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/ui.h"

extern char sessao_ativa[50];

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
    printf(" [4] Pesquisar / Filtros Avançados\n");
    printf(" [5] Excluir registro (Atual ou Todos)\n");
    printf(" [6] Favoritar / Desfavoritar atual\n");
    printf(" [7] Gerenciar Tags\n");
    printf(" [8] Trocar Sessão\n");
    printf(" [9] Painel de Ordenação Inteligente\n");
    printf(" [0] Sair do Navegador\n");
    printf("==========================================\n");
    printf("Escolha uma opção: ");
}

void exibir_tempo_relativo(char *data_hora_str) {
    if (strcmp(data_hora_str, "--/--/---- --:--") == 0) {
        printf("%s", data_hora_str);
        return;
    }
    struct tm tm_data = {0};
    int dia, mes, ano, hora, min;
    if (sscanf(data_hora_str, "%d/%d/%d %d:%d", &dia, &mes, &ano, &hora, &min) != 5) {
        printf("%s", data_hora_str);
        return;
    }
    tm_data.tm_mday = dia;
    tm_data.tm_mon = mes - 1;
    tm_data.tm_year = ano - 1900;
    tm_data.tm_hour = hora;
    tm_data.tm_min = min;
    tm_data.tm_isdst = -1;
    time_t tempo_passado = mktime(&tm_data);
    time_t agora = time(NULL);
    double diff = difftime(agora, tempo_passado);
    if (diff < 0) diff = 0;
    if (diff < 60) printf("agora mesmo");
    else if (diff < 3600) printf("há %d minutos", (int)(diff / 60));
    else if (diff < 86400) printf("há %d horas", (int)(diff / 3600));
    else if (diff < 172800) printf("ontem");
    else printf("há %d dias", (int)(diff / 86400));
}

void exibir_historico(No *cabeca, No *atual) {
    int pos_atual = 1;
    No *temp_pos = cabeca;
    while (temp_pos && temp_pos != atual) {
        pos_atual++;
        temp_pos = temp_pos->prox;
    }
    int pagina = (pos_atual <= 5) ? 1 : 2;
    int inicio = (pagina == 1) ? 1 : 6;
    int fim = (pagina == 1) ? 5 : 10;
    printf("\n========= Histórico de URLs (Página %d/2) =========\n", pagina);
    No *temp = cabeca;
    for (int i = 1; i <= 10; i++) {
        if (i >= inicio && i <= fim) {
            char *marcador = (temp == atual) ? " ->" : "   ";
            char *estrela = (temp->dado.favorito) ? " [★]" : "";
            printf("%s [%d]%s URL: %s\n        Último acesso: ", marcador, i, estrela, temp->dado.url);
            exibir_tempo_relativo(temp->dado.data_hora);
            int tem_tags = 0;
            for (int j = 0; j < 3; j++) {
                if (strlen(temp->dado.tags[j]) > 0) {
                    if (!tem_tags) { printf("\n        Tags: "); tem_tags = 1; }
                    else printf(" | ");
                    printf("%s", temp->dado.tags[j]);
                }
            }
            printf("\n");
        }
        temp = temp->prox;
    }
    printf("===================================================\n");
}

void ler_texto(char *url, int tamanho) {
    if (fgets(url, tamanho, stdin)) {
        url[strcspn(url, "\n")] = '\0';
    } else {
        url[0] = '\0';
    }
}

void obter_data_hora_atual(char *data_hora, int tamanho) {
    time_t agora = time(NULL);
    struct tm *momento = localtime(&agora);
    if (momento) strftime(data_hora, tamanho, "%d/%m/%Y %H:%M", momento);
    else { strncpy(data_hora, "--/--/---- --:--", tamanho - 1); data_hora[tamanho - 1] = '\0'; }
}

void exibir_tags(No *no) {
    if (!no) return;
    printf("\n--- Tags do registro ---\n");
    int tem_tags = 0;
    for (int i = 0; i < 3; i++) {
        if (strlen(no->dado.tags[i]) > 0) {
            printf("[%d] %s\n", i + 1, no->dado.tags[i]);
            tem_tags = 1;
        }
    }
    if (!tem_tags) printf("Nenhuma tag adicionada.\n");
    printf("------------------------\n");
}

void menu_gerenciar_tags(No *atual) {
    if (!atual || strcmp(atual->dado.url, "Vazia") == 0) {
        printf("\n[Erro] Nenhum registro selecionado ou registro está vazio.\n");
        return;
    }
    int opcao = -1;
    char nova_tag[50];
    while (opcao != 0) {
        printf("\n========== GERENCIAR TAGS ==========\n");
        printf("URL: %.80s\n", atual->dado.url);
        exibir_tags(atual);
        printf("\n[1] Adicionar tag\n[2] Remover tag\n[3] Limpar todas as tags\n[0] Voltar\nEscolha uma opção: ");
        if (scanf("%d", &opcao) != 1) { while (getchar() != '\n'); continue; }
        while (getchar() != '\n');
        if (opcao == 1) {
            printf("Qual slot (1-3): ");
            int slot; scanf("%d", &slot); while (getchar() != '\n');
            if (slot >= 1 && slot <= 3) {
                printf("Digite a tag: "); ler_texto(nova_tag, sizeof(nova_tag));
                strncpy(atual->dado.tags[slot-1], nova_tag, 49);
            }
        } else if (opcao == 2) {
            printf("Remover qual slot (1-3): ");
            int slot; scanf("%d", &slot); while (getchar() != '\n');
            if (slot >= 1 && slot <= 3) atual->dado.tags[slot-1][0] = '\0';
        } else if (opcao == 3) {
            for(int i=0; i<3; i++) atual->dado.tags[i][0] = '\0';
        }
    }
}