# Autenticação de Senhas com Tabela Hash

Este projeto demonstra dois métodos de autenticação de usuários utilizando tabelas hash em C. O objetivo é mostrar como armazenar e verificar senhas de forma simples e também utilizando técnicas mais seguras com hash e salt.

## Estrutura do Projeto

- `senhas.c`: Implementação didática, usando um hash simples para as senhas.
- `senhas1.c`: Implementação segura, usando SHA-256 e salt para proteger as senhas (requer OpenSSL).
- `senhas1`: Binário gerado a partir de `senhas1.c`.
- `output/senhas.exe`: Binário gerado (Windows).
- `README.md`: Este arquivo.

## Como funciona

### Cadastro e Autenticação

- O usuário pode se cadastrar informando nome e senha.
- As informações são armazenadas em uma tabela hash, permitindo buscas rápidas.
- Para autenticar, o usuário informa nome e senha, e o sistema verifica se a senha está correta.

### Diferenças entre as versões

- **senhas.c**: Usa um hash simples para a senha (apenas para fins didáticos, não seguro para produção).
- **senhas1.c**: Usa SHA-256 com salt aleatório, tornando o armazenamento das senhas mais seguro.

## Requisitos

- GCC para compilar os arquivos `.c`.
- Para `senhas1.c`, é necessário ter a biblioteca OpenSSL instalada (`libssl-dev` no Linux).

## Compilação

Para compilar a versão simples:
```sh
gcc senhas.c -o senhas 
```

Para compilar a versão segura:
```sh
gcc senhas1.c -o senhas1 -lssl -lcrypto
```

## Execução

No terminal, execute o binário desejado:
```sh
./senhas      # versão simples
./senhas1     # versão segura
```

## Observações

- O projeto é apenas para fins educacionais.
- Não utilize o método simples para aplicações reais.
- O método com SHA-256 e salt é mais seguro, mas para produção recomenda-se usar funções específicas para senhas (ex: bcrypt, Argon2).

## Licença

Este projeto é livre para uso acadêmico.