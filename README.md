# Navegador de Histórico (Lista Duplamente Encadeada)

Este projeto simula um histórico de navegação utilizando uma **Lista Duplamente Encadeada** em C, agora com uma arquitetura modular profissional.

## 📁 Estrutura do Projeto
- **`src/`**: Contém a implementação do código (.c) separada por responsabilidades.
  - `main.c`: Laço principal do programa.
  - `lista.c`: Manipulação da estrutura de dados da lista.
  - `storage.c`: Gerenciamento de arquivos CSV e sessões.
  - `ui.c`: Interface de usuário e menus.
  - `logica.c`: Algoritmos de busca, ordenação e tags.
- **`include/`**: Arquivos de cabeçalho (.h).
- **`data/`**: Onde os arquivos de histórico de cada sessão são armazenados.

## ✨ Novidades da Refatoração
1.  **Arquitetura Modular:** Código separado em módulos lógicos para fácil manutenção.
2.  **Timestamps Relativos:** Histórico mostra "há X minutos" ou "ontem" para melhor leitura.
3.  **Ordenação Inteligente:** Opção de visualizar o histórico por Ordem Alfabética ou por Frequência de Acesso.
4.  **Sistema Multi-Sessão:** Crie perfis diferentes (Trabalho, Estudo, etc) com históricos isolados.

## 🛠️ Como Compilar e Rodar
### No Windows:
Basta rodar o script utilitário:
```bash
.\compilar.bat
```
Ou usar o GCC manualmente:
```bash
gcc -I./include src/main.c src/lista.c src/storage.c src/ui.c src/logica.c -o navegador.exe
```

### No Linux/Mac:
```bash
gcc -I./include src/*.c -o navegador
./navegador
```

## 🚀 Funcionalidades
- Navegação (Avançar/Voltar)
- Edição de URLs
- Sistema de Favoritos [★]
- Tags Customizadas (até 3 por URL)
- Busca e Filtros Avançados
- Persistência em CSV
