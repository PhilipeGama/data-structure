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
	struct pilha *last;
}P;

P *operandStack1=NULL,*operandStack2 = NULL,*resultaStack;


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

push(int valor,P *aux){
	P *auxP;
	auxP = alocPilha();
	auxP->valor = valor;
	 
	if(inicio ==  NULL){
		inicio = auxP;	
		auxP->last = inicio;
	}else{
		auxP->anterior = last;
		last->proximo = auxP;
		auxP->last = auxP;
	}
}

void pop(P *auxP){
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
	if(isEmpty())
		return NULL;
	return last;
}

int main(){
 char a[20],b[20];
 		
 scanf("%s",&a);
 scanf("%s",&b);
 
 int x,i = 0;
  
 while(a[i]){
 	x = (int) a[i];
 	x = x - 48;
 	
 	printf("%d\n",x);
 	push(x,operandStack1);
 	i++;
 }
	
  while(b[i]){
 	x = (int) b[i];
 	x = x - 48;
 	
 	printf("%d\n",x);
 	push(x,operandStack2);
 	i++;
 }
 
return 1; 
}


