#include<stdio.h>
#include <string.h>
#include<string.h>

int main(){
char caminho[40];
char nome[40];

for(int i=0;i<65;i++){
	printf("%c",i);
}

strcpy(caminho,"listaB/");

strcpy(nome,"lista1.txt");
strcat(caminho,nome);

printf("%s",caminho);





return 0;
} 

