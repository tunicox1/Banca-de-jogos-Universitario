#ifndef JOGO_H_INCLUDED
#define JOGO_H_INCLUDED
#include "../Usuario/Usuario.h"


typedef struct jogo Jogo;

void Menu(int nivelDeAcesso);

void menuJogo(Usuario* user);

Jogo* lerJogos();

Jogo* criarJogo(
                int id,
                int status,
                char* campeonato,
                char* timeCasa,
                char* timeFora,
                int golsCasa,
                int golsFora,
                float valorCasa,
                float valorFora,
                float valorEmpate
                );

void imprimeJogosEncerrados(Jogo* j);

void imprimeJogosEmdamento(Jogo* j);

void imprimeCamepeonatos(Jogo* j, char* campeonato);

void imprimirJogos(Jogo* j);

float getValorCasa(Jogo* j);

float getValorFora(Jogo* j);

float getValorEmpate(Jogo* j);

int getIdJogo(Jogo* j);

int gerarIdJogo();

char* getTimeCasa(Jogo* j);

char* getTimeFora(Jogo* j);

char* getCampeonato(Jogo* j);

int getStatusJogo(Jogo* j);

int getGolsCasa(Jogo* j);

int getGolsFora(Jogo* j);

void salvaJogos(Jogo* j);

void atualizarDadosJogos(Jogo* j,char* opcao);

void alteraJogos(Jogo* j);

//funcoes para vetor normal
int contJogosArquivo();

Jogo* lerDadosJogos();

void imprimeJogoNaAposta(Jogo* j);

Jogo* retornaIndiceJogo(Jogo* j, int indice);

void modificarJogo(Jogo* j);
#endif // JOGO_H_INCLUDED
