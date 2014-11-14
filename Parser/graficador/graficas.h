#ifndef GRAFICAS_H
#define GRAFICAS_H
#include "imagen.h"
void graficar(imagen &M, double ini, double fin, double iniy, double finy, double(*f)(double x), color c){
	int n=M.columnas();
	int m=M.filas();
	double deltax=(fin-ini)/n;
	double min=iniy;
	double max=finy;
	double *valores = new double[M.columnas()+5];
	
	for(int i=0;i<M.columnas();i++){
		valores[i]=f(ini+deltax*i);
	}
	double deltay=(max-min)/m;
	if( 0 > min and 0<max){
		int x=-ini/deltax;
		linea(M, x,0, x, m, color(0,125,0));
		for(int i=int(ceil(iniy));i<finy;i++){
			int d=(double(i)-iniy)/deltay;
			linea(M, x+10,d, x-10, d, color(0,125,125)); 
		}
	}
	
	if( 0 >= ini and 0 < fin){
		int x=m+min/deltay;
		linea(M, 0,x, n,x, color(0,125,0));	
		for(int i=int(ceil(ini));i<fin;i++){
			int d=(double(i)-ini)/deltax; 
			linea(M, d,x+10, d, x-10, color(0,125,125)); 
		}
	}
	for(int i=1;i<M.columnas();i++){
		if(std::isfinite(valores[i]) and std::isfinite(valores[i-1]) and valores[i]*valores[i-1] >= 0){
			linea(M,i-1,floor(m-(valores[i-1]-min)/deltay),i,floor(m-(valores[i]-min)/deltay),c); 
		}
	}
	delete[] valores;
}

void graficar(imagen &M, double ini, double fin, double iniy, double finy, const double *valores, color c){
	int n=M.columnas();
	int m=M.filas();
	double deltax=(fin-ini)/n;
	double min=iniy;
	double max=finy;
	double deltay=(max-min)/m;
	if( 0 > min and 0<max){
		int x=-ini/deltax;
		linea(M, x,0, x, m, color(0,125,0));
		for(int i=int(ceil(iniy));i<finy;i++){
			int d=(double(i)-iniy)/deltay;
			linea(M, x+10,d, x-10, d, color(0,125,125)); 
		}
	}
	
	if( 0 >= ini and 0 < fin){
		int x=m+min/deltay;
		linea(M, 0,x, n,x, color(0,125,0));	
		for(int i=int(ceil(ini));i<fin;i++){
			int d=(double(i)-ini)/deltax; 
			linea(M, d,x+10, d, x-10, color(0,125,125)); 
		}
	}
	for(int i=1;i<M.columnas();i++){
		if(std::isfinite(valores[i]) and std::isfinite(valores[i-1]) and valores[i]*valores[i-1] >= 0){
			linea(M,i-1,floor(m-(valores[i-1]-min)/deltay),i,floor(m-(valores[i]-min)/deltay),c); 
		}
	}
}
#endif