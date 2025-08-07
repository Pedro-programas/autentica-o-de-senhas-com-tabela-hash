# Mini Sistema de Autenticação de Senhas com Tabela Hash

Projeto desenvolvido para a disciplina de Algoritmos e Estruturas de Dados II, orientado pelo professor Dr. Kennedy Reurison Lopes.

---

## Sumário

1. [Introdução](#introdução)
2. [Discentes e Docente](#discentes-e-docente)
3. [Estrutura do Projeto](#estrutura-do-projeto)
4. [Funcionamento](#funcionamento)
    - [Cadastro e Autenticação](#cadastro-e-autenticação)
    - [Diferenças entre as versões](#diferenças-entre-as-versões)
5. [Requisitos](#requisitos)
6. [Compilação](#compilação)
7. [Execução](#execução)
8. [Como Utilizar](#como-utilizar)
9. [Desafios Encontrados](#desafios-encontrados)
10. [Observações](#observações)
11. [Licença](#licença)

---

## Introdução

Este projeto apresenta um mini sistema de autenticação de usuários utilizando tabela hash para armazenamento seguro de senhas. O objetivo é demonstrar conceitos de segurança, hashing e manipulação de dados em C.

---

## Discentes e Docente

**Discentes:**
- Gabriel Guimarães Damião Pinto (Apresentador)
- Maycon Soares Maia (GitMaster)
- Pedro Henrique Pereira de Sousa (Codificador)
- Sávio de Oliveira Jerônimo (Redator)

**Docente:**
- Kennedy Reurison Lopes

---

## Estrutura do Projeto

- `senhas.c`: Implementação didática, usando um hash simples para as senhas.
- `senhas1.c`: Implementação segura, usando SHA-256 e salt para proteger as senhas (requer OpenSSL).
- `senhas1`: Binário gerado a partir de `senhas1.c`.

---

## Funcionamento

### Cadastro e Autenticação

- O usuário pode se cadastrar informando nome e senha.
- As informações são armazenadas em uma tabela hash, permitindo buscas rápidas.
- Para autenticar, o usuário informa nome e senha, e o sistema verifica se a senha está correta.

### Diferenças entre as versões

- **senhas.c**: Utiliza um hash simples para a senha (apenas para fins didáticos, não seguro para produção).
- **senhas1.c**: Utiliza SHA-256 com salt aleatório, tornando o armazenamento das senhas mais seguro.

---

## Requisitos

- GCC para compilar os arquivos `.c`.
- Para `senhas1.c`, é necessário ter a biblioteca OpenSSL instalada (`libssl-dev` no Linux).

---

## Compilação

Para compilar a versão simples:
```sh
gcc senhas.c -o senhas 
```

Para compilar a versão segura:
```sh
gcc senhas1.c -o senhas1 -lssl -lcrypto
```

---

## Execução

No terminal, execute o binário desejado:
```sh
./senhas      # versão simples
./senhas1     # versão segura
```

No Windows, utilize:
```sh
senhas.exe
senhas1.exe
```

---

## Como Utilizar

1. Ao executar o programa, será exibido um menu com as opções:
    - 1 - Cadastrar
    - 2 - Autenticar
    - 0 - Sair
2. Para cadastrar, escolha a opção 1, informe o nome e a senha desejada.
3. Para autenticar, escolha a opção 2, informe o nome e a senha cadastrados.
4. O programa informará se o usuário foi autenticado, se a senha está incorreta ou se o usuário não existe.
5. Para sair, escolha a opção 0.

---

## Desafios Encontrados

Durante o desenvolvimento, alguns desafios foram enfrentados:

- **Implementação do salt**: O salt precisa ser aleatório e associado corretamente ao usuário para garantir a segurança do hash da senha.
- **Uso do SHA-256**: Integrar a biblioteca OpenSSL para gerar o hash SHA-256, principalmente na manipulação dos dados binários e conversão para hexadecimal.
- **Validação e comparação de senhas**: Garantir que a combinação senha + salt fosse corretamente processada e comparada, evitando erros de autenticação.
- **Gerenciamento da tabela hash**: Implementar a estrutura de dados para armazenar múltiplos usuários e lidar com colisões exigiu atenção especial para garantir buscas rápidas e corretas.

---

## Observações

- O projeto é apenas para fins educacionais.
- O método implementado com SHA-256 e salt é mais seguro, mas para produção recomenda-se usar funções específicas para senhas (ex: bcrypt, Argon2).
- Contribuições são bem-vindas! Sinta-se à vontade para abrir issues ou pull requests.

---

## Licença

Este projeto é livre para uso acadêmico.