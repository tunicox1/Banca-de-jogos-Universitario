#ifndef USUARIO_H_INCLUDED
#define USUARIO_H_INCLUDED

typedef struct usuario Usuario;

typedef struct hash Hash;

Hash* hsh_cria(void);

Usuario* hsh_insere(Hash* tab,Usuario* user);

Usuario* hsh_busca(Hash* tab, int id);

int gerarId(char* nome);

Usuario* criarUsuario(char* nome, char* senha, int nivel_de_acesso, float carteira);

void atualizarUsuario(Usuario* usuario);

void salvarUsuarios(Hash* tab);

void lerUsuarios(Hash* tab);

void imprimirUsuario(Usuario* usuario);

Usuario* buscarUsuario(int nivelDeAcesso);

int getIdUsuario(Usuario* usuario);

char* getNomeUsuario(Usuario* usuario);

int getSenhaUsuario(Usuario* usuario);

int getNivelDeAcesso(Usuario* usuario);

float getCarteira(Usuario* usuario);

void setCarteira(Usuario* usuario, float valor);

void atualizarDadosUsuario(Usuario* user);

void atualizarUsuarios();

Usuario* buscarUsuarioNome(char* nome);
#endif // USUARIO_H_INCLUDED
