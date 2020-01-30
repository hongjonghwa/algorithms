#include<iostream>
#include<time.h>

/*
	메모리 사용 제한 : Heap, Stack 등 모두 합쳐 512M
	시간 제한 : 10초 이내 ( 시험당시 가장 빠른 사람은 1초대 였음)
*/

using namespace std;

struct Debug{
	long rtime = 0;
	long stime = 0;	
} debug;

struct CAR {
	int age;		// 0 ~ 11
	int passenger;	// 2 ~ 12
	int engine;		// 1000 ~ 3999
	int price;		// 10000 ~ 49999
};

struct Store{
	int age, passenger, engine, price;
	Store *next;
} store [1100001];
Store *head;
Store *order[20000];

int frees, o;
int debug_r;

void init() {
	// 초기화 함수가 있었는지 기억 안남
	head = 0;
	frees = o = 0;
	debug_r = 0;
	for (int i = 0 ; i < 20000 ; ++i) order[i] = 0;
}



void buyCar(CAR *newcar) {
	//TODO : 입고
	store[frees].age = newcar->age;
	store[frees].passenger = newcar->passenger;
	store[frees].engine = newcar->engine;
	store[frees].price = newcar->price;
	store[frees].next = head;
	head = &store[frees];
	++frees;
}

int sellCar(int from_age, int to_age, int from_passenger, int to_passenger, int from_engine, int to_engine, int from_price, int to_price) {	
	long clk = clock();
	++o;
	// cout << " sell called : " << o << endl;
	Store* p = head;
	Store* p_next;
	Store* store_last = 0;	
	// printf("order %d\n", o);

	while (p){
		p_next = p->next;
		if (
			p->age >= from_age && p->age <= to_age &&
			p->passenger >= from_passenger && p->passenger <= to_passenger &&
			p->engine >= from_engine && p->engine <= to_engine &&
			p->price >= from_price && p->price <= to_price
		){ 
			// store 에서 삭제 
			if (store_last) store_last->next = p->next;
			else head = p->next;

			// order 에 추가
			p->next = order[o];
			order[o] = p;			
			// 조건이 맞으면, head 가 이동, 
		}else{
			store_last = p; // 이전 노드 기억
		}
		p =  p_next;
		
	}

	debug.stime += clock()-clk;
	return o;
}
void refund(int orderNo) {
	long clk = clock();
	++debug_r;
	int tt = 0;
	//TODO : 주문취소
	if (order[orderNo] == 0) {
		// printf("order not found!\n");
 		return; // order 가 없으면
	}


	Store * order_last = order[orderNo];
	while (order_last->next) order_last = order_last->next;
	order_last->next = head;
	head = order[orderNo];

	/* clean */
	for (int i = 0 ; i <= o ; ++i){
		order[i] = 0;

	}

	debug.rtime += clock()-clk;
}
int getInven() {
	
	//TODO : 초기화, return 남은 차량 대수
	int ret = 0;
	

	Store* p = head;
	while (p){
		ret++;
		p = p->next;
	}
		
		
	/*
	cout << endl;
	cout << "freeS: " << frees << " O: " << o << " debugR: " << debug_r << endl;
	cout << "Sell Time: " << ((double)debug.stime/CLOCKS_PER_SEC) << endl;
	cout << "Refund Time: " << ((double)debug.rtime/CLOCKS_PER_SEC) << endl;
  */
	return ret;
}

