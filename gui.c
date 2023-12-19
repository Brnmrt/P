// Bruno Tiago Ferreira Martins - 2022147149

#include "gui.h"

void mostrarmenuprin() {
    printf("---- Menu Principal ----\n");
    printf("1. Paragens\n");
    printf("2. Linhas\n");
    printf("3. Calculo de Percursos\n");
    printf("4. Guardar Dados\n");
    printf("5. Sair\n");
    printf("Escolha uma opcao: ");
}

void mostramenuparagens() {
    printf("\n---- Menu Paragens ----\n");
    printf("1. Registar Paragem\n");
    printf("2. Eliminar Paragem\n");
    printf("3. Visualizar Paragens\n");
    printf("4. Voltar ao Menu Principal\n");
    printf("Escolha uma opcao: ");
}

void mostrarMenuLinhas() {
    printf("\n---- Menu Linhas ----\n");
    printf("1. Adicionar Linha\n");
    printf("2. Atualizar Nome Da Linha\n");
    printf("3. Adicionar Paragem a Linha\n");
    printf("4. Remover Paragem da Linha\n");
    printf("5. Visualizar Linhas\n");
    printf("6. Remover Linha\n");
    printf("7. Adicionar Linha a partir de Ficheiro\n");
    printf("8. Voltar ao Menu Principal\n");
    printf("Escolha uma opcao: ");
}


void mostrarMenuCalculoPercursos() {
    printf("\n---- Menu Calculo de Percursos ----\n");
    printf("1. Calcular Percursos\n");
    printf("2. Voltar ao Menu Principal\n");
    printf("Escolha uma opcao: ");
}

void mostrarMenuGuardarFicheiro() {
    printf("\n---- Menu Guardar Dados ----\n");
    printf("1. Guardar em Ficheiro de texto\n");
    printf("2. Guardar em Ficheiro binario\n");
    printf("3. Voltar ao Menu Principal\n");
    printf("Escolha uma opcao: ");
}