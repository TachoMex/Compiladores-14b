func int suma(int a, int b) 
	return a+b
endfunc

func int absdif(int a, int b)
	if(a>b)
		return a-b
	else
		return b-a
	endif
endfunc



int i, a, b,B[200], aux,  A[100]
int z=suma(2*5+a,aux*A[0])-absdif(10000, 500)
int w=10, C[a/b**aux]
double x=0, y, z, pi=3.141592
a=0
b=1

A[0]=10
A[a+b]=pi**x

for(i=0,i<10,i+=1)
	print("f(")
	print(i)
	print(")=") 
	println(a)
	aux=a
	a=a+b
	b=aux
endfor
read(x)
while(a<b) 
	println(x)
	y=x*pi
	z=ln(y)
	x+=z**0.5
endwhile

if(x!=0)
	println(a)
else
	println(b)
endif

if(x!=0)
	println(a)
elseif(x<0)
	println(b)
elseif(1==1)
	println(pi)
else
	x+=1
endif

int MAX=1000
int lista[MAX]
int j
for(i=0, i<MAX, i+=1)
	read(lista[i])
endfor

for(i=0, i<MAX, i+=1)
	for(j=1, j<MAX, j+=1)
		if(lista[j]<lista[j-1])
			int temp=lista[j]
			lista[j]=lista[j-1]
			lista[j-1]=temp
		endif
	endfor
endfor