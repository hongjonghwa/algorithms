#include <stdio.h>
#include <stdlib.h>

int main(){
	printf("300000 300000\n");
	for (int i = 0 ;i < 300000 ; ++i)
		printf( "%d ", rand() % 300000 + 1);
	printf("\n");
	for (int i = 0 ;i < 300000 ; ++i)
		printf( "%d ", rand() % 100000000 + 1);
	printf("\n");
	printf("300000\n");
	for (int i = 0 ;i < 300000 ; ++i)
		printf( "%d %d %d\n", rand() % 300000 + 1, rand() % 300000 + 1, rand() % 100000 + 1);

}

