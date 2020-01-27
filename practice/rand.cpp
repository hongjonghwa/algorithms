#include<iostream>
//#include<stdlib.h>
using namespace std;

// stdlib.h rand() 10^8 -> 1.12s 
int seed = 123456789;
int rand(){
	seed = (54321*seed)+1234567;
	return (seed>>16)&0x7FFF;
}

int main(){
	for (int i=0 ; i < 100000000 ; ++i)
		rand();
	
	for (int i=0 ; i < 10 ; ++i)
		cout << rand() << endl;
	return 0;
}
