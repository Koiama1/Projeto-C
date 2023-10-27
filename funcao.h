#ifndef funcao_h
#define funcao_h

#include <stdio.h>
#include <stdlib.h>

struct Cliente{
    int cnpj;
    char razao_social[100];
    char conta[10];
    float saldo;
    int senha;
    char historico[500];
};

struct Funcionario {
    int cpf;
    char nome[100];
    int senha;
};

void novo_funcionario(void);
void novo_cliente(void);
void login(void);
void apagar_clientes(struct Cliente *clientes, int tamanho);
void listar_clientes(void);
void apagar_funcionarios(struct Funcionario *funcionarios, int tamanho);
void listar_funcionarios(void);
void debito(struct Cliente *clientes, int tamanho);
void deposito(struct Cliente *clientes, int tamanho);
void extrato(void);
void transferencia(void);
void menu_login(void);
void menu_funcionario(void);
void menu_cliente(void);

#endif
