#include <string>
#include <cmath>
#include <iostream>
#include <fstream>
#include <map>
#include <stack>
#include <cctype>
using namespace std;
const int X=-1, AC=-2;
stack<double> pila;
map<string, double> tabSim;
bool error;
const int cantFunc=13;
string funciones[] = {"sin", "cos", "tan", "sec", "csc", "cot", "log", "ln","exp", "tanh", "sinh", "cosh", "abs"};
bool opx;
int G[10][7] = {
//    l  d  (  +  .  "  
	{ 1, 2, 8, 5, 3, 6, X},//0
	{ 1, 1,AC,AC, X, X, X},//1
	{ X, 2,AC,AC, 3, X, X},//2
	{ X, 4, X, X, X, X, X},//3
	{ X, 4,AC,AC, X, X, X},//4
	{AC,AC,AC,AC,AC,AC, X},//5
	{ 6, 6, 6, 6, 6, 7, 6},//6
	{ X, X,AC, AC, X, X, X},//7
	{AC,AC,AC,AC,AC,AC, X},//8
	{ X, X,AC,AC, X, X, X},//9
};
bool esFuncion(const string& s) {
	for(int i=0; i < cantFunc; i++) 
		if(funciones[i]==s) 
			return true;
	return false;
}
int tipo(char c){
	if(isdigit(c))
		return 1;
	if(isalpha(c) or c=='_')
		return 0;
	switch(c){
		case '(': case ')':
			return 2;
		case '+': case '-': case '*': case '/': case '^': case '=': case '%':
			return 3;
		case '.':
			return 4;
		case '"':
			return 5;
		default: 
			return 6;
	}
}


string instruccion;
void evalExp();
int idx;
string token, lexema;

void leeToken(){
	lexema="";
	int estado = 0, estAnt=0;
	while( idx < instruccion.size() and estado != X and estado != AC){
		char c = instruccion[idx++];
		int t = tipo(c);
		if( t >= 0 and estado != X and estado != AC){
			estAnt = estado;
			estado = G[estado][t];
			if( estado != X and estado != AC){ 
				lexema += c;
			}
		}else if (t < 0 ){ 
			estado = X;
		}
	}
	if(estado==X){
		cout<<instruccion[idx]<<" inesperado"<<endl;
	}
	if(estado == AC) 
		idx--;
	if(estado != X and estado != AC) 
		estAnt = estado;
	switch(estAnt) {
		case 1:
			token="id";
		break;
		case 2: case 4: 
			token="const";
		break;
		case 5: 
			token="op";
		break;
		case 8: 
			token="()";
		break;
		case 7:
			token="const_str";
		break;
		default:
			 token="NTK";
		break;
	}
}

void evalTermino(){
	if(lexema == "(" ) {
		leeToken();
		evalExp();
		if(lexema!=")" ) {
			error=true;
			cout<<"Error, Se esperaba cerrar parentesis )"<<endl;
		}
		leeToken();
	}else if(token=="id"){
		opx=true;
		string fn = lexema;
		if(!esFuncion(fn)){
			double val;
			if(tabSim.find(lexema)==tabSim.end()){
				cout<<"La variable '"<<lexema<<"' no ha sido definida"<<endl;
				error=true;
				pila.push(0);
			}else
			pila.push(tabSim[lexema]);
			opx=true;
			leeToken();
		}else{
			leeToken();
			if(lexema!="("){ 
				cout<<"Error, Se esperaba abrir parentesis ("<<endl;
				error=true;
			}
			leeToken();
			evalExp();
			if(lexema!=")") {
				error=true;
				cout<<"Error, Se esperaba cerrar parentesis )"<<endl;
			}
			leeToken();
			double val;
			if(fn=="sin"){
				val=pila.top();
				pila.pop();
				pila.push(sin(val)); 
			}else if(fn=="cos"){
				val=pila.top(); 
				pila.pop();
				pila.push(cos(val) ); 
			}else if(fn=="tan"){ 
				val=pila.top(); 
				pila.pop();
				pila.push(tan(val) ); 
			}else if(fn=="sec"){ 
				val=pila.top(); 
				pila.pop();
				pila.push(1.0 / cos(val) ); 
			}else if(fn=="csc"){ 
				val=pila.top(); 
				pila.pop();
				pila.push(1.0 / sin(val) );  
			}else if(fn=="exp"){
				val=pila.top(); 
				pila.pop();
				pila.push(pow(M_E,val)); 
			}else if(fn=="cot"){
				val=pila.top();
				pila.pop();
				pila.push(1.0/tan(val));
			}else if(fn=="log"){
				val=pila.top();
				pila.pop();
				pila.push(log10(val));
			}else if(fn=="ln"){
				val=pila.top();
				pila.pop();
				pila.push(log(val));
			}else if(fn=="tanh"){
				val=pila.top();
				pila.pop();
				pila.push(tanh(val));
			}else if(fn=="sinh"){
				val=pila.top();
				pila.pop();
				pila.push(sinh(val));
			}else if(fn=="cosh"){
				val=pila.top();
				pila.pop();
				pila.push(cosh(val));
			}else if(fn=="abs"){
				val=pila.top();
				pila.pop();
				pila.push(abs(val));
			}
			opx=true;
		}
	}else if(token=="const"){
		double val = stod(lexema);
		pila.push(val);
		opx=true;
		leeToken();
	}else {
		error=true;
		cout<<"Error, (, Ide, Dec "<<endl; 
		leeToken();
	}
}

void evalSigno(){
	bool sig=false;
	if(lexema=="-"){
		sig = true;
		leeToken();
	}
	evalTermino();
	if(sig){
		double val=pila.top();
		pila.pop();
		pila.push(-val);
	}
}

void evalPotencia(){
	string operador="";
	do{
		if(lexema=="^"){
			operador=lexema;
			leeToken();
		}
		evalSigno(); 
		if(operador=="^"){
			double izq = pila.top();
			pila.pop();
			double der=pila.top();
			pila.pop();
			pila.push(pow(der,izq));
		}
	}while(lexema=="^");
}

void evalMulti(){
	string operador="";
	do{
	//	cout<<"Multi "<<token<<"::"<<lexema<<endl;
		if(lexema=="*" or lexema=="/" or lexema=="%"){
			operador=lexema;
			leeToken();
		}
		evalPotencia(); 
	//	cout<<"Multi "<<token<<"::"<<lexema<<endl;
		if(operador=="%" or operador=="/" or operador=="*"){
			double der = pila.top();
			pila.pop();
			double izq = pila.top();
			pila.pop();
			if(operador=="*"){
				pila.push(izq*der);
			}else if(operador=="/"){ 
				pila.push(izq/der);
			}else if(operador=="%"){
				pila.push(fmod(izq,der));
			}
		}
	}while(lexema=="*" or lexema=="/" or lexema=="%");
}

void evalExp(){
	string operador="";
	do{
		if(lexema=="+" or lexema=="-" and opx){
			operador=lexema;
			leeToken();
		}
		evalMulti(); 
		if(operador=="+" or operador=="-" and opx){
			double der = pila.top();
			pila.pop();
			double izq=pila.top();
			pila.pop();
			if(operador=="+"){
				pila.push(izq+der);
			}else if(operador=="-"){ 
				pila.push(izq-der);
			}
		}
	}while(lexema=="+" or lexema=="-");
}

void evalua(){
/*	while(idx<instruccion.size()){
		leeToken();
		cout<<token<<"::"<<lexema<<endl;
	}
	return;*/
	if(instruccion=="")
		return;
	pila=stack<double>();
	leeToken();
	if(lexema=="leer"){
		leeToken();
		if(lexema=="("){
			leeToken();
			if(token=="id"){
				string sim=lexema;
				leeToken();
				if(lexema==")"){
					cin>>tabSim[sim];
					cin.ignore();
					return;
				}
			}
		}
	}else if(lexema=="mostrar"){
		leeToken();
		if(lexema=="("){
			leeToken();
			if(token=="const_str"){
				string salida=lexema;
				leeToken();
				if(lexema==")"){
					cout<<salida;
					return;
				}
			}else{
				evalExp();
				leeToken();
				cout<<pila.top();
				return;
				
			}
		}
	}else if(lexema=="mostrarnl"){
		leeToken();
		if(lexema=="("){
			leeToken();
			if(token=="const_str"){
				string salida=lexema.substr(1,-1);
				leeToken();
				if(lexema==")"){
					cout<<salida<<endl;
					return;
				}
			}else{
				evalExp();
				leeToken();
				cout<<pila.top()<<endl;
				return;
			}
		}
	}if(token=="id" and not esFuncion(lexema)){
		string id=lexema;
		leeToken();
		if(lexema=="="){
			leeToken();
			evalExp();
			tabSim[id]=pila.top();
			return;
		}
	}else{
		idx=0;
		leeToken();
		evalExp();
		cout<<pila.top()<<endl;
	}
}

int main(int argc, char**argv){
	if(argc>=2){
		ifstream arch(argv[1]);
		do{
			getline(arch,instruccion);
			idx=0;
			error=false;
			opx=false;
			evalua();
		}while(not arch.eof());
	}else{
		do{
			cout<<">>";
			getline(cin, instruccion);
			idx=0;
			error=false;
			opx=false;
			evalua();
		}while(not cin.eof());
	}
	return 0;
}