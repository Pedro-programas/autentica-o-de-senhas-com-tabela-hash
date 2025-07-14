#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h> // Requer libssl-dev
#include <time.h>

#define TAM 20
// Estrutura do usuário 
typedef struct Usuario {
    char nome[50];
    char senha_hash[SHA256_DIGEST_LENGTH*2+1]; // SHA-256 em hex
    char salt[16]; // Salt único
    struct Usuario* prox;
} Usuario;

Usuario* tabela[TAM];
// função para limpar a tela do terminal
void limpar_tela() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int hash(char* chave) {
    int soma = 0;
    for (int i = 0; chave[i] != '\0'; i++) {
        soma += chave[i];
    }
    return soma % TAM;
}

// Gerador de salt aleatório
void gerar_salt(char* salt, size_t tamanho) {
    const char* caracteres = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    for (size_t i = 0; i < tamanho - 1; i++) {
        salt[i] = caracteres[rand() % strlen(caracteres)];
    }
    salt[tamanho - 1] = '\0';
}

// Função para gerar o hash SHA-256 com salt
void hash_senha(const char* senha, const char* salt, char* hash_result) {
    char buffer[150];
    snprintf(buffer, sizeof(buffer), "%s%s", senha, salt);

    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char*)buffer, strlen(buffer), hash);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hash_result + (i * 2), "%02x", hash[i]);
    }
    hash_result[SHA256_DIGEST_LENGTH * 2] = '\0';
}

// Cadastro
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
    gerar_salt(novo->salt, sizeof(novo->salt));
    hash_senha(senha, novo->salt, novo->senha_hash);
    novo->prox = tabela[indice];
    tabela[indice] = novo;

    printf("Usuário cadastrado com sucesso!\n");
}

// Autenticação
int autenticar(char* nome, char* senha) {
    int indice = hash(nome);
    Usuario* atual = tabela[indice];
    char senha_hash[SHA256_DIGEST_LENGTH*2 + 1];

    while (atual != NULL) {
        if (strcmp(atual->nome, nome) == 0) {
            hash_senha(senha, atual->salt, senha_hash);
            if (strcmp(atual->senha_hash, senha_hash) == 0) {
                return 1;
            } else {
                return 0;
            }
        }
        atual = atual->prox;
    }
    return -1;
}
// função principal
int main() {
    srand(time(NULL));
    int opcao;
    char nome[50], senha[50];
    //Condição while para repetir o menu 
    while (1) {
        limpar_tela();
        printf("1 - Cadastrar\n2 - Autenticar\n0 - Sair\nEscolha: ");
        scanf("%d", &opcao);
        getchar(); // Limpa o buffer

        if (opcao == 1) {// Cadastrar novo usuário
            printf("Nome: ");
            fgets(nome, sizeof(nome), stdin);
            nome[strcspn(nome, "\n")] = 0;
            printf("Senha: ");
            fgets(senha, sizeof(senha), stdin);
            senha[strcspn(senha, "\n")] = 0;
            cadastrar(nome, senha);
            getchar();
        } else if (opcao == 2) {// Autenticar usuário
            printf("Nome: ");
            fgets(nome, sizeof(nome), stdin);
            nome[strcspn(nome, "\n")] = 0;
            printf("Senha: ");
            fgets(senha, sizeof(senha), stdin);
            senha[strcspn(senha, "\n")] = 0;
            int res = autenticar(nome, senha);
            if (res == 1)
                printf("Autenticado!\n");
            else if (res == 0)
                printf("Senha incorreta!\n");
            else
                printf("Usuário não encontrado!\n");
            getchar();
        } else if (opcao == 0) {
            break;
        }
    }
    return 0;
}