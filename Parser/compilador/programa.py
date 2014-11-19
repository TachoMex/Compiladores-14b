int i, a, b,aux
double x=0, y, z, pi=3.141592
a=0
b=1
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