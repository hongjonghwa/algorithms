#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include<time.h>
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

	for (int i = 0 ; i < MAXN ; ++i){
		for (int j = 0 ; j < MAXN ; ++j){
			c[i+j] += a[i] * b[j]; // BASE36 의 작은 값이라 오버플로워가 발생하지 않는다.
		}
	}
	for (int i = 0; i < MAXN * 2 -1 ; ++i){
		if (c[i] >= BASE) {
			c[i+1] += c[i] / BASE;
			c[i] %= BASE;
		}
	}

}
uint aa[32], bb[32];
lluint cc[64];

// 4개씩 압축 . BASE36에서 여유있게,,
void mul2(uint *a, uint *b, lluint *c){

	int newN = MAXN/4;
	for (int i = 0; i < newN ; ++i){
		aa[i] = a[i*4];
		aa[i] += a[i*4+1]+BM[1];
		aa[i] += a[i*4+2]+BM[2];
		aa[i] += a[i*4+3]+BM[3];
		bb[i] = b[i*4];
		bb[i] += b[i*4+1]+BM[1];
		bb[i] += b[i*4+2]+BM[2];
		bb[i] += b[i*4+3]+BM[3];
		//aa[i] = ( (a[i*4+3] * BASE + a[i*4+2]) * BASE + a[i*4+1] ) * BASE + a[i*4];
		//bb[i] = ( (b[i*4+3] * BASE + b[i*4+2]) * BASE + b[i*4+1] ) * BASE + b[i*4];
	}

	for (int i = 0 ; i < newN * 2 ; ++i)
		cc[i] = 0;

	for (register int i = 0 ; i < newN ; ++i){
		for (register int j = 0 ; j < newN ; ++j){
			// 오버 플로워에 주의... 연산 순서에따름
			// 결과 변수만 64bit로 바꿔서는 안됨... 
			cc[i+j] += (lluint)aa[i] * bb[j];
			//if (cc[i+j]<0) cout<< "! " << i << "," << j << "!"; // overflow check
		}
	}
	for (int i = 0; i < newN * 2 - 1 ; ++i){
		if (cc[i] >= BM[4]) {
			cc[i+1] += cc[i] / BM[4];
			cc[i] %= BM[4];
		}
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
main(){
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
			//print(A, MAXN);
			//print(B, MAXN);

			//mul( A, B, C); // 5 압축 N^2 연산 중 오버 처리 불필요
			//mul3( A, B, C); // 6압축 N^2 연산 중 오버 플로 방지 필요 --> (stack smashing 에러)
			mul2( A, B, C); // 4압축 
			//mul1( A, B, C); // 무압축
			for (int i = 0 ; i < MAXN * 2 ; ++i){
				//assert(C[i]> 0);
				chk = (chk + i*C[i] )% 10;
			}
			//print(C,MAXN*2);
		}
		cout << chk << "|";
	}
	return 0;
	cout << endl << endl << endl;
	cout << aa[0] << endl;
	cout << bb[0] << endl;
	cout << cc[0] << endl;
	cout << cc[1] << endl;

	print(A, MAXN);
	print(B, MAXN);
	print(C, MAXN * 2);

}



