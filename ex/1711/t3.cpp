#include<stdio.h>

char x[100];
char t[10][10];

void report(){
	for (int j = 0 ; j < 10 ; j++){
		for (int i = 0 ; i < 10 ; ++i)
			printf ("%d\t" , x[j*10+i]);
		printf("\n");
	}
	printf("\n");
}

int main(){
	int *xint = (int*)&x;
	xint[0] = 1;
	xint[1] = 2;
	xint[2] = 3;
	xint[3] = 4;
	xint[4] = 5;
	xint[5] = 256;
	xint[6] = 65536;
	xint[7] = 65536*10;
	xint[8] = 1e9;
	xint[9] = 2e9;
	report();
	//printf("%lld \n", t);
	/*
	for (int j = 0 ; j < 10 ; j++){
		for (int i = 0 ; i < 10 ; ++i)
			printf ("%d\t" , xx[j][i]);
		printf("\n");
	}
	printf("\n");
	*/
}
