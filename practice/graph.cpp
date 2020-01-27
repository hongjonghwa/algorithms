#include<iostream>
using namespace std;

struct AdjListNode{
	int dest;
	AdjListNode* next;
};
struct AdjList{
	AdjListNode* head;
};
struct Graph{
	int V;
	AdjList *array;
	Graph(int V){
		this->V =  V;
		array = new AdjList[V];
		for (int i = 0 ; i < V ; ++i)
			array[i].head = NULL;
	}
	~Graph() { delete[] array; }
	AdjListNode* newAdjListNode(int dest){
		AdjListNode* newNode = new AdjListNode;
		newNode->dest = dest;
		newNode->next = NULL;
		return newNode;
	}
	void addEdge(int src, int dest){
		AdjListNode* newNode = newAdjListNode(dest);
		newNode->next = array[src].head;
		array[src].head = newNode;
	}
	void print(){
		for (int v = 0; v < V ; ++v){
			AdjListNode* next = array[v].head;
			cout << "List " << v << " :";
			while (next){
				cout << " " << next->dest;
				next = next->next;
			}
			cout << endl;
		}
	}
};

int main(){
	Graph g(5);
	g.addEdge(0,1);
	g.addEdge(1,2);
	g.addEdge(2,3);
	g.addEdge(3,2);
	g.addEdge(3,4);
	g.print();
	
	for (int i = 0; i < g.V; ++i){
		AdjListNode* next = g.array[i].head;
		cout << i << " : ";
		while (next){
			cout << next->dest << " " ;
			next = next->next;
		}
		cout << endl;
	}

	return 0;
}

