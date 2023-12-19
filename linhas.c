// Bruno Tiago Ferreira Martins - 2022147149

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "linhas.h"
#include "paragens.h"

// Ponteiros globais para o array Linha e inteiro para armazenar o número de linhas.
Linha *linhas = NULL;
int numLinhas = 0;

// Função para encontrar uma Linha pelo nome.
Linha *encontrarLinha(char *nome) {
    // fazer a iteracao sobre todas as linhas
    for (int i = 0; i < numLinhas; i++) {
        // Se o nome da linha atual corresponder ao nome procurado, devolve a linha
        if (strcmp(linhas[i].nome, nome) == 0) {
            return &linhas[i];
        }
    }

    // Se nenhuma linha correspondente for encontrada, devolve NULL
    return NULL;
}

// Função para adicionar uma Paragem a uma Linha pelo nome da Linha e da Paragem.
void addParagempLinha(char *nomeLinha, char *nomeParagem) {
    // Buscar a linha pelo nome
    Linha *linha = encontrarLinha(nomeLinha);
    // Se a linha não for encontrada, imprimir uma mensagem de erro e devolve
    if (linha == NULL) {
        printf("Erro: Linha com esse nome não encontrada.\n");
        return;
    }

    // Encontrar a paragem pelo nome
    char codigoParagem[5];
    obterCodigoParagem(codigoParagem, nomeParagem);

    // Se a paragem não for encontrada, imprimir uma mensagem de erro e devolve
    if (strcmp(codigoParagem, "") == 0) {
        printf("Erro: Paragem com esse nome não encontrada.\n");
        return;
    }

    // Adicionar a paragem à linha
    addParagem(linha, nomeParagem, codigoParagem);
}

// Função para adicionar linhas predefinidas
void addLinhasPreDefinidas() {
    // Array de nomes de linhas predefinidos
    char *nomesLinhasPreDefinidas[] = {
            "Vermelha",
            "Azul",
            "Roxa",
            "Amarela",
    };

    // Número de linhas predefinidas
    int numLinhasPreDefinidas = sizeof(nomesLinhasPreDefinidas) / sizeof(nomesLinhasPreDefinidas[0]);

    // Array bidimensional de paragens predefinidas
    char *paragensPreDefinidas[][4] = {
            {
                    "Cantanhede",
                    "Figueira da Foz",
                    "Bifurcacao de Lares",
                    "Lourical"
            },
            {
                    "Alfarelos",
                    "Soure",
                    "Pombal",
                    "Coimbra-B"
            },
            {
                    "Coimbra",
                    "Portagem",
                    "Polo III",
                    "Condeixa-a-Nova"
            },
            {
                    "Santa Apolonia",
                    "Hospital Pediatrico",
                    "Loja do Cidadao",
                    "Quinta da Fonte"
            },

    };

    // Para cada linha predefinida...
    for (int i = 0; i < numLinhasPreDefinidas; i++) {
        // Adicionar a linha
        addLinha(nomesLinhasPreDefinidas[i]);
    }

    // Para cada linha predefinida...
    for (int i = 0; i < numLinhasPreDefinidas; i++) {
        // Para cada paragem nessa linha...
        for (int j = 0; j < 4; j++) {
            // Encontrar a linha correspondente pelo nome
            Linha *linha = encontrarLinha(nomesLinhasPreDefinidas[i]);

            // Adicionar a paragem à linha
            addParagem(linha, paragensPreDefinidas[i][j], linha->codigosParagens);
        }
    }
}

// Função para adicionar uma Linha
void addLinha(char *nome) {
    // Verificar se o nome já existe
    for (int i = 0; i < numLinhas; i++) {
        if (strcmp(linhas[i].nome, nome) == 0) {
            // Se o nome já existir, imprimir uma mensagem de erro e devolve
            printf("Erro: Linha com esse nome ja existe.\n");
            return;
        }
    }

    // Criar uma nova Linha
    Linha novaLinha;
    // Copiar o nome para o novo objeto Linha
    strcpy(novaLinha.nome, nome);
    // Inicializar os campos da nova Linha
    novaLinha.paragens = NULL;
    novaLinha.codigosParagens = NULL;
    novaLinha.contadorParagens = 0;

    // Incrementar o número de linhas
    numLinhas++;
    // Realocar o array de linhas para guardar a nova linha
    linhas = realloc(linhas, numLinhas * sizeof(Linha));
    // Adicionar a nova linha ao final do array
    linhas[numLinhas - 1] = novaLinha;

    // Imprimir uma mensagem
    printf("Linha adicionada com sucesso.\n");
}

// Função para adicionar uma Paragem a uma Linha
void addParagem(Linha *linha, char *nomeParagem, char **codigosParagens) {
    // Buscar a paragem pelo nome
    char codigoParagem[5];
    obterCodigoParagem(codigoParagem, nomeParagem);

    // Se a paragem não for encontrada, imprimir uma mensagem de erro e devolve
    if (strcmp(codigoParagem, "") == 0) {
        printf("Erro: Paragem com esse nome nao encontrada.\n");
        return;
    }

    // Verificar se a paragem já existe na linha
    for (int i = 0; i < linha->contadorParagens; i++) {
        if (strcmp(linha->paragens[i].nome, nomeParagem) == 0) {
            // Se s paragem já existe na linha, não é necessário adicioná-la novamente
            printf("A paragem '%s' já esta presente na linha.\n", nomeParagem);
            return;
        }
    }

    // Adicionar a paragem à linha
    Paragem novaParagem;
    strcpy(novaParagem.nome, nomeParagem);

    // Incrementar o número de paragens da linha
    linha->contadorParagens++;

    // Realocar os arrays de paragens e códigos para guardar a nova paragem
    linha->paragens = realloc(linha->paragens, linha->contadorParagens * sizeof(Paragem));
    linha->codigosParagens = realloc(linha->codigosParagens, linha->contadorParagens * sizeof(char *));

    // Atribuir o código existente à paragem na linha
    linha->paragens[linha->contadorParagens - 1] = novaParagem;
    linha->codigosParagens[linha->contadorParagens - 1] = malloc(5 * sizeof(char));
    strcpy(linha->codigosParagens[linha->contadorParagens - 1], codigoParagem);

    printf("Paragem '%s' adicionada com sucesso a linha.\n", nomeParagem);
}

// Função para remover uma Paragem de uma Linha pelo nome da Linha e da Paragem.
void removeParagemDeLinha(char *nomeLinha, char *nomeParagem) {
    // Procurar a linha pelo nome
    Linha *linha = encontrarLinha(nomeLinha);
    // Se a linha não for encontrada, imprimir uma mensagem de erro e devolve
    if (linha == NULL) {
        printf("Erro: Linha com esse nome nao encontrada.\n");
        return;
    }

    // Verificar se a paragem está na linha
    bool encontrada = false;
    for (int i = 0; i < linha->contadorParagens; i++) {
        if (strcmp(linha->paragens[i].nome, nomeParagem) == 0) {
            encontrada = true;
            // Remover a paragem da linha
            for (int j = i; j < linha->contadorParagens - 1; j++) {
                linha->paragens[j] = linha->paragens[j + 1];
                linha->codigosParagens[j] = linha->codigosParagens[j + 1];
            }
            break;
        }
    }

    // Se a paragem não estiver na linha, imprimir uma mensagem de erro e devolve
    if (!encontrada) {
        printf("Erro: A paragem nao pertence a linha.\n");
        return;
    }

    // Decrementar o número de paragens da linha
    linha->contadorParagens--;

    // Realocar os arrays de paragens e códigos para o novo tamanho
    linha->paragens = realloc(linha->paragens, linha->contadorParagens * sizeof(Paragem));
    linha->codigosParagens = realloc(linha->codigosParagens, linha->contadorParagens * sizeof(char *));

    printf("Paragem removida com sucesso da linha.\n");
}

// Função para atualizar uma Linha
void atualizarNomeLinha() {
    printf("\n--- Atualizar Nome Da Linha ---\n");

    // Verificar se existem linhas no sistema
    if (numLinhas == 0) {
        printf("Nao existem linhas no sistema.\n");
        return;
    }

    // Pedir o nome da linha a ser atualizada
    char nomeLinha[50];
    printf("Digite o nome da linha que deseja atualizar: ");
    fgets(nomeLinha, sizeof(nomeLinha), stdin);
    nomeLinha[strcspn(nomeLinha, "\n")] = '\0'; // Remover a nova linha do fim do nome da linha

    // Encontrar a linha pelo nome
    Linha *linha = encontrarLinha(nomeLinha);

    // Verificar se a linha foi encontrada
    if (linha == NULL) {
        printf("Linha nao encontrada.\n");
        return;
    }

    // Pedir o novo nome da linha
    char novoNome[50];
    printf("Digite o novo nome da linha: ");
    fgets(novoNome, sizeof(novoNome), stdin);
    novoNome[strcspn(novoNome, "\n")] = '\0'; // Remover a nova linha do fim do novo nome

    // Verificar se o novo nome já existe
    for (int i = 0; i < numLinhas; i++) {
        if (strcmp(linhas[i].nome, novoNome) == 0) {
            // Se o nome já existir, imprimir uma mensagem de erro e devolve
            printf("Erro: Linha com esse nome ja existe.\n");
            return;
        }
    }

    // Atualizar o nome da linha
    strcpy(linha->nome, novoNome);

    printf("Linha atualizada com sucesso.\n");
}

void removeLinha() {
    printf("\n--- Remover Linha ---\n");
    char nomeLinha[50];
    printf("Digite o nome da linha que deseja remover: ");
    fgets(nomeLinha, sizeof(nomeLinha), stdin);
    nomeLinha[strcspn(nomeLinha, "\n")] = '\0'; // Remover a nova linha do fim do nome da linha

    // Procurar a linha pelo nome
    int indiceLinha = (int) encontrarLinha(nomeLinha);

    if (indiceLinha == -1) {
        printf("A linha '%s' nao existe.\n", nomeLinha);
    } else {
        // Remover a linha e reorganizar as linhas restantes
        for (int i = indiceLinha; i < numLinhas - 1; i++) {
            linhas[i] = linhas[i + 1];
        }
        numLinhas--;

        printf("A linha '%s' foi removida com sucesso.\n", nomeLinha);
    }
}

// Função para visualizar todas as Linhas
void mostrarLinhas() {
    printf("\n--- Visualizar Linhas ---\n");

    // Se não existirem linhas, imprimir uma mensagem e devolve
    if (numLinhas == 0) {
        printf("Nao existem linhas registadas.\n");
        return;
    }

    // Para cada Linha...
    for (int i = 0; i < numLinhas; i++) {
        // Imprimir o nome da Linha e o número de Paragens
        printf("Linha: %s\n", linhas[i].nome);
        printf("Numero de paragens: %d\n", linhas[i].contadorParagens);

        // imprimir as Paragens da Linha
        printf("Paragens:\n");
        for (int j = 0; j < linhas[i].contadorParagens; j++) {
            // imprimir o nome e o código de cada Paragem
            printf("- Nome: %s\n", linhas[i].paragens[j].nome);
            printf("  Codigo: %s\n", linhas[i].codigosParagens[j]);
        }

        printf("\n");
    }
}