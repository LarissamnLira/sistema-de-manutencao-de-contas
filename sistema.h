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
                printf("Opcao invalida! Tente novamente.\n");
        }
    } 
    
    while (opcao != 7);
    fclose(arquivo);
    return 0;
}