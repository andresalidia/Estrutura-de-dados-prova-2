# Navegador de Histórico (Lista Duplamente Encadeada)

Este projeto foi desenvolvido como parte da disciplina de **Estrutura de Dados**. Consiste em um simulador de histórico de navegação utilizando uma **Lista Duplamente Encadeada** em linguagem C.

## 🚀 Funcionalidades Principais
- **Avançar/Voltar:** Navegação fluida entre os registros de endereços.
- **Editar:** Modificação da URL na posição atual com atualização automática de data e hora.
- **Persistência:** Salvamento automático em arquivo CSV (`historicoURL.csv`).

## ✨ Inovações e Melhorias Avançadas
Para elevar a qualidade técnica e usabilidade do projeto, as seguintes inovações foram implementadas:

1.  **Paginação Elegante (Automática):** A interface exibe o histórico em blocos de 5 itens por vez. O sistema detecta a posição do cursor (`->`) e alterna automaticamente entre a **Página 1** e a **Página 2**, mantendo o terminal organizado.
2.  **Sistema de Favoritos (`stdbool.h`):** Implementação de um marcador booleano para URLs favoritas. Itens favoritados são destacados visualmente com uma estrela `[★]`.
3.  **Busca e Filtros Inteligentes:** Um sub-menu de pesquisa que permite filtrar o histórico por:
    - **Palavra-chave:** Busca trechos de texto na URL.
    - **Data de Acesso:** Filtra registros por um dia específico (ex: `09/05/2026`).
    - **Favoritos:** Exibe apenas a lista de sites marcados como favoritos.
4.  **Exclusão Flexível:** Opção de limpar apenas o registro atual (resetando para "Vazia") ou realizar um "Wipe" completo em todo o histórico.
5.  **Persistência de Dados Evoluída:** O arquivo CSV salva URLs, datas e o status de favoritos, mantendo a integridade dos dados entre sessões.
6.  **Interface CLI Refinada:**
    - Limpeza automática do terminal (`system("cls")`) a cada interação.
    - Sistema de pausas para leitura de mensagens de confirmação e erro.
7.  **Arquitetura Modular Profissional:** Separação clara entre a lógica principal (`main.c`) e o módulo de funções (`funcoes.c`/`funcoes.h`).

## 🛠️ Como Compilar e Rodar
Certifique-se de ter o `gcc` instalado em seu ambiente.

1.  Abra o terminal na pasta do projeto.
2.  Compile o código:
    ```bash
    gcc main.c funcoes.c -o navegador.exe
    ```
3.  Execute a aplicação:
    ```bash
    .\navegador.exe
    ```

## 📂 Estrutura de Arquivos
- `main.c`: Lógica principal do menu e controle do fluxo.
- `funcoes.c`: Implementação de todas as operações da lista, filtros e arquivos.
- `funcoes.h`: Definições de tipos (structs), uso de `stdbool.h` e protótipos.
- `.gitignore`: Configurado para ignorar `.vscode`, `.exe` e arquivos de dados locais.
- `historicoURL.csv`: Banco de dados do histórico (formato: `url;data;favorito`).
