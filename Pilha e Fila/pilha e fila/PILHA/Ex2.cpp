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

typedef struct pilha_Stack{
	P *stack;
	P *topo;
	
}stackP; 


P *operandStack1=NULL,*operandStack2 = NULL,*resultaStack = NULL;
P *topoStack1=NULL,*topoStack2= NULL,*topoStack3=NULL;

P* alocPilha(){

	P *auxP;
	auxP = (P*) malloc(sizeof(P));
	auxP->proximo = NULL;
	auxP->anterior = NULL;	
	return auxP;
}

bool isEmpty(P *auxP){
	if(auxP == NULL){
		return true;
	}else{
		return false;
	}
}

void push(int valor,P **recebiStack,P **topo){
	P *auxP = NULL;
	auxP = alocPilha();
	auxP->valor = valor;
	//bool is = isEmpty(recebiStack);
	if(*recebiStack == NULL){
		cout << "entrou \n";
		
		*recebiStack = auxP;
		
		//cout << "recebi valor " << recebiStack->valor << "\n";
		//cout << "operand " <<*recebiStack;
		
		*topo = *recebiStack;	
	}else{
		(*topo)->proximo = auxP;
		auxP->anterior = *topo;
		*topo = auxP;
		
	}
	
}

void pop(P *auxP,P *topo){
	if(isEmpty(auxP))
		return;
	if(auxP->proximo = NULL){
		free(auxP);
		auxP = NULL;
	}
}

void clear(P *auxP,P *topo){
	while(isEmpty(auxP) != true){
		pop(auxP,topo);
	}
}

P* topEl(P* auxP,P *topo){
	
	if(isEmpty(auxP)){
		cout << "topEl NULL\n";  		
		return NULL;
	}else{
	
	return topo;
	}
}

int main(){
 char a[20],b[20];
 
 push(1,&operandStack1,&topoStack1);
 //push(2,operandStack1,topoStack1);
 
 
 P *percorre;
 percorre = topEl(operandStack1,topoStack1);
  
 //w//hile(percorre->anterior != NULL){
 if(percorre == NULL){
 	cout << "percorre NULL\n";
 }else{
 cout << "...";
 cout << percorre->valor << "\n";
}


 //	percorre = percorre->anterior;
 
  /*
 		
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
 */
 
 
 

return 1; 
}


