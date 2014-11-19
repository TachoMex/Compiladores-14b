#include <iostream>
using namespace std;
int main(){
	int i = 0;
	Et_Ini_0:	
	bool t0 = i < 5;
	if (!t0) 
		goto Et_fin_0;
	goto Et_med_0;
	Et_med2_0:	
		i = i + 1;
	goto Et_Ini_0;
	Et_med_0:
	cout<<i<<endl;
	goto Et_med2_0;
	Et_fin_0:
	return 0;
}