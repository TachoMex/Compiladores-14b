#include "trie.h"
#include<cstdio>
#define X 35 //Caracter no esperado

//funcion que convierte el caracter a un dato numerico segun el grupo
int hash(char c){
	switch(c){
		//Hexadecimales
		case 'a': case 'A': return 0; 
		case 'b': case 'B': return 1; 
		case 'c': case 'C': return 2; 
		case 'd': case 'D': return 3; 
		case 'e': case 'E': return 4; 
		case 'f': case 'F': return 5; 
		case 'h': case 'H': return 6; 
		
		//Letras no especiales, En la tabla son A
		case 'g': case 'G': case 'i': case 'I': case 'j': case 'J': case 'k': case 'K': case 'l': case 'L':
		case 'm': case 'M': case 'n': case 'N': case 'o': case 'O': case 'p': case 'P': case 'q': case 'Q':
		case 'r': case 'R': case 's': case 'S': case 't': case 'T': case 'u': case 'U': case 'v': case 'V':
		case 'w': case 'W': case 'x': case 'X': case 'y': case 'Y': case 'z': case 'Z': 
		return 7;
		
		case '_': return 8;
		
		//Operadores
		case '+': return 9;
		case '-': return 10;
		case '/': return 11;
		case '*': return 12;
		case '%': return 13;
		case '<': return 14;
		case '>': return 15;
		case '=': return 16;
		case '&': return 17;
		case '|': return 18;
		case '!': return 19;
		case '^': return 24;
		
		//Digitos
		case '0': return 20;
		case '1': case '2': case '3': case '4': case '5': case '6':case '7': case '8': case '9':return 21;
		case '.': return 22;
		
		//Operadores no validos para la actividad pero que sin son validos en C, si se me paso alguno lo agregan XD
		case ',': case '(': case')': case '{': case '}': case '[': case ']': case '\\': case '"': case '\'': case ':': case ';': case '#':
		return -1;
		
		//Espacios
		case ' ': case '\t': return 25;
		
		//Para cualquier otro caracter, esos si son no validos. En la tabla son la columna  @
		default: return 23;
	}
}
int G[][26]={
	  //a , b, c, d, e, f, h, A, _, +, -, /, *, %, <, >, =, &, |, !, 0, D, ., @, ^, 
	 { 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 5,28,28,28,24,25,29,31,32,33, 2, 2,17,36,27,0 },
	 { 1, 1, 1, 1, 1, 1, 1, 1, 1, X, X, X, X, X, X, X, X, X, X, X, 1, 1, X,36, X, X},
	 {10,10,10,10,10,10,16, X, X, X, X, X, X, X, X, X, X, X, X, X, 2, 2,17,36, X, X},
	 { X, X, X, X, X, X, X, X, X, 4, X, X, X, X, X, X,26, X, X, X, 7, 7, 8,36, X, X},
	 { X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,36, X, X},
	 { X, X, X, X, X, X, X, X, X, X, 6, X, X, X, X, X,26, X, X, X, 7, 7, 8,36, X, X},
	 { X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,36, X, X},
	 { X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, 7, 7, 8,36, X, X},
	 { X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, 9, 9, X,36, X, X},
	 { X, X, X, X,11, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, 9, 9, X,36, X, X},
	 {10,10,10,10,10,10,16, X, X, X, X, X, X, X, X, X, X, X, X, X,10,10, X,36, X, X},
	 { X, X, X, X, X, X, X, X, X,12,12, X, X, X, X, X, X, X, X, X,13,14, X,36, X, X},
	 { X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,13,14, X,36, X, X},
	 { X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,13,14, X,36, X, X},
	 { X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,15,15, X,36, X, X},
	 { X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,37,37, X,36, X, X},
	 { X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,36, X, X},
	 { X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,18,18, X,36, X, X},
	 { X, X, X, X,19, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,18,18, X,36, X, X},
	 { X, X, X, X, X, X, X, X, X,20,20, X, X, X, X, X, X, X, X, X,21,22, X,36, X, X},
	 { X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,21,22, X,36, X, X},
	 { X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,22,22, X,36, X, X},
	 { X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,23,23, X,36, X, X},
	 { X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,37,37, X,36, X, X},
	 { X, X, X, X, X, X, X, X, X, X, X, X, X, X,27, X,30, X, X, X, X, X, X,36, X, X},
	 { X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,27,30, X, X, X, X, X, X,36, X, X},
	 { X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,36, X, X},
	 { X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,26, X, X, X, X, X, X,36, X, X},
	 { X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,26, X, X, X, X, X, X,36, X, X},
	 { X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,30, X, X, X, X, X, X,36, X, X},
	 { X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,36, X, X},
	 { X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,26,34, X, X, X, X, X,36, X, X},
	 { X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,26, X,34, X, X, X, X,36, X, X},
	 { X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,30, X, X, X, X, X, X,36, X, X},
	 { X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,36, X, X},
	 { X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X},
	 {36,36,36,36,36,36,36,36,36,36,36,36,36,36,36,36,36,36,36,36,36,36,36,36,36,36},
	 {37,37,37,37,37,37,37,37,37,37,37,37,37,37,37,37,37,37,37,37,37,37,37,37,37,37},
};

//Arreglo con las cadenas de salida para cada estado. Creo que esto lo veran mas claro cuando les pase el dibujo
char estados[][100]={
	"Cadena Vacia",
	"Identificador",
	"Entero sin signo",
	"Operador aritmetico",
	"Operador aritmetico",
	"Operador aritmetico",
	"Operador aritmetico",
	"Entero con signo",
	"Cadena incompleta. Posible Real con signo",
	"Real con signo",
	"Cadena incompleta. Posible entero hexadecimal",
	"Cadena incompleta. Posible Real con signo Exponencial",
	"Cadena incompleta. Posible Real con signo Exponencial",
	"Real con signo forma Exponencial",
	"Real con signo forma Exponencial",
	"Real con signo forma Exponencial",
	"Entero Hexadecimal",
	"Cadena incompleta. Posible Real sin signo Exponencial",
	"Real sin signo",
	"Cadena incompleta. Posible Real sin signo Exponencial",
	"Cadena incompleta. Posible Real sin signo Exponencial",
	"Real con signo forma Exponencial",
	"Real con signo forma Exponencial",
	"Real con signo forma Exponencial",
	"Operador relacional",
	"Operador relacional",
	"Operador de asignacion",
	"Operador de bits",
	"Operador aritmetico",
	"Operador de asignacion",
	"Operador relacional",
	"Operador de bits",
	"Operador de bits",
	"Operador logico",
	"Operador logico",
	"Caracter inesperado",
	"Caracter no valido",
	"",
	"El valor absoluto del exponente es mayor a 99",
	"",
	"",
	"",
};

int evaluar(char *cad){
	int estado=0; //Contador de estado
	int pos=1; //Contador de posiciones recorridas
	
	while(*cad!='\0'){ //hasta llegar al fin de cadena
		int in=hash(*cad); //Obtiene la columna de la tabla con la funcion hash
		if(in>=0){ //La funcion hash retorna negativo para caracteres no validos en C, si lo encuentra se detiene y sale
			int sig=G[estado][in]; //obtiene el estado siguiente
			if(sig==X) //Si llega a caracter inesperado, rompe el ciclo y retorna la posicion en la que encontro el error
				return -pos;
			estado=sig;
		}else
			return -pos;
		cad++;
		pos++;
	}
	return estado;
}
int main(){
	trie palabrasReservadas;
	palabrasReservadas.agregarPalabra("auto");
	palabrasReservadas.agregarPalabra("break");
	palabrasReservadas.agregarPalabra("case");
	palabrasReservadas.agregarPalabra("char");
	palabrasReservadas.agregarPalabra("const");
	palabrasReservadas.agregarPalabra("continue");
	palabrasReservadas.agregarPalabra("default");
	palabrasReservadas.agregarPalabra("do");
	palabrasReservadas.agregarPalabra("double");
	palabrasReservadas.agregarPalabra("else");
	palabrasReservadas.agregarPalabra("enum");
	palabrasReservadas.agregarPalabra("extern");
	palabrasReservadas.agregarPalabra("float");
	palabrasReservadas.agregarPalabra("for");
	palabrasReservadas.agregarPalabra("goto");
	palabrasReservadas.agregarPalabra("if");
	palabrasReservadas.agregarPalabra("int");
	palabrasReservadas.agregarPalabra("long");
	palabrasReservadas.agregarPalabra("register");
	palabrasReservadas.agregarPalabra("return");
	palabrasReservadas.agregarPalabra("short");
	palabrasReservadas.agregarPalabra("signed");
	palabrasReservadas.agregarPalabra("sizeof");
	palabrasReservadas.agregarPalabra("static");
	palabrasReservadas.agregarPalabra("struct");
	palabrasReservadas.agregarPalabra("switch");
	palabrasReservadas.agregarPalabra("typedef");
	palabrasReservadas.agregarPalabra("union");
	palabrasReservadas.agregarPalabra("unsigned");
	palabrasReservadas.agregarPalabra("void");
	palabrasReservadas.agregarPalabra("volatile");
	palabrasReservadas.agregarPalabra("while");
	
	char linea[100];
	do{
		scanf("%[^\n]%*c",linea); //Leer la linea hasta el salto de linea
		if(palabrasReservadas.existe(linea)) //Verificar si esta dentro del arbol
			printf("Palabra Reservada\n");
		else{
			int p=evaluar(linea); //Evalua la cadena, recibe el estado final
			if(p<0) //cuando el numero que recibe es negativo, el error es que encontro un caracter que no iba, el valor absoluto es la posicion
				printf("caracter '%c' inesperado en posicion %d\n",linea[-p-1],-p);
			else
				printf("%s\n",estados[p]);
		}
	}while(true);
	return 0;
}