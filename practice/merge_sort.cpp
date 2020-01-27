#include<iostream>
using namespace std;
int seed = 1983;
int rand(){
	seed = seed *777771 + 2387691;
	return (seed>>16) & 0x7FFF;
}

void merge_sort(int A[], int l, int h){
	if (l == h) return;
	int m = (l+h)/2;
	merge_sort(A, l,m);
	merge_sort(A, m+1,h);
	
	int tmp[h-l+1];
	int i = l, j = m+1, k = 0;
	while( i < m+1 && j < h+1){
		if (A[i] <= A[j]) tmp[k++] = A[i++];
		else tmp[k++] = A[j++];
	}
	while( i < m+1 ) tmp[k++] = A[i++];
	while( j < h+1 ) tmp[k++] = A[j++];
	for (int t = 0 ; t < h-l+1 ; ++t)
		A[l+t] = tmp[t];
}

int main(){
	ios::sync_with_stdio(false);
	int A[10] = { 1,5,7,9,3,2,8,6,0,4};
	for (int i = 0 ; i < 10 ; ++i) cout << A[i] << " "; cout << endl;
	merge_sort(A, 0,9);
	for (int i = 0 ; i < 10 ; ++i) cout << A[i] << " "; cout << endl;

	int MAX_N = 1000000;
	int B[MAX_N];
	for (int i = 0; i < MAX_N ; ++i) B[i] = rand();
	cout << "run!!!" << endl;
	merge_sort(B,0,MAX_N-1);
	return 0;
}
