#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <windows.h>
#include<unistd.h> 


using namespace std;

void gotoxy(int x, int y){
     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){x-1,y-1});
}  

typedef struct pilha{
	int nota1;
	int nota2;
	char nome[20];
	int tamanho;
	struct pilha *proximo;
	struct pilha *anterior;
} PILHA;

PILHA *TOPO = NULL,*INICIO = NULL;

int isEmpty(){
	if(INICIO==NULL){
		return true;
	}else{
		return false;
	}
}

PILHA* aloca (){
	PILHA* novo = (PILHA*)malloc(sizeof(PILHA));
	if(!novo){
		return NULL;
	}else{
		novo->proximo = NULL;
		return novo;
	}
}

void push(char *nome,int nota1,int nota2){
	PILHA *novo;
	novo = aloca();
	novo->proximo = NULL;
	novo->nota1 = nota1;
	novo->nota2 = nota2;
	strcpy(novo->nome, nome);
	
	if(isEmpty()){
		
		INICIO = novo;
		TOPO = INICIO;
		novo->anterior = NULL;
		
	}else{
		novo->anterior = TOPO;
		TOPO->proximo = novo;
		TOPO = novo;
	}
}

void pop(){
	if(isEmpty()){
		return;
	}
	
	if(INICIO == TOPO){
		PILHA *aux = INICIO;
		free(aux);
		INICIO = NULL;
	}else{
	
	PILHA *aux = INICIO;
	INICIO = INICIO->proximo;
	INICIO->anterior = NULL; 
	free(aux);
	aux = NULL;
	}
}

void clear(){
	while(isEmpty() != true){
		pop();
	}
}


PILHA * ofirstEl(){
	if(isEmpty()){
		return NULL;
	}
	PILHA *aux1 = INICIO;
	aux1->proximo = NULL;
	aux1->anterior =NULL;	 

	return aux1;
}




void menu(){
	int op,x,y;
	do{
	
	do{
	system("cls");
	cout << "1 - Para adicionar um aluno\n";
	cout << "2 - Mostrar aluno do topo\n";
	cout << "3 - Remover do inicio\n";
	//cout << "4 - Retorna o primeiro aluno\n";
	cout << "4 - Limpar fila\n";
	cout << "5 - Sair\n";
	cout << "Opcao > ";
	cin  >> op;
	
	if(op > 6){
		cout << "Opcao invalida!!!";
		sleep(2);
		
	}
	system("cls");
	
	}while(op > 6); 
	
	switch(op){
	system("cls");
		case 1:
			char nome[40];
			int nota1,nota2;
			cout << "Adicionar aluno\n";
			cout << "***********************************\n"; 
			cout << "Nome:\n";
			
			cout << "Nota 2:\n";
			cout << "Nota 3:\n";
			 
			gotoxy(11,3);
			fflush(stdin);
			//setbuffer(stdin,NULL);
			gets(nome);
			gotoxy(11,4);
			cin >> nota1;
			gotoxy(13,5);
			cin >>nota2;
			push(nome,nota1,nota2);
		
		break;
		case 2:
			PILHA *aux1;
			aux1 = ofirstEl();
			if(aux1 ==NULL){
				break;
			} 
			
			cout << "Mostrar aluno do topo\n";
			cout << "***********************************\n"; 
		
			
			cout << "Nome :" <<	aux1->nome << "\n";
			
			cout << "Nota 1: "<< aux1->nota1 << "\n";
		
			
			cout << "Nota 2: "<< aux1->nota2 << "\n";
			
			system("pause");
			
		
		break;
		
		case 3:
			cout << "Remover do inicio\n";
			cout << "***********************************\n"; 
			pop();
			 
			
		break;
		case 4:
			cout << "Limpar fila\n";
			cout << "***********************************\n"; 
			clear();	
			
		
		break;
		
		
	
	}
	
	//getch();
	}while(op < 6);
	
	

}

int main(){
	menu();
	
	return 1;
}
