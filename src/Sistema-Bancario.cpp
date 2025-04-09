
/*
 * Projeto: Sistema Bancário
 * Autor: João Paulo
 * Data: Dezembro de 2024
 * Disciplina: Lógica de Programação
 *
 * Descrição:
 * Sistema de atendimento bancário desenvolvido em linguagem C como projeto final da disciplina de Lógica de Programação.
 * O sistema simula o funcionamento de um banco, permitindo a criação e gerenciamento de contas bancárias,
 * com funcionalidades como:
 * 
 * - Geração de senhas para atendimento (normal e prioritário)
 * - Cadastro e autenticação de clientes
 * - Atualização de dados cadastrais (Pix, endereço, e-mail, telefone, senha, etc.)
 * - Operações bancárias: depósitos, saques, transferências, consultas de saldo e extrato
 * - Emissão de comprovantes
 * - Armazenamento e atualização de dados persistente em arquivos .txt por CPF
 
 * O projeto também inclui uma interface de navegação com menu interativo e cores no terminal,
 * além de validações completas de dados (e-mail, CPF, senha, chave Pix, entre outros).
 *
 * Objetivo:
 * Aplicar os conhecimentos de lógica de programação, estruturas de dados, manipulação de arquivos
 * e organização de código modular para resolver problemas reais de forma prática.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

#define MAX 10

typedef struct {
	char nome[30];
	char tipoServico[30];
	char prioridade;
	char data[20];
	int mesas[2];
	char senha[10];
	char arquivoComprovante[50];
	char cpf[20];
} Cliente;

typedef struct {
	Cliente clientes[MAX];
	int frente;
	int atras;
	int senhaPrioritaria;
	int senhaNormal;
} FilaBanco;

typedef struct {
	char nomeCompleto[100];
	char dataNascimento[11];
	char cpf[15];
	char senha[20];
	char senhaTransacao[5];
	char perguntaSecreta[100];
	char respostaSecreta[100];
	float saldo;
	char pix[30];
	char numeroConta[10];
	char telefone[20];
	char email[30];
	char tipoConta[50];
	char sobrenome[20];

	char rua[100];
	char numero[10];
	char bairro[50];
	char cidade[50];
	char estado[3];
	char cep[10];

} ContaBancaria;

void entrarNaFila(FilaBanco *fila);
void menu();
void servicos();
void gerarComprovante(FilaBanco *fila, int indice);
void exibirFila(FilaBanco *fila);
void atenderCliente(FilaBanco *fila);
void CriarConta(ContaBancaria *conta);
void DeletarConta(ContaBancaria *conta);
void excluirSenha(FilaBanco *fila);
void consultarSaldo(char *cpf, char *senha, int recursivo);
void realizarDeposito(char *cpf, char *senha, int recursivo);
void realizarSaque(char *cpf, char *senha, int recursivo);
void realizarTransferencia(char *cpf, char *senha, int recursivo);
void extrato(char *cpf, char *senha, int recursivo);
void cab();
void exibirPontos();
void gerarCodigoTransacao(char *codigoTransacao);
void atualizarCadastro();
void atualizarPix(const char *cpf);
int validarSiglaEstado(char *sigla);
void mascararCPF(char *cpf, char *cpfFormatado);
int chavePixJaCadastrada(const char *arquivo, const char *chavePix);

void corTexto(int cor) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), cor);
}

char cpf[20];
float saldo = 0.0;
int op;
char senha[20];
char cpfRemetente[20];
float saldoRemetente = 0.0;

int main() {
	setlocale(LC_ALL, "Portuguese");
	ContaBancaria conta;
	FilaBanco fila;
	fila.frente = 0;
	fila.atras = 0;
	fila.senhaPrioritaria = 1;
	fila.senhaNormal = 1;
	conta.saldo = 0.0f;

	do {
		menu();

		switch (op) {
			case 1:
				entrarNaFila(&fila);
				break;
			case 2:
				system("cls");
				atenderCliente(&fila);
				break;
			case 3:
				exibirFila(&fila);
				break;
			case 4:
				excluirSenha(&fila);
				break;
			case 0:
				printf("Saindo do sistema...\n");
				break;
			default:
				system("cls");
				corTexto(12);
				printf("\nOpção inválida. Tente novamente.\n");
				corTexto(11);
		}
	} while (op != 0);

	return 0;
}

void menu() {
	corTexto(9);
	printf("\n==============================\n");
	corTexto(14);
	printf("     Sistema Bancário         \n");
	printf("        ProtecBank         \n");
	printf("     Seja bem-vindo(a)        \n");
	corTexto(9);
	printf("==============================\n");
	corTexto(11);
	printf("\n=== Sistema de Atendimento do Banco ===\n\n");
	corTexto(14);
	printf("1. Pegar uma senha\n");
	printf("2. Atender próximo cliente\n");
	printf("3. Exibir senhas\n");
	printf("4. Excluir uma senha\n");
	printf("0. Sair\n");
	corTexto(11);
	printf("\nEscolha uma opção: ");
	scanf("%d", &op);
	getchar();
}

void servicos() {
	system("cls");
	do {

		corTexto(9);
		printf("\n====================================\n");
		corTexto(14);
		printf("    	   ProtecBank      \n");
		printf("==== Sistema de senhas do Banco ====\n");

		corTexto(9);
		printf("====================================\n\n");
		corTexto(11);
		printf("=== Tipos de Serviço Disponíveis ===       \n\n");

		corTexto(14);
		printf("  [1]  %s\n", "Abrir Conta");
		printf("  [2]  %s\n", "Encerrar Conta");
		printf("  [3]  %s\n", "Consultar Saldo");
		printf("  [4]  %s\n", "Realizar Depósito");
		printf("  [5]  %s\n", "Realizar Saque");
		printf("  [6]  %s\n", "Transferir Valores");
		printf("  [7]  %s\n", "Extrato");
		printf("  [8]  %s\n", "Atualizacões cadastrais");
		corTexto(11);
		printf("\n====================================\n");
		printf("Escolha o serviço que deseja: ");
		corTexto(11);
		scanf("%d", &op);
		getchar();

		if(op <0 || op >8) {
			system("cls");
			corTexto(12);
			printf("\n	Opção inválida!!!");
			corTexto(11);
		}

	} while(op <0 || op >8);
}

void cab() {

	printf("\n           PROTECBANNK - ATENDIMENTO\n");

}

void entrarNaFila(FilaBanco *fila) {

	// Adiciona um cliente à fila com base no tipo de serviço e prioridade, gerando senha e comprovante.

	char opcao;

	if (fila->atras == MAX) {
		printf("A fila está cheia. Tente novamente mais tarde.\n");
		return;
	}

	Cliente cliente;
	servicos();

	int tipoServico = op;
	switch (tipoServico) {
		case 1:
			strcpy(cliente.tipoServico, "Abrir Conta");
			cliente.mesas[0] = 1;
			cliente.mesas[1] = 2;
			break;
		case 2:
			strcpy(cliente.tipoServico, "Encerrar Conta");
			cliente.mesas[0] = 3;
			cliente.mesas[1] = 4;
			break;
		case 3:
			strcpy(cliente.tipoServico, "Consultar Saldo");
			cliente.mesas[0] = 5;
			cliente.mesas[1] = 6;
			break;
		case 4:
			strcpy(cliente.tipoServico, "Realizar Depósito");
			cliente.mesas[0] = 7;
			cliente.mesas[1] = 8;
			break;
		case 5:
			strcpy(cliente.tipoServico, "Realizar Saque");
			cliente.mesas[0] = 9;
			cliente.mesas[1] = 10;
			break;
		case 6:
			strcpy(cliente.tipoServico, "Transferir Valores");
			cliente.mesas[0] = 11;
			cliente.mesas[1] = 12;
			break;
		case 7:
			strcpy(cliente.tipoServico, "Extrato");
			cliente.mesas[0] = 13;
			cliente.mesas[1] = 14;
			break;

		case 8:
			strcpy(cliente.tipoServico, "Atualizacões cadastrais");
			cliente.mesas[0] = 14;
			cliente.mesas[1] = 15;
			break;

		default:
			return;
	}

	printf("\nComo você deseja ser chamado?: ");
	corTexto(14);
	fgets(cliente.nome, sizeof(cliente.nome), stdin);
	cliente.nome[strcspn(cliente.nome, "\n")] = '\0';
	corTexto(11);

	do {
		printf("\nO atendimento é prioritário? (S/N): ");
		corTexto(14);
		scanf(" %c", &cliente.prioridade);
		fflush(stdin);
		corTexto(11);

		if (cliente.prioridade != 's' && cliente.prioridade != 'S' && cliente.prioridade != 'N' && cliente.prioridade != 'n') {
			corTexto(12);
			printf("\nOpção inválida!!!\n\n");
			corTexto(11);
		}

	} while(cliente.prioridade != 's' && cliente.prioridade != 'S' && cliente.prioridade != 'N' && cliente.prioridade != 'n');


	printf("\nServiço para ");
	corTexto(14);
	printf("'%s'", cliente.tipoServico);
	corTexto(11);
	printf(" confirmado! Gerando sua senha, aguarde");
	exibirPontos();

	time_t agora = time(NULL);
	struct tm *dataHora = localtime(&agora);
	strftime(cliente.data, sizeof(cliente.data), "%d/%m/%Y %H:%M", dataHora);

	if (cliente.prioridade == 'S' || cliente.prioridade == 's') {

		snprintf(cliente.senha, sizeof(cliente.senha), "P%03d", fila->senhaPrioritaria);
		fila->senhaPrioritaria++;
	} else {

		snprintf(cliente.senha, sizeof(cliente.senha), "%03d", fila->senhaNormal);
		fila->senhaNormal++;
	}

	fila->clientes[fila->atras] = cliente;

	fila->atras++;

	gerarComprovante(fila, fila->atras - 1);
	system("cls");
}

void gerarComprovante(FilaBanco *fila, int indice) {

	// Gera um comprovante em .txt com os dados do cliente e imprime no terminal.

	system("cls");

	char *nomeCliente = fila->clientes[indice].nome;
	char *tipoServico = fila->clientes[indice].tipoServico;
	char *senha = fila->clientes[indice].senha;
	char *dataHoraStr = fila->clientes[indice].data;
	int mesa1 = fila->clientes[indice].mesas[0];
	int mesa2 = fila->clientes[indice].mesas[1];
	
	time_t agora = time(NULL);
	struct tm *dataHora = localtime(&agora);
	char nomeArquivo[50];
	sprintf(nomeArquivo, "senha_%s_%s.txt", senha, tipoServico);

	strcpy(fila->clientes[indice].arquivoComprovante, nomeArquivo);

	FILE *arquivo = fopen(nomeArquivo, "w");
	if (arquivo == NULL) {
		printf("Erro ao criar o arquivo do comprovante.\n");
		return;
	}

	printf("---------------------------------------\n");
	printf(" %s Sua senha foi gerada com sucesso!\n",fila->clientes[indice].nome);
	printf("---------------------------------------\n");

	fprintf(arquivo, "|====== SENHA DE ATENDIMENTO ======|\n");
	fprintf(arquivo, "|  Banco ProtecBank                |\n");
	fprintf(arquivo, "|  Agência: 0001                   |\n");
	fprintf(arquivo, "|  Mesa de Atendimento: %2d e %2d    |\n", mesa1, mesa2);
	fprintf(arquivo, "|  Cliente: %-23s|\n", nomeCliente);
	fprintf(arquivo, "|  Serviço: %-23s|\n", tipoServico);
	fprintf(arquivo, "|  Senha: %-25s|\n", senha);
	fprintf(arquivo, "|  Data/Hora: %-15s     |\n", dataHoraStr);
	fprintf(arquivo, "|                                  |\n");
	fprintf(arquivo, "|  Aguarde sua senha ser chamada.  |\n");
	fprintf(arquivo, "|                                  |\n");
	fprintf(arquivo, "+----------------------------------+\n\n");

	corTexto(14);
	printf(" \n");
	printf("|====== SENHA DE ATENDIMENTO ======|\n");
	printf("|  Banco ProtecBank                |\n");
	printf("|  Agência: 0001                   |\n");
	printf("|  Mesa de Atendimento: %2d e %2d    |\n", mesa1, mesa2);
	printf("|  Cliente: %-23s|\n", nomeCliente);
	printf("|  Serviço: %-23s|\n", tipoServico);
	printf("|  Senha: %-25s|\n", senha);
	printf("|  Data/Hora: %-15s     |\n", dataHoraStr);
	printf("|                                  |\n");
	printf("|  Aguarde sua senha ser chamada.  |\n");
	printf("|                                  |\n");
	printf("+----------------------------------+\n\n");
	corTexto(11);
	fclose(arquivo);
	printf("Pressione Enter para voltar ao menu...\n");
	getchar();

}

void exibirFila(FilaBanco *fila) {

	// Exibe todos os clientes na fila com nome, serviço, senha e guichês designados.

	system("cls");
	corTexto(9);
	printf("===================================\n");
	corTexto(14);
	printf("         Fila de atendimento          \n");
	printf("          ** ProtecBank **         \n");
	corTexto(9);
	printf("===================================\n");

	if (fila->atras == 0) {
		corTexto(12);
		printf("\n");
		printf("    A FILA ESTÁ VAZIA!\n");
		printf("  Não há senhas para exibir.\n");
		printf("\n");
		corTexto(11);
		printf("===================================\n");
		return;
	}

	corTexto(11);
	printf("\n%-10s%-20s%-20s%-10s%-10s\n", "Posição", "Nome", "Tipo de Serviço", "Senha", "Guichê");
	printf("------------------------------------------------------------\n");

	corTexto(14);
	for (int i = 0; i < fila->atras; i++) {
		printf("%-10d%-20s%-20s%-10s%d e %d\n",
		       i + 1,
		       fila->clientes[i].nome,
		       fila->clientes[i].tipoServico,
		       fila->clientes[i].senha,
		       fila->clientes[i].mesas[0],
		       fila->clientes[i].mesas[1]);
	}

	corTexto(9);
	printf("\n\nPressione Enter para voltar ao menu...\n");
	getchar();
	system("cls");
}

void atenderCliente(FilaBanco *fila) {

	/*

	Realiza o atendimento do próximo cliente na fila do banco, com prioridade para clientes preferenciais.
	Executa o serviço bancário solicitado, exibe informações do atendimento e remove o cliente da fila
	após o atendimento ser concluído.

	*/

	ContaBancaria conta;
	if (fila->frente == fila->atras) {
		system("cls");
		corTexto(11);
		printf("=============================\n");
		corTexto(12);
		printf("    A fila está vazia!!!\n");
		printf("Não hà cliente para atender\n");
		corTexto(11);
		printf("=============================\n");
		return;
	}

	int indiceAtendimento = -1;

	for (int i = fila->frente; i < fila->atras; i++) {
		if (fila->clientes[i].prioridade == 'S' || fila->clientes[i].prioridade == 's') {
			indiceAtendimento = i;
			break;
		}

		if (indiceAtendimento == -1) {
			indiceAtendimento = i;
		}
	}

	if (indiceAtendimento == -1) {
		printf("===============================================\n");
		printf("Não há clientes na fila.\n");
		printf("===============================================\n");
		return;
	}

	Cliente *cliente = &fila->clientes[indiceAtendimento];

	corTexto(14);
	printf("===============================================\n");
	printf("Atendendo cliente: %s\n", cliente->nome);
	printf("Tipo de serviço: %s\n", cliente->tipoServico);
	printf("Senha: %s\n", cliente->senha);
	printf("===============================================\n\n");
	corTexto(11);

	if (strcmp(cliente->tipoServico, "Abrir Conta") == 0) {
		ContaBancaria novaConta;
		CriarConta(&novaConta);
	} else if (strcmp(cliente->tipoServico, "Encerrar Conta") == 0) {
		DeletarConta(&conta);
	} else if (strcmp(cliente->tipoServico, "Consultar Saldo") == 0) {
		consultarSaldo(cliente->cpf, cliente->senha, 0);
	} else if (strcmp(cliente->tipoServico, "Realizar Depósito") == 0) {
		realizarDeposito(cliente->cpf, cliente->senha, 0);
	} else if (strcmp(cliente->tipoServico, "Realizar Saque") == 0) {
		realizarSaque(cliente->cpf, cliente->senha, 0);
	} else if (strcmp(cliente->tipoServico, "Transferir Valores") == 0) {
		realizarTransferencia(cliente->cpf, cliente->senha, 0);
	} else if (strcmp(cliente->tipoServico, "Extrato") == 0) {
		extrato(cliente->cpf, cliente->senha, 0);
	} else if (strcmp(cliente->tipoServico, "Atualizacões cadastrais") == 0) {
		atualizarCadastro();
	} else {
		printf("===============================================\n");
		printf("Serviço desconhecido: %s\n", cliente->tipoServico);
		printf("===============================================\n");
	}

	for (int i = indiceAtendimento; i < fila->atras - 1; i++) {
		fila->clientes[i] = fila->clientes[i + 1];
	}
	fila->atras--;

	if (remove(cliente->arquivoComprovante) == 0) {
		corTexto(14);
		printf("\n\n===============================================\n");
		printf("Sua senha de atendimento foi descartada!!!\n");
		printf("===============================================\n");
		system("pause");
		system("cls");
		corTexto(11);
	} else {
		corTexto(12);
		printf("\n===============================================\n");
		printf("Erro ao remover o arquivo de comprovante: '%s'.\n", cliente->arquivoComprovante);
		printf("===============================================\n");
		corTexto(11);
	}
}

int gerarCodigo() {

	// Gera um código de 6 dígitos para verificação na redefinição de senha do cliente.

	return rand() % 900000 + 100000;
}

void obterHorarioAtual(char *horario, size_t tamanho) {
	time_t agora = time(NULL);
	struct tm *tm_info = localtime(&agora);
	strftime(horario, tamanho, "%d/%m/%Y às %H:%M:%S", tm_info);
}

void RedefinirSenha(char *cpf) {

	/*
	Permite a redefinição da senha do cliente utilizando um dos métodos de recuperação:
	telefone, e-mail ou pergunta secreta. Após validação da identidade, o usuário define
	uma nova senha que é atualizada no arquivo da conta.
	*/

	char nomeArquivo[30];
	char linha[256];
	char perguntaSecreta[256] = {0};
	char respostaSecreta[256] = {0};
	char novaSenha[50], confirmarSenha[50];
	int codigoGerado, codigoInformado;
	int escolha;
	int encontrouSessao = 0;
	int tentativas = 3;
	char horario[30];
	int encontrouPergunta = 0;
	int senhaValida;

	srand(time(NULL));

	do {
		snprintf(nomeArquivo, sizeof(nomeArquivo), "%s.txt", cpf);

		FILE *arquivo = fopen(nomeArquivo, "r");
		if (arquivo) {

			while (fgets(linha, sizeof(linha), arquivo)) {
				if (strncmp(linha, "Pergunta Secreta       :", 23) == 0) {
					strncpy(perguntaSecreta, linha + 24, sizeof(perguntaSecreta));
					perguntaSecreta[strcspn(perguntaSecreta, "\n")] = 0;
					encontrouPergunta = 1;
				} else if (strncmp(linha, "Resposta Secreta       :", 23) == 0) {
					sscanf(linha, "Resposta Secreta       : %[^\n]", respostaSecreta);
				}
			}
			fclose(arquivo);
			break;
		} else {
			printf("\n[ERRO] Nenhuma conta vinculada ao CPF %s foi encontrada.\n", cpf);
			tentativas--;
			if (tentativas == 0) {
				printf("\n[ERRO] Tentativas excedidas! Operação abortada.\n");
				return;
			}
		}
	} while (1);

	do {
		printf("\nComo deseja recuperar sua conta?\n");
		printf("[1] - Telefone\n");
		printf("[2] - E-mail\n");
		printf("[3] - Pergunta Secreta\n");
		printf("Escolha uma opção: ");
		scanf("%d", &escolha);
		getchar();

		if (escolha >= 1 && escolha <= 3) break;
		printf("\n[ERRO] Opção inválida! Tente novamente.\n");
	} while (1);

	if (escolha == 3) {

		if (!encontrouPergunta) {
			printf("\n[ERRO] Pergunta secreta não encontrada no arquivo. Operação abortada.\n");
			return;
		}

		char respostaUsuario[256];
		tentativas = 3;
		do {
			printf("\nPergunta Secreta: %s\n", perguntaSecreta);
			printf("Digite sua resposta: ");
			fgets(respostaUsuario, sizeof(respostaUsuario), stdin);
			respostaUsuario[strcspn(respostaUsuario, "\n")] = 0;

			if (strcmp(respostaUsuario, respostaSecreta) == 0) {
				printf("\n[SUCCESSO] Resposta correta!\n");
				break;
			} else {
				printf("\n[ERRO] Resposta incorreta! Tente novamente.\n");
				tentativas--;
				if (tentativas == 0) {
					printf("\n[ERRO] Tentativas excedidas! Operação abortada.\n");
					return;
				}
			}
		} while (1);
	} else {

		codigoGerado = gerarCodigo();
		obterHorarioAtual(horario, sizeof(horario));

		FILE *arquivo = fopen(nomeArquivo, "r");
		FILE *temp = fopen("TempArquivo.txt", "w");
		if (!temp) {
			printf("\n[ERRO] Não foi possível criar o arquivo temporário.\n");
			fclose(arquivo);
			return;
		}

		while (fgets(linha, sizeof(linha), arquivo)) {
			if (escolha == 1 && strstr(linha, "CAIXA DE ENTRADA DO TELEFONE")) {
				fprintf(temp, "%s", linha);
				fprintf(temp, "\nCódigo de Recuperação: %d\n", codigoGerado);
				fprintf(temp, "Recebido em: %s\n", horario);
				fprintf(temp, "---------------------------------------------\n\n");
				encontrouSessao = 1;
			} else if (escolha == 2 && strstr(linha, "CAIXA DE ENTRADA DO E-MAIL")) {
				fprintf(temp, "%s", linha);
				fprintf(temp, "Código de Recuperação: %d\n", codigoGerado);
				fprintf(temp, "Recebido em: %s\n", horario);
				fprintf(temp, "---------------------------------------------\n\n");
				encontrouSessao = 1;
			} else {
				fprintf(temp, "%s", linha);
			}
		}

		fclose(arquivo);
		fclose(temp);

		if (!encontrouSessao) {
			printf("\n[ERRO] Não foi possível encontrar a seção para escrever o código.\n");
			remove("TempArquivo.txt");
			return;
		}

		remove(nomeArquivo);
		rename("TempArquivo.txt", nomeArquivo);

		printf("\n[INFO] Código de recuperação enviado para a seção '");
		corTexto(14); 
		printf("%s", escolha == 1 ? "CAIXA DE ENTRADA DO TELEFONE" : "CAIXA DE ENTRADA DO E-MAIL");
		corTexto(11);  
		printf("' no arquivo da conta.\n");

		tentativas = 3;
		do {
			printf("\nDigite o código de recuperação enviado: ");
			corTexto(14); 
			scanf("%d", &codigoInformado);
			getchar();
			corTexto(11); 
			if (codigoInformado == codigoGerado) {
				break;
			} else {
				corTexto(12); 
				printf("\n[ERRO] Código incorreto! Tente novamente.\n");
				tentativas--;
				corTexto(11); 
				if (tentativas == 0) {
						corTexto(12); 
					printf("\n[ERRO] Tentativas excedidas! Operação abortada.\n");
						corTexto(11); 
					return;
				}
			}
		} while (1);
	}

	while (1) {
		senhaValida = 1;

		printf("\nDigite uma nova senha (6 a 8 caracteres): ");
		printf("\nA senha deve conter:\n");
		printf(" - Pelo menos 1 letra maiúscula\n");
		printf(" - Pelo menos 1 letra minúscula\n");
		printf(" - Pelo menos 1 número\n");
		printf(" - Pelo menos 1 caractere especial\nR: ");

		int i = 0;
		char ch;
		while ((ch = getch()) != '\r') {
			if (ch == '\b') {
				if (i > 0) {
					i--;
					printf("\b \b");
				}
			} else {
				novaSenha[i++] = ch;
				printf("*");
			}
		}
		novaSenha[i] = '\0';
		printf("\n");


		int temMaiuscula = 0, temMinuscula = 0, temNumero = 0, temEspecial = 0;
		if (strlen(novaSenha) >= 6 && strlen(novaSenha) <= 8) {
			for (int j = 0; novaSenha[j] != '\0'; j++) {
				if (isupper(novaSenha[j])) temMaiuscula = 1;
				else if (islower(novaSenha[j])) temMinuscula = 1;
				else if (isdigit(novaSenha[j])) temNumero = 1;
				else temEspecial = 1;
			}
		} else {
			senhaValida = 0;
		}

		if (!(temMaiuscula && temMinuscula && temNumero && temEspecial)) {
			senhaValida = 0;
		}

		if (!senhaValida) {
			corTexto(12); 
			printf("\n[ERRO] A senha não atende aos requisitos. Tente novamente.\n");
			corTexto(11); 
			continue;
		}


		printf("\nConfirme a nova senha: ");
		i = 0;
		while ((ch = getch()) != '\r') {
			if (ch == '\b') {
				if (i > 0) {
					i--;
					printf("\b \b");
				}
			} else {
				confirmarSenha[i++] = ch;
				printf("*");
			}
		}
		confirmarSenha[i] = '\0';
		printf("\n");

		if (strcmp(novaSenha, confirmarSenha) != 0) {
			corTexto(12); 
			printf("\n[ERRO] As senhas não coincidem. Tente novamente.\n");
			corTexto(11); 
		} else {
			corTexto(10); 
			printf("\n[SUCCESSO] Senha redefinida com sucesso!\n");
			corTexto(11); 
			break;
		}
	}

	FILE *arquivo = fopen(nomeArquivo, "r");
	FILE *temp = fopen("TempArquivo.txt", "w");

	if (!arquivo || !temp) {
		printf("\n[ERRO] Erro ao acessar os arquivos para atualizar a senha.\n");
		fclose(arquivo);
		fclose(temp);
		return;
	}

	while (fgets(linha, sizeof(linha), arquivo)) {
		if (strncmp(linha, "Senha                  :", 23) == 0) {
			fprintf(temp, "Senha                  : %s\n", novaSenha);
		} else {
			fprintf(temp, "%s", linha);
		}
	}

	fclose(arquivo);
	fclose(temp);

	remove(nomeArquivo);
	rename("TempArquivo.txt", nomeArquivo);
}


int validarIdade(const char *dataNascimento) {

	/*
	Validar a data de nascimento informada pelo cliente, verificando seu formato, consistência
	e calculando a idade com base na data atual do sistema. Garante que o cliente tenha pelo
	menos 18 anos para poder abrir uma conta bancária.
	*/

	time_t t = time(NULL);
	struct tm tmAtual = *localtime(&t);


	int dia, mes, ano;
	if (sscanf(dataNascimento, "%d/%d/%d", &dia, &mes, &ano) != 3) {
		corTexto(12);
		printf("[ERRO] Data de nascimento inválida. Use o formato DD/MM/AAAA.\n");
		corTexto(11);
		return -1;

	}

	if (ano < 1900 || ano > tmAtual.tm_year + 1900 || mes < 1 || mes > 12 || dia < 1 || dia > 31) {
		corTexto(12);
		printf("[ERRO] Data de nascimento inválida. Verifique os valores inseridos.\n");
		corTexto(11);
		return -1;

	}


	int diasNoMes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if (ano % 4 == 0 && (ano % 100 != 0 || ano % 400 == 0)) {
		diasNoMes[1] = 29;
	}
	if (dia > diasNoMes[mes - 1]) {
		corTexto(12);
		printf("[ERRO] Dia inválido para o mês especificado.\n");
		corTexto(11);
		return -1;

	}

	int idade = tmAtual.tm_year + 1900 - ano;

	if (mes > tmAtual.tm_mon + 1 || (mes == tmAtual.tm_mon + 1 && dia > tmAtual.tm_mday)) {
		idade--;
	}

	if (idade < 18) {
		corTexto(12);
		printf("[ERRO] Você precisa ter pelo menos 18 anos para criar uma conta.\n");
		corTexto(11);
		int opcao;
		printf("Deseja corrigir a data de nascimento \n[1] - Sim \n[2] - Não, finalizar \nR: ");
		scanf("%d", &opcao);
		getchar();

		if (opcao == 1) {
			return -1;
		} else {
			printf("Processo finalizado.\n");
			exit(1);
		}
	} else if (idade > 110) {
		corTexto(12);
		printf("[ERRO] Idade inválida. Verifique os dados inseridos.\n");
		corTexto(11);
		return -1;

	}

	return idade;
}

void aceitarTermos() {

	/*
	Exibir os termos de serviço do banco para que o cliente possa tomar ciência
	das condições antes de continuar com o uso do sistema.
	*/

	int esq;
	corTexto(9);
	printf("\n============================================");
	corTexto(14);
	printf("\n             Termos de Serviço ");
	printf("\n                 ProtecBank                     ");
	corTexto(9);
	printf("\n============================================\n\n");
	corTexto(11);
	printf("1. O banco não se responsabiliza por senhas compartilhadas.\n");
	printf("2. Os dados fornecidos serão usados exclusivamente para fins bancários.\n");
	printf("3. Todas as transações estão sujeitas à verificação de segurança.\n");
	printf("4. O cliente é responsável por manter os dados atualizados.\n");
	printf("5. As taxas e tarifas estão sujeitas a alterações com aviso prévio.\n");
	printf("6. O uso de sua conta deve estar de acordo com as leis vigentes.\n");
	printf("7. O banco pode suspender ou encerrar contas que apresentem atividades suspeitas.\n");
	printf("8. O cliente é responsável por reportar qualquer atividade não autorizada.\n");
	printf("9. Os limites de transação podem variar conforme o perfil do cliente.\n");
	printf("10. O banco oferece suporte ao cliente em horário comercial.\n");
	printf("====================================================\n\n");

}

void gerarChaveAleatoria(char *chave, size_t tamanho) {

	/*
	Gerar uma chave Pix aleatória no formato "XXX-XXX-XXX", utilizada como identificador
	único para transações no sistema bancário.
	*/

	if (tamanho < 12) {
		printf("[ERRO] Tamanho insuficiente para gerar a chave.\n");
		return;
	}

	srand(time(NULL));
	for (int i = 0; i < 11; i++) {
		if (i == 3 || i == 7) {
			chave[i] = '-';
		} else {
			int aleatorio = rand() % 36;
			chave[i] = (aleatorio < 10) ? ('0' + aleatorio) : ('a' + aleatorio - 10);
		}
	}
	chave[11] = '\0';
}

int validarChaveAleatoria(const char *chave) {

	/*
	Verifica se uma chave Pix aleatória fornecida está no formato correto utilizado
	pelo sistema ProtecBank.
	*/

	if (strlen(chave) != 11) return 0;
	for (int i = 0; i < 11; i++) {
		if (i == 3 || i == 7) {
			if (chave[i] != '-') return 0;
		} else {
			if (!isalnum(chave[i])) return 0;
		}
	}
	return 1;
}

int validarEmail(const char *email) {

	/*
	Verifica se o endereço de e-mail fornecido está em um formato válido
	conforme os critérios estabelecidos pelo sistema.
	*/

	int i = 0;
	if (!isalpha(email[i])) return 0;
	i++;
	while (email[i] != '\0' && email[i] != '@') {
		if (!isalnum(email[i]) && email[i] != '-' && email[i] != '_' && email[i] != '.') return 0;
		i++;
	}
	if (email[i] != '@') return 0;
	i++;
	if (!isalpha(email[i])) return 0;
	while (email[i] != '\0' && email[i] != '.') {
		if (!isalpha(email[i])) return 0;
		i++;
	}
	if (email[i] != '.') return 0;
	i++;
	int contadorExtensao = 0;
	while (email[i] != '\0') {
		if (!isalpha(email[i])) return 0;
		contadorExtensao++;
		i++;
	}
	return contadorExtensao == 2 || contadorExtensao == 3;
}


int verificarNumeroContaExistente(char *numeroConta) {

	/*
	Verifica se um número de conta bancária informado já está cadastrado no sistema para não criar aleatória.
	*/

	FILE *arquivo;
	char linha[10000];

	arquivo = fopen("Contas.txt", "r");
	if (arquivo == NULL) {
		return 0;
	}

	while (fgets(linha, sizeof(linha), arquivo)) {

		if (strstr(linha, numeroConta) != NULL) {
			fclose(arquivo);
			return 1;
		}
	}

	fclose(arquivo);
	return 0;
}

void gerarNumeroConta(char *numeroConta) {

	/*
	Gera um número de conta bancária único e semi-aleatório para um novo cliente.
	*/

	static int contador = 1000;
	int parteAleatoria = rand() % 10;

	sprintf(numeroConta, "%d-%d", contador++, parteAleatoria);
}

void menucriarconta() {
	corTexto(9);
	printf("===============================================\n");
	corTexto(14);
	printf("                 PROTECBANK                      \n");
	printf("           CRIAÇÃO DE CONTA BANCÁRIA          \n");
	corTexto(9);
	printf("===============================================\n");
	corTexto(11);
}

void exibirPontos() {

	for (int i = 0; i < 9; i++) {
		printf(".");
		fflush(stdout);
		Sleep(600);
	}

	printf("\n");
}

int validarSiglaEstado(char *sigla) {

	/*
	Verifica se a sigla informada corresponde a um dos 27 estados brasileiros ou ao Distrito Federal.
	*/

	const char *siglasValidas[] = {
		"AC", "AL", "AP", "AM", "BA", "CE", "DF", "ES", "GO", "MA",
		"MT", "MS", "MG", "PA", "PB", "PR", "PE", "PI", "RJ", "RN",
		"RS", "RO", "RR", "SC", "SP", "SE", "TO"
	};
	int totalSiglas = sizeof(siglasValidas) / sizeof(siglasValidas[0]);

	for (int i = 0; sigla[i]; i++) {
		sigla[i] = toupper((unsigned char)sigla[i]);
	}

	for (int i = 0; i < totalSiglas; i++) {
		if (strcmp(sigla, siglasValidas[i]) == 0) {
			return 1;
		}
	}
	return 0;
}

int validarCEP(char *cep) {

	/*
	  Verifica se o CEP informado possui um formato válido.
	*/

	int digitos = 0;

	for (int i = 0; cep[i] != '\0'; i++) {
		if (isdigit(cep[i])) {
			digitos++;
		} else if (cep[i] != '-') {
			return 0;
		}
	}

	return digitos == 8;
}

void CriarConta(ContaBancaria *conta) {

	/*
	Responsável por cadastrar um novo cliente no sistema bancário.
	Garante todas as validações necessárias para um cadastro correto e seguro.
	*/

	char senhaConfirmada[20], senhaTransacaoConfirmada[5];
	char nomeArquivo[50];
	char dataNascimento[11];
	int idade;
	char linha[200];
	int totalContas = 0;
	char numeroConta[1000];
	char dataCriacao[50];
	int esq;
	int esqo;
	char cpfFormatado[15];
	char sobrenome[50];

	time_t t = time(NULL);
	struct tm tm = *localtime(&t);

	FilaBanco *fila;

	FILE *arquivo;

	snprintf(dataCriacao, sizeof(dataCriacao), "%02d/%02d/%04d às %02d:%02d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min);
	corTexto(9);
	printf("\n===============================================\n");
	corTexto(14);
	printf("          CRIAR CONTA BANCARIA     \n");
	printf("             PROTECBANK              \n");
	corTexto(9);
	printf("===============================================\n");
	corTexto(11);

	while (1) {
		gerarNumeroConta(numeroConta);

		if (verificarNumeroContaExistente(numeroConta)) {
		} else {
			break;
		}
	}

	do {

		printf("\nPara podermos começar a criação da sua conta você precisa aceitar os termos e condições");
		printf("\n[1] - Aceito");
		printf("\n[2] - Visualizar os termos e condicões.\nR: ");
		scanf("%d", &esq);
		fflush(stdin);

		if(esq == 1) {
			break;
		} else if( esq == 2) {
			system("cls");
			aceitarTermos();
			printf("\nVocê aceita os Termos e condições do Serviço? \n[1] - Sim \n[2] - Não \nR: ");
			scanf("%d", &esq);
			fflush(stdin);

			if(esq== 1) {
				break;
			}
			if(esq==2) {
				printf("Você deve aceitar os Termos de Serviço para criar uma conta, até a próxima!!!");
				exit(0);
			}
		} else {
			corTexto(12);
			printf("\nOpção inválida!!!\n");
			corTexto(11);
		}
	} while (esq != 1 || esq != 2);

	system("cls");
	menucriarconta();
	corTexto(14);
	printf("\nOlá, seja bem-vindo(a), ficamos felizes por ter você aqui conosco ^^) Vamos começar.\n");
	printf("---------------------------------------------------------------------------------------------\n");
	corTexto(11);

	while (1) {

		printf("\nDigite seu primeiro nome: ");
		corTexto(14);
		fgets(conta->nomeCompleto, sizeof(conta->nomeCompleto), stdin);
		fflush(stdin);

		conta->nomeCompleto[strcspn(conta->nomeCompleto, "\n")] = '\0';

		int valido = 1;
		int comprimento = strlen(conta->nomeCompleto);
		int caracteresValidos = 0;

		if (comprimento < 2) {
			valido = 0;
		} else {
			for (int i = 0; conta->nomeCompleto[i] != '\0'; i++) {
				if (!isalpha((unsigned char)conta->nomeCompleto[i]) && conta->nomeCompleto[i] != ' ') {
					valido = 0;
					break;
				}
				if (isalpha((unsigned char)conta->nomeCompleto[i])) {
					caracteresValidos++;
				}
			}
			if (caracteresValidos < 2) {
				valido = 0;
			}
		}

		if (valido) break;

		corTexto(12);
		printf("O primeiro nome deve ter pelo menos 2 letras válidas e conter apenas letras e espaços. Tente novamente.\n");
		corTexto(11);
	}

	while (1) {

		corTexto(11);
		printf("\nDigite seu sobrenome: ");
		corTexto(14);
		fgets(conta->sobrenome, sizeof(conta->sobrenome), stdin);
		fflush(stdin);

		conta->sobrenome[strcspn(conta->sobrenome, "\n")] = '\0';

		int valido = 1;
		int comprimento = strlen(conta->sobrenome);
		int caracteresValidos = 0;

		if (comprimento < 2) {
			valido = 0;
		} else {
			for (int i = 0; conta->sobrenome[i] != '\0'; i++) {
				if (!isalpha((unsigned char)conta->sobrenome[i]) && conta->sobrenome[i] != ' ') {
					valido = 0;
					break;
				}
				if (isalpha((unsigned char)conta->sobrenome[i])) {
					caracteresValidos++;
				}
			}
			if (caracteresValidos < 2) {
				valido = 0;
			}
		}

		if (valido) break;

		corTexto(12);
		printf("O sobrenome deve ter pelo menos 2 letras válidas e conter apenas letras e espaços. Tente novamente.\n");
		corTexto(11);
	}

	strcat(conta->nomeCompleto, " ");
	strcat(conta->nomeCompleto, conta->sobrenome);

	corTexto(11);
	while (1) {
		printf("\nDigite sua data de nascimento (DD/MM/AAAA): ");
		corTexto(14);
		fgets(dataNascimento, sizeof(dataNascimento), stdin);
		fflush(stdin);
		dataNascimento[strcspn(dataNascimento, "\n")] = '\0';

		int idade = validarIdade(dataNascimento);
		if (idade != -1) {
			strcpy(conta->dataNascimento, dataNascimento);
			break;
		}

	}
	corTexto(11);

	while (1) {
		printf("\nDigite seu CPF (apenas números): ");
		corTexto(14);
		fgets(conta->cpf, sizeof(conta->cpf), stdin);
		conta->cpf[strcspn(conta->cpf, "\n")] = '\0';

		snprintf(nomeArquivo, sizeof(nomeArquivo), "%s.txt", conta->cpf);
		arquivo = fopen(nomeArquivo, "r");

		int valido = 1;
		if (arquivo != NULL) {
			fclose(arquivo);
			corTexto(12);
			printf("Já existe uma conta com este CPF. Use outro CPF.\n");
			corTexto(11);
			valido = 0;
		} else if (strlen(conta->cpf) != 11) {
			corTexto(12);
			printf("[ERRO] O CPF deve conter exatamente 11 números.\n");
			corTexto(11);
			valido = 0;
		} else {
			for (int i = 0; i < 11; i++) {
				if (!isdigit(conta->cpf[i])) {
					printf("[ERRO] O CPF deve conter apenas números.\n");
					valido = 0;
					break;
				}
			}
		}

		if (valido) break;
	}

	corTexto(11);

	printf("\nInforme o seu endereço:\n");

	printf("Rua: ");
	corTexto(14);
	fgets(conta->rua, sizeof(conta->rua), stdin);
	conta->rua[strcspn(conta->rua, "\n")] = '\0';
	corTexto(11);


	printf("Número: ");
	corTexto(14);
	fgets(conta->numero, sizeof(conta->numero), stdin);
	conta->numero[strcspn(conta->numero, "\n")] = '\0';
	corTexto(11);

	printf("Bairro: ");
	corTexto(14);
	fgets(conta->bairro, sizeof(conta->bairro), stdin);
	conta->bairro[strcspn(conta->bairro, "\n")] = '\0';
	corTexto(11);

	printf("Cidade: ");
	corTexto(14);
	fgets(conta->cidade, sizeof(conta->cidade), stdin);
	conta->cidade[strcspn(conta->cidade, "\n")] = '\0';  // Remove o '\n' no final
	corTexto(11);

	while (1) {

		printf("Estado (sigla): ");
		corTexto(14);
		fgets(conta->estado, sizeof(conta->estado), stdin);
		conta->estado[strcspn(conta->estado, "\n")] = '\0';
		fflush(stdin);

		if (validarSiglaEstado(conta->estado)) {
			corTexto(11);
			break;
		} else {
			corTexto(12);
			printf("Sigla inválida!!!\n");
			corTexto(11);
		}
	}

	while (1) {
		printf("CEP: ");
		corTexto(14);
		fgets(conta->cep, sizeof(conta->cep), stdin);
		conta->cep[strcspn(conta->cep, "\n")] = '\0';

		if (validarCEP(conta->cep)) {
			corTexto(11);
			break;
		} else {
			corTexto(12);
			printf("CEP inválido! Por favor, insira um CEP no formato 'NNNNN-NNN' ou 'NNNNNNNN'.\n");
			corTexto(11);
		}
	}

	int opcao;

	do {

		printf("\nEscolha o tipo de conta que deseja abrir:\n");
		printf("1. Conta Corrente\n");
		printf("2. Conta Poupança\n");
		printf("3. Conta Salário\n");
		printf("4. Conta Especial\n");
		printf("Digite o número da opção desejada: ");
		scanf("%d", &opcao);
		fflush(stdin);

		switch(opcao) {
			case 1:
				strcpy(conta->tipoConta, "Conta Corrente");
				break;
			case 2:
				strcpy(conta->tipoConta, "Conta Poupança");
				break;
			case 3:
				strcpy(conta->tipoConta, "Conta Salário");
				break;
			case 4:
				strcpy(conta->tipoConta, "Conta Especial");
				break;
			default:
				corTexto(12);
				printf("Opção inválida,\n");
				corTexto(11);
				break;
		}
	} while(opcao <1 || opcao >4);

	while (1) {
		printf("\nEscolha o tipo de chave Pix:\n");
		printf("[1] Telefone\n[2] CPF\n[3] E-mail\n[4] Chave Aleatória\n[5] Não desejo cadastar agora.\nR: ");
		int escolhaPix;
		scanf("%d", &escolhaPix);
		fflush(stdin);

		if (escolhaPix == 1) {

			printf("Digite seu número de telefone (apenas números, até 11 dígitos): ");
			corTexto(14);
			fgets(conta->pix, sizeof(conta->pix), stdin);
			conta->pix[strcspn(conta->pix, "\n")] = '\0';
			corTexto(11);
			int valido = 1;


			if (chavePixJaCadastrada("contas.txt", conta->pix)) {
				corTexto(12);
				printf("O telefone informado já está cadastrado como chave Pix. Tente novamente.\n");
				corTexto(11);
				continue;
			}

			if (strlen(conta->pix) < 10 || strlen(conta->pix) > 11) {
				valido = 0;
			}

			for (int i = 0; conta->pix[i] != '\0'; i++) {
				if (!isdigit(conta->pix[i])) {
					valido = 0;
					break;
				}
			}

			if (!valido) {
				corTexto(12);
				printf("[ERRO] O telefone deve conter apenas números e ter 10 ou 11 dígitos. Tente novamente.\n");
				corTexto(11);
			} else {

				printf("\nChave Pix do tipo telefone cadastrada com sucesso!\n");
				break;
			}

		} else if (escolhaPix == 2) {

			if (chavePixJaCadastrada("contas.txt", conta->cpf)) {
				corTexto(12);
				printf("O CPF informado já está cadastrado como chave Pix. Tente novamente.\n");
				corTexto(11);
				continue;
			}

			strcpy(conta->pix, conta->cpf);
			printf("\nChave Pix do CPF telefone cadastrada com sucesso!\n");
			break;

		} else if (escolhaPix == 3) {
			printf("Digite seu e-mail: ");
			corTexto(14);
			fgets(conta->pix, sizeof(conta->pix), stdin);
			conta->pix[strcspn(conta->pix, "\n")] = '\0';
			corTexto(11);

			if (!validarEmail(conta->pix)) {
				corTexto(12);
				printf("O e-mail é inválido. Verifique as regras e tente novamente.\n");
				corTexto(11);
				continue;
			}

			if (chavePixJaCadastrada("contas.txt", conta->pix)) {
				corTexto(12);
				printf("O e-mail informado já está cadastrado como chave Pix. Tente novamente.\n");
				corTexto(11);
				continue;
			}

			break;

		} else if (escolhaPix == 4) {
			gerarChaveAleatoria(conta->pix, sizeof(conta->pix));

			if (chavePixJaCadastrada("contas.txt", conta->pix)) {
				printf("Houve um conflito com a chave aleatória gerada. Gerando novamente...\n");
				continue;
			}
			printf("Sua chave Pix aleatória foi criada com sucesso = ");
			corTexto(14);
			printf("%s",conta->pix);
			corTexto(11);
			break;

		} else if (escolhaPix == 5) {
			break;
		} else {
			corTexto(12);
			printf("Opção inválida!!!.");
			corTexto(11);
		}

	}

	while (1) {
		printf("\n\nInforme seu número de telefone com DDD (11 dígitos): ");
		corTexto(14);
		fgets(conta->telefone, sizeof(conta->telefone), stdin);
		conta->telefone[strcspn(conta->telefone, "\n")] = '\0';
		corTexto(11);

		int valido = 1;

		if (strlen(conta->telefone) != 11) {
			corTexto(12);
			printf("O telefone deve conter exatamente 11 dígitos!!!\n");
			corTexto(11);
			valido = 0;
		} else {
			for (int i = 0; i < 11; i++) {
				if (!isdigit(conta->telefone[i])) {
					corTexto(12);
					printf("O telefone deve conter apenas números!!!\n");
					corTexto(11);
					valido = 0;
					break;
				}
			}
		}

		if (valido) break;
	}

	while (1) {
		printf("\nDigite seu e-mail: ");
		corTexto(14);
		fgets(conta->email, sizeof(conta->email), stdin);
		conta->email[strcspn(conta->email, "\n")] = '\0';
		corTexto(11);

		if (!validarEmail(conta->email)) {
			corTexto(12);
			printf("O e-mail é inválido. Verifique as regras e tente novamente.\n");
			corTexto(11);
			continue;
		}
		break;
	}

	while (1) {
		printf("\nDigite uma senha para acesso à conta (6 a 8 caracteres): ");
		printf("\nA senha deve conter:\n");
		printf(" - Pelo menos 1 letra maiúscula\n");
		printf(" - Pelo menos 1 letra minúscula\n");
		printf(" - Pelo menos 1 número\n");
		printf(" - Pelo menos 1 caractere especial\nR: ");
		corTexto(14);
		int i = 0;
		char ch;
		while ((ch = getch()) != '\r') {
			if (ch == '\b') {
				if (i > 0) {
					i--;
					printf("\b \b");
				}
			} else {
				conta->senha[i++] = ch;
				printf("*");
			}
		}
		conta->senha[i] = '\0';
		printf("\n");

		int temMaiuscula = 0, temMinuscula = 0, temNumero = 0, temEspecial = 0;
		if (strlen(conta->senha) >= 6 && strlen(conta->senha) <= 8) {
			for (int i = 0; conta->senha[i] != '\0'; i++) {
				if (isupper(conta->senha[i])) temMaiuscula = 1;
				else if (islower(conta->senha[i])) temMinuscula = 1;
				else if (isdigit(conta->senha[i])) temNumero = 1;
				else temEspecial = 1;
			}
		}

		if (!(temMaiuscula && temMinuscula && temNumero && temEspecial)) {
			corTexto(12);
			printf("[ERRO] A senha não atende aos requisitos. Tente novamente.\n");
			corTexto(11);
			continue;
		}
		corTexto(11);
		printf("\nConfirme a senha: ");
		corTexto(14);
		i = 0;
		while ((ch = getch()) != '\r') {
			if (ch == '\b') {
				if (i > 0) {
					i--;
					printf("\b \b");
				}
			} else {
				senhaConfirmada[i++] = ch;
				printf("*");
			}
		}
		senhaConfirmada[i] = '\0';
		printf("\n");

		if (strcmp(conta->senha, senhaConfirmada) != 0) {
			corTexto(12);
			printf("As senhas não coincidem. Tente novamente.\n");
			corTexto(11);
		} else {
			break;
		}
	}

	corTexto(11);
	while (1) {
		corTexto(11);
		printf("\nDigite uma senha para transações (4 dígitos): ");
		corTexto(14);
		int i = 0;
		char ch;
		while ((ch = getch()) != '\r') {
			if (ch == '\b') {
				if (i > 0) {
					i--;
					printf("\b \b");
				}
			} else {
				conta->senhaTransacao[i++] = ch;
				printf("*");
			}
		}
		conta->senhaTransacao[i] = '\0';
		printf("\n");

		if (strlen(conta->senhaTransacao) != 4 || !isdigit(conta->senhaTransacao[0])) {
			corTexto(12);
			printf("A senha deve conter exatamente 4 números. Tente novamente.\n");
			corTexto(11);
			continue;
		}
		corTexto(11);
		printf("\nConfirme a senha de transação: ");
		corTexto(14);
		i = 0;
		while ((ch = getch()) != '\r') {
			if (ch == '\b') {
				if (i > 0) {
					i--;
					printf("\b \b");
				}
			} else {
				senhaTransacaoConfirmada[i++] = ch;
				printf("*");
			}
		}
		senhaTransacaoConfirmada[i] = '\0';
		printf("\n");

		if (strcmp(conta->senhaTransacao, senhaTransacaoConfirmada) != 0) {
			corTexto(12);
			printf("[ERRO] As senhas de transação não coincidem. Tente novamente.\n");
			corTexto(11);
		} else {
			break;
		}
	}
	corTexto(11);

	printf("\nDigite uma pergunta secreta para recuperação de senha: ");
	corTexto(14);
	fgets(conta->perguntaSecreta, sizeof(conta->perguntaSecreta), stdin);
	conta->perguntaSecreta[strcspn(conta->perguntaSecreta, "\n")] = '\0';
	corTexto(11);

	printf("\nDigite a resposta para a pergunta secreta: ");
	corTexto(14);
	fgets(conta->respostaSecreta, sizeof(conta->respostaSecreta), stdin);
	conta->respostaSecreta[strcspn(conta->respostaSecreta, "\n")] = '\0';
	corTexto(11);

	conta->saldo = 0.0;

	arquivo = fopen(nomeArquivo, "w");
	fprintf(arquivo, "=============================================\n");
	fprintf(arquivo, "      DETALHES DA SUA CONTA BANCÁRIA         \n");
	fprintf(arquivo, "=============================================\n\n");
	fprintf(arquivo, "Pix                    : %s\n", conta->pix);
	fprintf(arquivo, "CPF                    : %s\n", conta->cpf);
	fprintf(arquivo, "Nome completo          : %s\n", conta->nomeCompleto);
	fprintf(arquivo, "Data de nascimento     : %s\n", conta->dataNascimento);
	fprintf(arquivo, "Número da Conta        : %s\n", numeroConta);
	fprintf(arquivo, "Endereço               : %s\n", conta->rua);
	fprintf(arquivo, "Número                 : %s\n", conta->numero);
	fprintf(arquivo, "Bairro                 : %s\n", conta->bairro);
	fprintf(arquivo, "Cidade                 : %s\n", conta->cidade);
	fprintf(arquivo, "Estado                 : %s\n", conta->estado);
	fprintf(arquivo, "CEP                    : %s\n", conta->cep);
	fprintf(arquivo, "Tipo de conta          : %s\n", conta->tipoConta);
	fprintf(arquivo, "Telefone               : %s\n", conta->telefone);
	fprintf(arquivo, "E-mail                 : %s\n", conta->email);
	fprintf(arquivo, "Senha                  : %s\n", conta->senha);
	fprintf(arquivo, "Senha de Transação     : %s\n", conta->senhaTransacao);
	fprintf(arquivo, "Pergunta Secreta       : %s\n", conta->perguntaSecreta);
	fprintf(arquivo, "Resposta Secreta       : %s\n", conta->respostaSecreta);
	fprintf(arquivo, "Saldo                  : R$ %.2f\n", conta->saldo);
	fprintf(arquivo, "Conta criada em        : %s\n\n", dataCriacao);
	fprintf(arquivo, "\n=============================================\n");
	fprintf(arquivo, "         CAIXA DE ENTRADA DO TELEFONE  \n\n\n");
	fprintf(arquivo, "\n=============================================\n");
	fprintf(arquivo, "         CAIXA DE ENTRADA DO E-MAIL  \n\n");

	fprintf(arquivo, "\n\n\n=============================================\n");
	fprintf(arquivo, "        EXTRATO BANCÁRIO   \n");
	fprintf(arquivo, "=============================================\n");
	fprintf(arquivo, "Saldo Atual: R$ %.2f\n\n",conta->saldo );
	fprintf(arquivo, "Data e Hora           | Tipo              | Valor      | Destinatário       | Código de Transação\n");
	fprintf(arquivo, "-----------------------------------------------------------------------------------------------\n");

	fclose(arquivo);
	arquivo = fopen("contas.txt", "r+");
	if (arquivo == NULL) {
		arquivo = fopen("contas.txt", "w");
		fprintf(arquivo, "----------------------------------------\n");
		fprintf(arquivo, "       REGISTRO DE CONTAS DO BANCO      \n");
		fprintf(arquivo, "----------------------------------------\n\n");
		fprintf(arquivo, "Total de clientes no banco: 0\n\n");
	} else {
		char linha[256];
		while (fgets(linha, sizeof(linha), arquivo)) {
			if (strstr(linha, "Total de clientes no banco:")) {
				sscanf(linha, "Total de clientes no banco: %d", &totalContas);
				break;
			}
		}
	}

	totalContas++;

	fseek(arquivo, 0, SEEK_SET);
	fprintf(arquivo, "----------------------------------------\n");
	fprintf(arquivo, "       REGISTRO DE CONTAS DO BANCO      \n");
	fprintf(arquivo, "----------------------------------------\n\n");
	fprintf(arquivo, "Total de clientes no banco: %d\n\n", totalContas);

	fseek(arquivo, 0, SEEK_END);

	fprintf(arquivo, "Cliente %d:\n", totalContas);
	fprintf(arquivo, "----------------------------------------\n");
	fprintf(arquivo, "Pix                    : %s\n", conta->pix);
	fprintf(arquivo, "CPF                    : %s\n", conta->cpf);
	fprintf(arquivo, "Nome completo          : %s\n", conta->nomeCompleto);
	fprintf(arquivo, "Data de nascimento     : %s\n", conta->dataNascimento);
	fprintf(arquivo, "Número da Conta        : %s\n", numeroConta);
	fprintf(arquivo, "Conta criada em        : %s\n", dataCriacao);
	fprintf(arquivo, "----------------------------------------\n\n");

	fclose(arquivo);

	system("cls");
	menucriarconta();

	corTexto(9);
	printf("\n****************************************************\n");
	printf("*                                                   *\n");
	corTexto(14);
	printf("* Olá, %s! Estamos finalizando seu cadastro.*\n", conta->nomeCompleto);
	corTexto(9);
	printf("*                                                   *\n");
	printf("****************************************************\n\n");

	corTexto(10);
	printf("Aguarde um momento enquanto concluímos o processo");
	for (int j = 0; j < 8; j++) {
		printf(".");
		fflush(stdout);
		Sleep(1000);
	}

	system("cls");
	corTexto(9);
	printf("\n====================================\n");
	corTexto(14);
	printf("    CONTA CRIADA COM SUCESSO!\n");
	printf("    Bem-vindo ao ProtecBank!\n");
	corTexto(9);
	printf("====================================\n");
	corTexto(11);

	mascararCPF(conta->cpf, cpfFormatado);
	corTexto(9);
	printf("\n====================================\n");
	corTexto(14);
	printf("        DETALHES DA CONTA\n");
	corTexto(9);
	printf("====================================\n");
	corTexto(11);
	printf("Nome completo          : %s\n", conta->nomeCompleto);
	printf("Data de nascimento     : %s\n", conta->dataNascimento);
	printf("CPF                    : %s\n", cpfFormatado);
	printf("Número da Conta        : %s\n", numeroConta);
	printf("Endereço               : %s\n", conta->rua);
	printf("Número                 : %s\n", conta->numero);
	printf("Bairro                 : %s\n", conta->bairro);
	printf("Cidade                 : %s\n", conta->cidade);
	printf("Estado                 : %s\n", conta->estado);
	printf("CEP                    : %s\n", conta->cep);
	printf("Tipo de conta          : %s\n", conta->tipoConta);
	printf("Pix                    : %s\n", conta->pix);
	printf("Telefone               : %s\n", conta->telefone);
	printf("E-mail                 : %s\n", conta->email);
	printf("Senha                  : %s\n", conta->senha);
	printf("Senha de Transação     : %s\n", conta->senhaTransacao);
	printf("Pergunta Secreta       : %s\n", conta->perguntaSecreta);
	printf("Resposta Secreta       : %s\n", conta->respostaSecreta);
	printf("Saldo disponível       : R$ %.2f\n", conta->saldo);
	printf("Conta criada em        : %s\n", dataCriacao);

}

void mascararCPF(char *cpf, char *cpfFormatado) {
	snprintf(cpfFormatado, 15, "***.%.3s.***-%c%c", cpf + 3, cpf[9], cpf[10]);
}

void RemoverDoBancoDeDados(char *cpf, const char *pix, const char *numeroConta, const char *nome) {

	/*
	Localiza e remove um cliente do arquivo de contas com base no Pix informado.
	Ao encontrar o cliente, registra os dados da exclusão (CPF, nome, conta e data)
	em um novo arquivo temporário. Depois, substitui o arquivo original pelo temporário
	sem os dados da conta excluída. Exibe uma mensagem se o cliente não for encontrado.
	*/

	FILE *arquivoOriginal, *arquivoTemp;
	char linha[20000];
	int clienteEncontrado = 0;
	char cpfFormatado[20];

	arquivoOriginal = fopen("contas.txt", "r");
	if (!arquivoOriginal) {
		printf("Erro ao abrir o arquivo original.\n");
		return;
	}

	arquivoTemp = fopen("TempContasBanco.txt", "w");
	if (!arquivoTemp) {
		printf("Erro ao criar o arquivo temporário.\n");
		fclose(arquivoOriginal);
		return;
	}

	mascararCPF(cpf, cpfFormatado);

	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	char dataHoraAtual[50];
	snprintf(dataHoraAtual, sizeof(dataHoraAtual), "%02d/%02d/%04d %02d:%02d",
	         tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min);

	while (fgets(linha, 20000, arquivoOriginal)) {

		if (strstr(linha, pix)) {
			clienteEncontrado = 1;

			while (fgets(linha, 20000, arquivoOriginal)) {
				if (strstr(linha, "----")) {
					break;
				}
			}

			fprintf(arquivoTemp, "         *** Conta excluida *** \n");
			fprintf(arquivoTemp, "CPF                    : %s\n", cpfFormatado);
			fprintf(arquivoTemp, "Nome do cliente        : %s\n", nome);
			fprintf(arquivoTemp, "Número da conta        : %s\n\n", numeroConta);
			fprintf(arquivoTemp, "Data da exclusão       : %s\n", dataHoraAtual);
			fprintf(arquivoTemp, "----------------------------------------\n");
			continue;
		}

		fprintf(arquivoTemp, "%s", linha);
	}

	fclose(arquivoOriginal);
	fclose(arquivoTemp);

	if (clienteEncontrado) {
		remove("contas.txt");
		rename("TempContasBanco.txt", "contas.txt");
	} else {
		remove("TempContasBanco.txt");
		printf("\nNenhum cliente encontrado com o Pix %s.\n", pix);
	}
}

void cabDeletar() {

	corTexto(9);
	printf("\n===============================================\n");
	corTexto(14);
	printf("       ENCERRAR CONTA BANCARIA     \n");
	printf("             PROTECBANK              \n");
	corTexto(9);
	printf("===============================================\n");
	corTexto(11);
}

void DeletarConta(ContaBancaria *conta) {

	/*
	Permite que um cliente exclua sua conta bancária do sistema com segurança,
	garantindo validação por CPF e confirmação por senha onde sua conta é deletada do banco.
	*/

	char linha[200];
	char nomeUsuario[100];
	char senhaArquivo[50];
	char chavePix[50];
	char numeroConta[50];
	FILE *arquivo;
	int tentarNovamente;
	char nomeArquivo[30];
	char senhaInformada[30];
	char cpfFormatado[15];
	char cpf[20];

	cabDeletar();

	do {

		printf("\n> Insira seu CPF (apenas números): ");
		corTexto(14);
		fgets(conta->cpf, sizeof(conta->cpf), stdin);
		conta->cpf[strcspn(conta->cpf, "\n")] = 0;
		corTexto(11);

		if (strlen(conta->cpf) != 11) {
			corTexto(12);
			printf("\nO CPF deve conter exatamente 11 dígitos. Tente novamente.\n");
			corTexto(11);
			continue;
		}

		mascararCPF(conta->cpf, cpfFormatado);

		snprintf(nomeArquivo, sizeof(nomeArquivo), "%s.txt", conta->cpf);
		arquivo = fopen(nomeArquivo, "r");

		if (arquivo == NULL) {
			corTexto(12);
			printf("\nNenhuma conta vinculada ao CPF %s foi encontrada.\n", conta->cpf);
			corTexto(11);

			do {
				printf("\nDeseja tentar novamente?\n");
				printf("1. Sim, inserir o CPF novamente\n");
				printf("2. Não, cancelar exclusão\n");
				printf("Escolha: ");
				scanf("%d", &tentarNovamente);
				fflush(stdin);

				if (tentarNovamente != 1 && tentarNovamente != 2) {
					corTexto(12);
					printf("\nOpção inválida. Por favor, escolha 1 ou 2.\n");
					corTexto(11);
				}
			} while (tentarNovamente != 1 && tentarNovamente != 2);

			if (tentarNovamente == 2) {
				corTexto(12);
				printf("\n[OPERAÇÃO CANCELADA] Nenhuma alteração foi feita na conta.\n");
				corTexto(11);
				return;
			}
		} else {
			break;
		}
	} while (1);

	int encontrouNome = 0, encontrouSenha = 0, encontrouPix = 0, encontrouNumeroConta = 0;

	while (fgets(linha, sizeof(linha), arquivo) != NULL) {
		if (strncmp(linha, "Nome completo          :", 23) == 0) {
			sscanf(linha, "Nome completo          : %[^\n]", nomeUsuario);
			encontrouNome = 1;
		} else if (strncmp(linha, "Senha                  :", 23) == 0) {
			sscanf(linha, "Senha                  : %s\n", senhaArquivo);
			encontrouSenha = 1;
		} else if (strncmp(linha, "Pix                    :", 23) == 0) {
			sscanf(linha, "Pix                    : %[^\n]", chavePix);
			encontrouPix = 1;
		} else if (strncmp(linha, "Número da Conta        :", 23) == 0) {
			sscanf(linha, "Número da Conta        : %[^\n]", numeroConta);
			encontrouNumeroConta = 1;
		}

		if (encontrouNome && encontrouSenha && encontrouPix && encontrouNumeroConta) {
			break;
		}
	}
	fclose(arquivo);

	if (!encontrouNome || !encontrouSenha || !encontrouPix || !encontrouNumeroConta) {
		corTexto(12);
		printf("\nDados corrompidos ou incompletos. Operação abortada.\n");
		corTexto(11);
		return;
	}

	do {
		system("cls");
		cabDeletar();
		corTexto(11);
		printf("\nOlá, ");
		corTexto(14);
		printf("%s!\n", nomeUsuario);
		corTexto(11);
		printf("\nPara encerrar sua conta, precisamos confirmar sua senha.\n");
		printf("Digite sua senha: ");
		corTexto(14);

		int i = 0;
		char ch;
		while ((ch = getch()) != '\r') {
			if (ch == '\b') {
				if (i > 0) {
					i--;
					printf("\b \b");
				}
			} else {
				senhaInformada[i++] = ch;
				printf("*");
			}
		}
		senhaInformada[i] = '\0';

		int op;
		if (strlen(senhaInformada) < 6) {
			do {
				corTexto(12);
				printf("\nA senha deve ter no mínimo 6 caracteres. Tente novamente.\n");
				corTexto(11);
				printf("\n[1] - Tentar novamente!");
				printf("\n[2] - Esqueci minha senha!");
				printf("\n[3] - Sair\nR:");
				scanf("%d", &op);
				fflush(stdin);

				switch(op) {

					case 1:
						continue;
					case 2:
						system("cls");
						strcpy(cpf, conta->cpf);
						RedefinirSenha(cpf);
						printf("\nO que você deseja fazer?");
						printf("\n[1] - Voltar a exclusao da minha conta!");
						printf("\n[2] - Sair");
						printf("\nR: ");
						scanf("%d", &op);
						fflush(stdin);

						if(op==1) {
							system("cls");
							DeletarConta(conta);
						} else if(op==2) {
							exit(1);
							printf("\nObrigado e até a próxima!!!");
						} else {
							printf("Opção inválida!!!");
						}

					case 3:
						exit(1);

					default:
						corTexto(12);
						printf("Opção inválida!!!");
						corTexto(11);
				}

				int op;
				printf("\nO que você deseja fazer?");
				printf("\n[1] - Voltar a exclusao da minha conta!");
				printf("\n[2]-  Voltar ao menu de atendimento!");
				printf("\n[3] - Sair");
				printf("\nR: ");
				scanf("%d", &op);
				fflush(stdin);

				if(op==1) {
					system("cls");
					DeletarConta(conta);
				} else if(op==2) {
					exit(1);
					printf("\nObrigado e até a próxima!!!");
				} else {
					corTexto(12);
					printf("Opção inválida!!!");
					corTexto(11);
				}


			} while(op < 1 || op >2 );

		}

		if (strcmp(senhaArquivo, senhaInformada) == 0) {
			system("cls");
			cabDeletar();
			corTexto(14);

			printf("\n\nAguarde um momento, estamos encerrando sua conta");

			for (int j = 0; j < 10; j++) {
				printf(".");
				fflush(stdout);
				Sleep(700);
			}
			corTexto(11);

			RemoverDoBancoDeDados(conta->cpf, chavePix, numeroConta, nomeUsuario);

			if (remove(nomeArquivo) == 0) {
				printf("\n\n");
				corTexto(10);
				printf("******************************************************\n");
				printf("  Conta excluída com sucesso! Sentiremos sua falta.\n");
				printf("  Muito obrigado por confiar no ProtecBank, %s!\n", nomeUsuario);
				printf("******************************************************\n\n");
				corTexto(11);
			} else {
				printf("\n\n");
				corTexto(12);
				printf("******************************************************\n");
				printf("  Não foi possível excluir sua conta no momento.\n");
				printf("  Por favor, tente novamente mais tarde.\n");
				printf("******************************************************\n\n");
				corTexto(11);
			}
			return;

		} else {
			corTexto(12);
			printf("\nA senha informada está incorreta!\n");
			corTexto(11);
			int op;
			do {
				corTexto(11);
				printf("[1] - Tentar novamente!\n");
				printf("[2] - Esqueci minha senha!\n");
				printf("[3] - Sair\n");
				printf("Escolha: ");
				scanf("%d", &op);
				fflush(stdin);

				switch(op) {

					case 1:
						system("cls");
						continue;
					case 2:
						system("cls");
						strcpy(cpf, conta->cpf);
						RedefinirSenha(cpf);
						printf("\nO que você deseja fazer?");
						printf("\n[1] - Voltar a exclusao da minha conta!");
						printf("\n[2] - Sair");
						printf("\nR: ");
						scanf("%d", &op);
						fflush(stdin);

						if(op==1) {
							system("cls");
							DeletarConta(conta);
						} else if(op==2) {
							exit(1);
							printf("\nObrigado e até a próxima!!!");
						} else {
							printf("Opção inválida!!!");
						}

					case 3:
						exit(1);

					default:
						corTexto(12);
						printf("Opção inválida!!!");
						corTexto(11);
				}

			} while(op < 1 || op >2 );
		}
	} while (1);
}

void excluirSenha(FilaBanco *fila) {

	/*
	Remove um cliente específico da fila do banco ProtecBank com base em sua senha,
	além de excluir o arquivo de comprovante associado ao atendimento
	*/

	system("cls");
	while (1) {
		corTexto(9);
		printf("\n==========================================\n");
		corTexto(14);
		printf("        	EXCLUIR SENHA     \n");
		printf("                 PROTECBANK              \n");
		corTexto(9);
		printf("==========================================\n");
		corTexto(11);

		int encontrado;
		char senha[10];
		char nome[30];

		if (fila->frente == fila->atras) {
			corTexto(12);
			printf("\nA fila está vazia. Não há clientes para excluir.\n");
			corTexto(11);
			printf("\n\nPressione Enter para voltar ao menu...\n");
			getchar();
			system("cls");
			return;
		}

		corTexto(14);
		printf("\n		Clientes na fila\n\n");
		corTexto(11);

		corTexto(11);
		printf("\n%-10s%-20s%-20s%-10s%-10s\n", "Posição", "Nome", "Tipo de Serviço", "Senha", "Guichê");
		printf("------------------------------------------------------------\n");

		corTexto(14);
		for (int i = 0; i < fila->atras; i++) {
			printf("%-10d%-20s%-20s%-10s%d e %d\n",
			       i + 1,
			       fila->clientes[i].nome,
			       fila->clientes[i].tipoServico,
			       fila->clientes[i].senha,
			       fila->clientes[i].mesas[0],
			       fila->clientes[i].mesas[1]);
		}
		corTexto(11);
		printf("\n\nDigite a senha do cliente a ser excluído: ");
		corTexto(14);
		fgets(senha, sizeof(senha), stdin);
		senha[strcspn(senha, "\n")] = '\0';
		corTexto(11);

		encontrado = 0;

		for (int i = fila->frente; i < fila->atras; i++) {
			if (strcmp(fila->clientes[i].senha, senha) == 0) {
				encontrado = 1;
				corTexto(14);
				printf("\nRemovendo a senha da fila, aguarde");
				exibirPontos();
				if (remove(fila->clientes[i].arquivoComprovante) == 0) {
					corTexto(10);
					printf("\n\nA senha de %s foi excluída com sucesso.\n", fila->clientes[i].nome);
					corTexto(11);
				} else {
					printf("Erro ao excluir o arquivo de comprovante '%s'.\n", fila->clientes[i].arquivoComprovante);
				}

				for (int j = i; j < fila->atras - 1; j++) {
					fila->clientes[j] = fila->clientes[j + 1];
				}
				fila->atras--;

				corTexto(10);
				printf("A senha '%s' foi excluida com sucesso.\n", senha);
				corTexto(11);
				int escolha;

				while (1) {
					printf("\nDeseja excluir outra senha?\n[1] - Não, voltar ao menu\n[2] - Sim\nEscolha: ");
					scanf("%d", &escolha);
					fflush(stdin);

					if (escolha == 1) {
						system("cls");
						return;
					} else if (escolha == 2) {
						system("cls");
						break;
					} else {
						corTexto(12);
						printf("\nOpção inválida. Digite 1 para não ou 2 para sim.\n");
						corTexto(11);
					}
				}

			}
		}

		if (!encontrado) {
			system("cls");
			corTexto(12);
			printf("\nA senha '%s' não foi encontrada. Tente novamente.\n", senha);
			corTexto(11);
		}


	}
}

void cabSaldo() {

	corTexto(9);
	printf("\n===============================================\n");
	corTexto(14);
	printf("             CONSULTA DE SALDO     \n");
	printf("                PROTECBANK              \n");
	corTexto(9);
	printf("===============================================\n");
}

void consultarSaldo(char *cpf, char *senha, int recursivo) {

	/*
	Consulta o saldo da conta bancária do cliente após validar CPF e senha.
	Utiliza um parâmetro de controle (recursivo) para evitar a repetição desnecessária da autenticação
	quando a função é chamada novamente por outras operações como depósito, saque, extrato ou transferência.
	*/

	char linha[256], senhaArquivo[20], nomeCliente[50], saldoAtual[20];
	double saldoAtualDouble;
	int encontrado = 0;
	char nomeArquivo[30];

	cabSaldo();

	if (recursivo == 0) {
		do {
			corTexto(11);
			printf("Informe seu CPF: ");
			corTexto(14);
			scanf("%s", cpf);
			fflush(stdin);
			corTexto(11);


			sprintf(nomeArquivo, "%s.txt", cpf);
			FILE *arquivo = fopen(nomeArquivo, "r");
			if (arquivo == NULL) {
				corTexto(12);
				printf("Erro: CPF não localizado no nosso banco. Corrija e tente novamente!\n");
				corTexto(11);
			} else {
				fclose(arquivo);
				encontrado = 1;
			}
		} while (!encontrado);
	}

	encontrado = 0;

	if (recursivo == 0) {
		do {
			corTexto(11);
			printf("Confirme sua senha para continuar: ");
			corTexto(14);
			scanf("%s", senha);
			fflush(stdin);
			corTexto(11);

			char nomeArquivo[30];
			sprintf(nomeArquivo, "%s.txt", cpf);
			FILE *arquivo = fopen(nomeArquivo, "r");
			while (fgets(linha, sizeof(linha), arquivo)) {
				if (strstr(linha, "Senha                  : ")) {
					sscanf(linha, "Senha                  : %s", senhaArquivo);
					break;
				}
			}
			fclose(arquivo);

			if (strcmp(senha, senhaArquivo) != 0) {
				corTexto(12);
				printf("Erro: Senha incorreta. Tente novamente.\n");
				corTexto(7);
			} else {
				encontrado = 1;
			}
		} while (!encontrado);
	}

	if (recursivo == 1) {
		do {
			corTexto(11);
			printf("Confirme sua senha novamente para continuar: ");
			corTexto(14);
			scanf("%s", senha);

			char nomeArquivo[30];
			sprintf(nomeArquivo, "%s.txt", cpf);
			FILE *arquivo = fopen(nomeArquivo, "r");
			while (fgets(linha, sizeof(linha), arquivo)) {
				if (strstr(linha, "Senha                  : ")) {
					sscanf(linha, "Senha                  : %s", senhaArquivo);
					break;
				}
			}
			fclose(arquivo);

			if (strcmp(senha, senhaArquivo) != 0) {
				corTexto(12);
				printf("Erro: Senha incorreta. Tente novamente.\n");
				corTexto(7);
			} else {
				encontrado = 1;
			}
		} while (!encontrado);
	}

	sprintf(nomeArquivo, "%s.txt", cpf);
	FILE *arquivo = fopen(nomeArquivo, "r");
	if (arquivo == NULL) {
		corTexto(12);
		printf("Erro: Não foi possível acessar o arquivo do cliente. Verifique o CPF.\n");
		corTexto(7);
		return;
	}

	while (fgets(linha, sizeof(linha), arquivo)) {
		if (strstr(linha, "Nome completo          : ")) {
			sscanf(linha, "Nome completo          : %[^\n]", nomeCliente);
		} else if (strstr(linha, "Saldo Atual: R$ ")) {
			sscanf(linha, "Saldo Atual: R$ %s", saldoAtual);
		}
	}
	saldoAtualDouble = atof(saldoAtual);

	corTexto(10);
	printf("\nSenha correta, carregando seu saldo, aguarde");
	for (int i = 0; i < 8; i++) {
		printf(".");
		fflush(stdout);
		Sleep(700);
	}

	printf("\n");

	system("cls");
	cabSaldo();
	corTexto(9);
	printf("\n\n--------------------------------------------\n");
	printf(" Olá, %s!\n", nomeCliente);
	printf("--------------------------------------------\n");
	corTexto(11);
	printf("\n>> Seu saldo atual é: ");
	corTexto(14);
	printf("R$ %.2f\n\n", saldoAtualDouble);
	corTexto(11);
	printf("--------------------------------------------\n");

	int escolha;
	do {
		printf("\nO que você deseja fazer?\n");
		printf("[1] - Realizar um depósito\n");
		printf("[2] - Realizar um saque\n");
		printf("[3] - Consultar meu extrato\n");
		printf("[4] - Realizar uma transferência\n");
		printf("[5] - Sair\n");
		printf("Escolha: ");
		scanf("%d", &escolha);
		fflush(stdin);

		switch (escolha) {
			case 1:
				system("cls");
				realizarDeposito(cpf, senha, 1);
				return;
			case 2:
				system("cls");
				realizarSaque(cpf, senha, 1);
				return;
			case 3:
				extrato(cpf, senha, 1);
				return;

			case 4:
				system("cls");
				realizarTransferencia(cpf, senha, 1);
				return;
			case 5:
				printf("Finalizando atendimento, aguarde");
				exibirPontos();
				exit(0);

			default:
				printf("Opção inválida. Tente novamente.\n");
		}
	} while (escolha < 1 || escolha > 3);
}

void CabDep() {

	corTexto(9);
	printf("\n============================================\n");
	corTexto(14);
	printf("               PROTECBANK                   \n");
	printf("              Bem-vindo(a)             \n");
	corTexto(9);
	printf("============================================\n");
	corTexto(11);
	printf("----------- DEPOSITO DE VALORES -----------\n");
	printf("--------------------------------------------\n\n");

}

void realizarDeposito(char *cpf, char *senha, int recursivo) {

	/*
	Realiza um depósito na conta do cliente após autenticação e confirmação do valor.
	Atualiza o saldo no arquivo e registra a transação no extrato no arquivo .txt
	*/

	char linha[256], senhaArquivo[20], senhaTransacao[10];
	char nomeCliente[50], saldo[20], saldoAtual[20];
	char senhaTransacaoInput[10];
	double saldoAtualDouble, saldoNovo, deposito;
	int encontrado = 0;
	int escolha;
	char codigoTransacao[20];
	char nomeArquivo[30];
	char saldoAtualStr[20];
	char numeroConta[20];

	time_t agora;
	struct tm *infoTempo;
	char dataHora[30];
	time(&agora);
	infoTempo = localtime(&agora);
	strftime(dataHora, 30, "%d/%m/%Y %H:%M:%S", infoTempo);

	CabDep();

	if (recursivo == 0 ) {
		do {
			corTexto(11);
			printf("Informe seu CPF: ");
			corTexto(14);
			scanf("%s", cpf);
			fflush(stdin);
			corTexto(11);

			sprintf(nomeArquivo, "%s.txt", cpf);
			FILE *arquivo = fopen(nomeArquivo, "r");
			if (arquivo == NULL) {
				corTexto(12);
				printf("Erro: CPF não localizado no nosso banco. Corrija e tente novamente!\n");
				corTexto(11);
			} else {
				fclose(arquivo);
				encontrado = 1;
			}
		} while (!encontrado);
	}
	encontrado = 0;


	sprintf(nomeArquivo, "%s.txt", cpf);
	FILE *arquivo = fopen(nomeArquivo, "r+");
	if (arquivo == NULL) {
		corTexto(12);
		printf("Erro: Não foi possível acessar o arquivo do cliente. Verifique o CPF.\n");
		corTexto(11);
		return;
	}

	while (fgets(linha, sizeof(linha), arquivo)) {
    if (strstr(linha, "Nome completo          : ")) {
        sscanf(linha, "Nome completo          : %[^\n]", nomeCliente);
    } else if (strstr(linha, "Número da Conta        : ")) {
        sscanf(linha, "Número da Conta        : %[^\n]", numeroConta);
    } else if (strstr(linha, "Saldo                  : ")) {
        sscanf(linha, "Saldo                  : R$ %s", saldo);
    } else if (strstr(linha, "Saldo Atual: R$ ")) {
        sscanf(linha, "Saldo Atual: R$ %s", saldoAtual);
    } else if (strstr(linha, "Senha de Transação     : ")) {
        sscanf(linha, "Senha de Transação     : %s", senhaTransacao);
    }
}

	if (recursivo == 0) {
		do {
			corTexto(11);
			printf("Informe a senha: ");
			corTexto(14);
			scanf("%s", senha);
			fflush(stdin);

			char nomeArquivo[30];
			sprintf(nomeArquivo, "%s.txt", cpf);
			FILE *arquivo = fopen(nomeArquivo, "r");
			while (fgets(linha, sizeof(linha), arquivo)) {
				if (strstr(linha, "Senha                  : ")) {
					sscanf(linha, "Senha                  : %s", senhaArquivo);
					break;
				}
			}
			fclose(arquivo);

			if (strcmp(senha, senhaArquivo) != 0) {
				corTexto(12); 
				printf("Erro: Senha incorreta. Tente novamente.\n");
				corTexto(11); 
			} else {
				encontrado = 1;
			}
		} while (!encontrado);
	}

	corTexto(10);
	printf("\nCarregando suas informações, aguarde");
	for (int i = 0; i < 6; i++) {
		printf(".");
		fflush(stdout);
		Sleep(1000);
	}
	system("cls");
	CabDep();
	corTexto(9);
	printf("\n--------------------------------------------\n");
	printf(" Olá, %s!\n", nomeCliente);
	printf("--------------------------------------------\n");
	corTexto(11);
	printf("\n>> Seu saldo atual é: ");
	corTexto(14);
	printf("R$ %s\n\n", saldo);
	corTexto(11);

	do {
		if(escolha == 1) {
			break;
		}
		do {

			printf("Informe o valor que deseja depositar: ");
			corTexto(14);
			printf("R$ ");
			fflush(stdin);


			if (scanf("%lf", &deposito) != 1 || deposito <= 0) {

				while(getchar() != '\n');

				corTexto(12);
				printf("Por favor, insira um valor numérico válido maior que 0!!!.\n");
				corTexto(11);
			} else {
				break;
			}

		} while (1);

		do {
			corTexto(11);
			printf("\nVocê está depositando ");
			corTexto(14);
			printf("%.2lf, ",deposito);
			corTexto(11);
			printf("confirma o valor? \n[1] - Sim\n[2] - Não, corrigir\nR: ");
			scanf("%d", &escolha);
			fflush(stdin);

			if(escolha == 1) {
				break;
			} else if(escolha ==2) {
				break;
			} else if(escolha != 1 || escolha != 2) {
				corTexto(12); 
				printf("\nOpção inválid!!!\n");
				corTexto(11); 
			}
		} while(escolha != 1 || escolha != 2);
	} while(escolha != 1 || escolha != 2);

	encontrado = 0;

	do {
		corTexto(11);
		printf("Para finalizar confirme sua senha de 4 dígitos: ");
		corTexto(14);
		scanf("%s", senhaTransacaoInput);
		fflush(stdin);
		corTexto(11);

		if (strcmp(senhaTransacaoInput, senhaTransacao) != 0) {
			corTexto(12);
			printf("Erro: Senha de transação incorreta. Tente novamente.\n");
			corTexto(1);
		} else {
			encontrado = 1;
		}
	} while (!encontrado);

	saldoAtualDouble = atof(saldo);
	saldoNovo = saldoAtualDouble + deposito;

	rewind(arquivo);
	FILE *tempArquivo = fopen("temp_cliente.txt", "w");
	while (fgets(linha, sizeof(linha), arquivo)) {
		if (strstr(linha, "Saldo                  : ")) {
			fprintf(tempArquivo, "Saldo                  : R$ %.2f\n", saldoNovo);
		} else if (strstr(linha, "Saldo Atual: R$ ")) {
			fprintf(tempArquivo, "Saldo Atual: R$ %.2f\n", saldoNovo);
		} else {
			fprintf(tempArquivo, "%s", linha);
		}
	}
	fclose(arquivo);
	fclose(tempArquivo);

	remove(nomeArquivo);
	rename("temp_cliente.txt", nomeArquivo);

	*saldoAtual = saldoNovo;

	corTexto(10);
	printf("\nFinalizando seu deposito, aguarde");
	for (int i = 0; i < 5; i++) {
		printf(".");
		fflush(stdout);
		Sleep(1000);
	}

	corTexto(10);
	printf("\nDepósito no valor de R$ %.2lf realizado com sucesso!\n", deposito);

	corTexto(11);
	printf("\nNovo saldo disponível: ");
	corTexto(14);
	printf("R$ %.2f\n\n", saldoNovo);
	corTexto(11);
	
	gerarCodigoTransacao(codigoTransacao);
	
	fflush(stdin);
	int opcaoComprovante;
	corTexto(11);
	printf("\nDeseja baixar o comprovante de depósito?\n[1] - Sim\n[2] - Não\nOpção: ");
	scanf("%d", &opcaoComprovante);
	fflush(stdin);

	if (opcaoComprovante == 1) {
		char nomeComprovante[100];
		snprintf(nomeComprovante, sizeof(nomeComprovante),
		         "Deposito_%s_%s.txt", nomeCliente, codigoTransacao);

		FILE *comprovante = fopen(nomeComprovante, "w");
		fprintf(comprovante, "--------------------------------------------------\n");
		fprintf(comprovante, "|              COMPROVANTE DE DEPÓSITO            |\n");
		fprintf(comprovante, "--------------------------------------------------\n");
		fprintf(comprovante, "Valor: R$ %.2f\n", deposito);
		fprintf(comprovante, "Tipo de Operação: Depósito\n");
		fprintf(comprovante, "Data e Hora: %s\n", dataHora);
		fprintf(comprovante, "Código da Transação: %s\n", codigoTransacao);
		fprintf(comprovante, "--------------------------------------------------\n");
		fprintf(comprovante, "|                INFORMAÇÕES DO CLIENTE           |\n");
		fprintf(comprovante, "--------------------------------------------------\n");
		fprintf(comprovante, "Nome: %s\n", nomeCliente);
		fprintf(comprovante, "Instituição: ProtectBank\n");
		fprintf(comprovante, "Agência: 0001\n");
		fprintf(comprovante, "Número da Conta: %s\n", numeroConta);
		fprintf(comprovante, "--------------------------------------------------\n");
		fprintf(comprovante, "|             Depósito realizado com sucesso!     |\n");
		fprintf(comprovante, "--------------------------------------------------\n");
		fclose(comprovante);
		corTexto(10);
		printf("\nComprovante gerado com sucesso!\n");
		corTexto(11);
	}

	FILE *arquivoExtrato = fopen(nomeArquivo, "a");
	if (!arquivoExtrato) {
		corTexto(12);
		printf("Erro ao abrir o arquivo para registrar o extrato.\n");
		corTexto(7);
	} else {
		fprintf(arquivoExtrato, "%s   | %s          | %+7.2f    |                    | %s\n",
		        dataHora, "Depósito", deposito, codigoTransacao);
		fclose(arquivoExtrato);

	}

	do {
		printf("\nO que você deseja fazer?\n");
		printf("[1] - Realizar um depósito\n");
		printf("[2] - Realizar um saque\n");
		printf("[3] - Consultar meu extrato e meu saldo\n");
		printf("[4] - Realizar uma transferência\n");
		printf("[5] - Sair\n");
		printf("Escolha: ");
		scanf("%d", &escolha);
		fflush(stdin);

		switch (escolha) {
			case 1:
				system("cls");
				realizarDeposito(cpf, senha, 1);
				return;
			case 2:
				realizarSaque(cpf, senha, 1);
				return;
			case 3:
				extrato(cpf, senha, 1);
				return;

			case 4:
				realizarTransferencia(cpf, senha, 1);
				return;
			case 5:
				printf("Finalizanod atendimento, aguarde");
				exibirPontos();
				exit(0);


			default:
				printf("Opção inválida. Tente novamente.\n");
		}
	} while (escolha < 1 || escolha > 3);

}

void cabSaq() {

	corTexto(9);
	printf("\n============================================\n");
	corTexto(14);
	printf("               PROTECBANK                   \n");
	printf("              Bem-vindo(a)             \n");
	corTexto(9);
	printf("============================================\n");
	corTexto(11);

	printf("----------- SAQUE DE VALORES -----------\n");
	printf("--------------------------------------------\n");
}

void realizarSaque(char *cpf, char *senha, int recursivo) {

	/* Função responsável por realizar o saque do cliente. Valida CPF, senha e senha de transação,
	 atualiza o saldo no arquivo, registra o saque no extrato e oferece novas opções de operação.
	 O parâmetro 'recursivo' indica se a chamada foi feita a partir de outra função (1) ou não (0) */
	
	char linha[256], senhaArquivo[20], senhaTransacao[10];
	char nomeCliente[50], saldo[20], saldoAtual[20];
	char senhaTransacaoInput[10];
	double saldoAtualDouble, saldoNovo, saque;
	int encontrado = 0;
	int escolha;
	int entradaValida;
	char codigoTransacao[20];
	char nomeArquivo[30];
	char numeroConta[20];

	time_t agora;
	struct tm *infoTempo;
	char dataHora[30];
	time(&agora);
	infoTempo = localtime(&agora);
	strftime(dataHora, 30, "%d/%m/%Y %H:%M:%S", infoTempo);

	cabSaq();

	if (recursivo == 0 ) {
		do {
			corTexto(11);
			printf("Informe seu CPF: ");
			corTexto(14);
			scanf("%s", cpf);
			fflush(stdin);
			corTexto(11);

			sprintf(nomeArquivo, "%s.txt", cpf);
			FILE *arquivo = fopen(nomeArquivo, "r");
			if (arquivo == NULL) {
				corTexto(12);
				printf("Erro: CPF não localizado no nosso banco. Corrija e tente novamente!\n");
				corTexto(11);
			} else {
				fclose(arquivo);
				encontrado = 1;
			}
		} while (!encontrado);
	}
	encontrado = 0;

	sprintf(nomeArquivo, "%s.txt", cpf);
	FILE *arquivo = fopen(nomeArquivo, "r+");
	if (arquivo == NULL) {
		corTexto(12);
		printf("Erro: Não foi possível acessar o arquivo do cliente. Verifique o CPF.\n");
		corTexto(11);
		return;
	}

while (fgets(linha, sizeof(linha), arquivo)) {
	if (strstr(linha, "Nome completo          : ")) {
		sscanf(linha, "Nome completo          : %[^\n]", nomeCliente);
	} else if (strstr(linha, "Número da Conta        : ")) {
		sscanf(linha, "Número da Conta        : %s", numeroConta);
	} else if (strstr(linha, "Saldo                  : ")) {
		sscanf(linha, "Saldo                  : R$ %s", saldo);
	} else if (strstr(linha, "Saldo Atual: R$ ")) {
		sscanf(linha, "Saldo Atual: R$ %s", saldoAtual);
	} else if (strstr(linha, "Senha de Transação     : ")) {
		sscanf(linha, "Senha de Transação     : %s", senhaTransacao);
	}
}

	if (recursivo == 0) {
		do {
			corTexto(11);
			printf("Informe a senha: ");
			corTexto(14);
			scanf("%s", senha);
			fflush(stdin);

			char nomeArquivo[30];
			sprintf(nomeArquivo, "%s.txt", cpf);
			FILE *arquivo = fopen(nomeArquivo, "r");
			while (fgets(linha, sizeof(linha), arquivo)) {
				if (strstr(linha, "Senha                  : ")) {
					sscanf(linha, "Senha                  : %s", senhaArquivo);
					break;
				}
			}
			fclose(arquivo);

			if (strcmp(senha, senhaArquivo) != 0) {
				corTexto(12);
				printf("Erro: Senha incorreta. Tente novamente.\n");
				corTexto(11);
			} else {
				encontrado = 1;
			}
		} while (!encontrado);
	}
	encontrado = 0;

	corTexto(10);
	printf("\nCarregando seu saldo, aguarde");
	for (int i = 0; i < 6; i++) {
		printf(".");
		fflush(stdout);
		Sleep(1000);
	}
	system("cls");
	cabSaq();
	corTexto(9);
	printf("\n--------------------------------------------\n");
	corTexto(9);
	printf(" Bem vindo(a), ");
	corTexto(14);
	printf("%s!\n", nomeCliente);
	corTexto(9);
	printf("--------------------------------------------\n");
	corTexto(11);
	printf(">> Seu saldo atual é: ");
	corTexto(14);
	printf("R$ %s\n\n", saldo);
	corTexto(11);

	do {
		if(escolha == 1) {
			break;
		}
		do {

			printf("Informe o valor que deseja sacar: ");
			corTexto(14);
			printf("R$ ");
			fflush(stdin);

			if (scanf("%lf", &saque) != 1 || saque <= 0) {
				while(getchar() != '\n');
				corTexto(12);
				printf("Por favor, insira um valor numérico válido maior que 0!!!.\n");
				corTexto(11);
			} else if(saque > atof(saldo)) {
				corTexto(12);
				printf("Erro: Saldo insuficiente! Você possui R$ %.2f e tentou sacar R$ %.2f.\n", atof(saldo), saque);
				corTexto(11);
			}	else {
				break;
			}

		} while (1);

		corTexto(11);
		fflush(stdin);

		do {
			printf("\nVocê está sacando ");
			corTexto(14);
			printf("R$ %.2lf,",saque);
			corTexto(11);
			printf(" confirma o valor? \n[1] - Sim\n[2] - Não, corrigir\nR: ");
			scanf("%d", &escolha);
			fflush(stdin);

			if(escolha == 1) {
				break;
			} else if(escolha ==2) {
				break;
			} else if(escolha != 1 || escolha != 2) {
				printf("\nOpção inválid!!!\n");
			}
		} while(escolha != 1 || escolha != 2);
	} while(escolha != 1 || escolha != 2);

	encontrado = 0;

	do {
		printf("Para finalizar confirme sua senha de 4 dígitos: ");
		scanf("%s", senhaTransacaoInput);
		fflush(stdin);

		if (strcmp(senhaTransacaoInput, senhaTransacao) != 0) {
			corTexto(12);
			printf("Erro: Senha de transação incorreta. Tente novamente.\n");
			corTexto(11);
		} else {
			encontrado = 1;
		}
	} while (!encontrado);

	saldoAtualDouble = atof(saldo);
	saldoNovo = saldoAtualDouble - saque;

	rewind(arquivo);
	FILE *tempArquivo = fopen("temp_cliente.txt", "w");
	while (fgets(linha, sizeof(linha), arquivo)) {
		if (strstr(linha, "Saldo                  : ")) {
			fprintf(tempArquivo, "Saldo                  : R$ %.2f\n", saldoNovo);
		} else if (strstr(linha, "Saldo Atual: R$ ")) {
			fprintf(tempArquivo, "Saldo Atual: R$ %.2f\n", saldoNovo);
		} else {
			fprintf(tempArquivo, "%s", linha);
		}
	}
	fclose(arquivo);
	fclose(tempArquivo);

	remove(nomeArquivo);
	rename("temp_cliente.txt", nomeArquivo);

	*saldoAtual = saldoNovo;

	corTexto(10); 
	printf("\nFinalizando seu saque, aguarde");
	for (int i = 0; i < 5; i++) {
		printf(".");
		fflush(stdout);
		Sleep(1000);
	}

	corTexto(11);
	printf("\n\nSaque no valor de ");
	corTexto(14);
	printf("R$ %.2lf", saque);
	corTexto(11);
	printf(" realizado com sucesso!\n");

	printf("Novo saldo disponível: ");
	corTexto(14);
	printf("R$ %.2f\n\n", saldoNovo);
	corTexto(11); 

	gerarCodigoTransacao(codigoTransacao);
	
	
	int opcaoComprovante;
	corTexto(11);
	printf("\nDeseja baixar o comprovante de saque?\n[1] - Sim\n[2] - Não\nOpção: ");
	scanf("%d", &opcaoComprovante);
	fflush(stdin);

	if (opcaoComprovante == 1) {
		char nomeComprovante[100];
		snprintf(nomeComprovante, sizeof(nomeComprovante),
		         "Saque_%s_%s.txt", nomeCliente, codigoTransacao);

		FILE *comprovante = fopen(nomeComprovante, "w");
		fprintf(comprovante, "--------------------------------------------------\n");
		fprintf(comprovante, "|               COMPROVANTE DE SAQUE              |\n");
		fprintf(comprovante, "--------------------------------------------------\n");
		fprintf(comprovante, "Valor: R$ %.2f\n", saque);
		fprintf(comprovante, "Tipo de Operação: Saque\n");
		fprintf(comprovante, "Data e Hora: %s\n", dataHora);
		fprintf(comprovante, "Código da Transação: %s\n", codigoTransacao);
		fprintf(comprovante, "--------------------------------------------------\n");
		fprintf(comprovante, "|               INFORMAÇÕES DO CLIENTE            |\n");
		fprintf(comprovante, "--------------------------------------------------\n");
		fprintf(comprovante, "Nome: %s\n", nomeCliente);
		fprintf(comprovante, "Instituição: ProtectBank\n");
		fprintf(comprovante, "Agência: 0001\n");
		fprintf(comprovante, "Número da Conta: %s\n", numeroConta);
		fprintf(comprovante, "--------------------------------------------------\n");
		fprintf(comprovante, "|             Saque realizado com sucesso!        |\n");
		fprintf(comprovante, "--------------------------------------------------\n");
		fclose(comprovante);

		corTexto(10);
		printf("\nComprovante gerado com sucesso!\n");
		corTexto(11);
	}
	

	FILE *arquivoExtrato = fopen(nomeArquivo, "a");
	if (!arquivoExtrato) {
		corTexto(12);
		printf("Erro ao abrir o arquivo para registrar o extrato.\n");
		corTexto(7);
	} else {
		fprintf(arquivoExtrato, "%s   | %s             | -%.2f     |                    | %s\n",
		        dataHora, "Saque", saque, codigoTransacao);
		fclose(arquivoExtrato);
	}

	do {

		printf("\nO que você deseja fazer?\n");
		printf("[1] - Realizar um depósito\n");
		printf("[2] - Realizar um saque\n");
		printf("[3] - Consultar meu extrato e meu saldo\n");
		printf("[4] - Realizar uma transferência\n");
		printf("[5] - Sair\n");
		printf("Escolha: ");
		scanf("%d", &escolha);
		fflush(stdin);

		switch (escolha) {
			case 1:
				system("cls");
				realizarDeposito(cpf, senha, 1);
				return;
			case 2:
				realizarSaque(cpf, senha, 1);
				return;
			case 3:
				extrato(cpf, senha, 1);
				return;

			case 4:
				realizarTransferencia(cpf, senha, 1);
				return;
			case 5:
				printf("Finalizanod atendimento, aguarde");
				exibirPontos();
				exit(0);
			default:
				printf("Opção inválida. Tente novamente.\n");
		}
	} while (escolha < 1 || escolha > 3);

}

void gerarCodigoTransacao(char *codigoTransacao) {
	
	/* 
	Gera um código único de identificação para cada transação bancária realizada, 
	como saques, depósitos e transferências. O código é gerado de forma aleatória 
	no formato XXX-XXXX-XXXX, utilizando letras maiúsculas e números, e é armazenado 
	na string 'codigoTransacao' fornecida como parâmetro.
	*/
	
	const char alfanumerico[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	int tamanho = strlen(alfanumerico);

	for (int i = 0; i < 3; i++) {
		codigoTransacao[i] = alfanumerico[rand() % tamanho];
	}
	codigoTransacao[3] = '-';

	for (int i = 4; i < 8; i++) {
		codigoTransacao[i] = alfanumerico[rand() % tamanho];
	}
	codigoTransacao[8] = '-';

	for (int i = 9; i < 13; i++) {
		codigoTransacao[i] = alfanumerico[rand() % tamanho];
	}
	codigoTransacao[13] = '\0';
}

void cabTransf() {

	corTexto(9);
	printf("\n===============================================\n");
	corTexto(14);
	printf("              TRANSFERÊNCIAS     \n");
	printf("                PROTECBANK              \n");
	corTexto(9);
	printf("===============================================\n");
	corTexto(11);
}

void realizarTransferencia(char *cpf, char *senha, int recursivo) {
	
	/* 
	  Realiza a transferência PIX entre contas bancárias do sistema. 
	  A função inicia validando o CPF do remetente e sua senha de acesso. Após a autenticação, 
	  carrega as informações da conta e solicita a chave PIX do destinatário, realizando a busca 
	  no arquivo de contas onde ficam todas as contas cadastradas para identificar o usuário correspondente.
	
	  O sistema apresenta os dados do destinatário para confirmação e, em seguida, solicita o valor 
	  da transferência, verificando se o saldo é suficiente. Para concluir a transferência, é exigida a senha de 
	  transação cadastrada. Havendo sucesso, o valor é debitado do remetente e creditado ao destinatário, 
	  atualizando ambos os arquivos .txt de saldo com segurança através de arquivos temporários.
	
	  Por fim, a função registra o comprovante com data, valor transferido, nome do destinatário e um 
	  código único da transação para histórico de movimentações.
	  
   */

	char linha[256], senhaArquivo[20], senhaTransacao[10];
	char nomeCliente[50], numeroContaRemetente[20];
	double saldoCliente = 0.0, transferencia;
	int encontrado = 0, confirmacao, escolha = 0;
	char codigoTransacao[20];
	char nomeArquivo[30];
	char dataHora[30];

	char chavePix[50], cpfDestinatario[20], nomeDestinatario[50], numeroContaDestinatario[20];

	time_t agora;
	struct tm *infoTempo;
	time(&agora);
	infoTempo = localtime(&agora);
	strftime(dataHora, 30, "%d/%m/%Y %H:%M:%S", infoTempo);

	cabTransf();

	if (recursivo == 0) {
		do {
			corTexto(11);
			printf("Informe seu CPF: ");
			corTexto(14);
			scanf("%s", cpf);
			fflush(stdin);
			sprintf(nomeArquivo, "%s.txt", cpf);
			FILE *arquivo = fopen(nomeArquivo, "r");
			if (arquivo == NULL) {
				corTexto(12);
				printf("Erro: CPF não localizado no nosso banco. Corrija e tente novamente!\n");
				corTexto(11);
			} else {
				fclose(arquivo);
				encontrado = 1;
			}
		} while (!encontrado);
	}
	encontrado = 0;

	sprintf(nomeArquivo, "%s.txt", cpf);
	FILE *arquivo = fopen(nomeArquivo, "r+");
	if (arquivo == NULL) {
		corTexto(12);
		printf("Erro: Não foi possível acessar o arquivo do cliente. Verifique o CPF.\n");
		corTexto(11);
		return;
	}

	while (fgets(linha, sizeof(linha), arquivo)) {
		if (strstr(linha, "Nome completo          : ")) {
			sscanf(linha, "Nome completo          : %[^\n]", nomeCliente);
		} else if (strstr(linha, "Saldo                  : ")) {
			sscanf(linha, "Saldo                  : R$ %lf", &saldoCliente);
		} else if (strstr(linha, "Senha                  : ")) {
			sscanf(linha, "Senha                  : %s", senhaArquivo);
		} else if (strstr(linha, "Número da Conta        : ")) {
			sscanf(linha, "Número da Conta        : %s", numeroContaRemetente);
		} else if (strstr(linha, "Senha de Transação     : ")) {
			sscanf(linha, "Senha de Transação     : %s", senhaTransacao);
		}
	}
	fclose(arquivo);

	if (recursivo == 0) {
		do {
			corTexto(11);
			printf("Informe sua senha: ");
			corTexto(14);
			scanf("%s", senha);
			fflush(stdin);

			if (strcmp(senha, senhaArquivo) != 0) {
				corTexto(12);
				printf("Erro: Senha incorreta. Tente novamente.\n");
				corTexto(11);
			} else {
				encontrado = 1;
			}
		} while (!encontrado);
	}

	corTexto(10);
	printf("\nCarregando suas informações, aguarde");
	for (int i = 0; i < 6; i++) {
		printf(".");
		fflush(stdout);
		Sleep(1000);
	}
	system("cls");
	cabTransf();
	corTexto(9);
	printf("\n--------------------------------------------\n");
	printf(" Olá, %s!\n", nomeCliente);
	printf(" Número da Conta: %s\n", numeroContaRemetente);
	printf("--------------------------------------------\n");
	corTexto(11);
	printf("\n>> Seu saldo atual é: ");
	corTexto(14);
	printf("R$ %.2lf\n\n", saldoCliente);
	corTexto(11);

	encontrado = 0;
	
	FILE *arquivoContas;
	do {
		printf("Informe a chave PIX do destinatário: ");
		corTexto(14);
		scanf("%s", chavePix);
		fflush(stdin);
		corTexto(11);

		arquivoContas = fopen("contas.txt", "r");
		if (arquivoContas == NULL) {
			corTexto(12);
			printf("Erro ao abrir o arquivo de contas. Verifique o caminho e tente novamente.\n");
			corTexto(11);
			return;
		}
		while (fgets(linha, sizeof(linha), arquivoContas)) {
			if (strstr(linha, "Pix                    : ")) {
				char pixTemp[50];
				sscanf(linha, "Pix                    : %s", pixTemp);
				if (strcmp(chavePix, pixTemp) == 0) {
					encontrado = 1;
					while (fgets(linha, sizeof(linha), arquivoContas)) {
						if (strstr(linha, "Nome completo          : ")) {
							sscanf(linha, "Nome completo          : %[^\n]", nomeDestinatario);
						}  else if (strstr(linha, "CPF                    : ")) {
							sscanf(linha, "CPF                    : %s", cpfDestinatario);
						} else if (strstr(linha, "----------------------------------------")) {
							break;
						}
					}
					break;
				}
			}
		}
		
		fclose(arquivoContas);
		
		if (!encontrado) {
			corTexto(12);
			printf("Chave PIX não encontrada. Tente novamente.\n");
			corTexto(11);
		}
	} while (!encontrado);

	printf("\nConfirme as informações do destinatário:\n");
	corTexto(11);
	printf("Nome: ");
	corTexto(14);
	printf("%s\n\n", nomeDestinatario);
	corTexto(11);
	printf("Deseja confirmar a transferência? \n[1] - Sim \n[2] - Não (corrigir Chave PIX)\nR: ");
	scanf("%d", &confirmacao);
	fflush(stdin);
	
	while (confirmacao != 1) {
		printf("Informe novamente a chave PIX do destinatário: ");
		scanf("%s", chavePix);
		fflush(stdin);

		encontrado = 0;
		arquivoContas = fopen("contas.txt", "r");
		if (arquivoContas == NULL) {
			corTexto(12);
			printf("Erro ao abrir o arquivo de contas. Verifique o caminho e tente novamente.\n");
			corTexto(11);
			return;
		}

		while (fgets(linha, sizeof(linha), arquivoContas)) {
			if (strstr(linha, "Pix                    : ")) {
				char pixTemp[50];
				sscanf(linha, "Pix                    : %s", pixTemp);
				if (strcmp(chavePix, pixTemp) == 0) {
					encontrado = 1;

					while (fgets(linha, sizeof(linha), arquivoContas)) {
						if (strstr(linha, "Nome completo          : ")) {
							sscanf(linha, "Nome completo          : %[^\n]", nomeDestinatario);
						} else if (strstr(linha, "CPF                    : ")) {
							sscanf(linha, "CPF                    : %s", cpfDestinatario);
						} else if (strstr(linha, "----------------------------------------")) {
							break;
						}
					}
					break;
				}
			}
		}
		fclose(arquivoContas);

		if (!encontrado) {
			corTexto(12);
			printf("Chave PIX não encontrada. Tente novamente.\n");
			corTexto(11);
		}

		printf("\nConfirme as informações do destinatário:\n");
		corTexto(11);
		printf("Nome: ");
		corTexto(14);
		printf("%s\n\n", nomeDestinatario);
		corTexto(11);
		printf("Deseja confirmar a transferência? \n[1] - Sim \n[2] - Não (corrigir Chave PIX)\nR: ");
		scanf("%d", &confirmacao);
		fflush(stdin);
	}

	do {
		printf("Digite o valor a ser transferido: R$ ");
		corTexto(14);
		if (scanf("%lf", &transferencia) != 1 || transferencia <= 0) {
			while (getchar() != '\n');
			corTexto(12);
			printf("Por favor, insira um valor numérico válido maior que 0!\n");
			corTexto(11);
		} else {
			if (transferencia > saldoCliente) {
				corTexto(12);
				printf("Saldo insuficiente para a transferência!\n");
			} else {
				break;
			}
		}
	} while (1);
	fflush(stdin);

	encontrado = 0;
	char senhaTransacaoInput[10];
	do {
		corTexto(11);
		printf("Para finalizar, confirme sua senha de 4 dígitos: ");
		corTexto(14);
		scanf("%s", senhaTransacaoInput);
		fflush(stdin);
		if (strcmp(senhaTransacaoInput, senhaTransacao) != 0) {
			corTexto(12);
			printf("Erro: Senha de transação incorreta. Tente novamente.\n");
			corTexto(11);
		} else {
			encontrado = 1;
		}
	} while (!encontrado);

	saldoCliente -= transferencia;
	arquivo = fopen(nomeArquivo, "r");
	FILE *tempArquivo = fopen("temp_cliente.txt", "w");
	while (fgets(linha, sizeof(linha), arquivo)) {
		if (strstr(linha, "Saldo                  : ")) {
			fprintf(tempArquivo, "Saldo                  : R$ %.2lf\n", saldoCliente);
		} else if (strstr(linha, "Saldo Atual: R$ ")) {
			fprintf(tempArquivo, "Saldo Atual: R$ %.2lf\n", saldoCliente);
		} else {
			fprintf(tempArquivo, "%s", linha);
		}
	}
	fclose(arquivo);
	fclose(tempArquivo);
	remove(nomeArquivo);
	rename("temp_cliente.txt", nomeArquivo);

	char nomeArquivoDest[30];
	sprintf(nomeArquivoDest, "%s.txt", cpfDestinatario);
	FILE *arquivoDest = fopen(nomeArquivoDest, "r+");
	if (arquivoDest == NULL) {
		corTexto(12);
		printf("Erro: Não foi possível acessar o arquivo do destinatário.\n");
		return;
	}
	double saldoDest = 0.0;
	char linhaDest[256];
	while (fgets(linhaDest, sizeof(linhaDest), arquivoDest)) {
		if (strstr(linhaDest, "Saldo                  : ")) {
			sscanf(linhaDest, "Saldo                  : R$ %lf", &saldoDest);
		}
	}
	saldoDest += transferencia;
	rewind(arquivoDest);
	FILE *tempArquivoDest = fopen("temp_destinatario.txt", "w");
	while (fgets(linhaDest, sizeof(linhaDest), arquivoDest)) {
		if (strstr(linhaDest, "Saldo                  : ")) {
			fprintf(tempArquivoDest, "Saldo                  : R$ %.2lf\n", saldoDest);
		} else if (strstr(linhaDest, "Saldo Atual: R$ ")) {
			fprintf(tempArquivoDest, "Saldo Atual: R$ %.2lf\n", saldoDest);
		} else {
			fprintf(tempArquivoDest, "%s", linhaDest);
		}
	}
	fclose(arquivoDest);
	fclose(tempArquivoDest);
	remove(nomeArquivoDest);
	rename("temp_destinatario.txt", nomeArquivoDest);

	gerarCodigoTransacao(codigoTransacao);
	arquivo = fopen(nomeArquivo, "a");
	if (arquivo) {

		fprintf(arquivo, "%s   | %s | %+7.2f    | %-18s | %s\n",
		        dataHora, "Transferência PIX", -transferencia, nomeDestinatario, codigoTransacao);
		fclose(arquivo);
	}
	arquivoDest = fopen(nomeArquivoDest, "a");
	if (arquivoDest) {

		fprintf(arquivoDest, "%s   | %s   | %+7.2f    | %-18s | %s\n",
		        dataHora, "Recebimento PIX", transferencia, nomeCliente, codigoTransacao);

		fclose(arquivoDest);
	}

	corTexto(10);
	printf("\nTransferência de R$ %.2lf realizada com sucesso!\n", transferencia);
	printf("Novo saldo disponível: R$ %.2lf\n", saldoCliente);
	corTexto(11);

	int opcaoComprovante;
	corTexto(11);
	printf("\nDeseja baixar o comprovante de transferência?\n[1] - Sim\n[2] - Não\nOpção: ");
	scanf("%d", &opcaoComprovante);
	fflush(stdin);

	if (opcaoComprovante == 1) {
		char nomeComprovante[100];
		snprintf(nomeComprovante, sizeof(nomeComprovante),
		         "Transferencia_%s_para_%s_%s.txt", nomeCliente, nomeDestinatario,codigoTransacao);

		FILE *comprovante = fopen(nomeComprovante, "w");
		fprintf(comprovante, "--------------------------------------------------\n");
		fprintf(comprovante, "|            COMPROVANTE DE TRANSFERÊNCIA         |\n");
		fprintf(comprovante, "--------------------------------------------------\n");
		fprintf(comprovante, "Valor: R$ %.2f\n", transferencia);
		fprintf(comprovante, "Tipo de Transferência: Pix\n");
		fprintf(comprovante, "Data e Hora: %s\n", dataHora);
		fprintf(comprovante, "Código da Transação: %s\n", codigoTransacao);
		fprintf(comprovante, "--------------------------------------------------\n");
		fprintf(comprovante, "|                INFORMAÇÕES DO DESTINATÁRIO      |\n");
		fprintf(comprovante, "--------------------------------------------------\n");
		fprintf(comprovante, "Nome: %s\n", nomeDestinatario);
		fprintf(comprovante, "Instituição: ProtectBank\n");
		fprintf(comprovante, "Agência: 0001\n");
		fprintf(comprovante, "--------------------------------------------------\n");
		fprintf(comprovante, "|                  INFORMAÇÕES DO REMETENTE       |\n");
		fprintf(comprovante, "--------------------------------------------------\n");
		fprintf(comprovante, "Nome: %s\n", nomeCliente);
		fprintf(comprovante, "Número da Conta: %s\n", numeroContaRemetente);
		fprintf(comprovante, "Instituição: ProtectBank\n");
		fprintf(comprovante, "Agência: 0001\n");
		fprintf(comprovante, "--------------------------------------------------\n");
		fprintf(comprovante, "|             Transação realizada com sucesso!    |\n");
		fprintf(comprovante, "--------------------------------------------------\n");
		fclose(comprovante);
		corTexto(10);
		printf("\nComprovante gerado com sucesso!\n");
		corTexto(11);
	}

	do {
		printf("\nO que você deseja fazer?\n");
		printf("[1] - Realizar uma transferência\n");
		printf("[2] - Realizar um depósito\n");
		printf("[3] - Realizar um saque\n");
		printf("[4] - Consultar meu extrato e saldo\n");
		printf("[5] - Sair\n");
		printf("Escolha: ");
		scanf("%d", &escolha);
		fflush(stdin);
		switch (escolha) {
			case 1:
				system("cls");
				realizarTransferencia(cpf, senha, 1);
				return;
			case 2:
				system("cls");
				realizarDeposito(cpf, senha, 1);
				return;
			case 3:
				system("cls");
				realizarSaque(cpf, senha, 1);
				return;
			case 4:
				system("cls");
				extrato(cpf, senha, 1);
				return;
			case 5:
				printf("Finalizando atendimento...\n");
				exit(0);
			default:
				printf("Opção inválida. Tente novamente.\n");
		}
	} while (1);
}

void extrato(char *cpf, char *senha, int recursivo) {

	/*
	Exibe o extrato bancário de um cliente com base no CPF e senha fornecidos.
	Busca no arquivo do cliente a seção "EXTRATO BANCÁRIO" e imprime todas as linhas seguintes
	relacionadas ao extrato de forma detalhada, oferecendo opção de gerar um comprovante.
	*/

	char caminhoArquivo[100];
	FILE *arquivoCliente;
	char linha[256];
	int encontrouExtrato = 0;
	char nomeCliente[100];
	char contaCliente[100];
	char extratoCompleto[5000] = "";

	if (recursivo == 0) {
		system("cls");
		corTexto(11);
		printf("-----------------------------------------------------\n");
		printf("    Bem-vindo ao Sistema de Extrato Bancário\n");
		printf("              ProtecBank                               \n");
		printf("-----------------------------------------------------\n");

		while (1) {
			corTexto(9);
			printf("Digite seu CPF (sem pontos e traços): ");
			corTexto(14);
			scanf("%11s", cpf);
			fflush(stdin);
			corTexto(9);

			printf("Digite sua senha: ");
			corTexto(14);
			scanf("%s", senha);
			fflush(stdin);
			corTexto(9);

			snprintf(caminhoArquivo, sizeof(caminhoArquivo), "%s.txt", cpf);
			arquivoCliente = fopen(caminhoArquivo, "r");
			if (arquivoCliente) break;

			corTexto(12);
			printf("\nErro: CPF não encontrado ou arquivo inacessível. Tente novamente.\n");
			corTexto(15);
		}
	} else {
		snprintf(caminhoArquivo, sizeof(caminhoArquivo), "%s.txt", cpf);
		arquivoCliente = fopen(caminhoArquivo, "r");
		if (!arquivoCliente) {
			corTexto(12);
			printf("\nErro ao abrir o arquivo do cliente.\n");
			corTexto(15);
			return;
		}
	}

	while (fgets(linha, sizeof(linha), arquivoCliente)) {
		if (strncmp(linha, "Nome completo          :", 24) == 0) {
			sscanf(linha, "Nome completo          : %[^\n]", nomeCliente);
		}else if (strstr(linha, "Número da Conta        : ")) {
			sscanf(linha, "Número da Conta        : %s", contaCliente);
		}
		
		if (strncmp(linha, "=============================================", 45) == 0) {
			if (fgets(linha, sizeof(linha), arquivoCliente) &&
				strncmp(linha, "        EXTRATO BANCÁRIO", 24) == 0) {
				
				system("cls");
				corTexto(9);
				printf("\nOlá, %s! Aqui está seu extrato bancário:\n\n", nomeCliente);
				corTexto(11);
				printf("=============================================\n");
				corTexto(11);
				printf("%s", linha);
				strcat(extratoCompleto, linha);
				
				fgets(linha, sizeof(linha), arquivoCliente);
				printf("%s", linha);
				strcat(extratoCompleto, linha);

				while (fgets(linha, sizeof(linha), arquivoCliente)) {
					printf("%s", linha);
					strcat(extratoCompleto, linha);
				}
				encontrouExtrato = 1;
				break;
			}
		}
	}
	fclose(arquivoCliente);

	if (!encontrouExtrato) {
		corTexto(12);
		printf("Erro: Seção de extrato bancário não encontrada.\n");
		corTexto(15);
		return;
	}

	int opcaoComprovante;
	printf("\n\nDeseja gerar um comprovante do extrato?\n[1] Sim\n[2] Não\nR: ");
	scanf("%d", &opcaoComprovante);
	fflush(stdin);

	if (opcaoComprovante == 1) {
		time_t agora = time(NULL);
		struct tm *dataHora = localtime(&agora);
		char dataFormatada[100];
		strftime(dataFormatada, sizeof(dataFormatada), "%d/%m/%Y às %H:%M:%S", dataHora);

		char nomeArquivo[100];
		snprintf(nomeArquivo, sizeof(nomeArquivo), "extrato_%s_conta_%s.txt", nomeCliente, contaCliente);
		FILE *comprovante = fopen(nomeArquivo, "w");

		if (comprovante) {
			fprintf(comprovante, "============================================================\n");
			fprintf(comprovante, "               Comprovante de Extrato Bancário              \n");
			fprintf(comprovante, "                        ProtecBank                          \n");
			fprintf(comprovante, "============================================================\n");
			fprintf(comprovante, "Cliente           : %s\n", nomeCliente);
			fprintf(comprovante, "Número da Conta   : %s\n", contaCliente);
			fprintf(comprovante, "Data da Solicitação: %s\n", dataFormatada);
			fprintf(comprovante, "------------------------------------------------------------\n");
			fprintf(comprovante, "%s", extratoCompleto);
			fprintf(comprovante, "------------------------------------------------------------\n");
			fprintf(comprovante, "            Obrigado por utilizar o ProtecBank!            \n");
			fprintf(comprovante, "============================================================\n");

			fclose(comprovante);
			corTexto(10);
			printf("\nComprovante gerado e baixado com sucesso!");
			corTexto(11);
		} else {
			corTexto(12);
			printf("\nErro ao criar o arquivo do extrato.\n");
		}
	}

	int esq;
	do {
		printf("\n\nO que você deseja fazer? \n[1] - Finalizar atendimento\n[2] - Realizar um deposito\n[3] - Realizar um saque\n[4] - Realizar uma transferência\nR: ");
		scanf("%d", &esq);
		fflush(stdin);

		switch (esq) {
			case 1:
				corTexto(11);
				printf("\nVocê escolheu finalizar o atendimento. Até logo!\n");
				break;
			case 2:
				corTexto(14);
				printf("\nVocê escolheu realizar um depósito.\n");
				realizarDeposito(cpf, senha, 1);
				break;
			case 3:
				corTexto(14);
				printf("\nVocê escolheu realizar um saque.\n");
				realizarSaque(cpf, senha, 1);
				break;
			case 4:
				corTexto(14);
				system("cls");
				printf("\nVocê escolheu realizar uma transferência.\n");
				realizarTransferencia(cpf, senha, 1);
				break;
			default:
				corTexto(12);
				printf("\nOpção inválida. Tente novamente.\n");
				corTexto(11);
				break;
		}
	} while (esq < 1 || esq > 4);
}

void atualizarEndereco(char *cpf) {
	
	/*

	Responsável por permitir ao cliente atualizar seu endereço cadastrado no sistema bancário. 

	É chamada dentro da função principal de atualização de cadastro, quando o usuário opta 
	por alterar o endereço.

	*/
	
	char linha[256], senhaArquivo[20];
	char nomeCliente[50], endereco[100], numero[10], bairro[50], cidade[50], estado[3], cep[10];
	int encontrado = 0;
	int escolha;
	char nomeArquivo[30];


	sprintf(nomeArquivo, "%s.txt", cpf);
	FILE *arquivo = fopen(nomeArquivo, "r");
	if (arquivo == NULL) {
		corTexto(12);
		printf("Erro: CPF não localizado no nosso banco. Corrija e tente novamente!\n");
		corTexto(11);
		return;
	} else {
		fclose(arquivo);
		encontrado = 1;
	}

	arquivo = fopen(nomeArquivo, "r+");
	if (arquivo == NULL) {
		corTexto(12);
		printf("Erro: Não foi possível acessar o arquivo do cliente. Verifique o CPF.\n");
		corTexto(11);
		return;
	}

	while (fgets(linha, sizeof(linha), arquivo)) {
		if (strstr(linha, "Nome completo          : ")) {
			sscanf(linha, "Nome completo          : %[^\n]", nomeCliente);
		} else if (strstr(linha, "Endereço               : ")) {
			sscanf(linha, "Endereço               : %[^\n]", endereco);
		} else if (strstr(linha, "Número                 : ")) {
			sscanf(linha, "Número                 : %[^\n]", numero);
		} else if (strstr(linha, "Bairro                 : ")) {
			sscanf(linha, "Bairro                 : %[^\n]", bairro);
		} else if (strstr(linha, "Cidade                 : ")) {
			sscanf(linha, "Cidade                 : %[^\n]", cidade);
		} else if (strstr(linha, "Estado                 : ")) {
			sscanf(linha, "Estado                 : %[^\n]", estado);
		} else if (strstr(linha, "CEP                    : ")) {
			sscanf(linha, "CEP                    : %[^\n]", cep);
		}
	}

	corTexto(10);
	printf("\nCarregando suas informações, aguarde");
	for (int i = 0; i < 6; i++) {
		printf(".");
		fflush(stdout);
		Sleep(1000);
	}
	system("cls");

	corTexto(9);
	printf("\n--------------------------------------------\n");
	printf(" Olá, %s!\n", nomeCliente);
	printf("--------------------------------------------\n");
	corTexto(11);
	printf("\n>> Seu endereço atual é:\n");
	corTexto(14);
	printf("Endereço: %s\n", endereco);
	printf("Número: %s\n", numero);
	printf("Bairro: %s\n", bairro);
	printf("Cidade: %s\n", cidade);
	printf("Estado: %s\n", estado);
	printf("CEP: %s\n\n", cep);
	corTexto(11);

	corTexto(11);
	printf("- Informe o novo endereço -\n");
	printf("Informe o nome da rua: ");
	corTexto(14);
	fflush(stdin);
	fgets(endereco, sizeof(endereco), stdin);
	endereco[strcspn(endereco, "\n")] = 0;

	corTexto(11);
	printf("Informe o novo número: ");
	corTexto(14);
	fgets(numero, sizeof(numero), stdin);
	numero[strcspn(numero, "\n")] = 0;

	corTexto(11);
	printf("Informe o novo bairro: ");
	corTexto(14);
	fgets(bairro, sizeof(bairro), stdin);
	bairro[strcspn(bairro, "\n")] = 0;

	corTexto(11);
	printf("Informe a nova cidade: ");
	corTexto(14);
	fgets(cidade, sizeof(cidade), stdin);
	cidade[strcspn(cidade, "\n")] = 0;

	corTexto(11);
	printf("Informe o novo estado (UF): ");
	corTexto(14);
	fgets(estado, sizeof(estado), stdin);
	estado[strcspn(estado, "\n")] = 0;
	fflush(stdin);

	corTexto(11);
	printf("Informe o novo CEP: ");
	corTexto(14);
	fgets(cep, sizeof(cep), stdin);
	cep[strcspn(cep, "\n")] = 0;

	do {
		corTexto(11);
		printf("\nVocê está alterando os dados para:\n\n");;
		corTexto(11); printf("Endereço: "); corTexto(14); printf("%s\n", endereco);
		corTexto(11); printf("Número: "); corTexto(14); printf("%s\n", numero);
		corTexto(11); printf("Bairro: "); corTexto(14); printf("%s\n", bairro);
		corTexto(11); printf("Cidade: "); corTexto(14); printf("%s\n", cidade);
		corTexto(11); printf("Estado: "); corTexto(14); printf("%s\n", estado);
		corTexto(11); printf("CEP: "); corTexto(14); printf("%s\n", cep);
		corTexto(11);
		printf("\nConfirma a alteração? \n[1] - Sim\n[2] - Não, corrigir\nR: ");
		scanf("%d", &escolha);
		fflush(stdin);

		if (escolha == 1) {
			break;
		} else if (escolha == 2) {
			return;
		} else {
			corTexto(12);
			printf("\nOpção inválida! Tente novamente.\n");
			corTexto(11);
		}
	} while (escolha != 1);

	rewind(arquivo);
	FILE *tempArquivo = fopen("temp_cliente.txt", "w");
	while (fgets(linha, sizeof(linha), arquivo)) {
		if (strstr(linha, "Endereço               : ")) {
			fprintf(tempArquivo, "Endereço               : %s\n", endereco);
		} else if (strstr(linha, "Número                 : ")) {
			fprintf(tempArquivo, "Número                 : %s\n", numero);
		} else if (strstr(linha, "Bairro                 : ")) {
			fprintf(tempArquivo, "Bairro                 : %s\n", bairro);
		} else if (strstr(linha, "Cidade                 : ")) {
			fprintf(tempArquivo, "Cidade                 : %s\n", cidade);
		} else if (strstr(linha, "Estado                 : ")) {
			fprintf(tempArquivo, "Estado                 : %s\n", estado);
		} else if (strstr(linha, "CEP                    : ")) {
			fprintf(tempArquivo, "CEP                    : %s\n", cep);
		} else {
			fprintf(tempArquivo, "%s", linha);
		}
	}
	fclose(arquivo);
	fclose(tempArquivo);

	remove(nomeArquivo);
	rename("temp_cliente.txt", nomeArquivo);

	corTexto(10);
	printf("\nEndereço atualizado com sucesso!\n");

}

void atualizarPix(const char *cpf) {
	
	/*
		Responsável por atualizar a chave Pix de um cliente no sistema bancário. 
	
	*/
	
	char senha[20], linha[256];
	char senhaArquivo[20], escolha[10];
	char novoDado[100], pixAntigo[100];
	int encontrado = 0;
	int esq;
	char nomeArquivo[20];
	sprintf(nomeArquivo, "%s.txt", cpf);
	FILE *arquivo = fopen(nomeArquivo, "r+");

	if (arquivo == NULL) {
		corTexto(12);
		printf("Erro: Não foi possível abrir o arquivo do cliente. Verifique o CPF.\n");
		corTexto(7);
		return;
	}

	while (fgets(linha, sizeof(linha), arquivo)) {
		if (strstr(linha, "Senha                  : ")) {
			sscanf(linha, "Senha                  : %s", senhaArquivo);
			encontrado = 1;
			break;
		}
	}

	if (!encontrado) {
		corTexto(12);
		printf("Erro: Senha não encontrada no arquivo do cliente.\n");
		corTexto(7);
		fclose(arquivo);
		return;
	}

	rewind(arquivo);
	encontrado = 0;
	while (fgets(linha, sizeof(linha), arquivo)) {
		if (strstr(linha, "Pix                    : ")) {
			sscanf(linha, "Pix                    : %s", pixAntigo);
			encontrado = 1;
			break;
		}
	}

	if (!encontrado) {
		corTexto(12);
		printf("Erro: Pix não encontrado no arquivo do cliente.\n");
		corTexto(7);
		fclose(arquivo);
		return;
	}

	do {
		printf("Informe sua nova chave PIX: \n");
		corTexto(14);
		scanf("%s", novoDado);
		corTexto(11);

		FILE *contas = fopen("contas.txt", "r");
		if (contas == NULL) {
			corTexto(12);
			printf("Erro: Não foi possível abrir o arquivo de contas.\n");
			corTexto(7);
			fclose(arquivo);
			return;
		}

		FILE *tempContas = fopen("contas_temp.txt", "w");
		if (!tempContas) {
			corTexto(12);
			printf("Erro: Não foi possível criar o arquivo temporário de contas.\n");
			corTexto(7);
			fclose(arquivo);
			fclose(contas);
			return;
		}

		encontrado = 0;
		while (fgets(linha, sizeof(linha), contas)) {
			if (strstr(linha, "Pix                    : ") && strstr(linha, novoDado)) {
				corTexto(12);
				printf("Erro: Esta chave PIX já está cadastrada em outra conta!\n");
				corTexto(11);
				encontrado = 1;
				break;
			}
			fprintf(tempContas, "%s", linha);
		}

		fclose(contas);
		fclose(tempContas);

		if (!encontrado) {
			remove("contas.txt");
			rename("contas_temp.txt", "contas.txt");
			break;
		} else {
			printf("\nDeseja tentar uma nova chave Pix?\n[1] - Sim\n[2] - Voltar ao menu de atualização\nEscolha: ");
			scanf("%d", &esq);
			fflush(stdin);

			if (esq == 2) {
				fclose(arquivo);
				return;
			}
		}
	} while (1);

	corTexto(10);
	printf("Seu Pix atualizado com sucesso!!!!\n");
	corTexto(11);

	rewind(arquivo);
	FILE *tempCliente = fopen("temp_cliente.txt", "w");
	if (!tempCliente) {
		corTexto(12);
		printf("Erro: Não foi possível criar o arquivo temporário do cliente.\n");
		corTexto(7);
		fclose(arquivo);
		return;
	}

	while (fgets(linha, sizeof(linha), arquivo)) {
		if (strstr(linha, "Pix                    : ")) {
			fprintf(tempCliente, "Pix                    : %s\n", novoDado);
		} else {
			fprintf(tempCliente, "%s", linha);
		}
	}

	fclose(arquivo);
	fclose(tempCliente);

	remove(nomeArquivo);
	rename("temp_cliente.txt", nomeArquivo);

	do {
		corTexto(11);
		printf("\nDeseja atualizar algum outro dado?\n[1] - Sim\n[2] - Não, sair!\nR: ");
		scanf("%d", &esq);
		fflush(stdin);

		if (esq == 1) {
			atualizarCadastro();
		} else if (esq == 2) {
			break;
		} else {
			printf("\nopção inválida!!!\n");
		}
	} while (esq != 1 || esq != 2);

}

void atualizarCadastro() {
	
	/*
     	Permite ao cliente atualizar seus dados cadastrais no sistema bancário.
	*/
	
	char cpf[12], senha[20], linha[256];
	char senhaArquivo[20], escolha[10];
	char novoDado[100];
	int encontrado = 0;
	char senhaConfirmada[20];
	int esqq;

	while (1) {
		corTexto(9);
		printf("\n=========================================\n");
		printf("           ATUALIZAÇÃO CADASTRAL         \n");
		printf("=========================================\n");
		corTexto(11);

		printf("Informe o CPF do cliente: ");
		corTexto(14);
		scanf("%s", cpf);
		fflush(stdin);
		corTexto(11);

		char nomeArquivo[20];
		sprintf(nomeArquivo, "%s.txt", cpf);
		FILE *arquivo = fopen(nomeArquivo, "r+");
		if (arquivo == NULL) {
			corTexto(12);
			printf("Erro: CPF não encontrado. Por favor, tente novamente.\n");
			corTexto(7);
			continue;
		}

		while (fgets(linha, sizeof(linha), arquivo)) {
			if (strstr(linha, "Senha                  : ")) {
				sscanf(linha, "Senha                  : %s", senhaArquivo);
				encontrado = 1;
				break;
			}
		}
		if (!encontrado) {
			corTexto(12);
			printf("Erro: Senha não encontrada no arquivo do cliente.\n");
			corTexto(11);
			fclose(arquivo);
			return;
		}

		printf("Informe a senha do cliente: ");
		corTexto(14);
		scanf("%s", senha);
		corTexto(11);
		if (strcmp(senha, senhaArquivo) != 0) {
			corTexto(12);
			printf("Erro: Senha incorreta. Tente novamente.\n");
			corTexto(7);
			fclose(arquivo);
			continue;
		}
		fclose(arquivo);
		break;
	}

	int opcao;
	do {
		system("cls");
		corTexto(9);
		printf("-----------------------------------------------------\n");
		corTexto(14);
		printf("    Bem-vindo ao Sistema de Extrato Bancário\n");
		printf("              ProtecBank                               \n");
		corTexto(9);
		printf("-----------------------------------------------------\n");
		printf("\n=========================================\n");
		printf("        ATUALIZAÇÃO CADASTRAL          \n");
		printf("=========================================\n\n");
		corTexto(11);
		printf("[1] - Atualizar Pix\n");
		printf("[2] - Atualizar Endereço\n");
		printf("[3] - Atualizar Telefone\n");
		printf("[4] - Atualizar Email\n");
		printf("[5] - Atualizar Senha\n");
		printf("[6] - Atualizar Senha de Transação\n");
		printf("[7] - Atualizar Pergunta/Resposta Secreta\n");
		printf("[0] - Voltar\n");
		printf("Escolha: ");
		scanf("%d", &opcao);
		fflush(stdin);

		if (opcao < 0 || opcao > 7) {
			corTexto(12);
			printf("Opção inválida. Por favor, tente novamente.\n");
			corTexto(7);
			continue;
		}

		if (opcao == 0) {
			corTexto(10);
			printf("Retornando ao menu principal...\n");
			corTexto(7);
			break;
		}

		if (opcao == 1) {
			atualizarPix(cpf);
			break;
		}

		corTexto(14);
		if (opcao == 2) {
			atualizarEndereco(cpf);

		} else if (opcao == 3) {
			while(1) {
				corTexto(11);
				printf("\nInforme seu novo número de telefone: ");
				corTexto(14);
				scanf(" %[^\n]", novoDado);
				corTexto(11);
				int valido = 1;

				if (strlen(novoDado) != 11) {
					corTexto(12);
					printf("O telefone deve conter exatamente 11 dígitos!!!\n");
					corTexto(11);
					valido = 0;
				} else {

					for (int i = 0; i < 11; i++) {
						if (!isdigit(novoDado[i])) {
							corTexto(12);
							printf("O telefone deve conter apenas números!!!\n");
							corTexto(11);
							valido = 0;
							break;
						}
					}
				}

				if (valido) break;
			}

			corTexto(2)	;
			printf("\nSeu telefone foi atualizado som sucesso!!!\n\n");
			corTexto(11);


		} else if (opcao == 4) {
			while (1) {
				printf("Informe seu novo email: ");
				scanf(" %[^\n]", novoDado);

				if (!validarEmail(novoDado)) {
					corTexto(12);
					printf("O e-mail é inválido. Verifique as regras e tente novamente.\n");
					corTexto(11);
					continue;
				}
				break;
			}
			corTexto(2)	;
			printf("\nSeu e-mail foi atualizado som sucesso!!!\n\n");
			corTexto(11);


		} else if (opcao == 5) {
			corTexto(11);
			RedefinirSenha(cpf);
		} else if (opcao == 6) {

			do {
				corTexto(11);
				printf("Informe sua nova senha de transação (4 dígitos): ");
				scanf("%s", novoDado);

				if (strlen(novoDado) != 4) {
					corTexto(12);
					printf("Formato incorreto, corrija!!!\n");
					corTexto(11);
				}

			} while (strlen(novoDado) != 4);

			printf("Senha atualiza com sucesso!\n");

		} else if (opcao == 7) {
			printf("Informe a nova pergunta e resposta secreta: ");
		}

		corTexto(11);

		char nomeArquivo[20];
		sprintf(nomeArquivo, "%s.txt", cpf);
		FILE *arquivo = fopen(nomeArquivo, "r");
		if (!arquivo) {
			corTexto(12);
			printf("Erro: Não foi possível abrir o arquivo do cliente.\n");
			corTexto(7);
			return;
		}

		FILE *temp = fopen("temp.txt", "w");
		if (!temp) {
			corTexto(12);
			printf("Erro: Não foi possível criar o arquivo temporário.\n");
			corTexto(7);
			fclose(arquivo);
			return;
		}

		while (fgets(linha, sizeof(linha), arquivo)) {
					if(
				    (opcao == 3 && strstr(linha, "Telefone               : ")) ||
			        (opcao == 4 && strstr(linha, "E-mail                 : ")) ||
			        (opcao == 6 && strstr(linha, "Senha de Transação     : ")) ||
			        (opcao == 7 && strstr(linha, "Pergunta Secreta       : "))) {
				fprintf(temp, "%.*s%s\n", (int)(strchr(linha, ':') - linha + 2), linha, novoDado);
			} else {
				fprintf(temp, "%s", linha);
			}
		}

		fclose(arquivo);
		fclose(temp);

		remove(nomeArquivo);
		rename("temp.txt", nomeArquivo);
		break;

	} while (1);

	do {

		printf("\nO que você deseja fazer?\n");
		printf("[1] - Realizar um depósito\n");
		printf("[2] - Realizar um saque\n");
		printf("[3] - Consultar meu extrato e meu saldo\n");
		printf("[4] - Realizar uma transferência\n");
		printf("[5] - Sair\n");
		printf("Escolha: ");
		scanf("%d", &esqq);
		fflush(stdin);

		switch (esqq) {
			case 1:
				system("cls");
				realizarDeposito(cpf, senha, 1);
				return;
			case 2:
				realizarSaque(cpf, senha, 1);
				return;
			case 3:
				extrato(cpf, senha, 1);
				return;

			case 4:
				realizarTransferencia(cpf, senha, 1);
				return;
			case 5:
				printf("Finalizando atendimento, aguarde");
				exibirPontos();
				exit(0);


			default:
				printf("Opção inválida. Tente novamente.\n");
		}
	} while (esqq < 1 || esqq > 3);

}

int chavePixJaCadastrada(const char *arquivo, const char *chavePix) {
	
	// Função para verificar se a chave Pix informada já está cadastrada em outro cliente no sistema.

	FILE *fp = fopen(arquivo, "r");
	if (fp == NULL) {
		printf("Erro ao abrir o arquivo de contas!\n");
		return 0; 
	}

	char linha[256];
	while (fgets(linha, sizeof(linha), fp)) {
		if (strstr(linha, "Pix                    :") != NULL) {
			char pixExistente[100];
			sscanf(linha, "Pix                    : %99[^\n]", pixExistente);

			if (strcmp(pixExistente, chavePix) == 0) {
				fclose(fp);
				return 1; 
			}
		}
	}

	fclose(fp);
	return 0; 
}








