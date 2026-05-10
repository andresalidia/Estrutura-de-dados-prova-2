#ifndef LOGICA_H
#define LOGICA_H

#include "lista.h"

void pesquisar_historico(No* cabeca);
void exibir_historico_ordenado(No* cabeca, int tipo);
void alternar_favorito(No* atual);
void serializar_tags(Item* item, char* tags_str);
void desserializar_tags(char* tags_str, Item* item);
void adicionar_tag(No* no, int indice, char* tag);
void remover_tag(No* no, int indice);

#endif