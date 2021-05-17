#include <stdio.h>
#include <stdlib.h>

struct no {
	int valor;
	struct no* proximo;
	struct no* anterior;
};
typedef struct no No;

struct pilha{
	No*TOPO;
};
typedef struct pilha Pilha;


Pilha* cria(Pilha* P)
{
	Pilha *novo = (Pilha*)malloc(sizeof(Pilha));
	novo->TOPO = NULL;
	return novo;
}

No* aloca(int v)
{
	No* novo = (No*)malloc(sizeof(No));
	novo->valor = v;
	novo->proximo = NULL;
	return novo;
}

int isEmpty(Pilha* P)
{
	if(!P->TOPO){
		return 1;	
	}
	return 0;	
}

void push(Pilha* P, int v)
{
	No* novo = aloca(v);
	if(isEmpty(P)){
		P->TOPO = novo;
		novo->anterior = NULL;
	}else{
		novo->anterior = P->TOPO;
		(P->TOPO)->proximo = novo;
		 P->TOPO = novo;
	}
}

void listar(Pilha* P)
{
	if(isEmpty(P)){
		return;
	}
	No* aux = P->TOPO;
	while(aux!=NULL){
		printf("%d\n", aux->valor);
		aux = aux->anterior;
	}
}

void pop(Pilha* P)
{
	if(isEmpty(P)){
		return;
	}
	No *segura = P->TOPO;
	P->TOPO = P->TOPO->anterior;
	segura = NULL;
	free(segura);
}


main()
{
	Pilha* pilha_1;
	pilha_1 = cria(pilha_1);
	
	Pilha* pilha_2;
	pilha_2 = cria(pilha_2);
	
	int i;
	for(i=1;i<=10;i++){
		push(pilha_1, i);
		push(pilha_2, i);
	}
	
	pop(pilha_1);
	pop(pilha_2);
	
	
	printf("Pilha 1\n\n");
	listar(pilha_1);
	
	printf("\nPilha 2\n\n");
	listar(pilha_2);
}
