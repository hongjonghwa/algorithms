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
	int price;
	Store *next;
} store [2000001];


Store *head[12][13][4000];
struct Order{
	int age, passenger, engine, price;
	Order *next;
} order [1000001];
Order *ohead[40000];

int frees, o, freeo;
int debug_r;

void init() {
	// 초기화 함수가 있었는지 기억 안남
	for (int i = 0 ; i < 12 ; ++i)
		for (int j = 2 ; j < 13 ; ++j)
			for (int k = 1000 ; k < 4000 ; ++k)
				head[i][j][k] = 0;
	
	frees = o = freeo = 0;
	debug_r = 0;
}



void buyCar(CAR *newcar) {
	//TODO : 입고
	++frees;
	store[frees].price = newcar->price;
	store[frees].next = head[newcar->age][newcar->passenger][newcar->engine];
	head[newcar->age][newcar->passenger][newcar->engine] = &store[frees];
}

Store* rsel(Store * p, int age, int passenger, int engine, int from_price, int to_price, int orderNo){
	if (p == 0) return 0;
	else if (p->price >= from_price && p->price <= to_price){ // 판매	
		freeo++;
		order[freeo].age = age;
		order[freeo].passenger = passenger;
		order[freeo].engine = engine;
		order[freeo].price = p->price;
		order[freeo].next = ohead[orderNo];
		ohead[orderNo] = &order[freeo];
		
		return rsel(p->next, age, passenger, engine, from_price, to_price, orderNo);
	}else{ // 안 판매
		p->next = rsel(p->next, age, passenger, engine, from_price, to_price, orderNo);
		return p;
		
	}
}

int sellCar(int from_age, int to_age, int from_passenger, int to_passenger, int from_engine, int to_engine, int from_price, int to_price) {	
	long clk = clock();
	++o;
	ohead[o] = 0;
	/*
	int tt = 0;
	cout << from_age << "~" << to_age << " ";
	cout << from_passenger << "~" << to_passenger << " ";
	cout << from_engine << "~" << to_engine << " ";
	cout << from_price << "~" << to_price << " ";
	*/
	for (int i = from_age ; i <= to_age ; ++i)
		for (int j = from_passenger ; j <= to_passenger ; ++j)
			for (int k = from_engine ; k <= to_engine ; ++k){
				if (head[i][j][k]){
					head[i][j][k] = rsel(head[i][j][k], i, j, k, from_price, to_price, o);
				}
			}


	// cout << " ==> s cnt : " << tt << "/" << s << endl;

	debug.stime += clock()-clk;
	return o;
}
void refund(int orderNo) {
	long clk = clock();
	++debug_r;
	int tt = 0;
	//TODO : 주문취소
	/*
	for (int i = 0 ; i < 12 ; ++i)
		for (int j = 2 ; j < 13 ; ++j)
			for (int k = 1000 ; k < 4000 ; ++k)
	*/

	Order* p = ohead[orderNo];
	
	while (p){
		++frees;
		store[frees].price = p->price;
		store[frees].next = head[p->age][p->passenger][p->engine];
		head[p->age][p->passenger][p->engine] = &store[frees];
		
		p = p->next;
	}


	/*
	cout << "refund# " << orderNo << " cnt: " << tt << endl;
	*/
	debug.rtime += clock()-clk;
}
int getInven() {
	
	//TODO : 초기화, return 남은 차량 대수
	int ret = 0;
	
	for (int i = 0 ; i < 12 ; ++i)
		for (int j = 2 ; j < 13 ; ++j)
			for (int k = 1000 ; k < 4000 ; ++k){
				Store* p = head[i][j][k];
				while (p){
					ret++;
					p = p->next;
				}
			}
		
	/*
	cout << endl;
	cout << "freeS: " << frees << " O: " << o << " debugR: " << debug_r << endl;
	cout << "Sell Time: " << ((double)debug.stime/CLOCKS_PER_SEC) << endl;
	cout << "Refund Time: " << ((double)debug.rtime/CLOCKS_PER_SEC) << endl;
	*/

	return ret;
}

