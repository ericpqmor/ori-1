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



/*
1.A função abaixo tem como objetivo, a criação do arquivo principal de dados, pode ser usada tanto para resetar, quanto para criar um novo arquivo, com nome
fixo
*/
int criaArquivo(char *n_arq){

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
    printf("0)Criar arquivo\n1)Inserir\n2)Mostrar todos os registros\n3)Mostrar registro n\n4)Mostrar registro com a KEY x\n5)Mostrar registro com FNAME s\n6)Remover registro\n7)Sair\n");
    ml(0,0);
    printf("Digite o digito:");
    scanf("%d",v);

    if((*v)<0 || (*v)>7){
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

/*
3.As três funções abaixo são primitivas, uma lê o arquivo de dados principal, a as outras duas, escrevem da forma desejado nos arquivos
*/

//Função: Ler os registros que existem logicamente de maneira sequencial, e exibi-los na tela
void le_arquivo(FILE *arquivo){

    //Declaração das variáveis locais
    Reg registro;
    int contador=0;
    char existe;
    char delimitador;

    //Abertura do arquivo principal em modo r
    arquivo = fopen(N_ARQUIVO,"rb");

    //Verifica se o arquivo foi aberto corretamente
    if(arquivo == NULL){
        printf("OPS, algo deu errado, encerrando a execucao...\n");
        exit(1);
    }
    
    //Arquivo necessariaente precisa estar em modo de leitura
    while( (fread(&delimitador,sizeof(char),1,arquivo)==TRUE) &&(fread(&existe,sizeof(char),1,arquivo)==TRUE)&& (fread(&delimitador,sizeof(char),1,arquivo)==TRUE) &&(fread(&registro,sizeof(Reg),1,arquivo) == TRUE)){
        if(delimitador == '|' && existe == '1'){
            ml(contador,TRUE);
            print_reg(registro);
            ml(contador,FALSE);
            sleep(1);
            printf("\n");
            contador++;
        }
    }
    fclose(arquivo);
}

//Função: Escreve no arquivo principal um registro na forma |e|reg, o arquivo deve necessariamente estar aberto em algum modo de escrita
void escreve_arquivo(FILE *arquivo,Reg registro,char existe){

    //Declaração da variavel local
    char delimitador = '|';

    //Escrever no arquivo principal de dados
    fwrite(&delimitador,sizeof(delimitador),1,arquivo);
    fwrite(&existe,sizeof(delimitador),1,arquivo);
    fwrite(&delimitador,sizeof(delimitador),1,arquivo);
	fwrite(&registro,sizeof(Reg),1,arquivo);

}
//Função: Escreve no arquivo secundario um registro na forma |e|reg, o arquivo deve necessariamente estar aberto em algum modo de escrita
void escreve_arquivo_secundario(FILE *arquivo,cSec registro, char existe){

    //Declaração da variavel local
    char delimitador = '|';

    //Escreve no arquivo secundário de dados
    fwrite(&delimitador,sizeof(delimitador),1,arquivo);
    fwrite(&existe,sizeof(delimitador),1,arquivo);
    fwrite(&delimitador,sizeof(delimitador),1,arquivo);
    fwrite(&registro,sizeof(cSec),1,arquivo);

}

/*
4.Busca dos campos dos registro, as funções a seguir buscam os campos do registro Reg,nos arquivos, tanto no arquivo principal de dados, 
como nos arquivos secundários
*/

//Função: Recupera um registro que é o n-esimo registro no arquivo, são contabilizados apenas registros que existem logicamente
int recupera_registro(FILE *arquivo,int valor){

    //Declarações da variaveis local
    Reg registro;
    int contador=0;
    int achou = FALSE;
    char existe;
    char delimitador;

    //Abre o arquivo no modo leitura
    arquivo = fopen(N_ARQUIVO,"rb");

    //Verifica se foi aberto corretamente
    if(arquivo == NULL){
        printf("OPS, algo deu errado, encerrando a execucao...\n");
        exit(1);
    }

    //Arquivo necessariaente precisa estar em modo de leitura
     while(!achou &&(fread(&delimitador,sizeof(char),1,arquivo)==TRUE) &&(fread(&existe,sizeof(char),1,arquivo)==TRUE)&& 
     (fread(&delimitador,sizeof(char),1,arquivo)==TRUE) &&(fread(&registro,sizeof(Reg),1,arquivo) == TRUE)){
        
        //Acho o arquivo de numero n
        if(delimitador == '|' && existe == '1' && contador == valor){
            printf("\nRegistro encontrado:\n");
            ml(contador,TRUE);
            print_reg(registro);
            ml(contador,FALSE);
            sleep(1);
            printf("\n");
            achou = TRUE;
        }

        //Incremente se o registro que foi lido existe logicamente
        if(existe=='1')
            contador++;
    }

    fclose(arquivo);

    if(!achou){
        return FALSE;
    }

    return TRUE;
}

//Função: Busca a chave primária de maneira sequencial no arquivo de dados primários, e exibe na tela o registro caso encontre
int busca_key(FILE *arquivo,long int key,int *pos,int booleano){
    
    //Declarações da variaveis local
    Reg registro;
    int contador=0;
    int achou = FALSE;
    char existe;
    char delimitador;

    //Abre o arquivo no modo de leitura
    arquivo = fopen(N_ARQUIVO,"rb");

    //Verifica se o arquivo foi aberto corretamente
    if(arquivo == NULL){
        printf("OPS, algo deu errado, encerrando a execucao...\n");
        exit(1);
    }

    //Arquivo necessariaente precisa estar em modo de leitura
   while( !achou &&(fread(&delimitador,sizeof(char),1,arquivo)==TRUE) &&(fread(&existe,sizeof(char),1,arquivo)==TRUE)&& (fread(&delimitador,sizeof(char),1,arquivo)==TRUE) &&(fread(&registro,sizeof(Reg),1,arquivo) == TRUE)){
        
        //Acho a chave desejada, e esta existe logicamente
        if(delimitador == '|' && existe == '1' && registro.key == key){
            
            //Verifica se é necessário printar
            if(booleano){
            printf("\nChave encontrada:\n");
            ml(contador,TRUE);
            print_reg(registro);
            ml(contador,FALSE);
            sleep(1);
            printf("\n");
            }
           
            achou = TRUE;
        }
        if(existe == '1')
            contador++;
    }

    //Salva a posição física do registro no arquivo
    int aux = ftell(arquivo)-(sizeof(Reg)+3);
    *pos = (aux / (sizeof(Reg)+3));

    //Fecha o arquivo
    fclose(arquivo);

    //Retornos
    if(!achou){
        return FALSE;
    }

    return TRUE;
}

//Função: Busca a chave secundaria, no arquivo secundário, e exibe na tela ,caso encontre, todos os registros com o nome n
int  busca_fName(FILE *arquivo,char fName[10]){
    
    printf("Procurando pelo nome %s\n\n",fName);

    //Declarações da variaveis local
    cSec registro;
    char existe;
    char delimitador;
    int achou = FALSE;
    int fim = FALSE;

    //Abre o arquivo em modo de leitura
    arquivo = fopen(N_ARQUIVO_SECUNDARIO,"rb");

    //Verifica se o arquivo foi aberto corretamente
    if(arquivo == NULL){
        printf("OPS, algo deu errado, encerrando a execucao...\n");
        exit(1);
    }

    //Determinar a quantidade de itens inseridos
    fseek(arquivo,0,SEEK_END);
    int pos = ftell(arquivo);
    fseek(arquivo,0,SEEK_SET);
    int qtdItens = pos / (sizeof(cSec)+3);

    //Variaveis de controle da busca binária
    int e = -1;
    int d = qtdItens;
    int m = (e+d)/2;

    //Tamanho de um registro, contado com os delimitadores
    int pulo = sizeof(cSec)+3;

    //Posição corrente ajustada
    fseek(arquivo,m*pulo,SEEK_SET);

    //Inicio da busca
    while(!fim && !achou &&(fread(&delimitador,sizeof(char),1,arquivo)==TRUE) &&(fread(&existe,sizeof(char),1,arquivo)==TRUE)&& 
    (fread(&delimitador,sizeof(char),1,arquivo)==TRUE) &&(fread(&registro,sizeof(cSec),1,arquivo) == TRUE)){

            int c = compara(fName,registro.nome);

            //Vai para a esquerda
            if(c < 0){
                d = m;
            }

            //Vai para a direita
            else if(c > 0){
                e = m;
            }

            //Achou
            else{
                //Existe logicamente
                if(existe == '1')
                achou = TRUE;

                //Nao existe logicamente
                else
                fim = TRUE;
            }

            //Condição de parada
            if(e >= d-1)
                fim = TRUE;

            //Calculo do novo meio
            m = (e+d)/2;
            fseek(arquivo,m*pulo,SEEK_SET);
    }

    //Fecha  o arquivo
    fclose(arquivo);

    //Retornos
    if(!achou || fim){
        return FALSE;
    }

    //Prints do(s) registros
    printf("Registro(s) com o nome: %s abaixo: ",registro.nome);
    int cont=0;
    while(registro.i[cont] != -1){
        recupera_registro(arquivo,registro.i[cont]);
        cont++;
    }
    return TRUE;

}


/*
5.As funções abaixo estão relacionados a verificarem a presença de remoção lógica nos 3 arquivos existentes
*/

//Função:Verifica a existencia de remoções lógicas no arquivo principal
int verifica(FILE *arquivo){

    //Declarações da variaveis local
    Reg registro;
    int achou = FALSE;
    char existe;
    char delimitador;

    //Arquivo necessariaente precisa estar em modo de leitura, mas é aberto em outra função
    while( !achou && (fread(&delimitador,sizeof(char),1,arquivo)==TRUE) &&(fread(&existe,sizeof(char),1,arquivo)==TRUE)&& (fread(&delimitador,sizeof(char),1,arquivo)==TRUE) &&(fread(&registro,sizeof(Reg),1,arquivo) == TRUE)){
        
        //Achou um registro que foi removido logicamente
        if(existe == '0')
            achou = TRUE;
        
    }
    if(!achou){
        return FALSE;
    }

    return TRUE;
}

//Função:Verifica a existencia de remoções lógicas no arquivo secundário
int verifica_indice_secundario(FILE *arquivo,int *pos){
    
    //Declarações da variaveis local
    cSec registro;
    char existe;
    char delimitador;
    int achou = FALSE;
    

    //Abre o arquivo no modo leitura
    arquivo = fopen(N_ARQUIVO_SECUNDARIO,"rb");


    //Inicio da busca de um registro removido
    while(!achou && fread(&delimitador,sizeof(delimitador),1,arquivo) && fread(&existe,sizeof(delimitador),1,arquivo) &&
    fread(&delimitador,sizeof(delimitador),1,arquivo) && fread(&registro,sizeof(cSec),1,arquivo)){

        //Achou um registro que foi removido logicamente
        if(existe == '0')
            achou = TRUE;
    }

    //Valores de retorno
    if(!achou)
        return FALSE;

    //Salva a posição do registro na variavel que foi passado por referencia
    *pos = ftell(arquivo) - (sizeof(cSec)+3);

    //Fecha o arquivo
    fclose(arquivo);

    return TRUE;

}
/*
6.Verifica se o vetor para a chave secundaria nome tem espaço suficiente
*/
int tamanho_disponivel(FILE *arquivo,char fName[10]){

   //Declarações da variaveis local
    int achou = FALSE;
    char delimitador;
    char existe;
    cSec registro;
   
   //Abre o arquivo no modo leitura
    arquivo = fopen(N_ARQUIVO_SECUNDARIO,"rb");
   

    //INicio da busca pela chave NAME, e verificação se existe tamanho disponivel
    while(!achou && (fread(&delimitador,sizeof(char),1,arquivo)==TRUE) &&(fread(&existe,sizeof(char),1,arquivo)==TRUE)&& 
    (fread(&delimitador,sizeof(char),1,arquivo)==TRUE) &&(fread(&registro,sizeof(cSec),1,arquivo) == TRUE)){

        int c = compara(fName,registro.nome);
        if(c < 0){
            fclose(arquivo);
            return TRUE;
        }
        //Achou
        else if(c == 0)
            achou = TRUE;
    }

    fclose(arquivo);

    //Verifica se na posição 19, que é a ultima posição está o valor -1, que indica que a lista está cheia, com 19 valores
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

//Função: A inserção principal no arquivo secundário
void insere_arq_secundario(FILE *arquivo,char nome[10],int indice,int tem_remocao){
    
    //Declarações da variaveis local
    cSec registro;
    int contador=0;
    int achou = FALSE;
    char delimitador;
    char existe;
    long int pos;
    int repetido = FALSE;
    
    //Abre o arquivo no modo rb+
    arquivo = fopen(N_ARQUIVO_SECUNDARIO,"rb+");

    //Verifica se  o arquivo foi aberto corretamente
    if(arquivo == NULL){
        printf("OPS, algo deu errado, encerrando a execucao...\n");
        exit(1);
    }
    
    //Inicio da busca da posição que deve ser inserido
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

    //Declarações da variaveis local
    cSec registro_auxiliar;
    char insercao = '1';
    delimitador = '|';


    strcpy(registro_auxiliar.nome,nome);

    //Caso seja a primeira ocorrencia da chave NAME no arquivo
    if(!repetido){
        registro_auxiliar.i[0] = indice;
        registro_auxiliar.i[1] = -1;
    }

    //Caso não seja
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
        escreve_arquivo_secundario(arquivo,registro_auxiliar,insercao);
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
            escreve_arquivo_secundario(arquivo,registro_auxiliar,insercao);
        }
        else{
            escreve_arquivo_secundario(arquivo,registro_auxiliar,insercao);
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

            escreve_arquivo_secundario(arquivo,registro,existe);

            existe = insercao;
            registro = registro_auxiliar;
        }
    }

    fclose(arquivo);    
}

/*Função: Este procedimento, realiza o ajuste no arquivo secundário, colocando o registro que foi removido logicamente, na ultima posição do arquivo, e dessa
forma, este não será escrito na inserção, que é a função chamada após esta.
*/
void ajusta_insercao_secundario(FILE *arquivo,int pos){

     /*Existe um registro que foi removido logicamente, logo esse espaço deve ser reaproveitado e inserido um novo registro em seu lugar,
    para reorganizar, esse registro deve ir para a ultima posição do vetor, e isso será feito subindo todos os registro abaixo em uma posição, e nesse caso,
    o ultimo registro estará repetido, e isso não tem problema, pois no final ele será substituido por ele mesmo
*/
    arquivo = fopen(N_ARQUIVO_SECUNDARIO,"rb+");

    if(arquivo == NULL){
        printf("OPS, algo deu errado, encerrando a execucao...\n");
        exit(1);
    }

    int acabou = FALSE;
    int pos_corr = pos + sizeof(cSec)+3;
    fseek(arquivo,pos_corr,SEEK_SET);

    //Declarações da variaveis local
    cSec registro;
    char delimitador,existe;

    while(!acabou){

        if((fread(&delimitador,sizeof(char),1,arquivo)==FALSE) || (fread(&existe,sizeof(char),1,arquivo)==FALSE)|| 
        (fread(&delimitador,sizeof(char),1,arquivo)==FALSE) ||(fread(&registro,sizeof(cSec),1,arquivo) == FALSE)){
            acabou = TRUE;
        }
        
        if(!acabou){
            fseek(arquivo,-2*(sizeof(cSec)+3),SEEK_CUR);

            escreve_arquivo_secundario(arquivo,registro,existe);

            fseek(arquivo,sizeof(cSec)+3,SEEK_CUR);
        }
    }

    fclose(arquivo);

}
/*
8.As funções abaixo são relacionadas a remoção de arquivos de chave secundaria
*/

//Função: Remove o registro do arquivo secundário
void remove_arq_secundario(FILE *arquivo,char nome[10],int indice){

    //Declarações da variaveis local
    int pos;
    int achou = FALSE;
    char delimitador;
    char existe;
    cSec registro;
    int contador=0;
    int sozinho=TRUE;
    int sair = FALSE;

    //Abre o arquivo no modo rb+
   arquivo = fopen(N_ARQUIVO_SECUNDARIO,"rb+");
   
   //Verifica se o arquivo foi aberto corretamente
   if(arquivo == NULL){
        printf("OPS, algo deu errado, encerrando a execucao...\n");
        exit(1);
    }

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

    escreve_arquivo_secundario(arquivo,registro,existe);

    fclose(arquivo);

    return;  
}
/*
9.A função abaixo é a inserção geral
*/
int insere(FILE *arquivo,Reg registro){

    //Cria os arquivos caso eles não existam
    arquivo = fopen(N_ARQUIVO_SECUNDARIO,"ab");
     if(arquivo == NULL){
        printf("OPS, algo deu errado, encerrando a execucao...\n");
        exit(1);
    }
    fclose(arquivo);

    int pos=0;

    if(busca_key(arquivo,registro.key,&pos,FALSE))
        return FALSE;
    //VERIFICAR SE O VETOR PARA O NOME N TEM ESPAÇO DISPONIVEL
    if(!tamanho_disponivel(arquivo,registro.nome))
        return FALSE;

    arquivo = fopen(N_ARQUIVO,"rb");
    //Houve remocao lógica
    if(verifica(arquivo)){

        pos = ftell(arquivo); //guarda posicao

        fclose(arquivo);
        arquivo = fopen(N_ARQUIVO,"rb+"); //abre o arquivo no modo rb+

        fseek(arquivo,pos,SEEK_SET);

        //Trocar o existe de 0 para 1
        fseek(arquivo,-sizeof(Reg)-3,SEEK_CUR);//Vai para algum lugar
        escreve_arquivo(arquivo,registro,'1');
    }
    //Nao houve remocao lógica
    else{
        fclose(arquivo);

        arquivo = fopen(N_ARQUIVO,"ab"); //abre o arquivo no modo append
        escreve_arquivo(arquivo,registro,'1');
    }


    pos = ftell(arquivo) - sizeof(Reg)-3;
    fseek(arquivo,0,SEEK_SET);//reseta a posição corrente]
    fclose(arquivo);

    //Calculo do indice, nesse caso o indice sera calculado com base na posicao do arquivo
    int indice = pos / (sizeof(Reg)+3);
    int tem_remocao = FALSE;

    //Inserção nos arquivos de chave primaria e secundária
    if(verifica_indice_secundario(arquivo,&pos)){
        ajusta_insercao_secundario(arquivo,pos);
        tem_remocao = TRUE;
    }

    insere_arq_secundario(arquivo,registro.nome,indice,tem_remocao);

    return TRUE;
}
/*
10.A função abaixo é a remoção em geral
*/
int remove_logico(FILE *arquivo,long int key){

    int pos;

    //Busca a chave no arquivo de indice secundario
    if(!busca_key(arquivo,key,&pos,FALSE))
        return FALSE;

    Reg registro;

    arquivo = fopen(N_ARQUIVO,"rb");
    pos *= (sizeof(Reg)+3);

    fseek(arquivo,3+pos,SEEK_SET);
    if(fread(&registro,sizeof(Reg),1,arquivo)==FALSE){
        return FALSE;
    }
   
   fclose(arquivo);

    arquivo = fopen(N_ARQUIVO,"rb+"); //abre o arquivo no modo rb+

    fseek(arquivo,pos,SEEK_SET);
    escreve_arquivo(arquivo,registro,'0');

    fclose(arquivo);

    pos = pos/(sizeof(Reg)+3);
    
    remove_arq_secundario(arquivo,registro.nome,pos);

    return TRUE;
}


/*
11.As funções abaixo são complementares em relação as ultilizadas acima, algumas são ultilizadas na main, outras são chamadas por funções
*/

//Função:Compara duas strings para determinar qual vem antes na ordem alfabetica
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

//Função:Exibe a lista do arquivo secundário
void print_arq_secundario(){

    FILE *arquivo = fopen(N_ARQUIVO_SECUNDARIO,"rb");

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

