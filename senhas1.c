#include <stdio.h>      // biblioteca padrão
#include <stdlib.h>     // biblioteca para manipulação de memória dinâmica
#include <string.h>     // biblioteca para manipulação de strings
#include <openssl/sha.h> // Requer libssl-dev
#include <time.h>

#define TAM 20
// struct do usuário 
typedef struct Usuario {
    char nome[50];
    char senha_hash[SHA256_DIGEST_LENGTH*2+1]; // SHA-256 em hex
    char salt[16]; // Salt único
    struct Usuario* prox;
} Usuario;

Usuario* tabela[TAM];
// função para limpar a tela do terminal
void limpar_tela() {// Limpa a tela do terminal
    // Verifica o sistema operacional e executa o comando apropriado
#ifdef _WIN32
    system("cls");// Para Windows
#else
    system("clear");// Para Unix/Linux/Mac
#endif
}

int hash(char* chave) {// Função de hash simples
    int soma = 0;// Inicializa a soma
    for (int i = 0; chave[i] != '\0'; i++) {// Percorre cada caractere da chave
        soma += chave[i];// Soma o valor ASCII de cada caractere
    }
    return soma % TAM;// Retorna o índice na tabela hash
}

// Gerador de salt aleatório
void gerar_salt(char* salt, size_t tamanho) {// Função para gerar um salt aleatório
    const char* caracteres = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";// Conjunto de caracteres para o salt
    for (size_t i = 0; i < tamanho - 1; i++) {// Preenche o salt com caracteres aleatórios
        salt[i] = caracteres[rand() % strlen(caracteres)];// Seleciona um caractere aleatório do conjunto
    }
    salt[tamanho - 1] = '\0';// Termina a string com null
}

// Função para gerar o hash SHA-256 com salt
void hash_senha(const char* senha, const char* salt, char* hash_result) {// Função para gerar o hash da senha com o salt
    char buffer[150];// Combina a senha e o salt
    snprintf(buffer, sizeof(buffer), "%s%s", senha, salt);// Combina a senha e o salt em um buffer

    unsigned char hash[SHA256_DIGEST_LENGTH];// Buffer para armazenar o hash
    SHA256((unsigned char*)buffer, strlen(buffer), hash);// Calcula o hash SHA-256 da combinação senha + salt

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {// Converte o hash para uma string hexadecimal
        sprintf(hash_result + (i * 2), "%02x", hash[i]);// Formata cada byte do hash como dois dígitos hexadecimais
    }
    hash_result[SHA256_DIGEST_LENGTH * 2] = '\0';// Termina a string com null
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
    strcpy(novo->nome, nome);// Copia o nome do usuário
    gerar_salt(novo->salt, sizeof(novo->salt));// Gera um salt aleatório
    hash_senha(senha, novo->salt, novo->senha_hash);// Gera o hash da senha com o salt
    novo->prox = tabela[indice];// Insere o novo usuário no início da lista
    tabela[indice] = novo;// Atualiza a tabela hash

    printf("Usuário cadastrado com sucesso!\n");
}

// Autenticação
int autenticar(char* nome, char* senha) {// Função para autenticar o usuário
    int indice = hash(nome);// Calcula o índice da tabela hash
    Usuario* atual = tabela[indice];// Obtém o usuário atual na tabela hash
    char senha_hash[SHA256_DIGEST_LENGTH*2 + 1];// Buffer para armazenar o hash da senha

    while (atual != NULL) {
        if (strcmp(atual->nome, nome) == 0) {// Verifica se o nome do usuário corresponde ao nome fornecido
            hash_senha(senha, atual->salt, senha_hash);// Gera o hash da senha fornecida com o salt do usuário
            if (strcmp(atual->senha_hash, senha_hash) == 0) {// Compara o hash da senha fornecida com o hash armazenado
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
    srand(time(NULL));// Inicializa o gerador de números aleatórios
    int opcao;
    char nome[50], senha[50];
    //Condição while para repetir o menu 
    while (1) {
        limpar_tela();
        printf("1 - Cadastrar\n2 - Autenticar\n0 - Sair\nEscolha: ");// Exibe o menu
        scanf("%d", &opcao);
        getchar(); // Limpa o buffer

        if (opcao == 1) {// Cadastrar novo usuário
            printf("Nome: ");
            fgets(nome, sizeof(nome), stdin);// Lê o nome do usuário
            nome[strcspn(nome, "\n")] = 0;// Remove newline character
            printf("Senha: ");
            fgets(senha, sizeof(senha), stdin);// Lê a senha do usuário
            senha[strcspn(senha, "\n")] = 0;// Remove newline character
            cadastrar(nome, senha);
            getchar();
        } else if (opcao == 2) {// Autenticar usuário
            printf("Nome: ");
            fgets(nome, sizeof(nome), stdin);// Lê o nome do usuário
            nome[strcspn(nome, "\n")] = 0;// Remove newline character
            printf("Senha: ");
            fgets(senha, sizeof(senha), stdin);// Lê a senha do usuário
            senha[strcspn(senha, "\n")] = 0;// Remove newline character
            int res = autenticar(nome, senha);
            if (res == 1)
                printf("Autenticado!\n");
            else if (res == 0)
                printf("Senha incorreta!\n");
            else
                printf("Usuário não encontrado!\n");
            getchar();
        } else if (opcao == 0) {
            break;// Sair do programa
        }
    }
    return 0;
}