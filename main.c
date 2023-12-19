// Bruno Tiago Ferreira Martins - 2022147149
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "gui.h"
#include "paragens.h"
#include "main.h"
#include "linhas.h"

// Função não implementada
void calcularPercursos() {
    printf("\nFuncao nao implementada\n");
}

// Função que guarda os dados inseridos pelo utilizador
void guardarDados() {
    printf("\n--- Guardar Dados ---\n");

    // Perguntar ao utilizador se ele deseja salvar os dados num Ficheiro de texto ou binário
    int opcao;
    mostrarMenuGuardarFicheiro();
    scanf("%d", &opcao);

    // Opções de escolha para o utilizador
    switch (opcao) {
        case 1:
            guardarDadosTexto(); // Guarda os dados num Ficheiro de texto
            break;
        case 2:
            guardarDadosBinario(); // Guarda os dados num Ficheiro binário
            break;
        case 3:
            printf("Voltando ao Menu Principal.\n"); // Volta ao menu principal
            break;
        default:
            printf("Opçao invalida. Tente novamente.\n"); // Caso o utilizador escolha uma opção inválida
            break;
    }
}

// Função que guarda os dados num Ficheiro de texto
// Função que guarda os dados num Ficheiro de texto
void guardarDadosTexto() {
    // Abrir o Ficheiro de texto para escrita
    FILE *file = fopen("data.txt", "w");
    if (file == NULL) {
        printf("Erro ao abrir o Ficheiro.\n");
        return;
    }

    // Escrever os dados das linhas e paragens no Ficheiro de texto
    for (int i = 0; i < numLinhas; i++) {
        fprintf(file, "%s\n", linhas[i].nome);

        // Escrever os dados das paragens da linha
        for (int j = 0; j < linhas[i].contadorParagens; j++) {
            fprintf(file, "%s #%s\n", linhas[i].paragens[j].nome, linhas[i].codigosParagens[j]);
        }

        fprintf(file, "\n"); // Adicionar uma linha em branco entre cada linha de paragens
    }

    fclose(file); // Fechar o Ficheiro

    printf("Dados guardados em Ficheiro de texto com sucesso.\n");
}

// Função que guarda os dados num Ficheiro binário
void guardarDadosBinario() {
    // Abrir o Ficheiro binário para escrita
    FILE *file = fopen("data.bin", "wb");
    if (file == NULL) {
        printf("Erro ao abrir o Ficheiro.\n");
        return;
    }

    // Escrever os dados das linhas no Ficheiro binário
    for (int i = 0; i < numLinhas; i++) {
        fwrite(&linhas[i], sizeof(Linha), 1, file);

        // Escrever os códigos alfanuméricos das paragens
        for (int j = 0; j < linhas[i].contadorParagens; j++) {
            fwrite(linhas[i].paragens[j].codigo, sizeof(char), 5, file);
        }
    }

    fclose(file); // Fechar o Ficheiro

    printf("Dados guardados em Ficheiro binario com sucesso.\n");
}

// Função que adiciona uma linha de um Ficheiro de texto (incompleta/nao implementada)
void addLinhaDeFicheiro(const char *nomeFicheiro) {
    /*   FILE *file = fopen(nomeFicheiro, "r");
       if (file == NULL) {
           printf("Erro ao abrir o Ficheiro.\n");
           return;
       }
       fclose(file);
   */
    printf("Funcao nao implementada\n");
}


// Função principal que controla o programa
int main() {

    adicionarParagensPreDefinidas();
    addLinhasPreDefinidas();
    system("cls");


    bool sair = false; // Variável para controlar a saída do loop principal
    int opcao;

    // Loop principal do programa
    while (!sair) {
        mostrarmenuprin();
        scanf("%d", &opcao);
        getchar(); // Limpar o buffer do teclado

        switch (opcao) {
            // Caso 1 - Trabalhar com paragens
            case 1:
                // Loop secundário para coisas relacionadas a paragens
                while (true) {
                    mostramenuparagens();
                    scanf("%d", &opcao);
                    getchar(); // Limpar o buffer do teclado

                    // Escolher as opcoes para paragens
                    switch (opcao) {
                        case 1:
                            registarParagem(); // registar uma nova paragem
                            break;
                        case 2:
                            eliminarParagem(); // Eliminar uma paragem existente
                            break;
                        case 3:
                            visualizarParagens(); // Visualizar todas as paragens
                            break;
                        case 4:
                            break; // Sair do menu de paragens
                        default:
                            printf("Opção invalida. Tente novamente.\n");
                            break;
                    }

                    // Sai do loop secundário quando a opção é 4
                    if (opcao == 4) {
                        break;
                    }
                }
                break;

                // Caso 2 - Trabalhar com linhas
            case 2:
                // Loop secundário para coisas relacionadas a linhas
                while (true) {
                    mostrarMenuLinhas();
                    scanf("%d", &opcao);
                    getchar(); // Limpar o buffer do teclado

                    // Escolhas de opcoes para linhas
                    switch (opcao) {
                        case 1: {
                            char nome_da_linha[50];
                            printf("Insira o nome da linha: ");
                            fgets(nome_da_linha, sizeof(nome_da_linha), stdin);
                            nome_da_linha[strcspn(nome_da_linha,
                                                  "\n")] = '\0'; // Remove a nova linha do fim do nome_da_linha
                            addLinha(nome_da_linha); // Adiciona uma nova linha
                            break;
                        }
                        case 2:
                            atualizarNomeLinha(); // Atualizar uma linha existente
                            break;
                        case 3: {
                            char nome_da_linha[50];
                            char nome_da_paragem[50];
                            printf("Insira o nome da linha: ");
                            fgets(nome_da_linha, sizeof(nome_da_linha), stdin);
                            nome_da_linha[strcspn(nome_da_linha,
                                                  "\n")] = '\0'; // Remover a nova linha do fim do nome_da_linha
                            printf("Insira o nome da paragem: ");
                            fgets(nome_da_paragem, sizeof(nome_da_paragem), stdin);
                            nome_da_paragem[strcspn(nome_da_paragem,
                                                    "\n")] = '\0'; // Remover a nova linha do fim do nome_da_paragem
                            addParagempLinha(nome_da_linha, nome_da_paragem); // Adicionar uma paragem a uma linha
                            break;
                        }
                        case 4: {
                            char nomeLinha[50];
                            printf("Digite o nome da linha: ");
                            fgets(nomeLinha, sizeof(nomeLinha), stdin);
                            nomeLinha[strcspn(nomeLinha, "\n")] = '\0'; // Remover a nova linha do fim do nome da linha

                            char nomeParagem[50];
                            printf("Digite o nome da paragem: ");
                            fgets(nomeParagem, sizeof(nomeParagem), stdin);
                            nomeParagem[strcspn(nomeParagem,
                                                "\n")] = '\0'; // Remover a nova linha do fim do nome da paragem

                            removeParagemDeLinha(nomeLinha, nomeParagem); // Remover uma paragem da linha
                            break;
                        }
                        case 5:
                            mostrarLinhas(); // Visualizar todas as linhas
                            break;
                        case 6:
                            removeLinha(); // Remover uma linha existente
                            break;
                        case 7: {
                            char nomeFicheiro[100];
                            printf("Insira o nome do Ficheiro de texto: ");
                            fgets(nomeFicheiro, sizeof(nomeFicheiro), stdin);
                            nomeFicheiro[strcspn(nomeFicheiro,
                                                 "\n")] = '\0'; // Remover a nova linha do fim do nomeFicheiro
                            addLinhaDeFicheiro(nomeFicheiro); // Adicionar uma linha de um Ficheiro
                            opcao = 7; // Atualizar o valor da opção
                            break;
                        }
                        case 8: {
                            break;
                        };
                        default:
                            printf("Opcao invalida. Tente novamente.\n");
                            break;
                    }

                    // Sai do loop secundário quando a opção é 8
                    if (opcao == 8) {
                        break;
                    }
                }
                break;

                // Caso 3 - Calcular percursos (nao implementado)
            case 3:
                while (true) {
                    mostrarMenuCalculoPercursos();
                    scanf("%d", &opcao);
                    getchar(); // Limpar o buffer do teclado

                    // Escolhas de opcoes para o cálculo de percursos
                    switch (opcao) {
                        case 1:
                            calcularPercursos(); // Calcular percursos
                            break;
                        case 2:
                            break; // Sair do menu de cálculo de percursos
                        default:
                            printf("Opcao invalida. Tente novamente.\n"); // Opção inválida
                            break;
                    }

                    // Sai do loop secundário quando a opção é 2
                    if (opcao == 2) {
                        break;
                    }
                }
                break;

                // Caso 4 - Guardar dados
            case 4:
                // Loop secundário para coisas relacionadas à gravação de dados
                while (true) {
                    mostrarMenuGuardarFicheiro();
                    scanf("%d", &opcao);
                    getchar(); // Limpar o buffer do teclado

                    // Escolhas de opcoes para a gravação de dados
                    switch (opcao) {
                        case 1:
                            guardarDadosTexto(); // Gravar dados num Ficheiro de texto
                            break;
                        case 2:
                            guardarDadosBinario(); // Gravar dados num Ficheiro binário
                            break;
                        case 3:
                            break; // Sair do menu de gravação de dados
                        default:
                            printf("Opçao invalida. Tente novamente.\n"); // Opção inválida
                            break;
                    }

                    // Sai do loop secundário quando a opção é 3
                    if (opcao == 3) {
                        break;
                    }
                }
                break;

                // Caso 5 - Sair do programa
            case 5:
                sair = true; // Encerra o loop principal
                break;

            default:
                printf("Opç¡cao invalida. Tente novamente.\n"); // Opção inválida
                break;
        }
    }

    printf("\nObrigado por utilizar o metro mondego, contribuindo para um futuro mais sustentavel!\n"); //escrever mensagem de finalizacao de programa

    return 0;
}