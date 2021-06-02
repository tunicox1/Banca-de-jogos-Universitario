#ifndef APOSTAS_H_INCLUDED
#define APOSTAS_H_INCLUDED
#include "../Jogo/jogo.h"
#include "../Usuario/Usuario.h"
#include "../Jogo/ArvBinJogo/ArvBinJogo.h"

typedef struct aposta Aposta;

void menuAposta(Usuario* user);

Aposta* cria_aposta( Aposta *Ap,Arv* jogos,Usuario* user);

void imprimeAposta(Aposta *Ap,Arv* jogos,Usuario* user);

void atualizarApostas( Aposta *Ap,Arv* jogos,Usuario *user);

void salvar_apostas(Aposta *Ap);

Aposta* lerApostas();

int geraIdAposta(Aposta*Ap);


#endif // APOSTAS_H_INCLUDED
