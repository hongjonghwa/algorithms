#include<stdio.h>
#include<stdlib.h>

int main(){
	printf("100000 100000\n");
	for (int i = 0; i < 100000 ; ++i)
		printf("%d %d %d\n", rand() % 100000 + 1, rand() % 100000 + 1, (i * 31) % 1000000 + 1 );
	printf("100000\n");
	for (int i = 0; i < 100000 ; ++i)
		printf("%d %d\n", rand() % 100000 + 1, rand() % 100000 + 1);
}
