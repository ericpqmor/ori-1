/**
NOME: Gabriel Meirelles Carvalho Orlando
RA: 790728

NOME: Eric Pereira Queiroz Moreira		
RA: 799662

CURSO: Ciencia da Computação
DATA: 19/10/2021
FLAGS: -std=c99 -Wall -Werror -Werror=vla -pedantic-errors -g -lm
*/

#include "t.h"



/*
1.A função abaixo tem como objetivo, a criação do arquivo principal de dados, pode ser usada tanto para resetar, quanto para criar um novo arquivo, com nome
fixo
*/
int criar_arquivo(char *n_arq){

    FILE *arquivo = fopen(n_arq,"wb+");


    if(arquivo == NULL){
        return FALSE;
    }

    fclose(arquivo);
    return TRUE;
    
}

/*
2.As funções abaixo tem como objetivo fazer o print de algo em especifico, sua ultilidade apenas é exibir os dados passados como parametros
*/
void menu(int *v){

    printf("\n----------------MENU---------------------------------------------\n");
    printf("0)Criar arquivo\n1)Inserir\n2)Mostrar todos os registros\n3)Mostrar registro com a KEY x\n4)Mostrar registro com FNAME s\n5)Remover registro\n6)Sair\n");
    ml(0,0);
    printf("Digite o digito:");
    scanf("%d",v);

    if((*v)<0 || (*v)>6){
        printf("Digito invalido\n");
        menu(v);
    }
}
void print_insercao(){

    printf("Digite a entrada da seguinte forma:\n");
    printf("Chave Name lname City State Zip-Code Telefone Numero Rua Complemento\n");
    printf("->");
}


void print_add(add registro){
    printf("ENDERECO = %s,%d,%s\n",registro.rua,registro.nro,registro.complemento);
}

void print_reg(Reg registro){

    printf("KEY = %ld\nLAST NAME = %s\nFIRST NAME = %s\nCITY = %s\nSTATE = %s\nCEP = %s\nPHONE = %s\n",registro.key,registro.lName,registro.nome,registro.city,registro.state,registro.cep,registro.phone);
    print_add(registro.adress);
}

void ml(int valor,int x){
    if(x)
        printf("--------------------------Registro: %d--------------------------\n",valor);
    else
        printf("----------------------------------------------------------------\n");

    return ;
}

/*3.Funções abaixo são funções para escreverem nos arquivos, elas devevem ser chamadas com os arquivos previamente abertos em modo que permite a escrita
*/
void escrever_arquivo_secundario(FILE *arquivo,cSec registro, char existe){

    char delimitador = '|';

    fwrite(&delimitador,sizeof(delimitador),1,arquivo);
    fwrite(&existe,sizeof(delimitador),1,arquivo);
    fwrite(&delimitador,sizeof(delimitador),1,arquivo);
    fwrite(&registro,sizeof(cSec),1,arquivo);

}

void escrever_arquivo(FILE *arquivo,Reg registro,char existe,int v[],int tam,int sobrouEspaco){

    char delimitador = '|';
    char inicio_reg = '#';

    fwrite(&inicio_reg,sizeof(inicio_reg),1,arquivo);
    
    fwrite(&delimitador,sizeof(delimitador),1,arquivo);
    fwrite(&existe,sizeof(delimitador),1,arquivo);
    fwrite(&delimitador,sizeof(delimitador),1,arquivo);
    
    fwrite(&tam,sizeof(int),1,arquivo);
    fwrite(&delimitador,sizeof(delimitador),1,arquivo);

    if(!sobrouEspaco){
        for(int i=0;i<10;i++){
            //Escreve o tamanho do campo
            fwrite(&v[i],sizeof(int),1,arquivo);
            fwrite(&delimitador,sizeof(delimitador),1,arquivo);
            
            switch (i){

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

}

/*4.Essa função lê todos os registros do arquivo de dados principal, e exibe os dados na tela
*/
void ler_arquivo(FILE *arquivo){

    char inicio_reg,delimitador,existe;
    int v[10];
    int tam;
    Reg registro;
    int contador=0;

    arquivo = fopen(NOME_ARQUIVO,"rb");

    while(fread(&inicio_reg,sizeof(inicio_reg),1,arquivo)){

        fread(&delimitador,sizeof(delimitador),1,arquivo);
        fread(&existe,sizeof(delimitador),1,arquivo);
        fread(&delimitador,sizeof(delimitador),1,arquivo);
        

        fread(&tam,sizeof(int),1,arquivo);
        fread(&delimitador,sizeof(delimitador),1,arquivo);

        if(existe == '0'){
            //Pular para o proximo registro, que estará na pos SEEK_CURR + TAM-1
            printf("%c%c%c%c%d%c\n",inicio_reg,delimitador,existe,delimitador,tam,delimitador);
            fseek(arquivo,tam-1,SEEK_CUR);

        }

        else{

            for(int i=0;i<10;i++){
                //Escreve o tamanho do campo
                fread(&v[i],sizeof(int),1,arquivo);
                fread(&delimitador,sizeof(delimitador),1,arquivo);
                
                switch (i){

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
            sleep(1);

            contador++;
        }      
    }
    fclose(arquivo);
}

/*5.Funções que verificam a existenia de remoção lógica nos arquivos, tanto de chave secundaria, como arquivo de dados em geral
*/
int verifica_indice_secundario(FILE *arquivo,int *pos){
    arquivo = fopen(NOME_ARQUIVO_SECUNDARIO,"rb");

    cSec registro;
    char existe;
    char delimitador;

    int achou = FALSE;

    while(!achou && fread(&delimitador,sizeof(delimitador),1,arquivo) && fread(&existe,sizeof(delimitador),1,arquivo) &&
    fread(&delimitador,sizeof(delimitador),1,arquivo) && fread(&registro,sizeof(cSec),1,arquivo)){

        if(existe == '0')
            achou = TRUE;
    }

    if(!achou)
        return FALSE;

    *pos = ftell(arquivo) - (sizeof(cSec)+3);

    fclose(arquivo);

    return TRUE;

}

int verifica(FILE *arquivo,int tamanho,int *pos,int *restante){

    char inicio_reg,delimitador,existe;
    int tam;
    int achou = FALSE;

    arquivo = fopen(NOME_ARQUIVO,"rb");

    while(!achou && fread(&inicio_reg,sizeof(inicio_reg),1,arquivo)){

        fread(&delimitador,sizeof(delimitador),1,arquivo);
        fread(&existe,sizeof(delimitador),1,arquivo);
        fread(&delimitador,sizeof(delimitador),1,arquivo);
        

        fread(&tam,sizeof(int),1,arquivo);
        fread(&delimitador,sizeof(delimitador),1,arquivo);

        if(existe == '0'){
            //Verificar se tamanho cabe em tam
            int c = tam - tamanho;

            //Três ações
            if(c == 0){
                //Espaço é igual, entao pode inserir na posição, logo deve-se voltar algumas posições, mais especificamente 1+1+1+sizeof(int)+1
                *pos = ftell(arquivo) - (5+sizeof(int));
                *restante = 0;
                achou = TRUE;
            }
            else if(c >= 9){
            /*O registro cabe nessa posição removida,
             entao pode inserir na posição, logo deve-se voltar algumas posições, mais especificamente 1+1+1+sizeof(int)+1 e também
             deve-se colocar o espaço restante, como c*/
                *pos = ftell(arquivo) - (5+sizeof(int));
                *restante = c;
                achou = TRUE;
            }
            else{
                //Andar posição até chegar no próximo #
                fseek(arquivo,tam-1,SEEK_CUR);
            }
        }

        else//caso o valor de existe for igual a 1, apenas pular para o proximo #
            fseek(arquivo,tam-1,SEEK_CUR);
  
        }
    fclose(arquivo);
    if(!achou)
        return FALSE;

    return TRUE;
}
/*
6.Verifica se o vetor para a chave secundaria nome tem espaço suficiente
*/
int tamanho_disponivel(FILE *arquivo,char fName[10]){

    arquivo = fopen(NOME_ARQUIVO_SECUNDARIO,"rb");
    int achou = FALSE;
    char delimitador;
    char existe;
    cSec registro;

    while(!achou && (fread(&delimitador,sizeof(char),1,arquivo)==TRUE) &&(fread(&existe,sizeof(char),1,arquivo)==TRUE)&& 
    (fread(&delimitador,sizeof(char),1,arquivo)==TRUE) &&(fread(&registro,sizeof(cSec),1,arquivo) == TRUE)){

        int c = compara(fName,registro.nome);
        if(c < 0){
            fclose(arquivo);
            return TRUE;
        }
        else if(c == 0)
            achou = TRUE;
    }

    fclose(arquivo);
    if(achou){
        if(registro.i[19] != -1)
            return TRUE;
        else
            return FALSE;
    }

    return TRUE;


}
/*

7. As funções abaixo estão atreladas a inserção no arquivo de chaves secundárias, tão como a inserção de fato, como o ajuste, na ocorrencia de alguma remoção
lógica
*/
void insere_arq_secundario(FILE *arquivo,char nome[10],int indice,int tem_remocao){
    arquivo = fopen(NOME_ARQUIVO_SECUNDARIO,"rb+");

    if(arquivo == NULL){
        printf("OPS, algo deu errado, encerrando a execucao...\n");
        exit(1);
    }

    if(arquivo == NULL)
        return;

    cSec registro;
    int contador=0;
    int achou = FALSE;
    char delimitador;
    char existe;
    long int pos;
    int repetido = FALSE;
   // int ultimo = FALSE;
    
    while( !achou && (fread(&delimitador,sizeof(char),1,arquivo)==TRUE) &&(fread(&existe,sizeof(char),1,arquivo)==TRUE)&& (fread(&delimitador,sizeof(char),1,arquivo)==TRUE) &&
    (fread(&registro,sizeof(cSec),1,arquivo) == TRUE)){

        /* O metodo compara tem os seguintes resultados:
        Caso for negativo, a string nome é maior(vem antes) da string registro.nome, logo deve entrar na condição para parar
        Caso for positivo, a string registro.nome(vem atnes) da string nome, logo não se deve parar
        Zero, caso for igual, e também não deve parar
        */
        if(compara(nome,registro.nome) == 0){
            achou = TRUE;
            repetido = TRUE;
            pos = ftell(arquivo);
        }
        else if(compara(nome,registro.nome) < 0){
            achou = TRUE;
            pos = ftell(arquivo);
        }
    }

    cSec registro_auxiliar;
    char insercao = '1';
    delimitador = '|';
    strcpy(registro_auxiliar.nome,nome);

    
    if(!repetido){
        registro_auxiliar.i[0] = indice;
        registro_auxiliar.i[1] = -1;
    }
    else{
        registro_auxiliar = registro;
        //A chave secundaria esta repetida, logo so basta reescrever o vetor
        while(registro_auxiliar.i[contador] != -1){
            contador++;
        }
        registro_auxiliar.i[contador] = indice;
        registro_auxiliar.i[contador+1] = -1;
    }
    if(achou){
        pos = pos - (sizeof(cSec)+3);//vai para o ultimo byte que está antes do primeiro |
        fseek(arquivo,pos,SEEK_SET);
        //Novo registro adicionado
        escrever_arquivo_secundario(arquivo,registro_auxiliar,insercao);
        if(repetido){
            fclose(arquivo);
            return;
        }
    }
   

    if(!achou){

        if(tem_remocao){
            /*Isso significa que tem remoção e essa remoção ou houve em um elemento que estava sozinho ou no ultimo elemento
             logo a posição corrente do arquivo estará em uma posição boa, pois estará no final do registro*/
            fseek(arquivo,-(sizeof(cSec)+3),SEEK_CUR); 
            escrever_arquivo_secundario(arquivo,registro_auxiliar,insercao);
        }
        else{
            escrever_arquivo_secundario(arquivo,registro_auxiliar,insercao);
        }
        fclose(arquivo);
        return; //quer dizer, que foi o primeiro indice a ser inserido, ou na ultima posicao, logo não é necessario reorganizar
    }
    //Agora é necessário reorganizar os temos abaixo
    int acabou = FALSE;

    while(!acabou){
        pos = ftell(arquivo);

        if((fread(&delimitador,sizeof(char),1,arquivo)==FALSE) || (fread(&insercao,sizeof(char),1,arquivo)==FALSE)|| 
        (fread(&delimitador,sizeof(char),1,arquivo)==FALSE) ||(fread(&registro_auxiliar,sizeof(cSec),1,arquivo) == FALSE)){
            acabou = TRUE;
            
        }
        
        if(!acabou || (pos == ftell(arquivo) && !tem_remocao) ){
            fseek(arquivo,pos,SEEK_SET);

            escrever_arquivo_secundario(arquivo,registro,existe);

            existe = insercao;
            registro = registro_auxiliar;
        }
    }

    fclose(arquivo);    
}


void ajusta_insercao_secundario(FILE *arquivo,int pos){

     /*Existe um registro que foi removido logicamente, logo esse espaço deve ser reaproveitado e inserido um novo registro em seu lugar,
    para reorganizar, esse registro deve ir para a ultima posição do vetor, e isso será feito subindo todos os registro abaixo em uma posição, e nesse caso,
    o ultimo registro estará repetido, e isso não tem problema, pois no final ele será substituido por ele mesmo
*/
    arquivo = fopen(NOME_ARQUIVO_SECUNDARIO,"rb+");

    if(arquivo == NULL){
        printf("OPS, algo deu errado, encerrando a execucao...\n");
        exit(1);
    }

    int acabou = FALSE;
    int pos_corr = pos + sizeof(cSec)+3;
    fseek(arquivo,pos_corr,SEEK_SET);


    cSec registro;
    char delimitador,existe;

    while(!acabou){

        if((fread(&delimitador,sizeof(char),1,arquivo)==FALSE) || (fread(&existe,sizeof(char),1,arquivo)==FALSE)|| 
        (fread(&delimitador,sizeof(char),1,arquivo)==FALSE) ||(fread(&registro,sizeof(cSec),1,arquivo) == FALSE)){
            acabou = TRUE;
        }
        
        if(!acabou){
            fseek(arquivo,-2*(sizeof(cSec)+3),SEEK_CUR);

            escrever_arquivo_secundario(arquivo,registro,existe);

            fseek(arquivo,sizeof(cSec)+3,SEEK_CUR);
        }
    }

    fclose(arquivo);

}



/*8. A função abaixo representa a inserção em geral, que verifica as condições de inserção para evitar algum problema
*/
int insere(FILE *arquivo,Reg registro){

    /*Na inserção temos dois impasses, o primeiro é caso uma chave já tenha sido inserida, o outro impasse é caso o vetor de tamanho fixo, da chave
    secundaria Name, esteja cheio, nesses dois casos, a função deve retornar false e nem escrever nada.
    */

    arquivo = fopen(NOME_ARQUIVO_SECUNDARIO,"ab");
    fclose(arquivo);

    if(!tamanho_disponivel(arquivo,registro.nome))
        return FALSE;
    int v[10];
    int tam;
    int indice; //guarda o byte offset

    if(busca_key(arquivo,registro.key,&indice,&tam,registro.nome,FALSE)){
        return FALSE;
    }
    //Calcula o tamanho do registro e o tamanho de cada campo do registro
    calcula_tamanho(registro,v,&tam);

    int pos,restante;
    if(!verifica(arquivo,tam,&pos,&restante)){
        //Não é possível reaproveitar o espaço, logo o registro deve ser inserido no fim do arquivo
        arquivo = fopen(NOME_ARQUIVO,"ab");

        indice = ftell(arquivo); //byte offset

        escrever_arquivo(arquivo,registro,'1',v,tam,FALSE);
        fclose(arquivo);
    }

    else{
        /*É possível reaproveitar o espaço, logo deve-se inserir de uma maneira cuidadosa, abrindo o arquivo no modo rb+, para conseguir
        escrever sem alterar o arquivo*/
        arquivo = fopen(NOME_ARQUIVO,"rb+");

        fseek(arquivo,pos,SEEK_SET);

        indice = ftell(arquivo);

        /*Agora a posicao corrente do arquivo esta na posição em que se pode reaproveitar o espaço lógico*/
        escrever_arquivo(arquivo,registro,'1',v,tam,FALSE);

        //Agora temos que trabalhar na escrita do espaço restante
        if(restante != 0){//Isso significa que sobrou espaço suficiente para escrever o padrão, isso significa que tem pelo menos 9 bytes disponiveis
        
            restante -= 8;
            escrever_arquivo(arquivo,registro,'0',v,restante,TRUE);
        }

        fclose(arquivo);
    }

    int tem_remocao = FALSE;

    //Inserção nos arquivos de chave secundária
    if(verifica_indice_secundario(arquivo,&pos)){
        ajusta_insercao_secundario(arquivo,pos);
        tem_remocao = TRUE;
    }

    insere_arq_secundario(arquivo,registro.nome,indice,tem_remocao);

    return TRUE;
}

/*
9.A funçães abaixo está relacionada a remoção de arquivos de chave secundaria
*/
void remove_arq_secundario(FILE *arquivo,char nome[10],int indice){

   arquivo = fopen(NOME_ARQUIVO_SECUNDARIO,"rb+");
   
   if(arquivo == NULL){
        printf("OPS, algo deu errado, encerrando a execucao...\n");
        exit(1);
    }

    int pos;
    int achou = FALSE;
    char delimitador;
    char existe;
    cSec registro;
    int contador=0;
    int sozinho=TRUE;
    int sair = FALSE;

    //Apenas trocar o byteoffset para 0
   while(!sair && !achou && (fread(&delimitador,sizeof(char),1,arquivo)==TRUE) &&(fread(&existe,sizeof(char),1,arquivo)==TRUE)&& 
   (fread(&delimitador,sizeof(char),1,arquivo)==TRUE) &&(fread(&registro,sizeof(cSec),1,arquivo) == TRUE)){
        
        if(compara(nome,registro.nome)==0 && existe == '1'){

            while(registro.i[contador] != indice && registro.i[contador] != -1)
                contador++;
            if(registro.i[1] != -1){
                sozinho = FALSE;
            }

            if(registro.i[contador] == -1)
                sair = TRUE;
                
            else{
                pos = ftell(arquivo)- (sizeof(cSec)+3);
                achou = TRUE;
            }
        }
   }

   if(!achou || sair){
       fclose(arquivo);
        return;
   }

    fseek(arquivo,pos,SEEK_SET);
    if(!sozinho)
        existe = '1';
    else
        existe = '0';
    //Achou o indice/chave secundária que quer remover, logo, deve-se trazer uma posição para trás todos os indices do vetor
    //Contador é onde se localiza o indice
    while(registro.i[contador] != -1){
        registro.i[contador] = registro.i[contador+1];
        contador++;
    }

    escrever_arquivo_secundario(arquivo,registro,existe);

    fclose(arquivo);

    return;  
}

/*10.Remoção geral
*/
int remove_logico(FILE *arquivo,long int key){

    int pos;
    int tamanho;
    char nome[10];

    //Variaveis lixo
    Reg registro_lixo;
    int v[2];

    //Função busca key, que retorna o byte offsett do registro
    if(!busca_key(arquivo,key,&pos,&tamanho,nome,FALSE))
        return FALSE;
    
    //Chave foi encontrada, e na variavel pos, está o byte offset do registro


    arquivo = fopen(NOME_ARQUIVO,"rb+");
    fseek(arquivo,pos,SEEK_SET);


    escrever_arquivo(arquivo,registro_lixo,'0',v,tamanho,TRUE);

    fclose(arquivo);

    
    remove_arq_secundario(arquivo,nome,pos);
    return TRUE;
}

/*11.Funções auxiliares
*/
int compara(char n[10],char p[10]){

    char aux1[10];
    char aux2[10];
    int espaco=0;

    //Deixar os nomes iguais, tirando espaço e letras maiusculas
    int i=0;
    while(n[i] != '\0'){

        if(n[i] == '_'){
            aux1[i-espaco] = tolower(n[i+1]);
            espaco++;
            i++;
        }
        
        else
            aux1[i-espaco] = tolower(n[i]);
        i++;
    }
    aux1[i-espaco] = '\0';

    i=0;
    espaco =0;
    while(p[i] != '\0'){
        if(p[i] == '_'){
            aux2[i-espaco] = tolower(p[i+1]);
            i++;
            espaco++;
        }
        
        else
            aux2[i-espaco] = tolower(p[i]);
        i++;
    }
    aux2[i-espaco] = '\0';

    return strcmp(aux1,aux2);
}

void calcula_tamanho(Reg registro,int v[],int *tam){

    v[0] = sizeof(long int);
    v[1] = strlen(registro.lName)+1;
    v[2] = strlen(registro.nome)+1;
    v[3] = sizeof(int);
    v[4] = strlen(registro.adress.rua)+1;
    v[5] = strlen(registro.adress.complemento)+1;
    v[6] = strlen(registro.city)+1;
    v[7] = strlen(registro.state)+1;
    v[8] = strlen(registro.cep)+1;
    v[9] = strlen(registro.phone)+1;

    int soma=0;
    for(int i=0;i<10;i++)
        soma += v[i];

    *tam = 10 * sizeof(int) + 20 * sizeof(char) + soma;

}

/*12.FUnção de teste do arquivo de chaves secundárias
*/
void print_arq_secundario(){

    FILE *arquivo = fopen(NOME_ARQUIVO_SECUNDARIO,"rb");

    cSec registro;
    char existe;
    char delimitador;
    int contador;

    if(arquivo == NULL){
        printf("OPS, algo deu errado, encerrando a execucao...\n");
        exit(1);
    }
    
    //Arquivo necessariaente precisa estar em modo de leitura
    while( (fread(&delimitador,sizeof(char),1,arquivo)==TRUE) &&(fread(&existe,sizeof(char),1,arquivo)==TRUE)&& 
    (fread(&delimitador,sizeof(char),1,arquivo)==TRUE) &&(fread(&registro,sizeof(cSec),1,arquivo) == TRUE)){
        contador=0;
        while(registro.i[contador] != -1){
            printf("%c%c%c %d %s\n",delimitador,existe,delimitador,registro.i[contador],registro.nome);
            contador++;
        }
        printf("%d\n",registro.i[contador]);
    }
    fclose(arquivo);
}

/*
13.As funções abaixo são funções relacionadas a busca, tanto busca de chave secundaria, como busca de chave primaria
*/

int  busca_fName(FILE *arquivo,char fName[10]){
    
    printf("Procurando pelo nome %s\n\n",fName);

    cSec registro;
    char existe;
    char delimitador;
    int achou = FALSE;
    int fim = FALSE;

    arquivo = fopen(NOME_ARQUIVO_SECUNDARIO,"rb");
    if(arquivo == NULL){
        printf("OPS, algo deu errado, encerrando a execucao...\n");
        exit(1);
    }

    //Determinar a quantidade de itens inseridos
    fseek(arquivo,0,SEEK_END);
    int pos = ftell(arquivo);
    fseek(arquivo,0,SEEK_SET);
    int qtdItens = pos / (sizeof(cSec)+3);

    int e = -1;
    int d = qtdItens;
    int m = (e+d)/2;

    int pulo = sizeof(cSec)+3;
    fseek(arquivo,m*pulo,SEEK_SET);

    while(!fim && !achou &&(fread(&delimitador,sizeof(char),1,arquivo)==TRUE) &&(fread(&existe,sizeof(char),1,arquivo)==TRUE)&& 
    (fread(&delimitador,sizeof(char),1,arquivo)==TRUE) &&(fread(&registro,sizeof(cSec),1,arquivo) == TRUE)){

            int c = compara(fName,registro.nome);
            if(c < 0){
                d = m;
            }
            else if(c > 0){
                e = m;
            }
            else{
                if(existe == '1')
                achou = TRUE;
                else
                fim = TRUE;
            }

            if(e >= d-1)
                fim = TRUE;

            m = (e+d)/2;
            fseek(arquivo,m*pulo,SEEK_SET);
    }
    fclose(arquivo);
    if(!achou || fim){
        return FALSE;
    }

    printf("Registro(s) com o nome: %s abaixo:\n",registro.nome);
    int cont=0;
    while(registro.i[cont] != -1){
        mostra_registro(arquivo,registro.i[cont],cont);
        cont++;
    }
    return TRUE;

}

int  busca_key(FILE *arquivo,long int key,int *pos,int *tam,char nome[10],int booleano){

    char inicio_reg,delimitador,existe;
    int v;
    int tamanho;
    Reg registro;
    int contador=0;
    int achou = FALSE;

    arquivo = fopen(NOME_ARQUIVO,"rb");

    *pos = ftell(arquivo);//byteoffset 0

    while(!achou && fread(&inicio_reg,sizeof(inicio_reg),1,arquivo) && inicio_reg == '#'){

        fread(&delimitador,sizeof(delimitador),1,arquivo);
        fread(&existe,sizeof(delimitador),1,arquivo);
        fread(&delimitador,sizeof(delimitador),1,arquivo);
        

        fread(&tamanho,sizeof(int),1,arquivo);
        fread(&delimitador,sizeof(delimitador),1,arquivo);

        if(existe == '0'){
            //Pular para o proximo registro, que estará na pos SEEK_CURR + TAM-1
            fseek(arquivo,tamanho-1,SEEK_CUR);

        }

        else{
            //Escreve o tamanho do campo
            fread(&v,sizeof(int),1,arquivo);
            fread(&delimitador,sizeof(delimitador),1,arquivo);
            fread(&registro.key,v,1,arquivo);

            if(registro.key == key){

                achou = TRUE;
                *tam = tamanho;

                //Ler o campo nome

                //Avançar lname
                fread(&delimitador,sizeof(delimitador),1,arquivo);
                fread(&v,sizeof(int),1,arquivo);

                //Avança para o proximo campo(tam|lName|)
                fseek(arquivo,v+2,SEEK_CUR);
                
                //Ler o campo name
                fread(&v,sizeof(int),1,arquivo);
                fread(&delimitador,sizeof(delimitador),1,arquivo);
                fread(&registro.nome,v,1,arquivo);

                strcpy(nome,registro.nome);  

                if(booleano){
                    fclose(arquivo);
                    mostra_registro(arquivo,*pos,contador);
                }
            }
            if(!achou){
                int pulo = tamanho - (2+sizeof(int)+v);
                fseek(arquivo,pulo,SEEK_CUR);
            }
                contador++;
            
        }
        
        if(!achou)
            *pos = ftell(arquivo);      
    }


    if(!achou){
        fclose(arquivo);
        return FALSE;
    }

    if(achou && !booleano)
        fclose(arquivo);

    return TRUE;

}

void mostra_registro(FILE *arquivo,int byte_offset,int c){

    char inicio_reg,delimitador,existe;
    int v[10];
    int tam;
    Reg registro;

    arquivo = fopen(NOME_ARQUIVO,"rb");
    fseek(arquivo,byte_offset,SEEK_SET);

    if(fread(&inicio_reg,sizeof(inicio_reg),1,arquivo)){

        fread(&delimitador,sizeof(delimitador),1,arquivo);
        fread(&existe,sizeof(delimitador),1,arquivo);
        fread(&delimitador,sizeof(delimitador),1,arquivo);
        

        fread(&tam,sizeof(int),1,arquivo);
        fread(&delimitador,sizeof(delimitador),1,arquivo);

            for(int i=0;i<10;i++){
                //Escreve o tamanho do campo
                fread(&v[i],sizeof(int),1,arquivo);
                fread(&delimitador,sizeof(delimitador),1,arquivo);
                
                switch (i){

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
            ml(c,0);
            printf("%c%c%c%c%d%c\n",inicio_reg,delimitador,existe,delimitador,tam,delimitador);
            print_reg(registro);
            ml(c,0);    
    }
    fclose(arquivo);
}