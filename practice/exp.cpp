#include<stdio.h>

int exp1(int a , int b){
	int ret = 1;
	for (int i = 0 ; i < b ; ++i)
		ret *= a;
	return ret;
}

int exp2(int a, int b){ // recursive
	if (b == 0) return 1;
	if (b%2 == 1) return exp2(a, b-1) * a;
	int t = exp2(a,b/2);
	return t*t;
}

int exp3(int a, int b){//iterative
	int ret = 1;
	while (b > 0){
		if (b%2 == 1) ret *= a;
		a *= a;
		b = b>>1;
	}
	return ret;
}

int main(){
	printf("%d\n", exp1(3,5));
	printf("%d\n", exp2(3,5));
	printf("%d\n", exp3(3,0));
	printf("%d\n", exp3(3,1));
	printf("%d\n", exp3(3,2));
	printf("%d\n", exp3(3,3));
	printf("%d\n", exp3(3,4));
	printf("%d\n", exp3(3,5));
	printf("%d\n", exp3(3,6));
}
