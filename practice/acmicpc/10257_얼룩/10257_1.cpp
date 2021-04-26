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
int loop;

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
		for (int i = 0 ; i < 29 ; ++i){
			for (int j = 0 ; j < 29 ; ++j){
				for (int k = 0 ; k < 29 ; ++k){
					if ( ((mask[i]|mask[j]|mask[k]) & X[l]) == X[l]  )
						D[l][j][k] = MIN(D[l][j][k], D[l-1][i][j] + bits[k]);
				}
			}
		}
	}
	int ret = 9999;
	for (int i = 0 ; i < 29 ; ++i){
		for (int j = 0 ; j < 29 ; ++j){
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

void solv(){
	scanf("%d%d%d", &m, &n, &c);
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

void recur(int n, int v, int c){
	if (n <= 2){
		mask[loop] = v;
		bits[loop] = c;
		++loop;
		return;
	}
	recur(n-1, v, c);
	recur(n-3, v | 7<<(n)>>3 , c+1);
}

int main(){
	loop = 0;
	recur(10,0,0);
	mask[loop] = 1023; // 3으로 떨어지지 않을 때 처리
	bits[loop++] = 4;
	
	/*
	for (int i = 0 ;i < loop ; ++i){
		printf ("#%d\t", i);
		print_hex(mask[i], 10);
		printf(" %d %d \n", mask[i], bits[i]);
	}
	*/
	

	scanf("%d", &t);
	for (int i = 0 ; i < t ; ++i) solv();
}
