/* Copyright (C) 1999 Lucent Technologies */
/* From 'Programming Pearls' by Jon Bentley */

/* priqueue.cpp -- priority queues (using heaps) */

#include <iostream>
#define MIN(x,y) ((x)<(y) ? (x) : (y))
using namespace std;

// define and implement priority queues

template<class T>
class priqueue {
private:
	int	n, maxsize;
	T	*x;
	void swap(int i, int j)
	{	T t = x[i]; x[i] = x[j]; x[j] = t; }
public:
	priqueue(int m)
	{	maxsize = m;
		x = new T[maxsize+1];
		n = 0;
	}
	void insert(T t)
	{	int i, p;
		x[++n] = t;
		for (i = n; i > 1 && x[p=i/2] > x[i]; i = p)
			swap(p, i);
	}
	T extractmin()
	{	int i, c;
		T t = x[1];
		x[1] = x[n--];
		/* equivalent siftdown(1,n)
		for (i = 1; (c=2*i) <= n; i = c) {
			if (c+1<=n && x[c+1]<x[c])
				c++;
			if (x[i] <= x[c])
				break;
			swap(c, i);
		}
		*/
		siftdown(1,n);
		return t;
	}
	void report()
	{
		cout << "Heap size : " << n << "/" << maxsize << endl;
		for (int i = 1 ; i <= MIN(n, 10) ; ++i)
			cout << x[i] << " ";
		cout << endl;
	}

	void siftdown(int l, int u){
		// Pre  : heap(l+1,u)
		// Post : heap(l  ,u)
		// 작동 : l을 쉬프트 다운
		int i, c;
		for (i = l ; (c=i*2) <= u ; i = c){
			if (c+1 <= u && x[c+1] < x[c])
				c++;
			if (x[i] <= x[c])
				break;
			swap(c,i);
		}
	}
};

// sort with priority queues (heap sort is strictly better)

template<class T>
void pqsort(T v[], int n)
{	priqueue<T> pq(n);
	int i;
	for (i = 0; i < n; i++)
		pq.insert(v[i]);
	for (i = 0; i < n; i++)
		v[i] = pq.extractmin();
}

// main

int main()
{	const int	n = 10;
	int	i, v[n];
	if (1) { // Generate and sort
		for (i = 0; i < n; i++)
			v[i] = (n-i) % 20;
		pqsort(v, n);
		for (i = 0; i < n; i++)
			cout << v[i] << "\n";
	} else if(2) {
		
	} else { // Insert integers; extract with 0
		priqueue<int> pq(100);
		while (cin >> i)
			if (i == 0)
			{
				pq.report();
				cout << pq.extractmin() << "\n";
				pq.report();
			}
			else
				pq.insert(i);
	}

	return 0;
}
