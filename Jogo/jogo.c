#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Jogo.h"
#include "../Usuario/Usuario.h"
#include "../apostas/apostas.h"
#include "ArvBinJogo/ArvBinJogo.h"

struct jogo{
 int id;
 int status;
 int golsCasa;
 int golsFora;
 char campeonato[21];
 char timeCasa[21];
 char timeFora[21];
 float valorCasa;
 float valorFora;
 float valorEmpate;
};

//funcao só para auxiliar o usuario escolhe a opcao
static void tabelaOpcao(){
    printf("------ Tabela opcoes Jogos ------\n");
     char opcoes[5][100] = {"Adicionar Jogos", "Imprimir Jogos","Alterar dados", "Apagar dado",  "Sair"};
     for(int i = 0;i < 5; i++){
            printf("\t%d - %s\n", i+1, opcoes[i]);
      }
    printf("----------------------------------\n");
}

//funcao para cadastro do jogo
static void cadastradoJogo(Arv* addJogo_no){
    system("cls\n");
    int n;
    printf("--------------------------------------------------------------------------\n");
    printf("digite o total de cadastro de jogos!\n");
    printf("--------------------------------------------------------------------------\n");
    scanf(" %d",&n);
    int i, maiorId = gerarIdJogo();
    for(i=0;i<n;i++){
      Jogo* jogo = lerJogos();
      jogo->id = maiorId+i;
      jj_insere_jogo(addJogo_no,
                      jogo->id,
                      jogo->status,
                      jogo->campeonato,
                      jogo->timeCasa,
                      jogo->timeFora,
                      jogo->golsCasa,
                      jogo->golsFora,
                      jogo->valorCasa,
                      jogo->valorFora,
                      jogo->valorEmpate
                      );
    }

}



//funcao auxiliar so para usuario escolher a opcao de imprimi
static void tabelaAuxiliarOpcaoImprime(){
    printf("--------------------------------------------------------------------------\n");
    printf("\t\t\t Opcao imprime \t\t\t\n");
    printf("--------------------------------------------------------------------------\n");
    printf("\t(1)- Todos jogos\n");
    printf("\t(2)- Jogos que Vao acontecer\n");
    printf("\t(3)- Jogos Encerrados\n");
    printf("\t(4)- Jogos por Campeonato\n");
    printf("\t(5)- Sair\n");
    printf("--------------------------------------------------------------------------\n");
}

//funcao auxiliar só para verificar se Arv esta vazia  , em seguinda imprime
static void imprime_jogos(Arv* jogo_no){
    int op;
    do{
        system("cls");
        tabelaAuxiliarOpcaoImprime();
        printf("digite a opcao: ");
        scanf("%d",&op);
        switch(op){
            case 1:{
            system("cls");
            if(verificarArvore(jogo_no) != NULL)
                jj_imprime(jogo_no);
            else
                printf("Arvore vazia!\n");
            break;
            }
            case 2:{
            system("cls");
            if(verificarArvore(jogo_no) != NULL)
                jj_imprime_andamento(jogo_no);
            else
                printf("Arvore vazia!\n");
            break;
            }
            case 3:{
            system("cls");
            if(verificarArvore(jogo_no) != NULL)
                jj_imprime_encerrados(jogo_no);
            else
                printf("Arvore vazia!\n");
            break;
            }
            case 4:{
            system("cls");
            if(verificarArvore(jogo_no) != NULL){
                jj_imprime(jogo_no);
                char camp [31];
                printf("Qual campeonato vc que ver: ");
                scanf(" %[^\n]",camp);

               if(jj_busca_campeonato(jogo_no, camp) == NULL){
                   printf("Campeonato nao existe!!\n");
               }
               else{
                    system("pause");
                    system("cls");
                    jj_imprime_campeonato(jogo_no, camp);
               }
            }else
                printf("Arvore vazia!\n");

            }
            break;
            case 5:{
                system("cls");
                return;
                break;
            }
            default:
                system("cls");
                printf("\tOPCAO INVALIDA!!\n\tDIGITE NOVAMENTE A OPCAO");
        }
        system("pause");
    }while(op > 0 && op < 5);

}

//funcao auxiliar para apagar o campeonato
static void apagarCampeonato(Arv* jogo_no){
    char camp[21];
    if(verificarArvore(jogo_no) != NULL)
       jj_imprime(jogo_no);
    else
        return;

    printf("Qual campeonato vc que apagar?\n");
    scanf(" %[^\n]",camp);

    do{
        jj_retira_jogo(jogo_no, camp);
    }while(jj_busca_campeonato(jogo_no, camp) != NULL);

    system("pause");
    system("cls");
}

//menu do Jogos
void Menu(int nivelDeAcesso){
   Arv* jogo_no = jj_cria_jogo();
   jogo_no = jj_lerArquivoJogos();
if(nivelDeAcesso == 0){
    int opJogo;
    do{
       system("cls");
       tabelaOpcao();
       scanf("%d",&opJogo);
       if(opJogo == 1){
          cadastradoJogo(jogo_no);
           if(contJogosArquivo() == 0){
            jj_jogo_salva_ArvBin(jogo_no);
          }else{
            jj_atualizarJogo(jogo_no);
          }
       }else if(opJogo == 2){
          imprime_jogos(jogo_no);
       }else if(opJogo == 3){
          char nome_campeonato[31];
          int id;
          jj_imprime(jogo_no);
          printf("Informe o campeonato: ");
          scanf(" %[^\n]",nome_campeonato);
          printf("Informe o id do jogo: ");
          scanf(" %d",&id);
          jj_altera_jogo(jogo_no,nome_campeonato, id);
          jj_atualizarJogo(jogo_no);
          atualizarUsuarios();
       }
       else if(opJogo == 4){
          apagarCampeonato(jogo_no);
          jj_atualizarJogo(jogo_no); //atualizar os dados do jogo aqui
       }else{
          printf("saindo......\n");
       }
    }while(opJogo > 0 && opJogo < 5);
}else{
      if(verificarArvore(jogo_no) != NULL)
          imprime_jogos(jogo_no);
      else{
         printf("Arvore vazia!\n");
        system("pause");
      }
      system("cls");
}
  system("cls");
  jj_libera_jogo(jogo_no); //libera memoria
}

//funcao que receber o usuario e pegar o nivel de acesso dele
void menuJogo(Usuario* user){
    int nivelDeAcesso = getNivelDeAcesso(user);
    Menu(nivelDeAcesso);
}

//validar gols
static int validarGols(int gols){
  while(gols < 0){
    printf("Invalido!!!, Digite novamente!\n");
    scanf("%d",&gols);
  }
  return gols;
}

//validar cotar
static float validarValorCota(float valor){
  while(valor < 0){
    printf("Invalido!!!, Digite um novo Valor!\n");
    scanf("%f",&valor);
  }
  return valor;
}

//aqui gera um id pegando o maior e add +1
 int gerarIdJogo(){
  FILE* jogoId = fopen("./tabelaDeJogo.txt", "r");
  int maiorId = 1;
  if(jogoId == NULL || contJogosArquivo()==0){
    return maiorId;
  }else{

    char linha[200];
    int id;
    while(fgets(linha,200,jogoId)!=NULL){
      sscanf(linha,"%d",&id);
      if(id > maiorId){
        maiorId = id;
      }
    }
    return maiorId + 1;
  }

  fclose(jogoId);
}

//compara se os dois times casa e fora tem o mesmo nome
static int strcmpNomeTimes(char* timeCasa, char* timeFora){
    if(strcmp(timeCasa, timeFora) == 0)
        return 1;
    else
        return 0;
}

//ler os times
static void lerNomesTimes(Jogo* j){
      printf("\n");
      printf("Time casa: ");
      scanf(" %[^\n]",j->timeCasa);

      printf("\n");
      printf("Time Fora: ");
      scanf(" %[^\n]",j->timeFora);

      int resultado;
      do{
        resultado = strcmpNomeTimes(j->timeCasa,j->timeFora);
        if(resultado == 1){
              printf("Dois times com nomes iguais!!, digite nomes difrentes por favor!!\n");
              printf("\n");
              printf("Time casa: ");
              scanf(" %[^\n]",j->timeCasa);

              printf("\n");
              printf("Time Fora: ");
              scanf(" %[^\n]",j->timeFora);
        }
      }while(resultado == 1);
}

//ler os gols do times aqui
static void lerGolsTimes(Jogo* j){
 //gols dos times
  printf("\n");
  printf("Total gols Time Casa: ");
  scanf(" %d",&j->golsCasa);
  j->golsCasa = validarGols(j->golsCasa); //validar

  printf("\n");
  printf("Total gols Time Fora: ");
  scanf(" %d",&j->golsFora);
  j->golsFora = validarGols(j->golsFora); //validar
}

//ler valores do times aqui
static void lerValoresCotas(Jogo* j){
  //valor dos times
  printf("\n");
  printf("Valor Time Casa: ");
  scanf(" %f",&j->valorCasa);
  j->valorCasa = validarValorCota(j->valorCasa); //validar

  printf("\n");
  printf("Valor Time Fora: ");
  scanf(" %f",&j->valorFora);
  j->valorFora = validarValorCota(j->valorFora); //valida

  printf("\n");
  printf("Valor Empate: ");
  scanf(" %f",&j->valorEmpate);
  j->valorEmpate = validarValorCota(j->valorEmpate); //validar
  system("cls");
}

//ler campeonato
static void lerCampeonato(Jogo* j){
  printf("Nome do Campeonato: ");
  scanf(" %[^\n]",j->campeonato);
  printf("\n");
}

//validar status
static int statusValido(){
  int status;
  printf("Status do Jogo: ex: [0- jogo encerrado || 1- jogo em andamento]\n");
  scanf(" %d",&status);
  do{
    system("cls");
    if(status < 0 || status > 1){
        printf("Status Invalido!!, digite um status valido [0- jogo encerrado || 1- jogo em andamento]\n");
        scanf(" %d",&status);
    }

  }while(status < 0 || status > 1);
  system("cls");
  return status;
}

//ler via terminal
Jogo* lerJogos(){
  Jogo* j = (Jogo*) malloc(sizeof(Jogo));
  if(j == NULL){
    printf("menoria invalida!!\n");
    exit(1);
  }

  printf("\n");
  printf("----------------------------------------------------------------\n");
  printf("\t\t           LER STATUS JOGO                             \n");
  printf("----------------------------------------------------------------\n");
  j->status = statusValido(j);
  printf("\n");
  system("cls");

   printf("----------------------------------------------------------------\n");
   printf("\t\t         LER NOME CAMPEONATO                              \n");
   printf("----------------------------------------------------------------\n");
   lerCampeonato(j); //ler nome do campeonato
   system("cls");

   printf("----------------------------------------------------------------\n");
   printf("\t\t         LER NOME TIMES                             \n");
   printf("----------------------------------------------------------------\n");
   lerNomesTimes(j); //ler e compara se nomes sao iguais;
   system("cls");

  //aqui olha se ja tem alguma informacao dentro do aqui
  Arv* test = jj_lerArquivoJogos();
  do{
    if(jj_busca_jogo_timeCasa(test, j->timeCasa) == NULL && jj_busca_jogo_timeFora(test,j->timeFora) == NULL){
        system("cls");
        //printf("times verificados tudo ok!!\n");
    }else{
       if(jj_busca_jogo_timeCasa(test, j->timeCasa) != NULL && jj_busca_jogo_timeFora(test, j->timeFora) == NULL){
            system("cls");
           printf("insira um time diferente desse time casa e pode repeti esse fora!\n");
           lerNomesTimes(j);
       }else if(jj_busca_jogo_timeCasa(test, j->timeCasa) == NULL && jj_busca_jogo_timeFora(test, j->timeFora) != NULL){
           system("cls");
           printf("insira um time diferente desse time fora e pode repeti esse casa!\n");
           lerNomesTimes(j);
       }else{
           printf("insira dois time diferents ja sao existente!\n");
           lerNomesTimes(j);
       }
    }
  }while(jj_busca_jogo_timeCasa(test, j->timeCasa) != NULL && jj_busca_jogo_timeFora(test,j->timeFora) != NULL);
   jj_libera_jogo(test); //libera arvore

   printf("----------------------------------------------------------------\n");
   printf("\t\t         LER GOLS DO TIMES                              \n");
   printf("----------------------------------------------------------------\n");
   lerGolsTimes(j); //ler e valida Gols
   system("cls");

   printf("----------------------------------------------------------------\n");
   printf("\t\t         LER COTAS DO TIMES                               \n");
   printf("----------------------------------------------------------------\n");
   lerValoresCotas(j); //ler e valida cotas de jogos;
   system("cls");

   j->id = gerarIdJogo();

  return j; //retornando enderenço de criacao
}

//cria jogo
Jogo* criarJogo(int id, int status, char* campeonato, char* timeCasa, char* timeFora, int golsCasa,int golsFora, float valorCasa, float valorFora, float valorEmpate){
  Jogo* j = (Jogo*) malloc(sizeof(Jogo));

  j->status = status;
  strcpy(j->campeonato, campeonato);
  strcpy(j->timeCasa, timeCasa);
  strcpy(j->timeFora, timeFora);
  j->golsCasa = golsCasa;
  j->golsFora = golsFora;
  j->valorCasa = valorCasa;
  j->valorFora = valorFora;
  j->valorEmpate = valorEmpate;
  j->id = id; //funcao que gera o id do jogo

  return j;
}

//imprime os campeonato
void imprimeCamepeonatos(Jogo* j, char* campeonato){
    if(strcmp(j->campeonato, campeonato) == 0){
         printf("-----------------------------------------------------------------------------------------\n");
         printf("\t\t\t\t Campeontano %s \t\t\t\n",j->campeonato);
         printf("-----------------------------------------------------------------------------------------\n");
         printf("\t\t\t\t Id do jogo: %d \t\t\t\n",j->id);
         printf("-----------------------------------------------------------------------------------------\n");
         printf("\t time_Casa\t| CotarCasa\t| cotarEmpate\t| cotarFora\t| time_Fora\n");
         printf("-----------------------------------------------------------------------------------------\n");
         printf("\t\t%s  |    \t%.2f   |     \t%.2f   |    \t%.2f     |    %s\n",
         j->timeCasa,
         j->valorCasa,
         j->valorEmpate,
         j->valorFora,
         j->timeFora
         );
         printf("-----------------------------------------------------------------------------------------\n");
    }
}

//imprime os jogos encerrados
void imprimeJogosEncerrados(Jogo* j){
    if(j->status == 0){
     printf("-----------------------------------------------------------------------------------\n");
     printf("\t\t\t\t ENCERRADOS \t\t\t\n");
     printf("------------------------------------------------------------------------------------\n");
     printf("\t\t\t\t CAMPEONATO %s\t\t\t\t\n",j->campeonato);
     if(j->golsCasa > j->golsFora){
        printf("TIME CASA GANHOU!\n");
        printf("%s (%d) x (%d) %s\n",j->timeCasa, j->golsCasa, j->golsFora ,j->timeFora);
     }else if(j->golsCasa < j->golsFora){
        printf("TIME FORA GANHOU!\n");
         printf("%s (%d) x (%d) %s\n",j->timeCasa, j->golsCasa, j->golsFora, j->timeFora);
     }else{
        printf("EMPANTE!\n");
        printf("%s (%d) x (%d) %s\n",j->timeCasa, j->golsCasa, j->golsFora, j->timeFora);
     }
    printf("--------------------------------------------------------------------------\n");
    printf("\n");
    }
}

//imprimir jogos encerrados
void imprimeJogosEmdamento(Jogo* j){
    if(j->status == 1){
    printf("\t\t\t\t JOGOS QUE IRAO ACONTECER \t\t\t\n");
    printf("------------------------------------------------------------------------------------\n");
    printf("\t\t\t\t CAMPEONATO %s\t\t\t\t\n",j->campeonato);
    printf("-----------------------------------------------------------------------------------------\n");
    printf("\t\t\t\t Id do jogo: %d \t\t\t\n",j->id);
    printf("-----------------------------------------------------------------------------------------\n");
    printf("\t time_Casa\t| CotarCasa\t| cotarEmpate\t| cotarFora\t| time_Fora\n");
    printf("-----------------------------------------------------------------------------------------\n");
    printf("\t\t%s  |    \t%.2f   |     \t%.2f   |    \t%.2f     |    %s\n",
         j->timeCasa,
         j->valorCasa,
         j->valorEmpate,
         j->valorFora,
         j->timeFora
         );
    printf("-----------------------------------------------------------------------------------------\n");
    }
    printf("\n");
}

//imprimir imformacoes
void imprimirJogos(Jogo* j){
  printf("-----------------------------------------------------------------------------------------\n");
  printf("\t\t\t\t CAMPEONATO %s\t\t\t\t\n",j->campeonato);
  printf("-----------------------------------------------------------------------------------------\n");
  printf("\t\t\t\t Id do jogo: %d \t\t\t\n",j->id);
  printf("-----------------------------------------------------------------------------------------\n");
  printf("\t time_Casa\t| CotarCasa\t| cotarEmpate\t| cotarFora\t| time_Fora\n");
  printf("-----------------------------------------------------------------------------------------\n");
  printf("\t\t%s  |    \t%.2f   |     \t%.2f   |    \t%.2f     |    %s\n",
         j->timeCasa,
         j->valorCasa,
         j->valorEmpate,
         j->valorFora,
         j->timeFora
         );
  printf("-----------------------------------------------------------------------------------------\n");
  printf("\n\n");
}

//pegar valor do time da casa
float getValorCasa(Jogo* j){
  return j->valorCasa;
}

//pegar valor do time fora
float getValorFora(Jogo* j){
  return j->valorFora;
}

//pegar valor do empate entre os dois times
float getValorEmpate(Jogo* j){
  return j->valorEmpate;
}

//pegar o id do jogo
int getIdJogo(Jogo* j){
  return j->id;
}

//pegar o time da casa
char* getTimeCasa(Jogo* j){
    return j->timeCasa;
}

//pegar o time de fora
char* getTimeFora(Jogo* j){
    return j->timeFora;
}

//pegar o campeonato
char* getCampeonato(Jogo* j){
    return j->campeonato;
}

//pegar o gols do time da casa
int getGolsCasa(Jogo* j){
   return j->golsCasa;
}

//pegar o gols do time de fora
int getGolsFora(Jogo* j){
   return j->golsFora;
}

//pegar o status do jogo
int getStatusJogo(Jogo* j){
 return j->status;
}

//salva dados do jogo
void salvaJogos(Jogo* j){
  FILE* arq = fopen("./tabelaDeJogo.txt", "a");
  if(arq == NULL){
    printf("menoria Insuficiente!!\n");
  }

  fprintf(arq,"%d\t%d\t%d\t%d\t%s\t%s\t%s\t%.2f\t%.2f\t%.2f\n",j->id,j->status,j->golsCasa,j->golsFora,j->campeonato,j->timeCasa,j->timeFora,j->valorCasa,j->valorFora,j->valorEmpate);

   fclose(arq); //fechamento do arquivo Jogo;
   system("cls");
}

//Atualizar dados do jogo
void atualizarDadosJogos(Jogo* j,char* opcao){
  FILE* arq = fopen("./tabelaDeJogo.txt", opcao);
  if(arq == NULL){
    return;
  }
  fprintf(arq,"%d\t%d\t%d\t%d\t%s\t%s\t%s\t%.2f\t%.2f\t%.2f\n",j->id,j->status,j->golsCasa,j->golsFora,j->campeonato,j->timeCasa,j->timeFora,j->valorCasa,j->valorFora,j->valorEmpate);
  fflush(arq);  // colocar em tempo real a informacoes
  fclose(arq); //fechamento do arquivo Jogo;
  system("cls");
}

static void menuAltera(){
    printf("--------------------------------------------------------------------------\n");
    printf("\t\t\t Menu Altera \t\t\t\n");
    printf("--------------------------------------------------------------------------\n");
    printf("(1) - nome campeonato\n");
    printf("(2) - status\n");
    printf("(3) - nome time Casa\n");
    printf("(4) - nome time Fora\n");
    printf("(5) - total de gols time casa\n");
    printf("(6) - total de gols time Fora\n");
    printf("(7) - cota do time casa\n");
    printf("(8) - cota do time Fora\n");
    printf("(9) - cota do time Empate\n");
    printf("(10) - Sair\n");
    printf("--------------------------------------------------------------------------\n");
}

void alteraJogos(Jogo* j){
  int idAltera;
  do{
    system("cls");
    menuAltera();
    printf("digite a opcao: ");
    scanf(" %d",&idAltera);

    if(idAltera == 1){
        char nomeNovo[31];
        printf("digite o o novo nome ou correcao!\n");
        scanf(" %[^\n]",nomeNovo);
        strcpy(j->campeonato, nomeNovo);
    }else if(idAltera == 2){
         if(j->status == 1){
            j->status = 0;
         }

    }else if(idAltera == 3){
            char timeCasa[31];
            printf("digite o nome corrigido:\n");
            scanf(" %[^\n]",timeCasa);
            strcpy(j->timeCasa, timeCasa);
    }else if(idAltera == 4){
            char timeFora[31];
            printf("digite o nome corrigido:\n");
            scanf(" %[^\n]",timeFora);
            strcpy(j->timeFora, timeFora);
    }else if(idAltera == 5){
       int golsAltualizado;
       printf("digite o total de gols atualizado do time Casa:\n");
       scanf(" %d",&golsAltualizado);
       j->golsCasa = validarGols(golsAltualizado);
    }else if(idAltera == 6){
       int golsAltualizado;
       printf("digite o total de gols atualizado do time Fora:\n");
       scanf(" %d",&golsAltualizado);
       j->golsFora = validarGols(golsAltualizado);
    }else if(idAltera == 7){
       float atualizarCotaCasa;
       printf("digite a cota Casa atualizada:\n");
       scanf(" %f",&atualizarCotaCasa);
       j->valorCasa = validarValorCota(atualizarCotaCasa);

    }else if(idAltera == 8){
       float atualizarCotaFora;
       printf("digite a cota Casa atualizada:\n");
       scanf(" %f",&atualizarCotaFora);
       j->valorFora = validarValorCota(atualizarCotaFora);

    }else if(idAltera == 9){
       float atualizarCotaEmpate;
       printf("digite a cota Casa atualizada:\n");
       scanf(" %f",&atualizarCotaEmpate);
       j->valorEmpate = validarValorCota(atualizarCotaEmpate);
    }else{
       printf("opcao invalida! saindo....\n");
    }
  }while(idAltera < 0 || idAltera < 10);

}

int contJogosArquivo(){
    FILE* arq = fopen("./tabelaDeJogo.txt", "r");
      if(arq == NULL){
         return 0;
      }
          int id, cont = 0;
          int status;
          char camp[31];
          char timeCasa[31];
          char timeFora[31];
          int golsCasa;
          int golsFora;
          float valorCasa;
          float valorFora;
          float valorEmpate;
     while(fscanf(arq, "%d\t%d\t%d\t%d\t%[^\t]\t%s\t%s\t%f\t%f\t%f",&id,&status,&golsCasa,&golsFora,camp,timeCasa,timeFora,&valorCasa,&valorFora,&valorEmpate) != EOF){
        cont++;
     }

     fclose(arq);
     return cont;
}

Jogo* lerDadosJogos(){
    Jogo* j = (Jogo*) malloc (contJogosArquivo() * sizeof(Jogo));
    if(j == NULL){
        printf("memoria insuficiente!\n");
        exit(1);
    }
    int index = 0;

    FILE* arq = fopen("./tabelaDeJogo.txt", "r");
    if(arq == NULL){
        printf("memoria insuficiente!\n");
        exit(1);
    }
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

     while(fscanf(arq, "%d\t%d\t%d\t%d\t%[^\t]\t%s\t%s\t%f\t%f\t%f",&id,&status,&golsCasa,&golsFora,camp,timeCasa,timeFora,&valorCasa,&valorFora,&valorEmpate) != EOF){
        j[index].id = id;
        j[index].status = status;
        strcpy(j[index].campeonato, camp);
        strcpy(j[index].timeCasa, timeCasa);
        strcpy(j[index].timeFora, timeFora);
        j[index].golsCasa = golsCasa;
        j[index].golsFora = golsFora;
        j[index].valorCasa = valorCasa;
        j[index].valorFora = valorFora;
        j[index].valorEmpate = valorEmpate;
        index++;
     }
    return j;
}

static void ordenarVetorJogo(Jogo* j){

    for(int i = 0; i < contJogosArquivo() - 1; i++){
            for(int jj = 0; jj < contJogosArquivo() - i - 1; jj++){
                    if(j[i].id > j[jj + 1].id){
                         Jogo troca = j[jj];
                         j[jj] = j[jj + 1];
                         j[jj + 1] = troca;
                    }
            }
    }

}

void imprimeJogoNaAposta(Jogo* j){
    if(contJogosArquivo() == 0){
        printf("nao a jogo aqui!\n");
    }else{
        ordenarVetorJogo(j);
        for(int i = 0; i < contJogosArquivo(); i++){
            printf("-----------------------------------------------------------------------------------------\n");
            printf("\t\t\t\t Campeontano %s\t\t\t\t\n",j[i].campeonato);
            printf("-----------------------------------------------------------------------------------------\n");
            printf("\t\t\t\t Id do jogo: %d \t\t\t\n",j[i].id);
            printf("-----------------------------------------------------------------------------------------\n");
            printf("\t time_Casa\t| CotarCasa\t| cotarEmpate\t| cotarFora\t| time_Fora\n");
            printf("-----------------------------------------------------------------------------------------\n");
            printf("\t\t%s  |    \t%.2f   |     \t%.2f   |    \t%.2f     |    %s\n",
             j[i].timeCasa,
             j[i].valorCasa,
             j[i].valorEmpate,
             j[i].valorFora,
             j[i].timeFora
             );
            printf("-----------------------------------------------------------------------------------------\n");
        }
   }
}

static void tabelaOpcaoAltera(){
printf("-----------------------------------------------------------------------\n");
printf("\t\t\t        MENU DE ALTERACAO                                        \n");
printf("-----------------------------------------------------------------------\n");
printf("(1) - ALTERAR NOME CAMPEONATO\n");
printf("(2) - ALTERAR STATUS DO JOGO\n");
printf("(3) - ALTERAR GOLS DO TIME CASA\n");
printf("(4) - ALTERAR GOLS DO TIME FORA\n");
printf("(5) - ALTERAR NOME TIME CASA\n");
printf("(6) - ALTERAR NOME TIME FORA\n");
printf("(7) - ALTERAR COTA TIME CASA\n");
printf("(8) - ALTERAR COTA DE FORA\n");
printf("(9) - ALTERAR COTA DE EMPATE\n");
printf("(10) - SAIR\n");
printf("------------------------------------------------------------------------\n");
}

void modificarJogo(Jogo* j){
  int op;
  do{
        system("cls");
    tabelaOpcaoAltera();
    printf("digite a opcao: ");
    scanf(" %d",&op);
    if(op == 1){
        char nome_campeonato[31];
        printf("digite o nome novo!\n");
        scanf(" %[^\n]",nome_campeonato);
        strcpy(j->campeonato, nome_campeonato);
    }else if(op == 2){
        if(j->status == 1){
            j->status = 0;
        }
    }else if(op == 3){
        int altera_gols_casa;
        printf("digite o total de gols alterado do time casa!\n");
        scanf(" %d",&altera_gols_casa);
        j->golsCasa = validarGols(altera_gols_casa);
    }else if(op == 4){
        int altera_gols_fora;
        printf("digite o total de gols alterado do time fora!\n");
        scanf(" %d",&altera_gols_fora);
        j->golsFora = validarGols(altera_gols_fora);
    }else if(op == 5){
        char nome_casa[31];
        printf("digite o novo nome time casa!\n");
        scanf(" %s",nome_casa);
        strcpy(j->timeCasa, nome_casa);
    }else if(op == 6){
        char nome_fora[31];
        printf("digite o novo nome time fora!\n");
        scanf(" %s",nome_fora);
        strcpy(j->timeFora, nome_fora);
    }else if(op == 7){
        float novaCotaCasa;
        printf("digite a nova cota casa!\n");
        scanf(" %f",&novaCotaCasa);
        j->valorCasa = validarValorCota(novaCotaCasa);
    }else if(op == 8){
        float novaCotaFora;
        printf("digite a nova cota fora!\n");
        scanf(" %f",&novaCotaFora);
        j->valorFora = validarValorCota(novaCotaFora);
    }else if(op == 9){
        float novaCotaEmpate;
        printf("digite a nova cota empate!\n");
        scanf(" %f",&novaCotaEmpate);
        j->valorEmpate = validarValorCota(novaCotaEmpate);
    }else{
        printf("saindo....!\n");
    }
    system("pause");
    system("cls");
  }while(op > 0 && op < 10);

}

