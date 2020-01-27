#include<iostream>
using namespace std;

struct Node{
	int x,y,z;
	Node(int _x, int _y, int _z) : x(_x), y(_y), z(_z){ }
	Node(){}
};

struct vector{
	Node *arr, *tmp;
	int size, reserve;

	void add(Node node){
		if (size>= reserve) expand();
		arr[size++] = node;
	}
	void expand(){
		//delete[] tmp;
		tmp = new Node[reserve*2];
		for (int i = 0 ; i < reserve ; ++i) 
			tmp[i] = arr[i];
		delete[] arr;
		arr = tmp;
		reserve *=2;
	}
	Node get(int i){
		return arr[i];
	}
	void clear(){
		delete[] arr;
		reserve = 4;
		arr = new Node[reserve];
		size = 0;
	}
	void print(){
		cout << "[" << size << "/" << reserve << "] ";
		for (int i = 0; i < size ; ++i)
			cout << arr[i].x << " ";
		cout << endl;
	}

	int getSize(){ return size; }
	int getReserve(){ return reserve; }
	vector() {
		reserve = 4;
		arr = new Node[reserve];
		size = 0;
	}
	~vector(){
		delete[] arr;
	}

};


vector adj[6];
int main(){
	adj[1].print();
	adj[1].add(Node(1,2,3));
	adj[1].print();
	adj[1].add({1,2,3});
	adj[1].print();
	adj[1].add(Node(3,2,3));
	adj[1].print();
	adj[1].add({5,2,3});
	adj[1].print();
	adj[1].add({5,2,3});
	adj[1].print();
	adj[1].add({7,2,3});
	adj[1].print();
	adj[1].add({7,2,3});
	adj[1].print();
	adj[1].add({9,2,3});
	adj[1].print();
	adj[1].add({9,2,3});
	adj[1].print();
}
