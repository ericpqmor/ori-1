/**
NOME: Gabriel Meirelles Carvalho Orlando
RA: 790728

NOME: Eric Pereira Queiroz Moreira		
RA: 799662

CURSO: Ciencia da Computação
DATA: 19/10/2021
FLAGS: -std=c99 -Wall -Werror -Werror=vla -pedantic-errors -g -lm
*/


#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <ctype.h>


#define TRUE 1
#define FALSE 0

#define NOME_ARQUIVO "arquivo.bin"
#define NOME_ARQUIVO_SECUNDARIO "arquivo_secundaria.bin"



//Registro de tamanho fixo/campos de tamanho fixo
typedef struct endereco{
    char rua[21];
    int nro;
    char complemento[10];
}add;

typedef struct Registro
{
    long int key;
    char lName[11];
    char nome[10];
    add adress;
    char city[24];
    char state[3];
    char cep[10];//cep, dps trocar
    char phone[15];//phone, dps trocar
}Reg;

typedef struct secundaria{

    char nome[10];
    int i[20];

}cSec;



int criar_arquivo(char *n_arq);


void escrever_arquivo(FILE *arquivo,Reg registro,char existe,int v[],int tam,int sobrouEspaco);
void escrever_arquivo_secundario(FILE *arquivo,cSec registro, char existe);
void ler_arquivo(FILE *arquivo);

//Métodos de impressão
void print_reg(Reg registro);
void print_add(add registro);
void print_insercao();
void ml(int valor,int x);
void menu(int *v);

//
void mostra_registro(FILE *arquivo,int byte_offset,int c);
int  busca_key(FILE *arquivo,long int key,int *pos,int *tam,char nome[10],int booleano);
int  busca_fName(FILE *arquivo,char fName[10]);


//Remocao de registros
int remove_logico(FILE *arquivo,long int key);


//Remoção do arquivo de indices secundarios
void remove_arq_secundario(FILE *arquivo,char fName[10],int indice);
int verifica_indice_secundario(FILE *arquivo,int *pos);
int tamanho_disponivel(FILE *arquivo,char fName[10]);

//Inserção de registros
int insere(FILE *arquivo,Reg registro);

//Verifica remoção lógica
int verifica(FILE *arquivo,int tamanho,int *pos,int *restante);

//Inserção do arquivo de indices primarios

//Inserção do arquivo de indices secundarios
void insere_arq_secundario(FILE *arquivo,char nome[10],int indice,int tem_remocao);
void ajusta_insercao_secundario(FILE *arquivo,int pos);
int compara(char n[10],char p[10]);


//Funções auxiliares
void print_arq_secundario();
void calcula_tamanho(Reg registro,int v[],int *tam);