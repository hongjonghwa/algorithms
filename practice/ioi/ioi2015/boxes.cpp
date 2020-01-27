#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<assert.h>

//#define MAXN 10000000
#define MAXN 1000
using namespace std;

int N,K,L;
int P[MAXN]; //incresing order

/*
int delivery(){
	long long int ret = 0;
	int rs, ls;
	for (rs = 0 ; rs+K < N && P[rs+K] * 2 < L ;rs+=K) ret += P[rs+K] * 2;
	for (ls = N-1 ; ls-K >= 0 && (L-P[ls-K]) * 2 < L ;ls-=K) ret += (L-P[ls-K]) * 2;
	assert(rs-ls+1 <= 2*K);

	int pos = rs;
	for (; pos <= ls && P[i]; ++pos){
		if (P[i] *2 < L) rsmax = P[i];
		else lsmax = L-P[i];
	}
}
*/
int cost(int from, int to){
	int ret = min(P[to], L-P[from]) * 2;
	ret = min(ret, L);
	return ret;
}
long long int delivery(){
	long long int D[N+1];
	memset(D,63, sizeof(D));
	D[0] = D[N] = 0;
	// 11 : 0~10 까지라면, 1-5, 6-10
	// 10 : 0~ 9 까지라면, 1-5, 5-9 까지
	int half_start = lower_bound(P, P+N, (L+1)/2 ) - P;
	for (int i = 1 ; i < half_start ; ++i)
		D[i] = D[max(i-K,0)] + 2*P[i];
	for (int i = N-1  ; i >=  half_start ; --i)
		D[i] = D[min(i+K,N)] + 2*(L-P[i]);


	printf("N K L %d %d %d \n" , N, K, L);
	printf(" %d %d\n" ,  P[0], P[999]); 
	long long int ret = D[half_start-1] + D[half_start];
	printf("ret : %lld , 0~%d %lld, %d~N %lld\n", ret, half_start-1, D[half_start-1], half_start, D[half_start]);
	for (int i = max(half_start-K+1, 0) ; i < half_start && i + K < N ; ++i){
		printf("  debug : %d , %d , %lld, %lld\n", i, min(i+1+K,N), D[i], D[min(i+1+K,N)]); 
		ret = min (ret, D[i] + D[min(i+1+K,N)] + L);
		printf("  ret : %lld\n", ret);
	}
	return ret;
}
long long int delivery_nk(){
	long long int D[N+1];
	memset(D,63, sizeof(D));
	D[0] = 0;
	long long int ret = 0;
	for (int i = 1; i <= N ; ++i){
		for (int j = 1; i-j>=0 && j <= K ; ++j){
			D[i] = min(D[i], D[i-j] + cost(i-j, i-1));
		}
	}
	return D[N];
}
int main(){
	scanf("%d%d%d", &N, &K, &L);
	for (int i  = 0; i < N ; ++i) scanf("%d", &P[i]);
	printf("delivery2 answer : %lld\n", delivery());
	printf("nk answer : %lld\n", delivery_nk());

}
