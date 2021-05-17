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

typedef struct fila{
	int nota1;
	int nota2;
	char nome[20];
	struct fila *proximo;
	struct fila *anterior;
}Fila;

int lin;



int isEmpty(Fila *inicio){
	if(inicio == NULL){
		return true;
	}else{
		return false;
	}
}

Fila* aloca (){
	Fila* novo = (Fila*)malloc(sizeof(Fila));
	if(!novo){
		return NULL;
	}else{
		novo->proximo = NULL;
		return novo;
	}
}


void push(char nome[],int nota1,int nota2,Fila *inicio,Fila *fim){
	Fila *novo;
	novo = aloca();
	
	novo->nota1 = nota1;
	novo->nota2 = nota2;
	strcpy(novo->nome,nome);
	
	if(isEmpty(inicio)){
		novo->anterior = NULL;
		inicio = novo;
		fim = inicio;
	
		
	}else{
		novo->anterior = fim;
		fim->proximo = novo;
		fim = novo;
	}
}

bool dequeue(Fila *inicio){
	
	if(isEmpty(inicio) == true){
		return false;
	}
	
	if(inicio->proximo == NULL){
		free(inicio);
		inicio = NULL;
	}else{
	
	Fila *aux = inicio->proximo;
	free(inicio);
	inicio = aux;
	
	}
}


void clear(Fila *inicio){
	while(isEmpty(inicio) != true){
		dequeue(inicio);
	}
}


Fila * firstEl(Fila *inicio){
	if(isEmpty(inicio) == true){
		return NULL;
		cout << "Listar Vazia";
		getch();
	}
	return inicio;
}

void menu(Fila *inicio,Fila *fim){
	int op,x,y;
	do{
	
	do{
	system("cls");
	cout << "1 - Para adicionar um aluno\n";
	cout << "2 - Listar alunos\n";
	cout << "3 - Remover aluno do inicio\n";
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
			
			cout << "Nota 1:\n";
			cout << "Nota 2:\n";
			 
			gotoxy(11,3);
			fflush(stdin);
			//setbuffer(stdin,NULL);
			gets(nome);
			gotoxy(11,4);
			cin >> nota1;
			gotoxy(11,5);
			cin >>nota2;
			push(nome,nota1,nota2,inicio,fim);
		
		break;
		case 2:
			Fila *aux2 = NULL;
			aux2 = firstEl(inicio);
			if(aux2 == NULL){
				cout << "Pilha vazia";
				getch();
				break;
			} 
			
			cout << "\tListar de Alunos\n";
			//cout << "***********************************\n"; 
		
			gotoxy(1,3);
			cout << "Nome ";
			gotoxy(20,3);
			cout << "Nota 1";
			gotoxy(30,3);
			cout << "Nota 2";
			lin = 5;
			while(aux2!=NULL){
				gotoxy(1,lin);
				cout << aux1->nome;
				gotoxy(20,lin);
				cout << aux1->nota1;
				gotoxy(30,lin);
				cout << aux1->nota2;
				lin++;
				aux1=aux1->proximo;
			}
			getch();
			
		
		break;
		
		case 3:
			cout << "Removendo do inicio da pilha";
			sleep(1);
			cout << ".";
			sleep(1);
			cout << ".";
			sleep(1);
			cout << ".";
			sleep(1);
			dequeue(inicio);
			
			 
			
		break;
		case 4:
			cout << "Limpando a pilha";
			sleep(1);
			cout << ".";
			sleep(1);
			cout << ".";
			sleep(1);
			cout << ".";
			sleep(1);
			clear(inicio);	
			
		
		break;
		case 5:
			exit(1);
		break;
		
		
	
	}
	
	}while(op < 6);
	
	

}

int main(){
	Fila *inic1=NULL,*fim=NULL;
	menu(inic1,fim);
	
	return 1;
}
