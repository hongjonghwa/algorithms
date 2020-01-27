#include<iostream>
#include<time.h>
#include<assert.h>
#include<stdlib.h>
using namespace std;

int g_seed = 1983;
int fastrand(){
	g_seed = 214013 * g_seed + 2531011;
	return (g_seed >> 16) & 0x7FFF;
}

const int MAXN = 1000;
int A[MAXN+1][MAXN+1];

int main(){
	int m = 8, n = 3;
	for (int i = 1 ; i <= m; i++){
		if (rand() % (m-i+1) < n){ cout << "pick :  " << i << endl; n--;};
		//m--;
		//cout << "m: " << m << " ,n:" << n << endl;
	}

}
