#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <conio.h>
#include <windows.h>


using namespace std;

void gotoxy(int x, int y){
     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){x-1,y-1});
}  


typedef struct Venda{
	int nVenda;
	float valor;
	struct Venda *prox;
}V;

V *percorreV;

typedef struct Funcionario{
	int matricula;
	char nome[50];
	float valorTotal;
	struct Venda *venda_inicio;
	struct Venda *venda_fim;
	struct Funcionario *dir;
	struct Funcionario *esq; 
}F;

F *auxF=NULL,*percorreF= NULL,*inicioF = NULL;

int lin;

//Funções Funcionarios;

F* alocFuncionario(){
	F *alocF;
	alocF = (F*) malloc (sizeof(F));
	alocF ->dir = NULL;
	alocF ->esq = NULL;
	alocF ->venda_inicio = NULL;
	alocF ->venda_fim = NULL;
	alocF ->valorTotal = 0;
	return alocF; 
}

 
void inserirFuncionario(F *no){
	if(inicioF == NULL){
		
		inicioF = no;
		percorreF = inicioF;
		
		
	}else{
		if(no->matricula < percorreF->matricula){
			if(percorreF->esq != NULL){
			
				percorreF = percorreF->esq;
				inserirFuncionario(no);
				
			}else{
				percorreF->esq = no;	
					
			}
			
		}
	else{
		if(percorreF->dir != NULL){
			percorreF = percorreF->dir;
			inserirFuncionario(no);		
		}else{
			percorreF->dir = no;
		}
	}	
	
	
	}
	
}



void cadastrarFuncionario(){
	char tempResp;
	do{
	system("cls");
	auxF = alocFuncionario();
	
	cout << "Cadastro de Funcionario\n";
	cout << "**********************************\n";
	cout << "Matricula:\n";
	cout << "Nome:\n";
	cout << "**********************************\n";
	gotoxy(12,3);
	cin >> auxF->matricula;
	fflush(stdin);
	gotoxy(7,4);
	gets(auxF->nome);
	inserirFuncionario(auxF);
	
	cout << "\nCadastrar outro funcionario[s]:";
	tempResp = toupper(getch());
	}while(tempResp == 'S');

	
	
}

int menuBuscar(){
	int matricula;
	cout << "Buscar de Funcionario\n";
	cout << "*****************************************\n";
	cout << "Matricula:\n";
	cout << "*****************************************\n"; 
	gotoxy(12,3);
	cin >> matricula;
	system("cls");
	return matricula;
} 

F* buscarFuncionario(F *auxF,int matricula){
	auxF = inicioF;
	while(auxF){
		if(matricula == auxF->matricula){
			return auxF;	
		}
		if(matricula < auxF->matricula){
			auxF = auxF->esq;	
		}else{
			auxF = auxF->dir;	
		}
	}
	return NULL;
}


void editarFuncionario(){
	int matricula = menuBuscar();
	auxF = buscarFuncionario(inicioF,matricula);
	
	if(auxF == NULL){
		cout << "Funcionario nao encontrado";
		getch();
		return;
	}
	cout << "Editar -> "<<auxF->nome<<"\n";

	cout << "**********************************\n";
	cout << "Matricula: " <<auxF->matricula<<"\n";
	cout << "Nome:\n";
	cout << "**********************************\n";
	fflush(stdin);
	gotoxy(7,4);
	gets(auxF->nome);
	system("cls");
	int op;
	cout << "Listar de vendas -> "<<auxF->nome << "\n";
	cout << "**********************************\n";
	cout << "1 - Editar\n2 - Limpar\n0 - Voltar pro Menu\nOpcao ->\n";
	cout << "**********************************\n";
	gotoxy(10,6);
	cin >> op;
	
	switch(op){
		case 1:
			gotoxy(1,8);
			cout << "Nome";
			gotoxy(1,9);
			cout << auxF->nome;
					
		break;
		case 2:
			while(auxF->venda_inicio){
				V *libera = auxF->venda_inicio;
				auxF->venda_inicio = auxF->venda_inicio->prox;
				free(libera);
				libera = NULL;	
			}
			
		break;	
	}
	getch();
	percorreV = auxF->venda_inicio;

} 

void listarPreFixado(F *no){
	gotoxy(1,3);
	cout << "Matricula";
	gotoxy(15,3);
	cout << "Nome";
	gotoxy(40,3);
	cout << "Media de Venda";
	
	if(no != NULL){
		gotoxy(1,lin);
		cout << no->matricula;
		gotoxy(15,lin);
		printf("%s",no->nome);
		if(no->venda_inicio == NULL){
			gotoxy(40,lin);
			cout << "0.00";
		}else{
			gotoxy(40,lin);
			printf("%.2f",no->valorTotal/no->venda_fim->nVenda);
		}
		lin++;
		listarPreFixado(no->esq);
		listarPreFixado(no->dir);
	}
	
}

void inserirVenda(F *auxF,float valor){
	
	V *no;
	no = (Venda*) malloc (sizeof(Venda));
	no->prox = NULL;
	
	no->valor = valor;
	auxF->valorTotal= auxF->valorTotal + valor;
	
	if(auxF->venda_inicio == NULL){
		auxF->venda_inicio = no;
		auxF->venda_inicio->nVenda = 1;
		auxF->venda_fim = no; 
	}else{
		no->nVenda = auxF->venda_fim->nVenda + 1;
		auxF->venda_fim->prox = no;
		auxF->venda_fim = no ; 
	}
	
}

void cadastrarVenda(){
	int matricula;
	matricula = menuBuscar();
	auxF = buscarFuncionario(inicioF,matricula);
	if(auxF == NULL){
		cout << "Funcionario nao encontrado";
		getch();
		return;
	}
	float valor;
	char tempResp;
	 
	do{
		system("cls");
		cout << "Funcionario -> " << auxF->nome << "\n"; 
		cout << "*************************************\n";
		cout << "Valor da venda:\n";
		
		cout << "*************************************";
		gotoxy(17,3);
		cin >> valor;
		inserirVenda(auxF,valor);
		cout << "\nCadastrar outra venda [s]:";
		tempResp = toupper(getch());
	}while(tempResp == 'S');
}

void listaVendas(){
	int matricula = menuBuscar();
	auxF = buscarFuncionario(inicioF,matricula);
	
	if(auxF==NULL){
		cout << "Funcionario nao encontrado";
		getch();
		return;
	}
	gotoxy(3,3);
	cout << "Nome";
	gotoxy(3,4);
	cout << auxF->nome;
	gotoxy(25,3);
	printf("Vendas");
	percorreV = auxF->venda_inicio;
	while(percorreV != NULL){
		gotoxy(25,lin);
		//cout << percorreV->valor; 
		printf("%.2f",percorreV->valor);
		percorreV = percorreV->prox;
		lin++;
	}
} 

F* removeAtual(F *atual){

	
	if(atual->esq == NULL){
		F *no1 = atual->dir;
		free(atual);
		return no1;
	}
	if(atual->dir == NULL){
		F *no1 = atual->esq;
		free(atual);
		return no1;
	}
	F *no1,*no2;
	
	no1 = atual->esq;
	no2 = atual->dir;
	no2->esq = no1;
	free(atual);
	return no2;
}

F *removeRaiz(F *atual){
	
	if(atual->esq== NULL && atual->dir == NULL){
		F *no1 = NULL;
		free(atual);
		atual = NULL;
		return no1;
	}
	
	if(atual->esq == NULL){
		F *no1 = atual->dir;
		
		while(no1->esq){
			no1 = no1->esq;
		}
		free(atual);
		return no1;
	}
	if(atual->dir == NULL){
		F *no1 = atual->esq;
		while(no1->dir){
			no1 = no1->dir;
		}
		free(atual);
		return no1;
	}
	F *no1,*no2;
	
	no1 = atual->esq;
	no2 = atual->dir;
	no2->esq = no1;
	free(atual);
	return no2;
	
}

bool removerF(F **raiz,int matricula){
	if(raiz == NULL)
	return 0;
	
	F *ant = NULL;
	F *atual = *raiz;
	
	while(atual != NULL){
		if(atual->matricula == matricula){
			if(atual == *raiz){
				*raiz = removeRaiz(atual);
			}else{
				if(atual->esq == NULL && atual->dir == NULL){
					if(atual->matricula < ant->matricula){
					
						cout << "....\nsasas";
						ant->esq = NULL;
						}
					else
						ant->dir = NULL; 	
				}else{
				
				
				F *aux = removeAtual(atual);
		
					
				if(aux->matricula < ant->matricula)
					ant->esq = aux;
				else
					ant->dir = aux;
				
				}
			
			
			}
			return 1;
		}
	ant = atual;
	
	if(atual->matricula > matricula  )
			atual = atual->esq;
	else
			atual = atual->dir;  		 
		
	}
}
		
		

void escreverArquivo(FILE *file,F *no){
	if(no != NULL){
		fprintf(file,"%d\n",no->matricula);
		fprintf(file,"%s\n",no->nome);
		fprintf(file,"%f\n",no->valorTotal);
		V *tempV = no->venda_inicio;
		while(tempV){
			fprintf(file,"%d\n",tempV->nVenda);
			fprintf(file,"%f\n",tempV->valor);
			tempV = tempV->prox;
		}
		
		escreverArquivo(file,no->esq);
		escreverArquivo(file,no->dir);
	
	}
} 



void criaArquivo(F *no){
FILE *file; 
file  = fopen("ListaDeVendendores.txt","w");
	if(file == NULL){
		cout << "Erro na criação do arquivo";
		return;
	}		
	escreverArquivo(file,no);

fclose(file);

}

void lerArquivos(F *no){
	FILE *file;
file = fopen("ListaDeVendedores.txt","w");
	if(file == NULL){
		cout << "Erro na leitura do arquivo";
		return;
	}
	F tempF;
	tempF.valorTotal = 0; 
	while(!feof(file)){
		fscanf(file,"%d\n",&tempF.matricula); 
		fscanf(file,"%s\n",&tempF.nome);
		fscanf(file,"%f\n",&tempF.valorTotal);
		
		float tempValorTotal = 0;
		V vendas;
		
		while(tempF.valorTotal < tempValorTotal){
			fscanf(file,"%d\n",&vendas.nVenda);
			fscanf(file,"%f\n",&vendas.valor);
			tempValorTotal = vendas.valor;
		}
	}
}


void  menu(){
	int op; 
	do{
	do{
	system("cls");
	cout << "\tLojinha\n\n";
	cout << "1 - Cadastrar novo vendendo\n";
	cout << "2 - Cadastrar venda\n";
	cout << "3 - Lista de vendas\n";
	cout << "4 - Listar de vendedores\n";
	cout << "5 - Editar vendedor\n";
	cout << "6 - Remover vendendor\n";
	cout << "7 - Sair\n";
	cout << "Opcao > ";
	cin >> op;
	if(op  == 7){
		cout << "Finalizando...";
	}
	if(op > 7){
		cout << "Opcao invalida\n";
	}
	}while(op >7);
	
	system("cls");
	
	switch(op){
	
	case 1:
		cadastrarFuncionario();
	break;
	
	
	case 2:
		cadastrarVenda();
		getch();
	break;
	
	case 3:
		lin=4;
		listaVendas();
		getch();
	break;
	case 4:	
		lin=4;
		listarPreFixado(inicioF);
		getch();
	break;
	case 5:
		editarFuncionario();
	break;
	
	case 6:
		int tempMat;
		cout << "Matricula: ";
		cin >> tempMat;  
		removerF(&inicioF,tempMat);
	break;
	
	case 7:
		criaArquivo(inicioF);
		exit(1);
	break;
	
	}

	}while(op != 7);

}


int main(){

menu();


}
