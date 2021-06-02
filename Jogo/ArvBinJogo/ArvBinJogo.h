#ifndef ARVBIN_H_INCLUDED
#define ARVBIN_H_INCLUDED
#include "../Jogo.h"

typedef struct arvno ArvNo;
typedef struct arv Arv;

Arv* jj_cria_jogo();

void jj_insere_jogo(
                    Arv* jogo_no,
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

void jj_imprime(Arv* jogo_no);

void jj_imprime_andamento(Arv* jogo_no);

void jj_imprime_encerrados(Arv* jogo_no);

void jj_imprime_campeonato(Arv* jogo_no, char* campeonato);

void jj_retira_jogo(Arv* jogo_no, char* campeonato);

void jj_atualizarJogo(Arv* jogo_no);

void jj_jogo_salva_ArvBin(Arv* jogo_no);

ArvNo* jj_busca_jogo_timeFora(Arv* jogo_no, char* timeFora);

ArvNo* jj_busca_jogo_timeCasa(Arv* jogo_no, char* timeCasa);

ArvNo* jj_busca_campeonato(Arv* jogo_no, char* campeonato);

void jj_pegar_jogo_id(Arv* jogo_no, int id);

Arv* jj_lerArquivoJogos();

Arv* verificarArvore(Arv* jogo_no);

void jj_libera_jogo(Arv* jogo_no);

void jj_altera_jogo(Arv* jogo_no, char* campeonato, int id);


//funcoes para apostas

int jj_id_jogo(Arv* jogo_no, char* campeonato, int id);

float jj_Valor_casa(Arv* jogo_no, char* campeonato, int id);

float jj_Valor_fora(Arv* jogo_no, char* campeonato, int id);

float jj_Valor_empate(Arv* jogo_no, char* campeonato, int id);

char* jj_time_casa(Arv* jogo_no, char* campeonato, int id);

char* jj_time_fora(Arv* jogo_no, char* campeonato, int id);

int jj_status_jogo(Arv* jogo_no, char* campeonato, int id);

int jj_gols_casa(Arv* jogo_no, char* campeonato, int id);

int jj_gols_fora(Arv* jogo_no, char* campeonato, int id);

#endif // ARVBIN_H_INCLUDED
