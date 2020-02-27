#include<stdio.h>

char x[10][10];

void report(){
	for (int j = 0 ; j < 10 ; j++){
		for (int i = 0 ; i < 10 ; ++i)
			printf ("%d\t" , x[j][i]);
		printf("\n");
	}
	printf("\n");
}
void report_addr(){
	for (int j = 0 ; j < 10 ; j++){
		for (int i = 0 ; i < 10 ; ++i)
			printf ("%d(%p)\t" , x[j][i], &x[j][i]);
		printf("\n");
	}
	printf("\n");
}

int main(){
	for (int j = 0 ; j < 10 ; j++)
		for (int i = 0 ; i < 10 ; ++i)
			x[j][i] = j*10 + i;
	report_addr();

	*((int*)x) = 1000;
	*((int*)(x+1)) = 65535;
	*((int*)(x+2)) = 4;
	*((int*)(x+3)) = 1;

	//void* xp = (void*) x;
	char* xp = (char*) x;
	*((int*)(xp+50)) = 1;
	*((int*)(xp+60)) = 256;
	*((int*)(xp+70)) = 65536;
	*((int*)(xp+80)) = 655360;
	
	report();
}
