#include<iostream>
#define SWAP(x,y,t) do{ t _tmp = (x) ; (x) = (y); (y) = _tmp; } while(0);
#define MAX(x,y) ((x)>(y) ? (x) : (y))
using namespace std;

inline int swap_int(int& x, int& y){
	int t=x;x=y;y=t;
}
template<class T>
inline void swapT(T & a, T & b){
	T tmp(a);
	a = b;
	b = tmp;
}

int seed = 1983;
int rand(){
	seed = seed*777771 + 238769l;
	return  (seed >> 16) & 0x7FFF;
}

struct MaxHeap{
	int *A;
	int size;
	void push(int p){
		A[size++] = p;
		int idx = size-1;
		while (idx > 0 && A[idx] > A[(idx-1)/2]){
			swap_int(A[idx], A[(idx-1)/2]);
			idx = (idx-1)/2;
		}
	}
	void pop(){
		A[0] = A[size-1];
		size--;
		int here = 0;
		while(true){
			int left = here*2+1, right = here*2+2;
			if (left >= size) break; // leaf

			int next = here;
			if (A[next] < A[left]) next = left;
			if (right < size && A[next] < A[right]) next = right;
			if (next == here) break; // bigger
			swap_int (A[here], A[next]);
			here = next;
		}
	}
	bool empty(){ return size == 0; } ;
	int top(){ return A[0]; }
	MaxHeap(int n): size(0){
		A = new int[n];
	};
	~MaxHeap(){
		delete[] A;
	};
	void print(){
		cout << "PRINT***********" <<endl;
		for (int i = 0 ; i < MAX(size, 8) ; ++i)
			cout << A[i] << " " ;
		cout << endl;
	}
};

int main(){
	ios::sync_with_stdio(false);
	int A[10] = { 1,5,7,9,3,2,8,6,0,4};
	for (int i = 0 ; i < 10 ; ++i) cout << A[i] << " "; cout << endl;
	MaxHeap mh(10);
	for (int i = 0 ; i < 10 ; ++i) 
		mh.push(A[i]);
	for (int i = 0 ; i < 10 ; ++i){
		int t = mh.top();
		cout << t << " ";
		//mh.print();
		mh.pop();
	}
	cout << endl;

	int MAX_N = 1000000;
	MaxHeap largemh(MAX_N);
	int B[MAX_N];
	for (int i  = 0; i < MAX_N; ++i)
		B[i] = rand();
	for (int i = 0 ; i < MAX_N ; ++i) 
		largemh.push(B[i]);
	for (int i = 0 ; i < MAX_N ; ++i){
		int t = largemh.top();
		largemh.pop();
	}
	
	return 0;
}
