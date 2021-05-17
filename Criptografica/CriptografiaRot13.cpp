#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max 1000

char texto[max],texto1[max];
char titulo[20],titulo1[20];
void rot13();
int menu();
void lerC();
void escreverC(char *titulo1);

int main(){
	
int op ;
do{	
op = menu();

system("cls");
if(op==1){
	getchar();
	printf("\t!!!Criando arquivo criptogrado!!!");
	printf("\n\n\nDigite o nome do arquivo:");
	scanf("%s",&titulo);
	getchar();

	printf("\n\nDigite o texto:\n\n");
	printf("\t\t");
	gets(texto);
	rot13();

	getchar;
	escreverC(titulo);
	printf("\n\nArquivo criptografado!!!\n\n");
	system("pause");
	system("cls");
}	

if(op==2){

	printf("\t!!!Criando arquivo criptogrado!!!");
	printf("\n\n\nDigite o nome do arquivo:");
	scanf("%s",&titulo);
	lerC();
	rot13();
	getchar();
	printf("Digite o novo nome do arquivo:");
	scanf("%s",&titulo1);
	escreverC(titulo1);
	system("pause");
	system("cls");
	
}

if(op==3){

	
	printf("\t!!!Descriptografar arquivo!!!");
	printf("\n\n\nDigite o nome do arquivo:");
	scanf("%s",&titulo);
	lerC();
	rot13();
	
	printf("\n\n\t\t%s\n\n\n",texto);
	
	system("pause");
	system("cls");
	
}

if(op==4){
	printf("\t!!!Lendo arquivo criptografado!!!");
	printf("\n\n\nDigite o nome do arquivo:");
	scanf("%s",&titulo);
	lerC();
	printf("\n\n\t\t%s\n\n\n",texto);
	system("pause");
	system("cls");
}
	
if(op==5){
	exit(1);
}
system("cls");
}while(op!=5);

return 1;
}



int menu(){
int op;
	printf("\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",3017,3021,3021,3021,3021,3021,3021,3021,3021,3021,3021,3021,3021,3021,3021,3021,3021,3021,3021,3021,3021,3003);
	printf("\t\t\t%c     CRIPTOGRAFIA   %c\n",3002,3002);
	printf("\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",3016,3021,3021,3021,3021,3021,3021,3021,3021,3021,3021,3021,3021,3021,3021,3021,3021,3021,3021,3021,3021,3004);
	printf("\n\n\n\t\t   1.Criar arquivo criptografado"); 
	printf("\n\n\n\t\t   2.Criptografar arquivo");
	printf("\n\n\n\t\t   3.Descriptografar arquivo");
	printf("\n\n\n\t\t   4.Ler arquivo");
	printf("\n\n\n\t\t   5.Sair:\n\n");
	printf("\t\t\t\t\t  Opcao >  ");
	scanf("%d",&op);
return op;	
}

void rot13(){
 	int k,i;
 	char codec_texto[max];
	   
      for (i=0; i < max; i++ ){
          k = int(texto[i]);
          // 65-77 para 78-90 e 97-109 para 110-122
          if ( (k >= 65 && k <= 77) || (k >= 97 && k <= 109) ) {
		   		codec_texto[i] = char(k+13);       		
          }
          // 78-90 para 65-77 e 110-122 para 97-109
          else if ( (k >= 78 && k <= 90) || (k >= 110 && k <= 122) ){
              codec_texto[i] = char(k-13);
          }
          else{
              codec_texto[i] = char(k);
          }
      }
      for(i=0; i<max; i++){
      	texto[i] = codec_texto[i];	
      }
}

void lerC(){
FILE *file;
	file = fopen(titulo,"r");
	if(file==NULL){
		printf("Erro na leitura do arquivo\n");	
		system("pause");
		exit(1);
	}
	while(!feof(file)){
		fgets(texto,sizeof(texto),file);
	}
	
fclose(file);
}


void escreverC(char *titulo){
	FILE *file;
	file = fopen(titulo,"w");
		if(file==NULL){
			printf("Erro na escrita do arquivo\n");
			system("pause");
			exit(1);
		}
		fprintf(file,"%s",texto);
	fclose(file);
}
	
