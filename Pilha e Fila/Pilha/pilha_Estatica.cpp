#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int const MAXTAM = 4;

typedef struct Aluno{
	char nome[40];
	int nota[3];
}A;

A pilha_Aluno[MAXTAM],*pont_pilha;
int topo = 0;

void pilha_Construtor(){
	topo = -1;
}

bool isEmpty(){
	if(topo == -1)
		return true;
	else
		return false;		
}

bool isFull(){
	if(topo ==MAXTAM - 1)
		return true;
	else
		return false;	
}

bool push(char *nome,float nota1,float nota2){
	if(isFull()){
		return false;
	}else{
		topo++;
		strcpy(pilha_Aluno[topo].nome,nome);
		pilha_Aluno[topo].nota[0] = nota1;
		pilha_Aluno[topo].nota[1] = nota2;   
		
		return true;
	}
}

//bool pop(A &valor){
bool pop(){
	if(isEmpty())
		return false;
	else{
		//valor = (pilha_Aluno[topo]);
		topo--;	
		return true;
	}	
}


bool topEl(){
	if(isEmpty())
		return false;
	else{
		pont_pilha = &pilha_Aluno[topo];
		return true;
	}	
}

bool clear(A &valor){
	if(isEmpty())
		return false;
	while(isEmpty() != true){
		valor = pilha_Aluno[topo];
		topo--;
	}	
}

int main(){
	void pilha_Construtor();
	
	push("Philipe",7.5,7.8);
	push("Pedro",8.5,7.8);
	push("Ruan",9.5,4.8);
	
	printf("\n**********    %d *****************\n",topo); 	
	pop();	
	topEl();
	printf("%s\n%d\n%d\n",pont_pilha->nome,pont_pilha->nota[0],pont_pilha->nota[1]);
	
	//printf("%s\n%d\n%d\n",pont_pilha->nome,pont_pilha->nota[0],pont_pilha->nota[1]);

	push("Zack",8.5,7.8);
	
		printf("\n**********    %d *****************\n",topo); 	
		
	topEl();
	printf("%s\n%d\n%d\n",pont_pilha->nome,pont_pilha->nota[0],pont_pilha->nota[1]);
	clear(pilha_Aluno[topo]);
	
			printf("\n**********    %d *****************\n",topo); 	
	printf("%s\n%d\n%d\n",pont_pilha->nome,pont_pilha->nota[0],pont_pilha->nota[1]);	

return 1;
}





