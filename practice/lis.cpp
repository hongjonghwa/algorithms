#include <iostream>
using namespace std;
 
int lowerBound(int A[], int lo, int hi, int key){
	while (hi - lo > 1){
		int mid = (lo+hi)/2;
		// 불변 lo는 key보다 작다, hi 는 크거나 같다
		if (A[mid] >= key) hi = mid;
		else lo = mid;
	}
	return hi;
}
int lis(int A[], int size){
	if (!size) return 0;

	int tail[size];
	int len = 1;
	tail[0] = A[0];
	for (int i = 1 ; i < size ; ++i){
		if (A[i] < tail[0]) 
			tail[0] = A[i];
		else if (A[i] > tail[len-1])
			tail[len++] = A[i];
		else
			tail[lowerBound(tail,0,len-1,A[i])] = A[i];
	}

	return len;
	//  길이만 가져오고, 배열은 못 가져옴
}
 
int main() {
	int A[9] = { 2, 5, 3, 7, 11, 8, 10, 13, 6 };
	cout << lis(A, 9) << endl;
	int B[5] = {1,2,3,2,4};
	cout << lis(B, 5) << endl;
   return 0;
}

