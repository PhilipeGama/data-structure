#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#define max 1000

char texto[max];
void lerT(char *titulo);
void escreverT(char *titulo);
void alterarT(char *titulo);
int menu();

int main(){
	//setlocale(LC_ALL, "Portuguese");
	int op;
	char titulo[20];
	
do{
	op = menu();
	getchar();
	
	system("cls");
	if(op==1){
		printf("CRIANDO UM ARQUIVO!!!\n\n");
		printf("Digite o titulo do arquivo: ");
		scanf("%s",&titulo);
		getchar();
		system("cls");
		printf("Digite o texto: \n\n\t");
		gets(texto);
		escreverT(titulo);
		printf("\nArquivo Salvo...");
	}	
	if(op==2){
		printf("EDITANDO ARQUIVO!!!\n\n");
		printf("Digite o titulo do arquivo: ");
		scanf("%s",titulo);
		lerT(titulo);
		getchar();
		system("cls");
		printf("Texto presente no arquivo!!!\n\n\n\t%s",texto);
	
		gets(texto);
		escreverT(titulo);
		printf("\nTEXTO EDITADO");
	}
	if(op==3){
		printf("Digite o titulo do arquivo: ");
		scanf("%s",titulo);
		lerT(titulo);
		getchar();
		printf("Texto presente no arquivo!!!\n\n\n\t%s",texto);
 		gets(texto);
		alterarT(titulo);
	}
	if(op==4){
		printf("Digite o titulo do arquivo: ");
		scanf("%s",titulo);
		system("cls");
		lerT(titulo);
		printf("Texto presente no arquivo!!!\n\n\n\t%s\n\n\n",texto);
		system("pause");
		
	}
	if(op==5){
		printf("FINALIZANDO SISTEMA...\n\n\n");
		system("pause");
		exit(1);
	}
	if(op>5){
		printf("OPCAO INVALIDADE\n\n");
		system("pause");
	}
printf("\n\n");	
system("pause");
system("cls");
}while(op!=5);	
	return 1;
}

void lerT(char *titulo){
	
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


void escreverT(char *titulo){
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

void alterarT(char *titulo){
	FILE *file;
	file = fopen(titulo,"a+");
		if(file==NULL){
			printf("Erro na escrita do arquivo\n");
			system("pause");
			exit(1);
		}
		fprintf(file," %s",texto);
	fclose(file);
}

int menu(){
	int op;
	//printf("\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",3017,3021,3021,3021,3021,3021,3021,3021,3021,3021,3021,3021,3021,3021,3021,3021,3021,3021,3021,3021,3021,3003);
	printf("\t\t\t\t\n   EDITOR DE TEXTO  \n",3002,3002);
	//printf("\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",3016,3021,3021,3021,3021,3021,3021,3021,3021,3021,3021,3021,3021,3021,3021,3021,3021,3021,3021,3021,3021,3004);	
	printf("\n\n\t\t  1  %c   CRIA UM ARQUIVO \n\n\t\t  2  %c   EDITAR UM ARQUIRVO\n\n\t\t  3  %c   ADICIONAR TEXTO \n\n\t\t  4  %c   LER ARQUIVO\n\n\t\t  5  %c   SAIR\n\n\t\t",16,16,16,16,16);
	printf("\n\t\t\t\t\t\t   Opcao >  ");
	scanf("%d",&op);
	return op;
}


	
