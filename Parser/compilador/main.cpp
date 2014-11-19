#include <string>
#include <cmath>
#include <iostream>
#include <fstream>
#include <map>
#include <stack>
#include <cctype>
using namespace std;
const int X=-1, AC=-2;
stack<string> pila;
int temporales;
int etiquetas;
map<string, string> tabSim;
ofstream codIntermedio;
bool error;
const int cantFunc=17;
const string funciones[] = {"sin", "cos", "tan", "sec", "csc", "cot", "log", "ln","exp", "tanh", "sinh", "cosh", "abs", "print", "println", "read", "readln"};
const string tiposDato[] = {"double", "int", "long", "bool", "void", "string", "char", "byte", "word"};
bool opx;
int G[][63]={
//	  0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f  g  h  i  j  k  l  m  n  o  p  q  r  s  t  u  v  w  x  y  z  '  "  +  -  *  /  >  <  %  =  .  ^  &  |  \  $  _  !     (  )  {  }  [  ]  , \t
	{ 1,11,11,11,11,11,11,11,11,11,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,48,41,15,16,31,32,28,29,33,30,21,36,35,34, X,38,39,57, X,58,58,58,58,58,58,58, 0},//0
	{11,11,11,11,11,11,11,11,11,11, X,10, X, X,22,26, X, X, X, X, X, X, X, X, 7, X, X, X, X, X, X, X, X, 4, X, X, X, X,AC,AC,AC,AC,AC,AC,AC,AC,21,AC,AC,AC, X, X, X,AC, X, X,AC, X, X, X,AC,AC,AC},//1
	{ 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, 3, 3, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,AC},//2
	{ 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,AC},//3
	{ 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,AC,AC,AC,AC,AC,AC,AC,AC, X,AC,AC,AC, X, X, X,AC, X, X,AC, X, X, X,AC,AC,AC},//4
	{ 7, 7, 7, 7, 7, 7, 7, 7, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, 6, 6, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,AC},//5
	{ 7, 7, 7, 7, 7, 7, 7, 7, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,AC},//6
	{ 7, 7, 7, 7, 7, 7, 7, 7, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,AC,AC,AC,AC,AC,AC,AC,AC, X,AC,AC,AC, X, X, X,AC, X, X,AC, X, X, X,AC,AC,AC},//7
	{10,10, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, 9, 9, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,AC},//8
	{10,10, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,AC},//9
	{10,10, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,AC,AC,AC,AC,AC,AC,AC,AC, X,AC,AC,AC, X, X, X,AC, X, X,AC, X, X, X,AC,AC,AC},//10
	{11,11,11,11,11,11,11,11,11,11, X, X, X, X,22,26, X, X, X, X, X,12, X, X, X, X, X, X, X, X,13, X, X, X, X, X, X, X,AC,AC,AC,AC,AC,AC,AC,AC,21,AC,AC,AC, X, X, X,AC, X, X,AC, X, X, X,AC,AC,AC},//11
	{ X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,14, X, X, X, X, X, X, X,AC,AC,AC,AC,AC,AC,AC,AC, X,AC,AC,AC, X, X, X,AC, X, X,AC, X, X, X,AC,AC,AC},//12
	{ X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,AC,AC,AC,AC,AC,AC,AC,AC, X,AC,AC,AC, X, X, X,AC, X, X,AC, X, X, X,AC,AC,AC},//13
	{ X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,AC,AC,AC,AC,AC,AC,AC,AC, X,AC,AC,AC, X, X, X,AC, X, X,AC, X, X, X,AC,AC,AC},//14
	{AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,17, X, X, X, X, X, X,18, X, X, X, X, X,AC,AC, X, X,AC, X, X, X, X,AC,AC,AC},//15
	{AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC, X,17, X, X, X, X, X,18, X, X, X, X, X,AC,AC, X, X,AC, X, X, X,AC,AC,AC,AC},//16
	{AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC, X, X, X, X, X, X, X, X, X, X, X,AC,AC, X, X,AC,AC, X, X,AC, X, X,AC},//17
	{AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC, X, X, X, X, X, X, X, X, X, X, X,AC,AC, X, X,AC, X, X, X,AC, X, X,AC},//18
	{20,20,20,20,20,20,20,20,20,20, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,AC},//19
	{20,20,20,20,20,20,20,20,20,20, X, X, X, X,22,26, X, X, X, X, X,27, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,AC,AC,AC,AC,AC,AC,AC,AC,21,AC,AC,AC, X, X, X,AC, X, X,AC, X, X, X,AC,AC,AC},//20
	{40,40,40,40,40,40,40,40,40,40, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,AC},//21
	{24,24,24,24,24,24,24,24,24,24, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,23,23, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,AC},//22
	{24,24,24,24,24,24,24,24,24,24, X, X, X, X, X,26, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,AC,AC,AC,AC,AC,AC,AC,AC, X,AC,AC,AC, X, X, X,AC, X, X,AC, X, X, X,AC,AC,AC},//23
	{25,25,25,25,25,25,25,25,25,25, X, X, X, X, X,26, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,AC,AC,AC,AC,AC,AC,AC,AC, X,AC,AC,AC, X, X, X,AC, X, X,AC, X, X, X,AC,AC,AC},//24
	{ X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,26, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,AC,AC,AC,AC,AC,AC,AC,AC, X,AC,AC,AC, X, X, X,AC, X, X,AC, X, X, X,AC,AC,AC},//25
	{ X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,AC,AC,AC,AC,AC,AC,AC,AC, X,AC,AC,AC, X, X, X,AC, X, X,AC, X, X, X,AC,AC,AC},//26
	{ X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,AC,AC,AC,AC,AC,AC,AC,AC, X,AC,AC,AC, X, X, X,AC, X, X,AC, X, X, X,AC,AC,AC},//27
	{AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC, X, X, X, X,33, X, X,37, X, X, X, X, X,AC,AC, X, X,AC, X, X, X, X, X, X,AC},//28
	{AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC, X, X, X, X,37,33, X,37, X, X, X, X, X,AC,AC, X, X,AC, X, X, X, X, X, X,AC},//29
	{AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC, X, X, X, X, X, X, X,37, X, X, X, X, X,AC,AC, X, X,AC, X, X, X, X, X, X,AC},//30
	{AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC, X, X,32, X, X, X, X,18, X, X, X, X, X,AC,AC, X, X,AC, X, X, X, X, X, X,AC},//31
	{AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC, X, X, X, X, X, X, X,18, X, X, X, X, X,AC,AC, X, X,AC, X, X, X, X, X, X,AC},//32
	{AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC, X, X, X, X, X, X, X,18, X, X, X, X, X,AC,AC, X, X,AC, X, X, X, X, X, X,AC},//33
	{AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC, X, X, X, X, X, X, X,18, X, X, X,37, X,AC,AC, X, X,AC, X, X, X, X, X, X,AC},//34
	{AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC, X, X, X, X, X, X, X,18, X, X,37, X, X,AC,AC, X, X,AC, X, X, X, X, X, X,AC},//35
	{AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC, X, X, X, X, X, X, X,18, X, X, X, X, X,AC,AC, X, X,AC, X, X, X, X, X, X,AC},//36
	{AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC, X, X, X, X, X, X, X, X, X, X, X, X, X,AC,AC, X, X,AC, X, X, X, X, X, X,AC},//37
	{AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC, X, X, X, X, X, X, X, X, X, X, X, X, X,AC,AC, X, X,AC, X, X, X, X, X, X,AC},//38
	{39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39, X, X,AC,AC,AC,AC,AC,AC,AC,AC, X,AC,AC,AC, X,39,39,AC, X,AC,AC, X, X,AC, X,AC,AC},//39
	{40,40,40,40,40,40,40,40,40,40, X, X, X, X,22,26, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,AC,AC,AC,AC,AC,AC,AC,AC, X,AC,AC,AC, X, X, X,AC, X,AC, X, X, X, X,AC, X,AC},//40
	{41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,43,41,41,41,41,41,41,41,41,41,41,41,41,42,41,41,41,41,41,41,41,41,41,41,41,41},//41
	{44,44,45,46,46,46,46,46,46,46,41,41, X, X, X,41, X, X, X, X, X, X, X,41, X, X, X,41, X,41, X,41, X, X, X, X,41,41, X, X, X, X, X, X, X, X, X, X, X, X,41, X, X, X, X, X, X, X, X, X, X, X,AC},//42
	{ X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,AC, X,AC, X,AC,AC, X,AC, X, X, X, X, X, X, X,AC, X, X,AC, X, X,AC,AC,AC,AC},//43
	{46,46,46,46,46,46,46,46,46,46,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,43,41,41,41,41,41,41,41,41,41,41,41,41,42,41,41,41,41,41,41,41,41,41,41,41,41},//44
	{46,46,46,46,46,47,49,49,49,49,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,43,41,41,41,41,41,41,41,41,41,41,41,41,42,41,41,41,41,41,41,41,41,41,41,41,41},//45
	{41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,43,41,41,41,41,41,41,41,41,41,41,41,41,42,41,41,41,41,41,41,41,41,41,41,41,41},//46
	{41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,43,41,41,41,41,41,41,41,41,41,41,41,41,42,41,41,41,41,41,41,41,41,41,41,41,41},//47
	{49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49, X,49,49,49,49,49,49,49,49,49,49,49,49,49,51,49,49,49,49,49,49,49,49,49,49,49,49},//48
	{ X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,50, X,AC, X,AC, X,AC,AC, X,AC, X, X, X, X, X, X, X,AC, X, X,AC, X, X,AC,AC,AC,AC},//49
	{ X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,50, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,AC},//50
	{53,53,52,54,54,54,54,54,54,54,49,49, X, X, X,49, X, X, X, X, X, X, X,49, X, X, X,49, X,49, X,49, X, X, X, X,49,49, X, X, X, X, X, X, X, X, X, X, X, X,49, X, X, X, X, X, X, X, X, X, X, X,AC},//51
	{54,54,54,54,54,55,49,49,49,49, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,50, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,AC},//52
	{54,54,54,54,54,54,54,54,54,54, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,50, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,AC},//53
	{49,49,49,49,49,49,49,49,49,49, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,50, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,AC},//54
	{49,49,49,49,49,49, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,50, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,AC},//55
	{19,19,19,19,19,19,19,19,19,19, X,10, X, X,22, X, X, X, X, X, X, X, X, X, 7, X, X, X, X, X, X, X, X, 4, X, X, X, X, X, X, X, X, X, X, X, X,21, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,AC},//56
	{AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC, X, X, X, X, X, X, X,37, X, X, X, X, X,AC,AC, X, X,AC, X, X, X, X, X, X,AC},//57
	{AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC,AC},//58
};
bool esFuncion(const string& s) {
	for(int i=0; i < cantFunc; i++) 
		if(funciones[i]==s) 
			return true;
	return false;
}
bool esTipo(const string& s){
	for(int i=0;i<9;i++){
		if(s==tiposDato[i]){
			return true;
		}
	}
	return false;
}

int tipo(char c){
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
		case '(':
				return 55;
		case ')':
				return 56;
		case '{':
				return 57;
		case '}':
				return 58;
		case '[':
				return 59;
		case ']':
				return 60;
		case ',':
				return 61;
		case ' ': case '\t':
				return 62;
		default:
				return 54;
	}
}
string estados[]={
	"vacio",
	"const",
	"Hexadecimal incompleto",
	"Hexadecimal incompleto",
	"const",
	"Octal incompleto",
	"Octal incompleto",
	"const",
	"Binario incompleto",
	"Binario incompleto",
	"const",
	"const",
	"const",
	"const",
	"const",
	"op",
	"op",
	"++",
	"op",
	"Entero con signo incompleto",
	"const",
	"Real incompleto",
	"Real incompleto",
	"const",
	"const",
	"const",
	"const",
	"const",
	"op",
	"op",
	"op",
	"op",
	"op",
	"op",
	"op",
	"op",
	"op",
	"op",
	"op",
	"id",
	"const",
	"Cadena incompleta",
	"Cadena incompleta",
	"const_str",
	"Cadena incompleta",
	"Cadena incompleta",
	"Cadena incompleta",
	"Cadena incompleta",
	"Caracter incompleto",
	"Caracter incompleto",
	"const",
	"Caracter incompleto",
	"Caracter incompleto",
	"Caracter incompleto",
	"Caracter incompleto",
	"Caracter incompleto",
	"Caracter incompleto",
	"op",
	"("
};

string instruccion;
void evalExp();
void evalua();
int idx;
string token, lexema;

void leeToken(){
	lexema="";
	if(instruccion[idx]=='\n'){
		token=lexema="\n";
		idx++;
		return;
	}
	int estado = 0, estAnt=0;
	while(instruccion[idx]==' ' or instruccion[idx]=='\t'){
		idx++;
	}
	while( idx < instruccion.size() and estado != X and estado != AC){
		char c = instruccion[idx++];
		int t = tipo(c);
		if( t >= 0 and estado != X and estado != AC){
			estAnt = estado;
			estado = (c=='\n'?AC:G[estado][t]);
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
	token = estados[estAnt];
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
			int val;
			if(tabSim.find(lexema)==tabSim.end()){
				cout<<"La variable '"<<lexema<<"' no ha sido definida"<<endl;
				error=true;
				pila.push(lexema);
			}else{
				pila.push(lexema);
			}
			opx=true;
			leeToken();
		}else{
			leeToken();
			if(lexema!="("){ 
				cout<<"Error, Se esperaba abrir parentesis ("<<endl;
				error=true;
			}
			leeToken();
			string arg=lexema;
			evalExp();
			if(lexema!=")") {
				error=true;
				cout<<"Error, Se esperaba cerrar parentesis )"<<endl;
			}
			leeToken();
			codIntermedio<<"#t"<<to_string(temporales)+"="+fn+"("+arg+")"<<endl;
			pila.push(string("#t")+to_string(temporales++));
			opx=true;
		}
	}else if(token=="const" or token=="const_str"){
		pila.push(lexema);
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
		string val=pila.top();
		codIntermedio<<"#t"<<temporales<<"=-"<<val<<endl;
		pila.pop();
		pila.push(string("#t")+to_string(temporales++));
	}
}

void evalPotencia(){
	string operador="";
	do{
		if(lexema=="**"){
			operador=lexema;
			leeToken();
		}
		evalSigno(); 
		if(operador=="**"){
			string izq = pila.top();
			pila.pop();
			string der=pila.top();
			pila.pop();
			codIntermedio<<"#t"<<temporales<<" = "<<der<<" ** "<<izq<<endl;
			pila.push(string("#t")+to_string(temporales++));
		}
	}while(lexema=="**");
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
			string der = pila.top();
			pila.pop();
			string izq = pila.top();
			pila.pop();
			codIntermedio<<"#t"<<temporales<<" = "<<izq<<" "<<operador<<" "<<der<<endl;
			pila.push(string("#t")+to_string(temporales++));
		}
	}while(lexema=="*" or lexema=="/" or lexema=="%");
}

void evalSuma(){
	string operador="";
	do{
		if(lexema=="+" or lexema=="-"){
			operador=lexema;
			leeToken();
		}
		evalMulti(); 
		if(operador=="+" or operador=="-"){
			string der = pila.top();
			pila.pop();
			string izq=pila.top();
			pila.pop();
			codIntermedio<<"#t"<<temporales<<" = "<<izq<<" "<<operador<<" "<<der<<endl;
			pila.push(string("#t")+to_string(temporales++));
		}
	}while(lexema=="+" or lexema=="-");
}

void evalBits(){
	string operador="";
	do{
		if(lexema=="|" or lexema=="&" or lexema=="^" or lexema=="<<" or lexema==">>"){
			operador=lexema;
			leeToken();
		}
		evalSuma(); 
		if(operador=="|" or operador=="&" or operador=="^" or operador=="<<" or operador==">>"){
			string der = pila.top();
			pila.pop();
			string izq=pila.top();
			pila.pop();
			codIntermedio<<"#t"<<temporales<<" = "<<izq<<" "<<operador<<" "<<der<<endl;
			pila.push(string("#t")+to_string(temporales++));
		}
	}while(lexema=="|" or lexema=="&" or lexema=="^" or lexema=="<<" or lexema==">>");
}

void evalLogico(){
	string operador="";
	do{
		if(lexema=="<" or lexema==">" or lexema=="==" or lexema=="<=" or lexema==">=" or lexema=="<>" or lexema=="!="){
			operador=lexema;
			leeToken();
		}
		evalBits(); 
		if(operador=="<" or operador==">" or operador=="==" or operador=="<=" or operador==">=" or operador=="<>" or operador=="!="){
			string der = pila.top();
			pila.pop();
			string izq=pila.top();
			pila.pop();
			codIntermedio<<"#t"<<temporales<<" = "<<izq<<" "<<operador<<" "<<der<<endl;
			pila.push(string("#t")+to_string(temporales++));
		}
	}while(lexema=="<" or lexema==">" or lexema=="==" or lexema=="<=" or lexema==">=" or lexema=="<>" or lexema=="!=");
}

void evalConjuncion(){
	string operador="";
	do{
		if(lexema=="and" or lexema=="or" or lexema=="&&" or lexema=="||"){
			operador=lexema;
			leeToken();
		}
		evalLogico(); 
		if(operador=="and" or operador=="or" or operador=="&&" or operador=="||"){
			string der = pila.top();
			pila.pop();
			string izq=pila.top();
			pila.pop();
			//cout<<izq<<operador<<der<<endl;
			codIntermedio<<"#t"<<temporales<<" = "<<izq<<" "<<operador<<" "<<der<<endl;
			pila.push(string("#t")+to_string(temporales++));
		}
		//cout<<"Lex="<<lexema<<endl;
	}while(lexema=="and" or lexema=="or" or lexema=="&&" or lexema=="||");
}

void evalExp(){
	string operador="";
	do{
		if(lexema=="=" or lexema=="+=" or lexema=="-=" or lexema=="*=" or lexema=="/=" or lexema=="%=" or lexema=="**=" or lexema=="<<=" or lexema==">>=" or lexema=="&=" or lexema=="|=" or lexema=="^=" and opx){
			operador=lexema;
			leeToken();
		}
		evalConjuncion(); 
		if(operador=="=" or operador=="+=" or operador=="-=" or operador=="*=" or operador=="/=" or operador=="%=" or operador=="**=" or operador=="<<=" or operador==">>=" or operador=="&=" or operador=="|=" or operador=="^=" and opx){
			string der = pila.top();
			pila.pop();
			string izq=pila.top();
			pila.pop();
			//cout<<izq<<operador<<der<<endl;
			if(operador=="="){
				codIntermedio<<izq<<" "<<operador<<" "<<der<<endl;
			}else if(operador=="<<=" or operador==">>=" or operador=="**="){
				codIntermedio<<izq<<" = "<<izq<<" "<<operador[0]<<operador[1]<<" "<<der<<endl;
			}else{
				codIntermedio<<izq<<" = "<<izq<<" "<<operador[0]<<" "<<der<<endl;
			}
			pila.push(izq);
		}
		//cout<<"Lex="<<lexema<<endl;
	}while(lexema=="=" or lexema=="+=" or lexema=="-=" or lexema=="*=" or lexema=="/=" or lexema=="%=" or lexema=="**=" or lexema=="<<=" or lexema==">>=" or lexema=="&=" or lexema=="|=" or lexema=="^=");
	if(lexema=="\n"){
		leeToken();
	}
}

void evalIf(){
	if(lexema=="if"){
		leeToken();
		int et=etiquetas++;
		codIntermedio<<"Et_Ini_"<<et<<":\t";
		if(lexema=="("){
			leeToken();
			evalExp();
			codIntermedio<<"if !"<<pila.top()<<" then goto "<<"Et_fin_"<<et<<endl;
			if(lexema==")"){
				leeToken();
				if(lexema=="\n"){
					leeToken();
					while(lexema!="endif"){
						while(lexema=="\n"){
							leeToken();
						}
						evalua();
					}
					codIntermedio<<"Et_fin_"<<et<<"\t empty"<<endl;
				}
			}
		}
	}
}

void evalFor(){
	if(lexema=="for"){
		leeToken();
		int et=etiquetas++;
		if(lexema=="("){
			leeToken();
			evalExp();
			if(lexema==","){
				leeToken();
				codIntermedio<<"Et_Ini_"<<et<<":\t";
				evalExp();
				codIntermedio<<"if !"<<pila.top()<<" then goto "<<"Et_fin_"<<et<<endl;
				codIntermedio<<"goto Et_med_"<<et<<endl;
				if(lexema==","){
					leeToken();
					codIntermedio<<"Et_med2_"<<et<<":\t";
					evalExp();
					codIntermedio<<"goto Et_Ini_"<<et<<endl;
					if(lexema==")"){
						codIntermedio<<"Et_med_"<<et<<endl;
						leeToken();
						if(lexema=="\n"){
							leeToken();
							while(lexema=="\n"){
								leeToken();
							}
							while(lexema!="endfor"){
								evalua();
								while(lexema=="\n"){
									leeToken();
								}
							}
							leeToken();
							codIntermedio<<"goto Et_med2_"<<et<<endl;
							codIntermedio<<"Et_fin_"<<et<<"\t empty"<<endl;
						}
					}
				}
			}

		}
	}
}

void evalWhile(){
	if(lexema=="while"){
		leeToken();
		int et=etiquetas++;
		codIntermedio<<"Et_Ini_"<<et<<":\t";
		if(lexema=="("){
			leeToken();
			evalExp();
			codIntermedio<<"if !"<<pila.top()<<" then goto "<<"Et_fin_"<<et<<endl;
			if(lexema==")"){
				leeToken();
				if(lexema=="\n"){
					leeToken();
					while(lexema!="endwhile"){
						while(lexema=="\n"){
							leeToken();
						}
						evalua();
					}
					codIntermedio<<"goto Et_Ini_"<<et<<endl;
					codIntermedio<<"Et_fin_"<<et<<"\t empty"<<endl;
				}
			}
		}
	}
}

void evalDeclaracion(){
	if(esTipo(lexema)){
		string tipoDato=lexema;
		leeToken();
		if(token=="id"){
			tabSim[lexema]=tipoDato;
		}
		evalExp();
		while(lexema==","){
			leeToken();
			if(token=="id"){
				tabSim[lexema]=tipoDato;
			}
			evalExp();
		}
	}
}

void evalua(){
	pila=stack<string>();
	opx=false;
	while(isspace(instruccion[idx])){
		idx++;
	}
	if(instruccion=="")
		return;
	//leeToken();
	/*if(lexema=="leer"){
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
				return;
			}
		}
	}else*/
	if(lexema=="if"){
		evalIf();
	}else if(lexema=="while"){
		evalWhile();
	}else if(lexema=="for"){
		evalFor();
	}else if(esTipo(lexema)){
		evalDeclaracion();
	}else{
		evalExp();
	}
}

int main(int argc, char**argv){
	if(argc>=2){
		ifstream arch(argv[1]);
		string nomArch=argv[1];
		codIntermedio.open(nomArch.substr(0,nomArch.rfind('.'))+".txt");
		instruccion=string((istreambuf_iterator<char>(arch)),(istreambuf_iterator<char>()));	
		leeToken();
		while(idx<instruccion.size()){
			while(lexema=="\n"){
				leeToken();
			}
			evalua();
		}
		codIntermedio.close();
	}else{
		cout<<"No hay archivo de entrada"<<endl;
	}
	return 0;
}