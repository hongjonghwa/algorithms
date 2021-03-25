#include<iostream>
using namespace std;

int main(){
	ios::sync_with_stdio(false);
	
	int MAXINT = 0x7FFFFFFF;
	cout << "max int : " << MAXINT << endl;

	unsigned int MAXUINT = -1;
	cout << "unsiged max int : " << MAXUINT << endl;

	long long int xx = 1;
	for (int i = 0 ; i < 8 ; ++i, xx *= 36)
		cout << " 36^" << i << " " << xx << " " << double(xx)/MAXUINT << endl;
}
