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

    // Abre o arquivo binário para leitura e escrita
    arquivo = fopen("contas.dat", "rb+");
    if (arquivo == NULL) {
        // Se não existir, cria um novo arquivo binário
        arquivo = fopen("contas.dat", "wb+");
        if (arquivo == NULL) {
            printf("Erro ao criar o arquivo.\n");
            return 1;
        }
    }