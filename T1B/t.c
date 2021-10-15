#include "t.h"

/*
1.A função abaixo tem como objetivo, a criação do arquivo principal de dados, pode ser usada tanto 
para resetar, quanto para criar um novo arquivo, com nome fixo
*/
int criaArquivo(char *n_arq) {
    FILE *arquivo = fopen(n_arq,"wb+");

    if(arquivo == NULL){
        return FALSE;
    }

    fclose(arquivo);
    return TRUE;
}

/*
2.As funções abaixo tem como objetivo fazer o print de algo em especifico, sua ultilidade apenas é
exibir os dados passados como parametros
*/
void menu(int *v) {
    printf("\n----------------MENU---------------------------------------------\n");
    printf("0)Criar arquivo\n1)Inserir\n2)Mostrar todos os registros\n3)Mostrar registro n\n4)Mostrar registro com a KEY x\n5)Mostrar registro com FNAME s\n6)Remover registro\n7)Sair\n");
    ml(0,0);
    printf("Digite o digito:");
    scanf("%d",v);

    if((*v)<0 || (*v)>7){
        printf("Digito invalido\n");
        menu(v);
    }
}
void print_insercao() {
    printf("Digite a entrada da seguinte forma:\n");
    printf("Chave Name lname City State Zip-Code Telefone Numero Rua Complemento\n");
    printf("->");
}


void print_add(add registro) {
    printf("ENDERECO = %s,%d,%s\n",registro.rua,registro.nro,registro.complemento);
}

void print_reg(Reg registro){
    printf("KEY = %ld\nLAST NAME = %s\nFIRST NAME = %s\nCITY = %s\nSTATE = %s\nCEP = %s\nPHONE = %s\n",registro.key,registro.lName,registro.nome,registro.city,registro.state,registro.cep,registro.phone);
    print_add(registro.adress);
}

void ml(int valor,int x) {
    if(x)
        printf("--------------------------Registro: %d--------------------------\n",valor);
    else
        printf("----------------------------------------------------------------\n");

    return ;
}

void escreve_arquivo(FILE *arquivo,Reg registro,char existe,int v[],int tam) {
    char delimitador = '|';
    char inicio_reg = '#';

    fwrite(&inicio_reg,sizeof(inicio_reg),1,arquivo);
    
    fwrite(&delimitador,sizeof(delimitador),1,arquivo);
    fwrite(&existe,sizeof(delimitador),1,arquivo);
    fwrite(&delimitador,sizeof(delimitador),1,arquivo);
    
    fwrite(&tam,sizeof(int),1,arquivo);
    fwrite(&delimitador,sizeof(delimitador),1,arquivo);

    for (int i=0;i<10;i++) {
        //Escreve o tamanho do campo
        fwrite(&v[i],sizeof(int),1,arquivo);
        fwrite(&delimitador,sizeof(delimitador),1,arquivo);
        
        switch (i) {
            case 0:
                fwrite(&registro.key,v[0],1,arquivo);
                break;

            case 1:
                fwrite(&registro.lName,v[1],1,arquivo);
                break;
                
            case 2:
                fwrite(&registro.nome,v[2],1,arquivo);
                break;

            case 3:
                fwrite(&registro.adress.nro,v[3],1,arquivo);
                break;

            case 4:
                fwrite(&registro.adress.rua,v[4],1,arquivo);
                break;

            case 5:
                fwrite(&registro.adress.complemento,v[5],1,arquivo);
                break;

            case 6:
                fwrite(&registro.city,v[6],1,arquivo);
                break;

            case 7:
                fwrite(&registro.state,v[7],1,arquivo);
                break;

            case 8:
                fwrite(&registro.cep,v[8],1,arquivo);
                break;

            case 9:
                fwrite(&registro.phone,v[9],1,arquivo);
                break;

            default:
                printf("ERRO\n");
                break;
        }

        if(i != 9)
            fwrite(&delimitador,sizeof(delimitador),1,arquivo);

    }

}

void le_arquivo(FILE *arquivo) {
    char inicio_reg,delimitador,existe;
    int v[10];
    int tam;
    Reg registro;
    int contador=0;

    while(fread(&inicio_reg,sizeof(inicio_reg),1,arquivo)) {
        fread(&delimitador,sizeof(delimitador),1,arquivo);
        fread(&existe,sizeof(delimitador),1,arquivo);
        fread(&delimitador,sizeof(delimitador),1,arquivo);
        

        fread(&tam,sizeof(int),1,arquivo);
        fread(&delimitador,sizeof(delimitador),1,arquivo);

        if(existe == '0') {
            //Pular para o proximo registro, que estará na pos SEEK_CURR + TAM-1
            printf("%ld\n",ftell(arquivo));
            fseek(arquivo,tam-1,SEEK_CUR);
            printf("%ld\n",ftell(arquivo));
        }

        else {
            printf("%ld\n",ftell(arquivo));
            for(int i=0;i<10;i++) {
                //Escreve o tamanho do campo
                fread(&v[i],sizeof(int),1,arquivo);
                fread(&delimitador,sizeof(delimitador),1,arquivo);
                
                switch (i) {
                    case 0:
                        fread(&registro.key,v[0],1,arquivo);
                        break;
                    case 1:
                        fread(&registro.lName,v[1],1,arquivo);
                        break;
                    case 2:
                        fread(&registro.nome,v[2],1,arquivo);
                        break;
                    case 3:
                        fread(&registro.adress.nro,v[3],1,arquivo);
                        break;
                    case 4:
                        fread(&registro.adress.rua,v[4],1,arquivo);
                        break;
                    case 5:
                        fread(&registro.adress.complemento,v[5],1,arquivo);
                        break;
                    case 6:
                        fread(&registro.city,v[6],1,arquivo);
                        break;
                    case 7:
                        fread(&registro.state,v[7],1,arquivo);
                        break;
                    case 8:
                        fread(&registro.cep,v[8],1,arquivo);
                        break;
                    case 9:
                        fread(&registro.phone,v[9],1,arquivo);
                        break;
                    default:
                        printf("ERRO\n");
                        break;
                }
                
                if(i != 9)
                    fread(&delimitador,sizeof(delimitador),1,arquivo);
            }

            ml(contador,1);
            printf("%c%c%c%c%d%c\n",inicio_reg,delimitador,existe,delimitador,tam,delimitador);
            print_reg(registro);
            ml(contador,0);

            contador++;
        }

        printf("%ld\n",ftell(arquivo));
    }
}