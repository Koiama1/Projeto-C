#ifndef FUNCAO_H
#define FUNCAO_H


struct Cliente {
    int cnpj;
    char razao_social[100];
    char conta[10];
    float saldo;
    int senha;
};

struct Funcionario {
    char nome[100];
    int cpf;
    int senha;
};

struct Cliente clientes[100]; // Tamanho máximo para clientes
int numClientes = 0;

struct Funcionario funcionarios[100]; // Tamanho máximo para funcionários
int numFuncionarios = 0;

void menu_cliente();

void menu_funcionario();

void menu_login();

void novo_cliente();


#endif
