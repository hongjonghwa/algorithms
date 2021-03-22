#include<iostream>

using namespace std;

int cnt[10];
struct Init{ 
    Init(){
	    for (int i = 0; i < 10 ; i++)
		    cnt[i] = i * i ;
    } 
} init; // static initialize - 변수명이 있어야 코드 실행 

struct II{
	int x[10];
    int a, b;
} i1; // 여기서 선언되어 있으면 내부 변수 값이 0으로 초기화 되어 있다.

int main(){
	ios::sync_with_stdio();

	for (int i = 0; i < 10 ; ++i)
		cout << cnt[i] << " ";
	cout << endl;

	for (int i = 0; i < 10 ; ++i)
		cout << i1.x[i] << " ";
	cout << endl;
    cout << i1.a << "," <<i1.b << endl;

	II i2; // 로컬 영역에서 선언하면 내부 변수 값이 0으로 초기화 되지 않는다.
	for (int i = 0; i < 10 ; ++i)
		cout << i2.x[i] << " ";
	cout << endl;
    cout << i2.a << "," <<i2.b << endl; // <-- warning 발생

	return 0;
}



