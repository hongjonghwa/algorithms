#define _CRT_SECURE_NO_WARNINGS

#define SWAPT(T,a,b) { T tmp = a; a = b; b = tmp;}
#include<stdio.h>
#include<assert.h>

int N;
int A[100];
int minFactor[1000001];
int fact2seq[1000001];
int seq[500][102]; // 0~99 , 100 : all, 101 : prime 

void eratosthenes() {
	minFactor[0] = minFactor[1] = -1; // 1은 예외 처리
	for (int i = 2; i <= 1000000; ++i) minFactor[i] = i;
	for (int i = 2; i <= 1000; ++i) { // ; i<=int(sqrt(N)) ;
		if (minFactor[i] == i)
			for (int j = i*i; j <= 1000000; j += i)
				// 아직 약수를 못 봤을 때만 가장 작은 약수 업데이트
				if (minFactor[j] == j) minFactor[j] = i;
	}
}

int pow(int a, int b) {
	if (b == 0) return 1;
	if (b % 2 == 1) return pow(a, b - 1) * a;
	int tmp = pow(a, b / 2);
	return tmp * tmp;
}

int main() {
	eratosthenes();

	scanf("%d", &N);
	for (int i = 0; i < N; ++i) 
		scanf("%d", &A[i]);

	
	int factseq = 0;
	for (int i = 0; i < N; ++i) {
		int n = A[i];
		while (n > 1) {
			int f = minFactor[n];
			if (fact2seq[f] == 0) {
				fact2seq[f] = ++factseq;
				seq[factseq][101] = f;
			}
			seq[fact2seq[f]][i]++;
			seq[fact2seq[f]][100]++;
			n /= f;
		}
	}


	int ans1 = 1, ans2 = 0;
	for (int i = 1; i <= factseq ; ++i) {
		int factor = seq[i][101];
		int maxcnt = seq[i][100] / N;
		//for (int ii = 0; ii < maxcnt; ++ii) ans1 *= factor;
		ans1 *= pow(factor, maxcnt);
		for (int ii = 0 ; ii < N ; ++ii)
			if (seq[i][ii] < maxcnt) ans2 += maxcnt - seq[i][ii];
	}
	printf("%d %d\n", ans1, ans2);

}