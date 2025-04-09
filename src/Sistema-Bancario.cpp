
/*
 * Projeto: Sistema Banc�rio
 * Autor: Jo�o Paulo
 * Data: Dezembro de 2024
 * Disciplina: L�gica de Programa��o
 *
 * Descri��o:
 * Sistema de atendimento banc�rio desenvolvido em linguagem C como projeto final da disciplina de L�gica de Programa��o.
 * O sistema simula o funcionamento de um banco, permitindo a cria��o e gerenciamento de contas banc�rias,
 * com funcionalidades como:
 * 
 * - Gera��o de senhas para atendimento (normal e priorit�rio)
 * - Cadastro e autentica��o de clientes
 * - Atualiza��o de dados cadastrais (Pix, endere�o, e-mail, telefone, senha, etc.)
 * - Opera��es banc�rias: dep�sitos, saques, transfer�ncias, consultas de saldo e extrato
 * - Emiss�o de comprovantes
 * - Armazenamento e atualiza��o de dados persistente em arquivos .txt por CPF
 
 * O projeto tamb�m inclui uma interface de navega��o com menu interativo e cores no terminal,
 * al�m de valida��es completas de dados (e-mail, CPF, senha, chave Pix, entre outros).
 *
 * Objetivo:
 * Aplicar os conhecimentos de l�gica de programa��o, estruturas de dados, manipula��o de arquivos
 * e organiza��o de c�digo modular para resolver problemas reais de forma pr�tica.
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
				printf("\nOp��o inv�lida. Tente novamente.\n");
				corTexto(11);
		}
	} while (op != 0);

	return 0;
}

void menu() {
	corTexto(9);
	printf("\n==============================\n");
	corTexto(14);
	printf("     Sistema Banc�rio         \n");
	printf("        ProtecBank         \n");
	printf("     Seja bem-vindo(a)        \n");
	corTexto(9);
	printf("==============================\n");
	corTexto(11);
	printf("\n=== Sistema de Atendimento do Banco ===\n\n");
	corTexto(14);
	printf("1. Pegar uma senha\n");
	printf("2. Atender pr�ximo cliente\n");
	printf("3. Exibir senhas\n");
	printf("4. Excluir uma senha\n");
	printf("0. Sair\n");
	corTexto(11);
	printf("\nEscolha uma op��o: ");
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
		printf("=== Tipos de Servi�o Dispon�veis ===       \n\n");

		corTexto(14);
		printf("  [1]  %s\n", "Abrir Conta");
		printf("  [2]  %s\n", "Encerrar Conta");
		printf("  [3]  %s\n", "Consultar Saldo");
		printf("  [4]  %s\n", "Realizar Dep�sito");
		printf("  [5]  %s\n", "Realizar Saque");
		printf("  [6]  %s\n", "Transferir Valores");
		printf("  [7]  %s\n", "Extrato");
		printf("  [8]  %s\n", "Atualizac�es cadastrais");
		corTexto(11);
		printf("\n====================================\n");
		printf("Escolha o servi�o que deseja: ");
		corTexto(11);
		scanf("%d", &op);
		getchar();

		if(op <0 || op >8) {
			system("cls");
			corTexto(12);
			printf("\n	Op��o inv�lida!!!");
			corTexto(11);
		}

	} while(op <0 || op >8);
}

void cab() {

	printf("\n           PROTECBANNK - ATENDIMENTO\n");

}

void entrarNaFila(FilaBanco *fila) {

	// Adiciona um cliente � fila com base no tipo de servi�o e prioridade, gerando senha e comprovante.

	char opcao;

	if (fila->atras == MAX) {
		printf("A fila est� cheia. Tente novamente mais tarde.\n");
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
			strcpy(cliente.tipoServico, "Realizar Dep�sito");
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
			strcpy(cliente.tipoServico, "Atualizac�es cadastrais");
			cliente.mesas[0] = 14;
			cliente.mesas[1] = 15;
			break;

		default:
			return;
	}

	printf("\nComo voc� deseja ser chamado?: ");
	corTexto(14);
	fgets(cliente.nome, sizeof(cliente.nome), stdin);
	cliente.nome[strcspn(cliente.nome, "\n")] = '\0';
	corTexto(11);

	do {
		printf("\nO atendimento � priorit�rio? (S/N): ");
		corTexto(14);
		scanf(" %c", &cliente.prioridade);
		fflush(stdin);
		corTexto(11);

		if (cliente.prioridade != 's' && cliente.prioridade != 'S' && cliente.prioridade != 'N' && cliente.prioridade != 'n') {
			corTexto(12);
			printf("\nOp��o inv�lida!!!\n\n");
			corTexto(11);
		}

	} while(cliente.prioridade != 's' && cliente.prioridade != 'S' && cliente.prioridade != 'N' && cliente.prioridade != 'n');


	printf("\nServi�o para ");
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
	fprintf(arquivo, "|  Ag�ncia: 0001                   |\n");
	fprintf(arquivo, "|  Mesa de Atendimento: %2d e %2d    |\n", mesa1, mesa2);
	fprintf(arquivo, "|  Cliente: %-23s|\n", nomeCliente);
	fprintf(arquivo, "|  Servi�o: %-23s|\n", tipoServico);
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
	printf("|  Ag�ncia: 0001                   |\n");
	printf("|  Mesa de Atendimento: %2d e %2d    |\n", mesa1, mesa2);
	printf("|  Cliente: %-23s|\n", nomeCliente);
	printf("|  Servi�o: %-23s|\n", tipoServico);
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

	// Exibe todos os clientes na fila com nome, servi�o, senha e guich�s designados.

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
		printf("    A FILA EST� VAZIA!\n");
		printf("  N�o h� senhas para exibir.\n");
		printf("\n");
		corTexto(11);
		printf("===================================\n");
		return;
	}

	corTexto(11);
	printf("\n%-10s%-20s%-20s%-10s%-10s\n", "Posi��o", "Nome", "Tipo de Servi�o", "Senha", "Guich�");
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

	Realiza o atendimento do pr�ximo cliente na fila do banco, com prioridade para clientes preferenciais.
	Executa o servi�o banc�rio solicitado, exibe informa��es do atendimento e remove o cliente da fila
	ap�s o atendimento ser conclu�do.

	*/

	ContaBancaria conta;
	if (fila->frente == fila->atras) {
		system("cls");
		corTexto(11);
		printf("=============================\n");
		corTexto(12);
		printf("    A fila est� vazia!!!\n");
		printf("N�o h� cliente para atender\n");
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
		printf("N�o h� clientes na fila.\n");
		printf("===============================================\n");
		return;
	}

	Cliente *cliente = &fila->clientes[indiceAtendimento];

	corTexto(14);
	printf("===============================================\n");
	printf("Atendendo cliente: %s\n", cliente->nome);
	printf("Tipo de servi�o: %s\n", cliente->tipoServico);
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
	} else if (strcmp(cliente->tipoServico, "Realizar Dep�sito") == 0) {
		realizarDeposito(cliente->cpf, cliente->senha, 0);
	} else if (strcmp(cliente->tipoServico, "Realizar Saque") == 0) {
		realizarSaque(cliente->cpf, cliente->senha, 0);
	} else if (strcmp(cliente->tipoServico, "Transferir Valores") == 0) {
		realizarTransferencia(cliente->cpf, cliente->senha, 0);
	} else if (strcmp(cliente->tipoServico, "Extrato") == 0) {
		extrato(cliente->cpf, cliente->senha, 0);
	} else if (strcmp(cliente->tipoServico, "Atualizac�es cadastrais") == 0) {
		atualizarCadastro();
	} else {
		printf("===============================================\n");
		printf("Servi�o desconhecido: %s\n", cliente->tipoServico);
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

	// Gera um c�digo de 6 d�gitos para verifica��o na redefini��o de senha do cliente.

	return rand() % 900000 + 100000;
}

void obterHorarioAtual(char *horario, size_t tamanho) {
	time_t agora = time(NULL);
	struct tm *tm_info = localtime(&agora);
	strftime(horario, tamanho, "%d/%m/%Y �s %H:%M:%S", tm_info);
}

void RedefinirSenha(char *cpf) {

	/*
	Permite a redefini��o da senha do cliente utilizando um dos m�todos de recupera��o:
	telefone, e-mail ou pergunta secreta. Ap�s valida��o da identidade, o usu�rio define
	uma nova senha que � atualizada no arquivo da conta.
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
				printf("\n[ERRO] Tentativas excedidas! Opera��o abortada.\n");
				return;
			}
		}
	} while (1);

	do {
		printf("\nComo deseja recuperar sua conta?\n");
		printf("[1] - Telefone\n");
		printf("[2] - E-mail\n");
		printf("[3] - Pergunta Secreta\n");
		printf("Escolha uma op��o: ");
		scanf("%d", &escolha);
		getchar();

		if (escolha >= 1 && escolha <= 3) break;
		printf("\n[ERRO] Op��o inv�lida! Tente novamente.\n");
	} while (1);

	if (escolha == 3) {

		if (!encontrouPergunta) {
			printf("\n[ERRO] Pergunta secreta n�o encontrada no arquivo. Opera��o abortada.\n");
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
					printf("\n[ERRO] Tentativas excedidas! Opera��o abortada.\n");
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
			printf("\n[ERRO] N�o foi poss�vel criar o arquivo tempor�rio.\n");
			fclose(arquivo);
			return;
		}

		while (fgets(linha, sizeof(linha), arquivo)) {
			if (escolha == 1 && strstr(linha, "CAIXA DE ENTRADA DO TELEFONE")) {
				fprintf(temp, "%s", linha);
				fprintf(temp, "\nC�digo de Recupera��o: %d\n", codigoGerado);
				fprintf(temp, "Recebido em: %s\n", horario);
				fprintf(temp, "---------------------------------------------\n\n");
				encontrouSessao = 1;
			} else if (escolha == 2 && strstr(linha, "CAIXA DE ENTRADA DO E-MAIL")) {
				fprintf(temp, "%s", linha);
				fprintf(temp, "C�digo de Recupera��o: %d\n", codigoGerado);
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
			printf("\n[ERRO] N�o foi poss�vel encontrar a se��o para escrever o c�digo.\n");
			remove("TempArquivo.txt");
			return;
		}

		remove(nomeArquivo);
		rename("TempArquivo.txt", nomeArquivo);

		printf("\n[INFO] C�digo de recupera��o enviado para a se��o '");
		corTexto(14); 
		printf("%s", escolha == 1 ? "CAIXA DE ENTRADA DO TELEFONE" : "CAIXA DE ENTRADA DO E-MAIL");
		corTexto(11);  
		printf("' no arquivo da conta.\n");

		tentativas = 3;
		do {
			printf("\nDigite o c�digo de recupera��o enviado: ");
			corTexto(14); 
			scanf("%d", &codigoInformado);
			getchar();
			corTexto(11); 
			if (codigoInformado == codigoGerado) {
				break;
			} else {
				corTexto(12); 
				printf("\n[ERRO] C�digo incorreto! Tente novamente.\n");
				tentativas--;
				corTexto(11); 
				if (tentativas == 0) {
						corTexto(12); 
					printf("\n[ERRO] Tentativas excedidas! Opera��o abortada.\n");
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
		printf(" - Pelo menos 1 letra mai�scula\n");
		printf(" - Pelo menos 1 letra min�scula\n");
		printf(" - Pelo menos 1 n�mero\n");
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
			printf("\n[ERRO] A senha n�o atende aos requisitos. Tente novamente.\n");
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
			printf("\n[ERRO] As senhas n�o coincidem. Tente novamente.\n");
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
	Validar a data de nascimento informada pelo cliente, verificando seu formato, consist�ncia
	e calculando a idade com base na data atual do sistema. Garante que o cliente tenha pelo
	menos 18 anos para poder abrir uma conta banc�ria.
	*/

	time_t t = time(NULL);
	struct tm tmAtual = *localtime(&t);


	int dia, mes, ano;
	if (sscanf(dataNascimento, "%d/%d/%d", &dia, &mes, &ano) != 3) {
		corTexto(12);
		printf("[ERRO] Data de nascimento inv�lida. Use o formato DD/MM/AAAA.\n");
		corTexto(11);
		return -1;

	}

	if (ano < 1900 || ano > tmAtual.tm_year + 1900 || mes < 1 || mes > 12 || dia < 1 || dia > 31) {
		corTexto(12);
		printf("[ERRO] Data de nascimento inv�lida. Verifique os valores inseridos.\n");
		corTexto(11);
		return -1;

	}


	int diasNoMes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if (ano % 4 == 0 && (ano % 100 != 0 || ano % 400 == 0)) {
		diasNoMes[1] = 29;
	}
	if (dia > diasNoMes[mes - 1]) {
		corTexto(12);
		printf("[ERRO] Dia inv�lido para o m�s especificado.\n");
		corTexto(11);
		return -1;

	}

	int idade = tmAtual.tm_year + 1900 - ano;

	if (mes > tmAtual.tm_mon + 1 || (mes == tmAtual.tm_mon + 1 && dia > tmAtual.tm_mday)) {
		idade--;
	}

	if (idade < 18) {
		corTexto(12);
		printf("[ERRO] Voc� precisa ter pelo menos 18 anos para criar uma conta.\n");
		corTexto(11);
		int opcao;
		printf("Deseja corrigir a data de nascimento \n[1] - Sim \n[2] - N�o, finalizar \nR: ");
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
		printf("[ERRO] Idade inv�lida. Verifique os dados inseridos.\n");
		corTexto(11);
		return -1;

	}

	return idade;
}

void aceitarTermos() {

	/*
	Exibir os termos de servi�o do banco para que o cliente possa tomar ci�ncia
	das condi��es antes de continuar com o uso do sistema.
	*/

	int esq;
	corTexto(9);
	printf("\n============================================");
	corTexto(14);
	printf("\n             Termos de Servi�o ");
	printf("\n                 ProtecBank                     ");
	corTexto(9);
	printf("\n============================================\n\n");
	corTexto(11);
	printf("1. O banco n�o se responsabiliza por senhas compartilhadas.\n");
	printf("2. Os dados fornecidos ser�o usados exclusivamente para fins banc�rios.\n");
	printf("3. Todas as transa��es est�o sujeitas � verifica��o de seguran�a.\n");
	printf("4. O cliente � respons�vel por manter os dados atualizados.\n");
	printf("5. As taxas e tarifas est�o sujeitas a altera��es com aviso pr�vio.\n");
	printf("6. O uso de sua conta deve estar de acordo com as leis vigentes.\n");
	printf("7. O banco pode suspender ou encerrar contas que apresentem atividades suspeitas.\n");
	printf("8. O cliente � respons�vel por reportar qualquer atividade n�o autorizada.\n");
	printf("9. Os limites de transa��o podem variar conforme o perfil do cliente.\n");
	printf("10. O banco oferece suporte ao cliente em hor�rio comercial.\n");
	printf("====================================================\n\n");

}

void gerarChaveAleatoria(char *chave, size_t tamanho) {

	/*
	Gerar uma chave Pix aleat�ria no formato "XXX-XXX-XXX", utilizada como identificador
	�nico para transa��es no sistema banc�rio.
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
	Verifica se uma chave Pix aleat�ria fornecida est� no formato correto utilizado
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
	Verifica se o endere�o de e-mail fornecido est� em um formato v�lido
	conforme os crit�rios estabelecidos pelo sistema.
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
	Verifica se um n�mero de conta banc�ria informado j� est� cadastrado no sistema para n�o criar aleat�ria.
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
	Gera um n�mero de conta banc�ria �nico e semi-aleat�rio para um novo cliente.
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
	printf("           CRIA��O DE CONTA BANC�RIA          \n");
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
	  Verifica se o CEP informado possui um formato v�lido.
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
	Respons�vel por cadastrar um novo cliente no sistema banc�rio.
	Garante todas as valida��es necess�rias para um cadastro correto e seguro.
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

	snprintf(dataCriacao, sizeof(dataCriacao), "%02d/%02d/%04d �s %02d:%02d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min);
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

		printf("\nPara podermos come�ar a cria��o da sua conta voc� precisa aceitar os termos e condi��es");
		printf("\n[1] - Aceito");
		printf("\n[2] - Visualizar os termos e condic�es.\nR: ");
		scanf("%d", &esq);
		fflush(stdin);

		if(esq == 1) {
			break;
		} else if( esq == 2) {
			system("cls");
			aceitarTermos();
			printf("\nVoc� aceita os Termos e condi��es do Servi�o? \n[1] - Sim \n[2] - N�o \nR: ");
			scanf("%d", &esq);
			fflush(stdin);

			if(esq== 1) {
				break;
			}
			if(esq==2) {
				printf("Voc� deve aceitar os Termos de Servi�o para criar uma conta, at� a pr�xima!!!");
				exit(0);
			}
		} else {
			corTexto(12);
			printf("\nOp��o inv�lida!!!\n");
			corTexto(11);
		}
	} while (esq != 1 || esq != 2);

	system("cls");
	menucriarconta();
	corTexto(14);
	printf("\nOl�, seja bem-vindo(a), ficamos felizes por ter voc� aqui conosco ^^) Vamos come�ar.\n");
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
		printf("O primeiro nome deve ter pelo menos 2 letras v�lidas e conter apenas letras e espa�os. Tente novamente.\n");
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
		printf("O sobrenome deve ter pelo menos 2 letras v�lidas e conter apenas letras e espa�os. Tente novamente.\n");
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
		printf("\nDigite seu CPF (apenas n�meros): ");
		corTexto(14);
		fgets(conta->cpf, sizeof(conta->cpf), stdin);
		conta->cpf[strcspn(conta->cpf, "\n")] = '\0';

		snprintf(nomeArquivo, sizeof(nomeArquivo), "%s.txt", conta->cpf);
		arquivo = fopen(nomeArquivo, "r");

		int valido = 1;
		if (arquivo != NULL) {
			fclose(arquivo);
			corTexto(12);
			printf("J� existe uma conta com este CPF. Use outro CPF.\n");
			corTexto(11);
			valido = 0;
		} else if (strlen(conta->cpf) != 11) {
			corTexto(12);
			printf("[ERRO] O CPF deve conter exatamente 11 n�meros.\n");
			corTexto(11);
			valido = 0;
		} else {
			for (int i = 0; i < 11; i++) {
				if (!isdigit(conta->cpf[i])) {
					printf("[ERRO] O CPF deve conter apenas n�meros.\n");
					valido = 0;
					break;
				}
			}
		}

		if (valido) break;
	}

	corTexto(11);

	printf("\nInforme o seu endere�o:\n");

	printf("Rua: ");
	corTexto(14);
	fgets(conta->rua, sizeof(conta->rua), stdin);
	conta->rua[strcspn(conta->rua, "\n")] = '\0';
	corTexto(11);


	printf("N�mero: ");
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
			printf("Sigla inv�lida!!!\n");
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
			printf("CEP inv�lido! Por favor, insira um CEP no formato 'NNNNN-NNN' ou 'NNNNNNNN'.\n");
			corTexto(11);
		}
	}

	int opcao;

	do {

		printf("\nEscolha o tipo de conta que deseja abrir:\n");
		printf("1. Conta Corrente\n");
		printf("2. Conta Poupan�a\n");
		printf("3. Conta Sal�rio\n");
		printf("4. Conta Especial\n");
		printf("Digite o n�mero da op��o desejada: ");
		scanf("%d", &opcao);
		fflush(stdin);

		switch(opcao) {
			case 1:
				strcpy(conta->tipoConta, "Conta Corrente");
				break;
			case 2:
				strcpy(conta->tipoConta, "Conta Poupan�a");
				break;
			case 3:
				strcpy(conta->tipoConta, "Conta Sal�rio");
				break;
			case 4:
				strcpy(conta->tipoConta, "Conta Especial");
				break;
			default:
				corTexto(12);
				printf("Op��o inv�lida,\n");
				corTexto(11);
				break;
		}
	} while(opcao <1 || opcao >4);

	while (1) {
		printf("\nEscolha o tipo de chave Pix:\n");
		printf("[1] Telefone\n[2] CPF\n[3] E-mail\n[4] Chave Aleat�ria\n[5] N�o desejo cadastar agora.\nR: ");
		int escolhaPix;
		scanf("%d", &escolhaPix);
		fflush(stdin);

		if (escolhaPix == 1) {

			printf("Digite seu n�mero de telefone (apenas n�meros, at� 11 d�gitos): ");
			corTexto(14);
			fgets(conta->pix, sizeof(conta->pix), stdin);
			conta->pix[strcspn(conta->pix, "\n")] = '\0';
			corTexto(11);
			int valido = 1;


			if (chavePixJaCadastrada("contas.txt", conta->pix)) {
				corTexto(12);
				printf("O telefone informado j� est� cadastrado como chave Pix. Tente novamente.\n");
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
				printf("[ERRO] O telefone deve conter apenas n�meros e ter 10 ou 11 d�gitos. Tente novamente.\n");
				corTexto(11);
			} else {

				printf("\nChave Pix do tipo telefone cadastrada com sucesso!\n");
				break;
			}

		} else if (escolhaPix == 2) {

			if (chavePixJaCadastrada("contas.txt", conta->cpf)) {
				corTexto(12);
				printf("O CPF informado j� est� cadastrado como chave Pix. Tente novamente.\n");
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
				printf("O e-mail � inv�lido. Verifique as regras e tente novamente.\n");
				corTexto(11);
				continue;
			}

			if (chavePixJaCadastrada("contas.txt", conta->pix)) {
				corTexto(12);
				printf("O e-mail informado j� est� cadastrado como chave Pix. Tente novamente.\n");
				corTexto(11);
				continue;
			}

			break;

		} else if (escolhaPix == 4) {
			gerarChaveAleatoria(conta->pix, sizeof(conta->pix));

			if (chavePixJaCadastrada("contas.txt", conta->pix)) {
				printf("Houve um conflito com a chave aleat�ria gerada. Gerando novamente...\n");
				continue;
			}
			printf("Sua chave Pix aleat�ria foi criada com sucesso = ");
			corTexto(14);
			printf("%s",conta->pix);
			corTexto(11);
			break;

		} else if (escolhaPix == 5) {
			break;
		} else {
			corTexto(12);
			printf("Op��o inv�lida!!!.");
			corTexto(11);
		}

	}

	while (1) {
		printf("\n\nInforme seu n�mero de telefone com DDD (11 d�gitos): ");
		corTexto(14);
		fgets(conta->telefone, sizeof(conta->telefone), stdin);
		conta->telefone[strcspn(conta->telefone, "\n")] = '\0';
		corTexto(11);

		int valido = 1;

		if (strlen(conta->telefone) != 11) {
			corTexto(12);
			printf("O telefone deve conter exatamente 11 d�gitos!!!\n");
			corTexto(11);
			valido = 0;
		} else {
			for (int i = 0; i < 11; i++) {
				if (!isdigit(conta->telefone[i])) {
					corTexto(12);
					printf("O telefone deve conter apenas n�meros!!!\n");
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
			printf("O e-mail � inv�lido. Verifique as regras e tente novamente.\n");
			corTexto(11);
			continue;
		}
		break;
	}

	while (1) {
		printf("\nDigite uma senha para acesso � conta (6 a 8 caracteres): ");
		printf("\nA senha deve conter:\n");
		printf(" - Pelo menos 1 letra mai�scula\n");
		printf(" - Pelo menos 1 letra min�scula\n");
		printf(" - Pelo menos 1 n�mero\n");
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
			printf("[ERRO] A senha n�o atende aos requisitos. Tente novamente.\n");
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
			printf("As senhas n�o coincidem. Tente novamente.\n");
			corTexto(11);
		} else {
			break;
		}
	}

	corTexto(11);
	while (1) {
		corTexto(11);
		printf("\nDigite uma senha para transa��es (4 d�gitos): ");
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
			printf("A senha deve conter exatamente 4 n�meros. Tente novamente.\n");
			corTexto(11);
			continue;
		}
		corTexto(11);
		printf("\nConfirme a senha de transa��o: ");
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
			printf("[ERRO] As senhas de transa��o n�o coincidem. Tente novamente.\n");
			corTexto(11);
		} else {
			break;
		}
	}
	corTexto(11);

	printf("\nDigite uma pergunta secreta para recupera��o de senha: ");
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
	fprintf(arquivo, "      DETALHES DA SUA CONTA BANC�RIA         \n");
	fprintf(arquivo, "=============================================\n\n");
	fprintf(arquivo, "Pix                    : %s\n", conta->pix);
	fprintf(arquivo, "CPF                    : %s\n", conta->cpf);
	fprintf(arquivo, "Nome completo          : %s\n", conta->nomeCompleto);
	fprintf(arquivo, "Data de nascimento     : %s\n", conta->dataNascimento);
	fprintf(arquivo, "N�mero da Conta        : %s\n", numeroConta);
	fprintf(arquivo, "Endere�o               : %s\n", conta->rua);
	fprintf(arquivo, "N�mero                 : %s\n", conta->numero);
	fprintf(arquivo, "Bairro                 : %s\n", conta->bairro);
	fprintf(arquivo, "Cidade                 : %s\n", conta->cidade);
	fprintf(arquivo, "Estado                 : %s\n", conta->estado);
	fprintf(arquivo, "CEP                    : %s\n", conta->cep);
	fprintf(arquivo, "Tipo de conta          : %s\n", conta->tipoConta);
	fprintf(arquivo, "Telefone               : %s\n", conta->telefone);
	fprintf(arquivo, "E-mail                 : %s\n", conta->email);
	fprintf(arquivo, "Senha                  : %s\n", conta->senha);
	fprintf(arquivo, "Senha de Transa��o     : %s\n", conta->senhaTransacao);
	fprintf(arquivo, "Pergunta Secreta       : %s\n", conta->perguntaSecreta);
	fprintf(arquivo, "Resposta Secreta       : %s\n", conta->respostaSecreta);
	fprintf(arquivo, "Saldo                  : R$ %.2f\n", conta->saldo);
	fprintf(arquivo, "Conta criada em        : %s\n\n", dataCriacao);
	fprintf(arquivo, "\n=============================================\n");
	fprintf(arquivo, "         CAIXA DE ENTRADA DO TELEFONE  \n\n\n");
	fprintf(arquivo, "\n=============================================\n");
	fprintf(arquivo, "         CAIXA DE ENTRADA DO E-MAIL  \n\n");

	fprintf(arquivo, "\n\n\n=============================================\n");
	fprintf(arquivo, "        EXTRATO BANC�RIO   \n");
	fprintf(arquivo, "=============================================\n");
	fprintf(arquivo, "Saldo Atual: R$ %.2f\n\n",conta->saldo );
	fprintf(arquivo, "Data e Hora           | Tipo              | Valor      | Destinat�rio       | C�digo de Transa��o\n");
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
	fprintf(arquivo, "N�mero da Conta        : %s\n", numeroConta);
	fprintf(arquivo, "Conta criada em        : %s\n", dataCriacao);
	fprintf(arquivo, "----------------------------------------\n\n");

	fclose(arquivo);

	system("cls");
	menucriarconta();

	corTexto(9);
	printf("\n****************************************************\n");
	printf("*                                                   *\n");
	corTexto(14);
	printf("* Ol�, %s! Estamos finalizando seu cadastro.*\n", conta->nomeCompleto);
	corTexto(9);
	printf("*                                                   *\n");
	printf("****************************************************\n\n");

	corTexto(10);
	printf("Aguarde um momento enquanto conclu�mos o processo");
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
	printf("N�mero da Conta        : %s\n", numeroConta);
	printf("Endere�o               : %s\n", conta->rua);
	printf("N�mero                 : %s\n", conta->numero);
	printf("Bairro                 : %s\n", conta->bairro);
	printf("Cidade                 : %s\n", conta->cidade);
	printf("Estado                 : %s\n", conta->estado);
	printf("CEP                    : %s\n", conta->cep);
	printf("Tipo de conta          : %s\n", conta->tipoConta);
	printf("Pix                    : %s\n", conta->pix);
	printf("Telefone               : %s\n", conta->telefone);
	printf("E-mail                 : %s\n", conta->email);
	printf("Senha                  : %s\n", conta->senha);
	printf("Senha de Transa��o     : %s\n", conta->senhaTransacao);
	printf("Pergunta Secreta       : %s\n", conta->perguntaSecreta);
	printf("Resposta Secreta       : %s\n", conta->respostaSecreta);
	printf("Saldo dispon�vel       : R$ %.2f\n", conta->saldo);
	printf("Conta criada em        : %s\n", dataCriacao);

}

void mascararCPF(char *cpf, char *cpfFormatado) {
	snprintf(cpfFormatado, 15, "***.%.3s.***-%c%c", cpf + 3, cpf[9], cpf[10]);
}

void RemoverDoBancoDeDados(char *cpf, const char *pix, const char *numeroConta, const char *nome) {

	/*
	Localiza e remove um cliente do arquivo de contas com base no Pix informado.
	Ao encontrar o cliente, registra os dados da exclus�o (CPF, nome, conta e data)
	em um novo arquivo tempor�rio. Depois, substitui o arquivo original pelo tempor�rio
	sem os dados da conta exclu�da. Exibe uma mensagem se o cliente n�o for encontrado.
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
		printf("Erro ao criar o arquivo tempor�rio.\n");
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
			fprintf(arquivoTemp, "N�mero da conta        : %s\n\n", numeroConta);
			fprintf(arquivoTemp, "Data da exclus�o       : %s\n", dataHoraAtual);
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
	Permite que um cliente exclua sua conta banc�ria do sistema com seguran�a,
	garantindo valida��o por CPF e confirma��o por senha onde sua conta � deletada do banco.
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

		printf("\n> Insira seu CPF (apenas n�meros): ");
		corTexto(14);
		fgets(conta->cpf, sizeof(conta->cpf), stdin);
		conta->cpf[strcspn(conta->cpf, "\n")] = 0;
		corTexto(11);

		if (strlen(conta->cpf) != 11) {
			corTexto(12);
			printf("\nO CPF deve conter exatamente 11 d�gitos. Tente novamente.\n");
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
				printf("2. N�o, cancelar exclus�o\n");
				printf("Escolha: ");
				scanf("%d", &tentarNovamente);
				fflush(stdin);

				if (tentarNovamente != 1 && tentarNovamente != 2) {
					corTexto(12);
					printf("\nOp��o inv�lida. Por favor, escolha 1 ou 2.\n");
					corTexto(11);
				}
			} while (tentarNovamente != 1 && tentarNovamente != 2);

			if (tentarNovamente == 2) {
				corTexto(12);
				printf("\n[OPERA��O CANCELADA] Nenhuma altera��o foi feita na conta.\n");
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
		} else if (strncmp(linha, "N�mero da Conta        :", 23) == 0) {
			sscanf(linha, "N�mero da Conta        : %[^\n]", numeroConta);
			encontrouNumeroConta = 1;
		}

		if (encontrouNome && encontrouSenha && encontrouPix && encontrouNumeroConta) {
			break;
		}
	}
	fclose(arquivo);

	if (!encontrouNome || !encontrouSenha || !encontrouPix || !encontrouNumeroConta) {
		corTexto(12);
		printf("\nDados corrompidos ou incompletos. Opera��o abortada.\n");
		corTexto(11);
		return;
	}

	do {
		system("cls");
		cabDeletar();
		corTexto(11);
		printf("\nOl�, ");
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
				printf("\nA senha deve ter no m�nimo 6 caracteres. Tente novamente.\n");
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
						printf("\nO que voc� deseja fazer?");
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
							printf("\nObrigado e at� a pr�xima!!!");
						} else {
							printf("Op��o inv�lida!!!");
						}

					case 3:
						exit(1);

					default:
						corTexto(12);
						printf("Op��o inv�lida!!!");
						corTexto(11);
				}

				int op;
				printf("\nO que voc� deseja fazer?");
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
					printf("\nObrigado e at� a pr�xima!!!");
				} else {
					corTexto(12);
					printf("Op��o inv�lida!!!");
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
				printf("  Conta exclu�da com sucesso! Sentiremos sua falta.\n");
				printf("  Muito obrigado por confiar no ProtecBank, %s!\n", nomeUsuario);
				printf("******************************************************\n\n");
				corTexto(11);
			} else {
				printf("\n\n");
				corTexto(12);
				printf("******************************************************\n");
				printf("  N�o foi poss�vel excluir sua conta no momento.\n");
				printf("  Por favor, tente novamente mais tarde.\n");
				printf("******************************************************\n\n");
				corTexto(11);
			}
			return;

		} else {
			corTexto(12);
			printf("\nA senha informada est� incorreta!\n");
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
						printf("\nO que voc� deseja fazer?");
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
							printf("\nObrigado e at� a pr�xima!!!");
						} else {
							printf("Op��o inv�lida!!!");
						}

					case 3:
						exit(1);

					default:
						corTexto(12);
						printf("Op��o inv�lida!!!");
						corTexto(11);
				}

			} while(op < 1 || op >2 );
		}
	} while (1);
}

void excluirSenha(FilaBanco *fila) {

	/*
	Remove um cliente espec�fico da fila do banco ProtecBank com base em sua senha,
	al�m de excluir o arquivo de comprovante associado ao atendimento
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
			printf("\nA fila est� vazia. N�o h� clientes para excluir.\n");
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
		printf("\n%-10s%-20s%-20s%-10s%-10s\n", "Posi��o", "Nome", "Tipo de Servi�o", "Senha", "Guich�");
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
		printf("\n\nDigite a senha do cliente a ser exclu�do: ");
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
					printf("\n\nA senha de %s foi exclu�da com sucesso.\n", fila->clientes[i].nome);
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
					printf("\nDeseja excluir outra senha?\n[1] - N�o, voltar ao menu\n[2] - Sim\nEscolha: ");
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
						printf("\nOp��o inv�lida. Digite 1 para n�o ou 2 para sim.\n");
						corTexto(11);
					}
				}

			}
		}

		if (!encontrado) {
			system("cls");
			corTexto(12);
			printf("\nA senha '%s' n�o foi encontrada. Tente novamente.\n", senha);
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
	Consulta o saldo da conta banc�ria do cliente ap�s validar CPF e senha.
	Utiliza um par�metro de controle (recursivo) para evitar a repeti��o desnecess�ria da autentica��o
	quando a fun��o � chamada novamente por outras opera��es como dep�sito, saque, extrato ou transfer�ncia.
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
				printf("Erro: CPF n�o localizado no nosso banco. Corrija e tente novamente!\n");
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
		printf("Erro: N�o foi poss�vel acessar o arquivo do cliente. Verifique o CPF.\n");
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
	printf(" Ol�, %s!\n", nomeCliente);
	printf("--------------------------------------------\n");
	corTexto(11);
	printf("\n>> Seu saldo atual �: ");
	corTexto(14);
	printf("R$ %.2f\n\n", saldoAtualDouble);
	corTexto(11);
	printf("--------------------------------------------\n");

	int escolha;
	do {
		printf("\nO que voc� deseja fazer?\n");
		printf("[1] - Realizar um dep�sito\n");
		printf("[2] - Realizar um saque\n");
		printf("[3] - Consultar meu extrato\n");
		printf("[4] - Realizar uma transfer�ncia\n");
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
				printf("Op��o inv�lida. Tente novamente.\n");
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
	Realiza um dep�sito na conta do cliente ap�s autentica��o e confirma��o do valor.
	Atualiza o saldo no arquivo e registra a transa��o no extrato no arquivo .txt
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
				printf("Erro: CPF n�o localizado no nosso banco. Corrija e tente novamente!\n");
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
		printf("Erro: N�o foi poss�vel acessar o arquivo do cliente. Verifique o CPF.\n");
		corTexto(11);
		return;
	}

	while (fgets(linha, sizeof(linha), arquivo)) {
    if (strstr(linha, "Nome completo          : ")) {
        sscanf(linha, "Nome completo          : %[^\n]", nomeCliente);
    } else if (strstr(linha, "N�mero da Conta        : ")) {
        sscanf(linha, "N�mero da Conta        : %[^\n]", numeroConta);
    } else if (strstr(linha, "Saldo                  : ")) {
        sscanf(linha, "Saldo                  : R$ %s", saldo);
    } else if (strstr(linha, "Saldo Atual: R$ ")) {
        sscanf(linha, "Saldo Atual: R$ %s", saldoAtual);
    } else if (strstr(linha, "Senha de Transa��o     : ")) {
        sscanf(linha, "Senha de Transa��o     : %s", senhaTransacao);
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
	printf("\nCarregando suas informa��es, aguarde");
	for (int i = 0; i < 6; i++) {
		printf(".");
		fflush(stdout);
		Sleep(1000);
	}
	system("cls");
	CabDep();
	corTexto(9);
	printf("\n--------------------------------------------\n");
	printf(" Ol�, %s!\n", nomeCliente);
	printf("--------------------------------------------\n");
	corTexto(11);
	printf("\n>> Seu saldo atual �: ");
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
				printf("Por favor, insira um valor num�rico v�lido maior que 0!!!.\n");
				corTexto(11);
			} else {
				break;
			}

		} while (1);

		do {
			corTexto(11);
			printf("\nVoc� est� depositando ");
			corTexto(14);
			printf("%.2lf, ",deposito);
			corTexto(11);
			printf("confirma o valor? \n[1] - Sim\n[2] - N�o, corrigir\nR: ");
			scanf("%d", &escolha);
			fflush(stdin);

			if(escolha == 1) {
				break;
			} else if(escolha ==2) {
				break;
			} else if(escolha != 1 || escolha != 2) {
				corTexto(12); 
				printf("\nOp��o inv�lid!!!\n");
				corTexto(11); 
			}
		} while(escolha != 1 || escolha != 2);
	} while(escolha != 1 || escolha != 2);

	encontrado = 0;

	do {
		corTexto(11);
		printf("Para finalizar confirme sua senha de 4 d�gitos: ");
		corTexto(14);
		scanf("%s", senhaTransacaoInput);
		fflush(stdin);
		corTexto(11);

		if (strcmp(senhaTransacaoInput, senhaTransacao) != 0) {
			corTexto(12);
			printf("Erro: Senha de transa��o incorreta. Tente novamente.\n");
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
	printf("\nDep�sito no valor de R$ %.2lf realizado com sucesso!\n", deposito);

	corTexto(11);
	printf("\nNovo saldo dispon�vel: ");
	corTexto(14);
	printf("R$ %.2f\n\n", saldoNovo);
	corTexto(11);
	
	gerarCodigoTransacao(codigoTransacao);
	
	fflush(stdin);
	int opcaoComprovante;
	corTexto(11);
	printf("\nDeseja baixar o comprovante de dep�sito?\n[1] - Sim\n[2] - N�o\nOp��o: ");
	scanf("%d", &opcaoComprovante);
	fflush(stdin);

	if (opcaoComprovante == 1) {
		char nomeComprovante[100];
		snprintf(nomeComprovante, sizeof(nomeComprovante),
		         "Deposito_%s_%s.txt", nomeCliente, codigoTransacao);

		FILE *comprovante = fopen(nomeComprovante, "w");
		fprintf(comprovante, "--------------------------------------------------\n");
		fprintf(comprovante, "|              COMPROVANTE DE DEP�SITO            |\n");
		fprintf(comprovante, "--------------------------------------------------\n");
		fprintf(comprovante, "Valor: R$ %.2f\n", deposito);
		fprintf(comprovante, "Tipo de Opera��o: Dep�sito\n");
		fprintf(comprovante, "Data e Hora: %s\n", dataHora);
		fprintf(comprovante, "C�digo da Transa��o: %s\n", codigoTransacao);
		fprintf(comprovante, "--------------------------------------------------\n");
		fprintf(comprovante, "|                INFORMA��ES DO CLIENTE           |\n");
		fprintf(comprovante, "--------------------------------------------------\n");
		fprintf(comprovante, "Nome: %s\n", nomeCliente);
		fprintf(comprovante, "Institui��o: ProtectBank\n");
		fprintf(comprovante, "Ag�ncia: 0001\n");
		fprintf(comprovante, "N�mero da Conta: %s\n", numeroConta);
		fprintf(comprovante, "--------------------------------------------------\n");
		fprintf(comprovante, "|             Dep�sito realizado com sucesso!     |\n");
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
		        dataHora, "Dep�sito", deposito, codigoTransacao);
		fclose(arquivoExtrato);

	}

	do {
		printf("\nO que voc� deseja fazer?\n");
		printf("[1] - Realizar um dep�sito\n");
		printf("[2] - Realizar um saque\n");
		printf("[3] - Consultar meu extrato e meu saldo\n");
		printf("[4] - Realizar uma transfer�ncia\n");
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
				printf("Op��o inv�lida. Tente novamente.\n");
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

	/* Fun��o respons�vel por realizar o saque do cliente. Valida CPF, senha e senha de transa��o,
	 atualiza o saldo no arquivo, registra o saque no extrato e oferece novas op��es de opera��o.
	 O par�metro 'recursivo' indica se a chamada foi feita a partir de outra fun��o (1) ou n�o (0) */
	
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
				printf("Erro: CPF n�o localizado no nosso banco. Corrija e tente novamente!\n");
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
		printf("Erro: N�o foi poss�vel acessar o arquivo do cliente. Verifique o CPF.\n");
		corTexto(11);
		return;
	}

while (fgets(linha, sizeof(linha), arquivo)) {
	if (strstr(linha, "Nome completo          : ")) {
		sscanf(linha, "Nome completo          : %[^\n]", nomeCliente);
	} else if (strstr(linha, "N�mero da Conta        : ")) {
		sscanf(linha, "N�mero da Conta        : %s", numeroConta);
	} else if (strstr(linha, "Saldo                  : ")) {
		sscanf(linha, "Saldo                  : R$ %s", saldo);
	} else if (strstr(linha, "Saldo Atual: R$ ")) {
		sscanf(linha, "Saldo Atual: R$ %s", saldoAtual);
	} else if (strstr(linha, "Senha de Transa��o     : ")) {
		sscanf(linha, "Senha de Transa��o     : %s", senhaTransacao);
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
	printf(">> Seu saldo atual �: ");
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
				printf("Por favor, insira um valor num�rico v�lido maior que 0!!!.\n");
				corTexto(11);
			} else if(saque > atof(saldo)) {
				corTexto(12);
				printf("Erro: Saldo insuficiente! Voc� possui R$ %.2f e tentou sacar R$ %.2f.\n", atof(saldo), saque);
				corTexto(11);
			}	else {
				break;
			}

		} while (1);

		corTexto(11);
		fflush(stdin);

		do {
			printf("\nVoc� est� sacando ");
			corTexto(14);
			printf("R$ %.2lf,",saque);
			corTexto(11);
			printf(" confirma o valor? \n[1] - Sim\n[2] - N�o, corrigir\nR: ");
			scanf("%d", &escolha);
			fflush(stdin);

			if(escolha == 1) {
				break;
			} else if(escolha ==2) {
				break;
			} else if(escolha != 1 || escolha != 2) {
				printf("\nOp��o inv�lid!!!\n");
			}
		} while(escolha != 1 || escolha != 2);
	} while(escolha != 1 || escolha != 2);

	encontrado = 0;

	do {
		printf("Para finalizar confirme sua senha de 4 d�gitos: ");
		scanf("%s", senhaTransacaoInput);
		fflush(stdin);

		if (strcmp(senhaTransacaoInput, senhaTransacao) != 0) {
			corTexto(12);
			printf("Erro: Senha de transa��o incorreta. Tente novamente.\n");
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

	printf("Novo saldo dispon�vel: ");
	corTexto(14);
	printf("R$ %.2f\n\n", saldoNovo);
	corTexto(11); 

	gerarCodigoTransacao(codigoTransacao);
	
	
	int opcaoComprovante;
	corTexto(11);
	printf("\nDeseja baixar o comprovante de saque?\n[1] - Sim\n[2] - N�o\nOp��o: ");
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
		fprintf(comprovante, "Tipo de Opera��o: Saque\n");
		fprintf(comprovante, "Data e Hora: %s\n", dataHora);
		fprintf(comprovante, "C�digo da Transa��o: %s\n", codigoTransacao);
		fprintf(comprovante, "--------------------------------------------------\n");
		fprintf(comprovante, "|               INFORMA��ES DO CLIENTE            |\n");
		fprintf(comprovante, "--------------------------------------------------\n");
		fprintf(comprovante, "Nome: %s\n", nomeCliente);
		fprintf(comprovante, "Institui��o: ProtectBank\n");
		fprintf(comprovante, "Ag�ncia: 0001\n");
		fprintf(comprovante, "N�mero da Conta: %s\n", numeroConta);
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

		printf("\nO que voc� deseja fazer?\n");
		printf("[1] - Realizar um dep�sito\n");
		printf("[2] - Realizar um saque\n");
		printf("[3] - Consultar meu extrato e meu saldo\n");
		printf("[4] - Realizar uma transfer�ncia\n");
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
				printf("Op��o inv�lida. Tente novamente.\n");
		}
	} while (escolha < 1 || escolha > 3);

}

void gerarCodigoTransacao(char *codigoTransacao) {
	
	/* 
	Gera um c�digo �nico de identifica��o para cada transa��o banc�ria realizada, 
	como saques, dep�sitos e transfer�ncias. O c�digo � gerado de forma aleat�ria 
	no formato XXX-XXXX-XXXX, utilizando letras mai�sculas e n�meros, e � armazenado 
	na string 'codigoTransacao' fornecida como par�metro.
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
	printf("              TRANSFER�NCIAS     \n");
	printf("                PROTECBANK              \n");
	corTexto(9);
	printf("===============================================\n");
	corTexto(11);
}

void realizarTransferencia(char *cpf, char *senha, int recursivo) {
	
	/* 
	  Realiza a transfer�ncia PIX entre contas banc�rias do sistema. 
	  A fun��o inicia validando o CPF do remetente e sua senha de acesso. Ap�s a autentica��o, 
	  carrega as informa��es da conta e solicita a chave PIX do destinat�rio, realizando a busca 
	  no arquivo de contas onde ficam todas as contas cadastradas para identificar o usu�rio correspondente.
	
	  O sistema apresenta os dados do destinat�rio para confirma��o e, em seguida, solicita o valor 
	  da transfer�ncia, verificando se o saldo � suficiente. Para concluir a transfer�ncia, � exigida a senha de 
	  transa��o cadastrada. Havendo sucesso, o valor � debitado do remetente e creditado ao destinat�rio, 
	  atualizando ambos os arquivos .txt de saldo com seguran�a atrav�s de arquivos tempor�rios.
	
	  Por fim, a fun��o registra o comprovante com data, valor transferido, nome do destinat�rio e um 
	  c�digo �nico da transa��o para hist�rico de movimenta��es.
	  
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
				printf("Erro: CPF n�o localizado no nosso banco. Corrija e tente novamente!\n");
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
		printf("Erro: N�o foi poss�vel acessar o arquivo do cliente. Verifique o CPF.\n");
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
		} else if (strstr(linha, "N�mero da Conta        : ")) {
			sscanf(linha, "N�mero da Conta        : %s", numeroContaRemetente);
		} else if (strstr(linha, "Senha de Transa��o     : ")) {
			sscanf(linha, "Senha de Transa��o     : %s", senhaTransacao);
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
	printf("\nCarregando suas informa��es, aguarde");
	for (int i = 0; i < 6; i++) {
		printf(".");
		fflush(stdout);
		Sleep(1000);
	}
	system("cls");
	cabTransf();
	corTexto(9);
	printf("\n--------------------------------------------\n");
	printf(" Ol�, %s!\n", nomeCliente);
	printf(" N�mero da Conta: %s\n", numeroContaRemetente);
	printf("--------------------------------------------\n");
	corTexto(11);
	printf("\n>> Seu saldo atual �: ");
	corTexto(14);
	printf("R$ %.2lf\n\n", saldoCliente);
	corTexto(11);

	encontrado = 0;
	
	FILE *arquivoContas;
	do {
		printf("Informe a chave PIX do destinat�rio: ");
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
			printf("Chave PIX n�o encontrada. Tente novamente.\n");
			corTexto(11);
		}
	} while (!encontrado);

	printf("\nConfirme as informa��es do destinat�rio:\n");
	corTexto(11);
	printf("Nome: ");
	corTexto(14);
	printf("%s\n\n", nomeDestinatario);
	corTexto(11);
	printf("Deseja confirmar a transfer�ncia? \n[1] - Sim \n[2] - N�o (corrigir Chave PIX)\nR: ");
	scanf("%d", &confirmacao);
	fflush(stdin);
	
	while (confirmacao != 1) {
		printf("Informe novamente a chave PIX do destinat�rio: ");
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
			printf("Chave PIX n�o encontrada. Tente novamente.\n");
			corTexto(11);
		}

		printf("\nConfirme as informa��es do destinat�rio:\n");
		corTexto(11);
		printf("Nome: ");
		corTexto(14);
		printf("%s\n\n", nomeDestinatario);
		corTexto(11);
		printf("Deseja confirmar a transfer�ncia? \n[1] - Sim \n[2] - N�o (corrigir Chave PIX)\nR: ");
		scanf("%d", &confirmacao);
		fflush(stdin);
	}

	do {
		printf("Digite o valor a ser transferido: R$ ");
		corTexto(14);
		if (scanf("%lf", &transferencia) != 1 || transferencia <= 0) {
			while (getchar() != '\n');
			corTexto(12);
			printf("Por favor, insira um valor num�rico v�lido maior que 0!\n");
			corTexto(11);
		} else {
			if (transferencia > saldoCliente) {
				corTexto(12);
				printf("Saldo insuficiente para a transfer�ncia!\n");
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
		printf("Para finalizar, confirme sua senha de 4 d�gitos: ");
		corTexto(14);
		scanf("%s", senhaTransacaoInput);
		fflush(stdin);
		if (strcmp(senhaTransacaoInput, senhaTransacao) != 0) {
			corTexto(12);
			printf("Erro: Senha de transa��o incorreta. Tente novamente.\n");
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
		printf("Erro: N�o foi poss�vel acessar o arquivo do destinat�rio.\n");
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
		        dataHora, "Transfer�ncia PIX", -transferencia, nomeDestinatario, codigoTransacao);
		fclose(arquivo);
	}
	arquivoDest = fopen(nomeArquivoDest, "a");
	if (arquivoDest) {

		fprintf(arquivoDest, "%s   | %s   | %+7.2f    | %-18s | %s\n",
		        dataHora, "Recebimento PIX", transferencia, nomeCliente, codigoTransacao);

		fclose(arquivoDest);
	}

	corTexto(10);
	printf("\nTransfer�ncia de R$ %.2lf realizada com sucesso!\n", transferencia);
	printf("Novo saldo dispon�vel: R$ %.2lf\n", saldoCliente);
	corTexto(11);

	int opcaoComprovante;
	corTexto(11);
	printf("\nDeseja baixar o comprovante de transfer�ncia?\n[1] - Sim\n[2] - N�o\nOp��o: ");
	scanf("%d", &opcaoComprovante);
	fflush(stdin);

	if (opcaoComprovante == 1) {
		char nomeComprovante[100];
		snprintf(nomeComprovante, sizeof(nomeComprovante),
		         "Transferencia_%s_para_%s_%s.txt", nomeCliente, nomeDestinatario,codigoTransacao);

		FILE *comprovante = fopen(nomeComprovante, "w");
		fprintf(comprovante, "--------------------------------------------------\n");
		fprintf(comprovante, "|            COMPROVANTE DE TRANSFER�NCIA         |\n");
		fprintf(comprovante, "--------------------------------------------------\n");
		fprintf(comprovante, "Valor: R$ %.2f\n", transferencia);
		fprintf(comprovante, "Tipo de Transfer�ncia: Pix\n");
		fprintf(comprovante, "Data e Hora: %s\n", dataHora);
		fprintf(comprovante, "C�digo da Transa��o: %s\n", codigoTransacao);
		fprintf(comprovante, "--------------------------------------------------\n");
		fprintf(comprovante, "|                INFORMA��ES DO DESTINAT�RIO      |\n");
		fprintf(comprovante, "--------------------------------------------------\n");
		fprintf(comprovante, "Nome: %s\n", nomeDestinatario);
		fprintf(comprovante, "Institui��o: ProtectBank\n");
		fprintf(comprovante, "Ag�ncia: 0001\n");
		fprintf(comprovante, "--------------------------------------------------\n");
		fprintf(comprovante, "|                  INFORMA��ES DO REMETENTE       |\n");
		fprintf(comprovante, "--------------------------------------------------\n");
		fprintf(comprovante, "Nome: %s\n", nomeCliente);
		fprintf(comprovante, "N�mero da Conta: %s\n", numeroContaRemetente);
		fprintf(comprovante, "Institui��o: ProtectBank\n");
		fprintf(comprovante, "Ag�ncia: 0001\n");
		fprintf(comprovante, "--------------------------------------------------\n");
		fprintf(comprovante, "|             Transa��o realizada com sucesso!    |\n");
		fprintf(comprovante, "--------------------------------------------------\n");
		fclose(comprovante);
		corTexto(10);
		printf("\nComprovante gerado com sucesso!\n");
		corTexto(11);
	}

	do {
		printf("\nO que voc� deseja fazer?\n");
		printf("[1] - Realizar uma transfer�ncia\n");
		printf("[2] - Realizar um dep�sito\n");
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
				printf("Op��o inv�lida. Tente novamente.\n");
		}
	} while (1);
}

void extrato(char *cpf, char *senha, int recursivo) {

	/*
	Exibe o extrato banc�rio de um cliente com base no CPF e senha fornecidos.
	Busca no arquivo do cliente a se��o "EXTRATO BANC�RIO" e imprime todas as linhas seguintes
	relacionadas ao extrato de forma detalhada, oferecendo op��o de gerar um comprovante.
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
		printf("    Bem-vindo ao Sistema de Extrato Banc�rio\n");
		printf("              ProtecBank                               \n");
		printf("-----------------------------------------------------\n");

		while (1) {
			corTexto(9);
			printf("Digite seu CPF (sem pontos e tra�os): ");
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
			printf("\nErro: CPF n�o encontrado ou arquivo inacess�vel. Tente novamente.\n");
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
		}else if (strstr(linha, "N�mero da Conta        : ")) {
			sscanf(linha, "N�mero da Conta        : %s", contaCliente);
		}
		
		if (strncmp(linha, "=============================================", 45) == 0) {
			if (fgets(linha, sizeof(linha), arquivoCliente) &&
				strncmp(linha, "        EXTRATO BANC�RIO", 24) == 0) {
				
				system("cls");
				corTexto(9);
				printf("\nOl�, %s! Aqui est� seu extrato banc�rio:\n\n", nomeCliente);
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
		printf("Erro: Se��o de extrato banc�rio n�o encontrada.\n");
		corTexto(15);
		return;
	}

	int opcaoComprovante;
	printf("\n\nDeseja gerar um comprovante do extrato?\n[1] Sim\n[2] N�o\nR: ");
	scanf("%d", &opcaoComprovante);
	fflush(stdin);

	if (opcaoComprovante == 1) {
		time_t agora = time(NULL);
		struct tm *dataHora = localtime(&agora);
		char dataFormatada[100];
		strftime(dataFormatada, sizeof(dataFormatada), "%d/%m/%Y �s %H:%M:%S", dataHora);

		char nomeArquivo[100];
		snprintf(nomeArquivo, sizeof(nomeArquivo), "extrato_%s_conta_%s.txt", nomeCliente, contaCliente);
		FILE *comprovante = fopen(nomeArquivo, "w");

		if (comprovante) {
			fprintf(comprovante, "============================================================\n");
			fprintf(comprovante, "               Comprovante de Extrato Banc�rio              \n");
			fprintf(comprovante, "                        ProtecBank                          \n");
			fprintf(comprovante, "============================================================\n");
			fprintf(comprovante, "Cliente           : %s\n", nomeCliente);
			fprintf(comprovante, "N�mero da Conta   : %s\n", contaCliente);
			fprintf(comprovante, "Data da Solicita��o: %s\n", dataFormatada);
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
		printf("\n\nO que voc� deseja fazer? \n[1] - Finalizar atendimento\n[2] - Realizar um deposito\n[3] - Realizar um saque\n[4] - Realizar uma transfer�ncia\nR: ");
		scanf("%d", &esq);
		fflush(stdin);

		switch (esq) {
			case 1:
				corTexto(11);
				printf("\nVoc� escolheu finalizar o atendimento. At� logo!\n");
				break;
			case 2:
				corTexto(14);
				printf("\nVoc� escolheu realizar um dep�sito.\n");
				realizarDeposito(cpf, senha, 1);
				break;
			case 3:
				corTexto(14);
				printf("\nVoc� escolheu realizar um saque.\n");
				realizarSaque(cpf, senha, 1);
				break;
			case 4:
				corTexto(14);
				system("cls");
				printf("\nVoc� escolheu realizar uma transfer�ncia.\n");
				realizarTransferencia(cpf, senha, 1);
				break;
			default:
				corTexto(12);
				printf("\nOp��o inv�lida. Tente novamente.\n");
				corTexto(11);
				break;
		}
	} while (esq < 1 || esq > 4);
}

void atualizarEndereco(char *cpf) {
	
	/*

	Respons�vel por permitir ao cliente atualizar seu endere�o cadastrado no sistema banc�rio. 

	� chamada dentro da fun��o principal de atualiza��o de cadastro, quando o usu�rio opta 
	por alterar o endere�o.

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
		printf("Erro: CPF n�o localizado no nosso banco. Corrija e tente novamente!\n");
		corTexto(11);
		return;
	} else {
		fclose(arquivo);
		encontrado = 1;
	}

	arquivo = fopen(nomeArquivo, "r+");
	if (arquivo == NULL) {
		corTexto(12);
		printf("Erro: N�o foi poss�vel acessar o arquivo do cliente. Verifique o CPF.\n");
		corTexto(11);
		return;
	}

	while (fgets(linha, sizeof(linha), arquivo)) {
		if (strstr(linha, "Nome completo          : ")) {
			sscanf(linha, "Nome completo          : %[^\n]", nomeCliente);
		} else if (strstr(linha, "Endere�o               : ")) {
			sscanf(linha, "Endere�o               : %[^\n]", endereco);
		} else if (strstr(linha, "N�mero                 : ")) {
			sscanf(linha, "N�mero                 : %[^\n]", numero);
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
	printf("\nCarregando suas informa��es, aguarde");
	for (int i = 0; i < 6; i++) {
		printf(".");
		fflush(stdout);
		Sleep(1000);
	}
	system("cls");

	corTexto(9);
	printf("\n--------------------------------------------\n");
	printf(" Ol�, %s!\n", nomeCliente);
	printf("--------------------------------------------\n");
	corTexto(11);
	printf("\n>> Seu endere�o atual �:\n");
	corTexto(14);
	printf("Endere�o: %s\n", endereco);
	printf("N�mero: %s\n", numero);
	printf("Bairro: %s\n", bairro);
	printf("Cidade: %s\n", cidade);
	printf("Estado: %s\n", estado);
	printf("CEP: %s\n\n", cep);
	corTexto(11);

	corTexto(11);
	printf("- Informe o novo endere�o -\n");
	printf("Informe o nome da rua: ");
	corTexto(14);
	fflush(stdin);
	fgets(endereco, sizeof(endereco), stdin);
	endereco[strcspn(endereco, "\n")] = 0;

	corTexto(11);
	printf("Informe o novo n�mero: ");
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
		printf("\nVoc� est� alterando os dados para:\n\n");;
		corTexto(11); printf("Endere�o: "); corTexto(14); printf("%s\n", endereco);
		corTexto(11); printf("N�mero: "); corTexto(14); printf("%s\n", numero);
		corTexto(11); printf("Bairro: "); corTexto(14); printf("%s\n", bairro);
		corTexto(11); printf("Cidade: "); corTexto(14); printf("%s\n", cidade);
		corTexto(11); printf("Estado: "); corTexto(14); printf("%s\n", estado);
		corTexto(11); printf("CEP: "); corTexto(14); printf("%s\n", cep);
		corTexto(11);
		printf("\nConfirma a altera��o? \n[1] - Sim\n[2] - N�o, corrigir\nR: ");
		scanf("%d", &escolha);
		fflush(stdin);

		if (escolha == 1) {
			break;
		} else if (escolha == 2) {
			return;
		} else {
			corTexto(12);
			printf("\nOp��o inv�lida! Tente novamente.\n");
			corTexto(11);
		}
	} while (escolha != 1);

	rewind(arquivo);
	FILE *tempArquivo = fopen("temp_cliente.txt", "w");
	while (fgets(linha, sizeof(linha), arquivo)) {
		if (strstr(linha, "Endere�o               : ")) {
			fprintf(tempArquivo, "Endere�o               : %s\n", endereco);
		} else if (strstr(linha, "N�mero                 : ")) {
			fprintf(tempArquivo, "N�mero                 : %s\n", numero);
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
	printf("\nEndere�o atualizado com sucesso!\n");

}

void atualizarPix(const char *cpf) {
	
	/*
		Respons�vel por atualizar a chave Pix de um cliente no sistema banc�rio. 
	
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
		printf("Erro: N�o foi poss�vel abrir o arquivo do cliente. Verifique o CPF.\n");
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
		printf("Erro: Senha n�o encontrada no arquivo do cliente.\n");
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
		printf("Erro: Pix n�o encontrado no arquivo do cliente.\n");
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
			printf("Erro: N�o foi poss�vel abrir o arquivo de contas.\n");
			corTexto(7);
			fclose(arquivo);
			return;
		}

		FILE *tempContas = fopen("contas_temp.txt", "w");
		if (!tempContas) {
			corTexto(12);
			printf("Erro: N�o foi poss�vel criar o arquivo tempor�rio de contas.\n");
			corTexto(7);
			fclose(arquivo);
			fclose(contas);
			return;
		}

		encontrado = 0;
		while (fgets(linha, sizeof(linha), contas)) {
			if (strstr(linha, "Pix                    : ") && strstr(linha, novoDado)) {
				corTexto(12);
				printf("Erro: Esta chave PIX j� est� cadastrada em outra conta!\n");
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
			printf("\nDeseja tentar uma nova chave Pix?\n[1] - Sim\n[2] - Voltar ao menu de atualiza��o\nEscolha: ");
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
		printf("Erro: N�o foi poss�vel criar o arquivo tempor�rio do cliente.\n");
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
		printf("\nDeseja atualizar algum outro dado?\n[1] - Sim\n[2] - N�o, sair!\nR: ");
		scanf("%d", &esq);
		fflush(stdin);

		if (esq == 1) {
			atualizarCadastro();
		} else if (esq == 2) {
			break;
		} else {
			printf("\nop��o inv�lida!!!\n");
		}
	} while (esq != 1 || esq != 2);

}

void atualizarCadastro() {
	
	/*
     	Permite ao cliente atualizar seus dados cadastrais no sistema banc�rio.
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
		printf("           ATUALIZA��O CADASTRAL         \n");
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
			printf("Erro: CPF n�o encontrado. Por favor, tente novamente.\n");
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
			printf("Erro: Senha n�o encontrada no arquivo do cliente.\n");
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
		printf("    Bem-vindo ao Sistema de Extrato Banc�rio\n");
		printf("              ProtecBank                               \n");
		corTexto(9);
		printf("-----------------------------------------------------\n");
		printf("\n=========================================\n");
		printf("        ATUALIZA��O CADASTRAL          \n");
		printf("=========================================\n\n");
		corTexto(11);
		printf("[1] - Atualizar Pix\n");
		printf("[2] - Atualizar Endere�o\n");
		printf("[3] - Atualizar Telefone\n");
		printf("[4] - Atualizar Email\n");
		printf("[5] - Atualizar Senha\n");
		printf("[6] - Atualizar Senha de Transa��o\n");
		printf("[7] - Atualizar Pergunta/Resposta Secreta\n");
		printf("[0] - Voltar\n");
		printf("Escolha: ");
		scanf("%d", &opcao);
		fflush(stdin);

		if (opcao < 0 || opcao > 7) {
			corTexto(12);
			printf("Op��o inv�lida. Por favor, tente novamente.\n");
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
				printf("\nInforme seu novo n�mero de telefone: ");
				corTexto(14);
				scanf(" %[^\n]", novoDado);
				corTexto(11);
				int valido = 1;

				if (strlen(novoDado) != 11) {
					corTexto(12);
					printf("O telefone deve conter exatamente 11 d�gitos!!!\n");
					corTexto(11);
					valido = 0;
				} else {

					for (int i = 0; i < 11; i++) {
						if (!isdigit(novoDado[i])) {
							corTexto(12);
							printf("O telefone deve conter apenas n�meros!!!\n");
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
					printf("O e-mail � inv�lido. Verifique as regras e tente novamente.\n");
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
				printf("Informe sua nova senha de transa��o (4 d�gitos): ");
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
			printf("Erro: N�o foi poss�vel abrir o arquivo do cliente.\n");
			corTexto(7);
			return;
		}

		FILE *temp = fopen("temp.txt", "w");
		if (!temp) {
			corTexto(12);
			printf("Erro: N�o foi poss�vel criar o arquivo tempor�rio.\n");
			corTexto(7);
			fclose(arquivo);
			return;
		}

		while (fgets(linha, sizeof(linha), arquivo)) {
					if(
				    (opcao == 3 && strstr(linha, "Telefone               : ")) ||
			        (opcao == 4 && strstr(linha, "E-mail                 : ")) ||
			        (opcao == 6 && strstr(linha, "Senha de Transa��o     : ")) ||
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

		printf("\nO que voc� deseja fazer?\n");
		printf("[1] - Realizar um dep�sito\n");
		printf("[2] - Realizar um saque\n");
		printf("[3] - Consultar meu extrato e meu saldo\n");
		printf("[4] - Realizar uma transfer�ncia\n");
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
				printf("Op��o inv�lida. Tente novamente.\n");
		}
	} while (esqq < 1 || esqq > 3);

}

int chavePixJaCadastrada(const char *arquivo, const char *chavePix) {
	
	// Fun��o para verificar se a chave Pix informada j� est� cadastrada em outro cliente no sistema.

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








