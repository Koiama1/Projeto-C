#include "funcao.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

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

  if (funcionario_existe(cpf, senha)) {
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
    menu_login();
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
  while (menu != 4) {
    printf("1. Cadastrar funcionário\n");
    printf("2. Cadastrar cliente\n");
    printf("3. Login\n");
    printf("4. Sair\n");
    printf("Digite o número respectivo à opção desejada: ");
    scanf("%d", &menu);
    if (menu == 1) {
      novo_funcionario();
    } else if (menu == 2) {
      novo_cliente();
    } else if (menu == 3) {
      login();
    }
  }
}

void debito(struct Cliente *clientes, int tamanho) {
  int cnpj;
  printf("Digite seu CNPJ: ");
  scanf("%d", &cnpj);

  FILE *arquivo = fopen("clientes.dat", "rb+");
  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo de clientes.\n");
    exit(1);
  }

  struct Cliente cliente;

  while (fread(&cliente, sizeof(struct Cliente), 1, arquivo)) {
    if (cliente.cnpj == cnpj) {
      int senha;
      printf("Digite sua senha: ");
      scanf("%d", &senha);

      if (cliente.senha != senha) {
        printf("Senha incorreta\n");
        fclose(arquivo);
        return;
      }

      float valor;
      printf("Digite o valor: ");
      scanf("%f", &valor);

      float tarifa;
      if (strcmp(cliente.conta, "Comum") == 0) {
        tarifa = valor * 0.05;
      } else if (strcmp(cliente.conta, "Plus") == 0) {
        tarifa = valor * 0.03;
      }

      float valor_tarifado = valor + tarifa;

      if (cliente.saldo - valor_tarifado >= -1000 &&
          strcmp(cliente.conta, "Comum") == 0) {
        cliente.saldo -= valor_tarifado;
        printf("Saldo atual: R$ %.2f\n", cliente.saldo);

        fseek(arquivo, -sizeof(struct Cliente), SEEK_CUR);
        fwrite(&cliente, sizeof(struct Cliente), 1, arquivo);

        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        char data_str[100];
        sprintf(data_str, "Data: %02d/%02d/%04d %02d:%02d", tm.tm_mday,
                tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min);

        FILE *historico_arquivo = fopen("historico.txt", "a");
        if (historico_arquivo == NULL) {
          printf("Erro ao abrir o arquivo de histórico.\n");
          exit(1);
        }

        fprintf(historico_arquivo, "%s - Débito de %.2f saindo do CNPJ: %d\n",
                data_str, valor, cnpj);
        fclose(historico_arquivo);

        printf("Débito realizado com sucesso! Novo saldo: %.2f\n",
               cliente.saldo);
        return;

        fclose(arquivo);
        return;

    
      } else if (cliente.saldo - valor_tarifado >= -5000 &&
                 strcmp(cliente.conta, "Plus") == 0) {
        cliente.saldo -= valor_tarifado;
        printf("Saldo atual: R$ %.2f\n", cliente.saldo);

        fseek(arquivo, -sizeof(struct Cliente), SEEK_CUR);
        fwrite(&cliente, sizeof(struct Cliente), 1, arquivo);

        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        char data_str[100];
        sprintf(data_str, "Data: %02d/%02d/%04d %02d:%02d", tm.tm_mday,
                tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min);

        FILE *historico_arquivo = fopen("historico.txt", "a");
        if (historico_arquivo == NULL) {
          printf("Erro ao abrir o arquivo de histórico.\n");
          exit(1);
        }

        fprintf(historico_arquivo, "%s - Débito de %.2f saindo do CNPJ: %d\n",
                data_str, valor, cnpj);
        fclose(historico_arquivo);

        printf("Débito realizado com sucesso! Novo saldo: %.2f\n",
               cliente.saldo);
        return;

        fclose(arquivo);
        return;
      } else {
        printf("Saldo insuficiente\n");
        fclose(arquivo);
        return;
      }
    }
  }

  printf("Cliente com CNPJ %d não encontrado.\n", cnpj);
  fclose(arquivo);
}

void deposito(struct Cliente *clientes, int tamanho) {
  int cnpj;
  float valor;
  printf("Digite o CNPJ referente à conta do depósito: ");
  scanf("%d", &cnpj);
  printf("Digite o valor: ");
  scanf("%f", &valor);

  FILE *arquivo = fopen("clientes.dat", "rb+");
  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo de clientes.\n");
    exit(1);
  }

  struct Cliente cliente;
  while (fread(&cliente, sizeof(struct Cliente), 1, arquivo)) {
    if (cliente.cnpj == cnpj) {
      cliente.saldo += valor;
      fseek(arquivo, -sizeof(struct Cliente), SEEK_CUR);
      fwrite(&cliente, sizeof(struct Cliente), 1, arquivo);
      fclose(arquivo);

      time_t t = time(NULL);
      struct tm tm = *localtime(&t);
      char data_str[100];
      sprintf(data_str, "Data: %02d/%02d/%04d %02d:%02d", tm.tm_mday,
              tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min);

      FILE *historico_arquivo = fopen("historico.txt", "a");
      if (historico_arquivo == NULL) {
        printf("Erro ao abrir o arquivo de histórico.\n");
        exit(1);
      }

      fprintf(historico_arquivo, "%s - Depósito de %.2f para CNPJ: %d\n",
              data_str, valor, cnpj);
      fclose(historico_arquivo);

      printf("Depósito realizado com sucesso! Novo saldo: %.2f\n",
             cliente.saldo);
      return;
    }
  }

  fclose(arquivo);
  printf("Cliente com CNPJ %d não encontrado.\n", cnpj);
}

void transferencia() {
  debito(0, 0);
  deposito(0, 0);
}

void extrato() {
  //
}

void listar_clientes() {
  FILE *arquivo = fopen("clientes.dat", "rb");
  if (arquivo == NULL) {
    printf("Falha ao abrir o arquivo.\n");
    exit(1);
  }

  printf("====================================================\n");
  printf("| CNPJ | Razão social | Tipo de conta | Saldo |\n");
  printf("====================================================\n");

  struct Cliente cliente;
  while (fread(&cliente, sizeof(struct Cliente), 1, arquivo) == 1) {
    printf("| %d | %s | %s | %.2f |\n", cliente.cnpj, cliente.razao_social,
           cliente.conta, cliente.saldo);
  }

  if (fread(&cliente, sizeof(struct Cliente), 1, arquivo) == 0)
    fclose(arquivo);
}

void apagar_clientes(struct Cliente *clientes, int tamanho) {
  int cnpj;
  printf("Digite o CNPJ da conta que deseja excluir: ");
  scanf("%d", &cnpj);

  FILE *arquivo = fopen("clientes.dat", "rb+");
  if (arquivo == NULL) {
    printf("Falha ao abrir o arquivo de clientes.\n");
    return;
  }

  struct Cliente cliente;
  size_t tamanho_cliente = sizeof(struct Cliente);

  int encontrado = 0;
  while (fread(&cliente, tamanho_cliente, 1, arquivo) == 1) {
    if (cliente.cnpj == cnpj) {
      encontrado = 1;
      break;
    }
  }

  if (encontrado) {
    fseek(arquivo, -tamanho_cliente, SEEK_CUR);

    memset(&cliente, 0, tamanho_cliente);

    fwrite(&cliente, tamanho_cliente, 1, arquivo);
    fclose(arquivo);
    printf("Cliente com CNPJ %d apagado com sucesso.\n", cnpj);
  } else {
    fclose(arquivo);
    printf("Cliente com CNPJ %d não encontrado.\n", cnpj);
  }
}

void listar_funcionarios() {
  FILE *arquivo = fopen("funcionarios.dat", "rb");
  if (arquivo == NULL) {
    printf("Falha ao abrir o arquivo.\n");
    exit(1);
  }

  printf("=================\n");
  printf("| CPF | NOME |\n");
  printf("=================\n");

  struct Funcionario funcionario;
  while (fread(&funcionario, sizeof(struct Funcionario), 1, arquivo) == 1) {
    printf("| %d | %s |\n", funcionario.cpf, funcionario.nome);
  }

  if (fread(&funcionario, sizeof(struct Funcionario), 1, arquivo) == 0)
    fclose(arquivo);
}

void apagar_funcionarios(struct Funcionario *funcionarios, int tamanho) {
  int cpf;
  printf("Digite o CPF da conta que deseja excluir: ");
  scanf("%d", &cpf);

  FILE *arquivo = fopen("funcionarios.dat", "rb+");
  if (arquivo == NULL) {
    printf("Falha ao abrir o arquivo de funcionarios.\n");
    return;
  }

  struct Funcionario funcionario;
  size_t tamanho_funcionario = sizeof(struct Funcionario);

  int encontrado = 0;
  while (fread(&funcionario, tamanho_funcionario, 1, arquivo) == 1) {
    if (funcionario.cpf == cpf) {
      encontrado = 1;
      break;
    }
  }

  if (encontrado) {
    fseek(arquivo, -tamanho_funcionario, SEEK_CUR);

    memset(&funcionario, 0, tamanho_funcionario);

    fwrite(&funcionario, tamanho_funcionario, 1, arquivo);
    fclose(arquivo);
    printf("Funcionário com CPF %d apagado com sucesso.\n", cpf);
  } else {
    fclose(arquivo);
    printf("Funcionário com CPF %d não encontrado.\n", cpf);
  }
}

void menu_cliente() {
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
      debito(0, 0);
    } else if (menu_cliente == 2) {
      deposito(0, 0);
    } else if (menu_cliente == 3) {
      extrato();
    } else if (menu_cliente == 4) {
      transferencia();
    }
  }
}

void menu_funcionario() {
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
      apagar_clientes(0, 0);
    } else if (menu_funcionario == 3) {
      listar_funcionarios();
    } else if (menu_funcionario == 4) {
      apagar_funcionarios(0, 0);
    }
  }
}
