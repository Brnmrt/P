// Bruno Tiago Ferreira Martins - 2022147149

#ifndef TRABALHO_PROGRAMACAO_PARAGENS_H
#define TRABALHO_PROGRAMACAO_PARAGENS_H

typedef struct Paragem {
    char nome[50];
    char codigo[5];
    char ** linhas;
    int numLinhasTotais;
}Paragem;

void gerarCodigo(char * codigo);
void obterCodigoParagem(char * codigo, const char * nomeParagem);
void registarParagem();
void eliminarParagem();
void visualizarParagens();
void adicionarParagensPreDefinidas();
void atualizarCodigoParagem(const char * nomeParagem, const char * novoCodigo);

#endif //TRABALHO_PROGRAMACAO_PARAGENS_H