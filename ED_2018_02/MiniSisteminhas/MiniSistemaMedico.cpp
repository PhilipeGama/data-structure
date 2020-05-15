#include <stdio.h>
#include <malloc.h>
#include <conio.h>
#include <ctype.h>
#include <iostream>
#include<windows.h> 
#include <time.h>
#include<unistd.h> 


using namespace std;

void gotoxy(int x, int y){
     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){x-1,y-1});
}  

/*************Estruturas*****************/	
typedef struct Contato{
char fone[12];
char email[30]; 
}Contato;

typedef struct Nascimento{
int dia;
int mes;
int ano;
}Nascimento;

typedef struct F{
struct F *anterior; 
int matricula;
char cpf[11];
char senha[40];
char nome[40];
char especialidade[40];
Nascimento nascimento;
Contato contanto;
struct F *proximo;
}F; 

F *inicioF=NULL,*fimF=NULL,*auxF = NULL;

typedef struct P{
struct P *anterior;
int codigo;
char nome[40];
Nascimento nascimento;
int idade;
float peso; 
char sangue[5]; 
int matF;
struct P *proximo;
}P;

P *inicioP=NULL,*fimP=NULL,*auxP=NULL;


typedef struct C{
	struct C *anterior;
	int codigoC;
	int codigoP;
	int codigoF;
	Nascimento dataC;
	int hora;
	int min;  
	char descricao[60];
	struct C *proximo;
}C;

C *inicioC=NULL,*fimC=NULL,*auxC=NULL; 

typedef struct Login{
	int matricula;
	char nome[40];
	char senha[40];
	bool admin; 
}Login;

Login usuario;

/*************Variaveis Globais*****************/	
int matF=0,codC=0,codP=0,i,op,maTemp;


FILE *file;
/*************Funcoes*****************/
// Funcoes Funcionarios
void lerF();
void salvarF();
void inserirF();
void listarF();
void editarF();
void removerF();
int gerarCodFuncionario();
bool validarCodigoF(int x);
// Funcoes Pacientes
void lerP();
void salvarP();
void inserirP();
void listarP();
//void editarP();
int gerarCodPaciente();
void removerP();
bool validarCodigoP(int x);
// Funcoes Consulta
void inserirC();
void listarC();
void editarC();
void removerC();

void pegarHora(struct tm h);

void menuPaciente();
void menuFuncionario();
void menuInicial();
void listarVazia();
void telaLogin();
void lerArquivos();

int buscarF();
int buscarPaciente();
//Relatorios
void menuRelatorio();
void rlistagemProfissional();
void rlistagemProfissionalF();
void ratendimentoGeral();
void ratendimentoGeralF();
void rAniversariantes();
void rAniversariantesF(struct tm tm);
void mostrarUsuario();
int main(){
	
lerArquivos();
telaLogin();
menuInicial();
	
return 1;
}

/************Funcao Funcionario***************/

void inserirF(){
 		
  int x,y;
	
  int tempMat;
  F *no; 
  no = (struct F*) malloc (sizeof(struct F)); 
  no->proximo = NULL; 

  

  
  gotoxy(11,3);
 
  
  gotoxy(1,1);
  cout << "CADASTRANDO NOVO FUNCIONARIO\n";
  cout << "************************************";
  gotoxy(1,3);
  
  if(inicioF == NULL){
  	 tempMat = 20180001;		
  }else{
  	tempMat = fimF->matricula;
  	tempMat++;
  
  } 
  
  no->matricula = tempMat;
  
  cout << "Matricula " << no->matricula;
  gotoxy(1,4);
  fflush(stdin);
  cout << "Nome:";
  gotoxy(1,5);
  cout <<"Senha:";
  gotoxy(1,6);
  cout << "Cpf:";
  gotoxy(1,7);
  cout << "Nascimento:  /  /";
  gotoxy(1,8);
  cout << "Especialidade:";
  gotoxy(1,9);	
  cout << "Email:";  
  gotoxy(1,10);
  cout << "Telefone:";
  fflush(stdin);
  gotoxy(6,4);
  gets(no->nome);
  gotoxy(7,5);
  cin >> no->senha;
  gotoxy(5,6);
  cin >> no->cpf;  
  gotoxy(12,7);	
  cin >> no->nascimento.dia;
  gotoxy(15,7);	
  cin >> no->nascimento.mes;
  gotoxy(18,7);	
  cin >> no->nascimento.ano;
  gotoxy(15,8);
  fflush(stdin);
  gets(no->especialidade);
  gotoxy(7,9);
  cin >> no->contanto.email;
  gotoxy(10,10);
  cin >> no->contanto.fone;
  
 
  
  getch(); 

  if(inicioF==NULL){
  	no->anterior = NULL;
    inicioF = no;
  	fimF = no ;
   }else{
  	no->anterior = fimF;
	fimF->proximo = no;
	fimF= no;     
  }

}


void removerF(){


 	if(inicioF==NULL){
 		cout << "Listar vazia ";
 		sleep(1);
 		return;
	}
	int tempMat;
	cout << "EXCLUIR FUNCIONARIO\n";	
	cout << "****************************************\n";
	cout << "Matricula do funcionario:";
	cout << "\n****************************************";
	gotoxy(27,3);
	cin >> tempMat;
	
	if(inicioF->matricula==tempMat){
		if(inicioF==fimF){
			free(inicioF);
			inicioF = NULL;
			fimF = NULL; 
			return;
		}else{
			F *aux = inicioF->proximo;
			free(inicioF);
			inicioF = aux;
			inicioF->anterior = NULL;
			return;		
		}
	}	
	
	F *no = inicioF;
	
	while(no){
		if(no->matricula ==tempMat){
			if(no == fimF){
				fimF = fimF->anterior;
				fimF->proximo = NULL;
				free(no);
				no = NULL;  
				return; 
			}else{
				F *aux = no->anterior;
				aux->proximo = no->proximo;
				free(no);
				
				
				no = NULL;
				return;
			}
			
		}
		no = no->proximo;
		
	}
	cout << "Matricula Funcionario inexistente";
			no = NULL; 
}
 
void salvarF(){
file = fopen("funcionarios.txt","w");
 	if(file==NULL){
 		cout << "Erro escrita do arquivo funcionario ";
 		return; 
 	}
 	
 	F *no = inicioF; 
 	
 	while(no){
	
 	fprintf(file,"%d\n",no->matricula);
 	fprintf(file,"%s\n",no->cpf);
 	fprintf(file,"%s\n",no->nome);
 	fprintf(file,"%s\n",no->senha);
 	fprintf(file,"%s\n",no->especialidade);
 	fprintf(file,"%d %d %d\n",no->nascimento.dia,no->nascimento.mes,no->nascimento.ano);
 	fprintf(file,"%s\n%s\n",no->contanto.fone,no->contanto.email);
 	no = no->proximo;
 	
 	
 	}
fclose(file);	
}

void lerF(){
 
file = fopen("funcionarios.txt","r");
	if(file==NULL){
	
		F *auxF= (F*) malloc(sizeof(F));;
		
		strcpy(auxF->nome,"Admin");
		auxF->matricula = 1;
		strcpy(auxF->senha,"123");
		strcpy(auxF->especialidade,"Agente de Saude");
		
		auxF->anterior = NULL;	
		inicioF = auxF;
		fimF = auxF;    
		
		cout << "login padrao:Admin\n 123";
		return;	
	}
	F tempF;

	while(!feof(file)){
	
		auxF = (F*) malloc(sizeof(F));
		auxF->proximo = NULL;
		
		fscanf(file,"%d\n",&tempF.matricula);
		fscanf(file,"%s\n",&tempF.cpf);
	 	
	 	fscanf(file,"%[^\n]s\n",&tempF.nome);
	 	fscanf(file,"%s\n",&tempF.senha);
	 
	 	fscanf(file,"%[^\n]s\n",&tempF.especialidade);
	 
	 	fscanf(file,"%d %d %d\n",&tempF.nascimento.dia,&tempF.nascimento.mes,&tempF.nascimento.ano);
	 	fscanf(file,"%s\n%s\n",&tempF.contanto.fone,&tempF.contanto.email);
	 	
	 	auxF->matricula = tempF.matricula;
	 	strcpy(auxF->cpf,tempF.cpf);
	 	
	 	
		strcpy(auxF->nome,tempF.nome);
		strcpy(auxF->especialidade,tempF.especialidade);
	
		strcpy(auxF->senha,tempF.senha);
		auxF->nascimento.dia = tempF.nascimento.dia;
		auxF->nascimento.mes = tempF.nascimento.mes;
		auxF->nascimento.ano = tempF.nascimento.ano;
		strcpy(auxF->contanto.fone,tempF.contanto.fone);
		strcpy(auxF->contanto.email,tempF.contanto.email);
		
		if(inicioF==NULL){
			 auxF->anterior = NULL;	
			 inicioF = auxF;
			 fimF = auxF;    
		}else{
			auxF->anterior = fimF;
			fimF->proximo = auxF;
			fimF = auxF; 
		}
		
 	}
fclose(file);
} 


void listarF(){
if(inicioF == NULL){
	cout << "Listar vazia";
	sleep(1);
	return;
}

F *no = inicioF;
cout << "LISTA DE FUNCIONARIOS\n";
cout << "*********************************";
while(no){
	cout << "\nMatricula:" << no->matricula;
	cout << "\nNome:"<<no->nome;
	cout << "\nCPF:"<<no->cpf;
	printf("\nNascimento: %d/%d/%d",no->nascimento.dia,no->nascimento.mes,no->nascimento.ano); 
	cout << "\nEspecialidade:"<<no->especialidade;
	cout << "\nTelefone:"<<no->contanto.fone;
	cout << "\nEmail:"<<no->contanto.email;
	cout << "\n*********************************";
	no = no->proximo; 
	}
getch();

}

void editarF(){
F tempF;
auxF = inicioF;
int tempMat;
char c;
	if(inicioF==NULL){
		listarVazia();
		return;
	}
	
	
		cout << "EDITANDO FUNCIONARIO\n";
		cout << "***********************************\n";
		cout << "Matricula: ";
		cout << "\n***********************************";
		gotoxy(12,3);
		cin >> tempMat;
		
		system("cls");
		cout << "EDITANDO FUNCIONARIO\n";
		cout << "***********************************\n";
		while(auxF){
			if(auxF->matricula == tempMat){
				gotoxy(1,3);
				cout << "Matricula:" << auxF->matricula<< "\nNome:" <<auxF->nome;
				cout << "\n***********************************\n";
				gotoxy(1,6);
				cout << "Nome:";
				gotoxy(1,7);
				cout << "Senha:";
				gotoxy(1,8);
				cout << "CPF:";
				gotoxy(1,9);
				cout <<  "Aniversario:    /   /";
				gotoxy(1,10);
				cout << "Especialidade:";
				gotoxy(1,11);
				cout << "Email:";
				gotoxy(1,12);
				cout << "Telefone:";
				gotoxy(1,13);
				cout << "***********************************\n";
			
				fflush(stdin);
				gotoxy(7,6);
				gets(tempF.nome);
				gotoxy(8,7);
				cin >> tempF.senha;
				gotoxy(6,8);
				cin >> tempF.cpf;
				gotoxy(15,9);
				cin >> tempF.nascimento.dia;
				gotoxy(18,9);
				cin >> tempF.nascimento.mes;
				gotoxy(22,9);
				cin >> tempF.nascimento.ano;
				fflush(stdin);
				gotoxy(16,10);
				gets (tempF.especialidade);
				gotoxy(8,11);
				cin >> tempF.contanto.email;
				gotoxy(11,12);
				cin >> tempF.contanto.fone;
				gotoxy(8,14);
				cout << "\tComfirmar[S/N]: ";
				c = toupper(getch());
				if(c == 'S'){
						strcpy(auxF->cpf,tempF.cpf);
					 	for(i=0;i<41;i++){
					 		if(tempF.nome[i]=='\n') tempF.nome[i] =' ';
					 		auxF->nome[i] = tempF.nome[i]; 
							if(tempF.especialidade[i]=='\n') tempF.especialidade[i] = ' ';
							auxF->especialidade[i] = tempF.especialidade[i];   
						}
						strcpy(auxF->senha,tempF.senha);
						auxF->nascimento.dia = tempF.nascimento.dia;
						auxF->nascimento.mes = tempF.nascimento.mes;
						auxF->nascimento.ano = tempF.nascimento.ano;
						strcpy(auxF->contanto.fone,tempF.contanto.fone);
						strcpy(auxF->contanto.email,tempF.contanto.email);
				}else{
					return;
				}
				
			}
			auxF = auxF->proximo;
		} 
	}
		

void menuFuncionario(){
do{
	system("cls");
do{

	system("cls");
	
	int col = 15;
	gotoxy(col,9);
	cout << "       Menu Funcionario 	";
	gotoxy(col,11);
	cout << "1 - Inserir";
	gotoxy(col,12);
	cout << "2 - Listar";
	gotoxy(col,13);
	 cout << "3 - Editar";
	 gotoxy(col,14);
	 cout << "4 - Excluir";	
	 gotoxy(col,15);
	 cout << "5 - Sair";
	 gotoxy(col,16);
	 cout << "Opcao > ";
	 gotoxy(col+8,16);

	 fflush(stdin);
	 cin >> op;
	  if (op<1 || op>5){
	    op=-1;
	    gotoxy(col,17);
	    cout << "Opcao invalida";
	    sleep(2);
	  }  
}while(op==-1);

	  system("cls");
	 switch(op){
	 	case 1:
	 		if(usuario.admin ==  false){
				gotoxy(20,7);
				cout << "Usuario nao e admin nao pode fazer essa operacao";
				getch();
				break;
			}
	 		inserirF();
	 	break;
	 	case 2:
	 		listarF();
	 		
	 	break;
		case 3:
			if(usuario.admin ==  false){
				gotoxy(20,7);
				cout << "Usuario nao e admin nao pode fazer essa operacao";
				getch();
				break;
			}
			editarF();
		break;	
		case 4:
			if(usuario.admin ==  false){
				gotoxy(20,7);
				cout << "Usuario nao e admin nao pode fazer essa operacao";
				getch();
				break;
			}
			removerF();
		break;
		case 5:
			gotoxy(30,7);
			salvarF();
			cout << "SALVANDO E VOLTANDO PARA O MENU INICIAL";
			sleep(2);
			return;
		break;	
	 } 


}while(op != 5);
  		
	
}

int buscarF(){
	
    int cont;
	int col,linha;
	char tempNome[40],tempNome2[40];
	gotoxy(37,9);
	cout << " ------------------------------------";
	gotoxy(37,10);
	cout<< "|Buscar funcionario                 |";
	gotoxy(37,11);
	cout << " ------------------------------------";
	
	gotoxy(37,12);
	cout << "|Nome:                              |";
	fflush(stdin);
	gotoxy(44,12);
	gets(tempNome);
	
	auxF = inicioF; 
	int nomeIgual;
	
	while(auxF){
		
	  //strcpy(tempNome2,auxF->nome); 	
	  if(strcmp(tempNome,auxF->nome)==0){
	  
		//if(nomeIgual == 0){
		
			gotoxy(37,12);
			cout << "|Nome: " << auxF->nome << "";    
			gotoxy(50,13);
			cout << "|" ;  
			gotoxy(37,13);
			
			cout << "|Matricula: " << auxF->matricula << "";
			gotoxy(73,13);
			cout << "|" ;  
			gotoxy(37,14);
			cout << " ------------------------------------";
			int tempCodigo = auxF->matricula; 
			return tempCodigo;
		//}
		}
	//*/
	auxF = auxF->proximo;
	
	}
		char opR;
		cout << "\n\nNome nao existe,procura outro[s/n]:";
		opR = toupper(getchar());
		if(opR == 'S'){
			buscarF();		
		}else{
			return 0;
		}
}


/************Funcao Paciente***************/

void inserirP(){
	P *no;
	no = (P*) malloc(sizeof(P));
	no->proximo = NULL;
	
	gotoxy(1,1);
	cout << "CADASTRANDO PACIENTE\n";
	cout <<"***********************************"; 
	int tempCod;
	if(inicioP == NULL ){
		tempCod= 20180001;
	}else{
	
		tempCod = fimP->codigo + 1;
	}
	
	gotoxy(1,3);
	cout << "Codigo: " << tempCod;
	gotoxy(1,4);
	cout << "Nome:";
	gotoxy(1,5);
	cout << "Nascimento:  /  /";
	gotoxy(1,6); 
	cout << "Idade:";
	gotoxy(1,7);
	cout << "Peso:";
	gotoxy(1,8);
	cout << "Tipo sanguineo: ";
	no->matF = usuario.matricula;
	gotoxy(1,9);
	cout << "Matricula do Funcionario: ";
	no->codigo = tempCod;
	
	gotoxy(6,4);
	fflush(stdin);
	gets(no->nome);
	fflush(stdin);
	gotoxy(12,5);
	cin >> no->nascimento.dia;
	gotoxy(15,5);
	cin >> no->nascimento.mes;
	gotoxy(18,5);
	cin >> no->nascimento.ano;
	no->idade = 2018- no->nascimento.ano;
	gotoxy(7,6);
	cout << no->idade;
	gotoxy(6,7);
	cin >> no->peso;
	gotoxy(16,8);
	cin >> no->sangue;
	gotoxy(20,9);
	cout << no->matF;
	
	if(inicioP==NULL){
		inicioP = no;
		no->anterior=NULL;
		fimP = no;
	} else{
		no->anterior = fimP;
		fimP->proximo = no; 
		fimP = no;
	}


}


void listarP(){

	if(inicioP==NULL){
		cout << "Lista vazia";
		sleep(2);
		return;
	}	
	
	P *no = inicioP;
	cout << "LISTA DE PACIENTES\n";
	cout << "*********************************\n";
	while(no){
		cout << "Codigo: " << no->codigo;
		cout << "\nNome: " << no->nome;
		printf("\nNascimento: %d/%d/%d",no->nascimento.dia,no->nascimento.mes,no->nascimento.ano);
		cout << "\nIdade " << no->idade;
		printf("\nPeso: %.2f ",no->peso);
				cout << "\nTipo sanguineo: " << no->sangue;	
		cout << "\nMatricula funcionario: " << no->matF;
		cout << "\n*********************************\n";
		
	 no = no->proximo; 	
	}
	getch();

}

void editarP(){
	if(inicioP == NULL){
		cout << "Listar Paciente vazia\n";
		sleep(2);
		return;
	}
	P *no = inicioP ;
	int tempCod;
	cout << "EDITANDO PACIENTE\n";
	cout << "**********************************\n";
	cout << "Codigo do cliente:";
	cout << "\n**********************************";
	gotoxy(21,3);
	cin >> tempCod;
	system("cls");
	while(no){
		if(no->codigo == tempCod){
			cout << "EDITANDO PACIENTE\n";
			cout << "**********************************\n";
			cout << "Codigo do cliente:"<< no->codigo;
			cout << "\nNome:" << no->nome;  
			cout << "\n**********************************";
			
			P tempP;
			gotoxy(1,6);
			cout << "Nome:";
			gotoxy(1,7);
			cout << "Nascimento:  /  /";
			gotoxy(1,8); 
			cout << "Peso:";
			gotoxy(1,9);
			cout << "Tipo sanguineo: ";
			gotoxy(1,10);
			cout << "**********************************\n";
			fflush(stdin);
			
			gotoxy(6,6);
			gets(tempP.nome);
			gotoxy(12,7);
			cin >> tempP.nascimento.dia;
			gotoxy(15,7);
			cin >> tempP.nascimento.mes;
			gotoxy(18,7);
			cin >> tempP.nascimento.ano;
			gotoxy(6,8);
			cin >> tempP.peso;
			gotoxy(16,9);
			cin >> tempP.sangue;
			char tempResp;
			gotoxy(13,11);
			cout << "Confirma[S/N]:";
			tempResp = toupper(getch());
			if (tempResp == 'S'){
				strcpy(no->nome,tempP.nome);
				no->nascimento.dia = tempP.nascimento.dia;
				no->nascimento.mes = tempP.nascimento.mes;
				no->nascimento.ano = tempP.nascimento.ano;
				no->idade = 2018 - tempP.nascimento.ano;
				no->peso = tempP.peso;
				strcpy(no->sangue,tempP.sangue);
			}		
		}
		no = no->proximo;
	}
	

}

void removerP(){
	if(inicioP==NULL){
		cout << "Lista Paciente vazia\n";
		sleep(2);
		return;
	}

	int tempCod;
	cout << "REMOVER PACIENTE\n";
	cout << "**********************************\n";
	cout << "Codigo do cliente:";
	cout << "\n**********************************";
	gotoxy(21,3);
	cin >> tempCod; 
	
	
	if(inicioP->codigo==tempCod){
		if(inicioP==fimP){
			free(inicioP);
			inicioP=NULL;
			fimP = NULL;
			return;
		}else{
			P *no = inicioP;
			inicioP = inicioP->proximo;
			free(no);
			no = NULL;
			inicioP->anterior=NULL;
			return;
		}
	}	

	auxP = inicioP;
		
	while(auxP){
	if(auxP->codigo == tempCod){
		if(auxP==fimP){
			fimP = fimP->anterior;
			fimP->proximo = NULL;
			free(auxP);
			auxP = NULL; 
			return;
		}else{
		
			P *auxAnt = auxP->anterior;
			P *auxProx = auxP->proximo; 
 			
 			auxAnt->proximo = auxProx;
 			free(auxP);
 			auxP = NULL;
 			return;
		}
	
	}
	auxP = auxP->proximo;
	}
	cout << "Codigo do pacientes inexistente";
	sleep(2);
	
}	


void salvarP(){
	if(inicioP==NULL){
		cout << "Sem Pacientes para salvar";
		sleep(2);
		return;
	}	
	FILE *file;
file = fopen("pacientes.txt","w");
		if(file==NULL){
			cout << "Erro na criacao do arquivo ";
			sleep(2);
			return;
		}
		P *no=inicioP;
		while(no){
			fprintf(file,"%d\n",no->codigo);
			fprintf(file,"%s\n",no->nome);
			fprintf(file,"%d %d %d\n",no->nascimento.dia,no->nascimento.mes,no->nascimento.ano);
			fprintf(file,"%d\n",no->idade);
			fprintf(file,"%.2f\n",no->peso);
			
			fprintf(file,"%s\n",no->sangue);
			fprintf(file,"%d\n",no->matF);
			no = no->proximo;
		}
fclose(file);
}

void lerP(){

	FILE *file;
file = fopen("pacientes.txt","r");
		if(file==NULL){
			//cout << "Erro na leitura do arquivo paciente";
			sleep(2);
			return;
		}
		P tempP;
		P *no = NULL;
		
		while(!feof(file)){
		
			no = (P*) malloc(sizeof(P));
			no->proximo = NULL;
			
			fscanf(file,"%d\n",&tempP.codigo);
		
			fscanf(file,"%[^\n]s\n",&tempP.nome);
			fscanf(file,"%d %d %d\n",&tempP.nascimento.dia,&tempP.nascimento.mes,&tempP.nascimento.ano);
			fscanf(file,"%d\n",&tempP.idade);
			fscanf(file,"%f\n",&tempP.peso);
			fscanf(file,"%s\n",&tempP.sangue);
			fscanf(file,"%d\n",&tempP.matF);
			
			no->codigo = tempP.codigo;
			
			for(i=0;i<41;i++){
				if(tempP.nome[i] != '\n'){
						 tempP.nome[i] = tempP.nome[i];
				}
				if(tempP.nome[i] != '\n'){
					no->nome[i] = tempP.nome[i];
				}
			}
			no->nascimento.dia = tempP.nascimento.dia;
			no->nascimento.mes = tempP.nascimento.mes;
			no->nascimento.ano = tempP.nascimento.ano;
			no->idade = tempP.idade;
			no->peso = tempP.peso;
			
			strcpy(no->sangue,tempP.sangue); 
			no->matF = tempP.matF;
			
			if(inicioP==NULL){
				inicioP = no;
				no->anterior=NULL;
				fimP = no;
			} else{
			no->anterior = fimP;
			fimP->proximo = no; 
			fimP = no;
			}
		}
fclose(file);
}


void menuPaciente(){
do{
	system("cls");
do{

	system("cls");
	
	int col = 15;
	gotoxy(col,10);
	cout << "\tMenu Paciente";
	gotoxy(col,11);
	cout << "1 - Inserir";
	gotoxy(col,12);
	cout << "2 - Listar ";
	gotoxy(col,13);
	cout << "3 - Editar";
	gotoxy(col,14);
	cout << "4 - Excluir";	
	gotoxy(col,15);
	cout << "5 - Sair";

	gotoxy(col,16);
	cout << "Opcao > ";
	cin >> op;
	 
	if (op<1 || op>5){
	    op=-1;
	    gotoxy(col,17);
	    cout << "Opcao invalida";
	    sleep(2);
	}  
}while(op==-1);

	  system("cls");
	 switch(op){
	 	case 1:
	 		if(usuario.admin ==  false){
				gotoxy(20,7);
				cout << "Usuario nao e admin nao pode fazer essa operacao";
				getch();
				break;
			}
	 		inserirP();
	 	break;
	 	case 2:
	 		
	 		listarP();
	 		
	 	break;
		case 3:
			if(usuario.admin ==  false){
				gotoxy(20,7);
				cout << "Usuario nao e admin nao pode fazer essa operacao";
				getch();
				break;
			}
			editarP();
		break;	
		case 4:
			if(usuario.admin ==  false){
				gotoxy(20,7);
				cout << "Usuario nao e admin nao pode fazer essa operacao";
				getch();
				break;
			}
			removerP();
		break;
		case 5:
			gotoxy(30,7);
			cout << "VOLTANDO PARA O MENU INICIAL";
			salvarP();
			sleep(1);
			return;
		break;	
	 } 


}while(op != 5);
  		
	
}


/***************************Funcao Consultas***************/
void inserirC(){
 	C *no = inicioC;

 	no = (C*) malloc(sizeof(C));
 	no->proximo = NULL;
 	
 	C tempC;
 	int codC;
 	if(inicioC == NULL){
 	 codC = 20180001;
	}else{
	 codC = fimC->codigoC+1;		
	}
 
 	gotoxy(1,1);
 	cout << "\tCADASTRO DE CONSULTA";
 	gotoxy(1,3);
 	cout << "Codigo da consulta "<< codC;
 	tempC.codigoC = codC;
 	gotoxy(35,3);
	cout << "Data:   /  /      ";
	gotoxy(1,4);
 	cout << "Codigo do medico:";
 	gotoxy(1,5);
	cout << "Codigo do paciente:";
	
	gotoxy(1,7);
	cout << "Descricao: ";
	
	gotoxy(21,4); 
	cin >> tempC.codigoF;
	
	bool respValidarF =  validarCodigoF(tempC.codigoF);
	
if(respValidarF == false){
		int  opVF;
		gotoxy(1,9);
		cout << "Codigo do funcionario invalido!!!\n[1] Busca funcionario pelo nome \n[2] Sair do cadastro de consulta\nOpcao > ";
		cin >> opVF;
		
		if (opVF == 1){
			int tcodF;
			tcodF = buscarF();
			if(tcodF == 0 ){
				gotoxy(1,14);
				cout << "Nao foi retornado um codigo fucionario valido saindo ";
				getch();
				return; 
			}
			tempC.codigoF = tcodF;
			gotoxy(21,4); 
			cout << tempC.codigoF;
		}
		if( opVF == 2){
			cout << "Saindo... ";
			sleep(1);
			return;
		}
}

	

gotoxy(21,5);
cin >> tempC.codigoP;
	
	bool respValidarP = validarCodigoP(tempC.codigoP);
if(respValidarP == false){
		int opVP;
		gotoxy(1,18);
		cout << "Codigo do paciente invalido!!!\n[1] Buscar paciente pelo nome    \n[2] Sair do cadastro de consulta\nOpcao > ";
		cin >> opVP;
		if(opVP == 1){
			int tcodP;
			tcodP = buscarPaciente();
				if(tcodP == 0){
						cout << "Nao foi retornado um codigo valido saindo ";
						getch();
						return; 
				}
			tempC.codigoP = tcodP;
			gotoxy(21,5);	
			cout << tempC.codigoP;
					
		}
		if( opVP == 2){
			cout << "Saindo... ";
			sleep(1);
			return;
		}
			
} 
	

	fflush(stdin);
	

	gotoxy(12,7);
	gets(tempC.descricao);
	
	gotoxy(41,3);
	cin >> tempC.dataC.dia; 
	gotoxy(44,3);
	cin >> tempC.dataC.mes;
	gotoxy(47,3); 
	cin >> tempC.dataC.ano; 
	gotoxy(56,3);
	cout << "h    m";
	gotoxy(54,3);
	cin >> tempC.hora;
	gotoxy(59,3);
	cin >>tempC.min;
	
	char respC;
	gotoxy(20,6);
	cout << "Confirma [S/N]:";
	cin >> respC;
	respC = toupper(respC);
	
  if(respC == 'S'){
	auxC = (C*) malloc (sizeof(C));
	auxC->proximo = NULL; 
	auxC->codigoC = tempC.codigoC;
	auxC->codigoF = tempC.codigoF;
	auxC->codigoP = tempC.codigoP;
	auxC->dataC.dia = tempC.dataC.dia;
	auxC->dataC.mes = tempC.dataC.mes;
	auxC->dataC.ano = tempC.dataC.ano;
	auxC->hora = tempC.hora;
	auxC->min = tempC.min;
	
	strcpy(auxC->descricao,tempC.descricao);
	
	if(inicioC == NULL){
		auxC->anterior = NULL;
		inicioC = auxC;
		fimC = auxC;
	}else{
		auxC->anterior = fimC;
		fimC->proximo = auxC;
		fimC = auxC;
	} 
}
	
}


void listarC(){

	if(inicioC==NULL){
		cout << " Listar Vazia...";
		sleep(2);
		return;  
	}

	cout << "LISTA DE CONSULTAS\n";
	cout << "****************************************\n";
		auxC = inicioC;
	while(auxC!=NULL){
		cout << "Codigo da consulta " << auxC ->codigoC << "\n";
		cout << "Matricula do medico " << auxC ->codigoF << "\n";
		cout << "Codigo do paciente " << auxC ->codigoP << "\n";
		printf("Data:%d/%d/%d  %dh  %dm \n",auxC->dataC.dia,auxC ->dataC.mes,auxC->dataC.ano,auxC->hora,auxC->min);
		cout << "Descricao:"<< auxC ->descricao<<"\n";
		cout << "****************************************\n";	
		
		auxC  = auxC->proximo;
	}
	
	getch();

}

void editarC(){
	
	if(inicioC ==NULL ){
		cout << "Listar vazia ";
		sleep(2);
		return ;
	}
	int tempCod;
	cout << "EDITANDO CONSULTA\n";
	cout << "***********************************\n";
	cout << "Codigo: ";
	cout << "\n***********************************";
	gotoxy(8,3);
	cin >> tempCod;
	
	C tempC,*no = inicioC;
	
	system("cls");
	cout << "EDITANDO CONSULTA\n";
	cout << "***********************************\n";
	
	
	while(no){
		if(tempCod == no->codigoC){
			cout << "Codigo de consulta: " << no->codigoC << "\n";
			cout << "Codigo de medico: " << no->codigoF << "\n";
			cout << "Codigo de paciente: " << no->codigoP << "\n";
			
			cout << "***********************************\n";
			gotoxy(1,7);			
			cout << "Data:   /  /";
			gotoxy(1,8);
			cout <<"Horario:    h     m";
			gotoxy(1,9);
			cout << "Descricao:";
			gotoxy(1,10);
			cout << "***********************************\n";
			gotoxy(7,7);
			cin >> tempC.dataC.dia;
			gotoxy(10,7);
			cin >> tempC.dataC.mes;
			gotoxy(13,7);
			cin >> tempC.dataC.ano;
			gotoxy(10,8);
			cin >> tempC.hora;
			gotoxy(16,8);
			cin >> tempC.min;
			fflush(stdin);
			gotoxy(12,9);
			gets(tempC.descricao);
			
			char tempResp;
			gotoxy(10,11);
			cout<< "Confirmar[S/N]:";
			tempResp = toupper(getch());
			if(tempResp == 'S'){
				no->dataC.dia = tempC.dataC.dia;
				no->dataC.mes = tempC.dataC.mes;
				no->dataC.ano = tempC.dataC.ano;
				no->hora = tempC.hora;
				no->min = tempC.min;
				strcpy(no->descricao,tempC.descricao);
			
			}
		
		}	
		
		
		
	no= no->proximo ;
		
	}
	
}

void removerC(){
	if(inicioC==NULL){
		cout << "Lista consultar vazia";
		sleep(2);
		return;
	}
	
	int tempCod;
	cout << "EDITANDO CONSULTA\n";
	cout << "***********************************\n";
	cout << "Codigo: ";
	cout << "\n***********************************";
	gotoxy(8,3);
	cin >> tempCod;
	cout << "....";
	getch(); 
	if(inicioC->codigoC == tempCod){
		if(inicioC==fimC){
			free(inicioC);
			inicioC = NULL;
			fimC = NULL;
			return;			
		}else{
			auxC = inicioC->proximo;
			free(inicioC);
			inicioC = auxC;
			inicioC->anterior = NULL;
		
			return;
		}
	}
	cout << "....";
	getch(); 
	
	auxC = inicioC;
	
	while(auxC){
		if(auxC->codigoC == tempCod){
			if(auxC == fimC){
				fimC = fimC->anterior;
				fimC->proximo = NULL;
				free(auxC);
				auxC = NULL;
				
				return;
			}else{
				C *noC = auxC->anterior;
				noC->proximo = auxC->proximo;
				free(auxC);
				auxC = NULL;
				return;
			}
			
			
		}
		auxC = auxC->proximo;
	
	}
	
	cout << "Codigo da consulta inexistente";
	sleep(2);
	
	
}


void salvarC(){
	FILE *file;
file = fopen("consultas.txt","w");
	auxC = inicioC;
	if(file == NULL){
		cout << "Erro na criacao do arquivo";
		sleep(2);
		return;
	}	
	auxC = inicioC;
	while(auxC){
		fprintf(file,"%d\n",auxC->codigoC);
		fprintf(file,"%d\n",auxC->codigoF);
		fprintf(file,"%d\n",auxC->codigoP);
		fprintf(file,"%d %d %d\n",auxC->dataC.dia,auxC->dataC.mes,auxC->dataC.ano);
	
		fprintf(file,"%s\n",auxC->descricao);
			fprintf(file,"%d %d\n",auxC->hora,auxC->min);
		auxC = auxC->proximo;		
	}
fclose(file);	
}




void lerC(){
	FILE *file;
	
file = fopen("consultas.txt","r");

	if(file == NULL){
		//cout << "Erro na leitura do arquivo consulta";
		sleep(2);
		return;
	}
	C tempC;
	
while(!feof(file)){
	

	
	auxC = (C*) malloc (sizeof(C));
	auxC->proximo = NULL;
	 
		 fscanf(file,"%d\n",&tempC.codigoC);
		 fscanf(file,"%d\n",&tempC.codigoF);
		 fscanf(file,"%d\n",&tempC.codigoP);
		 fscanf(file,"%d %d %d\n",&tempC.dataC.dia,&tempC.dataC.mes,&tempC.dataC.ano);
		 fscanf(file,"%[^\n]s\n",&tempC.descricao);
		 fscanf(file,"%d %d\n",&tempC.hora,&tempC.min);
		 
		
		 
	auxC->codigoC = tempC.codigoC;
	auxC->codigoF = tempC.codigoF;
	auxC->codigoP = tempC.codigoP;
	
	auxC->dataC.dia = tempC.dataC.dia;
	auxC->dataC.mes = tempC.dataC.mes;
	auxC->dataC.ano = tempC.dataC.ano;	
	
	
	auxC->hora = tempC.hora;
	auxC->min = tempC.min;
	
	strcpy(auxC->descricao,tempC.descricao);
	


	if(inicioC == NULL){
		auxC->anterior = NULL;
		inicioC = auxC;
		fimC = auxC;
		
	}else{
		auxC->anterior = fimC;
		fimC->proximo = auxC;
		fimC = auxC;
	} 
	
		
}



fclose(file);	
}


bool validarCodigoF(int x){
	F *no = inicioF;
	while(no){
		if(no->matricula == x){
			return true;
		}
	no = no->proximo;
	}
	return false;
}

bool validarCodigoP(int x){
	P *no = inicioP;
	while(no){
		if(no->codigo == x){
			return true;
		}
	no = no->proximo;
	}
	return false;
}





void menuConsulta(){
do{
	system("cls");
do{

	system("cls");
	
	int col = 15;
	gotoxy(col+10,10);
	cout << "Menu Consulta";
	gotoxy(col,11);
	cout << "1 - Inserir";
	gotoxy(col,12);
	cout << "2 - Listar";
	gotoxy(col,13);
	cout << "3 - Editar";
	gotoxy(col,14);
	cout << "4 - Excluir";	
	gotoxy(col,15);
	cout << "5 - Sair";
	gotoxy(col,16);
	cout << "Opcao > ";
	gotoxy(23,16);
	fflush(stdin);
	cin >> op;
	if (op<1 || op>5){
	    op=-1;
	    gotoxy(col,17);
	    cout << "Opcao invalida";
	    sleep(2);
	}
	  
}while(op==-1);

	  system("cls");
	 switch(op){
	 	case 1:
	 		if(usuario.admin ==  false){
				gotoxy(20,7);
				cout << "Usuario nao e admin nao pode fazer essa operacao";
				getch();
				break;
			}
	 		inserirC();
	 	break;
	 	case 2:
	 		if(usuario.admin ==  false){
				gotoxy(20,7);
				cout << "Usuario nao e admin nao pode fazer essa operacao";
				getch();
				break;
			}
	 		listarC();
	 		
	 	break;
		case 3:
			if(usuario.admin ==  false){
				gotoxy(20,7);
				cout << "Usuario nao e admin nao pode fazer essa operacao";
				getch();
				break;
			}
			editarC();
		break;	
		case 4:
			if(usuario.admin ==  false){
				gotoxy(20,7);
				cout << "Usuario nao e admin nao pode fazer essa operacao";
				getch();
				break;
			}
			removerC();
		break;
		case 5:
			gotoxy(30,7);
			salvarC();
			cout << "VOLTANDO PARA O MENU INICIAL";
			sleep(2);
			return;
		break;	
	 } 


}while(op != 5);
  		
	
}
		

/************Menus***************/

void menuInicial(){
 int col=15;
do{
	system("cls"); 
do{
	 mostrarUsuario();			
	 gotoxy(col,9);
	 cout << "           Menu Inicial         ";
	 gotoxy(col,11);
	 cout << "1 - Funcionario";
	 gotoxy(col,12);
	 cout << "2 - Paciente ";
	 gotoxy(col,13);
	 cout << "3 - Consulta";
	 gotoxy(col,14);
	 cout << "4 - Relatorio  ";	
	 gotoxy(col,15);
	 cout << "5 - Sair";
	 gotoxy(col,16);
	 cout << "Opcao >"; 
	 gotoxy(23,16);
	 cin >> op;
	 
	  if (op<1 || op>4){
	    op=-1;
	    gotoxy(col,17);
	    cout << "Opcao invalida";
	    sleep(2);
	  }
	  system("cls");
}while(op==-1);
  	
  switch(op){
  	case 1:
  		menuFuncionario();
  	break;
  	case 2:
  		menuPaciente();
  	break;
  	case 3:
  		menuConsulta();
  	break;
  	case 4:
  		menuRelatorio();
  	break;
  	case 5:
  		exit(1);
  	break;
  }	
  
}while(op != -1); 
}



void telaLogin(){
	system("cls");
	F tempF,*no = inicioF;
	int n1,n2,n3=0;
	gotoxy(15,8);
	cout << "Login:";

	
	gotoxy(15,9);
	cout<< "Senha:";
	fflush(stdin);
	gotoxy(22,8);
	gets(tempF.nome);
	gotoxy(22,9);
	cin >> tempF.senha;
	
	while(no){
	
		n1 = strcmp(no->nome,tempF.nome);
		n2 = strcmp(no->senha,tempF.senha);
		
		if(n1==0 && n2==0){
		cout << "2222222";
			strcpy(usuario.nome,tempF.nome);
			strcpy(usuario.senha,tempF.senha);
			usuario.matricula = no->matricula;
			char tempEsp[40],agente[40]= "AGENTE DE SAUDE";
			 
			strcpy(tempEsp,no->especialidade);
			for(i=0;i<41;i++){
				tempEsp[i] = toupper(tempEsp[i]);
				if(tempEsp[i] == agente[i]){
					n3++;
				}
			}
		
			
		
			if(strcmp(tempEsp,agente)==0){
				usuario.admin = true;
			}else{
				usuario.admin = false;
			}
			return;
		}	
		no = no->proximo;
	} 
	gotoxy(15,12);
	cout << "Usuario ou senha incorreta\n";
	getch();
	system("cls");
	telaLogin();
}

void listarVazia(){
	system("cls");
	gotoxy(27,10);
	cout << "Listar vazia";
	getch();
	return; 
}


//buscar Funcoes

int buscarPaciente(){
	
    int cont;
	int col,linha;
	char tempNome[40];
	
	gotoxy(37,17);
	cout << " ------------------------------------\n";
	gotoxy(37,18);
	cout<< "|Buscar paciente                    |\n";
	gotoxy(37,19);
	cout << " ------------------------------------\n";
	gotoxy(37,20);
	cout << "|Nome:                              |";
	fflush(stdin);
	gotoxy(43,20);
	gets(tempNome); 
	
	auxP = inicioP;
	while(auxP){
	
		
		if(strcmp(tempNome,auxP->nome)==0){
		
	
			gotoxy(37,20);
			cout << "|Nome: " << auxP->nome;
			gotoxy(37,21);
			cout << "|Matricula: " << auxP->codigo;
			gotoxy(37,22);
			cout << " ------------------------------------";
			int tempCodigo = auxP->codigo; 
			return tempCodigo;
		}
	
	auxP = auxP->proximo;
	}
		char opR;
		
		cout << "\n\nNome nao existe,procura outro[s/n]:";
		opR = toupper(getchar());
		if(opR == 'S'){
			buscarPaciente();		
		}else{
			return 0;
		}
		
		
	
	
	}



void lerArquivos(){
	lerF();
	lerP();
	lerC();
}

//relatorio

void menuRelatorio(){
	int op;
	do{
	system("cls");
do{
	
	system("cls");
	
	int col = 15;
	gotoxy(col+10,10);
	cout << "Menu Relatorio";
	gotoxy(col,11);
	cout << "1 - Listagem de Funcioanrio";
	gotoxy(col,12);
	cout << "2 - Listagem de aniversariantes";
	gotoxy(col,13);
	cout << "3 - Atedimento Geral";
	gotoxy(col,14);
	cout << "4 - Estatistica do Profissional";	
	gotoxy(col,15);
	cout << "5 - Sair";
	gotoxy(col,16);
	cout << "Opcao > ";
	gotoxy(23,16);

	cin >> op;
	if (op<1 || op>5){
	    op=-1;
	    gotoxy(col,17);
	    cout << "Opcao invalida";
	    sleep(2);
	}
	  
}while(op==-1);

	  system("cls");
	 switch(op){
	 	case 1:
	 		rlistagemProfissional(); 
	 	break;
	 	case 2:
	 		rAniversariantes();
	 		
	 	break;
		case 3:
			ratendimentoGeral();
		break;	
		case 4:
			
		break;
		case 5:
			gotoxy(30,7);
			cout << "VOLTANDO PARA O MENU INICIAL";
			sleep(2);
			return;
		break;	
	 } 


}while(op != 5);
  		
	
}



void rlistagemProfissional(){
	auxF = inicioF;
	cout << "*****************************************************\n";
	printf("LISTAGEM DE PROFISSIONAIS\n");
	cout << "*****************************************************\n";
	gotoxy(1,4);
	cout << "Matricula";
	gotoxy(18,4);
	cout << "Nome";
	gotoxy(38,4);
	cout << "Especialidade";
	cout << "\n*****************************************************\n";
	int col,lin=6;
	while(auxF){
		gotoxy(1,lin);
		cout << auxF->matricula;
		gotoxy(18,lin);
		cout << auxF->nome;
		gotoxy(38,lin);
		cout << auxF->especialidade;
		
		auxF =  auxF->proximo;
		lin++;
	}
	char tempResp;
	cout << "\n*****************************************************\n";
	cout << "Gerar um relatorio txt [S/N]:";
	
	tempResp = toupper(getch());
	if(tempResp == 'S'){
		rlistagemProfissionalF();
	}
}


void rlistagemProfissionalF(){
	FILE *file;
	file = fopen("listagemProfissionais.txt","w");
	if(file==NULL){
		cout << "na criação do arquivo ";
		sleep(2);
		return;
	}
	
	auxF = inicioF;
	fprintf(file,"*****************************************************************\n");
	fprintf(file,"LISTAGEM DE PROFISSIONAIS\n");	
	fprintf(file,"*****************************************************************\n");

	fprintf(file,"Matricula");

	fprintf(file,"\tNome");
	
	fprintf(file,"\t\t\tEspecialidade\n");
	fprintf(file,"*****************************************************************\n");
	while(auxF){
		fprintf(file,"%d",auxF->matricula);
		fprintf(file,"\t%s",auxF->nome);
		fprintf(file,"\t\t\t%s\n",auxF->especialidade);
		//fprintf(file,"*****************************************************************\n");	
	auxF = auxF->proximo;
	}
	
fclose(file);
}

void ratendimentoGeral(){
	if(inicioC == NULL){
		cout << "Lista vazia";
		sleep(2);
		return;
	}
	cout << "*****************************************************\n";
	printf("ATENDIMENTO GERAL\n");
	cout << "*****************************************************\n";
	
	
	int a = 0;
	auxC = inicioC;
	
	while(auxC){
	a++;
	cout << "Numero da consulta " << a << "\n";
	auxP = inicioP;
	
	while(auxP){
		if(auxC->codigoP == auxP->codigo ){
			cout << "Nome do Paciente: " << auxP->nome << "\n";
			break;
		}
	
		auxP =  auxP->proximo;
	}
	auxF = inicioF;
	while(auxF){
		if(auxC->codigoF == auxF->matricula){
			cout << "Nome do Funcionario: " << auxF->nome << "\n";
			break;
		}
	
		auxF = auxF->proximo;
	}
	
	printf("Data:%d/%d/%d\n",auxC->dataC.dia,auxC->dataC.mes,auxC->dataC.ano);
	printf("Hora: %dh %dm\n",auxC->hora,auxC->min);
	cout << "*****************************************************\n";
	auxC = auxC->proximo;
	
	}
	char tempR;
	cout << "Gera um txt do relatorio[S/N]:";
	tempR = toupper(getch());
	if (tempR == 'S'){
		ratendimentoGeralF();
	}
}

void ratendimentoGeralF(){

	if(inicioC == NULL){
		cout << "Lista vazia";
		sleep(2);
		return;
	}
	FILE *file;
	
	file = fopen("antedimentoGeral.txt","w");
	
	if(file == NULL){
		cout << "Erro na criacao de antedimento geral ";
		sleep(2);
		return;
	}
	
	
	fprintf(file,"*****************************************************\n");
	fprintf(file,"ATENDIMENTO GERAL\n");
	fprintf(file,"*****************************************************\n");
	
	int a = 0;
	auxC = inicioC;
	
	while(auxC){
	a++;
	fprintf(file,"Numero da consulta %d \n",a);
	auxP = inicioP;
	
	while(auxP){
		if(auxC->codigoP == auxP->codigo ){
			fprintf(file,"Nome do Paciente: %s\n",auxP->nome);
			break;
		}
	
		auxP =  auxP->proximo;
	}
	auxF = inicioF;
	while(auxF){
		if(auxC->codigoF == auxF->matricula){
			fprintf(file,"Nome do Funcionario: %s\n",auxF->nome);
			break;
		}
	
		auxF = auxF->proximo;
	}
	
	fprintf(file,"Data:%d/%d/%d\n",auxC->dataC.dia,auxC->dataC.mes,auxC->dataC.ano);
	fprintf(file,"Hora: %dh %dm\n",auxC->hora,auxC->min);
	fprintf(file,"*****************************************************\n");
	auxC = auxC->proximo;
	
	}
	
		
fclose(file);
}


typedef struct Aniversariantes{
	int cod;
	int contador;	
	struct Aniversariantes *prox;
}A;

//struct A *auxA,inicio;
//auxA =  &inicio;
void rEstatistica_de_Atendimento(){
	if(inicioC == NULL){
		cout << "Lista vazia";
		sleep(2);
		return;
	
	}
	auxC = inicioC;
	C tempC;
	cout << "Relatorio Estatica de Atedimento";
	cout << "***********************************************";
	cout << "Data:  / /";
	cout << "***********************************************";
	gotoxy(7,3);
	cin >> tempC.dataC.dia;
	gotoxy(11,3); 
	cin >> tempC.dataC.mes; 
	gotoxy(14,3);
	cin >> tempC.dataC.ano; 
	

	
	while(auxC){
		
		
	}

}


void rAniversariantes(){

	time_t mytime;
	mytime = time(NULL);
	struct tm tm;
	tm = *localtime(&mytime);
	
	cout << "***********************************************\n";
	cout << "Aniversariante do dia\n";
	cout << "***********************************************\n";
	
	auxF = inicioF;
	gotoxy(1,4);
	cout << "Nome";
	gotoxy(20,4);
	cout << "Data de Aniversario\n";
	cout << "***********************************************\n";

	int lin = 6;
	while(auxF){
		
		if(auxF->nascimento.mes == tm.tm_mon+1 && auxF->nascimento.dia == tm.tm_mday){
			gotoxy(1,lin);
			cout << auxF->nome;
			gotoxy(20,lin);
			printf("%d/%d/%d",auxF->nascimento.dia,auxF->nascimento.mes,auxF->nascimento.ano);
			lin++;
		}
	auxF = auxF->proximo;	
	} 
	char resp; //rAniversariantes(tm);
	gotoxy(1,lin);
	cout << "Gerar realtorio txt[s]:";
	resp = toupper(getch());
	if(resp == 'S'){
		rAniversariantesF(tm);
	}
	
}

void rAniversariantesF(struct tm tm){
	if(inicioF == NULL){
		cout << "Lista vazia";
		sleep(2);
		return;
	}
	
	FILE *file1;
	
file1 = fopen("rAniversarianteF.txt","w");
	if(file1 == NULL){
		cout << "Erro ao criar arquivo Aniversariante";
		sleep(2);
		return;
	}
	
	
	fprintf(file1,"***********************************************\n");
	fprintf(file1,"Aniversariante do dia\n");
	fprintf(file1,"***********************************************\n");
	
	fprintf(file1,"Nome");

	fprintf(file1,"\t\t\tData de Aniversario\n");
	fprintf(file1,"***********************************************\n");
	auxF = inicioF;

	while(auxF){
		if(auxF->nascimento.mes == tm.tm_mon+1 && auxF->nascimento.dia == tm.tm_mday){
			fprintf(file1,"%s",auxF->nome);
			fprintf(file1,"\t\t\t%d/%d/%d\n",auxF->nascimento.dia,auxF->nascimento.mes,auxF->nascimento.ano);
			
			
		}
	auxF = auxF->proximo;	
	} 
	
	
fclose(file1);	
}



void mostrarUsuario(){
gotoxy(50,1);

cout << usuario.matricula; 
gotoxy(50,2);  	
cout << usuario.nome;


}









