 #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <conio.h>
#include <windows.h>


using namespace std;

void gotoxy(int x, int y){
     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){x-1,y-1});
}  

typedef struct palavras{
	char palavra[40];
	char nArquivo[40];
	
	struct palavras *prox;
}P;

P *inicioP = NULL,*fimP = NULL; 

typedef struct letras{
	int ocorrencia;
	char letra;
	P *inicio;
	P *fim;
	struct letras *prox;
	struct letras *ant;
}L;

L *inicioL = NULL,*fimL = NULL;

//aloca memoria

L* novaLetra(){
	L *novaL;
	novaL = (L*) malloc (sizeof(L));
	novaL->inicio = NULL;
	novaL->fim = NULL;
	novaL->ant = NULL;
	novaL->prox = NULL;
	novaL->ocorrencia = 0;
	return novaL;
}


P* novaPalavra(){
	P *novaP;
	novaP = (P*) malloc (sizeof(P));
	novaP->prox = NULL;
	return novaP;
}



void inserirPalavra(L *auxL,char npalavra[],char nArquivo[]){
	
	P *auxP = auxL->inicio;
	
	while(auxP){
		if(strcmp(auxP->palavra,npalavra) == 0){
				return;
		}
		auxP = auxP->prox;
	}
	
	auxL->ocorrencia = auxL->ocorrencia + 1;
	
	P *novap = novaPalavra();
	strcpy(novap->palavra,npalavra);
	strcpy(novap->nArquivo,nArquivo);
	
	
	if(auxL->inicio == NULL){
		auxL->inicio = novap;
		auxL->fim = auxL->inicio;
	}else{
		auxL->fim->prox = novap;
		auxL->fim = novap;
	}
};




void inserirLetra(char npalavra[],char nArquivo[]){
	
	if(inicioL == NULL){
		inicioL = novaLetra();
		
		inicioL->letra = npalavra[0];
		inserirPalavra(inicioL,npalavra,nArquivo);
		fimL = inicioL; 
		return;
	}
	
	L *auxL = inicioL;
	while(auxL){
			if(auxL->letra == npalavra[0]){
			
				inserirPalavra(auxL,npalavra,nArquivo);
				return;
			}
			auxL = auxL->prox;		
	}
	
	
	L *novaL = novaLetra();
	novaL->letra = npalavra[0];

	novaL->ant = fimL;
	fimL->prox = novaL;
	fimL = novaL;
	
	inserirPalavra(novaL,npalavra,nArquivo);
	
	
}


P* buscarP(L *auxL,char npalavra[]){
	P *auxP = auxL->inicio;
	while(auxP){
		if(strcmp(auxP->palavra,npalavra) == 0){
		
			return auxP;
		}
		auxP = auxP->prox;
	}
	return NULL;
}


L* buscarLetra(char npalavra){
	L *auxL = inicioL;
	while(auxL){
		if(auxL->letra == npalavra){
		
			return auxL;
		}
		
		auxL = auxL->prox;
	}
	
	return NULL;
}



P* buscarPalavra(char npalavra[]){
	L *auxL = inicioL;
	while(auxL){
		if(auxL->letra == npalavra[0]){
			P *auxP = auxL->inicio;
			while(auxP){
				if(strcmp(auxP->palavra,npalavra) == 0){
					return auxP;
				}
					auxP = auxP->prox;
			}
			return NULL;
		}
		auxL = auxL->prox;
	}
	return NULL;
}




bool excluirLetra(L* auxL){	
			cout << "0";
	if(auxL == NULL){
		cout << "1";
		return false;
		
	}
	
	if(auxL->ant == NULL && auxL->prox == NULL){
		cout << "2";
		free(inicioL);
		inicioL = NULL; 
		
		return true;
	}
	if(auxL->ant == NULL && auxL->prox != NULL){
		cout << "3";
		L *auxL2 = inicioL;
		inicioL = inicioL->prox;
		inicioL->ant = NULL;
		free(auxL2);
		return true;
		
	}
	
	L *auxD = auxL->ant;
	auxD->prox = auxL->prox;
	free(auxL);
	return true;
}


bool excluirPalavra(char npalavra[]){
	L *auxL  = inicioL;
	P *auxP = NULL;
	
	if(auxL == NULL){
		return false;
	}else{
		while(auxL){
		
		P *antP = NULL,*auxP = auxL->inicio;
		if(auxL->letra == npalavra[0]){
		
			while(auxP){
				if(strcmp(auxP->palavra,npalavra)== 0){
					if(auxP == auxL->inicio){
						P *remove = auxL->inicio;
						auxL->inicio = auxL->inicio->prox;
						free(remove);
						
						if(auxL->inicio == NULL){
							excluirLetra(auxL);
							
						}
						
						return true;
						
					}
					
					if(auxP->prox == NULL){
						free(auxP);
						auxP = NULL;
						antP->prox = NULL;
						return true;
					}else{
						antP->prox = auxP->prox;
						free(auxP);
						auxP = NULL;
						return true;
					}
				}
				antP = auxP;
				auxP = auxP->prox;	
				
			}
		
		}
		
		auxL = auxL->prox;
	}

	}

}

void salvarArquivo(char *nome){
	FILE *file = NULL;
	L *auxL = inicioL;
	P *auxP;
	
	file = fopen(nome,"w");
	if(file == NULL){
		cout << "Erro na cricao do arquivo";
		return;
	}
	while(auxL){
		auxP = auxL->inicio;
		
		while(auxP){
			fprintf(file,"%s\n",auxP->palavra);
			fprintf(file,"%s\n",auxP->nArquivo);
			fprintf(file,"*********\n");
				
			auxP = auxP->prox; 
		}
		
		auxL = auxL->prox; 
	}
	fclose(file);
}

void lerArquivo(){
	FILE *file = NULL;
	
	file = fopen ("palavrasDesorganizadas.txt","r");
	if(file == NULL){
		cout << "Erro na leitura do arquivo";
		return;
	} 
	char npalavra[40],nArquivo[40];
	while(!feof(file)){
		fscanf(file,"%s\n",&npalavra);
		fscanf(file,"%s\n",&nArquivo);
		fprintf(file,"*********\n");
		inserirLetra(npalavra,nArquivo);
	}
	
	fclose(file);
		
}

int tamanhoLista(L *inicio){
	L *auxL = inicio;
	int tamanho = 0;
	while(auxL){
		tamanho++;
		auxL = auxL->prox;
	}
	return tamanho;
	
}


void preencherVetorL(L *auxL,L *vetor[]){
	int cont = 0;
	while(auxL){
		vetor[cont] = auxL;
		cont++;
		auxL = auxL->prox;
	} 
}

void trocaVetorL(L *vetor[],int i,int j){
	L *aux = vetor[i];
	vetor[i] = vetor[j];
	vetor[j] = aux;    
}


void encadearVetorL(L *vetor[],int tamanho){
	vetor[0]->ant = NULL;
	int i = 1;
	while(i < tamanho){
		
		vetor[i-1]->prox = vetor[i];
		vetor[i]->ant = vetor[i-1];
		i++;
	}
	vetor[tamanho-1]->prox = NULL;
}


void bubbleSortLetras(L *inicio){
	L *auxL1= NULL, *auxL2 = NULL;
	auxL1 = inicioL;
	
	L *menor = NULL;

		
	while(auxL1){
		auxL2 = auxL1->prox;
			
		while(auxL2){
			
			if(auxL1->letra > auxL2->letra){
						
						
						
					    P *inicio = auxL2->inicio;
						P *fim = auxL2->fim;
						char letra = auxL2->letra;
						int ocorrencia = auxL2->ocorrencia;
					
						
						auxL2->inicio = auxL1->inicio;
						auxL2->fim = auxL1->fim;
						auxL2->letra = auxL1->letra;
						auxL2->ocorrencia = auxL1->ocorrencia;
						
						
						auxL1->inicio = inicio; 
						auxL1->fim = fim;
						auxL1->letra = letra; 
						auxL1->ocorrencia = ocorrencia;
						
						
			}
			auxL2 = auxL2->prox;	
		}	
		auxL1 = auxL1->prox;
	}
		
}

void bubbleSortPalavras(){
	L *auxL = inicioL;
	
	while(auxL){
		P *auxP1 = auxL->inicio;
		while(auxP1){
			P *auxP2 = auxP1->prox;
			while(auxP2){
				if(strcmp(auxP1->palavra,auxP2->palavra) > 0){
					char trocaPalavra[40];
					strcpy(trocaPalavra,auxP2->palavra);
					strcpy(auxP2->palavra,auxP1->palavra);
					strcpy(auxP1->palavra,trocaPalavra);
					
				}
				auxP2 = auxP2->prox;
			}
			auxP1 = auxP1->prox;
		}
		auxL = auxL->prox;	
	}
	
	
}

void insertSortLetras(L **inicio){
	
	L *auxL =  *inicio;

	int tamanho = tamanhoLista(auxL);
	L *vetor[tamanho];

	preencherVetorL(auxL,vetor);
	
	
	L *key;
	int i,j;
	for(i = 1; i < tamanho ; i++){
		key = vetor[i];
		j = i - 1;
		while(j >= 0 && vetor[j]->letra > key->letra){
			vetor[j+1] = vetor[j];
			j  = j - 1;
		}
		vetor[j+1] = key;  
	}
	encadearVetorL(vetor,tamanho);
	*inicio = vetor[0]; 
	
}

void selectSortLetra(L **inicio){
	L *auxL = *inicio;
	int tamanho = tamanhoLista(inicioL);
	L *vetor[tamanho];
	int cont = 0;
	
	preencherVetorL(auxL,vetor);
	int i,j,tempJ;
	
	L *auxTroca; 
	
	for(i = 0;i < tamanho - 1; i++){
		bool troca = false;
		char menorL = 'z'; 
		for(j =  i + 1; j < tamanho ; j++){
			if(vetor[i]->letra > vetor[j]->letra){
				if(vetor[j]->letra < menorL){
					troca = true;
					tempJ = j ; 
					menorL = vetor[j]->letra;
				}
			}
		}
		if(troca == true){
			trocaVetorL(vetor,i,tempJ);
		}
	}	
	encadearVetorL(vetor,tamanho);
	*inicio = vetor[0]; 
	
}
/*
void shellSort(int *vet, int size) {
    int i , j , value;
    int gap = 1;
    
    while(gap < size) {
        gap = 3*gap+1;
    }
    
    while ( gap > 1) {
        gap /= 3;
        for(i = gap; i < size; i++) {
            value = vet[i];
            j = i;
            while (j >= gap && value < vet[j - gap]) {
                vet[j] = vet [j - gap];
                
                j = j - gap;
            }
            vet [j] = value;
        }
    }
}
*/



void shellIntercalaLetra(L *vetor[],int tamanho){
	int i , j , value;
	L *auxTroca;;
	
	int gap = 1;
	
	while(gap < tamanho){
		gap = 3*gap+1;
	}
	 
	while(gap > 0){
		cout<< "gab:" << gap << "\n";
		
		gap = (gap)/2;
		
		for(i = gap;i < tamanho; i++){
			auxTroca = vetor[i];
			j = i;
		} 
		while( auxTroca->letra < vetor[j-gap]->letra){
			vetor[j] = vetor[j - gap];
			j -= gap;
			if(j<gap) break;
		}
		vetor[j] = auxTroca;
	}

}

void iniciaShell(L **inicio){
	int tamanho = tamanhoLista(inicioL);
	L *vetor[tamanho];
	L *auxL = inicioL;
	preencherVetorL(auxL,vetor);
	shellIntercalaLetra(vetor,tamanho);
	
	encadearVetorL(vetor,tamanho);
	*inicio = vetor[0]; 
}


void intecarlaMerge(L *vetor[],int inicio,int fim,int meio){
	int poslivre,inicioV1,inicioV2,i;
	L *auxL[fim+1];
	inicioV1 = inicio;
	inicioV2 = meio+1;
	
	poslivre = inicio;
	while(inicioV1 <= meio && inicioV2 <= fim){
		if(vetor[inicioV1]->letra <= vetor[inicioV2]->letra){
			auxL[poslivre] = vetor[inicioV1];
			inicioV1++;
		}else{
			auxL[poslivre] = vetor[inicioV2];
			inicioV2++;
		}
		poslivre++;		
	}
	for(i = inicioV1 ; i<=meio ; i++){
		auxL[poslivre] = vetor[i];
		poslivre++;
	}
	for(i = inicioV2;i<=fim;i++){
		auxL[poslivre] = vetor[i];
		poslivre++;
	}
	
	for(i = inicio;i<=fim;i++){
		vetor[i] = auxL[i];
	}
	
}



void mergeSortLetra(L *vetor[],int inicio,int fim){
	int meio;
	if(inicio < fim){
		meio = (inicio+fim)/2; 
		mergeSortLetra(vetor,inicio,meio);
		mergeSortLetra(vetor,meio+1,fim);
		intecarlaMerge(vetor,inicio,fim,meio);
		
	}
}

void iniciaMerge(L **inicio){
	L *auxL = *inicio;
	int tamanho = tamanhoLista(auxL);
	L *vetor[tamanho];
	preencherVetorL(auxL,vetor);
	mergeSortLetra(vetor,0,tamanho-1);
	
	encadearVetorL(vetor,tamanho);
	* inicio = vetor[0];	
}



int particaoQuickL(L *vetor[],int p,int r){
	L *pivo;
	pivo = vetor[(p+r)/2];
	int i,j;
	i = p - 1;
	j = r + 1;
	while(i < j){
		do{
			j = j - 1;
		}while(vetor[j]->letra > pivo->letra);
		do{
			i = i + 1; 
		}while(vetor[i]->letra < pivo->letra);
		if(i < j) trocaVetorL(vetor,i,j);
		
	}
	return j;
}

void quickSortLetras(L *vetor[],int p,int r ){
	int q;
	if(p<r){
		q = particaoQuickL(vetor,p,r);
		quickSortLetras(vetor,p,q);
		quickSortLetras(vetor,q+1,r);
	}
}

 void quick(L **inicio){
 	L *auxL = *inicio;
 	int tamanho = tamanhoLista(auxL);
	L *vetor[tamanho];
	//L *auxL = *inicio;
	preencherVetorL(auxL,vetor);
	
	quickSortLetras(vetor,0,tamanho-1);
	encadearVetorL(vetor,tamanho);
	*inicio = vetor[0];	
 }
 
// A Quicksort
void qs(char *item,int left,int right)
{
	register int i,j;
	char x,y;
	
	i = left;j = right;
	x = item[(left+right)/2];
	
	do{
		while(item[i]<x && j<right) i++;
		while(x<item[j] && j>left) j--;
		
		if(i<=j){
			y = item[i];
			item[i] = item[j];
			item[j] = y;
			i++,y--;
			 
		}	
	
	}while(i<=j);
	
	if(left<j) qs(item,left,j);
	if(i<right)qs(item,i,right);	
}

// Função de inicialização da Quicksort
void quick(char *item,int count)
{
	qs(item,0,count-1);	
}



void mostraDicionario(){
	L *auxL = inicioL;
	cout << "Lista de Palavra\n";
	while(auxL){
		P *auxP =auxL->inicio;
		cout << "**************************************\n";
		printf("Letra %c Ocorrencias %d\n",toupper(auxL->letra),auxL->ocorrencia);
		while(auxP){
			cout << "**************************************\n";
			cout << "Palavra: " << auxP->palavra << "\n";
			cout << "Arquivo: " << auxP->nArquivo << "\n";
			auxP = auxP->prox; 	
		}
				
		auxL = auxL->prox;
	}
}






int menuInicial(){
	int op,op2;
	L* auxL;
	P* auxP; 
	char npalavra[40],narquivo[40],resp;
	bool verificacao;
	do{
		system("cls");
		cout << "Lista de Dicionario \n\n";
		cout << "1 - Inserir\n";
		cout << "2 - Editar\n";
		cout << "3 - Excluir\n";
		cout << "4 - Pesquisar\n";
		cout << "5 - Metodos de Ordenacao\n";
		cout << "6 - Mostra Dicionario\n";
		cout << "0 - Sair\n"; 
		cout << "Opcao > ";
		cin >> op;
		system("cls");
		
		
		
		switch(op){
			case 0:
				cout << "Saindo...";
			break;
				
				case 1: 
				cout << "Inserir palavra\n";
				cout << "**************************\n"; 
				cout << "Palavra:\n";
				
				cout << "Arquivo:\n";
			
				cout << "**************************\n"; 
				gotoxy(10,3);
				cin >> npalavra;
				strlwr(npalavra);
				gotoxy(10,4);
				cin >> narquivo;
				inserirLetra(npalavra,narquivo);	
			
			break;
			
			
			case 2:
				
				cout << "Editar palavra\n";
				cout << "**************************\n"; 
				cout << "Palavra:\n";
				cout << "**************************"; 
				gotoxy(10,3);
				cin >> npalavra;
				strlwr(npalavra);
				if(verificacao == true){
					cout << "\nNovos Dados";
					cout << "\n**************************"; 
					
					cout << "\nPalavra: ";
					cout << "\nArquivo: ";
					
					cout << "\n**************************"; 
					gotoxy(10,7);
					cin >> npalavra;
					gotoxy(10,8);
					cin >> narquivo; 
					
					inserirLetra(npalavra,narquivo);
				}else{
					cout << "\nPalavra nao encotrada";
				} 	
				
						 
			break;	
			
			case 3:
				cout << "Excluir palavra\n";
				cout << "**************************\n"; 
				cout << "Palavra:\n";
				cout << "**************************\n"; 
				gotoxy(9,3);
				cin >> npalavra;
				strlwr(npalavra);
				
				excluirPalavra(npalavra); 
			break;	
			
			case 4:
				int op2;
				
				do{
					
				system("cls");
					
				cout << "Buscar\n";
				cout << "*************\n"; 
				cout << "1 - Letra\n";
				cout << "2 - Palavra\n";
				cout << "0 - Voltar\n";
				cout << "Opcao > \n";
				cout << "*************\n"; 
				gotoxy(9,6);
				cin >> op2;
				
				system("cls");
				
				switch(op2){
					case 0:
						cout << "Voltando";
					break;	
					
					case 1:
						char pletra;
						cout << "Buscando por Letra\n";
						cout << "**************************\n"; 
						cout << "Letra:\n";
						cout << "**************************\n"; 
						gotoxy(7,3);
						cin >> pletra;
						
						auxL = buscarLetra(pletra);
						
						if(auxL != NULL){
							system("cls");
							auxP = auxL->inicio;
							//cout << "Letr A " << auxL->ocorrencia << "\n";
							printf("Letra %c numero de palavras %d\n",toupper(auxL->letra),auxL->ocorrencia);
							cout << "*******************************\n"; 
							int i=1;
							
							while(auxP){
								cout << "Numero " << i++ << endl;    
								cout << "Palavra: " << auxP->palavra << "\n";
								cout << "Arquivo: " << auxP->nArquivo << "\n";
								auxP = auxP->prox; 	
								cout << "*******************************\n"; 
							}
							
						}
						
						 
					break;	
					
						
					case 2:
						cout << "Buscando por Letra\n";
						cout << "**************************\n"; 
						cout << "Palavra:\n";
						cout << "**************************\n"; 
						gotoxy(10,3);
						cin >> npalavra;
						auxP = buscarPalavra(npalavra);
						if(auxP == NULL){
							cout << "\nPalavra nao encontrada";
						}else{
							cout << "\nPalavra: " <<auxP->palavra << "\n";
							cout << "Arquivo: " <<auxP->nArquivo <<  "\n";
							
						}
						cout << "**************************\n"; 
						
					break;	
					
				
					
					default:
						cout << "Opcao invalida";
					break;	
					
				}
				
				getch();
				
				}while(op2 != 0);
				
				
			break;	
			case 5:
				char nome[40];
				do{
					system("cls");
					cout << "1 - Metodo burbblesort\n";
					cout << "2 - Metodo selectSort\n";
					cout << "3 - Metodo insertSort\n";
					
					cout << "4 - Metodo shellSort\n";
					cout << "5 - Metodo mergeSort\n";
					cout << "6 - Metodo quickSort\n";
					cout << "0 - Voltar\n";
					cout << "Opcao >> ";
					cin >> op2; 
					system("cls");
					switch(op2){
					
						case 0:
							cout << "Voltando";
						break;
						case 1:
							cout << "Metodo BurbbleSort";
							bubbleSortLetras(inicioL);
							
							strcpy(nome,"BubbleSort.txt");
							
							salvarArquivo(nome);
						break;	
						case 2:
						
							cout << "Metodo SelectSort\n";
							
							selectSortLetra(&inicioL);
							strcpy(nome,"SelectSort.txt");
							salvarArquivo(nome);	
							
						break;
						case 3:
							cout << "Metodo InsertSort\n";
							insertSortLetras(&inicioL);
							strcpy(nome,"InsertSort.txt");
							salvarArquivo(nome);	
						break;	
						
						case 4:
							cout << "Metodo ShellSort\n";
							iniciaMerge(&inicioL);
							strcpy(nome,"ShellSort.txt");
							salvarArquivo(nome);
						break;	
						case 5:
							cout << "Metodo MergeSort.txt\n";
							iniciaMerge(&inicioL);
							strcpy(nome,"MergeSort.txt");
							salvarArquivo(nome);
								
						break;
						break;	
						case 6:
							cout << "QuickSort";
							quick(&inicioL);
							strcpy(nome,"QuickSort.txt");
							salvarArquivo(nome);
								
						break;
						
				
							
						default:
							cout << "Opcao invalidade";
						break;
						 	
						
					}
					getch();
				
				}while(op2 != 0);
			break; 
			
			case 6:
				mostraDicionario();
			break;	
			
			
			default:
				cout << "Opcao invalida";
				
			break; 
			
		}
		getch();
	}while(op != 0);

}

int main(){
		
		lerArquivo();
		menuInicial();
		

	
	
	
	return 1;
}
