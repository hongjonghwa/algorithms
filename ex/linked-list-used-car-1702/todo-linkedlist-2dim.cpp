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
	int engine, price;
	Store *next;
} store [1100001];
Store *head[12][13];

struct Order{
	int age, passenger, engine, price;
	Order *next;
} order [1000001];
Order *ohead[20000];

int frees, o, freeo;
int debug_r;

void init() {
	// 초기화 함수가 있었는지 기억 안남
	for (int i = 0 ; i < 12 ; ++i)
		for (int j = 2 ; j < 13 ; ++j)
			head[i][j] = 0;
	
	frees = o = freeo = 0;
	debug_r = 0;
}



void buyCar(CAR *newcar) {
	//TODO : 입고
	++frees;
	store[frees].engine = newcar->engine;
	store[frees].price = newcar->price;
	store[frees].next = head[newcar->age][newcar->passenger];
	head[newcar->age][newcar->passenger] = &store[frees];
}

int sellCar(int from_age, int to_age, int from_passenger, int to_passenger, int from_engine, int to_engine, int from_price, int to_price) {	
	long clk = clock();
	++o;
	// cout << " sell called : " << o << endl;
	ohead[o] = 0;
	/*
	int tt = 0;
	cout << from_age << "~" << to_age << " ";
	cout << from_passenger << "~" << to_passenger << " ";
	cout << from_engine << "~" << to_engine << " ";
	cout << from_price << "~" << to_price << " ";
	*/
	for (int i = from_age ; i <= to_age ; ++i){
		for (int j = from_passenger ; j <= to_passenger ; ++j){
			Store * p = head[i][j];
			Store * prev = 0;
			
			while (p){
				Store *next = p->next;
				if (
					p->engine >= from_engine && p->engine <= to_engine &&
					p->price >= from_price && p->price <= to_price
				){
					freeo++;
					order[freeo].age = i;
					order[freeo].passenger = j;
					order[freeo].engine = p->engine;
					order[freeo].price = p->price;
					
					order[freeo].next = ohead[o];
					ohead[o] = &order[freeo];
					
					if (prev) prev->next = p->next;
					else head[i][j] = next;
					// 조건이 맞으면, head 가 이동, 
				}else{
					prev = p; // 이전 노드 기억
				}
				p =  p->next;
				
			}
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
		store[frees].engine = p->engine;
		store[frees].price = p->price;
		store[frees].next = head[p->age][p->passenger];
		head[p->age][p->passenger] = &store[frees];
		
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
		for (int j = 2 ; j < 13 ; ++j){
			Store* p = head[i][j];
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

