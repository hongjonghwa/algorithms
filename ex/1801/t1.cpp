#include<stdio.h>
#include<stdlib.h>

int x[65];

int main(){
	int ret = 0;
	for (int i = 0 ; i < 10000 ; ++i){
		int sum = 64 ;
		for (int j = 0 ; j < 64 ; ++j)
			if (rand() % 10 == 0) sum--;
		x[sum]++;
	}
	for (int i = 64 ; i >=40 ; --i)
		printf("%d %d\n", i, x[i]);
}
