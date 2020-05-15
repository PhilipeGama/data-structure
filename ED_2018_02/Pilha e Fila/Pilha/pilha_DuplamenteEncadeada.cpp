#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <iostream>
#include <windows.h>
#include<unistd.h> 


using namespace std;

void gotoxy(int x, int y){
     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){x-1,y-1});
}  

typedef struct pilha{
	//int nota1;
	//int nota2;
	//char nome[20];
	//int tamanho;
	int valor;
	struct pilha *proximo;
	struct pilha *anterior;
} P;

P *inicio=NULL,*last=NULL;

P* alocPilha(){

	P *auxP = (P*) malloc (sizeof(P));
	auxP->proximo = NULL;
	auxP->anterior = NULL;
}

bool isEmpty(){
	if(inicio == NULL)
		return true;
	else
		return false;	
}

push(int valor){
	P *auxP;
	auxP = alocPilha();
	auxP->valor = valor;
	 
	if(inicio ==  NULL){
		inicio = auxP;	
		last = inicio;
	}else{
		auxP->anterior = last;
		last->proximo = auxP;
		last = auxP;
	}
}

void pop(){
	if(isEmpty())
		return;
	if(last->anterior != NULL){
		P *auxP = last->anterior;
		auxP->proximo = NULL;
		free(last);
		last = auxP;
	}else{
		free(last);
		inicio = NULL;
		last = NULL;
	}
		
}
void clear(){
	while(isEmpty() != true){
		pop();
	}
}

P* topEl(){
	if(isEmpty()){
		return NULL;
	
	return last;
		
}
}



int main(){

push(1);
push(2);
pop();
pop();
push(3);
 
P* topo = topEl();
if(topo == NULL){
	printf("1 - Vazia\n");
}else{

printf("1 - %d\n",topo->valor);
}
push(1);
push(2);
push(4);
push(5);
push(4);

topo = topEl();
if(topo == NULL){
	printf("2 - Vazia\n");
}else{

printf("2 - %d\n",topo->valor);
}

clear();

if(topo == NULL){
	printf("3 - Vazia\n");
}else{
printf("3 - %d\n",topo->valor);
}

return 1;
}



