#include<iostream>
using namespace std;

int main(){
	ios::sync_with_stdio(false);
	int MAXINT = 0x7FFFFFFF;
	cout << MAXINT << endl;

	unsigned int MAXUINT = -1;
	cout << MAXUINT << endl;
	long long int xx = 1;
	cout << (xx *= 36) << endl;
	cout << (xx *= 36) << endl;
	cout << (xx *= 36) << endl;
	cout << (xx *= 36) << endl;
	cout << (xx *= 36) << endl;
	cout << (xx *= 36) << endl;
}
