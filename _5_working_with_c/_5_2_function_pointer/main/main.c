#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da estrutura (sem function pointer dentro dela)
typedef struct {
    char firstName[20];
    char lastName[20];
    int  age;
} Person;

// Tipo do callback (deixa mais legível)
//typedef void (*PersonCallback)(Person *person);

// Função que "simula" conexão + aloca + preenche + chama o callback
void connectAndGetInfo(const char *url, void (*callback)(Person *person))
{
    // Aloca a estrutura dentro da função (como você pediu)
    Person *person = malloc(sizeof(Person));
    if (person == NULL) {
        printf("Erro: malloc falhou\n");
        return;
    }

    // Limpa a memória para evitar lixo
    memset(person, 0, sizeof(Person));

    // Simula obtenção de dados (no lugar de uma requisição HTTP real)
    strncpy(person->firstName, "Augusto", sizeof(person->firstName) - 1);
    person->firstName[sizeof(person->firstName)-1] = '\0';

    strncpy(person->lastName, "Cavalcanti", sizeof(person->lastName) - 1);
    person->lastName[sizeof(person->lastName)-1] = '\0';

    person->age = 66;

    printf("[connectAndGetInfo] Simulando conexão para: %s\n", url);
    printf("[connectAndGetInfo] Dados obtidos → chamando callback...\n");

    // Chama o callback passando o Person alocado
    // note que person é um pointer para a memória alocada
    callback(person);

    // Importante: quem aloca → quem libera (neste caso a função)
    // Mas atenção: se o callback quisesse guardar o ponteiro,
    // isso causaria use-after-free. Por isso o comentário abaixo.
    free(person);

    printf("[connectAndGetInfo] Memória liberada\n\n");
}

// =============================================
// Exemplos de callbacks diferentes
// =============================================

void imprimirDadosSimples(Person *p)
{
    printf("  Callback SIMPLES:\n");
    printf("  Nome: %s %s\n", p->firstName, p->lastName);
    printf("  Idade: %d anos\n\n", p->age);
}

void imprimirDadosFormatado(Person *p)
{
    printf("  Callback FORMATADO:\n");
    printf("  --------------------------------\n");
    printf("     Pessoa cadastrada:\n");
    printf("     Nome completo: %s %s\n", p->firstName, p->lastName);
    printf("     Idade.......: %d\n", p->age);
    printf("  --------------------------------\n\n");
}

void imprimirSomentePrimeiroNome(Person *p)
{
    printf("  Callback SÓ PRIMEIRO NOME:\n");
    printf("  Olá, %s!\n\n", p->firstName);
}

// =============================================
// Uso no main / app_main
// =============================================
void app_main(void)   // ou void app_main(void) no ESP-IDF
{
    printf("=== Testando connectAndGetInfo com diferentes callbacks ===\n\n");

    // Chamada 1 - callback simples
    connectAndGetInfo("https://api.exemplo.com/user/123", imprimirDadosSimples);

    // Chamada 2 - callback formatado
    connectAndGetInfo("https://api.exemplo.com/user/456", imprimirDadosFormatado);

    // Chamada 3 - callback diferente
    connectAndGetInfo("https://api.exemplo.com/user/789", imprimirSomentePrimeiroNome);

    
}