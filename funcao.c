#include "funcao.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Aluno: João Pedro Lopes Santana Villas Bôas - RA: 24.123.071-3
//Aluno: João Pedro Gardenghi Peterutto - RA: 24.123.045-7
//Aluno: Gabriel Koiama Rocha de Oliveira Lira - RA: 24.123.051-5

//Função para salvar os clientes criados no arquivo binario
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

//Função para salvar os funcionários criados no arquivo binario
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

//Função para ver se os clientes estão cadastrados no arquivo binario
int cliente_existe(int cpf, int senha) {
  FILE *arquivo;
  struct Cliente cliente;

  arquivo = fopen("clientes.dat", "rb");
  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo de clientes.\n");
    exit(1);
  }

  while (fread(&cliente, sizeof(struct Cliente), 1, arquivo)) {
    if (cliente.cpf == cpf && cliente.senha == senha) {
      fclose(arquivo);
      return 1;
    }
  }

  fclose(arquivo);
  return 0;
}

//Função para ver se os funcionários estão cadastrados no arquivo binario
int funcionario_existe(int cpf_funcionario, int senha) {
  FILE *arquivo;
  struct Funcionario funcionario;

  arquivo = fopen("funcionarios.dat", "rb");
  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo de funcionários.\n");
    exit(1);
  }

  while (fread(&funcionario, sizeof(struct Funcionario), 1, arquivo)) {
    if (funcionario.cpf_funcionario == cpf_funcionario && funcionario.senha == senha) {
      fclose(arquivo);
      return 1;
    }
  }

  fclose(arquivo);
  return 0;
}

//Função para criar um novo funcionário
void novo_funcionario(void) {
  int cpf_funcionario;
  char nome[100];
  int senha;

  printf("Digite seu CPF: ");
  scanf("%d", &cpf_funcionario);
  printf("Digite seu nome: ");
  scanf("%s", nome);
  printf("Digite sua senha: ");
  scanf("%d", &senha);

  if (funcionario_existe(cpf_funcionario, senha)) {
    printf("Funcionário já cadastrado.\n");
  } else {
    struct Funcionario novo_funcionario = {cpf_funcionario, "", senha};
    strcpy(novo_funcionario.nome, nome);
    salvar_funcionario(novo_funcionario);
    printf("Funcionário cadastrado com sucesso!\n");
    menu_login();
  }
}

//Função para criar um novo cliente
void novo_cliente(void) {
  int cpf;
  char nome_cliente[100];
  char conta[10];
  float saldo;
  int senha;

  printf("Digite seu CPF: ");
  scanf("%d", &cpf);
  printf("Digite seu nome: ");
  scanf("%s", nome_cliente);
  printf("Digite o tipo da conta (Comum ou Plus): ");
  scanf("%s", conta);
  printf("Digite o saldo inicial: ");
  scanf("%f", &saldo);
  printf("Digite sua senha: ");
  scanf("%d", &senha);

  if (cliente_existe(cpf, senha)) {
    printf("Cliente já cadastrado.\n");
  } else {
    struct Cliente novo_cliente = {cpf, "", "", 0, senha};
    strcpy(novo_cliente.nome_cliente, nome_cliente);
    strcpy(novo_cliente.conta, conta);
    novo_cliente.saldo = saldo;
    salvar_cliente(novo_cliente);
    printf("Cliente cadastrado com sucesso!\n");
    menu_login();
  }
}

//Função de login para escolher qual conta acessar, a de funcionário ou a de cliente
void login(void) {
  int tipo_de_login;
  printf("Qual login deseja acessar? (Funcionário = 1) (Cliente = 2): ");
  scanf("%d", &tipo_de_login);

  if (tipo_de_login == 1) {
    int cpf_funcionario, senha;
    printf("Digite seu CPF: ");
    scanf("%d", &cpf_funcionario);
    printf("Digite sua senha: ");
    scanf("%d", &senha);

    if (funcionario_existe(cpf_funcionario, senha)) {
      printf("Login de funcionário bem-sucedido.\n");
      menu_funcionario();
    } else {
      printf("Login de funcionário inválido.\n");
    }
  } else if (tipo_de_login == 2) {
    int cpf, senha;
    printf("Digite seu CPF: ");
    scanf("%d", &cpf);
    printf("Digite sua senha: ");
    scanf("%d", &senha);

    if (cliente_existe(cpf, senha)) {
      printf("Login de cliente bem-sucedido.\n");
      menu_cliente();
    } else {
      printf("Login de cliente inválido.\n");
    }
  } else {
    printf("Opção inválida.\n");
  }
}

//Função inicial do programa em que apresenta as principais opções para utilizar o programa
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

//Função para realizar um débito
void debito(struct Cliente *clientes, int tamanho) {
  int cpf;
  printf("Digite seu CPF: ");
  scanf("%d", &cpf);

  FILE *arquivo = fopen("clientes.dat", "rb+");
  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo de clientes.\n");
    exit(1);
  }

  struct Cliente cliente;

  while (fread(&cliente, sizeof(struct Cliente), 1, arquivo)) {
    if (cliente.cpf == cpf) {
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

        fprintf(historico_arquivo, "%s - Débito de %.2f (mais %.2f de tarifa) saindo do CPF: %d\n",
                data_str, valor, tarifa, cpf);
        fclose(historico_arquivo);

        printf("Débito realizado com sucesso! Novo saldo: %.2f\n",
               cliente.saldo);

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

        fprintf(historico_arquivo, "%s - Débito de %.2f (mais %.2f de tarifa) saindo do CPF: %d\n",
                data_str, valor, tarifa, cpf);
        fclose(historico_arquivo);

        printf("Débito realizado com sucesso! Novo saldo: %.2f\n",
               cliente.saldo);

        fclose(arquivo);
        return;
      } else {
        printf("Saldo insuficiente\n");
        fclose(arquivo);
        return;
      }
    }
  }

  printf("Cliente com CPF %d não encontrado.\n", cpf);
  fclose(arquivo);
}

//Função para realizar um depósito
void deposito(struct Cliente *clientes, int tamanho) {
  int cpf;
  float valor;
  printf("Digite o CPF referente à conta do depósito: ");
  scanf("%d", &cpf);
  printf("Digite o valor: ");
  scanf("%f", &valor);

  int cpf_real;
  cpf_real = cpf;

  FILE *arquivo = fopen("clientes.dat", "rb+");
  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo de clientes.\n");
    exit(1);
  }

  struct Cliente cliente;
  while (fread(&cliente, sizeof(struct Cliente), 1, arquivo)) {
    if (cliente.cpf == cpf) {
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

      fprintf(historico_arquivo, "%s - Depósito de %.2f para CPF: %d\n", data_str, valor, cpf_real);
      fclose(historico_arquivo);

      printf("Depósito realizado com sucesso! Novo saldo: %.2f\n",cliente.saldo);
      return;
    }
  }

  fclose(arquivo);
  printf("Cliente com CPF %d não encontrado.\n", cpf);
}

//Função para realizar uma transferência
void transferencia() {
  debito(0, 0);
  deposito(0, 0);
}

//Função que irá acessar o histórico de transações e imprimi-lo
void imprimir_historico(int cpf) {
    FILE *arquivo = fopen("historico.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de histórico.\n");
        return;
    }

    char linha[256];
    int numero_linha = 1;
    int encontrou = 0;

    while (fgets(linha, sizeof(linha), arquivo)) {
        char *cpf_str = strstr(linha, "CPF:");
        if (cpf_str != NULL) {
            cpf_str += 5;
            int cpf_lido;
            if (sscanf(cpf_str, "%d", &cpf_lido) == 1) {
                if (cpf_lido == cpf) {
                    encontrou = 1;
                    printf("%d - %s", numero_linha, linha);
                }
            }
        }
        numero_linha++;
    }
    fclose(arquivo);
    if (!encontrou) {
        printf("Nenhuma transação encontrada para o CPF %d.\n", cpf);
    }
}

//Função para acessar os dados do cliente para poder chamar a função imprimir_histórico
void extrato(struct Cliente clientes[], int num_clientes) {
    int cpf;
    printf("Digite o CPF da conta que quer acessar o extrato: ");
    scanf("%d", &cpf);

    FILE *arquivo_clientes = fopen("clientes.dat", "rb");
    if (arquivo_clientes == NULL) {
        printf("Erro ao abrir o arquivo de clientes.\n");
        return;
    }

    struct Cliente cliente;
    int encontrado = 0;

    while (fread(&cliente, sizeof(struct Cliente), 1, arquivo_clientes) == 1) {
        if (cliente.cpf == cpf) {
            encontrado = 1;
            int senha;
            printf("Digite a senha referente ao CPF: ");
            scanf("%d", &senha);

            if (cliente.senha == senha) {
                printf("Nome: %s\n", cliente.nome_cliente);
                printf("CPF: %d\n", cliente.cpf);
                printf("Conta: %s\n", cliente.conta);
                printf("Saldo atual: %.2f\n", cliente.saldo);

                imprimir_historico(cpf);
            } else {
                printf("Senha incorreta\n");
            }
            break;
        }
    }

    if (!encontrado) {
        printf("CPF inválido\n");
    }

    fclose(arquivo_clientes);
}

//Função para listar todos os clientes criados
void listar_clientes() {
  FILE *arquivo = fopen("clientes.dat", "rb");
  if (arquivo == NULL) {
    printf("Falha ao abrir o arquivo.\n");
    exit(1);
  }

  printf("====================================================\n");
  printf("| CPF | NOME | Tipo de conta | Saldo |\n");
  printf("====================================================\n");

  struct Cliente cliente;
  while (fread(&cliente, sizeof(struct Cliente), 1, arquivo) == 1) {
    printf("| %d | %s | %s | %.2f |\n", cliente.cpf, cliente.nome_cliente,
           cliente.conta, cliente.saldo);
  }

  if (fread(&cliente, sizeof(struct Cliente), 1, arquivo) == 0)
    fclose(arquivo);
}

//Função para apagar um cliente em específico e todos os seus dados
void apagar_clientes(struct Cliente *clientes, int tamanho) {
  int cpf;
  printf("Digite o CPF da conta que deseja excluir: ");
  scanf("%d", &cpf);

  FILE *arquivo = fopen("clientes.dat", "rb+");
  if (arquivo == NULL) {
    printf("Falha ao abrir o arquivo de clientes.\n");
    return;
  }

  struct Cliente cliente;
  size_t tamanho_cliente = sizeof(struct Cliente);

  int encontrado = 0;
  while (fread(&cliente, tamanho_cliente, 1, arquivo) == 1) {
    if (cliente.cpf == cpf) {
      encontrado = 1;
      break;
    }
  }

  if (encontrado) {
    fseek(arquivo, -tamanho_cliente, SEEK_CUR);

    memset(&cliente, 0, tamanho_cliente);

    fwrite(&cliente, tamanho_cliente, 1, arquivo);
    fclose(arquivo);
    printf("Cliente com CPF %d apagado com sucesso.\n", cpf);
  } else {
    fclose(arquivo);
    printf("Cliente com CPF %d não encontrado.\n", cpf);
  }
}

//Função para listar todos os funcionários criados
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
    printf("| %d | %s |\n", funcionario.cpf_funcionario, funcionario.nome);
  }

  if (fread(&funcionario, sizeof(struct Funcionario), 1, arquivo) == 0)
    fclose(arquivo);
}

//Função para apagar um funcionário em específico e todos os seus dados
void apagar_funcionarios(struct Funcionario *funcionarios, int tamanho) {
  int cpf_funcionario;
  printf("Digite o CPF da conta que deseja excluir: ");
  scanf("%d", &cpf_funcionario);

  FILE *arquivo = fopen("funcionarios.dat", "rb+");
  if (arquivo == NULL) {
    printf("Falha ao abrir o arquivo de funcionarios.\n");
    return;
  }

  struct Funcionario funcionario;
  size_t tamanho_funcionario = sizeof(struct Funcionario);

  int encontrado = 0;
  while (fread(&funcionario, tamanho_funcionario, 1, arquivo) == 1) {
    if (funcionario.cpf_funcionario == cpf_funcionario) {
      encontrado = 1;
      break;
    }
  }

  if (encontrado) {
    fseek(arquivo, -tamanho_funcionario, SEEK_CUR);

    memset(&funcionario, 0, tamanho_funcionario);

    fwrite(&funcionario, tamanho_funcionario, 1, arquivo);
    fclose(arquivo);
    printf("Funcionário com CPF %d apagado com sucesso.\n", cpf_funcionario);
  } else {
    fclose(arquivo);
    printf("Funcionário com CPF %d não encontrado.\n", cpf_funcionario);
  }
}

//Função do menu do cliente
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
      extrato(0, 0);
    } else if (menu_cliente == 4) {
      transferencia();
    }
  }
}

//Função do menu do funcionário
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
