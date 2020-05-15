#include <stdio.h>
#include <iostream>
#include<windows.h> 
#include<unistd.h> 
#include <conio.h>

using namespace std;

void gotoxy(int x, int y){
     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){x-1,y-1});
}  

int multiplicacao(int x,int y){
int  result;	
	if(x==0 || y==0){
		return 0;
	}else{
		result = x + multiplicacao(x,y-1);
		return result;
	}
}

int pontecia(int x,int y){
int result;

	if(x==0 && y==0){
		return 0;
	}
	else if (x>0 && y==0){
		return 1;
	}else{
		result = x * pontecia(x,y-1); 
		return result;
	}	

}

void convertor(int x){
int result,resto;	
	if(x <= 1 ){
		cout << x;
		return ;
	}else{
		resto =  x % 2;
		x = x / 2;
		convertor(x);
		printf("%d",resto);		
		return ;
	}
} 

int fatorial(int x){
int result;
if(x==1 || x==0){
	return 1;
}else{
	result = x *fatorial(x -1);
	return result;	
}
}

int fibbonacci(int x) {
   if(x == 0){
      return 0;
   } else if(x == 1) {
      return 1;
   } else {
      return (fibbonacci(x-1) + fibbonacci(x-2));
   }
}

void menu(){
	int op,x,y;
	do{
	
	do{
	system("cls");
	cout << "Calculadora rercusiva\n\n";
	cout << "1 - Multiplicacao\n";
	cout << "2 - Pontencia\n";
	cout << "3 - Converto da base decimal para binaria\n";
	cout << "4 - Fatorial\n";
	cout << "5 - Fibonacci\n";
	cout << "6 - Sair\n";
	cout << "Opcao > ";
	cin  >> op;
	
	if(op > 6){
		cout << "Opcao invalida!!!";
		sleep(2);
	}
		
	system("cls");
	
	}while(op > 6); 
	
	switch(op){
	system("cls");
		case 1:
			cout << "Multiplicacao\n";
			cout << "***********************************\n"; 
			cout << "Numero 1:\n";
			cout << "Numero 2:\n";
			cout << "Resultado = ";
			gotoxy(11,3);
			cin >> x;
			gotoxy(11,4);
			cin >> y;
			gotoxy(13,5);
			cout << multiplicacao(x,y);
		break;
		case 2:
			cout << "Pontecia\n";
			cout << "***********************************\n"; 
			cout << "Numero 1:\n";
			cout << "Numero 2:\n";
			cout << "Resultado = ";
			gotoxy(11,3);
			cin >> x;
			gotoxy(11,4);
			cin >> y;
			gotoxy(13,5);
			cout << pontecia(x,y); 
		break;	
		case 3:
			cout << "Base 10 para 2\n";
			cout << "***********************************\n"; 
			cout << "Numero 1:\n";
			
			
			cout << "Binario:";
			gotoxy(11,3);
			cin >> x;
			gotoxy(11,4);
			convertor(x); 
			//cout << "Resultador = " << convertor(x);
		break;
		case 4:
			cout << "Fatorial\n";
			cout << "***********************************\n"; 
			cout << "Numero 1:\n";
			cout << "Fatorial:";
			gotoxy(11,3);
			cin >> x;
			gotoxy(11,4);
			cout << fatorial(x);
		break;
		case 5:
			cin >> x;
			cout << fibbonacci(x);
		break;
	}
	getch();
	}while(op < 6);
}

int main(){
	menu();
return 1;
}
