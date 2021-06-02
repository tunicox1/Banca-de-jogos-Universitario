#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ArvBinJogo.h"

struct arvno{
    Jogo* info;
    ArvNo* esq;
    ArvNo* dir;
};

struct arv{
    ArvNo* raiz;
};

Arv* jj_cria_jogo(){
    Arv* jogo_no = (Arv*)malloc(sizeof(Arv));
    jogo_no->raiz = NULL;

    return jogo_no;
}

static ArvNo* insere(ArvNo* jogo_no, int id, int status, char* campeonato, char* timeCasa, char* timeFora, int golsCasa, int golsFora, float valorCasa, float valorFora, float valorEmpate){
    if(jogo_no == NULL){
        jogo_no = (ArvNo*)malloc(sizeof(ArvNo));
        jogo_no->info = criarJogo(id,status,campeonato,timeCasa,timeFora,golsCasa,golsFora,valorCasa,valorFora,valorEmpate);
        jogo_no->esq = jogo_no->dir = NULL;
    }
    else if(strcmp(campeonato,getCampeonato(jogo_no->info)) < 0)
        jogo_no->esq = insere(jogo_no->esq,id,status,campeonato,timeCasa,timeFora,golsCasa,golsFora,valorCasa,valorFora,valorEmpate);
    else
        jogo_no->dir = insere(jogo_no->dir,id,status,campeonato,timeCasa,timeFora,golsCasa,golsFora,valorCasa,valorFora,valorEmpate);
    return jogo_no;
}

void jj_insere_jogo(Arv* jogo_no, int id, int status, char* campeonato, char* timeCasa, char* timeFora, int golsCasa, int golsFora, float valorCasa, float valorFora, float valorEmpate){
    jogo_no->raiz = insere(jogo_no->raiz, id, status, campeonato, timeCasa,timeFora,golsCasa,golsFora,valorCasa,valorFora,valorEmpate);
}

static void imprimeJogo(ArvNo* jogo_no){
    if(jogo_no != NULL){
        imprimeJogo(jogo_no->esq);
        imprimirJogos(jogo_no->info);
        imprimeJogo(jogo_no->dir);
    }

}

void jj_imprime(Arv* jogo_no){
    imprimeJogo(jogo_no->raiz);
}

static void JogoAndamento(ArvNo* jogo_no){
    if(jogo_no != NULL){
        JogoAndamento(jogo_no->esq);
        imprimeJogosEmdamento(jogo_no->info);
        JogoAndamento(jogo_no->dir);
    }
}

void jj_imprime_andamento(Arv* jogo_no){
    JogoAndamento(jogo_no->raiz);
}

static void JogoEncerrados(ArvNo* jogo_no){
    if(jogo_no != NULL){
        JogoEncerrados(jogo_no->esq);
        imprimeJogosEncerrados(jogo_no->info);
        JogoEncerrados(jogo_no->dir);
    }
}

void jj_imprime_encerrados(Arv* jogo_no){
    JogoEncerrados(jogo_no->raiz);
}

static void jogoCampeonato(ArvNo* jogo_no, char* campeonato){
    if(jogo_no != NULL){
        jogoCampeonato(jogo_no->esq,campeonato);
        imprimeCamepeonatos(jogo_no->info, campeonato);
        jogoCampeonato(jogo_no->dir, campeonato);
    }
}

void jj_imprime_campeonato(Arv* jogo_no, char* campeonato){
    jogoCampeonato(jogo_no->raiz, campeonato);
}

static ArvNo* busca_fora(ArvNo* jogo_no, char* timeFora){
    if(jogo_no == NULL) return NULL;
    else if(strcmp(timeFora, getTimeFora(jogo_no->info)) < 0) return busca_fora(jogo_no->esq, timeFora);
    else if (strcmp(timeFora, getTimeFora(jogo_no->info)) > 0) return busca_fora(jogo_no->dir, timeFora);
    else return jogo_no;
}

ArvNo* jj_busca_jogo_timeFora(Arv* jogo_no, char* timeFora){
    return busca_fora(jogo_no->raiz, timeFora);
}

static ArvNo* busca_id(ArvNo* jogo_no, int id){
    if(jogo_no == NULL) return NULL;
    else if(getIdJogo(jogo_no->info) < id) return busca_fora(jogo_no->esq, id);
    else if (getIdJogo(jogo_no->info) > id) return busca_fora(jogo_no->dir, id);
    else return jogo_no;
}

void jj_pegar_jogo_id(Arv* jogo_no, int id){
    ArvNo* take = busca_id(jogo_no->raiz, id);
    alteraJogos(take->info);
}

static ArvNo* busca_casa(ArvNo* jogo_no, char* timeCasa){
    if(jogo_no == NULL) return NULL;
    else if(strcmp(timeCasa, getTimeCasa(jogo_no->info)) < 0) return busca_casa(jogo_no->esq, timeCasa);
    else if (strcmp(timeCasa, getTimeCasa(jogo_no->info)) > 0) return busca_casa(jogo_no->dir, timeCasa);
    else return jogo_no;
}

ArvNo* jj_busca_jogo_timeCasa(Arv* jogo_no, char* timeCasa){
    return busca_casa(jogo_no->raiz, timeCasa);
}

static ArvNo* busca_campeonato(ArvNo* jogo_no, char* campeonato){
    if(jogo_no == NULL) return NULL;
    else if(strcmp(campeonato, getCampeonato(jogo_no->info)) < 0) return busca_campeonato(jogo_no->esq, campeonato);
    else if (strcmp(campeonato, getCampeonato(jogo_no->info)) > 0) return busca_campeonato(jogo_no->dir, campeonato);
    else return jogo_no;
}

ArvNo* jj_busca_campeonato(Arv* jogo_no, char* campeonato){
    return busca_campeonato(jogo_no->raiz, campeonato);
}

static ArvNo* busca_id_campeonato(ArvNo* jogo_no, char* campeonato, int id){
    if(jogo_no != NULL){
        if(strcmp(campeonato, getCampeonato(jogo_no->info)) == 0 && getIdJogo(jogo_no->info) == id){
            return jogo_no;
        }else if(strcmp(campeonato, getCampeonato(jogo_no->info)) < 0){
            return busca_id_campeonato(jogo_no->esq, campeonato, id);
        }else{
            return busca_id_campeonato(jogo_no->dir, campeonato, id);
        }
    }
    return NULL;
}

void jj_altera_jogo(Arv* jogo_no, char* campeonato, int id){
    ArvNo* v = busca_id_campeonato(jogo_no->raiz, campeonato, id);
    if(v != NULL){
        modificarJogo(v->info);
    }else{
       printf("nao existe esse campeonato\n");
    }
}

static ArvNo* retira(ArvNo* jogo_no,char* campeonato){
     if(jogo_no == NULL){
        system("pause");
        system("cls");
        return NULL;
     }
    else if(strcmp(getCampeonato(jogo_no->info), campeonato) > 0)
        jogo_no->esq = retira(jogo_no->esq,campeonato);
    else if(strcmp(getCampeonato(jogo_no->info), campeonato) < 0)
        jogo_no->dir = retira(jogo_no->dir, campeonato);
    else{
        if(jogo_no->esq == NULL && jogo_no->dir == NULL){
            free(jogo_no);
            jogo_no = NULL;
        }
        else if(jogo_no->esq == NULL){
            ArvNo* t = jogo_no;
            jogo_no = jogo_no->dir;
            free(t);
        }
        else if(jogo_no->dir == NULL){
            ArvNo* t = jogo_no;
            jogo_no = jogo_no->esq;
            free(t);
        }
        else{
            ArvNo* f = jogo_no->esq;
            while(f->dir != NULL){
                f = f->dir;
            }
            strcpy(getCampeonato(jogo_no->info), getCampeonato(f->info));
            strcpy(getCampeonato(f->info), campeonato);
            jogo_no->esq = retira(jogo_no->esq, campeonato);
        }
    }
    return jogo_no;
}

void jj_retira_jogo(Arv* jogo_no, char* campeonato){
    jogo_no->raiz = retira(jogo_no->raiz, campeonato);
}

static void jogoAtualizar(ArvNo* jogo_no,int cont){
    if(jogo_no != NULL){

        if(cont==0){
            atualizarDadosJogos(jogo_no->info,"w");
        }else{
            atualizarDadosJogos(jogo_no->info,"a");
        }
        //salva os jogos essa arvore binaria
        jogoAtualizar(jogo_no->esq,cont+1);
        jogoAtualizar(jogo_no->dir,cont+1);
    }
}

void jj_atualizarJogo(Arv* jogo_no){
    jogoAtualizar(jogo_no->raiz,0);
}

static void jogoSalvo(ArvNo* jogo_no){
    if(jogo_no != NULL){
        jogoSalvo(jogo_no->esq);
        salvaJogos(jogo_no->info); //salva os jogos essa arvore binaria
        jogoSalvo(jogo_no->dir);
    }
}

void jj_jogo_salva_ArvBin(Arv* jogo_no){
    jogoSalvo(jogo_no->raiz);
}

Arv* jj_lerArquivoJogos(){
  FILE* arq = fopen("./tabelaDeJogo.txt","r");
  if(arq == NULL){
    printf("menoria insuficiente!!!\n");
    exit(1);
  }

  //criando a raiz do jogo
  Arv* updateJogo = jj_cria_jogo();
  //variaveis
  char linha[121];
  int id;
  int status;
  char camp[31];
  char timeCasa[31];
  char timeFora[31];
  int golsCasa;
  int golsFora;
  float valorCasa;
  float valorFora;
  float valorEmpate;

  while(fgets(linha, 121, arq) != NULL){
    sscanf(linha,"%d\t%d\t%d\t%d\t%[^\t]\t%s\t%s\t%f\t%f\t%f",
           &id,
           &status,
           &golsCasa,
           &golsFora,
           camp,
           timeCasa,
           timeFora,
           &valorCasa,
           &valorFora,
           &valorEmpate);

    jj_insere_jogo(
           updateJogo,
           id,
           status,
           camp,
           timeCasa,
           timeFora,
           golsCasa,
           golsFora,
           valorCasa,
           valorFora,
           valorEmpate
           );
  }

  fclose(arq);

  return updateJogo;
}

Arv* verificarArvore(Arv* jogo_no){
   if(jogo_no == NULL || jogo_no->raiz == NULL)
        return NULL;
    else
        return jogo_no;
}

static void libera(ArvNo* jogo_no){
    if(jogo_no != NULL){
        libera(jogo_no->esq);
        libera(jogo_no->dir);
        free(jogo_no);
    }
    return;
}

void jj_libera_jogo(Arv* jogo_no){
    libera(jogo_no->raiz);
}

//tunico para vc pegar os get sao essas funcoes das arvores aqui
static ArvNo* id_jogo(ArvNo* jogo_no, char* campeonato, int id){
    if(jogo_no != NULL){
        if(strcmp(campeonato, getCampeonato(jogo_no->info)) == 0 && getIdJogo(jogo_no->info) == id){
            return jogo_no;
        }else if(strcmp(campeonato, getCampeonato(jogo_no->info)) < 0){
            return id_jogo(jogo_no->esq, campeonato, id);
        }else{
            return id_jogo(jogo_no->dir, campeonato, id);
        }
    }
    return NULL;
}

int jj_id_jogo(Arv* jogo_no, char* campeonato, int id){
    ArvNo* v = id_jogo(jogo_no->raiz, campeonato, id);
    if(v != NULL){
       return getIdJogo(v->info);
    }else{
       return 0;
    }
}

static ArvNo* valor_casa(ArvNo* jogo_no, char* campeonato, int id){
    if(jogo_no != NULL){
        if(strcmp(campeonato, getCampeonato(jogo_no->info)) == 0 && getIdJogo(jogo_no->info) == id){
            return jogo_no;
        }else if(strcmp(campeonato, getCampeonato(jogo_no->info)) < 0){
            return valor_casa(jogo_no->esq, campeonato, id);
        }else{
            return valor_casa(jogo_no->dir, campeonato, id);
        }
    }
    return NULL;
}

float jj_Valor_casa(Arv* jogo_no, char* campeonato, int id){
    ArvNo* v = valor_casa(jogo_no->raiz, campeonato, id);
    if(v != NULL){
       return getValorCasa(v->info);
    }else{
       printf("Erro com o campeonato ou ID!!\n");
       return 0.0;
    }
}

static ArvNo* valor_fora(ArvNo* jogo_no, char* campeonato, int id){
    if(jogo_no != NULL){
        if(strcmp(campeonato, getCampeonato(jogo_no->info)) == 0 && getIdJogo(jogo_no->info) == id){
            return jogo_no;
        }else if(strcmp(campeonato, getCampeonato(jogo_no->info)) < 0){
            return valor_fora(jogo_no->esq, campeonato, id);
        }else{
            return valor_fora(jogo_no->dir, campeonato, id);
        }
    }
    return NULL;
}

float jj_Valor_fora(Arv* jogo_no, char* campeonato, int id){
    ArvNo* v = valor_fora(jogo_no->raiz, campeonato, id);
    if(v != NULL){
       return getValorFora(v->info);
    }else{
       printf("Erro com o campeonato ou ID!!\n");
       return 0.0;
    }
}

static ArvNo* valor_empate(ArvNo* jogo_no, char* campeonato, int id){
    if(jogo_no != NULL){
        if(strcmp(campeonato, getCampeonato(jogo_no->info)) == 0 && getIdJogo(jogo_no->info) == id){
            return jogo_no;
        }else if(strcmp(campeonato, getCampeonato(jogo_no->info)) < 0){
            return valor_empate(jogo_no->esq, campeonato, id);
        }else{
            return valor_empate(jogo_no->dir, campeonato, id);
        }
    }
    return NULL;
}

float jj_Valor_empate(Arv* jogo_no, char* campeonato, int id){
    ArvNo* v = valor_empate(jogo_no->raiz, campeonato, id);
    if(v != NULL){
       return getValorEmpate(v->info);
    }else{
       printf("Erro com o campeonato ou ID!!\n");
       return 0.0;
    }
}

static ArvNo* timeCasa(ArvNo* jogo_no, char* campeonato, int id){
    if(jogo_no != NULL){
        if(strcmp(campeonato, getCampeonato(jogo_no->info)) == 0 && getIdJogo(jogo_no->info) == id){
            return jogo_no;
        }else if(strcmp(campeonato, getCampeonato(jogo_no->info)) < 0){
            return timeCasa(jogo_no->esq, campeonato, id);
        }else{
            return timeCasa(jogo_no->dir, campeonato, id);
        }
    }
    return NULL;
}

char* jj_time_casa(Arv* jogo_no, char* campeonato, int id){
    ArvNo* v = timeCasa(jogo_no->raiz, campeonato, id);
    if(v != NULL){
       return getTimeCasa(v->info);
    }else{
       printf("Erro com o campeonato ou ID!!\n");
       return "Erro404";
    }
}

static ArvNo* timeFora(ArvNo* jogo_no, char* campeonato, int id){
    if(jogo_no != NULL){
        if(strcmp(campeonato, getCampeonato(jogo_no->info)) == 0 && getIdJogo(jogo_no->info) == id){
            return jogo_no;
        }else if(strcmp(campeonato, getCampeonato(jogo_no->info)) < 0){
            return timeFora(jogo_no->esq, campeonato, id);
        }else{
            return timeFora(jogo_no->dir, campeonato, id);
        }
    }
    return NULL;
}

char* jj_time_fora(Arv* jogo_no, char* campeonato, int id){
    ArvNo* v = timeFora(jogo_no->raiz, campeonato, id);
    if(v != NULL){
       return getTimeFora(v->info);
    }else{
       printf("Erro com o campeonato ou ID!!\n");
       return "error404";
    }

}

static ArvNo* status(ArvNo* jogo_no, char* campeonato, int id){
    if(jogo_no != NULL){
        if(strcmp(campeonato, getCampeonato(jogo_no->info)) == 0 && getIdJogo(jogo_no->info) == id){
            return jogo_no;
        }else if(strcmp(campeonato, getCampeonato(jogo_no->info)) < 0){
            return status(jogo_no->esq, campeonato, id);
        }else{
            return status(jogo_no->dir, campeonato, id);
        }
    }
    return NULL;
}

int jj_status_jogo(Arv* jogo_no, char* campeonato, int id){
    ArvNo* v = status(jogo_no->raiz, campeonato, id);
    if(v != NULL){
       return getStatusJogo(v->info);
    }else{
       printf("Erro com o campeonato ou ID!!\n");
       return 0;
    }
}

static ArvNo* gols_casa(ArvNo* jogo_no, char* campeonato, int id){
    if(jogo_no != NULL){
        if(strcmp(campeonato, getCampeonato(jogo_no->info)) == 0 && getIdJogo(jogo_no->info) == id){
            return jogo_no;
        }else if(strcmp(campeonato, getCampeonato(jogo_no->info)) < 0){
            return gols_casa(jogo_no->esq, campeonato, id);
        }else{
            return gols_casa(jogo_no->dir, campeonato, id);
        }
    }
    return NULL;
}

int jj_gols_casa(Arv* jogo_no, char* campeonato, int id){
    ArvNo* v = gols_casa(jogo_no->raiz, campeonato, id);
    if(v != NULL){
       return getGolsCasa(v->info);
    }else{
       printf("Erro com o campeonato ou ID!!\n");
       return 0;
    }
}

static ArvNo* gols_fora(ArvNo* jogo_no, char* campeonato, int id){
    if(jogo_no != NULL){
        if(strcmp(campeonato, getCampeonato(jogo_no->info)) == 0 && getIdJogo(jogo_no->info) == id){
            return jogo_no;
        }else if(strcmp(campeonato, getCampeonato(jogo_no->info)) < 0){
            return gols_fora(jogo_no->esq, campeonato, id);
        }else{
            return gols_fora(jogo_no->dir, campeonato, id);
        }
    }
    return NULL;
}

int jj_gols_fora(Arv* jogo_no, char* campeonato, int id){
    ArvNo* v = gols_fora(jogo_no->raiz, campeonato, id);
    if(v != NULL){
       return getGolsFora(v->info);
    }else{
       printf("Erro com o campeonato ou ID!!\n");
       return 0;
    }
}






