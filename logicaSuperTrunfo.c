#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define MAX_CARTAS 20

// Estrutura da Carta
typedef struct {
    char codigo[5];
    char nome[50];
    char estado[3];
    long long populacao;
    double area;
    long long pib;
    int pontosTuristicos;
    double densidadePopulacional;
    double pibPerCapita;
} Carta;

// Protótipos de funções
void cadastrarCarta(Carta *carta, int numeroCarta);
void calcularPropriedades(Carta *carta);
void exibirCarta(Carta carta);
void compararCartasNovato(Carta carta1, Carta carta2);
void menuAventureiro(Carta *cartas, int numCartas);
void menuMestre(Carta *cartas, int numCartas);
void compararCartas(Carta carta1, Carta carta2, int atributo);
void limparBuffer();

// Função principal
int main() {
    setlocale(LC_ALL, "Portuguese");
    
    Carta cartas[MAX_CARTAS];
    int numCartas = 0;
    int opcao;

    while (1) {
        printf("\n--- Super Trunfo: Jogo de Cartas de Cidades ---\n");
        printf("1. Cadastrar Cartas\n");
        printf("2. Nível Novato: Comparação Simples\n");
        printf("3. Nível Aventureiro: Menu de Comparação\n");
        printf("4. Nível Mestre: Comparação Avançada\n");
        printf("5. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1:
                printf("Quantas cartas deseja cadastrar? (máx. %d): ", MAX_CARTAS);
                scanf("%d", &numCartas);
                limparBuffer();

                for (int i = 0; i < numCartas; i++) {
                    cadastrarCarta(&cartas[i], i+1);
                    calcularPropriedades(&cartas[i]);
                }
                break;

            case 2: // Nível Novato
                if (numCartas < 2) {
                    printf("Cadastre pelo menos 2 cartas primeiro!\n");
                    break;
                }
                compararCartasNovato(cartas[0], cartas[1]);
                break;

            case 3: // Nível Aventureiro
                if (numCartas < 2) {
                    printf("Cadastre pelo menos 2 cartas primeiro!\n");
                    break;
                }
                menuAventureiro(cartas, numCartas);
                break;

            case 4: // Nível Mestre
                if (numCartas < 2) {
                    printf("Cadastre pelo menos 2 cartas primeiro!\n");
                    break;
                }
                menuMestre(cartas, numCartas);
                break;

            case 5:
                printf("Encerrando o programa...\n");
                return 0;

            default:
                printf("Opção inválida!\n");
        }
    }

    return 0;
}

// Função para cadastrar carta
void cadastrarCarta(Carta *carta, int numeroCarta) {
    printf("\n--- Cadastro da Carta %d ---\n", numeroCarta);
    
    sprintf(carta->codigo, "%c%02d", 'A' + ((numeroCarta-1)/4), ((numeroCarta-1)%4) + 1);
    strcpy(carta->estado, carta->codigo);

    printf("Nome da cidade: ");
    fgets(carta->nome, sizeof(carta->nome), stdin);
    carta->nome[strcspn(carta->nome, "\n")] = 0;

    printf("População: ");
    scanf("%lld", &carta->populacao);
    limparBuffer();

    printf("Área (km²): ");
    scanf("%lf", &carta->area);
    limparBuffer();

    printf("PIB: ");
    scanf("%lld", &carta->pib);
    limparBuffer();

    printf("Pontos Turísticos: ");
    scanf("%d", &carta->pontosTuristicos);
    limparBuffer();
}

// Calcular propriedades derivadas
void calcularPropriedades(Carta *carta) {
    carta->densidadePopulacional = carta->populacao / carta->area;
    carta->pibPerCapita = (double)carta->pib / carta->populacao;
}

// Exibir carta
void exibirCarta(Carta carta) {
    printf("\nCarta: %s\n", carta.codigo);
    printf("Cidade: %s\n", carta.nome);
    printf("Estado: %s\n", carta.estado);
    printf("População: %lld\n", carta.populacao);
    printf("Área: %.2f km²\n", carta.area);
    printf("PIB: R$ %lld\n", carta.pib);
    printf("Pontos Turísticos: %d\n", carta.pontosTuristicos);
    printf("Densidade Populacional: %.2f hab/km²\n", carta.densidadePopulacional);
    printf("PIB per Capita: R$ %.2f\n", carta.pibPerCapita);
}

// Comparação Nível Novato
void compararCartasNovato(Carta carta1, Carta carta2) {
    printf("\n--- Comparação de Cartas (Nível Novato) ---\n");
    exibirCarta(carta1);
    exibirCarta(carta2);

    // Comparação por população
    Carta vencedor = carta1.populacao > carta2.populacao ? carta1 : carta2;
    printf("\nCarta vencedora por População: %s\n", vencedor.nome);
}

// Menu Nível Aventureiro
void menuAventureiro(Carta *cartas, int numCartas) {
    int escolha, carta1, carta2;

    printf("\n--- Menu de Comparação (Nível Aventureiro) ---\n");
    printf("Escolha o atributo para comparação:\n");
    printf("1. População\n");
    printf("2. Área\n");
    printf("3. PIB\n");
    printf("4. Pontos Turísticos\n");
    printf("5. Densidade Populacional\n");
    printf("Opção: ");
    scanf("%d", &escolha);
    limparBuffer();

    printf("Escolha duas cartas para comparar (1 a %d): ", numCartas);
    scanf("%d %d", &carta1, &carta2);
    limparBuffer();

    if (carta1 < 1 || carta1 > numCartas || carta2 < 1 || carta2 > numCartas) {
        printf("Cartas inválidas!\n");
        return;
    }

    compararCartas(cartas[carta1-1], cartas[carta2-1], escolha);
}

// Comparação de cartas
void compararCartas(Carta carta1, Carta carta2, int atributo) {
    printf("\n--- Comparação de Cartas ---\n");
    exibirCarta(carta1);
    exibirCarta(carta2);

    switch (atributo) {
        case 1: // População
            printf("\nVencedor: %s\n", 
                carta1.populacao > carta2.populacao ? carta1.nome : carta2.nome);
            break;
        case 2: // Área
            printf("\nVencedor: %s\n", 
                carta1.area > carta2.area ? carta1.nome : carta2.nome);
            break;
        case 3: // PIB
            printf("\nVencedor: %s\n", 
                carta1.pib > carta2.pib ? carta1.nome : carta2.nome);
            break;
        case 4: // Pontos Turísticos
            printf("\nVencedor: %s\n", 
                carta1.pontosTuristicos > carta2.pontosTuristicos ? carta1.nome : carta2.nome);
            break;
        case 5: // Densidade Populacional
            printf("\nVencedor: %s\n", 
                carta1.densidadePopulacional < carta2.densidadePopulacional ? carta1.nome : carta2.nome);
            break;
        default:
            printf("Atributo inválido!\n");
    }
}

// Menu Nível Mestre
void menuMestre(Carta *cartas, int numCartas) {
    int escolha1, escolha2, carta1, carta2;

    printf("\n--- Comparação Avançada (Nível Mestre) ---\n");
    printf("Escolha o primeiro atributo:\n");
    printf("1. População\n2. Área\n3. PIB\n4. Pontos Turísticos\n5. Densidade Populacional\n");
    scanf("%d", &escolha1);
    limparBuffer();

    printf("Escolha o segundo atributo:\n");
    printf("1. População\n2. Área\n3. PIB\n4. Pontos Turísticos\n5. Densidade Populacional\n");
    scanf("%d", &escolha2);
    limparBuffer();

    printf("Escolha duas cartas para comparar (1 a %d): ", numCartas);
    scanf("%d %d", &carta1, &carta2);
    limparBuffer();

    if (carta1 < 1 || carta1 > numCartas || carta2 < 1 || carta2 > numCartas) {
        printf("Cartas inválidas!\n");
        return;
    }

    Carta c1 = cartas[carta1-1];
    Carta c2 = cartas[carta2-1];

    // Comparação com dois atributos usando operadores ternários
    Carta vencedor = (
        (escolha1 == 1 && c1.populacao > c2.populacao) || 
        (escolha1 == 2 && c1.area > c2.area) || 
        (escolha1 == 3 && c1.pib > c2.pib) || 
        (escolha1 == 4 && c1.pontosTuristicos > c2.pontosTuristicos) || 
        (escolha1 == 5 && c1.densidadePopulacional < c2.densidadePopulacional)
    ) ? c1 : c2;

    printf("\nCarta vencedora considerando os atributos escolhidos: %s\n", vencedor.nome);
}

// Função para limpar buffer de entrada
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}