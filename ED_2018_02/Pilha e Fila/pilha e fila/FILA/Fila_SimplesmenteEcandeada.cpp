#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Aluno{
	char nome[40];
	float nota[2];
	struct Aluno *prox;
}A;

typedef struct Pilha{
	A *inicio;
	A *fim;
}P;


A * alocA(){
	Aluno *novo = (A*) malloc (sizeof(A));
	novo->prox = NULL;	
}

P *alocP(){
	P *novo = (P*) malloc (sizeof(P));
	novo->inicio = NULL;
	novo->fim = NULL; 
}

bool isEmpty(A *inicioAluno){
	if(inicioAluno == NULL){
		return true;
	}else{
		return false;
	}
}


	
void push(A *pilha1,A aluno){
	Aluno *novo = alocA();
	novo = &aluno;
	
	novo->nota = n;
	novo->prox = TOPO;
	TOPO = novo;

		
}


void dequeue(A *inicioAluno){
	if(isEmpty(inicioAluno)){
		return;	
	}else{
		A *aux = inicioAluno->prox;
		free(inicioAluno);
		inicioAluno = aux;
	}
}

void clear(A *inicioAluno){
	if(isEmpty(inicioAluno)){
		return;
	}else{
		dequeue(inicioAluno);
	}
}

A* firstEl(A* inicioAluno){
	if(isEmpty(inicioAluno)){
		return NULL;
	}else{
		return inicioAluno;
	}
}



int main(){
	
	P *fila1 = NULL;
	A a1;
	
	a1.nota[1] = 2;

	
	push(fila1,a1);
	push(fila1,a1);

	
	
	return 1;
}
