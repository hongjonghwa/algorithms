#include<iostream>
#define SWAP(x,y,t) do{ t _tmp = (x) ; (x) = (y); (y) = _tmp; } while(0);
using namespace std;

inline int swap_int(int& x, int& y){
	int t=x;x=y;y=t;
}

int seed = 1983;
int rand(){
	seed = seed*777771 + 238769l;
	return  (seed >> 16) & 0x7FFF;
}

void quick_sort(int A[], int lo, int hi){
	if (lo >= hi) return;

	int pivot = A[lo], mid = lo;
	for (int i = lo + 1; i <= hi ; ++i){
		if (A[i] <= pivot){
			++mid;
			swap_int(A[i],A[mid]);
		}
	}
	swap_int(A[lo], A[mid]);

	quick_sort(A, lo, mid-1);
	quick_sort(A, mid+1, hi);
}

int main(){
	ios::sync_with_stdio(false);
	int A[10] = { 1,5,7,9,3,2,8,6,0,4};
	for (int i = 0 ; i < 10 ; ++i) cout << A[i] << " "; cout << endl;
	quick_sort(A, 0,9);
	for (int i = 0 ; i < 10 ; ++i) cout << A[i] << " "; cout << endl;

	int MAX_N = 1000000;
	int B[MAX_N];
	for (int i  = 0; i < MAX_N; ++i)
		B[i] = rand();
	cout << "run!!!" << endl;
	quick_sort(B,0,MAX_N-1);
	
	return 0;
}
