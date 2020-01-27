#include<iostream>
using namespace std;

int seed = 1983;
int rand(){
	seed = seed*1234567 + 3275157;
	return (seed>>16) & 0x7FFF;
}


struct Item{
	int x,y,z;
	Item(){
	}
	Item(int _x, int _y, int _z) : x(_x), y(_y){
		z = 0;
	}
	void print(){
		cout << x << ":" << y << endl;
	}
};

Item item[10];

void merge_sort(int l, int h){
	if (l == h) return;
	int m = (l+h)/2;
	merge_sort(l,m);
	merge_sort(m+1,h);
	
	Item tmp[h-l+1];
	int i = l, j = m+1, k = 0;
	while( i < m+1 && j < h+1){
		if (item[i].y <= item[j].y) tmp[k++] = item[i++];
		else tmp[k++] = item[j++];
	}
	while( i < m+1 ) tmp[k++] = item[i++];
	while( j < h+1 ) tmp[k++] = item[j++];
	for (int t = 0 ; t < h-l+1 ; ++t)
		item[l+t] = tmp[t];
}

int main(){
	ios::sync_with_stdio(false);
	for (int i = 0 ; i < 10 ; ++i){
		item[i].x = rand();
		item[i].y = rand();
	}
	for (int i = 0 ; i < 10 ; ++i) item[i].print(); cout << endl;

	merge_sort(0,9);
	for (int i = 0 ; i < 10 ; ++i) item[i].print(); cout << endl;
	return 0;
}
