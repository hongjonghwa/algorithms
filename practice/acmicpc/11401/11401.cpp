#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>
#include<ctime>

using namespace std;

int MOD = 1000000007;

long long int exp(int a, int x, int mod){
	if (x == 0) return 1;
	if (x == 1) return a;
	if (x % 2 == 1) return exp(a, x-1, mod)*a % mod;
	long long int ret = exp(a, x/2, mod);
	return (ret * ret) % mod;
}
long long pow(long long x, long long y, int mod)
{
    long long ans = 1;
    while(y > 0) {
        if(y&1) {
            ans = (ans * x) % mod;
        }
        x = (x*x)  % mod;
        y = y >> 1;
    }
    return ans;
}

// 페르마 소정리, nCr MOD p 계산, p 는 소수
long long int fermat(int n, int r){
	// Prerequisite : p is prime or gcd(n,p) == 1
	long long int ret = 1, divider = 1;
	for (int i = 1 ; i <= n ; ++i){
		ret = (ret * i ) % MOD ;
		if (i == r) divider = (divider * ret) % MOD;
		if (i == n-r) divider = (divider * ret) % MOD;
	}
	ret = ( ret * exp(divider, MOD-2, MOD) ) % MOD;

	return ret;
}

int main(){
	int n, k;
    
    //cin >> n >> k;

	n = 987654321, k = 123456789;

	clock_t begin = clock();

	for (int i = 0 ;  i < 1000000 ; ++i)
		exp(n+i,k-i,MOD);

	clock_t end1 = clock();

	for (int i = 0 ;  i < 1000000 ; ++i)
		pow(n+i,k-i,MOD);

	clock_t end2 = clock();

	cout << "recur : " << end1-begin << endl;
	cout << "while : " << end2-end1 << endl;
	cout << "CLOCKS_PER_SEC : " << CLOCKS_PER_SEC << endl;

	cout << exp(n,k,MOD);
	cout << endl;
	cout << pow(n,k,MOD);
	//cout << fermat(n,k);
	return 0;
}
