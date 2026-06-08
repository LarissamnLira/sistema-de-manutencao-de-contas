# Sistema de Manutenção de Contas em C

Este projeto consiste em um sistema de gerenciamento e manutenção de contas de clientes desenvolvido em **Linguagem C**. A aplicação utiliza manipulação de arquivos binários com registros de tamanho fixo para garantir uma persistência de dados eficiente, estável e segura, simulando o banco de dados de um sistema bancário.

O projeto foi estruturado de forma modular e segue estritamente os tópicos consolidados de entrada/saída, estruturas de decisão, tipos estruturados (`struct`), subprogramas (funções), arquivos binários e ponteiros.

---

## 🚀 Funcionalidades Implementadas

O sistema disponibiliza um menu interativo no terminal com as seguintes opções:

1. **Cadastrar um novo cliente em uma posição específica:** Permite salvar um registro escolhendo o índice exato no arquivo, evitando sobreposição caso a posição já esteja ocupada por uma conta ativa.
2. **Consultar um cliente pelo número da conta:** Realiza uma busca sequencial baseada no identificador numérico da conta.
3. **Atualizar o saldo de um cliente:** Localiza o cliente e substitui o valor do saldo diretamente no arquivo binário.
4. **Encerrar conta (remover cliente):** Realiza a exclusão lógica do cliente alterando o status da propriedade `ativa` para `0`.
5. **Listar todos os clientes:** Exibe no console todos os registros de clientes que estão atualmente com o status ativo.
6. **Restaurar a leitura do arquivo do início com `rewind()`:** Reposiciona o cursor no byte zero do arquivo e repete de forma proposital a listagem completa.
7. **Encerrar:** Fecha o fluxo de comunicação com o arquivo com segurança e encerra a execução do programa.

---

## 🛠️ Detalhes Técnicos e Estrutura de Dados

### Registro de Tamanho Fixo
Para possibilitar o acesso direto a posições específicas, foi definida uma estrutura (`struct`) com tamanho predeterminado em memória:

```c
typedef struct {
    int numero_conta;
    char nome[50];
    double saldo;
    int ativa; // Flag para Exclusão Lógica (1 = Ativa, 0 = Inativa/Removida)
} Cliente;

### 🛠️ Funções de Manipulação de Arquivos

O código implementa de forma prática os requisitos fundamentais de manipulação de arquivos em modo binário (`rb+` / `wb+`):

* **`fseek()`**: Utilizado na função `cadastrar` para pular diretamente para a posição desejada (`SEEK_SET`). Também é usado nas funções `atualizar` e `encerrar` com valor negativo (`-sizeof(Cliente)`) a partir da posição atual (`SEEK_CUR`) para voltar o cursor exatamente um registro e sobrescrever a estrutura alterada.
* **`fread()` e `fwrite()`**: Transferem blocos inteiros da estrutura `Cliente` diretamente entre a memória RAM e o disco de forma rápida, preservando a formatação binária.
* **`rewind()`**: Reinicia o indicador de posição do arquivo de volta para o início (byte 0). Usado antes das buscas sequenciais e explicitamente na opção 6 do menu.
* **Exclusão Lógica**: Quando uma conta é "removida", o campo `ativa` passa a ser `0`. O registro permanece fisicamente no arquivo para manter a integridade dos índices de posições, mas é ignorado pelas funções de listagem e consulta.
