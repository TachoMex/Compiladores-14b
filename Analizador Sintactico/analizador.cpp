#include <iostream>
#include <string>
#include <vector>
#include "trie.h"
#include "lexico.h"
#include "sintactico.h"
using namespace std;
int main(){
	string linea;
	palabrasReservadas.agregarPalabra("int");
	palabrasReservadas.agregarPalabra("long");
	palabrasReservadas.agregarPalabra("uint");
	palabrasReservadas.agregarPalabra("ulong");
	palabrasReservadas.agregarPalabra("real");
	palabrasReservadas.agregarPalabra("char");
	palabrasReservadas.agregarPalabra("string");
	palabrasReservadas.agregarPalabra("void");

	palabrasReservadas.agregarPalabra("for");
	palabrasReservadas.agregarPalabra("if");
	palabrasReservadas.agregarPalabra("else");
	palabrasReservadas.agregarPalabra("while");
	//palabrasReservadas.agregarPalabra("switch");
	
	//palabrasReservadas.agregarPalabra("do");
	palabrasReservadas.agregarPalabra("return");
	palabrasReservadas.agregarPalabra("break");
	//palabrasReservadas.agregarPalabra("case");
	//palabrasReservadas.agregarPalabra("foreach");
	//palabrasReservadas.agregarPalabra("const");
	palabrasReservadas.agregarPalabra("not");
	palabrasReservadas.agregarPalabra("and");
	palabrasReservadas.agregarPalabra("or");
	
	palabrasReservadas.agregarPalabra("read");
	palabrasReservadas.agregarPalabra("print");
	getline(cin,linea); //Leer la linea hasta el salto de linea
	int contLinea=1;
	do{
		int p=evaluar(linea.c_str(),contLinea,linea.c_str()); //Evalua la cadena, recibe el estado final
		if(p<0) //cuando el numero que recibe es negativo, el error es que encontro un caracter que no iba, el valor absoluto es la posicion
			cout<<linea<<"::: Caracter '"<<linea[-p-1]<<"' inesperado en posicion "<<-p<<" Linea "<<contLinea<<endl;
		tokens.push_back(token("\n","\n",contLinea,linea.size()));
		contLinea++;
	}while(getline(cin,linea));
	tokens.push_back(token("\n","\n",contLinea,0));
	tokens.push_back(token("EOF","EOF",contLinea,0));
	int i=0;
	for(int i=0;i<tokens.size();i++){
		//cout<<"|"<<tokens[i].tok<<"|";
		cout<<"<"<<tokens[i].tipo<<" = '"<<tokens[i].tok<<"' "<<tokens[i].linea<<"::"<<tokens[i].numero<<">"<<endl;
	}
	nodoArbol raiz=eval();
	//raiz.mostrar(0);
	//cout<<tokens[idx].tok<<endl;
	return 0;
}
