#include<iostream>

/*
	메모리 사용 제한 : Heap, Stack 등 모두 합쳐 512M
	시간 제한 : 10초 이내 ( 시험당시 가장 빠른 사람은 1초대 였음)
*/

using namespace std;

struct CAR {
	int age;		// 0 ~ 11
	int passenger;	// 2 ~ 12
	int engine;		// 1000 ~ 3999
	int price;		// 10000 ~ 49999
};

struct Store{
	int age, passenger, engine, price, orderNo;
} store [1000001];
int s, o, r;


void buyCar(CAR *newcar) {
	//TODO :차량 입고
	//cout << "#";
	++s;
	store[s].age = newcar->age;
	store[s].passenger = newcar->passenger;
	store[s].engine = newcar->engine;
	store[s].price = newcar->price;
	store[s].orderNo = 0;
}

int sellCar(int from_age, int to_age, int from_passenger, int to_passenger, int from_engine, int to_engine, int from_price, int to_price) {	
	++o;

	int tt = 0;
	for (int i = 1 ; i <= s ; ++i){
		if (store[i].orderNo == 0 &&
			store[i].age >= from_age && store[i].age <= to_age &&
			store[i].passenger >= from_passenger && store[i].passenger <= to_passenger &&
			store[i].engine >= from_engine && store[i].engine <= to_engine &&
			store[i].price >= from_price && store[i].price <= to_price)
		{
			store[i].orderNo = o;
			tt++;
		}
	}

	return o;
}

void shrink() {
	int idx = 0;
	for (int i = 1 ; i<= s ; ++i){
		if (store[i].orderNo == 0){
			store[++idx] = store[i];
		}
	}
	s = idx;
}

void refund(int orderNo) {
	// ++r;
	//TODO : 주문취소
	for (int i = 1 ; i <= s ; ++i)
		if (store[i].orderNo == orderNo)
			store[i].orderNo = 0;		

	shrink();
}
int getInven() {
	int ret = 0;
	for (int i = 1 ; i <= s ; ++i)
		if (store[i].orderNo == 0) 
			ret++;
	return ret;
}

void init() {
	s = o = r = 0;
}
