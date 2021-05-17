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

bool DicionarioisEmpty(L *inicio){
		if(inicio == NULL){
				cout << "Dicionario vazio";
				return true;
		}
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
		
	if(auxL == NULL){
		
		return false;
		
	}
	
	if(auxL->ant == NULL && auxL->prox == NULL){
	
		free(inicioL);
		inicioL = NULL; 
		
		return true;
	}
	if(auxL->ant == NULL && auxL->prox != NULL){
		
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


void salvarPalavra(char *nome,char *nArq){
	FILE *file;
	file = fopen(nArq,"a");
	if(file == NULL){
		cout << "Erro na cricao ou leitura do arquivo";
				cout << " nao  foi";
		getch();
		return;
	}
	fprintf(file,"%s ",nome);
	fclose(file);
	cout << "foi";
getch();
	
}
void salvarArquivo(char *nome,char *caminho){
	FILE *file = NULL;
	L *auxL = inicioL;
	P *auxP;
	strcat(caminho,nome);
	
	file = fopen(caminho,"w");

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



bool lerArquivo(char *nome,char *caminho){
	FILE *file = NULL;
	strcat(caminho,nome);
	
	cout << caminho;
	file = fopen (strcat(caminho,".txt"),"r");
	if(file == NULL){
		cout << "\nErro na leitura do arquivo";
		getch();
		return false;
	} 
	char npalavra[40],nArquivo[200];;
	while(!feof(file)){
		fscanf(file,"%s",&npalavra);
		strlwr(npalavra);
		inserirLetra(npalavra,nome);
	}
	
	fclose(file);
	return true;
		
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
	cout << "Lista de Palavras\n";
	gotoxy(1,2);
	cout << "Palavra";
	gotoxy(30,2);
	cout << "Arquivo";

		
	int y=3;
	while(auxL){
		P *auxP =auxL->inicio;
	
		gotoxy(1,y++);
		for(int i=0;i<65;i++){
			printf("%c",22);
		}

		gotoxy(1,y++);
		printf("Letra %c Ocorrencias %d\n",toupper(auxL->letra),auxL->ocorrencia);
		//gotoxy(1,y);
//		cout << "Palavra";
//		gotoxy(30,y++);
//		cout << "Arquivo";
//		gotoxy(1,y++);
		gotoxy(1,y++);
		for(int i=0;i<65;i++){
			printf("%c",22);
		}
		
		while(auxP){
			gotoxy(1,y);
			cout << auxP->palavra;
			gotoxy(30,y++);
			cout << auxP->nArquivo;
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
	char caminho[40];
	bool verificacao;
	do{
		system("cls");
		cout << "Lista de Dicionario \n\n";
		cout << "1 - Inserir\n";
		cout << "2 - Editar\n";
		cout << "3 - Excluir\n";
		cout << "4 - Pesquisar\n";
		cout << "5 - Metodos de Ordenacao Letras\n";
		cout << "6 - Metodos de Odernacao Palavras\n";
		cout << "7 - Mostra Dicionario\n";
		cout << "8 - Ler Arquivos\n";
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
				strcat(narquivo,".txt");
				char caminho[40];
				strcpy(caminho,"Lista_de__Palavras/");
				strcat(caminho,narquivo);
				inserirLetra(npalavra,narquivo);
				salvarPalavra(npalavra,caminho);	
			
			break;
			
			
			case 2:
				if(inicioL == NULL){
					cout << "Dicionario vazio";
					break;
				}
				cout << "Editar palavra\n";
				cout << "**************************\n"; 
				cout << "Palavra:\n";
				cout << "**************************"; 
				gotoxy(10,3);
				cin >> npalavra;
				strlwr(npalavra);
				if(buscarPalavra(npalavra)){
					excluirPalavra(npalavra);
					cout << "\nNovos Dados";
					cout << "\n**************************"; 
					
					cout << "\nPalavra: ";
					cout << "\nArquivo: ";
					
					cout << "\n**************************"; 
					gotoxy(10,7);
					cin >> npalavra;
					gotoxy(10,8);
					cin >> narquivo; 
				
				
					strcpy(caminho,"Lista_de__Palavras/");
					strcat(caminho,narquivo);
					inserirLetra(npalavra,strcat(narquivo,".txt"));
					salvarPalavra(npalavra,caminho);
				}else{
					cout << "\nPalavra nao encotrada";
				} 	
				
						 
			break;	
			
			case 3:
				if(inicioL == NULL){
					cout << "Dicionario vazio";
					break;
				}
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
				if(inicioL == NULL){
					cout << "Dicionario vazio";
					break;
				}
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
							
							printf("Letra %c numero de palavras %d\n",toupper(auxL->letra),auxL->ocorrencia);
							int y =2;
							gotoxy(1,y);  
							cout << "Palavra";
							gotoxy(30,y);
							cout << "Arquivo\n"; 
							
							
							for(int i=0;i<55;i++){
									printf("%c",22);
							}
							cout << "\n";
						
							y = 4;
							while(auxP){
								gotoxy(1,y);  
								cout << auxP->palavra;
								gotoxy(30,y++);
								cout << auxP->nArquivo;
								auxP = auxP->prox; 	
						
							}
							cout << "\n";
							for(int i=0;i<55;i++){
									printf("%c",22);
							}
							
						}
						
						 
					break;	
					
						
					case 2:
						cout << "Buscando por Palavra\n";
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
				if(inicioL == NULL){
					cout << "Dicionario vazio";
					break;
				}
				char nome[40];
				do{
					system("cls");
					cout << "METODOS DE ORGANIZACAO\n";
					for(int i=0;i<25;i++){
						printf("%c",22);
					}

					cout << "\n1 - Metodo Burbblesort\n";
					cout << "2 - Metodo SelectSort\n";
					cout << "3 - Metodo InsertSort\n";
					
					cout << "4 - Metodo ShellSort\n";
					cout << "5 - Metodo MergeSort\n";
					cout << "6 - Metodo QuickSort\n";
				
					cout << "0 - Voltar\n";
					
					for(int i=0;i<25;i++){
						printf("%c",22);
					}
					cout << "\nOpcao >> ";
					cin >> op2; 
					char caminho[40];
					strcpy(caminho,"Palavras_organizadas/");
					
					for(int i=0;i<25;i++){
						printf("%c",22);
					}
					cout << "\n";
					//system("cls");
					switch(op2){
					
						case 0:
							cout << "VOLTANDO..";
						break;
						case 1:
							cout << "BurbbleSort.txt Criado...";
							bubbleSortLetras(inicioL);
							
							strcpy(nome,"BubbleSort.txt");
							
							salvarArquivo(nome,caminho);
						break;	
						case 2:
						
							cout << "SelectSort.txt Criado...";
							
							selectSortLetra(&inicioL);
							strcpy(nome,"SelectSort.txt");
							salvarArquivo(nome,caminho);	
							
						break;
						case 3:
							cout << "InsertSort.txt Criado...";
							insertSortLetras(&inicioL);
							strcpy(nome,"InsertSort.txt");
							salvarArquivo(nome,caminho);	
						break;	
						
						case 4:
							cout << "ShellSort.txt Criado...";
							iniciaMerge(&inicioL);
							strcpy(nome,"ShellSort.txt");
							salvarArquivo(nome,caminho);
						break;	
						case 5:
							cout << "MergeSort.txt Criado...";
							iniciaMerge(&inicioL);
							strcpy(nome,"MergeSort.txt");
							salvarArquivo(nome,caminho);
								
						break;
						break;	
						case 6:
							cout << "QuickSort.txt Criado...";
							quick(&inicioL);
							strcpy(nome,"QuickSort.txt");
							salvarArquivo(nome,caminho);
								
						break;
						
				
							
						default:
							cout << "Opcao invalidade";
						break;
						 	
						
					}
					getch();
				
				}while(op2 != 0);
			break;
			
			case 6:
				do{
				
				cout << "1 -BubbleSort\n";
				cout << "2 - SelectSort\n";
				cout << "0 - Voltar\n";  
				cout << "Opcao >> ";
				cin >> op2;  
				switch(op){
					case 1:
						cout << "BubbleSort Palavras";
					break;	
					case 0:
						cout << "Voltando...\n";
					break; 
				}
				}while(op2 !=0);
			break; 
			
			case 7:
				if(inicioL == NULL){
					cout << "Dicionario vazio";
					break;
				}
				mostraDicionario();
			break;	
			
				
			case 8:
				char nomeArq[40];
				cout << "Lendo um arquivo\n";
				cout << "**************************************\n"; 
				cout << "Digite o nome do arquivo:\n";
				cout << "**************************************\n"; 
				gotoxy(27,3);
				cin >> nomeArq;
				//char caminho[40];
				strcpy(caminho,"Lista_de__Palavras/");
				if(lerArquivo(nomeArq,caminho)){
					cout << "\nArquivo encontrado, palavras inseridas no dicionario";
				}
			break;
			
			default:
				cout << "Opcao invalida";
				
			break; 
			
		}
		getch();
	}while(op != 0);

}

int main(){
		
//		char caminho[40],nome[40];
//		strcpy(caminho,"Lista_de__Palavras/");
//		strcpy(nome,"lista1"); 
//		lerArquivo(nome,caminho);
//		
		menuInicial();
		

	
	
	
	return 1;
}
