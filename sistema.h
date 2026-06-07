#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int numero_conta;
    char nome[50];
    double saldo;
    int ativa; // 1 = ativa, 0 = excluída/vazia
} Cliente;

void cadastrar(FILE *arquivo);
void consultar(FILE *arquivo);
void atualizar(FILE *arquivo);
void encerrar(FILE *arquivo);
void listar(FILE *arquivo);

int main() {
    FILE *arquivo;
    int opcao;

    arquivo = fopen("contas.dat", "rb+");
    if (arquivo == NULL) {
        arquivo = fopen("contas.dat", "wb+");
        if (arquivo == NULL) {
            printf("Erro ao criar o arquivo.\n");
            return 1;
        }
    }

    do {
        printf("< SISTEMA DE MANUTENÇÃO DE CONTAS >\n");
        printf("1. Cadastrar um novo cliente em posição específica\n");
        printf("2. Consultar um cliente pelo número da conta\n");
        printf("3. Atualizar o saldo de um cliente\n");
        printf("4. Encerrar conta (remover cliente)\n");
        printf("5. Listar todos os clientes\n");
        printf("6. Restaurar leitura do início (rewind) e listar\n");
        printf("7. Encerrar\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrar(arquivo);
                break;
            case 2:
                consultar(arquivo);
                break;
            case 3:
                atualizar(arquivo);
                break;
            case 4:
                encerrar(arquivo);
                break;
            case 5:
                listar(arquivo);
                break;
            case 6:
                printf("\nExecutando rewind()...\n");
                rewind(arquivo);
                listar(arquivo); 
                break;
            case 7:
                printf("Encerrando o sistema...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } 
    
    while (opcao != 7);
    fclose(arquivo);
    return 0;
}

void cadastrar(FILE *arquivo) {
    int posicao;
    Cliente c;

    printf("Digite a posição para cadastrar (ex: 1, 2, 3...): ");
    scanf("%d", &posicao);

    if (posicao < 1) {
        printf("Posição inválida.\n");
        return;
    }

    fseek(arquivo, (posicao - 1) * sizeof(Cliente), SEEK_SET);

    Cliente temp;
    if (fread(&temp, sizeof(Cliente), 1, arquivo) == 1 && temp.ativa == 1) {
        printf("Já existe uma conta ativa nesta posição!\n");
        return;
    }

    printf("Número da conta: ");
    scanf("%d", &c.numero_conta);
    printf("Nome do cliente: ");
    getchar(); 
    fgets(c.nome, 50, stdin);
    c.nome[strcspn(c.nome, "\n")] = 0; 
    printf("Saldo inicial: R$ ");
    scanf("%lf", &c.saldo);
    c.ativa = 1;

    fseek(arquivo, (posicao - 1) * sizeof(Cliente), SEEK_SET);
    fwrite(&c, sizeof(Cliente), 1, arquivo);

    printf("Cliente cadastrado com sucesso na posição %d!\n", posicao);
}

void consultar(FILE *arquivo) {
    int num_conta;
    Cliente c;

    printf("Digite o número da conta para consulta: ");
    scanf("%d", &num_conta);

    rewind(arquivo);
    while (fread(&c, sizeof(Cliente), 1, arquivo) == 1) {
        if (c.ativa == 1 && c.numero_conta == num_conta) {
            printf("\nCliente Encontrado!\n");
            printf("Conta: %d\nNome: %s\nSaldo: R$ %.2f\n", c.numero_conta, c.nome, c.saldo);
            return;
        }
    }
    printf("Conta não encontrada ou inativa.\n");
}

void atualizar(FILE *arquivo) {
    int num_conta;
    Cliente c;

    printf("Digite o número da conta para atualizar o saldo: ");
    scanf("%d", &num_conta);

    rewind(arquivo);
    while (fread(&c, sizeof(Cliente), 1, arquivo) == 1) {
        if (c.ativa == 1 && c.numero_conta == num_conta) {
            printf("Saldo atual: R$ %.2f\n", c.saldo);
            printf("Digite o novo saldo: R$ ");
            scanf("%lf", &c.saldo);

            fseek(arquivo, -sizeof(Cliente), SEEK_CUR);
            fwrite(&c, sizeof(Cliente), 1, arquivo);

            printf("Saldo atualizado com sucesso!\n");
            return;
        }
    }
    printf("Conta não encontrada.\n");
}

void encerrar(FILE *arquivo) {
    int num_conta;
    Cliente c;

    printf("Digite o número da conta para encerrar: ");
    scanf("%d", &num_conta);

    rewind(arquivo);
    while (fread(&c, sizeof(Cliente), 1, arquivo) == 1) {
        if (c.ativa == 1 && c.numero_conta == num_conta) {
            c.ativa = 0; // Marca como inativo (exclusão lógica)

            fseek(arquivo, -sizeof(Cliente), SEEK_CUR);
            fwrite(&c, sizeof(Cliente), 1, arquivo);

            printf("Conta encerrada com sucesso.\n");
            return;
        }
    }
    printf("Conta não encontrada.\n");
}

void listar(FILE *arquivo) {
    Cliente c;
    int encontrou = 0;

    rewind(arquivo);
    
    printf("\nLista de Clientes Ativos:\n");

    while (fread(&c, sizeof(Cliente), 1, arquivo) == 1) {
        if (c.ativa == 1) {
            printf("Conta: %05d | Nome: %-20s | Saldo: R$ %.2f\n", c.numero_conta, c.nome, c.saldo);
            encontrou = 1;
        }
    }

    if (!encontrou) {
        printf("Nenhum cliente ativo no sistema.\n");
    }
}