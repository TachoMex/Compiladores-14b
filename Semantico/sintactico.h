#include <stack>
#include <map>

map<string,string> tabsim;


class nodoArbol{
public: 
	string tipo;
	string lexema;
	vector<nodoArbol> hijos;
	bool error;
	nodoArbol(){
		tipo="";
		lexema="";	
	}

	void agrega(const nodoArbol& v){
		hijos.push_back(v);
	}

	void mostrar(int t){
		for(int i=0;i<t;i++)
			cout.put('-');
		cout<<lexema<<"{"<<endl;
		for(int i=0;i<hijos.size();i++){
			hijos[i].mostrar(t+1);
		}

		for(int i=0;i<t;i++)
			cout.put('-');
		cout<<"}"<<endl;
	}
};

int idx;
/*

	for(<exp>,<exp>,<exp){
		<instrucciones>
	}
	
	while(<exp>){
		<intrucciones>
	}
	
	if(<exp){
		<instrucciones>
	}else{
		<instrucciones>
	}
	
	<tipo> <lista sentencias left=right>
	<tipo>[] = [1,2,3,4]
	
	<tipo> <id>(<lista param>){
		<instrucciones>
	}
	
	<buffer> <lista ids>

	<id> = <right>

*/
void debug(string s=""){
	cout<<idx<<"::"<<tokens[idx].tok<<"--"<<tokens[idx].tipo<<s<<endl;
}
nodoArbol eval_exp();
nodoArbol eval_for();
nodoArbol eval_if();
nodoArbol eval_while();
nodoArbol eval_declaracion();
nodoArbol eval_bloque();
nodoArbol eval_multi();
nodoArbol eval_aritmetico();
nodoArbol eval_logico();
nodoArbol eval_unario();
nodoArbol eval_termino();


bool esOperador(const token& t){
	return t.tipo=="OA" or t.tipo=="OB" or t.tok=="and" or t.tok=="or" or t.tipo=="O=" or t.tipo=="Ol";
}

bool esValor(const token& t){
	if(t.tipo=="ID"){
		if(not tabsim.count(t.tok)){
			cout<<"La variable "<<t.tok<<" No ha sido declarada"<<endl;
		}
	}
	return t.tipo=="%D" or t.tipo=="%O" or t.tipo=="%B" or t.tipo=="%H" or t.tipo=="%L" or t.tipo=="ID" or t.tipo=="ST" or t.tipo=="CH" or t.tipo=="FL";
}

bool esUnario(const token& t){
	return t.tok=="-" || t.tok=="not" || t.tok=="!";
}
bool esTipo(const token& t){
	return t.tok=="int" or t.tok=="long" or t.tok=="uint" or t.tok=="ulong" or t.tok=="real" or t.tok=="char" or t.tok=="string" or t.tok=="void";
}

nodoArbol eval_logico(){
	nodoArbol raiz = eval_aritmetico();
	if(raiz.error){
		return raiz;
	}
	while(tokens[idx].tipo=="Ol" or tokens[idx].tipo=="OB"){
		nodoArbol hijo;
		hijo.tipo=tokens[idx].tipo;
		hijo.lexema=tokens[idx].tok;
		raiz.agrega(hijo);
		idx++;
		hijo=eval_aritmetico();
		if(hijo.error){
			return hijo;
		}else{
			raiz.agrega(hijo);
		}
	}
	return raiz;
}


nodoArbol eval_for(){
	nodoArbol raiz;
	nodoArbol hijo;
	if(tokens[idx].tok=="for"){
		idx++;
		raiz.tipo="for";
		raiz.lexema="for";
		if(tokens[idx].tok=="("){
			idx++;
			if(esTipo(tokens[idx])){
				hijo.tipo="tipo";
				hijo.lexema=tokens[idx].tok;
				raiz.agrega(hijo);
				idx++;
				tabsim[tokens[idx].tok]=hijo.lexema;
			}else{
				hijo.tipo="tipo";
				hijo.lexema="sin tipo";
				raiz.agrega(hijo);
			}
			hijo=eval_exp();
			if(not hijo.error){
				if(tokens[idx].tok==","){
					//debug("for2");
					idx++;
					hijo=eval_exp();
					if(not hijo.error){
						raiz.agrega(hijo);
						if(tokens[idx].tok==","){
							idx++;
							hijo=eval_exp();
							if(not hijo.error){
								raiz.agrega(hijo);
								if(tokens[idx].tok==")"){
									idx++;
									if(tokens[idx].tok=="\n"){
										idx++;
									}
									if(tokens[idx].tok=="{"){
										idx++;
										if(tokens[idx].tok=="\n"){
											idx++;
										}else{
											hijo.error=true;
											hijo.tipo=hijo.lexema="Se esperaba '\\n' al final de la linea";
											cout<<tokens[idx-1].linea<<":"<<tokens[idx-1].numero<<". "<<hijo.tipo<<endl;
											return hijo;
										}
										while(tokens[idx].tok!="}"){
											//agrega hijo
											while(tokens[idx].tok=="\n")
												idx++;
										//	debug(". FOR bloques");
											try{
												hijo=eval_bloque();
												raiz.agrega(hijo);
											}catch(...){

											}
										}
										idx++;
										//return raiz;
										if(tokens[idx].tok=="\n"){
											idx++;
											return raiz;
										}else{
											hijo.error=true;
											hijo.tipo=hijo.lexema="Se esperaba '\\n' al final de la linea";
											cout<<tokens[idx-1].linea<<":"<<tokens[idx-1].numero<<". "<<hijo.tipo<<endl;
											return hijo;
										}
									}else{
										hijo.error=true;
										hijo.tipo=hijo.lexema="Se esperaba '{' al final de la linea";
										cout<<tokens[idx-1].linea<<":"<<tokens[idx-1].numero<<". "<<hijo.tipo<<endl;
										return hijo;
									}
								}else{
									hijo.error=true;
									hijo.tipo=hijo.lexema="Se esperaba ')'";
									cout<<tokens[idx-1].linea<<":"<<tokens[idx-1].numero<<". "<<hijo.tipo<<endl;
									return hijo;
								}
							}else{
								return hijo;
							}
						}else{
							hijo.error=true;
							hijo.tipo=hijo.lexema="Se esperaba ','";
							cout<<tokens[idx-1].linea<<":"<<tokens[idx-1].numero<<". "<<hijo.tipo<<endl;
							return hijo;
						}
					}else{
						return hijo;
					}
				}else{
					hijo.error=true;
					hijo.tipo=hijo.lexema="Se esperaba ','";
					cout<<tokens[idx-1].linea<<":"<<tokens[idx-1].numero<<". "<<hijo.tipo<<endl;
					return hijo;
				}
			}else{
				return hijo;
			}
		}else{
			hijo.error=true;
			hijo.tipo=hijo.lexema="Se esperaba '('";
			cout<<tokens[idx-1].linea<<":"<<tokens[idx-1].numero<<". "<<hijo.tipo<<endl;
			return hijo;
		}
	}else{
		hijo.error=true;
		hijo.tipo=hijo.lexema="Se esperaba 'for'";
		cout<<tokens[idx-1].linea<<":"<<tokens[idx-1].numero<<". "<<hijo.tipo<<endl;
		return hijo;
	}
}

nodoArbol eval_while(){
	nodoArbol raiz;
	nodoArbol hijo;
	if(tokens[idx].tok=="while"){
		idx++;
		raiz.tipo="while";
		raiz.lexema="while";
		if(tokens[idx].tok=="("){
			idx++;
			hijo=eval_exp();
			if(not hijo.error){
				raiz.agrega(hijo);
				if(tokens[idx].tok==")"){
					idx++;
					if(tokens[idx].tok=="\n"){
						idx++;
					}
					if(tokens[idx++].tok=="{"){
						while(tokens[idx].tok!="}"){
							//agrega hijo
							while(tokens[idx].tok=="\n")
								idx++;
							//debug("while bloque");
							try{
								hijo=eval_bloque();
								raiz.agrega(hijo);
							}catch(...){

							}
						}
						idx++;
						//return raiz;
						if(tokens[idx].tok=="\n"){
							idx++;
							return raiz;
						}else{
							hijo.error=true;
							hijo.tipo=hijo.lexema="Se esperaba '\\n' al final de la linea";
							cout<<tokens[idx-1].linea<<":"<<tokens[idx-1].numero<<". "<<hijo.tipo<<endl;
							return hijo;	
						}
					}else{
						hijo.error=true;
						hijo.tipo=hijo.lexema="Se esperaba '}' al final de la linea";
						cout<<tokens[idx-1].linea<<":"<<tokens[idx-1].numero<<". "<<hijo.tipo<<endl;
						return hijo;
					}
				}else{
					hijo.error=true;
					hijo.tipo=hijo.lexema="Se esperaba ')'";
					cout<<tokens[idx-1].linea<<":"<<tokens[idx-1].numero<<". "<<hijo.tipo<<endl;
					return hijo;	
				}
			}else{
				return hijo;	
			}
		}else{
			hijo.error=true;
			hijo.tipo=hijo.lexema="Se esperaba '('";
			cout<<tokens[idx-1].linea<<":"<<tokens[idx-1].numero<<". "<<hijo.tipo<<endl;
			return hijo;	
		}
	}else{
		hijo.error=true;
		hijo.tipo=hijo.lexema="Se esperaba 'while'";
		cout<<tokens[idx-1].linea<<":"<<tokens[idx-1].numero<<". "<<hijo.tipo<<endl;
		return hijo;	
	}
}

nodoArbol eval_if(){
	nodoArbol raiz;
	nodoArbol hijo;
	if(tokens[idx].tok=="if"){
		idx++;
		raiz.tipo="if";
		raiz.lexema="if";
		if(tokens[idx].tok=="("){
			idx++;
			hijo=eval_exp();
			if(not hijo.error){
				if(tokens[idx].tok==")"){
					idx++;
					if(tokens[idx].tok=="\n"){
						idx++;
					}
					if(tokens[idx].tok=="{"){
						idx++;
						while(tokens[idx].tok!="}"){
							//agrega hijo
							//debug(" IF bloque");
							while(tokens[idx].tok=="\n")
								idx++;
							try{
								hijo=eval_bloque();
								raiz.agrega(hijo);
							}catch(...){

							}
						}
						idx++;
						if(tokens[idx].tok=="else"){
							idx++;
							raiz.tipo="ifelse";
							hijo.tipo="else";
							hijo.lexema="else";
							raiz.agrega(hijo);
							if(tokens[idx].tok=="\n"){
								idx++;
							}
							if(tokens[idx].tok=="{"){
								idx++;
								while(tokens[idx].tok!="}"){
									//agrega hijo
									while(tokens[idx].tok=="\n")
										idx++;
									try{
										hijo=eval_bloque();
										raiz.agrega(hijo);
									}catch(...){

									}
								}
								idx++;
								if(tokens[idx].tok=="\n"){
									if(tokens[idx].tok=="\n"){
										idx++;
										return raiz;
									}else{
										hijo.error=true;
										hijo.tipo=hijo.lexema="Se esperaba '\\n' al final de la linea";
										cout<<tokens[idx-1].linea<<":"<<tokens[idx-1].numero<<". "<<hijo.tipo<<endl;
										return hijo;
									}
								}else{
									hijo.error=true;
									hijo.tipo=hijo.lexema="Se esperaba '\\n' al final de la linea";
									cout<<tokens[idx-1].linea<<":"<<tokens[idx-1].numero<<". "<<hijo.tipo<<endl;
									return hijo;
								}
							}else{
								hijo=nodoArbol();
								hijo.error=true;
								hijo.lexema=hijo.tipo="Se esperaba {";
								cout<<hijo.lexema<<endl;
								return hijo;
							}
						}
						return raiz;
					}else{
						hijo.error=true;
						hijo.tipo=hijo.lexema="Se esperaba '{'";
						cout<<tokens[idx-1].linea<<":"<<tokens[idx-1].numero<<". "<<hijo.tipo<<endl;
						return hijo;
					}
				}
			}else{
				return hijo;
			}
		}else{
			hijo.error=true;
			hijo.tipo=hijo.lexema="Se esperaba '('";
			cout<<tokens[idx-1].linea<<":"<<tokens[idx-1].numero<<". "<<hijo.tipo<<endl;
			return hijo;
		}
	}else{
		hijo.error=true;
		hijo.tipo=hijo.lexema="Se esperaba for";
		cout<<tokens[idx-1].linea<<":"<<tokens[idx-1].numero<<". "<<hijo.tipo<<endl;
		return hijo;
	}
}
nodoArbol eval_exp(){
	nodoArbol raiz;
	nodoArbol hijo;
	if(tokens[idx].tok=="return"){
		idx++;
		raiz.tipo="return";
		raiz.lexema="return";
		hijo=eval_exp();
		if(not hijo.error){
			raiz.agrega(hijo);
			if(tokens[idx].tok=="\n"){
				idx++;
				return raiz;
			}else{
				hijo.error=true;
				hijo.tipo=hijo.lexema="Se esperaba '\\n' al final de la linea";
				cout<<tokens[idx-1].linea<<":"<<tokens[idx-1].numero<<". "<<hijo.tipo<<endl;
				return hijo;
			}
		}else{
			return hijo;
		}
	}else{ 
		raiz=eval_logico();
		if(not raiz.error){
			while(tokens[idx].tipo=="O="){
				hijo.tipo=tokens[idx].tipo;
				hijo.lexema=tokens[idx].tok;
				raiz.agrega(hijo);
				idx++;
				hijo=eval_logico();
				if(not hijo.error){
					raiz.agrega(hijo);
				}else{
					return hijo;
				}
			}
			return raiz;
		}else{
			raiz=eval_unario();
			return raiz;
		}
	}
}

nodoArbol eval_aritmetico(){
	nodoArbol raiz=eval_multi();
	nodoArbol hijo;
	if(not raiz.error){
		while(tokens[idx].tok=="+" or tokens[idx].tok=="-"){
			hijo.tipo=hijo.lexema=tokens[idx].tok;
			raiz.agrega(hijo);
			idx++;
			hijo=eval_multi();
			if(hijo.error)
				return hijo;
			else raiz.agrega(hijo);
		}
		return raiz;
	}else{
		return eval_unario();
	}
}

nodoArbol eval_multi(){
	nodoArbol raiz=eval_termino();
	nodoArbol hijo;
	if(not raiz.error){
		while(tokens[idx].tok=="*" or tokens[idx].tok=="%" or tokens[idx].tok=="/"){
			hijo.tipo=hijo.lexema=tokens[idx].tok;
			raiz.agrega(hijo);
			idx++;
			hijo=eval_exp();
			if(hijo.error){
				return hijo;
			}
		}
		return raiz;
	}else{
		hijo.error=true;
		hijo.tipo=hijo.lexema="Se esperaba expresion";
		//cout<<hijo.tipo<<endl;
		return hijo;
	}
}

nodoArbol eval_unario(){
	nodoArbol raiz=eval_termino();
	nodoArbol hijo;
	if(not raiz.error){
		return raiz;
	}else if(esUnario(tokens[idx])){
		raiz = nodoArbol();
		raiz.tipo="unario";
		raiz.lexema=tokens[idx].tok;
		idx++;
		hijo=eval_exp();
		if(not hijo.error){
			raiz.agrega(hijo);
			return raiz;
		}else{
			return hijo;
		}
	}else if(tokens[idx].tipo=="ID" or tokens[idx].tok=="read" or tokens[idx].tok=="print"){
		raiz=nodoArbol();
		raiz.tipo="functor";
		raiz.lexema=tokens[idx].tok;
		idx++;
		if(tokens[idx].tok=="("){
			idx++;
			while(tokens[idx].tok!=")"){
				//agrega hijo
				hijo=eval_exp();
				raiz.agrega(hijo);
				if(tokens[idx].tok==","){
					idx++;
				}else if(tokens[idx].tok==")"){
					
				}else{
					nodoArbol err;
					err.tipo=err.lexema=tokens[idx].tok+" inesperado";
					cout<<err.tipo<<endl;
					return err;
				}
			}
			idx++;
			return raiz;
		}else{
			if(esOperador(tokens[idx])){
				idx++;
				hijo.tipo=tokens[idx].tipo;
				hijo.lexema=tokens[idx].tok;
				raiz.agrega(hijo);
				raiz.agrega(eval_exp());
				return raiz;
			}else{
				return raiz;
			}
		}
	}else if(esUnario(tokens[idx])){
		raiz=nodoArbol();
		raiz.tipo=tokens[idx].tipo;
		raiz.lexema=tokens[idx].tok;
		idx++;
		if(not (hijo=eval_exp()).error){
			raiz.agrega(hijo);
			return raiz;
		}else{
			return hijo;
		}
	}else if(tokens[idx].tipo=="ID" or tokens[idx].tok=="read" or tokens[idx].tok=="print"){
		idx++;
		raiz=nodoArbol();
		raiz.tipo="functor";
		raiz.lexema=tokens[idx].tok;
		if(tokens[idx].tok=="("){
			idx++;
			while(tokens[idx].tok!=")"){
				//agrega hijo
				if(not(hijo=eval_exp()).error){
					raiz.agrega(hijo);
					if(tokens[idx].tok==","){
						idx++;
					}else if(tokens[idx].tok==")"){

					}else{
						hijo=nodoArbol();
						hijo.error=true;
						hijo.tipo=hijo.lexema="Se esperaba )";
						cout<<hijo.lexema<<endl;
						return hijo;
					}
				}else{
					return hijo;
				}
			}
			idx++;
			return raiz;
		}else{
			if(esOperador(tokens[idx])){
				idx--;
				return eval_exp();
			}else{
				return raiz;
			}
		}
	}
}

nodoArbol eval_termino(){
	nodoArbol raiz;
	if(tokens[idx].tok=="("){
		idx++;
		raiz=eval_exp();
		if(tokens[idx].tok==")"){
			idx++;
		}
		return raiz;
	}else{
		if(esValor(tokens[idx])){
			idx++;
			raiz.tipo="constante";
			raiz.lexema=tokens[idx-1].tok;
			return raiz;
		}else{
			//debug("No es constante");
			raiz.tipo=raiz.lexema=tokens[idx].tok+" inesperado ";
			raiz.error=true;
			return raiz;
		}
		
	}
}

nodoArbol eval_declaracion(){
	nodoArbol raiz;
	nodoArbol hijo;
	if(esTipo(tokens[idx])){
		string tipo_dato=tokens[idx].tok;
		idx++;
		raiz.tipo="declaracion";
		raiz.lexema=tokens[idx].tipo;
		while(tokens[idx].tipo=="ID"){
			tabsim[tokens[idx].tok]=tipo_dato;
			hijo.tipo="ID";
			hijo.lexema=tokens[idx].tok;
			idx++;
			raiz.agrega(hijo);
			if(tokens[idx].tipo=="O="){
				idx++;
				hijo.tipo="O=";
				hijo.lexema="=";
				raiz.hijos[0].agrega(hijo);
				hijo=eval_exp();
				raiz.hijos[0].agrega(hijo);
			}
			if(tokens[idx].tok==","){
				idx++;
			}
		}
		if(tokens[idx].tok!="\n"){
			raiz=nodoArbol();
			raiz.tipo=raiz.lexema="Se esperaba \\n";
			cout<<raiz.tipo<<endl;
			raiz.error=true;
			return raiz;
		}
	}else{
		raiz.tipo=raiz.lexema="Se esperaba un tipo de dato";
		cout<<raiz.tipo<<endl;
		return raiz;
	}
}

nodoArbol eval_bloque(){
	if(tokens[idx].tok=="for"){
		//cout<<"for.---"<<endl;
		return eval_for();
	}else if(tokens[idx].tok=="while"){
		return eval_while();

	}else if(tokens[idx].tok=="if"){
		return eval_if();
	}else if(esTipo(tokens[idx])){
		return eval_declaracion();
	}else{
		nodoArbol raiz=eval_exp();
		while(tokens[idx].tok=="\n"){
			idx++;
		}
		return raiz;
	}
}

nodoArbol eval(){
	nodoArbol raiz;
	raiz.tipo="programa";
	while(idx<tokens.size() and tokens[idx].tok!="EOF"){
		try{
			raiz.agrega(eval_bloque());	
			//cout<<idx<<"::"<<tokens[idx].tok<<endl;
			while(idx<tokens.size() and tokens[idx].tok=="\n")
				idx++;
		}catch(...){

		}
		//debug("FIN Intruccion");
		//return;
		//Agregar
	}
	return raiz;
}


