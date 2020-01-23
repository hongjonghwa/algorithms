#include<iostream>
#include<time.h>
#include<set>
using namespace std;

int gseed = 1983;
int rand(){
	gseed = gseed*31+29989;
	return gseed&0x7FFF;
}
int rand(int l, int h){
	return rand() % (h-l+1) + l;
}
//-----------------------------------------------------
class IntSetSTL{
private:
	set<int> S;
public:
	IntSetSTL(int maxelements, int maxval){}
	int size(){return S.size();}
	void insert(int t){ S.insert(t); }
	void report(int *v)
	{	int j = 0;
		set<int>::iterator it;
		for (it = S.begin(); it != S.end(); ++it)
			v[j++] = *it;
	}
};
//-----------------------------------------------------
class IntSetArr{
private:
	int n, *x;
public:
	IntSetArr(int maxelements, int maxval)
	{	x = new int[1+maxelements];
		n = 0;
		x[0] = maxval; // sentinel at x[n]
	}
	int size(){ return n;}
	void insert(int t)
	{	int i,j;
		for (i=0;x[i]<t;i++)
			;
		if (x[i] == t) return;
		//cout << n;
		for (j = n; j >=i;j--)
			x[j+1] = x[j];
		x[i] = t;
		n++;
	}
	void report(int *v)
	{	for (int i = 0 ; i < n ; i++)
			v[i] = x[i];
	}
};
//-----------------------------------------------------
class IntSetList{
private:
	int n;
	struct node{
		int val;
		node *next;
		node(int i , node *p): val(i), next(p){}
		node(){}
	};
	node *head, *sentinel;
	node *freenode;
	node* rinsert(node *p, int t){
		if (p->val < t){
			p->next = rinsert(p->next,t);
		} else if (p->val > t){
			p = new node(t,p);
			n++;
		}
		return p;
	}
public:
	IntSetList(int maxelements, int maxval): n(0)
	{	sentinel = head = new node(maxval,0);
		freenode = new node[maxelements];
	}
	int size() {return n;}
	void insert(int t) { 
		node **p;
		p = &head;
		while ((*p)->val < t){ // exist sentinel
			p = &((*p)->next);
		}
		if ((*p)->val == t) return;
		freenode->val = t;
		freenode->next = *p;
		*p = freenode;
		freenode++;
		//(*p) = new node(t,(*p)-->next);
		//(*p) = new node(t,(*p)); // Attention!!!
		n++;
	}
	void insert2(int t) { 
		node **p;
		p = &head;
		while ((*p)->val < t) // exist sentinel
			p = &((*p)->next);
		if ((*p)->val == t) return;
		//(*p) = new node(t,(*p)-->next);
		(*p) = new node(t,(*p)); // Attention!!!
		n++;
	}
	void insert_recursion(int t) { head = rinsert(head,t); }
	void report(int *v)
	{	int j = 0;
		for (node *p = head ; p != sentinel; p = p->next)
			v[j++] = p->val;
	}
};
//-----------------------------------------------------
class IntSetBitVec{
private:
	enum { BITSPERWORD = 32, SHIFT = 5, MASK = 0x1F };
	int n, hi, *x;
	void set(int i){        x[i>>SHIFT] |=  (1<<(i & MASK)); }
	void clr(int i){        x[i>>SHIFT] &= ~(1<<(i & MASK)); }
	int test(int i){ return x[i>>SHIFT] &   (1<<(i & MASK)); }
public:
	IntSetBitVec(int maxelements, int maxval){
		hi = maxval;
		x = new int[1+hi/BITSPERWORD];
		for (int i = 0; i < hi; i++)
			clr(i);
		n = 0;
	}
	int size(){ return n; }
	void insert(int t){
		if (test(t)) return;
		set(t);
		n++;
	}
	void report(int *v){
		int j = 0;
		for (int i = 0; i < hi; i++)
			if (test(i)) v[j++] = i;
	}
};
//-----------------------------------------------------
class IntSetBST{
private:
	int n, *v, vn;
	struct node{
		int val;
		node *left, *right;
		node(int v): val(v), left(0), right(0) {}
	};
	node *root;
	node *rinsert(node *p, int t){
		if (p==0){
			p = new node(t);
			n++;
		}else if (t < p->val){
			p->left = rinsert(p->left, t);
		}else if (t > p->val){
			p->right = rinsert(p->right, t);
		}
		return p;
	}
	void traverse(node *p)
	{	if (p==0) return;
		traverse(p->left);
		v[vn++] = p->val;
		traverse(p->right);
	}
public:
	IntSetBST(int maxelements, int maxval): root(0), n(0){}
	int size() { return n; } 
	void insert2(int t) { root = rinsert(root,t); }
	void insert(int t) { 
		node **p;
		p = &root;
		while((*p)){
			if ( t < (*p)->val)
				p = &((*p)->left);
			else if ( t > (*p)->val)
				p = &((*p)->right);
			else break;
		}
		if ((*p)) return; // (*p)->val == t 가 확실함 
		//if ((*p)->val == t) return;
		(*p) = new node(t);
		//root = rinsert(root,t); 
	}
	void report(int *x) { v = x; vn = 0; traverse(root); }
};
//-----------------------------------------------------
class IntSetBins{
private:
	int n, bins, maxval;
	struct node{
		int val;
		node *next;
		node(int v, node *p):val(v),next(p){}
		node(){}
	};
	node **bin, *sentinel;
	node *freenode;
	node *rinsert(node *p, int t) {	
		if (p->val < t){
			p->next = rinsert(p->next,t);
		}else if (p->val > t){
			p = new node(t, p);
			n++;
		}
		return p;
	}
public:
	IntSetBins(int maxelements, int pmaxval){
		bins = maxelements;
		maxval = pmaxval;
		bin = new node*[bins];
		sentinel = new node(maxval,0);
		for (int i = 0 ;i < bins;i++)
			bin[i] = sentinel;
		n = 0;
		freenode = new node[maxelements];
	}
	int size() { return n; }
	void insert(int t){
		int i = t / (1 + maxval/bins); // check??
		node **p;
		p = &bin[i];
		while ( (*p)->val < t )
			p = & ((*p)->next);
		if ((*p)->val == t ) return;
		freenode->val = t;
		freenode->next = *p;
		(*p) = freenode;
		freenode++;
		//(*p) = new node(t,(*p));
		//bin[i] = rinsert(bin[i],t);
	}
	void insert1(int t){
		int i = t / (1 + maxval/bins); // check??
		bin[i] = rinsert(bin[i],t);
	}
	void report(int *v){
		int j = 0;
		for (int i = 0; i < bins; i++)
			for (node *p = bin[i]; p != sentinel; p = p->next)
				v[j++] = p->val;
	}
};
//-----------------------------------------------------

const int MAXN = 1000 * 100 * 1;
const int MAXVAL = 1000 * 1000 * 100;
int main(){

	long long int clk = clock();

	//IntSetSTL setImpl(MAXN, MAXVAL);
	//IntSetArr setImpl(MAXN, MAXVAL);
	//IntSetList setImpl(MAXN, MAXVAL);
	//IntSetBitVec setImpl(MAXN, MAXVAL);
	IntSetBST setImpl(MAXN, MAXVAL);
	//IntSetBins setImpl(MAXN, MAXVAL);

	for (int i =  0 ; i < MAXN ; ++i){
		//rand(1,MAXVAL);
		setImpl.insert(rand(1, MAXVAL));
		//break;
	}
	int *v = new int [MAXN];
	setImpl.report(v);
	for (int i = 0 ; i <= 10 ; ++i)
		cout << " " << v[i];
	cout << endl;


	cout << "Time is : "<<( (double)clock()-clk)/CLOCKS_PER_SEC << endl;
	cout << "1e7 rand() : 0.074" << endl;
	//cout << "1e7 rand(),StlSetInsert : 4.500" << endl;
	//cout << "1e7 rand(),ArrInsert : 23.977" << endl;
	cout << "1e5 rand(),StlSetInsert    : 0.045 " << endl;
	cout << "1e5 rand(),ArrInsert       : 0.244 " << endl;
	cout << "1e5 rand(),ListInsert      : 0.996 " << endl;
	cout << "1e5 rand(),ListInsert NoRecur    : 0.548 " << endl;
	cout << "1e5 rand(),ListInsert NoRecur Alloc   : 0.459 " << endl;
	cout << "1e5 rand(),BitVectorInsert : 0.579 " << endl;
	cout << "1e5 rand(),BTreeInsert     : 0.0145" << endl;
	cout << "1e5 rand(),BTreeInsert     : 0.0137" << endl;
	cout << "1e5 rand(),BinsInsert      : 0.033" << endl;
	cout << "1e5 rand(),BinsInsert NoRecur    : 0.024" << endl;
	cout << "1e5 rand(),BinsInsert NoRecur Alloc   : 0.022" << endl;
}
