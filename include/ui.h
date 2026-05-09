#ifndef UI_H
#define UI_H

#include "lista.h"

void limpar_tela();
void pausar();
void exibir_menu();
void exibir_historico(No* cabeca, No* atual);
void exibir_tempo_relativo(char* data_hora_str);
void ler_texto(char* texto, int tamanho);
void obter_data_hora_atual(char* data_hora, int tamanho);
void menu_gerenciar_tags(No* atual);
void exibir_tags(No* no);

#endif