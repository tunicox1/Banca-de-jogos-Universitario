#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <string.h>

#include "apostas.h"

struct aposta
{
    int id;
    int id_usuario;
    int id_jogo;
    char campeonato[50];
    int time_apostado;
    float valor;
    int status;

    Aposta* prox;
};
/*
status das apostas
0 = nao atualizada
1 = venceu
2 = perdeu
*/
/*
time apostado das apostas
0 = time de casa
1 = time de fora
2 = empate
*/
//int tam = 0;
static int contApostasArquivo(){
    FILE* arq = fopen("./apostas/aposta.txt", "r");
    int cont=0;
    if(arq == NULL){
        return cont;
    }
    Aposta* a =(Aposta*) malloc(sizeof(Aposta));
    if(a==NULL){
        printf("Memoria insuficiente!\n");
        exit(1);
    }

     while(fscanf(arq, "%d\t%d\t%d\t%[^\t]\t%f\t%d\t%d",&a->id,&a->id_usuario,&a->id_jogo,a->campeonato,&a->valor,&a->time_apostado,&a->status) != EOF){
        // printf("id:%d\t Valor:%f\t Op Apostada:%d\n",id,valor,time_apostado);
        cont++;
     }
     return cont;
}
void menuA(){
   printf("-----------------------------------------------------------------------------------------\n");
   printf("\t       MENU APOSTA                                                      \n");
   printf("-----------------------------------------------------------------------------------------\n");
   printf("\t (1) - criar apostas\n");
   printf("\t (2) - imprimir aposta\n");
   printf("\t (3) - sair\n");
   printf("-----------------------------------------------------------------------------------------\n");
}

void menuAposta(Usuario* user)
{
    int opcao;
    Aposta *lista_aposta;
    int contApostas = contApostasArquivo();
    if(contApostas>0)
        lista_aposta=lerApostas();
    else
        lista_aposta=NULL;

    Arv* jogos = jj_cria_jogo();
    jogos = jj_lerArquivoJogos();

    do{
        if(jogos==NULL){
            printf("------------------------------------------\n");
            printf("Nenhum jogo cadastrado no momento!\nImpossivem de realizar apostas!!\n");
            printf("------------------------------------------\n");
            return;
        }

        menuA();

        printf("\t ->");
        scanf(" %d",&opcao);
        system("cls");

        switch(opcao)
        {
        case 1:{
            if(contJogosArquivo()>0){
                Aposta* novo = cria_aposta(lista_aposta,jogos,user);
                if(novo!=NULL){
                    novo->prox = lista_aposta;
                    lista_aposta = novo;
                    salvar_apostas(lista_aposta);
                }
            }else{
                printf("------------------------------------------------------\n");
                printf("Nenhum jogo cadastrado!\n");
                printf("------------------------------------------------------\n");
            }
            break;
        }
        case 2:{
            imprimeAposta(lista_aposta,jogos,user);
            break;
        }
        case 3:{
            printf("Saindo!!\n");
            break;
        }
        default:
            printf("Opcao Invalida!\n");
        }

    }while(opcao!=3);

}



Aposta* cria_aposta( Aposta *Ap,Arv* jogos,Usuario* user)
{
    jj_imprime_andamento(jogos);
    Usuario* adm = buscarUsuario(0);
    float carteiraAdm = getCarteira(adm);
    Aposta* novo = (Aposta*) malloc(sizeof(Aposta));
    if(novo==NULL){
        printf("Memoria insuficiente!");
        exit(1);
    }
    float carteira = getCarteira(user);
    if(carteira==0.0){
        printf("Saldo insuficiente!\n");
        system("pause");
        system("cls");
    }else{
        printf("\tCarteira: R$ %.2f\n",carteira);
        do{
            scanf("%*c");
            printf("------------------------------------------------------\n");
            printf("Digite o Campeonato do jogo que deseja apostar:");
            scanf(" %[^\n]",novo->campeonato);
            printf("Digite o id do jogo que deseja apostar:");
            scanf("%d",&novo->id_jogo);
            if(jj_id_jogo(jogos,novo->campeonato,novo->id_jogo)==0){
                system("cls");
                jj_imprime_andamento(jogos);
                printf("------------------------------------------------------\n");
                printf("\tJogo nao encontrado!\n\tDigite Novamente!\n");
            }

        }while(jj_id_jogo(jogos,novo->campeonato,novo->id_jogo)==0);
        do{

            printf("Digite o valor da aposta:");
            scanf("%f",&novo->valor);
            if(novo->valor>carteira){
                system("cls");
                printf("------------------------------------------------------\n");
                printf("\tValor Invalido!\n\tDigite Novamente!\n");
                printf("------------------------------------------------------\n");
            }else{
                float novaCarteira = carteira-novo->valor;
                setCarteira(user,novaCarteira);
                atualizarDadosUsuario(user);

                float novaCarteiraAdm = carteiraAdm+novo->valor;
                setCarteira(adm,novaCarteiraAdm);
                atualizarDadosUsuario(adm);
            }

        }while(novo->valor>carteira);
        do{

            printf("------------------------------------------------------\n");
            printf("\tInforme o time apostado: \n");
            printf("------------------------------------------------------\n");
            printf("\t1 - Time de casa\n");
            printf("\t2 - Time de fora\n");
            printf("\t3 - Empate\n");
            printf("------------------------------------------------------\n");
            printf("->");
            scanf("%d",&novo->time_apostado);
            if(novo->time_apostado<1 || novo->time_apostado>3){
                system("cls");
                printf("------------------------------------------------------\n");
                printf("\tOpcao invalida!\n\tDigite Novamente!");
            }

        }while(novo->time_apostado<1 || novo->time_apostado>3);

        novo->time_apostado--;
        novo->status = 0;
        novo->id_usuario = getIdUsuario(user);
        novo->id = geraIdAposta(Ap);

        novo->prox = NULL;
        system("cls");
        printf("------------------------------------------------------\n");
        printf("\tSucesso ao cadastrar a aposta!\n");
        printf("------------------------------------------------------\n");

        return novo;
    }
    return NULL;
}

int geraIdAposta(Aposta*Ap){
    if(Ap==NULL || contApostasArquivo()==0){
        return 0;
    }
    int maiorId = 0;
    Aposta* aux = Ap;
    while(aux!=NULL){
        if(aux->id>maiorId){
            maiorId = aux->id;
        }
        aux = aux->prox;
    }

    return maiorId+1;
}

void salvar_apostas(Aposta* Ap)
{
    if(Ap!=NULL){
        FILE* fp = fopen("./apostas/aposta.txt","w");
        if(fp == NULL)
        {
            printf("Erro ao abrir arquivo");
            exit(1);
        }
        Aposta* a = Ap;
        while(a!=NULL){
            fprintf(fp,"%d\t%d\t%d\t%s\t%f\t%d\t%d\n",a->id,a->id_usuario,a->id_jogo,a->campeonato,a->valor,a->time_apostado,a->status);
            a = a->prox;
        }

        fclose(fp);
    }

}

Aposta* lerApostas(){
    Aposta* j = (Aposta*) malloc (sizeof(Aposta));
    if(j == NULL){
        printf("memoria insuficiente!\n");
        exit(1);
    }


    FILE* arq = fopen("./apostas/aposta.txt", "r");
    if(arq == NULL){
        return NULL;
    }

    Aposta* a =(Aposta*) malloc(sizeof(Aposta));
    if(a==NULL){
        printf("Memoria insuficiente!\n");
        exit(1);
    }
    int cont=0;
     while(fscanf(arq, "%d\t%d\t%d\t%[^\t]\t%f\t%d\t%d",&a->id,&a->id_usuario,&a->id_jogo,a->campeonato,&a->valor,&a->time_apostado,&a->status) != EOF){
        // printf("id:%d\t Valor:%f\t Op Apostada:%d\n",id,valor,time_apostado);
         if(cont == 0){
            j->id=a->id;
            j->id_usuario = a->id_usuario;
            j->id_jogo = a->id_jogo;

            strcpy(j->campeonato,a->campeonato);

            j->valor=a->valor;
            j->time_apostado=a->time_apostado;
            j->status = a->status;
            j->prox = NULL;
            cont++;
         }else{
            lista_insere(j,a);
         }


     }
    return j;
}

void lista_insere(Aposta* dest,Aposta* dado){
    Aposta* novo =(Aposta*)malloc(sizeof(Aposta));
    if(novo ==NULL){
        printf("Memoria insuficiente!\n");
        exit(1);
    }

    novo->id=dado->id;
    novo->id_usuario = dado->id_usuario;
    novo->id_jogo = dado->id_jogo;

    strcpy(novo->campeonato,dado->campeonato);

    novo->valor=dado->valor;
    novo->time_apostado=dado->time_apostado;
    novo->status = dado->status;
    novo->prox = dest->prox;

    dest->prox=novo;

}


void atualizarApostas( Aposta *Ap,Arv* jogos,Usuario *user)
{
    Usuario* adm = buscarUsuario(0);
    float carteiraAdm = getCarteira(adm);
    Aposta* aux = Ap;
    float cotacao = 0.0, novaCarteira=getCarteira(user), novaCarteiraAdm = 0.0,valorGanho=0.0;
    int golsCasa=0,golsFora=0, idUsuario = getIdUsuario(user),statusJogo=1;
    while(aux!=NULL){
        if(idUsuario == aux->id_usuario){
            statusJogo = jj_status_jogo(jogos,aux->campeonato,aux->id_jogo);
            golsCasa = jj_gols_casa(jogos,aux->campeonato,aux->id_jogo);
            golsFora = jj_gols_fora(jogos,aux->campeonato,aux->id_jogo);
            if(aux->time_apostado == 0 && golsCasa>golsFora && statusJogo == 0 && aux->status==0){
                cotacao = jj_Valor_casa(jogos,aux->campeonato,aux->id_jogo);
                aux->status = 1;

            }else if(aux->time_apostado == 1 && golsCasa<golsFora && statusJogo == 0 && aux->status==0){
                cotacao = jj_Valor_fora(jogos,aux->campeonato,aux->id_jogo);
                aux->status = 1;

            }else if(aux->time_apostado == 2 && golsCasa == golsFora && statusJogo == 0 && aux->status==0){
                cotacao = jj_Valor_empate(jogos,aux->campeonato,aux->id_jogo);
                aux->status = 1;

            }else if(statusJogo == 0 && aux->status==0){
                cotacao=0.0;
                aux->status = 2;

            }
            if(cotacao>0){
                valorGanho = ((cotacao*aux->valor)+aux->valor);
            }
            novaCarteiraAdm = carteiraAdm - valorGanho;
            novaCarteira += valorGanho;
            setCarteira(user,novaCarteira);
            setCarteira(adm,novaCarteiraAdm);
            valorGanho = 0;
            cotacao=0;
        }
        aux=aux->prox;
    }
    salvar_apostas(Ap);
    atualizarDadosUsuario(user);
    atualizarDadosUsuario(adm);


}

void imprimeAposta( Aposta *Ap,Arv* jogos,Usuario* user)
{
    Aposta *pointer;
    pointer = Ap;
    int idUsuario = getIdUsuario(user);
    int cont = 1;
    char timeApostado[3][50] = {"Time de casa","Time de fora", "Empate dos times"};
    char status[3][50] = {"Jogo nao aconteceu ainda","Venceu", "Perdeu"};
    while(pointer!=NULL){
        if(idUsuario == pointer->id_usuario){
            printf("---------------------------------------------------\n");
            printf("\tJogo\n");
            printf("---------------------------------------------------\n");
            printf("\t%s (%d) X (%d) %s\n",jj_time_casa(jogos,pointer->campeonato,pointer->id_jogo),
                   jj_gols_casa(jogos,pointer->campeonato,pointer->id_jogo),
                   jj_gols_fora(jogos,pointer->campeonato,pointer->id_jogo),
                   jj_time_fora(jogos,pointer->campeonato,pointer->id_jogo));
            printf("---------------------------------------------------\n");
            printf("\tAposta\n");
            printf("---------------------------------------------------\n");
            printf("\tid: %d\n",cont);
            printf("\tTime da aposta: %s\n",timeApostado[pointer->time_apostado]);
            printf("\tValor da aposta: %.2f\n",pointer->valor);
            printf("\tstatus: %s \n",status[pointer->status]);
            printf("---------------------------------------------------\n\n");
            cont++;
        }
        pointer = pointer->prox;
    }



}


