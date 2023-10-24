#include "funcao.h"

struct funcionario {
    char nome[100];
    int cpf;
    int senha;
};

struct cliente {
    int cnpj;
    char razao_social[100];
    char conta[10];
    float saldo;
    int senha;
};

struct funcionario funcionarios[100];
struct cliente clientes[100];

// Função para cadastrar um novo funcionário
void novo_funcionario(void) {
    char nome[100];
    int cpf;
    int senha;

    printf("Digite seu nome: ");
    scanf("%s", nome);
    printf("Digite seu CPF: ");
    scanf("%d", &cpf);
    printf("Digite sua senha: ");
    scanf("%d", &senha);

    // Verifica se o funcionário já existe
    for (int i = 0; i < sizeof(funcionarios) / sizeof(funcionarios[0]); i++) {
        if (funcionarios[i].cpf == cpf) {
            printf("Funcionario ja cadastrado.\n");
            return;
        }
    }

    // Adiciona o funcionário ao vetor
    struct funcionario novo_funcionario = {nome, cpf, senha};
    funcionarios[sizeof(funcionarios) / sizeof(funcionarios[0])] = novo_funcionario;

    printf("Funcionario cadastrado com sucesso!\n");
    menu_login();
}

// Função para cadastrar um novo cliente
void novo_cliente(void) {
    int cnpj;
    char razao_social[100];
    char conta[10];
    float saldo;
    int senha;

    printf("Digite seu CNPJ: ");
    scanf("%d", &cnpj);
    printf("Digite sua razao social: ");
    scanf("%s", razao_social);
    printf("Digite o tipo da conta (Comum ou Plus): ");
    scanf("%s", conta);
    printf("Digite o saldo inicial: ");
    scanf("%f", &saldo);
    printf("Digite sua senha: ");
    scanf("%d", &senha);

    // Verifica se o cliente já existe
    for (int i = 0; i < sizeof(clientes) / sizeof(clientes[0]); i++) {
        if (clientes[i].cnpj == cnpj) {
            printf("Cliente ja cadastrado.\n");
            return;
        }
    }

    // Adiciona o cliente ao vetor
    struct cliente novo_cliente = {cnpj, razao_social, conta, saldo, senha};
    clientes[sizeof(clientes) / sizeof(clientes[0])] = novo_cliente;

    printf("Cliente cadastrado com sucesso!\n");
    menu_login();
}

void menu_cliente(){
  //Função para login cliente
}

void menu_funcionario(){
  //Função para login funcionario
}

void login(void) {
    // Obtém o tipo de login
    int tipo_de_login;
    printf("Qual login deseja acessar? (Funcionario = 1) (cliente = 2):  ");
    scanf("%d", &tipo_de_login);

    // Verifica o tipo de login
    if (tipo_de_login == 1) {
        // Login de funcionário

        // Obtém o CPF do funcionário
        int cpf;
        printf("Digite seu CPF: ");
        scanf("%d", &cpf);

        // Verifica se o funcionário existe
        for (int i = 0; i < sizeof(funcionarios) / sizeof(funcionarios[0]); i++) {
            if (funcionarios[i].cpf == cpf) {
                // Obtém a senha do funcionário
                int senha;
                printf("Digite sua senha: ");
                scanf("%d", &senha);

                // Verifica se a senha está correta
                if (funcionarios[i].senha == senha) {
                    // Login bem-sucedido
                    menu_funcionario();
                }
            }
        }

        // Login inválido
        return 0;
    } else if (tipo_de_login == 2) {
        // Login de cliente

        // Obtém o CNPJ do cliente
        int cnpj;
        printf("Digite seu CNPJ: ");
        scanf("%d", &cnpj);

        // Verifica se o cliente existe
        for (int i = 0; i < sizeof(clientes) / sizeof(clientes[0]); i++) {
            if (clientes[i].cnpj == cnpj) {
                // Obtém a senha do cliente
                int senha;
                printf("Digite sua senha: ");
                scanf("%d", &senha);

                // Verifica se a senha está correta
                if (clientes[i].senha == senha) {
                    // Login bem-sucedido
                    menu_cliente();
                }
            }
        }

        // Login inválido
        return 0;
    } else {
        // Opção inválida
        return 0;
    }
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
