// versão para testes e testar como irá funcionar a aplicação do codigo ultilizando hash e salt
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 20

// Estrutura do usuário
typedef struct Usuario {
    char nome[50];
    char senha_hash[100];
    struct Usuario* prox;
} Usuario;

Usuario* tabela[TAM];

// Limpa a tela do terminal
void limpar_tela() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Função hash para o nome do usuário
int hash(char* chave) {
    int soma = 0;
    for (int i = 0; chave[i] != '\0'; i++) {
        soma += chave[i];
    }
    return soma % TAM;
}

// Função de hash da senha (didática, simples) com salting
void hash_senha(char* senha, char* hash_result) {
    char salt[] = "abc123"; // exemplo de salt fixo
    char senha_com_salt[150];
    sprintf(senha_com_salt, "%s%s", senha, salt);

    int valor = 0;
    for (int i = 0; senha_com_salt[i] != '\0'; i++) {
        valor += senha_com_salt[i] * (i + 1);
    }
    sprintf(hash_result, "%x", valor); // resultado em hexadecimal
}

// Cadastrar novo usuário
void cadastrar(char* nome, char* senha) {
    int indice = hash(nome);

    Usuario* atual = tabela[indice];
    while (atual != NULL) {
        if (strcmp(atual->nome, nome) == 0) {
            printf("Usuário já existe!\n");
            return;
        }
        atual = atual->prox;
    }

    Usuario* novo = malloc(sizeof(Usuario));
    strcpy(novo->nome, nome);
    hash_senha(senha, novo->senha_hash);
    novo->prox = tabela[indice];
    tabela[indice] = novo;

    printf("Usuário cadastrado com sucesso!\n");
}

// Autenticar usuário
int autenticar(char* nome, char* senha) {
    int indice = hash(nome);
    Usuario* atual = tabela[indice];
    char senha_hash[100];
    hash_senha(senha, senha_hash);

    while (atual != NULL) {
        if (strcmp(atual->nome, nome) == 0) {
            if (strcmp(atual->senha_hash, senha_hash) == 0) {
                return 1; // sucesso
            } else {
                return 0; // senha incorreta
            }
        }
        atual = atual->prox;
    }
    return -1; // usuário não encontrado
}

// Menu interativo
void menu() {
    int opcao;
    char nome[50];
    char senha[50];

    do {
        printf("\n=== MENU ===\n");
        printf("1. Cadastrar\n");
        printf("2. Login\n");
        printf("3. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        limpar_tela(); // limpa a tela após selecionar uma opção

        switch (opcao) {
            case 1:
                printf("Cadastro de usuário:\n");
                printf("Nome: ");
                scanf("%s", nome);
                printf("Senha: ");
                scanf("%s", senha);
                cadastrar(nome, senha);
                break;

            case 2:
                printf("Login:\n");
                printf("Nome: ");
                scanf("%s", nome);
                printf("Senha: ");
                scanf("%s", senha);
                int res = autenticar(nome, senha);
                if (res == 1)
                    printf("Login bem-sucedido!\n");
                else if (res == 0)
                    printf("Senha incorreta.\n");
                else
                    printf("Usuário não encontrado.\n");
                break;

            case 3:
                printf("Encerrando...\n");
                break;

            default:
                printf("Opção inválida!\n");
        }

    } while (opcao != 3);
}

int main() {
    menu();
    return 0;
}
