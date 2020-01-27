#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>
#define lint long long int

using namespace std;

int MOD = 1000000007;

lint exp(int a, int x, int p){
	if (x==0) return 1;
	if (x==1) return a % p;
	lint half = exp(a, x/2, p);
	if ((x%2) == 1){
		return (half*half*a) %p;
	}else return (half*half) %p;

}

lint fermat(int n, int r, int p){
	// Prerequisite : p is prime or gcd(n,p) == 1
	lint upper = 1;
	for (int i = max(r, n-r) + 1 ; i <= n ; ++i) upper = (upper * i ) % p ;
	//cout << "upper : " << upper << endl;
	lint lower = 1;
	for (int i = 1 ; i <= min(r, n-r) ; ++i) lower *= (lint)i;
	//cout << "lower : " << lower << endl;
	// 곱셈 역원은 lower ^ (p-2)
	lint inverse_lower = exp(lower, p-2, p);

	return (upper * inverse_lower) % p;
}

int main(){
    ios::sync_with_stdio(false);
    setbuf(stdout, NULL);
    
	int n, r, p;
    
    //cin >> n >> k;
	//cout << normal(25,2,MOD) << endl;
	//cout << pascal(25,2,MOD) << endl;
	cout << pascal(55,2,MOD) << endl;
	cout << fermat(55,2,MOD) << endl;

    return 0;
}
