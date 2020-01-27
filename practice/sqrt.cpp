#include<stdio.h>
#include<math.h>


double sqrt2 ( double n){
	double ret = 1;
	for (int i = 0 ; i < 30 ; ++i){
		ret = 0.5*(ret+n/ret);
		printf("[%3d] %.12f \n", i, ret);
	}
	return ret;
}

int main(){
	double n = 10000000;

	printf("math.h %.12f \n", sqrt(n));
	printf("my     %.12f \n", sqrt2(n));
}
