/*
	다음 블로그의 풀이를 참고하였습니다
	http://blog.myungwoo.kr/78
*/ 
#define _CRT_SECURE_NO_WARNINGS

#define MAX(x,y) ( (x)>(y) ? (x) : (y))
#define MIN(x,y) ( (x)<(y) ? (x) : (y))

#include <stdio.h>
#include <string.h>

using namespace std;

int mask[29], bits[29];
int casecnt;

int t, m, n;
int X[1001];
int D[1001][29][29];
int c;


void print_hex(int x, int len){
	if (len){
		print_hex( x >> 1, len-1);
		if (x&1) printf ("1");
		else printf ("0");
	}
}


void report_X(){
	printf("X[][]\n");
	for (int y = 1 ; y <= m ; ++y){
		printf("%10d", X[y]);
	}
	printf("\n");
}

void dp(){
	for (int l = 1 ; l <= n ; ++l){
		for (int i = 0 ; i < casecnt ; ++i){
			for (int j = 0 ; j < casecnt ; ++j){
				for (int k = 0 ; k < casecnt ; ++k){
					if ( ((mask[i]|mask[j]|mask[k]) & X[l]) == X[l]  ) // 비트 연산(&)보다 대입 연산(==) 이 우선 순위가 높은 것에 주의!
						D[l][j][k] = MIN(D[l][j][k], D[l-1][i][j] + bits[k]);
				}
			}
		}
	}
	int ret = 9999;
	for (int i = 0 ; i < casecnt ; ++i){
		for (int j = 0 ; j < casecnt ; ++j){
			if (ret > D[n][i][j]) ret = D[n][i][j];
		}
	}
	printf("%d ", ret);
	//printf("\n\n\n");
	/*
	for (int i = 0 ; i < 29 ; ++i){
		for (int j = 0 ; j < 29 ; ++j){
			printf("%d ", D[1][i][j]);
		}
		printf("\n");
	}
	*/

}

void recur(int n, int v, int c){
	if (n <= 2){
		mask[casecnt] = v;
		bits[casecnt] = c;
		++casecnt;
		return;
	}
	recur(n-1, v, c);
	recur(n-3, v | 7<<(n)>>3 , c+1);
}

void solv(){
	scanf("%d%d%d", &m, &n, &c);
	casecnt = 0;
	recur(m,0,0);
	mask[casecnt] =(1<<m)-1; // 3으로 떨어지지 않을 때 처리
	bits[casecnt++] = (m+2)/3;
	memset(X, 0, sizeof(X));
	for (int i = 0 ; i < c ; ++i){
		int u, v;
		scanf("%d%d", &u, &v);
		X[v] |= 1 << (u-1);
	}
	/*
	for (int i = 1 ; i <= n ; ++i){
		print_hex(X[i], m);
		printf(" %d \n", X[i]);
	}
	*/
	memset(D, 63, sizeof(D));
	D[0][0][0] = 0;
	dp();
}


int main(){

	
	/*
	for (int i = 0 ;i < casecnt ; ++i){
		printf ("#%d\t", i);
		print_hex(mask[i], 10);
		printf(" %d %d \n", mask[i], bits[i]);
	}
	*/
	

	scanf("%d", &t);
	for (int i = 0 ; i < t ; ++i) solv();
}
