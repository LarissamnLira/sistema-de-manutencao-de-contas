#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura de tamanho fixo para o registro
typedef struct {
    int numero_conta;
    char nome[50];
    double saldo;
    int ativa; // 1 = ativa, 0 = excluída/vazia
} Cliente;

// Protótipos das funções
void cadastrar(FILE *arquivo);
void consultar(FILE *arquivo);
void atualizar(FILE *arquivo);
void encerrar(FILE *arquivo);
void listar(FILE *arquivo);