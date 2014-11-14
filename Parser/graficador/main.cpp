#include <GL/freeglut.h>
#include <GL/gl.h>
#include <string>
#include <cmath>
#include <iostream>
#include <map>
#include <stack>
#include <cctype>
#include "graficas.h"

using namespace std;
imagen M(800,400,color::negro);
void renderFunction(){
	M.draw();
	glFlush();
}

namespace parser{
	int idx=0;
	const int ERR=-1, ACP = 999, cantFunc=13;
	string expr="", token="", lex="";
	bool opx=false;
	map<string, double> tabSim;
	stack<double> pila;
	bool error=false;


	int matran[7][5] = {
	/*q0*/{1, 2, 6, 5, ERR},
	/*q1*/{1, 1, ACP, ACP, ACP},
	/*q2*/{ACP, 2, ACP, ACP, 3},
	/*q3*/{ERR, 4, ERR, ERR, ERR},
	/*q4*/{ACP, 4, ACP, ACP, ACP},
	/*q5*/{ACP, ACP, ACP, ACP, ACP},
	/*q6*/{ACP, ACP, ACP, ACP, ACP}
	};
	string func[] = {"sin", "cos", "tan", "sec", "csc", "cot", "log", "ln","exp", "tanh", "sinh", "cosh", "abs"};
	bool esFuncion(const string&);
	int colCar(char);
	string lexico();
	void termino();
	void signo();
	void expo();
	void multi();
	void exp();
	double eval(const string& );
	bool esFuncion(const string& s) {
		for(int i=0; i < cantFunc; i++) 
			if(func[i]==s) 
				return true;
		return false;
	}

	int colCar( char c ) {
		if(isalpha(c) or c == '_') 
			return 0;
		if(isdigit(c)) 
			return 1;
		if( c == '(' or c == ')' ) 
			return 2;
		if( c == '+' or c == '-' or c == '*' or c == '/' or c == '%' or c == '^' ) 
			return 3;
		if( c == '.' ) 
			return 4;
		cout<<"Simbolo Ilegal en expresion "<<c<<endl;
		error=true;
		return ERR;
	}

	string lexico() {
		string lexema="";
		int estado = 0, estAnt=0;
		while( idx < expr.length() and estado != ERR and estado != ACP) {
			char c = expr[idx++];
			int col = colCar( c );
			if( col >= 0 and estado != ERR and estado != ACP ) {
				estAnt=estado;
				estado = matran[estado][col];
				if( estado != ERR and estado != ACP ) 
					lexema += c;
			}
			else if (col < 0 ) 
				estado = ERR;
		}
		if( estado == ACP ) 
			idx--;
		if( estado != ERR and estado != ACP) 
			estAnt = estado;
		switch(estAnt) {
			case 1:
				token="Ide";
			break;
			case 2: case 4: 
				token="Dec";
			break;
			case 5: 
				token="Opr";
			break;
			case 6: 
				token="Del";
			break;
			default:
				 token="NTK";
			break;
		}
		return lexema;
	}
	void termino() {
		if(lex == "(" ) {
			lex = lexico();
			exp();
			if(lex!=")" ) {
				error=true;
				cout<<"Error, Se esperaba cerrar parentesis )"<<endl;
			}
			lex = lexico();
		}else if( token==("Ide") ) {
			opx=true;
			string fn = lex;
			if(!esFuncion(lex) ) {
				double val;
				if(tabSim.find(lex)==tabSim.end()){
					cout<<lex<<": ";
					cin>>val;
					cin.ignore();
					tabSim[lex]=val;
				}
				val = tabSim[lex];
				pila.push(val);
				lex = lexico();
			}else{
				lex = lexico();
				if(lex!="("){ 
					cout<<"Error, Se esperaba abrir parentesis ("<<endl;
					error=true;
				}
				lex = lexico();
				exp();
				if(lex!=")") {
					error=true;
					cout<<"Error, Se esperaba cerrar parentesis )"<<endl;
				}
				lex = lexico();
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
				}
				else if(fn=="log"){
					val=pila.top();
					pila.pop();
					pila.push(log10(val));
				}
				else if(fn=="ln"){
					val=pila.top();
					pila.pop();
					pila.push(log(val));
				}
				else if(fn=="tanh"){
					val=pila.top();
					pila.pop();
					pila.push(tanh(val));
				}
				else if(fn=="sinh"){
					val=pila.top();
					pila.pop();
					pila.push(sinh(val));
				}
				else if(fn=="cosh"){
					val=pila.top();
					pila.pop();
					pila.push(cosh(val));
				}
				else if(fn=="abs"){
					val=pila.top();
					pila.pop();
					pila.push(abs(val));
				}
			}
		}else if( token=="Dec" ) {
			double val = stod(lex);
			pila.push(val);
			lex = lexico();
		}else {
			error=true;
			cout<<"Error, (, Ide, Dec "<<endl; 
			lex= lexico();
		}
	}

	void signo() {
		bool sig=false;
		if(lex=="-"){
			sig = true;
			lex = lexico();
		}
		termino();
		if(sig) {
			double val=pila.top();
			pila.pop();
			pila.push(-val);
		}

	}
	void expo(){
		string ope = "";
		do{
			if(lex=="^"){
				ope=lex;
				lex = lexico();
			}
			signo(); 
			if(ope=="^"){
				double opd = pila.top();
				pila.pop();
				double opi = pila.top();
				pila.pop();
				pila.push(pow(opi,opd));
			}
		}while(lex=="^");
	}
	void multi() {
		string ope="";
		do {
			if( lex=="*" or lex=="/" or lex=="%") {
				ope=lex;
				lex = lexico();
			}
			expo(); 
			if(ope=="*" or ope=="/" or ope=="%"){
				double opd = pila.top();
				pila.pop();
				double opi=pila.top();
				pila.pop();
				if(ope==("*")) 
					pila.push(opi*opd);
				else if(ope==("/")) 
					pila.push(opi/opd);
				else if(ope==("%")) 
					pila.push(fmod(opi,opd));
			}
		}while( lex=="*" or lex=="/" or lex=="%");
	}
	void exp() {
		string ope="";
		do{
			if(lex=="+" or lex=="-" and opx){
				ope=lex;
				lex = lexico();
			}
			multi(); 
			if(ope=="+" or ope=="-" and opx){
				double opd = pila.top();
				pila.pop();
				double opi=pila.top();
				pila.pop();
				if(ope=="+") 
					pila.push(opi+opd);
				else if(ope=="-") 
					pila.push(opi-opd);
			}
		}while(lex=="+" or lex=="-");
	}
	double eval(const string &s){
		idx=0;
		lex="";
		pila = stack<double>();
		expr = s;
		error=false;
		lex=lexico();
		exp();
		double val = pila.top();
		return val;
	}
};

int main(int argc, char**argv){
	string expresion;
	double a, b,c,d;

	do{
		cout<<"f(x)=";
		getline(cin,expresion);
		cout<<"x inf: ";
		cin>>a;
		cout<<"x sup: ";
		cin>>b;
		cout<<"y inf: ";
		cin>>c;
		cout<<"y sup: ";
		cin>>d;
		double *valores = new double[M.columnas()+1];
		cin.ignore();
		double h=(b-a)/M.columnas();
		parser::tabSim["x"]=a;
		parser::eval(expresion);
		if(not parser::error){
			for(int i=0;i<=M.columnas();i++){
				parser::tabSim["x"]=a+i*h;
				valores[i]=-parser::eval(expresion);
			}
			graficar(M,a,b,c,d,valores,color::blanco);
			glutInit(&argc,argv);
			glutInitDisplayMode(GLUT_SINGLE);
			glutInitWindowSize(M.columnas(),M.filas());
			glutInitWindowPosition(0,0);
			glutCreateWindow(expresion.c_str());
			glClearColor(0, 0,0, 0.0);
			glMatrixMode(GL_PROJECTION);
		    glClear(GL_COLOR_BUFFER_BIT);
			gluOrtho2D(0, M.columnas(),0,M.filas() ); 
			glFlush();
			glutDisplayFunc(renderFunction);
			glutMainLoop();   
		}else{
			cout<<"No evaluado"<<endl;
		}
		delete valores;
	}while(expresion!="." and not cin.eof());
	return 0;
}