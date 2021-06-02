#include <stdio.h>
#include <stdlib.h>
#include "./Usuario/Usuario.h"
#include"./Jogo/Jogo.h"
#include"./apostas/apostas.h"




void menuCadastroBanca(){
  printf("-------------------------------------------------------------\n");
  printf("\tDigite as informacoes para cadastrar a sua banca\n");
  printf("-------------------------------------------------------------\n");

}

void menuDeErro(char* mensagem){
  printf("-------------------------------------------------------------\n");
  printf("%s\n",mensagem);
  printf("-------------------------------------------------------------\n");
  printf("\t1 - SIM\n");
  printf("\t2 - NAO\n");
  printf("-------------------------------------------------------------\n");
  printf("Informe a opcao: ");

}

void menuDeMensagem(char* mensagem){
  printf("-------------------------------------------------------------\n");
  printf("%s\n",mensagem);
  printf("-------------------------------------------------------------\n");
}

void menuLogin(){
  printf("-------------------------------------------------------------\n");
  printf("\tBem vindo, Digite suas informacoes para entrar\n");
  printf("-------------------------------------------------------------\n");
}

void menuCadastroUsuario(){
  printf("-------------------------------------------------------------\n");
  printf("\tDigite as informacoes do Usuario\n");
  printf("-------------------------------------------------------------\n");
}

void menuTelaInicial(){
  printf("-------------------------------------------------------------\n");
  printf("1 - Tela Login\n");
  printf("2 - Tela Cadastro\n");
  printf("3 - Sair\n");
  printf("-------------------------------------------------------------\n");
}

void menuSistemaLogado(Usuario* user){
  int nivelDeAcesso =  getNivelDeAcesso(user);
  printf("-------------------------------------------------------------\n");
  printf("Bem vindo a area de logado do sistema %s  SALDO = %.2f\n",getNomeUsuario(user),getCarteira(user));
  printf("-------------------------------------------------------------\n");
  if(nivelDeAcesso==0){
    printf("1 - Efetuar deposito em conta\n");
  }else{
    printf("1 - Apostas\n");
  }
  printf("2 - Jogos\n");
  printf("3 - Sair\n");
  printf("-------------------------------------------------------------\n");
}

void MenuAposta(Usuario* user){
    system("cls");
    menuDeMensagem("\tMenu de apostas!!");
}

void logado(Usuario* user){
    int opcao,nivelDeAcesso = getNivelDeAcesso(user);
    do{
      user = buscarUsuarioNome(getNomeUsuario(user));
      menuSistemaLogado(user);
      printf("Digite a opcao: ");
      scanf("%d",&opcao);
      switch(opcao){
        case(1):{
          system("cls");
          if(nivelDeAcesso==0){
            float valor;
            char nome[100];
            printf("Digite o valor a ser depositado: ");
            scanf("%f",&valor);
            printf("Digite o nome da pessoa que deseja depositar: ");
            scanf(" %[^\n]",nome);
            Usuario* us = buscarUsuarioNome(nome);
            if(us!=NULL){
                float novaCarteira = getCarteira(us)+valor;
                setCarteira(us, novaCarteira);
                atualizarDadosUsuario(us);
                printf("Valor depositado com sucesso!\n");
            }else{
                printf("Usuario nao encontrado!");
            }
          }else{
            menuAposta(user);
          }
          break;
        }
        case(2):{
          system("cls");
          menuJogo(user);
          break;
        }
        case(3):{
          system("cls");
          menuDeMensagem("\t\tDeslogado com sucesso!!");
          break;
        }
        default:
            system("cls");
            menuDeMensagem("\tOPCAO INVALIDA!!\n\tDIGITE NOVAMENTE!!");
      }
  }while(opcao!=3);
}

void cadastrarBanca(Hash* tabelaUsuarios){
    char nome[100];
    char senha[100];
    float carteira = 0;
    menuCadastroBanca();
    printf("nome: ");
    scanf("%[^\n]",nome);
    printf("senha: ");
    scanf(" %[^\n]",senha);
    printf("Saldo da banca: ");
    scanf("%f",&carteira);

    Usuario* admin = criarUsuario(nome, senha, 0, carteira);
    hsh_insere(tabelaUsuarios,admin);
    salvarUsuarios(tabelaUsuarios);

}

void cadastrarUsuario(Hash* tabelaUsuarios){
    system("cls");
    char nome[100]="";
    char senha[100]="";
    int opcao;
    do{
    menuCadastroUsuario();

    printf("nome: ");
    scanf(" %[^\n]",nome);
    printf("senha: ");
    scanf(" %[^\n]",senha);

    Usuario* user = criarUsuario(nome, senha, 1, 0);
    user = hsh_insere(tabelaUsuarios, user);

    if(user==NULL){
        menuDeErro("\tJa existe um usuario cadastrado com este nome!!\n\tDeseja tentar novamente??");
        scanf("%d",&opcao);
    }else{
        menuDeMensagem("\tUsuario cadastrado com sucesso!!\n");
        salvarUsuarios(tabelaUsuarios);
        system("pause");
        opcao=2;
    }

    system("cls");
    }while(opcao!=2);

}

void logarUsuario(Hash* tabelaUsuarios){
  system("cls");
  char nome[100];
  char senha[100];
  int opcao;
  do{
  menuLogin();

  printf("\tnome: ");
  scanf(" %[^\n]",nome);
  printf("\tsenha: ");
  scanf(" %[^\n]",senha);
  printf("-------------------------------------------------------------\n");
  printf("\n");
  int id = gerarId(nome);
  Usuario* user = hsh_busca(tabelaUsuarios,id);

  if(user==NULL){
    menuDeErro("\tUsuario nao encontrado!!\n\tDeseja tentar logar novamente??");
    scanf("%d",&opcao);
    system("cls");
  }else{
    if(strcmp(getNomeUsuario(user),nome)==0 && strcmp(getSenhaUsuario(user),senha)==0){
        system("cls");
        menuDeMensagem("\tUSUARIO LOGADO COM SUCESSO!!");

        logado(user);
        opcao = 2;
    }else{
        menuDeErro("\tUsuario ou senha incorretos!!\n\tDeseja tentar logar novamente??");
        scanf("%d",&opcao);
        system("cls");
    }
  }
  }while(opcao!=2);
}

Hash* inicializarDados(){
    Hash* tabela = hsh_cria();
    lerUsuarios(tabela);
    return tabela;
}

void menuInicial(Hash* tabelaUsuarios){

  FILE* usuarios = fopen("./Usuario/usuarios.txt", "r");

  if(usuarios == NULL){
    cadastrarBanca(tabelaUsuarios);
  }
  fclose(usuarios);
  int opcao;
  do{
      menuTelaInicial();
      printf("Digite a opcao: ");
      scanf("%d",&opcao);
      switch(opcao){
        case(1):
          logarUsuario(tabelaUsuarios);
          tabelaUsuarios = inicializarDados();
          break;
        case(2):
          cadastrarUsuario(tabelaUsuarios);
          break;
        case(3):
          system("cls");
          menuDeMensagem("\t\tPrograma finalizado!!");
          exit(1);
          break;
        default:
            system("cls");
            menuDeMensagem("\tOPCAO INVALIDA!!\n\tDIGITE NOVAMENTE A OPCAO");
      }
  }while(opcao!=3);

}



int main(void) {

  Hash* tabelaUsuarios = inicializarDados();

  menuInicial(tabelaUsuarios);

  salvarUsuarios(tabelaUsuarios);
  return 0;
}
