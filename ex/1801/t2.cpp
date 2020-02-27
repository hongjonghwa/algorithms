#include<stdio.h>
#include<stdlib.h>

int x[100];

int main(){
	int ret = 0;
	for (int i = 0 ; i < 10000 ; ++i){
		int sum = 4 ;
		for (int j = 0 ; j < 4 ; ++j)
			if (rand() % 10 == 0) sum++;
		for (int j = 0 ; j < 4 ; ++j)
			if (rand() % 10 == 0) sum--;
		x[sum]++;
	}
	for (int i = 0 ; i < 8 ; ++i)
		printf("%d %d\n", i, x[i]);
}
