#include<iostream>
#define MIN(x,y) ((x)<(y)?(x):(y))
#define MID(x,y) (((x)+(y))/2)
#define INF 987654321

using namespace std;

struct RMQ{
	int n;
	int *rangeMin;
	RMQ(int *array, int size){
		n = size;
		rangeMin = new int[n*4];
		init (array, 1, 0, n-1);
	}
	int init(int *array, int node, int left, int right){ // 최소값 반환
		cout << node << " : " << left << "-" << right << endl;
		if (left == right)
			return rangeMin[node] = array[left];
		int mid = MID(left, right);
		int leftmin = init(array, node*2, left, mid);
		int rightmin = init(array, node*2+1, mid+1, right);
		return rangeMin[node] = MIN (leftmin, right);
	}
	int update(int index, int newValue, int node, int left, int right){
		if (index < left || index > right) return rangeMin[node]; // 범위 밖
		if (left==right) return rangeMin[node] = newValue;
		int mid = MID(left, right);
		int leftmin = update(index, newValue, node*2, left, mid);
		int rightmin = update(index, newValue, node*2+1, mid+1, right);
		return rangeMin[node] = MIN(leftmin, rightmin);
	}
	int update(int index, int newValue){
		return update(index, newValue, 1, 0, n-1);
	}

	int query(int l, int r, int node, int left, int right){
		//cout << l << " " << r << " " << node << " " << left << " " << right << endl;
		if (left > r  || right < l) return INF;// l~r 이 범위 밖
		if (left >= l && right <= r) return rangeMin[node];
		int mid = MID(left, right);
		int leftmin = query(l,r, node*2, left, mid);
		int rightmin = query(l,r, node*2+1 , mid+1, right);
		return MIN(leftmin, rightmin);
	}

	int query(int l, int r){
		cout << "N : " << n << endl;
		return query(l,r,1,0,n-1);
	}
	void print(){
		for (int i = 1 ; i <= n*2 ; ++i){
			cout << rangeMin[i] << " ";
		}
		cout << endl;
	}
	
};
int main(){
	/*

	int A[4] = {1,2,3,4};
	RMQ rmq(A,4);
	rmq.print();
	*/
	int A[10] = {1,2,3,4,5,9,8,7,6,0};

	//int A[8] = {1,2,3,4,5,6,7,8};
	RMQ rmq(A,10);
	rmq.print();
	cout << rmq.query(0,3) << endl;
	cout << rmq.query(4,6) << endl;
	cout << rmq.query(0,9) << endl;
	rmq.update(1,0);
	cout << rmq.query(0,3) << endl;
	rmq.update(5,4);
	cout << rmq.query(5,7) << endl;
	cout << rmq.query(6,7) << endl;

	return 0;
}
