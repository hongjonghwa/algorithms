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

struct Order{
	int from_age, to_age, from_passenger, to_passenger, from_engine, to_engine, from_price, to_price;
} order [100000];



struct Store{
	int age,passenger,engine, orderNo;
	Store *next;
} store [1000001];


Store *head[50000];

int s, o, r;

void init() {
	// 초기화 함수가 있었는지 기억 안남
	for (int i = 10000 ; i < 50000 ; ++i)
		head[i] = 0;
	s = o = r = 0;
}



void buyCar(CAR *newcar) {
	//TODO : 입고
	++s;
	store[s].age = newcar->age;
	store[s].passenger = newcar->passenger;
	store[s].engine = newcar->engine;
	store[s].orderNo = 0;
	store[s].next = head[newcar->price];
	head[newcar->price] = &store[s];
}

int sellCar(int from_age, int to_age, int from_passenger, int to_passenger, int from_engine, int to_engine, int from_price, int to_price) {	
	long clk = clock();
	++o;
	order[o].from_age = from_age;
	order[o].to_age = to_age;
	order[o].from_passenger = from_passenger;
	order[o].to_passenger = to_passenger;
	order[o].from_engine = from_engine;
	order[o].to_engine = to_engine;
	order[o].from_price = from_price;
	order[o].to_price = to_price;
	/*
	int tt = 0;
	cout << from_age << "~" << to_age << " ";
	cout << from_passenger << "~" << to_passenger << " ";
	cout << from_engine << "~" << to_engine << " ";
	cout << from_price << "~" << to_price << " ";
	*/
	for (int i = from_price ; i <= to_price ; ++i){
		Store* p = head[i];
		while (p){
			if (
				p->orderNo == 0 
				&& p->age >= from_age && p->age <= to_age
				&& p->passenger >= from_passenger && p->passenger <= to_passenger
				&& p->engine >= from_engine && p->engine <= to_engine
			)
			{
				p->orderNo = o;
				// tt++;
			}
			p = p->next;
		}
	}


	// cout << " ==> s cnt : " << tt << "/" << s << endl;

	debug.stime += clock()-clk;
	return o;
}

Store* rdel(Store * p){
	if (p == 0) return 0;
	else if (p->orderNo == 0){
		p->next = rdel(p->next);
		return p;
	}else{
		return rdel(p->next);
	}
}
void shrink() {
	//TODO : 
	for (int i = 10000 ; i < 50000 ; ++i)
		head[i] = rdel(head[i]);

}
void refund(int orderNo) {
	long clk = clock();
	++r;
	int tt = 0;
	//TODO : 주문취소
	/*
	for (int i = 0 ; i < 12 ; ++i)
		for (int j = 2 ; j < 13 ; ++j)
			for (int k = 1000 ; k < 4000 ; ++k)
	*/
	for (int i = order[orderNo].from_price ; i <= order[orderNo].to_price ; ++i)
	{
		Store* p = head[i];
		while (p){
			if (p->orderNo == orderNo){
				p->orderNo = 0;
				tt++;
			}
			p = p->next;
		}
	}


	shrink();
	/*
	cout << "refund# " << orderNo << " cnt: " << tt << endl;
	*/
	debug.rtime += clock()-clk;
}
int getInven() {
	
	//TODO : 초기화, return 남은 차량 대수
	int ret = 0;
	
	for (int i = 10000 ; i < 50000 ; ++i)
	{
		Store* p = head[i];
		while (p){
			if (p->orderNo == 0){
				ret++;
			}
			p = p->next;
		}
	}
		
	/*
	cout << endl;
	cout << "S: " << s << " O: " << o << " R: " << r << endl;
	cout << "Sell Time: " << ((double)debug.stime/CLOCKS_PER_SEC) << endl;
	cout << "Refund Time: " << ((double)debug.rtime/CLOCKS_PER_SEC) << endl;
	*/

	return ret;
}

