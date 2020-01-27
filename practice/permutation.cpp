/* 
   순열 알고리즘
   */

#include<iostream>
#define SWAP(x,y,t) do{ t TMP = (x); (y) = (x); (x) = TMP }while(0)
using namespace std;
int swap_int (int &x, int &y){
	int t = x;
	x = y;
	y = t;
}
void perm(int A[], int s, int e){
	if (s == e){
		for (int i = 0 ; i < e; ++i) cout << " " <<A[i]; cout << endl;
		return;
	}
	for (int i = s; i < e ; i++){
		swap_int(A[i], A[s]);
		perm(A, s+1, e);
		swap_int(A[i], A[s]);
	}
}
int main(){
	int A[] = { 1,2,3,4,5,6,7,8,9,0};
	perm(A, 0, 3);
	return 0;
}
