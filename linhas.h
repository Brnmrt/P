// Bruno Tiago Ferreira Martins - 2022147149

#ifndef TRABALHO_PROGRAMACAO_LINHAS_H
#define TRABALHO_PROGRAMACAO_LINHAS_H

#include "paragens.h"

typedef struct Linha {
    char nome[50];
    char **codigosParagens;
    int contadorParagens;
    Paragem *paragens;
}Linha;

extern Linha *linhas;
extern int numLinhas;

void addLinha(char *nome);
void addParagem(Linha *linha, char *nomeParagem, char **pString);
void addLinhasPreDefinidas();
void removeLinha();
void atualizarNomeLinha();
void mostrarLinhas();
Linha *encontrarLinha(char *nome);
void addParagempLinha(char *nomeLinha, char *nomeParagem);
void removeParagemDeLinha(char *nomeLinha, char *nomeParagem);

#endif    // TRABALHO_PROGRAMACAO_LINHAS_H