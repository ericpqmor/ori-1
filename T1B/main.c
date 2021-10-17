#include "t.h"

int main(){

    add end;
    Reg registro;

    char string[sizeof(Reg)];

    int continuar = 0;
    FILE *arquivo = malloc(sizeof(FILE*));
    while(continuar != 6)
    {
       
        menu(&continuar);

        if(continuar == 0){
            if(criaArquivo(N_ARQUIVO))
                printf("Arquivo criado com sucesso\n");
            else{
                printf("OPS, algo deu errado, encerrando a execucao...\n");
                return 0;
            }
        }

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

        else if(continuar == 2){
            printf("\nRegistros do arquivo %s\n",N_ARQUIVO);
            le_arquivo(arquivo);
        }
        else if(continuar == 3){
            printf("Digite o numero da chave:");
            long int key;
            int pos,tam;
            char nome[10];
            scanf("%ld",&key);
           
            
            if(!busca_key(arquivo,key,&pos,&tam,nome,TRUE))
                printf("\nOPS, algo deu errado, nao existe a chave %ld...\n",key);
        }
        else if(continuar == 4){
            printf("Digite o primeiro nome:");
            char nome[10];
            scanf("%*c%[^\n]",nome);
           
            
            if(!busca_fName(arquivo,nome))
                printf("\nOPS, algo deu errado, nao existe o nome %s...\n",nome);
        }

        else if(continuar == 5){
            printf("Digite a chave para remover:");
            long int key;
            scanf("%ld",&key);
          
            
            if(!remove_logico(arquivo,key))
                printf("\nOPS, algo deu errado, nao existe a chave %ld...\n",key);
        }

        else if(continuar == 6)
            printf("\nEncerrando o programa...\n");
    }
    
    print_arq_secundario();
    free(arquivo);
    arquivo = NULL;
    return 0;
}
/*
gcc -std=c99 -Wall -Werror -Werror=vla -pedantic-errors -g -lm main.c t.c t.h -o 1

*/
