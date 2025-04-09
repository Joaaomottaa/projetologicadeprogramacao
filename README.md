# Sistema bancário 

# – Sistema Bancário em Linguagem C

Este é um sistema bancário completo desenvolvido como projeto final da disciplina de **Lógica de Programação** no curso de **Desenvolvimento de Sistemas**. O objetivo principal foi aplicar os conceitos de lógica, validações, modularização, estrutura de dados e manipulação de arquivos, simulando o funcionamento de um banco real por terminal.

---

##  Funcionalidades Principais

- **Geração de Senhas com Prioridade**
  - Geração de senhas **preferenciais** e **convencionais**.
  - Controle de atendimento por ordem e prioridade na fila.

- **Cadastro de Contas Bancárias**
  - Validação completa dos dados do cliente:
    - Nome completo (sem números)
    - Data de nascimento (formato válido)
    - CPF (único e válido com 11 dígitos)
    - Endereço e contato
    - Senha com regras de segurança
    - Tipo de conta (Poupança, corrente, salário, especial)
    - Chave Pix (única: e-mail, CPF,  telefone ou chave aleatória)
  - Geração automática do número da conta.
  - Armazenamento persistente de todos os dados em um arquivo `.txt` com nome do CPF.
  - Criação do arquivo contas, onde armazena todas as contas do banco, para acesso admin ter controle por exemplo.

- **Validações de Acesso**
  - Login por número da conta e senha.
  - Se o cliente já está em uma função e chamar a recursão ou outra função não é pedido CPF e senha.
  - Reforço de segurança nas operações bancárias.

- **Redefinição de Senha**
  - Recuperação por:
    -  E-mail
    -  Telefone
    -  Pergunta secreta
  - Verificação de critérios de senha segura e atualização no arquivo.
  - E-mail / Telefone é gerado e enviado um código de 6 dígitos no arquivo .txt do cliente a partir da linha de caixa de entrada do telefone ou do e-mail onde só é possível alterar com a confirmação correta.

- **Operações Bancárias**
  -  Abrir conta
  -  Encerrar conta
  -  Consultar saldo
  -  Saque
  -  Depósito
  -  Transferência via Pix
  -  Emissão de extrato
  -  Atualização de dados cadastrais

- **Emissão de Comprovantes**
  - Comprovante de atendimento, depósito, saque, transferência e mais tudo direto criando um arquivo .txt

- **Persistência de Dados**
  - Todos os dados são armazenados diretamente em arquivos `.txt`.
  - Atualização automática das informações após cada operação.
  - Arquivo central com todas as contas do banco.

- **Interface Interativa**
  - Terminal colorido com menus de navegação intuitivos.
  - Layout dividido por seções e uso de símbolos para melhor leitura.

- **Fila de Atendimento**
  - Organização de atendimento por prioridade e tipo de serviço.
  - Sistema simula uma agência bancária com emissão e chamada de senhas.

- **🛡️ OBS:**
  - Todos os dados inseridos pelos usuários são **validados** e tratados.
  - O sistema **trata erros e exceções** para evitar falhas durante todo o uso.

---

## 🛠️ Tecnologias Utilizadas

- **Linguagem:** C
- **Persistência de Dados:** Arquivos `.txt`
- **Plataforma:** Terminal (CLI)
- **Editor:** DevC++ 

---

## 📸 Imagens do Sistema

> Veja abaixo algumas telas do sistema em funcionamento:

| Tela Inicial | Cadastro de Conta | Conta Criada |
|--------------|-------------------|---------------|
| ![](./screens/tela-inicial.png) | ![](./screens/cadastro.png) | ![](./screens/conta-criada.png) |

| Fila de Atendimento | Depósito | Transferência Pix |
|---------------------|----------|--------------------|
| ![](./screens/fila.png) | ![](./screens/deposito.png) | ![](./screens/pix.png) |

| Extrato | Exclusão de Conta |
|--------|--------------------|
| ![](./screens/extrato.png) | ![](./screens/excluir.png) |

---

## 🧠 Aprendizados

Durante o desenvolvimento do projeto, foi possível aprofundar conhecimentos em:
- Estrutura e modularização de código em C
- Manipulação de arquivos
- Validações de dados
- Estruturas condicionais e de repetição
- Boas práticas de usabilidade via terminal
- Funções recursivas e iterativas
- Busca e ordenação
- Lista, fila e pilha
- 
---

## 📁 Como Executar

1. Clone o repositório:
   ```bash
   git clone https://github.com/seu-usuario/ProtecBank.git
