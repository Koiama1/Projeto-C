#include "funcao.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void salvar_cliente(struct Cliente cliente) {
    FILE *arquivo;
    arquivo = fopen("clientes.dat", "ab");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de clientes.\n");
        exit(1);
    }
    fwrite(&cliente, sizeof(struct Cliente), 1, arquivo);
    fclose(arquivo);
}


void salvar_funcionario(struct Funcionario funcionario) {
    FILE *arquivo;
    arquivo = fopen("funcionarios.dat", "ab");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de funcionários.\n");
        exit(1);
    }
    fwrite(&funcionario, sizeof(struct Funcionario), 1, arquivo);
    fclose(arquivo);
}


int cliente_existe(int cnpj, int senha) {
    FILE *arquivo;
    struct Cliente cliente;

    arquivo = fopen("clientes.dat", "rb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de clientes.\n");
        exit(1);
    }

    while (fread(&cliente, sizeof(struct Cliente), 1, arquivo)) {
        if (cliente.cnpj == cnpj && cliente.senha == senha) {
            fclose(arquivo);
            return 1;
        }
    }

    fclose(arquivo);
    return 0;
}


int funcionario_existe(int cpf, int senha) {
    FILE *arquivo;
    struct Funcionario funcionario;

    arquivo = fopen("funcionarios.dat", "rb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de funcionários.\n");
        exit(1);
    }

    while (fread(&funcionario, sizeof(struct Funcionario), 1, arquivo)) {
        if (funcionario.cpf == cpf && funcionario.senha == senha) {
            fclose(arquivo);
            return 1;
        }
    }

    fclose(arquivo);
    return 0;
}


void novo_funcionario(void) {
    int cpf;
    char nome[100];
    int senha;

    printf("Digite seu CPF: ");
    scanf("%d", &cpf);
    printf("Digite seu nome: ");
    scanf("%s", nome);
    printf("Digite sua senha: ");
    scanf("%d", &senha);

    if (funcionario_existe(cpf, senha)){
        printf("Funcionário já cadastrado.\n");
    } else {
        struct Funcionario novo_funcionario = {cpf, "", senha};
        strcpy(novo_funcionario.nome, nome);
        salvar_funcionario(novo_funcionario);
        printf("Funcionário cadastrado com sucesso!\n");
        menu_login();
    }
}


void novo_cliente(void) {
    int cnpj;
    char razao_social[100];
    char conta[10];
    float saldo;
    int senha;

    printf("Digite seu CNPJ: ");
    scanf("%d", &cnpj);
    printf("Digite sua razão social: ");
    scanf("%s", razao_social);
    printf("Digite o tipo da conta (Comum ou Plus): ");
    scanf("%s", conta);
    printf("Digite o saldo inicial: ");
    scanf("%f", &saldo);
    printf("Digite sua senha: ");
    scanf("%d", &senha);

    if (cliente_existe(cnpj, senha)) {
        printf("Cliente já cadastrado.\n");
    } else {
        struct Cliente novo_cliente = {cnpj, "", "", 0, senha};
        strcpy(novo_cliente.razao_social, razao_social);
        strcpy(novo_cliente.conta, conta);
        novo_cliente.saldo = saldo;
        salvar_cliente(novo_cliente);
        printf("Cliente cadastrado com sucesso!\n");
    }
}


void login(void) {
    int tipo_de_login;
    printf("Qual login deseja acessar? (Funcionário = 1) (Cliente = 2): ");
    scanf("%d", &tipo_de_login);

    if (tipo_de_login == 1) {
        int cpf, senha;
        printf("Digite seu CPF: ");
        scanf("%d", &cpf);
        printf("Digite sua senha: ");
        scanf("%d", &senha);

        if (funcionario_existe(cpf, senha)) {
            printf("Login de funcionário bem-sucedido.\n");
            menu_funcionario();
        } else {
            printf("Login de funcionário inválido.\n");
        }
    } else if (tipo_de_login == 2) {
        int cnpj, senha;
        printf("Digite seu CNPJ: ");
        scanf("%d", &cnpj);
        printf("Digite sua senha: ");
        scanf("%d", &senha);

        if (cliente_existe(cnpj, senha)) {
            printf("Login de cliente bem-sucedido.\n");
            menu_cliente();
        } else {
            printf("Login de cliente inválido.\n");
        }
    } else {
        printf("Opção inválida.\n");
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


void debito(){
  //
}


void deposito(){
  //
}


void transferencia(){
  //
}


void extrato(){
  //
}


void listar_clientes(){
  //
}


void apagar_clientes(struct Cliente *clientes, int tamanho) {
  int cnpj;
  printf("Digite o CNPJ que deseja excluir: ");
  scanf("%d", &cnpj);
  FILE *arquivo = fopen("clientes.dat", "rb");
  if (arquivo == NULL) {
    printf("Falha ao abrir o arquivo.\n");
    exit(1);
  }
  for (int i = 0; i < tamanho; i++) {
    fread(&clientes[i], sizeof(struct Cliente), 1, arquivo);
    if (clientes[i].cnpj == cnpj) {
      memmove(&clientes[i], &clientes[i + 1], (tamanho - i - 1) * sizeof(struct Cliente));
      tamanho--;
      menu_funcionario();
    }
  }

  // Fecha o arquivo clientes.dat
  fclose(arquivo);
}

  
void listar_funcionarios(){
  //
}


void apagar_funcionarios(){
  //
}


void menu_cliente(){
      int menu_cliente;

      while (1) {
          printf("1. Débito\n");
          printf("2. Déposito\n");
          printf("3. Extrato\n");
          printf("4. Transferencia\n");
          printf("5. Sair\n");
          printf("Digite o número respectivo à opção desejada: ");
          scanf("%d", &menu_cliente);

          if (menu_cliente == 5) {
              break;
          } else if (menu_cliente == 1) {
              debito();
          } else if (menu_cliente == 2) {
              deposito();
          } else if (menu_cliente == 3) {
              extrato();
          }else if (menu_cliente == 4) {
              transferencia();
        }
      }
  }


void menu_funcionario(){
  int menu_funcionario;
  int tamanho = 0;
  struct Cliente clientes;
  
  while (1) {
      printf("1. Listar clientes\n");
      printf("2. Apagar clientes\n");
      printf("3. Listar funcionários\n");
      printf("4. Apagar funcionários\n");
      printf("5. Sair\n");
      printf("Digite o número respectivo à opção desejada: ");
      scanf("%d", &menu_funcionario);

      if (menu_funcionario == 5) {
          break;
      } else if (menu_funcionario == 1) {
          listar_clientes();
      } else if (menu_funcionario == 2) {
          apagar_clientes(&clientes, tamanho);
      } else if (menu_funcionario == 3) {
          listar_funcionarios();
      }else if (menu_funcionario == 4) {
          apagar_funcionarios();
    }
  }
}
