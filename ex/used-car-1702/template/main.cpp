#include<iostream>
#include<time.h>
#define SWAPI(x,y) {int T = x ; x = y; y = T; }
using namespace std;

/* fastrand.cpp */
extern int fastrand();


/*
	problem template 
*/

struct CAR {
	int age;		// 0 ~ 11
	int passenger;	// 2 ~ 12
	int engine;		// 1000 ~ 3999
	int price;		// 10000 ~ 49999
};

CAR* newCar() {
	CAR *p = new CAR();
	(*p).age = (fastrand() % 12);
	(*p).passenger = (fastrand() % 11) + 2;
	(*p).engine = (fastrand() % 3000) + 1000;
	(*p).price = (fastrand() % 40000) + 10000;
	return p;
}
extern void buyCar(CAR *newcar);
extern int sellCar(int from_age, int to_age, int from_passenger, int to_passenger, int from_engine, int to_engine, int from_price, int to_price);
extern void refund(int orderNo);
extern int getInven();
extern void init();

int sellCar_random() {
	int from_age = (fastrand() % 12);
	int to_age = (fastrand() % 12);
	if (from_age > to_age) SWAPI(from_age, to_age);
	int from_passenger = (fastrand() % 11) + 2;
	int to_passenger = (fastrand() % 11) + 2;
	if (from_passenger > to_passenger) SWAPI(from_passenger, to_passenger);
	int from_engine = (fastrand() % 3000) + 1000;
	int to_engine = (fastrand() % 3000) + 1000;
	if (from_engine > to_engine) SWAPI(from_engine, to_engine);
	int from_price = (fastrand() % 40000) + 10000;
	int to_price = (fastrand() % 40000) + 10000;
	if (from_price > to_price) SWAPI(from_price, to_price);

	return sellCar(from_age, to_age, from_passenger, to_passenger, from_engine, to_engine, from_price, to_price);
}



const int TOTAL_LOOP = 10;
const int CAR_BUYING = 1000 * 1000;

int main() {
	clock_t start, end;
	start = clock();


	int orderno = -1;
	init();
	for (int loop = 0; loop < TOTAL_LOOP; ++loop) {
		for (int i = 0; i < CAR_BUYING; ++i) {
			buyCar(newCar());
			if ( (fastrand() % 100) == 0) {
				int t = sellCar_random();
				if (fastrand() % 10 == 0)  orderno = t;
				
			}
			if (fastrand() % 10000 == 0 && orderno != -1) {
				refund(orderno);
				orderno = -1;
			}
		}
		cout << getInven() << endl;
		orderno = -1;
	}

	end = clock();
	cout << "Time required for execution: "
		<< (double)(end - start) / CLOCKS_PER_SEC
		<< " seconds." << "\n\n";
	return 0;
}