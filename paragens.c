// Bruno Tiago Ferreira Martins - 2022147149

#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include "paragens.h"

#include "linhas.h"

// Definição global das paragens
Paragem *paragens = NULL; // Array dinâmico de Paragem (estrutura definida em paragens.h)
int contadorParagens = 0; // Contador do número de paragens registradas

// Função para gerar um código alfanumérico aleatório
void gerarCodigo(char *codigo) {
    // String contendo todos os possíveis caracteres para o código
    const char *caracteres = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    int tamanho = strlen(caracteres);

    // Gera 4 caracteres aleatórios a partir do array de caracteres
    for (int i = 0; i < 4; i++) {
        codigo[i] = caracteres[rand() % tamanho];
    }

    // Termina a string do código com o caracter nulo
    codigo[4] = '\0';
}

// Função para obter o código da paragem a partir do seu nome
void obterCodigoParagem(char *codigo, const char *nomeParagem) {
    // Percorre todas as paragens registradas
    for (int i = 0; i < contadorParagens; i++) {
        // Se o nome da paragem atual é igual ao nome fornecido
        if (strcmp(paragens[i].nome, nomeParagem) == 0) {
            // Copia o código da paragem para a string de saída e retorna
            strcpy(codigo, paragens[i].codigo);
            return;
        }
    }

    // Se a paragem não foi encontrada, a string de saída fica vazia
    strcpy(codigo, "");
}

// Função para registar uma nova paragem
void registarParagem() {
    printf("\n--- Registar Paragem ---\n");

    // Obtém o nome da nova paragem
    char nome[50];
    printf("Nome da paragem: ");
    fgets(nome, sizeof(nome), stdin); // Lê a entrada do utilizador
    nome[strcspn(nome, "\n")] = '\0'; // Remove o caractere de nova linha da entrada

    // Verifica se já existe uma paragem com esse nome
    for (int i = 0; i < contadorParagens; i++) {
        if (strcmp(paragens[i].nome, nome) == 0) {
            printf("Erro: Paragem com esse nome ja existe.\n");
            return;
        }
    }

    // Gera um código alfanumérico para a nova paragem
    char codigo[5];
    int codigoExiste;
    do {
        gerarCodigo(codigo);
        codigoExiste = 0;
        for (int i = 0; i < contadorParagens; i++) {
            if (strcmp(paragens[i].codigo, codigo) == 0) {
                codigoExiste = 1;
                break;
            }
        }
    } while (codigoExiste);

    // Cria a nova paragem
    Paragem novaParagem;
    strcpy(novaParagem.nome, nome);
    strcpy(novaParagem.codigo, codigo);
    novaParagem.numLinhasTotais = 0;
    novaParagem.linhas = NULL;

    // Adiciona a nova paragem ao array de paragens
    contadorParagens++; // Incrementa o número de paragens
    paragens = realloc(paragens, contadorParagens * sizeof(Paragem)); // Realoca o array de paragens
    paragens[contadorParagens - 1] = novaParagem; // Adiciona a nova paragem ao final do array

    printf("Paragem registada com sucesso.\n");
}


// Função para eliminar uma paragem
void eliminarParagem() {
    printf("\n--- Eliminar Paragem ---\n");

    // Verifica se existem paragens registradas
    if (contadorParagens == 0) {
        printf("Erro: Nao existem paragens registadas.\n");
        return;
    }

    // Obtém o nome da paragem a ser eliminada
    char nome[50];
    printf("Nome da paragem a eliminar: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    // Procura a paragem pelo nome
    int indiceParagem = -1;
    for (int i = 0; i < contadorParagens; i++) {
        // Se encontrou a paragem, guarda o seu índice
        if (strcmp(paragens[i].nome, nome) == 0) {
            indiceParagem = i;
            break;
        }
    }

    // Se a paragem não foi encontrada, exibe uma mensagem de erro e retorna
    if (indiceParagem == -1) {
        printf("Erro: Paragem com esse nome nao encontrada.\n");
        return;
    }

    // Se a paragem está associada a uma ou mais linhas, não pode ser eliminada
    for (int i = 0; i < numLinhas; i++) {
        Linha linha = linhas[i];
        for (int j = 0; j < linha.contadorParagens; j++) {
            if (strcmp(linha.paragens[j].nome, nome) == 0) {
                printf("Erro: A paragem esta associada a uma ou mais linhas. Nao pode ser removida.\n");
                return;
            }
        }
    }

    // Move todas as paragens para a esquerda, começando na posição do índice da paragem a ser eliminada
    for (int i = indiceParagem; i < contadorParagens - 1; i++) {
        paragens[i] = paragens[i + 1];
    }

    // Decrementa o número de paragens e realoca o array de paragens
    contadorParagens--;
    paragens = realloc(paragens, contadorParagens * sizeof(Paragem));
    // Se houve um erro na realocação de memória e ainda existem paragens, termina o programa
    if (!paragens && contadorParagens > 0) {
        printf("Erro: Falha ao realocar memoria.\n");
        exit(EXIT_FAILURE);
    }

    printf("Paragem removida com sucesso.\n");
}

// Função para adicionar paragens pré-definidas
void adicionarParagensPreDefinidas() {
    // Array com os nomes das paragens pré-definidas
    char *paragensPreDefinidas[] = {
            "Cantanhede",
            "Figueira da Foz",
            "Bifurcacao de Lares",
            "Lourical",
            "Alfarelos",
            "Soure",
            "Pombal",
            "Coimbra-B",
            "Coimbra",
            "Portagem",
            "Polo III",
            "Condeixa-a-Nova",
            "Santa Apolonia",
            "Hospital Pediatrico",
            "Loja do Cidadao",
            "Quinta da Fonte"
    };

    int contadorParagensPreDefinidas = sizeof(paragensPreDefinidas) / sizeof(paragensPreDefinidas[0]);

    // Para cada paragem pré-definida
    for (int i = 0; i < contadorParagensPreDefinidas; i++) {
        // Gera um código alfanumérico para a paragem
        char codigo[5];
        gerarCodigo(codigo);

        // Cria a nova paragem
        Paragem novaParagem;
        strcpy(novaParagem.nome, paragensPreDefinidas[i]);
        strcpy(novaParagem.codigo, codigo);
        novaParagem.numLinhasTotais = 0;
        novaParagem.linhas = NULL;

        // Adiciona a nova paragem ao array de paragens
        contadorParagens++;
        paragens = realloc(paragens, contadorParagens * sizeof(Paragem));
        paragens[contadorParagens - 1] = novaParagem;
    }
}


// Função para visualizar todas as paragens
// Função para visualizar todas as paragens
// Função para visualizar todas as paragens
void visualizarParagens() {
    printf("\n--- Visualizar Paragens ---\n");

    // Se não existem paragens, exibe uma mensagem e retorna
    if (contadorParagens == 0) {
        printf("Nao existem paragens registadas.\n");
        return;
    }

    // Para cada paragem, exibe o nome, código e linhas associadas
    for (int i = 0; i < contadorParagens; i++) {
        printf("Nome: %s\n", paragens[i].nome);
        printf("Codigo: %s\n", paragens[i].codigo);
        printf("Linhas:");

        int numLinhasAssociadas = 0; // Contador para o número de linhas associadas à paragem

        // Percorre todas as linhas para verificar se a paragem está associada
        for (int j = 0; j < numLinhas; j++) {
            Linha linha = linhas[j];

            // Verifica se a paragem está associada à linha
            for (int k = 0; k < linha.contadorParagens; k++) {
                if (strcmp(linha.paragens[k].nome, paragens[i].nome) == 0) {
                    printf(" %s", linha.nome);
                    numLinhasAssociadas++;
                    break; // Sai do loop interno assim que a paragem for encontrada na linha
                }
            }
        }

        // Se não houver linhas associadas, exibe "Nenhuma"
        if (numLinhasAssociadas == 0) {
            printf(" Nenhuma");
        }

        printf("\n\n");
    }
}