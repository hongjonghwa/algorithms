#include<stdio.h>

char x[3][3];


int main(){
	**x = 1;
	*((*x)+1) = 2;
	*((*x)+2) = 3;
	*((*x)+3) = 4;
	*((*x)+4) = 5;
	*((*x)+5) = 6;
	*((*x)+6) = 7;

	printf ("%lld \n", *x);
	printf ("%lld \n", x);
	// *x와 x의 결과는 같다. 다차원 배열을 1차원 배열로 type casting 가능하다
	for (int j = 0 ; j < 3 ; j++){
		for (int i = 0 ; i < 3 ; ++i){
			printf ("%d " , x[j][i]);
		}
	}
	printf("\n");

	for (int j = 0 ; j < 9 ; j++){
		printf ("%d " , ((char*)x)[j]);
	}
	printf("\n");

	char *t = (char *)x; // 2차 배열 x 를 char*로 캐스팅
	for (int j = 0 ; j < 9 ; j++){
		printf ("%d " , t[j]);
	}
	printf("\n");

	void *tt = (void *)x; // void*로 캐스팅 후 다시 char*로 캐스팅
	for (int j = 0 ; j < 9 ; j++){
		printf ("%d " , ((char*)tt)[j]);
	}
	printf("\n");
}

