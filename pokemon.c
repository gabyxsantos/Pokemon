#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100
#define MAXLINHA 1000
#define AUMENTO 1.20
#define DIMINUI 0.80

typedef struct atributos{
    char nome[MAX];
    float ataque;
    float defesa;
    float vida;
    char tipo[MAX];
}atributos;


typedef struct pokemon{
    char nome[MAX];
}pokemon;

void forca(atributos *atacante, atributos *defensor){
     
    if (strcmp(atacante->tipo, "eletrico") == 0){
        if ((strcmp(defensor->tipo, "agua") == 0)) {atacante->ataque *= AUMENTO;}
        else if ((strcmp(defensor->tipo, "pedra") == 0)) {atacante->ataque *= DIMINUI;}
    }

    else if (strcmp(atacante->tipo, "agua") == 0){
        if ((strcmp(defensor->tipo, "fogo") == 0)) {atacante->ataque *= AUMENTO;}
        else if ((strcmp(defensor->tipo, "eletrico") ==0)) {atacante->ataque *= DIMINUI;}
    }

    else if (strcmp(atacante->tipo, "fogo") == 0){
        if ((strcmp(defensor->tipo, "gelo") == 0)) {atacante->ataque *= AUMENTO;}
        else if ((strcmp(defensor->tipo, "agua") == 0)) {atacante->ataque *= DIMINUI;}
    }

    else if (strcmp(atacante->tipo, "gelo") == 0){
        if ((strcmp(defensor->tipo, "pedra") == 0)) {atacante->ataque *= AUMENTO;}
        else if ((strcmp(defensor->tipo, "fogo") ==0)) {atacante->ataque *= DIMINUI;}
    }

    else if (strcmp(atacante->tipo, "pedra") == 0){
        if ((strcmp(defensor->tipo, "eletrico") == 0)) {atacante->ataque *= AUMENTO;}
        else if ((strcmp(defensor->tipo, "gelo") == 0)) {atacante->ataque *= DIMINUI;}
    }
}



void controle_vida (atributos *j1, atributos *j2, atributos *j1aux, atributos *j2aux, int *indice_j1, int *indice_j2, int *turno){
        
    if (j1aux->vida <= 0){ 
        printf("%s venceu %s\n", j2aux->nome, j1aux->nome);
        j1[*indice_j1].vida = 0.0; 
        (*indice_j1)++; 
        *j1aux = j1[*indice_j1];
        j2aux->ataque = j2[*indice_j2].ataque;
        *turno = 0;
    }

    else  if (j2aux->vida <= 0){
        printf("%s venceu %s\n", j1aux->nome, j2aux->nome);
        j2[*indice_j2].vida = 0.0;
        (*indice_j2)++;
        *j2aux = j2[*indice_j2];
        j1aux->ataque = j1[*indice_j1].ataque;
        *turno = 1;
    }

    
}

void imprime_resultados (atributos *j1, atributos *j2, pokemon *sobreviventes, pokemon *derrotados, int quantidade_j1, int quantidade_j2){

    int indice_sobreviventes = 0;
    int indice_derrotados = 0;

    for (int j=0; j<quantidade_j1; j++){
        if(j1[j].vida > 0){
            strcpy(sobreviventes[indice_sobreviventes].nome,  j1[j].nome);
            indice_sobreviventes ++;
        }
        
        else if (j1[j].vida == 0){
            strcpy(derrotados[indice_derrotados].nome, j1[j].nome);
            indice_derrotados ++;
        }
    }

    if (indice_sobreviventes > 0) printf("O jogador 1 venceu!\n");
    else printf("O jogador 2 venceu!\n");

    for (int j=0; j<quantidade_j2; j++){
        if(j2[j].vida > 0){
            strcpy(sobreviventes[indice_sobreviventes].nome,  j2[j].nome);
            indice_sobreviventes ++;
        }
        else if (j2[j].vida == 0){
            strcpy(derrotados[indice_derrotados].nome, j2[j].nome);
            indice_derrotados ++;
        }
    }

    printf("\n");

    printf("Pokemon sobreviventes:\n");
    for(int j=0; j<indice_sobreviventes; j++){
        printf ("%s\n", sobreviventes[j].nome);
    }
    printf("\n");

    printf("Pokemon derrotados:\n");
    for(int j=0; j<indice_derrotados; j++){
        printf ("%s\n", derrotados[j].nome);
    }

    printf("\n");
}

void batalha (atributos j1[], atributos j2[], pokemon derrotados[], pokemon sobreviventes[], int quantidade_j1, int quantidade_j2){
    
    int indice_j1 = 0;
    int indice_j2 = 0;
   
    atributos j1aux = j1[indice_j1];
    atributos j2aux = j2[indice_j2];
    int turno = 0; 

    printf ("\nVamos iniciar a batalha!!\n\n");

    while (indice_j1<quantidade_j1 && indice_j2<quantidade_j2){ 

        forca(&j1aux, &j2aux); 
        forca(&j2aux, &j1aux);
        
        
        while (j1aux.vida > 0 && j2aux.vida > 0 ) { 

            if (turno == 0 ){
                if (j1aux.ataque > j2aux.defesa){
                    j2aux.vida -=  (j1aux.ataque - j2aux.defesa); 
                }
                 else if (j1aux.ataque <= j2aux.defesa){
                    j2aux.vida -= 1;
                }
                turno = 1;
            }

            else if (turno == 1){
                if (j2aux.ataque > j1aux.defesa){
                    j1aux.vida -=  (j2aux.ataque - j1aux.defesa); 
                }
                 else if (j2aux.ataque <= j1aux.defesa){
                    j1aux.vida -= 1;
                }
                turno = 0;
            }
            
        }

        controle_vida(j1, j2, &j1aux, &j2aux, &indice_j1, &indice_j2, &turno);

    }

    printf("\n");

    imprime_resultados(j1, j2, sobreviventes, derrotados, quantidade_j1, quantidade_j2);
    
}



int main(){

    atributos j1[MAX]; 
    atributos j2[MAX];
    pokemon sobreviventes[MAX];
    pokemon derrotados[MAX];
    
    FILE *arq;
	arq = fopen("arquivo.txt","r");
 
	if (arq == NULL) {  
		printf("Arquivo nao encontrado :)\n");
		return 1; 
	}
     
    char buf[MAXLINHA];
	fgets(buf, MAXLINHA, arq);
    
	int num_j1 = atoi(strtok(buf," ")); 
    int num_j2 = atoi(strtok(NULL," ")); 

    if (num_j1<=0 || num_j1>100 || num_j2<=0 || num_j2>100){ 
        printf("Os valores informados estão fora do intervalo previsto :(\n");
        return 1;
    }
    
    //como todo final de linha tem um \n, temos que tirar ele:
    for(int i = 0; buf[i] != '\0'; i++){  
        if(buf[i] == '\n'){
            buf[i] = '\0';
            break;
        }
    }

    char nome[MAX], tipo[MAX];
    float ataque, defesa, vida;

    int j = 1; // a primeira linha ja foi lida, portanto, j começa do 1
    int k = 0;
    int z = 0;
    
    /*no while a seguir, a leitura dos dados do arquivo é feita, por meio do fscanf, adicionando
    nas variaveis nome, ataque, defesa, vida e tipo, e depois copiando as strings e 
    atribuindo os valores float para os vetores dos jogadores*/
    
    while (fscanf(arq, "%s %f %f %f %s", nome, &ataque, &defesa, &vida, tipo) != EOF){
        
        if (ataque<0 || defesa <0 || vida<0 ){
            printf("Valores nagativos para os atributos nao sao aceitos...\n");
            return 1;
        }

		if ( j>=1 && j<=num_j1){ 
            strcpy(j1[z].nome, nome);
            j1[z].ataque = ataque;
            j1[z].defesa = defesa;
            j1[z].vida = vida;
            strcpy(j1[z].tipo, tipo);
            j++;
            z++;
        }
    
        else if(j>num_j1) {
            strcpy(j2[k].nome, nome);
            j2[k].ataque = ataque;
            j2[k].defesa = defesa;
            j2[k].vida = vida;
            strcpy(j2[k].tipo, tipo);
            k++;
            j++;
        } 

    }

    if ((num_j1 + num_j2) != (z + k)){ //conferindo se a quantidade de pokemon bate com as quantidades descritas
        printf ("\nUm problema foi detectado, podendo ser:\n");
        printf("1) A quantidade de pokemon do arquivo nao corresponde com os numeros dados.\n");
        printf("2) O arquivo de entrada apresenta dados insuficientes.\n");
        return 1;
    }

    printf("\n");
    
    // agora, precisamos imprimir os dados:

    printf("Dados presentes no arquivo lido:\n");

    printf("\n");

    printf("%d %d\n", num_j1, num_j2);
    
    for (int j = 0; j<num_j1; j++){
        printf("%s %.2f %.2f %.2f %s\n", j1[j].nome, j1[j].ataque, j1[j].defesa, j1[j].vida, j1[j].tipo);
    }

    for (int j = 0; j<num_j2; j++){
        printf("%s %.2f %.2f %.2f %s\n", j2[j].nome, j2[j].ataque, j2[j].defesa, j2[j].vida, j2[j].tipo);
    }
    
    batalha (j1, j2, derrotados, sobreviventes, num_j1, num_j2);

    return 0;
}