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

void buyCar(CAR *newcar) {
	//TODO :차량 입고
	//cout << "#";
}

int sellCar(int from_age, int to_age, int from_passenger, int to_passenger, int from_engine, int to_engine, int from_price, int to_price) {
	//TODO : 주문, return 주문번호
	return 0;
}

void refund(int orderNo) {
	//TODO : 주문취소
}
int getInven() {
	//TODO : 초기화, return 남은 차량 대수
	return 0;
}

void init() {
	// 초기화 함수가 있었는지 기억 안남
}