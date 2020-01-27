#include <iostream>

using namespace std;

int bitCount(int i){
	if (i==0) return 0;
	return i%2+bitCount(i/2);
}
/*
1001 : 9
100 : 4
*/
void printBit(int n){
	for (int i = sizeof(n)*8 - __builtin_clz(n) -1 ; i >=0 ; --i){
		if ((1<<i)&n) cout<<"1";
		else cout<<"0";
	}
	cout << endl;
}

int main(){


	unsigned int pizzaFull = (1<<20)-1;
	cout << "full : ";printBit(pizzaFull);

	unsigned int pizza = 0;

	cout << "add 0,1,2,5 : ";
	pizza |= (1<<0);
	pizza |= (1<<1);
	pizza |= (1<<2);
	pizza |= (1<<5);
	printBit(pizza);

	cout << "toggie 2,5,6,9 : ";
	pizza ^= (1<<2);
	pizza ^= (1<<5);
	pizza ^= (1<<6);
	pizza ^= (1<<9);
	printBit(pizza);

	cout << "remove 0,1 :";
	pizza &= ~(1<<0);
	pizza &= ~(1<<1);
	printBit(pizza);

	cout << "check in 6 :";
	if (pizza & (1<<6)) cout << "Y";
	cout << endl;

	cout << "check in 7 :";
	if (pizza & (1<<7)) cout << "Y";
	cout << endl;

	cout << endl;


	pizza |= (1<<2);
	pizza |= (1<<4);
	pizza |= (1<<11);
	printBit(pizza);
	int firstElem = (pizza & -pizza);
	printBit(firstElem);


	cout << "loop except 0(all off)" << endl;
	for (int subset = pizza; subset; subset=((subset-1)&pizza)){
        printBit(subset);
	}


	cout << "delete first elem" << endl;
	pizza &= (pizza-1);
	printBit(pizza);

	pizza &= (pizza-1);
	printBit(pizza);

	pizza &= (pizza-1);
	printBit(pizza);

	pizza &= (pizza-1);
	printBit(pizza);


	return 0;


}
