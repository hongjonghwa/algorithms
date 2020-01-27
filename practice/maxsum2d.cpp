#include<stdio.h>
#include<time.h>
#include<string.h>
#define N 1000
#define M 2000
#define MAX(a,b) (a) > (b) ? (a) : (b)

int SEED =1000001;
int fastrand(){
	SEED *= 29989;
	SEED += 1891;
	SEED >>= 4;
	return SEED & 0x3FFF;
}

int X[N][M];

void solv1(){
	int maxsofar = 0;
	for (int i =0 ; i < N ; ++i){
		for (int j =i; j < N ; ++j){
			int sum = 0;
			for (int k = i; k <= j; ++k){
				sum += X[k][0];
			}
			maxsofar = MAX(maxsofar,sum);
		}
	}
	printf ("Solv1: %d \n", maxsofar);
}
void solv2(){
	int maxsofar = 0;
	for (int i =0 ; i < N ; ++i){
		int sum = 0;
		for (int j =i; j < N ; ++j){
			sum += X[j][0];
			maxsofar = MAX(maxsofar,sum);
		}
	}
	printf ("Solv2: %d \n", maxsofar);
}
void solv3() {
	int maxsofar = 0;
	int cur = 0; 
	for (int i =0 ; i < N ; ++i){
		cur = MAX(cur + X[i][0], 0);
		maxsofar = MAX( maxsofar, cur);
	}
	printf ("Solv3: %d \n", maxsofar);
}

void solv4(){
	int MAXN = 300;
	long long int D[1001][1001];
	memset(D,0,sizeof(D));
	printf("%lld \n", D[0][0]);
	printf("%lld \n", D[10][10]);
	for (int i = 1 ; i <= 1000; ++i)
		for (int j = 1 ; j <= 1000 ; ++j)
			D[i][j] = D[i-1][j] + D[i][j-1] - D[i-1][j-1] + X[i-1][j-1];
	long long int ret = 0;
	for (int i1 = 1 ; i1 <= MAXN; ++i1)
		for (int j1 = 1 ; j1 <= MAXN ; ++j1)
			for (int i2 = i1; i2 <= MAXN ; ++i2)
				for (int j2 = j1; j2 <= MAXN; ++j2){
					long long int t = D[i2][j2] - D[i2][j1-1] - D[i1-1][j2] + D[i1-1][j1-1];
					ret = MAX(ret, t);
				}
	printf("%lld \n", ret);
}

void solv5(){
	int MAXN = 1000;
	long long int D[1000][1001];
	for (int i = 0 ; i < 1000; ++i){
		D[i][0] = 0;
		for (int j = 1 ; j <= 1000 ; ++j){
			D[i][j] = D[i][j-1] + X[i][j+1];
		}
	}
	long long int ret = 0;
	for (int j1 = 1 ; j1 <= MAXN; ++j1){
		for (int j2 = j1; j2 <= MAXN ; ++j2){
			long long int cur = 0;
			for (int i = 0 ; i < MAXN ; ++i){
				cur = MAX( cur + D[i][j2+1] - D[i][j1], 0);
				ret = MAX(ret, cur);
			}
		}
	}
	printf("%lld \n", ret);
}
int main(){
	for (int i = 0 ; i < N ; ++i)
		for (int j = 0 ; j <M; ++j)
			X[i][j] = (fastrand() % 199) - 99;

	long clk;
	clk = clock();
	solv1();
	printf ( " time SOLV1 - %f \n", (double)(clock()-clk)/CLOCKS_PER_SEC);
	clk = clock();
	solv2();
	printf ( " time SOLV2 - %f \n", (double)(clock()-clk)/CLOCKS_PER_SEC);
	clk = clock();
	solv3();
	printf ( " time SOLV3 - %f \n", (double)(clock()-clk)/CLOCKS_PER_SEC);
	clk = clock();
	solv4();
	printf ( " time SOLV4- %f \n", (double)(clock()-clk)/CLOCKS_PER_SEC);
	clk = clock();
	solv5();
	printf ( " time SOLV5- %f \n", (double)(clock()-clk)/CLOCKS_PER_SEC);
}

