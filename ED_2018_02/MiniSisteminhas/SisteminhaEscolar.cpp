/* Prof.: Sergio Augusto C. Bezerra
 Programa MODULADO "LS_INS02.CPP" para exemplificar uma lista simplesmente encadeada
 para guardar a matricula e o nome dos alunos com duas notas de uma
 determinada disciplina, alem do calculo da media.
 Melhorado  
*/
#include <stdio.h>
#include <malloc.h>
#include <conio.h>
#include <ctype.h>
#include <iostream>
#include<windows.h> 

using namespace std;

void gotoxy(int x, int y){
     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){x-1,y-1});
}  
void clrscr(){
	system("cls");
}

/****************** VARIAVEIS GLOBAIS ******************/
 char professor[50],disciplina[50],turma[10];
 int opcao,opcao1,i;
 char resp;
 int linha,col, matTemp,matTemp1=1,nomTemp;
 FILE *file;
 
 struct Aluno {
 int matricula; /* numeros de 1 a no maximo 40 */
 char nome[30];
 float notas[3]; /* valores das notas */
 struct Aluno *pProx; /* ponteiro para o proximo aluno */
 };
 Aluno inicio, *pAux, *pAnt;
 /********************FUNCOES***********************************/
 void salvarTurma();
 void lerTurma();
 void criarTurma();
 void gerarRelatorio();
 void editar();
 void buscarAluno();
 void relatorioAluno();
 
/****************** FUNCAO CABECALHO ******************/


void cabecalho(){
 clrscr();
 gotoxy(3,5);
 cout << "PROGRAMA PARA GERENCIAR A MATRICULA, O NOME E AS NOTAS";
 gotoxy(3,7);
 cout << "DE UM ALUNO USANDO UMA LISTA SIMPLESMENTE ENCADEADA\n";
}
/****************** FUNCAO MENU ******************/
void menu(){

 col=15;
 gotoxy(col,10);
 cout << "*************** Menu ****************";
 gotoxy(col,11);
 cout << "* Exibir......[1] *";
 gotoxy(col,12);
 cout << "* Inserir.....[2] *";
 gotoxy(col,13);
 cout << "* Remover.....[3] *";
 gotoxy(col,14);
 cout << "* Relatorio...[4] *";	
 gotoxy(col,15);
 cout << "* Salvar......[5] *";
 gotoxy(col,16); 
 cout << "* Sair........[0] *";
 gotoxy(col,17);
 cout << "* Editar......[6] *";
 gotoxy(col,18);
 cout << "* Digite a opcao: *";
 gotoxy(col,19);
 cout << "*************************************";
 gotoxy(42,18);
 cin >> opcao;
}
/******************** FUNCAO DIARIO *******************/
void diario(){
 gotoxy(3,9);
 cout << "PREENCHER OS DADOS DO CABECALHO DO DIARIO";
 gotoxy(3,11);
 fflush(stdin);
 cout << "Professor:";
 gets(professor);
 gotoxy(3,13);
 cout << "Disciplina: ";
 gets(disciplina);
 gotoxy(3,15);
 cout << "Turma: ";
 gets(turma);
}
/********************* FUNCAO EXIBIR *******************/
void exibir(){
 			
 pAux = inicio.pProx; /* aponta para o inicio da lista */
 clrscr();
 gotoxy(1,5);
 cout << "******************************** DIARIO *********************************";
 gotoxy(1,7);
 cout << "Professor: " << professor;
 gotoxy(1,8);
 cout << "Disciplina: " << disciplina;
 gotoxy(1,9);
 cout << "Turma: " << turma;
 linha=11;
 cout << "\n---------------------------------------------------------------------------";
 gotoxy(1,linha);
 cout << "Matricula";
 gotoxy(15,linha);
 cout << "Nome";
 gotoxy(50,linha);
 cout << "Nota1";
 gotoxy(60,linha);
 cout << "Nota2";
 gotoxy(70,linha);
 cout << "Media";
 linha=13;
 cout << "\n---------------------------------------------------------------------------";
 while(pAux){
 gotoxy(1,linha);
 cout << pAux->matricula;
 gotoxy(15,linha);
 cout << pAux->nome;
 gotoxy(50,linha);
 cout << pAux->notas[0];
 gotoxy(60,linha);
 cout << pAux->notas[1];
 gotoxy(70,linha);
 cout << pAux->notas[2];
 
 pAux = pAux->pProx;
 linha++;
 }
 cout << "\n---------------------------------------------------------------------------";
 printf("\nPressione Enter para continuar!");
 getch();
}
/********************* FUNCAO INSERIR *******************/
void inserir(){
	
 pAux = &inicio; /* aponta para o inicio da lista */
 while(pAux->pProx != NULL)
 pAux = pAux->pProx;
 matTemp1=pAux->matricula;
 do{
 clrscr();
 cout << "************************* CADASTRO DE ALUNO *************************";
 pAux->pProx = new(Aluno);
 pAux = pAux->pProx;
  matTemp1++;
 gotoxy(1,2);
 cout << "* Matricula: *";
 gotoxy(1,3);
 cout << "* Nome do Aluno: *";
 gotoxy(1,4);
 cout << "* Nota1: *";
 gotoxy(1,5);
 cout << "* Nota2: *";
 cout << "\n*********************************************************************";
 gotoxy(20,2);
 pAux->matricula = matTemp1;
 cout << pAux->matricula;
 gotoxy(20,3);
 fflush(stdin);
 gets(pAux->nome);
 gotoxy(20,4);
 cin >> pAux->notas[0];
 gotoxy(20,5);
 cin >> pAux->notas[1];
 pAux->notas[2] = (pAux->notas[0] + pAux->notas[1])/2;
 pAux->pProx = NULL;

 cout << "\nContinuar inserindo dados? Sim[S] Nao[outra tecla]---->";
 resp = toupper(getch());
 }while (resp == 'S');
}

/********************* FUNCAO REMOVER *******************/
void remover(){
 resp = '0';
 clrscr();
 cout << "************************** REMOVER ALUNO ****************************";
 gotoxy(1,2);
 cout << "* Matricula: *";
 gotoxy(1,3);
 cout << "*********************************************************************";
 gotoxy(15,2);
 cin >> matTemp;
 pAux = &inicio;
 
 
 while(pAux->matricula!=matTemp && pAux->pProx!=NULL){
 pAnt=pAux;
 pAux = pAux->pProx;
 }
 
 if(pAux->matricula==matTemp){
 gotoxy(20,2);
 cout << "Remover " << pAux->nome << "? Sim[S] Nao[outra tecla]---->";
 resp = toupper(getch());
 if(resp=='S'){
 pAnt->pProx = pAux->pProx;
 pAux->pProx = NULL;
 pAnt = NULL;
 delete(pAux);
 }
 }
 
 else{
 gotoxy(20,2);
 cout << "Matricula inexistente";
 getch();
 pAnt = NULL;
 pAux = NULL;
 }
}
/****************** FUNCAO PRINCIPAL ******************/
main(){

criarTurma();

if(opcao1==1){

 inicio.pProx = NULL; /* lista vazia */
 cabecalho();
 diario();
 
do{

 do{
 cabecalho();
 menu();
 if((int)opcao<0 || (int)opcao>6){
 opcao= -1;
 gotoxy(50,15);
 cout << "Opcao Invalida!";
 }
 }while(opcao == -1);
 switch(opcao){
 case 0:
break;
 case 1:
exibir();
break;
 case 2:
inserir();
exibir();
break;
 case 3:
remover();
break;

 case 4:
gerarRelatorio(); 
 break;
 
 case 5:
salvarTurma(); 
 break;
 case 6:
 editar();	
 break;	
		
 default:
printf("\nOpcao invalida");
getch();
 }
}while (opcao != 0);

}

if(opcao1==2){
lerTurma();

do{

 do{
 cabecalho();
 menu();
 if((int)opcao<0 || (int)opcao>6){
 opcao= -1;
 gotoxy(50,15);
 cout << "Opcao Invalida!";
 }
 }while(opcao == -1);
 switch(opcao){
 case 0:
break;
 case 1:
exibir();
break;
 case 2:
inserir();
exibir();
break;
 case 3:
remover();
break;
 case 4:
 gerarRelatorio();
 break;
 case 5:
salvarTurma();
 break;	
 case 6:
  	editar();	
 break;		
 default:
printf("\nOpcao invalida");
getch();
 }
}while (opcao != 0);
}
}

void salvarTurma(){
	char nomeF[20];
	gotoxy(15,20);
	cout << "Nome do arquivo dessa turma:";
	cin >> nomeF;
	strcat(nomeF,".txt");
file = fopen(nomeF,"w");
		if(file==NULL){
			cout << "Erro na criacao do arquivo\n";
			system("pause");
		}
	fprintf(file,"%s\n",professor);	
	fprintf(file,"%s\n",disciplina);	
	fprintf(file,"%s\n",turma);	
	//inicio da lista
	pAux = inicio.pProx;
	//alunos
	while(pAux){
	fprintf(file,"%d\n",pAux->matricula);	
	fprintf(file,"%s\n",pAux->nome);
	fprintf(file,"%.2f %.2f %.2f\n",pAux->notas[0],pAux->notas[1],pAux->notas[2]);
	pAux = pAux->pProx;
	}
fclose(file);
		
}


void lerTurma(){
	char nomeF[20];
	int i; 
	gotoxy(15,18);
	cout << "Nome do arquivo dessa turma:";
	cin >> nomeF;
	strcat(nomeF,".txt");
file = fopen(nomeF,"r");
		if(file==NULL){
			cout << "Erro na criacao do arquivo\n";
			system("pause");
		}

	fgets(professor,sizeof(professor),file);
	for(i=0;i<51;i++){
		if(professor[i]=='\n'){
			professor[i]=' ';
		}
		professor[i]=professor[i];
	}	
	fscanf(file,"%s\n",&disciplina);	
	fscanf(file,"%s\n",&turma);	

	Aluno a;
	pAux = &inicio;
	

while(!feof(file)){
	pAux->pProx = new(Aluno);
 	pAux = pAux->pProx;
 	fscanf(file,"%d\n",&a.matricula);
 	fgets(a.nome,sizeof(a.nome),file);
 	fscanf(file,"%f %f %f\n",&a.notas[0],&a.notas[1],&a.notas[2]);
 	pAux->matricula = a.matricula;	
	pAux->notas[0] = a.notas[0];
	pAux->notas[1] = a.notas[1];
	pAux->notas[2] = a.notas[2];
	for(i=0;i<31;i++){
		if(a.nome[i]=='\n'){
			a.nome[i]=' ';
		}
		a.nome[i] = a.nome[i];
		pAux->nome[i] = a.nome[i];
	}
	pAux->pProx=NULL;
}
fclose(file);
}

void relatorioAluno(){
	char nomeF[20];
	cout << "\nNome relatorio desse aluno:";
	cin >> nomeF;
	strcat(nomeF,".txt");
file = fopen(nomeF,"w");
		if(file==NULL){
			cout << "Erro na criacao do arquivo\n";
			system("pause");
		}
		fprintf(file,"Professor: %s\nDisciplina: %s\nTurma: %s\n",professor,disciplina,turma);
		fprintf(file,"---------------------------------------------------------------------------\n");
 		
 		fprintf(file,"Matricula      Nome\t\t\t\tNota1\tNota2\tMedia\n");
 		fprintf(file,"---------------------------------------------------------------------------\n");
 		fprintf(file,"%d\t       %s\t\t\t%.2f\t%.2f\t%.2f",pAux->matricula,pAux->nome,pAux->notas[0],pAux->notas[1],pAux->notas[2]);	
 	
   	fprintf(file,"\n---------------------------------------------------------------------------");

	
fclose(file);

}
void relatorioTurma(){
	char nomeF[20];
	
	cout << "\nNome relatorio da turma:";
	cin >> nomeF;
	strcat(nomeF,".txt");
file = fopen(nomeF,"w");
		if(file==NULL){
			cout << "Erro na criacao do arquivo\n";
			system("pause");
		}
		fprintf(file,"Professor: %s\nDisciplina: %s\nTurma: %s\n",professor,disciplina,turma);
		fprintf(file,"---------------------------------------------------------------------------\n");
 		
 		fprintf(file,"Matricula      Nome\t\t\t\tNota1\tNota2\tMedia\n");
 		fprintf(file,"---------------------------------------------------------------------------");
 		pAux = inicio.pProx;
 		while(pAux){
			fprintf(file,"\n%d\t       %s\t\t\t%.2f\t%.2f\t%.2f    ",pAux->matricula,pAux->nome,pAux->notas[0],pAux->notas[1],pAux->notas[2]);	
 			pAux = pAux->pProx;
		} 	
   	fprintf(file,"\n---------------------------------------------------------------------------");

	
fclose(file);

}
void criarTurma(){
 col=15;
 gotoxy(col,10);
 cout << "*************** Menu ****************";
 gotoxy(col,11);
 cout << "* Criar uma nova turma.....[1] *";
 gotoxy(col,12);
 cout << "* Usar turma cadastrada......[2] *";
 gotoxy(col,13);
 cout << "* Remover uma turma.....[3] *";
 gotoxy(col,14);
 cout << "* Sair........[0] *";
 gotoxy(col,15);
 cout << "* Digite a opcao: *";
 gotoxy(col,16);
 cout << "*************************************";
 gotoxy(42,15);
 cin >> opcao1;
}	

void gerarRelatorio(){
 system("cls");
 cabecalho();
 int opcao2;
   col=15;
 gotoxy(col,10);
 cout << "*************** RELATORIO	 ****************";
 gotoxy(col,11);
 cout << "* Relatorio da turma.....[1] *";
 gotoxy(col,12);
 cout << "* Relatorio de um aluno ......[2] *";
 gotoxy(col,13);
 cout << "* Sair .....[3] *\n";
 gotoxy(col,14);
 cout << "* Digite a opcao: *";
 gotoxy(col,15);
 cout << "*************************************";
 gotoxy(42,14);
 cin >> opcao2;
 switch(opcao2){
 	case 1:
 		relatorioTurma();
 	break;
 	case 2:
 	    buscarAluno();
 	break;
 	case 3:
 	break;
 	
 
 
 }
 
}   
void editar(){

 resp = '0';
 clrscr();
 cout << "************************** EDITAR ALUNO ****************************";
 gotoxy(1,2);
 cout << "* Matricula: *";
 gotoxy(1,3);
 cout << "*********************************************************************";
 gotoxy(15,2);
 cin >> matTemp;
 pAux = &inicio;
 system("cls");
 
 
 while(pAux->matricula!=matTemp && pAux->pProx!=NULL){
 pAnt=pAux;
 pAux = pAux->pProx;
 }
 
 if(pAux->matricula==matTemp){
 Aluno a1;
 gotoxy(2,2);
 //gotoxy(1,2);
 cout << "* Matricula: *";
 
 gotoxy(1,3);
 cout << "* Nome do Aluno: *";
 gotoxy(1,4);
 cout << "* Nota1: *";
 gotoxy(1,5);
 cout << "* Nota2: *";
 //cout << "\n*********************************************************************";
 gotoxy(20,2);
 cout << pAux->matricula;
 fflush(stdin);
 gotoxy(20,3);
 gets(a1.nome);
 gotoxy(20,4);
 cin >> a1.notas[0];
 gotoxy(20,5);
 cin >> a1.notas[1];
 a1.notas[2] = (a1.notas[0] + a1.notas[1])/2;  
 cout << "Novos dados \n";
 cout << "Salvar no lugar de" << pAux->nome << "? Sim[S] Nao[outra tecla]---->";
 resp = toupper(getch());
 if(resp=='S'){
 	for(i=0;i<31;i++){
	 
	pAux->nome[i]=a1.nome[i];
	}
	pAux->notas[0]=a1.notas[0];	
	pAux->notas[1]=a1.notas[1];	
	pAux->notas[2]=a1.notas[2];	
 }
 }
 
 else{
 gotoxy(20,2);
 cout << "Matricula inexistente";
 getch();
 pAnt = NULL;
 pAux = NULL;
 }
}

void buscarAluno(){
 resp = '0';
 clrscr();
 cout << "************************** GERANDO RELATORIO DO ALUNO  ****************************";
 gotoxy(1,2);
 cout << "* Matricula: *";
 gotoxy(1,3);
 cout << "*********************************************************************";
 gotoxy(15,2);
 cin >> matTemp;
 pAux = &inicio;
 
 
 while(pAux->matricula!=matTemp && pAux->pProx!=NULL){
 pAnt=pAux;
 pAux = pAux->pProx;
 }
 
 if(pAux->matricula==matTemp){
 linha=5;
 cout << "\n---------------------------------------------------------------------------";
 gotoxy(1,linha);
 cout << "Matricula";
 gotoxy(15,linha);
 cout << "Nome";
 gotoxy(50,linha);
 cout << "Nota1";
 gotoxy(60,linha);
 cout << "Nota2";
 gotoxy(70,linha);
 cout << "Media";
 linha=6;
 //cout << "\n---------------------------------------------------------------------------";

 gotoxy(1,linha);
 cout << pAux->matricula;
 gotoxy(15,linha);
 cout << pAux->nome;
 gotoxy(50,linha);
 cout << pAux->notas[0];
 gotoxy(60,linha);
 cout << pAux->notas[1];
 gotoxy(70,linha);
 cout << pAux->notas[2];
  relatorioAluno();
 //pAux = pAux->pProx;
 linha++;

 cout << "\n---------------------------------------------------------------------------\n";
 
	system("pause");
 }
 
  	
else{
 gotoxy(20,2);
 cout << "Matricula inexistente";
 getch();
 pAnt = NULL;
 pAux = NULL;
 getchar();
 }
}




