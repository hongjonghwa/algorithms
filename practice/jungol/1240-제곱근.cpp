#include<iostream>

using namespace std;

int main() {
	unsigned long long n;
	cin >> n;
	long long hi = 1ll<<32, lo = 0;
	while (hi>lo+1){
		long long mid = (hi+lo)/2;
		if (mid * mid > n) hi = mid;
		else lo = mid;
	}
	cout << lo << "\n";
}
