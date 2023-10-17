#include <stdio.h>
#include "funcao.h"

void debito() {
    // Implemente a função de débito
}

void deposito() {
    // Implemente a função de depósito
}

void extrato() {
    // Implemente a função de extrato
}

void transferencia() {
    // Implemente a função de transferência
}

void menu_cliente() {
    int menu;

    while (1) {
        printf("1. Débito\n");
        printf("2. Depósito\n");
        printf("3. Extrato\n");
        printf("4. Transferência entre contas\n");
        printf("5. Sair\n");
        printf("Digite o número respectivo à opção desejada: ");
        scanf("%d", &menu);

        if (menu == 5) {
            break;
        } else if (menu == 1) {
            debito();
        } else if (menu == 2) {
            deposito();
        } else if (menu == 3) {
            extrato();
        } else if (menu == 4) {
            transferencia();
        }
    }
}
void apagar_funcionario() {
    // Implemente a função de apagar funcionário
}

void listar_funcionarios() {
    // Implemente a função de listar funcionários
}

void listar_clientes(){

}

void apagar_cliente() {

}

void menu_funcionario() {
    int menu;

    while (1) {
        printf("1. Apagar cliente\n");
        printf("2. Listar clientes\n");
        printf("3. Apagar funcionário\n");
        printf("4. Listar funcionários\n");
        printf("5. Sair\n");
        printf("Digite o número respectivo à opção desejada: ");
        scanf("%d", &menu);

        if (menu == 5) {
            break;
        } else if (menu == 1) {
            apagar_cliente();
        } else if (menu == 2) {
            listar_clientes();
        } else if (menu == 3) {
            apagar_funcionario();
        } else if (menu == 4) {
            listar_funcionarios();
        }
    }
}

void novo_funcionario() {
    // Implemente a função novo_funcionario
}

void novo_cliente() {
    int cnpj;
    char razao_social[100];
    char conta[10];
    float saldo;
    int senha;

    printf("CNPJ: ");
    scanf("%d", &cnpj);

    for (int i = 0; i < numClientes; i++) {
        if (clientes[i].cnpj == cnpj) {
            printf("Cliente já cadastrado\n");
            menu_login();
            return;
        }
    }

    printf("Razão Social: ");
    scanf("%s", razao_social);

    printf("Tipo de conta (Comum ou Plus): ");
    scanf("%s", conta);

    if (strcmp(conta, "Plus") != 0 && strcmp(conta, "Comum") != 0) {
        printf("Tipo de conta inválido\n");
        menu_login();
        return;
    }

    printf("Digite o valor inicial da conta: ");
    scanf("%f", &saldo);

    printf("Defina uma senha: ");
    scanf("%d", &senha);

    struct Cliente novoCliente;
    novoCliente.cnpj = cnpj;
    strcpy(novoCliente.razao_social, razao_social);
    strcpy(novoCliente.conta, conta);
    novoCliente.saldo = saldo;
    novoCliente.senha = senha;

    clientes[numClientes] = novoCliente;
    numClientes++;

    printf("Cliente cadastrado com sucesso!\n");
    menu_login();

}

void login() {
    // Implemente a função de login
}

void sair() {
    // Implemente a função de sair
}

void menu_login() {
    int menu;

    while (1) {
        printf("1. Cadastrar funcionário\n");
        printf("2. Cadastrar cliente\n");
        printf("3. Login\n");
        printf("4. Sair\n");
        printf("Digite o número respectivo à opção desejada: ");
        scanf("%d", &menu);

        if (menu == 4) {
            sair();
            break;
        } else if (menu == 1) {
            novo_funcionario();
        } else if (menu == 2) {
            novo_cliente();
        } else if (menu == 3) {
            login();
        }
    }
}
