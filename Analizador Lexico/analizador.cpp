#include <iostream>
#include "trie.h"
#define X -1
using namespace std;
int G[][60]={
	{ 1,11,11,11,11,11,11,11,11,11,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,48,41,15,16,31,32,28,29,33,30,21,36,35,34, X,38,39,57, X},//0
	{11,11,11,11,11,11,11,11,11,11, X, X, X, X,22,26, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,21, X, X, X, X, X, X, X, X},//1
	{ 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, 3, 3, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X},//2
	{ 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X},//3
	{ 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X},//4
	{ 7, 7, 7, 7, 7, 7, 7, 7, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, 6, 6, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X},//5
	{ 7, 7, 7, 7, 7, 7, 7, 7, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X},//6
	{ 7, 7, 7, 7, 7, 7, 7, 7, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X},//7
	{10,10, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, 9, 9, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X},//8
	{10,10, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X},//9
	{10,10, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X},//10
	{11,11,11,11,11,11,11,11,11,11, X, X, X, X,22,26, X, X, X, X, X,12, X, X, X, X, X, X, X, X,13, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,21, X, X, X, X, X, X, X, X},//11
	{ X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,14, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X},//12
	{ X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X},//13
	{ X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X},//14
	{56,19,19,19,19,19,19,19,19,19, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,17, X, X, X, X, X, X,18, X, X, X, X, X, X, X, X, X},//15
	{56,19,19,19,19,19,19,19,19,19, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,17, X, X, X, X, X,18, X, X, X, X, X, X, X, X, X},//16
	{ X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X},//17
	{ X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X},//18
	{20,20,20,20,20,20,20,20,20,20, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X},//19
	{20,20,20,20,20,20,20,20,20,20, X, X, X, X,22,26, X, X, X, X, X,27, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,21, X, X, X, X, X, X, X, X},//20
	{40,40,40,40,40,40,40,40,40,40, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X},//21
	{24,24,24,24,24,24,24,24,24,24, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,23,23, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X},//22
	{24,24,24,24,24,24,24,24,24,24, X, X, X, X, X,26, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X},//23
	{25,25,25,25,25,25,25,25,25,25, X, X, X, X, X,26, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X},//24
	{ X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,26, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X},//25
	{ X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X},//26
	{ X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X},//27
	{ X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,33, X, X,37, X, X, X, X, X, X, X, X, X},//28
	{ X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,33, X,37, X, X, X, X, X, X, X, X, X},//29
	{ X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,37, X, X, X, X, X, X, X, X, X},//30
	{ X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,18, X, X, X, X, X, X, X, X, X},//31
	{ X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,18, X, X, X, X, X, X, X, X, X},//32
	{ X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,18, X, X, X, X, X, X, X, X, X},//33
	{ X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,18, X, X, X,37, X, X, X, X, X},//34
	{ X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,18, X, X,37, X, X, X, X, X, X},//35
	{ X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,18, X, X, X, X, X, X, X, X, X},//36
	{ X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X},//37
	{ X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X},//38
	{39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,39,39, X, X},//39
	{40,40,40,40,40,40,40,40,40,40, X, X, X, X,22,26, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X},//40
	{41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,43,41,41,41,41,41,41,41,41,41,41,41,41,42,41,41,41,41},//41
	{44,44,45,46,46,46,46,46,46,46,41,41, X, X, X,41, X, X, X, X, X, X, X,41, X, X, X,41, X,41, X,41, X, X, X, X,41,41, X, X, X, X, X, X, X, X, X, X, X, X,41, X, X, X, X},//42
	{ X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X},//43
	{46,46,46,46,46,46,46,46,46,46,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,43,41,41,41,41,41,41,41,41,41,41,41,41,42,41,41,41,41},//44
	{46,46,46,46,46,47,49,49,49,49,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,43,41,41,41,41,41,41,41,41,41,41,41,41,42,41,41,41,41},//45
	{41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,43,41,41,41,41,41,41,41,41,41,41,41,41,42,41,41,41,41},//46
	{41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,43,41,41,41,41,41,41,41,41,41,41,41,41,42,41,41,41,41},//47
	{49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49, X,49,49,49,49,49,49,49,49,49,49,49,49,49,51,49,49,49,49},//48
	{ X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,50, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X},//49
	{ X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,50, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X},//50
	{53,53,52,54,54,54,54,54,54,54,49,49, X, X, X,49, X, X, X, X, X, X, X,49, X, X, X,49, X,49, X,49, X, X, X, X,49,49, X, X, X, X, X, X, X, X, X, X, X, X,49, X, X, X, X},//51
	{54,54,54,54,54,55,49,49,49,49, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,50, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X},//52
	{54,54,54,54,54,54,54,54,54,54, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,50, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X},//53
	{49,49,49,49,49,49,49,49,49,49, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,50, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X},//54
	{49,49,49,49,49,49, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,50, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X},//55
	{19,19,19,19,19,19,19,19,19,19, X,10, X, X,22, X, X, X, X, X, X, X, X, X, 7, X, X, X, X, X, X, X, X, 4, X, X, X, X, X, X, X, X, X, X, X, X,21, X, X, X, X, X, X, X, X},//56
	{ X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,37, X, X, X, X, X, X, X, X, X},//57
//	  0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f  g  h  i  j  k  l  m  n  o  p  q  r  s  t  u  v  w  x  y  z  '  "  +  -  *  /  >  <  %  =  .  ^  &  |  \  $  _  !
};



string estados[]={
	"Cadena Vacia",
	"Entero",
	"Hexadecimal incompleto",
	"Hexadecimal incompleto",
	"Hexadecimal",
	"Octal incompleto",
	"Octal incompleto",
	"Octal",
	"Binario incompleto",
	"Binario incompleto",
	"Binario",
	"Entero",
	"Entero largo",
	"Entero sin signo",
	"Entero largo sin signo",
	"Operador aritmetico",
	"Operador aritmetico",
	"Operador Incremento/Decremento",
	"Operador Asignacion",
	"Entero con signo incompleto",
	"Entero con signo",
	"Real incompleto",
	"Real incompleto",
	"Real",
	"Real",
	"Real",
	"Real",
	"Entero con signo largo",
	"Operador relacional",
	"Operador relacional",
	"Asignacion",
	"Operador aritmetico",
	"Operador aritmetico",
	"Operador aritmetico",
	"Operador binario",
	"Operador binario",
	"Operador binario",
	"Operador binario",
	"Operador binario",
	"Identificador",
	"Real",
	"Cadena incompleta",
	"Cadena incompleta",
	"Cadena",
	"Cadena incompleta",
	"Cadena incompleta",
	"Cadena incompleta",
	"Cadena incompleta",
	"Caracter incompleto",
	"Caracter incompleto",
	"Caracter",
	"",
	"",
	"",
	"",
	"",
	"",
	"Operador logico",
};

int hash(char c){
	switch(c){
		case '0':
				return 0;
		case '1':
				return 1;
		case '2':
				return 2;
		case '3':
				return 3;
		case '4':
				return 4;
		case '5':
				return 5;
		case '6':
				return 6;
		case '7':
				return 7;
		case '8':
				return 8;
		case '9':
				return 9;
		case 'a': case 'A':
				return 10;
		case 'b': case 'B':
				return 11;
		case 'c': case 'C':
				return 12;
		case 'd': case 'D':
				return 13;
		case 'e': case 'E':
				return 14;
		case 'f': case 'F':
				return 15;
		case 'g': case 'G':
				return 16;
		case 'h': case 'H':
				return 17;
		case 'i': case 'I':
				return 18;
		case 'j': case 'J':
				return 19;
		case 'k': case 'K':
				return 20;
		case 'l': case 'L':
				return 21;
		case 'm': case 'M':
				return 22;
		case 'n': case 'N':
				return 23;
		case 'o': case 'O':
				return 24;
		case 'p': case 'P':
				return 25;
		case 'q': case 'Q':
				return 26;
		case 'r': case 'R':
				return 27;
		case 's': case 'S':
				return 28;
		case 't': case 'T':
				return 29;
		case 'u': case 'U':
				return 30;
		case 'v': case 'V':
				return 31;
		case 'w': case 'W':
				return 32;
		case 'x': case 'X':
				return 33;
		case 'y': case 'Y':
				return 34;
		case 'z': case 'Z':
				return 35;
		case '\'':
				return 36;
		case '"':
				return 37;
		case '+':
				return 38;
		case '-':
				return 39;
		case '*':
				return 40;
		case '/':
				return 41;
		case '>':
				return 42;
		case '<':
				return 43;
		case '%':
				return 44;
		case '=':
				return 45;
		case '.':
				return 46;
		case '^':
				return 47;
		case '&':
				return 48;
		case '|':
				return 49;
		case '\\':
				return 50;
		case '$':
				return 51;
		case '_':
				return 52;
		case '!':
				return 53;
		default:
				return 54;
	}
}


int evaluar(const char *cad){
	int estado=0; //Contador de estado
	int pos=1; //Contador de posiciones recorridas
	
	while(*cad!='\0'){ //hasta llegar al fin de cadena
		int in=hash(*cad); //Obtiene la columna de la tabla con la funcion hash
		//cout<<estado<<endl;
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
	string linea;
	trie palabrasReservadas;
	palabrasReservadas.agregarPalabra("int");
	palabrasReservadas.agregarPalabra("long");
	palabrasReservadas.agregarPalabra("uint");
	palabrasReservadas.agregarPalabra("ulong");
	palabrasReservadas.agregarPalabra("for");
	palabrasReservadas.agregarPalabra("if");
	palabrasReservadas.agregarPalabra("else");
	palabrasReservadas.agregarPalabra("while");
	palabrasReservadas.agregarPalabra("do");
	palabrasReservadas.agregarPalabra("float");
	palabrasReservadas.agregarPalabra("char");
	palabrasReservadas.agregarPalabra("string");
	palabrasReservadas.agregarPalabra("void");
	palabrasReservadas.agregarPalabra("return");
	palabrasReservadas.agregarPalabra("break");
	palabrasReservadas.agregarPalabra("switch");
	palabrasReservadas.agregarPalabra("case");
	palabrasReservadas.agregarPalabra("foreach");
	palabrasReservadas.agregarPalabra("const");
	palabrasReservadas.agregarPalabra("not");
	palabrasReservadas.agregarPalabra("and");
	palabrasReservadas.agregarPalabra("or");
	do{
		getline(cin,linea); //Leer la linea hasta el salto de linea
		if(palabrasReservadas.existe(linea.c_str())) //Verificar si esta dentro del arbol
			cout<<"Palabra Reservada"<<endl;
		else{
			int p=evaluar(linea.c_str()); //Evalua la cadena, recibe el estado final
			if(p<0) //cuando el numero que recibe es negativo, el error es que encontro un caracter que no iba, el valor absoluto es la posicion
				cout<<"caracter '"<<linea[-p-1]<<"' inesperado en posicion "<<-p<<endl;
			else
				cout<<estados[p]<<endl;
		}
	}while(true);
}