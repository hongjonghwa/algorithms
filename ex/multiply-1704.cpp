#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#define BASE 36 
#define MAXN 128

typedef unsigned int uint;
typedef long long unsigned lluint;
using namespace std;

uint BM[7];
struct Init{
	Init(){
		BM[0] = 1;
		for (int i = 1 ; i <= 6 ; ++i)
			BM[i] = BM[i-1] * BASE;
	}
}init;

// 압축 없이
void mul1(uint *a, uint *b, lluint *c){
	for (int i = 0 ; i < MAXN * 2 ; ++i)
		c[i] = 0;

	for (int i = 0 ; i < MAXN ; ++i)
		for (int j = 0 ; j < MAXN ; ++j)
			c[i+j] += a[i] * b[j]; // BASE36 의 작은 값이라 오버플로워가 발생하지 않는다.

	for (int i = 0; i < MAXN * 2 -1 ; ++i)
		if (c[i] >= BASE) {
			c[i+1] += c[i] / BASE;
			c[i] %= BASE;
		}
}

uint aa[32], bb[32];
lluint cc[64];

// 4개씩 압축 . BASE36에서 여유있게,,
void mul2(uint *a, uint *b, lluint *c){

	int newN = MAXN/4;
	for (int i = 0; i < newN ; ++i){
		aa[i] = ( (a[i*4+3] * BASE + a[i*4+2]) * BASE + a[i*4+1] ) * BASE + a[i*4];
		bb[i] = ( (b[i*4+3] * BASE + b[i*4+2]) * BASE + b[i*4+1] ) * BASE + b[i*4];
	}

	for (int i = 0 ; i < newN * 2 ; ++i)
		cc[i] = 0;

	for (int i = 0 ; i < newN ; ++i)
		for (int j = 0 ; j < newN ; ++j)
			cc[i+j] += (lluint)aa[i] * bb[j]; // aa 을 미리 long type캐스팅 해야 aa * bb 에서 오버플러 방지

	for (int i = 0; i < newN * 2 - 1 ; ++i)
		if (cc[i] >= BM[4]) {
			cc[i+1] += cc[i] / BM[4];
			cc[i] %= BM[4];
		}
		
	for (int i = 0; i < newN * 2; ++i){
		lluint tmp = cc[i];
		//cout << i << " : " << tmp << endl;
		c[i*4] = tmp % BASE;
		tmp = tmp / BASE;
		c[i*4 + 1] = tmp % BASE;
		tmp = tmp / BASE;
		c[i*4 + 2] = tmp % BASE;
		c[i*4 + 3] = tmp / BASE;
	}
}

// 6개씩 압축 . BASE36에서 여유있게,,
void mul3(uint *a, uint *b, lluint *c){

	int newN = (MAXN-1)/6+1;
	int i = 21;
	aa[i] = a[i*6+1] * BASE + a[i*6];
	bb[i] = b[i*6+1] * BASE + b[i*6];
	for (i = 0; i <=20 ; ++i){
		aa[i] = a[i*6+5] * BM[5]
			  + a[i*6+4] * BM[4]
			  + a[i*6+3] * BM[3]
			  + a[i*6+2] * BM[2]
			  + a[i*6+1] * BM[1]
			  + a[i*6];
		 bb[i] = b[i*6+5] * BM[5]
			  + b[i*6+4] * BM[4]
			  + b[i*6+3] * BM[3]
			  + b[i*6+2] * BM[2]
			  + b[i*6+1] * BM[1]
			  + b[i*6];
	}

	for (int i = 0 ; i < newN * 2 ; ++i)
		cc[i] = 0;

	for (int i = 0 ; i < newN ; ++i){
		for (int j = 0 ; j < newN ; ++j){
			int k = i + j;
			cc[k] = cc[k] + (lluint)aa[i] * bb[j];
			// overflow 확인
			if (cc[k] >= BM[6]) {
				cc[k+1] += cc[k] / BM[6];
				cc[k] %= BM[6];
			}
		}
	}
	for (int i = 0; i < newN * 2 - 1 ; ++i){
		if (cc[i] >= BM[6]) {
			cc[i+1] += cc[i] / BM[6];
			cc[i] %= BM[6];
		}
	}
	for (int i = 0; i < newN * 2; ++i){
		lluint tmp = cc[i];
		c[i*6] = tmp % BASE;
		tmp = tmp / BASE;
		c[i*6 + 1] = tmp % BASE;
		tmp = tmp / BASE;
		c[i*6 + 2] = tmp % BASE;
		tmp = tmp / BASE;
		c[i*6 + 3] = tmp % BASE;
		tmp = tmp / BASE;
		c[i*6 + 4] = tmp % BASE;
		c[i*6 + 5] = tmp / BASE;
	}
}



// 5개씩 압축 . 절충 
void mul(uint *a, uint *b, lluint *c){

	int newN = (MAXN-1)/5+1; // 26
	int i = 25;
	aa[i] = a[i*5+2] * BM[2] + a[i*5+1] * BM[1] + a[i*5];
	bb[i] = b[i*5+2] * BM[2] + b[i*5+1] * BM[1] + b[i*5];
	for (i = 0; i <=24 ; ++i){
		aa[i] = a[i*5+4] * BM[4]
			  + a[i*5+3] * BM[3]
			  + a[i*5+2] * BM[2]
			  + a[i*5+1] * BM[1]
			  + a[i*5] ;
		bb[i] = b[i*5+4] * BM[4]
			  + b[i*5+3] * BM[3]
			  + b[i*5+2] * BM[2]
			  + b[i*5+1] * BM[1]
			  + b[i*5] ;
	}

	for (int i = 0 ; i < newN * 2 ; ++i)
		cc[i] = 0;

	for (int i = 0 ; i < newN ; ++i){
		for (int j = 0 ; j < newN ; ++j){
			int k = i + j;
			cc[k] = cc[k] + (lluint)aa[i] * bb[j];
		}
	}

	for (int i = 0; i < newN * 2 - 1 ; ++i){
		if (cc[i] >= BM[5]) {
			cc[i+1] += cc[i] / BM[5];
			cc[i] %= BM[5];
		}
	}

	for (int i = 0; i < newN * 2; ++i){
		lluint tmp = cc[i];
		//cout << i << " : " << tmp << endl;
		c[i*5] = tmp % BASE;
		tmp = tmp / BASE;
		c[i*5 + 1] = tmp % BASE;
		tmp = tmp / BASE;
		c[i*5 + 2] = tmp % BASE;
		tmp = tmp / BASE;
		c[i*5 + 3] = tmp % BASE;
		c[i*5 + 4] = tmp / BASE;
	}
}


void print(lluint * p, int len){
	bool flag = 0;
	for (int i = len -1 ; i >= 0 ; --i){
		if (p[i]) flag = true;
		if (flag) cout << p[i] << " ";
	}
	cout << endl;
}
void print(uint * p, int len){
	bool flag = 0;
	for (int i = len -1 ; i >= 0 ; --i){
		if (p[i]) flag = true;
		if (flag) cout << p[i] << " ";
	}
	cout << endl;
}

int main(){
	ios::sync_with_stdio();
	srand(1);
	uint A[MAXN+ 5];
	uint B[MAXN+ 5];
	lluint C[MAXN * 2 + 5];
	for (int ttt = 0 ; ttt < 10 ; ++ttt){
		long long int chk = 0;
		for (int tt = 0 ; tt < 100000 ; ++tt){
			for (int i = 0;i < MAXN ; ++i) A[i] = rand() % BASE;
			for (int i = 0;i < MAXN ; ++i) B[i] = rand() % BASE;

			int MODE = 1; // 1 fastest
			switch(MODE){
				case 1: // 5개 씩
					mul(A,B,C);
					break;
				case 2: // 4개 씩
					mul2(A,B,C);
					break;
				case 3: // 6개 씩 (오버플로처리 필요)
					mul3(A,B,C);
					break;
				case 4: // 그냥
					mul1(A,B,C);
					break;
			}

			for (int i = 0 ; i < MAXN * 2 ; ++i){
				chk = (chk + i*C[i] ) % 10;
			}
		}
		cout << chk << "|";
	}
	return 0;
}



