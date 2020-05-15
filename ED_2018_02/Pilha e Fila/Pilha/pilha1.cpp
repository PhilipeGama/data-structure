#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int const MAXTAM = 10;

typedef struct Aluno{
	char nome[40];
	float nota1;
	float nota2;
	struct Aluno *prox;
}A;

typedef struct Pilha{
	int topo;
	A *aluno;
}P;

P *pilhaAluno,*inicio;

bool inicializarPonteiros(){
	pilhaAluno = inicio = NULL; 
}



bool criaPilha(){
	pilhaAluno = (P*) malloc(sizeof(P));
	if(pilhaAluno = NULL)
	return false;
	 	
	pilhaAluno->topo = -1 ; 
	return true;
}


bool isEmpty(){
	if(pilhaAluno->topo == 0)
		return true;
	else
		return false;		
}


bool isFull(){
	if(pilhaAluno->topo == MAXTAM - 1)
		return true;
	else
		return false;	
}


bool push(char nome[],float nota1,float nota2){

	if(isFull()){
		return false;
	}else{
		 
		A *novo;
		novo = (A*) malloc (sizeof(A));
		
		strcpy(novo->nome,nome);
		novo->nota1 = nota1;
		novo->nota2 = nota2;
		
		
		if(inicio == NULL){
			inicio = pilhaAluno;
			pilhaAluno->aluno = novo;	
			pilhaAluno->topo++; 
		}else{
			
		
		
		}	
		return true;
	}
		
	
}
/*
bool pop(A &valor){
	if(isEmpty())
		return false;
	else{
		*valor = pilhaAluno;
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

bool clear(pilhaAluno &valor){
	if(isEmpty())
		return false;
	while(isEmpty()!= true){
		valor = pilhaAluno;
		pilhaAluno->topo--;
	}	
}
*/

int main(){
	void pilha_Construtor();
	
	//push("Philipe",7.5,7.8);
	//push("Pedro",8.5,7.8);
//	push("Ruan",9.5,4.8);
	
	//pop(pilha_Aluno[topo]);
	
		
	//topEl();
	//printf("%s %d %d",pont_pilha->nome,pont_pilha->nota[0],pont_pilha->nota[1]);
	
	//printf("%s\n%d\n%d\n",pont_pilha->nome,pont_pilha->nota[0],pont_pilha->nota[1]);

	//push("Zack",8.5,7.8);
	
	//topEl();
	//printf("%s\n%d\n%d\n",pont_pilha->nome,pont_pilha->nota[0],pont_pilha->nota[1]);
	//clear(pilha_Aluno[topo]);
	
	
	//printf("%s %d %d",pont_pilha->nome,pont_pilha->nota[0],pont_pilha->nota[1]);	
	






return 1;
}





