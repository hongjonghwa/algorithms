#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main(int argc, char** argv)
{
	int N;
	cin >> N;

    vector<int> X = vector<int>(N);
    for (int i = 0 ; i < N ; ++i)
        cin >> X[i];
    sort(X.begin(), X.end());
    cout << X[N/2] << "\n";
	return 0;
}
