/**
NOME: Gabriel Meirelles Carvalho Orlando
RA: 790728

NOME: Eric Pereira Queiroz Moreira		
RA: 799662

CURSO: Ciencia da Computação
DATA: 19/10/2021
FLAGS: -std=c99 -Wall -Werror -Werror=vla -pedantic-errors -g -lm
*/
#include "t1.h"

int main(){

    add end;
    Reg registro;

    char string[sizeof(Reg)];

    int continuar = 0;
    FILE *arquivo = malloc(sizeof(FILE*));

    //Laço principal
    while(continuar != 7)
    {
       
        //Entrada da opção
        menu(&continuar);

        //Cria o arquivo
        if(continuar == 0){
            if(criaArquivo(N_ARQUIVO))
                printf("Arquivo criado com sucesso\n");
            else{
                printf("OPS, algo deu errado, encerrando a execucao...\n");
                return 0;
            }
        }

        //Insere no arquivo um registro lido
        else if(continuar == 1){
            print_insercao();
            scanf("%*c%[^\n]",string);
            sscanf(string,"%ld %s %s %s %s %s %s %d %s %s",&registro.key,registro.nome,registro.lName,registro.city,registro.state,registro.cep,registro.phone,&end.nro,end.rua,end.complemento);
            registro.adress = end;

            
            if(insere(arquivo,registro))
                printf("\nRegistro adicionado ao arquivo %s\n",N_ARQUIVO);
            else{
                printf("\nOPS, algo deu errado, a chave %ld ja esta inserida\n",registro.key);
            }
        }

        //Mostra os registro
        else if(continuar == 2){
            printf("\nRegistros do arquivo %s\n",N_ARQUIVO);
            le_arquivo(arquivo);
        }

        //Mostra o registro n
        else if(continuar==3){
            printf("Digite o numero do registro:");
            int nReg;
            scanf("%d",&nReg);
         
            if(!recupera_registro(arquivo,nReg))
                printf("\nOPS, algo deu errado, nao existe o registro %d...\n",nReg);
        }

        //Busca o registro de chave key
        else if(continuar == 4){
            printf("Digite o numero da chave:");
            long int key;
            int pos;
            scanf("%ld",&key);
           
            
            if(!busca_key(arquivo,key,&pos,TRUE))
                printf("\nOPS, algo deu errado, nao existe a chave %ld...\n",key);
        }

        //Busca o registro com a chave secundária fName
        else if(continuar == 5){
            printf("Digite o primeiro nome:");
            char nome[10];
            scanf("%*c%[^\n]",nome);
           
            
            if(!busca_fName(arquivo,nome))
                printf("\nOPS, algo deu errado, nao existe o nome %s...\n",nome);
        }

        //Remove um registro
        else if(continuar == 6){
            printf("Digite a chave para remover:");
            long int key;
            scanf("%ld",&key);
          
            
            if(!remove_logico(arquivo,key))
                printf("\nOPS, algo deu errado, nao existe a chave %ld...\n",key);
            else{
                printf("Registro com a chave %ld removido\n",key);
            }
        }

        //Encerra a execução
        else if(continuar == 7)
            printf("\nEncerrando o programa...\n");
    }
    
    //Exibe a lista de chaves secundárias
    print_arq_secundario();

    //Libera o arquivo
    free(arquivo);
    arquivo = NULL;
    return 0;
}
/*
gcc -std=c99 -Wall -Werror -Werror=vla -pedantic-errors -g -lm main.c t1.c t1.h -o 1

*/
