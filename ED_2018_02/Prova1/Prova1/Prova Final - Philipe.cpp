#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include<unistd.h> 
#include<windows.h> 

void gotoxy(int x, int y){
     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){x-1,y-1});
}  

using namespace std;

typedef struct Dicionario{
	char palavra[40];
	int ocorrencia;
	struct Dicionario *prox;
	
}D;

D inicio,*no;

void menu();
void inserirD();
void editarD();
void listarD();
void excluirD();
bool buscarD();
void criarD();
void lerD(); 

int main(){
inicio.prox = NULL;
	
	menu();
	
	
	
	
	return 1;
}

void menu(){
	int op1,op2;
do{
	system("cls");
	cout << "1. Criar um novo dicionario:\n";
	cout << "2. Carregar dicionario:\n";
	cout << "3. Sair";
	cout << "\nOpcao >";
	cin >> op1;	
	
	
	switch(op1){
		case 1:
			do{
			
			do{
			system("cls");
			cout << "Criando um novo dicionario\n";
			cout << "1.Inserir\n";
			cout << "2.Listar\n";
			cout << "3.Editar\n";
			cout << "4.Excluir\n";
			cout << "5.Pesquisar\n";
			cout << "6.Salvar\n";
			cout << "7.Voltar\n";
			cout << "Opcao >";
			cin >> op2;
			if(op2<1 || op2>7) op2 = -1;
			
			}while(op2 == -1);
				system("cls");
				switch(op2){
					case 1:
						inserirD();
					break;	
					case 2:
						listarD();
					break;
					case 3:
						editarD();
					break;
					case 4:
						excluirD();
					break;
					case 5:
						bool bus;
						bus = buscarD();
						if(bus == 0) cout << "Palavra nao existe\n";
						if(bus == 1) cout << "Palavra existe\n";
						sleep(3); 
					break;
					case 6:
						criarD(); 
					break;	
					case 7:
						cout << "Voltando pro menu principal";
						sleep(2);
						op2 = -1;
					break;			
				}
			}while(op2 != -1 );
		break;
		
		case 2:
			
			lerD();
			do{
			
			do{
			system("cls");
			cout << "Criando um novo dicionario\n";
			cout << "1.Inserir\n";
			cout << "2.Listar\n";
			cout << "3.Editar\n";
			cout << "4.Excluir\n";
			cout << "5.Pesquisar\n";
			cout << "6.Salvar\n";
			cout << "7.Voltar\n";
			cout << "Opcao >";
			cin >> op2;
			if(op2<1 || op2>7) op2 = -1;
			
			}while(op2 == -1);
			
				system("cls");
				
				switch(op2){
					case 1:
						inserirD();
					break;	
					case 2:
						listarD();
					break;
					case 3:
						editarD();
					break;
					case 4:
						excluirD();
					break;
					case 5:
						bool bus;
						bus =buscarD();
						if(bus == 0) cout << "Palavra nao existe\n";
						
						if(bus == 1) cout << "Palavra existe\n";
						
						sleep(3); 
					break;
					case 6:
						criarD(); 
					break;	
					case 7:
						cout << "Voltando pro menu principal";
						sleep(2);
						op2 = -1;
					break;	
								
				}
			}while(op2 != -1 );
			
		break;	
		
		case 3:
			cout<<"Fechando o sistema...";
			sleep(2);
			exit(2); 
		break; 
	}
	
	inicio.prox = NULL;
	
}while(op1 != -1);

}

void inserirD(){
	no = &inicio;
	int x = 1 ;
	
	char tempPalavra[40];
	
	cout << "Digite uma palavra: ";
	scanf("%s",&tempPalavra);
	
	while(no->prox){
		no = no->prox;	
	
		x = strcmp(no->palavra,tempPalavra);
		
		if(x==0){
			no->ocorrencia = no->ocorrencia + 1;
			cout << "\n\n\tPalavra ja existe adicionado mais um ao numero de ocorrencias";
			getch();
			break;
		}
		
	}


	

	if(x != 0 ){
		
		no = &inicio; 
		while(no->prox) {
		no=no->prox;
		}
		
		no->prox = new(D);
		no = no->prox; 
		
		no->ocorrencia = 1; 
		
		strcpy(no->palavra,tempPalavra);
		
		no->prox = NULL;
		
		cout << "Nova palavra cadastrada";
		
	}else{
		cout << "Palavra ja existe";
	}
	
}

void editarD(){
	
	if(inicio.prox == NULL){
		cout << "Dicionario vazio";
		sleep(2);
		return;
	}
	int x;
	char tempPalavra[40];
	
	cout << "Digite a palavra que deseja editar: ";
	cin >> tempPalavra;
	no = &inicio;
	while(no){
		x=  strcmp(no->palavra,tempPalavra);
		if (x == 0){
			cout << "Digite a nova palavra:";
			cin >> tempPalavra;
			strcpy(no->palavra,tempPalavra);
			return;
		}
		no = no->prox;
	}

		cout << "Essa palavra nao existe";
		sleep(2);
	
}


void excluirD(){

	if(inicio.prox == NULL){
		cout << "Dicionario vazio";
		sleep(2);
		return;
	}
	
	int x = 0;
	char tempPalavra[40];
	no = &inicio;
	
	
  	D *ant;
  	printf("Digite a letra que deseja excluir:");
  	cin >> tempPalavra;
  	
  	while (no->prox != NULL){
  	  ant = no;	
  	  no = no->prox;	
  	  x = strcmp(no->palavra,tempPalavra);
	  if(x == 0) break;
  	  
  	  
	  			
	}
	
	if(x == 0){
		ant->prox = no->prox;
		delete(no);
 		no = NULL;
 		ant = NULL;
 		
	}
  	else{
  		cout << "Letra nao existe";	
  		sleep(2);
	}
  	
  	

		
}

void listarD(){
	if(inicio.prox == NULL){
		cout << "Dicionario vazio";
		sleep(2);
		return;
	}
	no = inicio.prox;
	int i = 0;
	cout << "Listar de palavras\n\n";
	while(no){
		i++;
		gotoxy(1,i+2);
		printf("Palavra %d:%s",i,no->palavra);
		gotoxy(30,i+2);
		cout <<"Ocorrecias:"<< no->ocorrencia;
		no = no->prox;
	}
	getch();
	
}



void criarD(){
	if(inicio.prox == NULL){
		cout << "Dicionario vazio";
		sleep(2);
		return;
	}
	FILE *file;
	char nomeD[20];
	cout << "Digite o nome do arquivo: ";
	cin >> nomeD;
	strcat(nomeD,".txt");
file = fopen(nomeD,"w");
		if(file == NULL){
			cout << "Erro na criacao do arquivo";
			sleep(2);
			return;
		}	
		
		no = inicio.prox;
		
		while(no){
			
			fprintf(file,"%d\n",no->ocorrencia);
			fprintf(file,"%s\n",no->palavra);
			no = no->prox;
		}
	 
fclose(file);	
}

void lerD(){
	system("cls");
	FILE *file;
	char nomeD[20];
	cout << "Digite o nome do arquivo: ";
	cin >> nomeD;
	strcat(nomeD,".txt");
file = fopen(nomeD,"r");
		if(file == NULL){
			cout << "Erro na leitura do arquivo";
			sleep(2);
			lerD();
		}	
		
		no = &inicio;
		
		while(!feof(file)){
			D aux;
			no->prox = new(D);
			no = no->prox;
			
			fscanf(file,"%d\n",&aux.ocorrencia);
			fscanf(file,"%s\n",&aux.palavra);
			
			no->ocorrencia = aux.ocorrencia ;
			int i;
			
			strcpy(no->palavra,aux.palavra);
		
			
			no->prox = NULL;
		}
	 
fclose(file);	
}

bool buscarD(){
	if(inicio.prox == NULL){
		cout << "Dicionario vazio\n";
		sleep(2);
		return 0;
	}
	
	int x;
	char tempPalavra[40];
	cout << "Digite a palavra que procura:";
	cin >> tempPalavra;
	no = &inicio;
	while(no){
		x=  strcmp(no->palavra,tempPalavra);
		if (x == 0){
		
			strcpy(no->palavra,tempPalavra);
			return 1; 
		}
		no = no->prox;
	}

		return 0;
	
}


