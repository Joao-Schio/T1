#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/* Este código abre o arquivo dna.ent, e cria as saídas dna1.sai, dna2.sai, dna3.sai
    dna1.sai possui todas as sequências de DNA, que possuem mais CG's do que AT's
     dna2.sai possui a fita que tem a maior diferença de AT's para CG's
      dna3.sai possui todas as sequencias palindromicas de DNA */






/* definindo uma lista encadeada
    que será importante, pois não conseguimos saber quantas sequencias de DNA serão armazenadas na saída 1 e 3 */
typedef struct cel {
    char elemento[1500];
    struct cel *prox;
} celula;


// funcao que conta a quantidade de CG'S e AT'S e retorna a diferença entre os dois pares de bases nitrogenadas

int count(char entrada[1500]){  

    // como sempre serão trabalhados em pares, não é preciso de uma variavel para A e outra para o T, com somente uma se armazena o par
    int CG = 0;
    int AT = 0;


    for(int i = 0; i < strlen(entrada); i++){
        if(entrada[i] == 'T' || entrada[i] == 'A'){
            AT++;
        }
        else // se nao for A ou T tem que ser C ou G
            CG++;
    }
    int saida = AT - CG;
    return saida;


}

// funcao que encontra a fita complementar de uma determinada fita de DNA
void complementa (char fita[1500] , char b[1500]){

    char complementar[1500] = {};


    for(int i = 0; i < strlen(fita); i++){
        if(fita[i] == 'A'){
            complementar[i] = 'T';
        }
        else if(fita[i] == 'T'){
            complementar[i] = 'A';
        }
        else if ( fita[i] == 'C'){
            complementar[i] = 'G';
        }
        else if(fita[i] == 'G'){
            complementar[i] = 'C';
        }
    }


    strcpy(b,complementar); // strcpy copia uma string para a outra


}







int palindromico(char entrada[1500]){
    
    char aux[1500] = {};
    complementa(entrada,aux);
    int saida = 1; // funcao de logica para o palindromico


    int i,j;
    i = strlen(aux) - 1;
    for(j = 0; j < strlen(entrada) ; j++){
        if (aux[i] != entrada[j]){
            saida++;
            return saida; // se uma base não é palindromica não é preciso continuar o loop pelo resto da string
        }
        i--;
    }


    return saida; // logica para o palindromico

}







int main(){

    // criando as variaveis de tipo FILE
    FILE *Entrada = fopen("dna.ent","r"); 
    FILE *saida = fopen("dna1.sai","w"); //criando os arquivos de saida, para poder usar fprintf no modo append
    fclose(saida);
    saida = fopen("dna2.sai","w");
    fclose(saida);
    saida = fopen("dna3.sai","w");
    fclose(saida);


    char leitura[1500]; // armazenamento da string de entrada
    int maior_relacao = 0; // armazenar a relacao de AT para CG, usado na saida 2
    char linha_com_maior_relacao[1500]; // armazenar a fita com a maior relação para a saida 2

    celula *Elementos_com_mais_CG,*p; // criando as listas
    celula *Elementos_palindromicos, *q;

    p = Elementos_com_mais_CG = (celula*) malloc(sizeof(celula));
    Elementos_palindromicos = q = (celula*) malloc(sizeof(celula));
    p -> prox = NULL;
    q -> prox = NULL;




    while(fscanf(Entrada,"%s",leitura) != EOF){
        if(count(leitura) < 0){ // como a funcao count retorna a diferenca de AT para CG, se o resultado for menor que 0 então a fita possui mais CG's do que AT's
            p -> prox = (celula*) malloc(sizeof(celula)); // criando mais uma posicao na lista
            p = p -> prox;
            strcpy(p->elemento,leitura); // armazenando a string na lista
            p -> prox = NULL; // definindo o proximo elemento como nulo, simbolizando que a lista não possui mais elementos
        }
        if(count(leitura) > 0){ // mesma logica, se o resulado for maior que 0 a fita possui mais AT's do que CG's
            if(count(leitura) > maior_relacao){ // checar se a relação da fita autal é maior que a maior relação atual
                maior_relacao = count(leitura); // se for fazer as mudancas nas variaveis
                strcpy(linha_com_maior_relacao,leitura);
            }
        }

        if(palindromico(leitura) == 1){ // se a saida for 1 significa que a fita é palindromica
            q -> prox = (celula*) malloc(sizeof(celula)); 
            q = q -> prox;
            strcpy(q-> elemento, leitura);
            q -> prox = NULL;
        }

    }
    fclose(Entrada); // todo arquivo aberto tem que ser fechado


// imprimindo as saidas

    for(p = Elementos_com_mais_CG -> prox; p != NULL; p = p -> prox){
        saida = fopen("dna1.sai","a");
        fprintf(saida,"%s\n", p -> elemento);
        fclose(saida);
    }



    saida = fopen("dna2.sai","a");
    fprintf(saida,"%s\n",linha_com_maior_relacao);
    fclose(saida);





    for(q = Elementos_palindromicos -> prox; q != NULL; q = q -> prox){
        saida = fopen("dna3.sai","a");
        fprintf(saida,"%s\n",q -> elemento);
        fclose(saida);
    }


    return 0;





}


