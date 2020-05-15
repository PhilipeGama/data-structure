#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include <iostream>
#include<windows.h> 
#define max 25

void gotoxy(int x, int y){
     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){x-1,y-1});
}  
void clrscr(){
	system("cls");
}
using namespace std;

typedef struct{
	int dia;
	int mes;
	int ano;
}data;


typedef struct cliente {
	char nome[40];
	data nascimento;
	int num;
	bool especial;
	int poltrona;
	int fila; 
	cliente *pProx;
}cliente;


cliente inicio,*pAux,*pAnt,*pFim;
 

/**********VARIAVEIS GLOBAIS**************/
char resp,pTemp,e;
int i,j,numC,tempNum,opcao,idCliente=1;
int aviao[15][7],fila,pot;
int check;
FILE *file;
cliente c1;
/*************FUNCOES*****************/
void lerC();
void mostrarC();
void telaC();
void cadastrarC();
int telaInicial();

void exibirClientes();
void telaAviao();
void converteP();
void convertePv();
void ocuparPoltronas(); 
void verificacao();
void salvarLugar();
void removerCliente();
void editarCliente();


int main(){

inicio.pProx = NULL; /* lista vazia */

lerC();


do{
ocuparPoltronas();

	do{
	 system("cls");	
	 opcao = telaInicial();
	 if((int)opcao<0 || (int)opcao>7){
	 opcao= -1;
	 cout << "\t\t\tOpcao Invalida!\n";
	 system("pause");
	
	 }
	}while(opcao == -1);


	system("cls"); 
	
	switch(opcao){
		
	case 1:
		
		telaC();
		cadastrarC();
	break;
	
	case 2:
		
		telaAviao();
		getch();
	
	break;
	
	case 3:
		exibirClientes();
	break;
	
	case 4:
		editarCliente();
	break;
	 
	case 5:
		removerCliente();
	break;
	
	case 6:
	  printf("Saindo...");
	break;
			
	default:
	printf("\nOpcao invalida");
	getch();
	break;
	
	}


}while (opcao != 6);


return 1;
}


void telaC(){
	pAux = &inicio;
	
	while(pAux->pProx)
 	pAux = pAux->pProx;
 	
 	idCliente = pAux->num;
	 
	 
	 pAux->pProx = new(cliente);
 	 pAux = pAux->pProx;
 	 idCliente++;
	   	fflush(stdin);
		system("cls");
		gotoxy(4,2);
		printf("CADASTRO DE CLIENTE\n");
		gotoxy(4,4);
		cout << "Nome:";
		gotoxy(4,6);
		cout << "Nascimento:  /  /  ";
		gotoxy(4,8);
		printf("ID cliente:");
		gotoxy(4,10);
		cout << "Cliente especial [S/N] > ";  
		gotoxy(25,20);
		printf("Nascimento: Dia/Mes/Ano ");
		
		gotoxy(10,4);		
		gets(pAux->nome);
		fflush(stdin);
		gotoxy(15,6);
		cin >> pAux->nascimento.dia;
		gotoxy(18,6);
		cin >> pAux->nascimento.mes;
		gotoxy(21,6);
		cin >> pAux->nascimento.ano; 
	
	
		pAux->num=idCliente;
		
		gotoxy(16,8);
		
		printf("%d",pAux->num);
		gotoxy(29,10);
		cin >> e;
		fflush(stdin);
		e = toupper(e);
		if(e=='S'){
			pAux->especial = 1;
		}
		else{
			pAux->especial = 0;
		}
		
	system("cls");
	salvarLugar();
pAux->pProx = NULL;
}



void cadastrarC(){

file = fopen("CadastroClientes.txt","w");
	if(file==NULL){
		printf("Erro no cadastramento do cliente\n");
		system("pause");
		exit(1);
	}
	pAux = inicio.pProx; /* aponta para o inicio da lista */
	while(pAux){
	fprintf(file,"%s\n%d %d %d\n",pAux->nome,pAux->nascimento.dia,pAux->nascimento.mes,pAux->nascimento.ano);
	fprintf(file,"%d\n%d\n",pAux->especial,pAux->num);
	fprintf(file,"%d %d\n",pAux->poltrona,pAux->fila);
	pAux= pAux->pProx;
	}
	
fclose(file);
}

void lerC(){
	char *result;

	file = fopen("CadastroClientes.txt","r");
	if(file==NULL){
		printf("Sem clientes cadastrados\n");
		getch();
		return;
	}
	
	cliente c;
	pAux = &inicio;
		
while(!feof(file)){	
	pAux->pProx = new(cliente);
 	pAux = pAux->pProx;
 	
	fgets(c.nome,sizeof(c.nome),file);
	fscanf(file,"%d %d %d\n",&c.nascimento.dia,&c.nascimento.mes,&c.nascimento.ano);
	fscanf(file,"%d\n%d\n",&c.especial,&c.num);
	fscanf(file,"%d %d\n",&c.poltrona,&c.fila);
	
	for(i=0;i<41;i++){
		if(c.nome[i] == '\n'){
			c.nome[i] = ' ';
		}
		pAux->nome[i] = c.nome[i];
	}
	
	pAux->nascimento.dia = c.nascimento.dia;
	pAux->nascimento.mes = c.nascimento.mes;
	pAux->nascimento.ano = c.nascimento.ano;
	pAux->num = c.num;
	pAux->especial = c.especial;
	pAux->poltrona =c.poltrona; 
	pAux->fila = c.fila;
	
	pAux->pProx = NULL;
}
fclose(file);
}

int telaInicial(){
	int r;
	printf("\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",3017,3021,3021,3021,3021,3021,3021,3021,3021,3021,3021,3021,3021,3021,3021,3021,3021,3021,3021,3021,3021,3003);

	printf("\t\t\t%c VENDA DE PASSAGENS %c\n",3002,3002);
	printf("\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",3016,3021,3021,3021,3021,3021,3021,3021,3021,3021,3021,3021,3021,3021,3021,3021,3021,3021,3021,3021,3021,3004);		
	printf("\n\n\t\t  1  %c   CADASTRAMENTO DE CLIENTE\n\n",16);
	printf("\t\t  2  %c   VERIFICAR POLTRONAS\n\n",16);
	printf("\t\t  3  %c   LISTA DE PASSAGEIROS\n\n",16);
	printf("\t\t  4  %c   EDITAR\n\n",16);
	printf("\t\t  5  %c   EXCLUIR\n\n",16);
	printf("\t\t  6  %c   SAIR\n\n",16);
	printf("\n\t\t\t\t\t   OPCAO >  ");
	scanf("%d",&r);
	return r;
	
}

void exibirClientes(){
 int linha;			
 pAux = inicio.pProx; /* aponta para o inicio da lista */
 
 clrscr();
 linha=1;
 cout << "\n---------------------------------------------------------------------------";
 gotoxy(1,linha);
 cout << "Numero";
 gotoxy(15,linha);
 cout << "Nome";
 gotoxy(42,linha);
 cout << "Idade";
 gotoxy(55,linha);
 cout << "Poltrona";
 gotoxy(65,linha);
 cout << "Especial";
 linha=3;
 cout << "\n---------------------------------------------------------------------------";
 while(pAux){

 gotoxy(1,linha);
 cout << pAux->num;
 gotoxy(15,linha);
 cout << pAux->nome;
 gotoxy(42,linha);
 printf("%d/%d/%d",pAux->nascimento.dia,pAux->nascimento.mes,pAux->nascimento.ano);
 convertePv();
 gotoxy(57,linha);
 
 cout << pTemp;
 gotoxy(59,linha);
 cout << pAux->fila;
  gotoxy(68,linha);
 cout << pAux->especial;
  pAux = pAux->pProx;
 linha++;
 }
 cout << "\n---------------------------------------------------------------------------\n";
 system("pause");
}	


void ocuparPoltronas(){
if(inicio.pProx == NULL){
	return;
}
int linha,col,numero;

	for (i=1;i<16;i++){
		for(j=0;j<7;j++){
			aviao[i][j] = 0;
			}
		}
		pAux = inicio.pProx;
			while(pAux){
				linha = pAux->fila;
				col = pAux->poltrona;
				numero = pAux->num;
				aviao[linha][col]=numero;
				pAux = pAux->pProx; 
		}	
}

void salvarPoltronas(){
int i,j,pos;
file = fopen("ocupado.txt","w");
	if(file==NULL){
		printf("Erro no preenchimento das posicoes ocupadas\n");
		system("pause");
		exit(1);	
	}
	for (i=0;i<15;i++){
		fprintf(file,"\n");
		for(j=0;j<7;j++){
			
			fprintf(file,"%d ",aviao[i][j]);
		}
	}
fclose(file);
	
}


void telaAviao(){
	int i,j,lugar=0;
	printf("\tA  B  C	        D  E  F\n  ");
	
	for (i=1;i<16;i++){
		printf("\n");

		printf("%d\t",lugar=lugar+1);
		for(j=0;j<7;j++){
			if(j == 3){
				printf("|   |  ");
			}
			else{
				if(aviao[i][j] == 0){
				printf("%d  ",aviao[i][j]);
				}
				else {
					printf("X  ");
				}
			}
		}
	}
}

void converteP(){
	pTemp = toupper(pTemp);
 	if(pTemp == 'A'){pot=0;}
	if(pTemp == 'B'){pot=1;}
	if(pTemp == 'C'){pot=2;}
	if(pTemp == 'D'){pot=4;}
	if(pTemp == 'E'){pot=5;}
	if(pTemp == 'F'){pot=6;}
}
void convertePv(){
	//pTemp = toupper(pTemp);
 	if(pAux->poltrona == 0){pTemp = 'A';}
 	if(pAux->poltrona == 1){pTemp = 'B';}
 	if(pAux->poltrona == 2){pTemp = 'C';}
 	if(pAux->poltrona == 4){pTemp = 'D';}
 	if(pAux->poltrona == 5){pTemp = 'E';}
 	if(pAux->poltrona == 6){pTemp = 'F';}
}

void verificacao(){


if(aviao[fila][pot] != 0){
	gotoxy(37,9);
	printf("Poltrona Ocupada");
	check = 0;
}

else if(pAux->especial==0 && (fila==1 || fila==2)){
	gotoxy(37,9);
	printf("Lugar reservado  para clinetes preferencias");
	check = 0;
}
else if(pAux->nascimento.ano>2000 && fila==7 ){
	gotoxy(37,9);
	printf("Lugar reservado para maiores de 18 anos");
	check = 0;
}
	
else{
	gotoxy(37,9);
	printf("Lugar reservado com sucesso");
	aviao[pot][fila] = pAux->num;
	check = 1;
}
getch();
}

	
void salvarLugar(){

do{
	system("cls");
	telaAviao();
	fflush(stdin);
	gotoxy(37,3);
	cout << "Poltronas = {A,B,C,D,E,F}";
	gotoxy(37,4);
	cout << "Fila = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15}";
	gotoxy(37,7);
	cout << "Poltrona e Fila : ";
	cin >> pTemp;
	cin >>fila;
converteP();
verificacao();

}while(check != 1);

aviao[fila][pot] = pAux->num;
pAux->poltrona = pot;
pAux->fila = fila;

}


void removerCliente(){
 int numTemp; 
 clrscr();
 cout << "************************** REMOVER CLIENTE ****************************";
 gotoxy(1,2);
 cout << "* Numero cliente: *";
 gotoxy(1,3);
 cout << "*********************************************************************";
 gotoxy(22,2);
 cin >> numTemp;
 pAux = &inicio;
 
 
 while(pAux->num!=numTemp && pAux->pProx!=NULL){
 pAnt=pAux;
 pAux = pAux->pProx;
 }
 
 if(pAux->num==numTemp){
 gotoxy(20,2);
 cout << "Remover " << pAux->nome << " ? Sim[S] Nao[outra tecla]---->";
 resp = toupper(getch());
 if(resp=='S'){
 pAnt->pProx = pAux->pProx;
 pAux->pProx = NULL;
 pAnt = NULL;
 free(pAux);
 }
 }
 
 else{
 gotoxy(20,2);
 cout << "Numedo do cliente inexistente";
 getch();
 pAnt = NULL;
 pAux = NULL;
 }
}

void editarCliente(){
 int numTemp; 
 clrscr();
 cout << "************************** EDITAR CLIENTE ****************************";
 gotoxy(1,2);
 cout << "* Numero cliente: *";
 gotoxy(1,3);
 cout << "*********************************************************************";
 gotoxy(22,2);
 cin >> numTemp;
 pAux = &inicio;
 
 
 
 while(pAux->num!=numTemp && pAux->pProx!=NULL){
 pAnt=pAux;
 pAux = pAux->pProx;
 }
 
 cliente editC;
 if(pAux->num==numTemp){
 gotoxy(30,2);
 cout << "Nome: " << pAux->nome;
 gotoxy(30,5);
 cout << "Editando";
 gotoxy(21,7);
 cout << "Nome do cliente: ";
 cin >>editC.nome;
 fflush(stdin);
 gotoxy(21,8);
 cout << "Cliente especial [S/N]:";
 cin >> e;
	
	e = toupper(e);
	if(e=='S'){
		editC.especial = 1;
	}
	else{
		editC.especial = 0;
	}
 salvarLugar();	  

 for(i=0;i<40;i++){
 	 pAux->nome[i] = editC.nome[i];
 }
 pAux->especial = editC.especial;
 
 }
 
 else{
 gotoxy(20,2);
 cout << "Numedo do cliente inexistente";
 getch();
 pAnt = NULL;
 pAux = NULL;
 }
}





