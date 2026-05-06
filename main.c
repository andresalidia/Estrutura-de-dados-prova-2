#include <stdio.h>
#include "moldes.h"

int main() {
    // Carrega o histórico do arquivo ou inicia vazio
    No* cabeca = carregar_csv("historicoURL.csv");
    No* atual = cabeca;

    // Exemplo de uso:
    if (atual) {
        printf("Página atual: %s\n", atual->dado.url);
        
        // Navegar
        atual = ir_para_proximo(atual);
        
        // Editar a página atual
        editar_endereco(atual, "https://google.com", "06/05/2026 16:00");
        
        // Salvar as alterações
        salvar_csv(cabeca, "historicoURL.csv");
    }

    return 0;
}