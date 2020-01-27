#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>
#define lint long long int

using namespace std;

int MOD = 1000000007;

lint normal(lint n, lint r, lint p){
	lint ret = 1;
	for (int i = max(r, n-r) + 1 ; i <= n ; ++i) ret *= i;
	for (int i = 1 ; i <= min(r, n-r) ; ++i) ret /= i;

	return (ret) % p;
}
long long int pascal(int n, int r, int p){
	long long int C[n+1];
	memset(C,0,sizeof(C));
	C[0]=1;
	for (int i = 1 ; i <=n ; i++){
		for (int j = min(i,r) ; j > 0 ; j--){
		//for (int j = i ; j > 0 ; j--){
			//C[j] = (C[j] + C[j-1] ) %p;
			C[j] = (C[j] + C[j-1] );
		}
	}
	return C[r];
}
lint exp(int a, int x, int p){
	if (x==0) return 1;
	if (x==1) return a % p;
	lint ret = exp(a, x/2, p);
	ret = (ret * ret) % p;

	if ((x%2) == 1){
		ret = (ret*a) % p;
	}
	return ret;

}
lint fermat_old(int n, int r, int p){
    // Prerequisite : p is prime or gcd(n,p) == 1
    lint ret = 1;
    for (int i = max(r, n-r) + 1 ; i <= n ; ++i) ret = (ret * i ) % p ;

    for (int i = 1 ; i <= min(r, n-r) ; ++i){
        lint inverse_element = exp(i, p-2, p);
        ret = (ret * inverse_element) % p ;
    }

    return ret;
}

lint fermat(int n, int r, int p){
	// Prerequisite : p is prime or gcd(n,p) == 1
	lint ret = 1;
	for (int i = max(r, n-r) + 1 ; i <= n ; ++i) ret = (ret * i ) % p ;

	lint sum = 1;
	for (int i = 1 ; i <= min(r, n-r) ; ++i){
		if (sum*i > p){
			lint inverse_element = exp(sum, p-2, p);
			ret = (ret * inverse_element) % p ;
			sum = 1;
		}
		sum *= i;
	}
	if (sum != 1){
		lint inverse_element = exp(sum, p-2, p);
		ret = (ret * inverse_element) % p ;
	}

	return ret;
}
lint lucas(int n, int r, int p){
	// Prerequisite : p is prime
	if (r == 0 || r == n) return 1;
	if (r>n) return 0;

	if (n>p){
		int ni = n%p, ri = r%p;
		return (lucas(n/p,r/p,p)*lucas(ni,ri,p)) % p;
	}else{
		return normal(n,r,p);
	}
}

int main(){
    ios::sync_with_stdio(false);
    setbuf(stdout, NULL);
    
	int n, r, p;
    
    //cin >> n >> k;
	n = 1000, r = 500;
	//cout << normal(n,r,MOD) << endl;
	for (int r = 1000; r < 1000; ++r)
	pascal(n,r,MOD);
	cout << pascal(n,r,MOD) << endl;
	//cout << fermat(n,r,MOD) << endl;

    return 0;
}
