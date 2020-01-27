#include <iostream>
using namespace std;

int main(){

	int set = 22;

	for (int subset = set ; 1 ; subset = (subset-1)&set){
		cout << subset << endl;
		if (!subset) break;
	}

	cout << endl;
	for (int subset = set ; subset ; subset = (subset-1)&set){
		cout << subset << endl;
	}

	return 0;
}
