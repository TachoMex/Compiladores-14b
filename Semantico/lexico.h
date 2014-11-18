#define X -1
#define B -2
trie palabrasReservadas;

class token{
	public:
		string tipo;
		string tok;
		int linea;
		int numero;
	token(){

	}
	token(const string& a,const string &b,int l, int n){
		tipo=a;
		tok=b;
		linea = l;
		numero = n;
	}
};
vector<token> tokens;

string estados[]={
	"",
	"%D",
	"Hexadecimal incompleto",
	"Hexadecimal incompleto",
	"%H",
	"Octal incompleto",
	"Octal incompleto",
	"%O",
	"Binario incompleto",
	"Binario incompleto",
	"%B",
	"%D",
	"%L",
	"UI",
	"UL",
	"OA",
	"OA",
	"++",
	"O=",
	"Entero con signo incompleto",
	"UI",
	"Real incompleto",
	"Real incompleto",
	"FL",
	"FL",
	"FL",
	"FL",
	"%L",
	"Ol",
	"Ol",
	"O=",
	"OA",
	"OA",
	"OA",
	"OB",
	"OB",
	"OB",
	"OB",
	"OB",
	"ID",
	"FL",
	"Cadena incompleta",
	"Cadena incompleta",
	"ST",
	"Cadena incompleta",
	"Cadena incompleta",
	"Cadena incompleta",
	"Cadena incompleta",
	"Caracter incompleto",
	"Caracter incompleto",
	"CH",
	"Caracter incompleto",
	"Caracter incompleto",
	"Caracter incompleto",
	"Caracter incompleto",
	"Caracter incompleto",
	"Caracter incompleto",
	"OL",
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

int G[][63]={
//	  0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f  g  h  i  j  k  l  m  n  o  p  q  r  s  t  u  v  w  x  y  z  '  "  +  -  *  /  >  <  %  =  .  ^  &  |  \  $  _  !     (  )  {  }  [  ]  , \t
	{ 1,11,11,11,11,11,11,11,11,11,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,48,41,15,16,31,32,28,29,33,30,21,36,35,34, X,38,39,57, X,58,58,58,58,58,58,58, 0},//0
	{11,11,11,11,11,11,11,11,11,11, X,10, X, X,22,26, X, X, X, X, X, X, X, X, 7, X, X, X, X, X, X, X, X, 4, X, X, X, X, B, B, B, B, B, B, B, B,21, B, B, B, X, X, X, B, X, X, B, X, X, X, B, B, B},//1
	{ 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, 3, 3, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X},//2
	{ 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X},//3
	{ 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, B, B, B, B, B, B, B, B, X, B, B, B, X, X, X, B, X, X, B, X, X, X, B, B, X},//4
	{ 7, 7, 7, 7, 7, 7, 7, 7, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, 6, 6, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X},//5
	{ 7, 7, 7, 7, 7, 7, 7, 7, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X},//6
	{ 7, 7, 7, 7, 7, 7, 7, 7, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, B, B, B, B, B, B, B, B, X, B, B, B, X, X, X, B, X, X, B, X, X, X, B, B, B},//7
	{10,10, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, 9, 9, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X},//8
	{10,10, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X},//9
	{10,10, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, B, B, B, B, B, B, B, B, X, B, B, B, X, X, X, B, X, X, B, X, X, X, B, B, B},//10
	{11,11,11,11,11,11,11,11,11,11, X, X, X, X,22,26, X, X, X, X, X,12, X, X, X, X, X, X, X, X,13, X, X, X, X, X, X, X, B, B, B, B, B, B, B, B,21, B, B, B, X, X, X, B, X, X, B, X, X, X, B, B, B},//11
	{ X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,14, X, X, X, X, X, X, X, B, B, B, B, B, B, B, B, X, B, B, B, X, X, X, B, X, X, B, X, X, X, B, B, B},//12
	{ X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, B, B, B, B, B, B, B, B, X, B, B, B, X, X, X, B, X, X, B, X, X, X, B, B, B},//13
	{ X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, B, B, B, B, B, B, B, B, X, B, B, B, X, X, X, B, X, X, B, X, X, X, B, B, B},//14
	{ B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B,17, X, X, X, X, X, X,18, X, X, X, X, X, B, B, X, X, B, X, X, X, X, B, B, B},//15
//	  0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f  g  h  i  j  k  l  m  n  o  p  q  r  s  t  u  v  w  x  y  z  '  "  +  -  *  /  >  <  %  =  .  ^  &  |  \  $  _  !     (  )  {  }  [  ]  ,
	{ B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, X,17, X, X, X, X, X,18, X, X, X, X, X, B, B, X, X, B, X, X, X, B, B, B, B},//16
	{ B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, X, X, X, X, X, X, X, X, X, X, X, B, B, X, X, B, B, X, X, B, X, X, B},//17
	{ B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, X, X, X, X, X, X, X, X, X, X, X, B, B, X, X, B, X, X, X, B, X, X, B},//18
	{20,20,20,20,20,20,20,20,20,20, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X},//19
	{20,20,20,20,20,20,20,20,20,20, X, X, X, X,22,26, X, X, X, X, X,27, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, B, B, B, B, B, B, B, B,21, B, B, B, X, X, X, B, X, X, B, X, X, X, B, B, B},//20
	{40,40,40,40,40,40,40,40,40,40, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X},//21
	{24,24,24,24,24,24,24,24,24,24, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,23,23, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X},//22
	{24,24,24,24,24,24,24,24,24,24, X, X, X, X, X,26, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, B, B, B, B, B, B, B, B, X, B, B, B, X, X, X, B, X, X, B, X, X, X, B, B, B},//23
	{25,25,25,25,25,25,25,25,25,25, X, X, X, X, X,26, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, B, B, B, B, B, B, B, B, X, B, B, B, X, X, X, B, X, X, B, X, X, X, B, B, B},//24
	{ X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,26, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, B, B, B, B, B, B, B, B, X, B, B, B, X, X, X, B, X, X, B, X, X, X, B, B, B},//25
	{ X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, B, B, B, B, B, B, B, B, X, B, B, B, X, X, X, B, X, X, B, X, X, X, B, B, B},//26
	{ X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, B, B, B, B, B, B, B, B, X, B, B, B, X, X, X, B, X, X, B, X, X, X, B, B, B},//27
	{ B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, X, X, X, X,33, X, X,37, X, X, X, X, X, B, B, X, X, B, X, X, X, X, X, X, X},//28
	{ B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, X, X, X, X, X,33, X,37, X, X, X, X, X, B, B, X, X, B, X, X, X, X, X, X, X},//29
	{ B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, X, X, X, X, X, X, X,37, X, X, X, X, X, B, B, X, X, B, X, X, X, X, X, X, B},//30
//	  0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f  g  h  i  j  k  l  m  n  o  p  q  r  s  t  u  v  w  x  y  z  '  "  +  -  *  /  >  <  %  =  .  ^  &  |  \  $  _  !     (  )  {  }  [  ]  ,
	{ B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, X, X, X, X, X, X, X,18, X, X, X, X, X, B, B, X, X, B, X, X, X, X, X, X, X},//31
	{ B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, X, X, X, X, X, X, X,18, X, X, X, X, X, B, B, X, X, B, X, X, X, X, X, X, X},//32
	{ B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, X, X, X, X, X, X, X,18, X, X, X, X, X, B, B, X, X, B, X, X, X, X, X, X, X},//33
	{ B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, X, X, X, X, X, X, X,18, X, X, X,37, X, B, B, X, X, B, X, X, X, X, X, X, X},//34
	{ B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, X, X, X, X, X, X, X,18, X, X,37, X, X, B, B, X, X, B, X, X, X, X, X, X, X},//35
	{ B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, X, X, X, X, X, X, X,18, X, X, X, X, X, B, B, X, X, B, X, X, X, X, X, X, X},//36
	{ B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, X, X, X, X, X, X, X, X, X, X, X, X, X, B, B, X, X, B, X, X, X, X, X, X, B},//37
	{ B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, X, X, X, X, X, X, X, X, X, X, X, X, X, B, B, X, X, B, X, X, X, X, X, X, X},//38
	{39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39, X, X, B, B, B, B, B, B, B, B, X, B, B, B, X,39,39, B, X, B, B, X, X, B, X, B, B},//39
	{40,40,40,40,40,40,40,40,40,40, X, X, X, X,22,26, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, B, B, B, B, B, B, B, B, X, B, B, B, X, X, X, B, X, B, X, X, X, X, B, X, X},//40
	{41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,43,41,41,41,41,41,41,41,41,41,41,41,41,42,41,41,41,41,41,41,41,41,41,41,41,41},//41
	{44,44,45,46,46,46,46,46,46,46,41,41, X, X, X,41, X, X, X, X, X, X, X,41, X, X, X,41, X,41, X,41, X, X, X, X,41,41, X, X, X, X, X, X, X, X, X, X, X, X,41, X, X, X, X, X, X, X, X, X, X, X, X},//42
	{ X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, B, X, B, X, B, B, X, B, X, X, X, X, X, X, X, B, X, X, B, X, X, B, B, B, B},//43
	{46,46,46,46,46,46,46,46,46,46,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,43,41,41,41,41,41,41,41,41,41,41,41,41,42,41,41,41,41,41,41,41,41,41,41,41,41},//44
	{46,46,46,46,46,47,49,49,49,49,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,43,41,41,41,41,41,41,41,41,41,41,41,41,42,41,41,41,41,41,41,41,41,41,41,41,41},//45
//	  0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f  g  h  i  j  k  l  m  n  o  p  q  r  s  t  u  v  w  x  y  z  '  "  +  -  *  /  >  <  %  =  .  ^  &  |  \  $  _  !     (  )  {  }  [  ]  ,
	{41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,43,41,41,41,41,41,41,41,41,41,41,41,41,42,41,41,41,41,41,41,41,41,41,41,41,41},//46
	{41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,43,41,41,41,41,41,41,41,41,41,41,41,41,42,41,41,41,41,41,41,41,41,41,41,41,41},//47
	{49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49, X,49,49,49,49,49,49,49,49,49,49,49,49,49,51,49,49,49,49,49,49,49,49,49,49,49,49},//48
	{ X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,50, X, B, X, B, X, B, B, X, B, X, X, X, X, X, X, X, B, X, X, B, X, X, B, B, B, B},//49
	{ X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,50, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X},//50
	{53,53,52,54,54,54,54,54,54,54,49,49, X, X, X,49, X, X, X, X, X, X, X,49, X, X, X,49, X,49, X,49, X, X, X, X,49,49, X, X, X, X, X, X, X, X, X, X, X, X,49, X, X, X, X, X, X, X, X, X, X, X, X},//51
	{54,54,54,54,54,55,49,49,49,49, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,50, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X},//52
	{54,54,54,54,54,54,54,54,54,54, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,50, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X},//53
	{49,49,49,49,49,49,49,49,49,49, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,50, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X},//54
	{49,49,49,49,49,49, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,50, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X},//55
	{19,19,19,19,19,19,19,19,19,19, X,10, X, X,22, X, X, X, X, X, X, X, X, X, 7, X, X, X, X, X, X, X, X, 4, X, X, X, X, X, X, X, X, X, X, X, X,21, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X},//56
	{ B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, X, X, X, X, X, X, X,37, X, X, X, X, X, B, B, X, X, B, X, X, X, X, X, X, X},//57
//	  0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f  g  h  i  j  k  l  m  n  o  p  q  r  s  t  u  v  w  x  y  z  '  "  +  -  *  /  >  <  %  =  .  ^  &  |  \  $  _  !     (  )  {  }  [  ]  ,
	{ X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X},//58
};


int evaluar(const char *cad,int contLinea, const char * contChar){
	const char *ini = cad;
	int estado=0; //Contador de estado
	int pos=1; //Contador de posiciones recorridas
	int x;
	if((x=palabrasReservadas.prefijo(cad))!=-1){ //Verificar si esta dentro del arbol
			while(*cad==' ' or *cad=='\t'){
				cad++;
				x--;
			}
			tokens.push_back(token("PR",string(cad).substr(0,x),contLinea,(int)(cad - contChar)+1));
			return evaluar(cad+x,contLinea, contChar);
	}
	while(*cad!='\0'){ //hasta llegar al fin de cadena
		int in=hash(*cad); //Obtiene la columna de la tabla con la funcion hash
		//cout<<estado<<endl;
		if(estado==58){
			tokens.push_back(token("{}",string("")+*(cad-1),contLinea,(int)(cad - contChar)+1));
			return evaluar(cad,contLinea,contChar);
		}else
		if(in>=0){ //La funcion hash retorna negativo para caracteres no validos en C, si lo encuentra se detiene y sale
			int sig=G[estado][in]; //obtiene el estado siguiente
			if (sig==B){
				while(*ini==' ' or *ini=='\t'){
					ini++;
				}
				tokens.push_back(token(estados[estado],string(ini).substr(0,(int)(cad-ini)),contLinea,(int)(cad - contChar)+1));
				return evaluar(cad,contLinea,contChar);
			}
			else if(sig==X){ //Si llega a caracter inesperado, rompe el ciclo y retorna la posicion en la que encontro el error
				return -pos;
			}
			estado=sig;
		}else
			return -pos;
		cad++;
		pos++;
	}
	if(estado==58){
		tokens.push_back(token("{}",string("")+*(cad-1),contLinea,(int)(cad - contChar)+1));
		return 0;
	}else if(estado){
		while(*ini==' ' or *ini=='\t'){
			ini++;
		}
		tokens.push_back(token(estados[estado],string(ini).substr(0,(int)(cad-ini)),contLinea,(int)(cad - contChar)+1));
	}
	return estado;
}

