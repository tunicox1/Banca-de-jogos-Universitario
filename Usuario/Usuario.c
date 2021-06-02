#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../apostas/apostas.h"
#include "../Jogo/jogo.h"
#include "../Jogo/ArvBinJogo/ArvBinJogo.h"
#include "Usuario.h"

#define M 101

struct usuario{
  int id;
  char nome[100];
  char senha[100];
  int nivelDeAcesso;
  float carteira;
  Usuario* prox;
};

struct hash{
    Usuario* users[M];
};
//funcoes para a tabela hash
Hash* hsh_cria(void){
    Hash* tabela = (Hash*) malloc(sizeof(Hash));
    if(tabela == NULL){
        printf("Memoria insuficiente para a tabela!!");
        exit(1);
    }
    int i;
    for(i=0;i<M;i++)
        tabela->users[i] = NULL;

    return tabela;
}

static int hash(int id){
    return id%M;
}

int gerarId(char* nome){
    int i, h = *(nome+0);
    for(i=1;*(nome+i) != '\0';i++){
        h = h*256 + *(nome+i);
    }

    return h;
}

Usuario* hsh_insere(Hash* tab,Usuario* user){
    int h = hash(user->id);
    if(hsh_busca(tab,user->id)!=NULL){
        return NULL;
    }
    user->prox = tab->users[h];
    tab->users[h] = user;
    return user;
}

Usuario* hsh_busca(Hash* tab, int id){
    int h = hash(id);
    Usuario* u = tab->users[h];
    while(u!=NULL){
        if(u->id == id)
            return u;
        u=u->prox;
    }
    return NULL;
}

Usuario* criarUsuario(char* nome, char* senha, int nivelDeAcesso, float carteira){

  Usuario* user = (Usuario*) malloc(sizeof(Usuario));

  if(user == NULL){
    printf("memoria insuficiente!\n");
    exit(1);
  }
  strcpy(user->nome, nome);
  strcpy(user->senha, senha);

  user->id = gerarId(user->nome);

  user->nivelDeAcesso = nivelDeAcesso;

  user->carteira = carteira;

  user->prox = NULL;

  return user;
}

void atualizarUsuarios(){
    Aposta* Ap = lerApostas();

    Hash* tab = hsh_cria();
    lerUsuarios(tab);

    Arv* jogos = jj_cria_jogo();
    jogos = jj_lerArquivoJogos();

    int i;

    for(i=0;i<M;i++){
        if(tab->users[i]!=NULL){
            Usuario* aux = tab->users[i];
            while(aux!=NULL){
                atualizarApostas(Ap,jogos,aux);
                aux = aux->prox;
            }
        }
    }
}
void atualizarDadosUsuario(Usuario* user){
    Hash* tab = hsh_cria();
    lerUsuarios(tab);
    int posicao = hash(user->id);
    tab->users[posicao] = user;
    salvarUsuarios(tab);
}

void lerUsuarios(Hash* tab){
    FILE* usuariosDB = fopen("./Usuario/usuarios.txt","r");
    char linha[400];
    while(fgets(linha,400, usuariosDB)!=NULL){
        Usuario* user = criarUsuario("temp","123",0,0);
        sscanf(linha,"%d\t%[^\t]\t%[^\t]\t%d\t%f",&user->id,user->nome,user->senha,&user->nivelDeAcesso,&user->carteira);
        hsh_insere(tab,user);
    }
}
Usuario* buscarUsuario(int nivelDeAcesso){
    Hash* tab = hsh_cria();
    lerUsuarios(tab);
    int i;
    for(i=0;i<M;i++){
        if(tab->users[i]!=NULL){
            Usuario* aux = tab->users[i];
            while(aux!=NULL){
                if(aux->nivelDeAcesso == nivelDeAcesso){
                    return aux;
                }
                aux = aux->prox;
            }
        }
    }
    return NULL;
}
Usuario* buscarUsuarioNome(char* nome){
    Hash* tab = hsh_cria();
    lerUsuarios(tab);
    int i;
    for(i=0;i<M;i++){
        if(tab->users[i]!=NULL){
            Usuario* aux = tab->users[i];
            while(aux!=NULL){
                if(strcmp(nome,aux->nome)==0){
                    return aux;
                }
                aux = aux->prox;
            }
        }
    }
    return NULL;
}
void salvarUsuarios(Hash* tab){
  int i;
  FILE* usuariosDB = fopen("./Usuario/usuarios.txt","w");
  for(i=0;i<M;i++){
    if(tab->users[i]!=NULL){
        Usuario* usuario = tab->users[i];
        while(usuario!=NULL){
            fprintf(usuariosDB,"%d\t%s\t%s\t%d\t%.2f\n",usuario->id, usuario->nome, usuario->senha, usuario->nivelDeAcesso, usuario->carteira);
            usuario = usuario->prox;
        }
    }
  }
  fclose(usuariosDB);

}

int getIdUsuario(Usuario* usuario){
  return usuario->id;
}

char* getNomeUsuario(Usuario* usuario){
    return usuario->nome;
}

int getSenhaUsuario(Usuario* usuario){
  return usuario->senha;
}

int getNivelDeAcesso(Usuario* usuario){
    return usuario->nivelDeAcesso;
}

float getCarteira(Usuario* usuario){
    return usuario->carteira;
}
void setCarteira(Usuario* usuario, float valor){
    usuario->carteira = valor;
}

