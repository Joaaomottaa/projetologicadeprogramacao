# Sistema bancário 

# – Sistema Bancário em Linguagem C

Este é um sistema bancário completo desenvolvido como projeto final da disciplina de **Lógica de Programação** no curso de **Desenvolvimento de Sistemas**. O objetivo principal foi aplicar os conceitos de lógica, validações, modularização, estrutura de dados e manipulação de arquivos, simulando o funcionamento de um banco real por terminal.

---
# 📁 Organização das Pastas

O projeto está estruturado em pastas para facilitar a organização e entendimento dos arquivos utilizados durante o desenvolvimento do sistema.

🗒️ **Observação importante**: As pastas e arquivos contidos no projeto são apenas **exemplos** gerados em testes e simulações. Eles servem como referência de funcionamento e estrutura.

# Pasta /	Descrição

- **Banco de dados - contas**/	Contém arquivos .txt simulando o armazenamento individual das contas criadas com base no CPF do cliente.

- **Comprovantes de transacoes**/	Armazena comprovantes gerados automaticamente nas operações como saques, depósitos, transferências e extratos.
  
- **Imagens**/	Capturas de tela e imagens ilustrativas do funcionamento do sistema bancário no terminal.
  
- **Senhas na fila** /	Arquivos de controle de senha preferencial e convencional gerados pelo sistema durante o atendimento.
  
- **Todas contas do banco** /	Contém o arquivo contas.txt com o registro de todas as contas criadas no sistema.
  
- **Src** /	Pasta onde se encontra o código-fonte principal do sistema (Sistema-Bancario.cpp).


## ⚙️ Funcionalidades Principais

- **Geração de Senhas com Prioridade**
  - Geração de senhas **preferenciais** e **convencionais**.
  - Controle de atendimento por ordem e prioridade na fila.

- **Cadastro de Contas Bancárias**
  - Validação completa dos dados do cliente:
    - Nome completo (sem números)
    - Data de nascimento (formato e idade válidos)
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
  - Comprovante de senha do atendimento
  - Comprovante de depósito, saque, transferência, extrato tudo direto criando um arquivo com todos detalhes da transação .txt

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
- 

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

## 🧗‍♂️ Desafios Enfrentados

Durante o desenvolvimento do sistema, alguns dos maiores desafios enfrentados foram:

1° **Manipulação de arquivos .txt**: trabalhar com leitura, escrita, atualização e exclusão de dados em arquivos externos foi uma das partes mais complexas do projeto. Garantir que os dados fossem armazenados de forma persistente, com consistência e segurança, exigiu atenção aos modos de abertura (r, w, a, r+, w+) e ao controle de fluxo dos dados.
- Leitura e extração de dados: extrair informações específicas de arquivos, como buscar uma conta pelo CPF ou localizar linhas para modificar dados do cliente, foi desafiador. Isso envolveu a leitura linha por linha, além de lógica para identificar exatamente o que precisava ser alterado.
- Alteração de dados dentro do arquivo: modificar informações sem comprometer o restante do conteúdo foi um processo delicado. Em muitos casos, foi necessário criar arquivos temporários para reescrever os dados com as alterações corretas.

2° **Uso de ponteiros**: um dos aspectos mais difíceis da linguagem C é o uso correto de ponteiros. Lidar com ponteiros exige entender a diferença entre o valor e o endereço de uma variável, saber quando usar * ou &, além de ter cuidado com a alocação e liberação de memória.

Superar essas dificuldades exigiu prática, revisão frequente do código e um entendimento mais profundo do funcionamento interno da linguagem. Apesar de complexos, os ponteiros também trouxeram muito mais flexibilidade ao código e foram indispensáveis para o bom funcionamento do sistema.

  ## ⚙️ Como Executar o Projeto

### 🖥️ Opção 1: Usando o Dev C++ (O que usei para fazer todo o projeto)

> Recomendado para usuários Windows que desejam compilar com interface gráfica.

1. Baixe ou clone o repositório:
   ```bash
   git clone https://github.com/Joaaomottaa/projetologicadeprogramacao.git

- Abra o Dev C++.
- Vá em Arquivo > Abrir e selecione o arquivo PROJETO FINAL.cpp.
- Clique em Compilar e Executar (F11).

 ###  🧩 Opção 2: Usando o Visual Studio (Windows)

Recomendado para quem já utiliza o Visual Studio como IDE principal.

- Abra o Visual Studio.
- Vá em Arquivo > Novo > Projeto.
- Selecione "Aplicativo de Console (C++)" e clique em Avançar.
- Dê um nome ao projeto e escolha o local onde ele será salvo (pode usar a mesma pasta onde está o PROJETO FINAL.cpp, se quiser manter os arquivos juntos).
- Após o projeto ser criado, exclua o arquivo .cpp padrão que o Visual Studio criou (geralmente projectname.cpp).
- Vá em Projeto > Adicionar Arquivo Existente..., selecione o PROJETO FINAL.cpp do seu repositório e clique em Adicionar.
- Clique em Compilar e Executar (F5) para rodar o programa.
