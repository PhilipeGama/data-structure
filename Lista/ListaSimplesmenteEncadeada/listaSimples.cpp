#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

typedef struct lista{
	int numero;
	struct lista *proximo;
}L;

L *lista=NULL,*inicio = NULL;

bool inicializarPonteiros(){
	lista = NULL;
	inicio = NULL;
	lista = inicio;
} 

L* alocaPilha(){
	L *novo = (L*) malloc (sizeof(L));
	novo->proximo = NULL;
	if(novo == NULL){
		cout << "Erro na alocação da pilha";
		return NULL;
	}else{
		return novo;
	}
}


void addLista(int x){
	if(alocaPilha()!=NULL){
			
	
			if(inicio == NULL){
				inicio = alocaPilha();
				inicio->numero = x;
				lista = inicio;
			}else{
				lista->proximo = alocaPilha();
				lista = lista->proximo;
				lista->numero = x;
				
			}
	}else{
		cout << "Erro na adicionar na lista\n";
	}
}

void percorreLista(){
	lista = inicio;
	int i = 0;
	while(lista!=NULL){
		i++;
		printf("Numero %d: %d\n",i,lista->numero);
		lista = lista->proximo;
	}
}

void removerLista(int numero){
	L *ant = NULL,*aux = inicio;
	
	
	while(aux){
		if(inicio->numero == numero){
	
			aux = inicio;
			inicio = inicio->proximo;
			free(aux);
			break;
		}
		if(numero == aux->numero){
			if(aux->proximo == NULL){
			
				ant->proximo = NULL;
				free(aux);
				aux = NULL;
				break;
			}else{
		
				ant->proximo = aux->proximo;
			
				free(aux);
				aux = NULL;
			
				break;
			}
			
		}
		ant = aux;
		aux = aux->proximo;
	}
}


int main(){
inicializarPonteiros();
addLista(1);
addLista(3);
addLista(4);

percorreLista();

removerLista(1);

percorreLista();

}
