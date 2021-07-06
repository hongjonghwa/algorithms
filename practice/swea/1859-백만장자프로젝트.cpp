#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

// 1859. 백만 장자 프로젝트

int main(int argc, char** argv)
{
	int T,N;
	// freopen("input.txt", "r", stdin);
	cin >> T;
	for (int test_case = 1; test_case <= T; ++test_case)
	{
		cin >> N;
		vector<int> X(N);
		for (int i = 0; i < N; ++i) cin >> X[i];


		int highest_price = 0;
		long long profit = 0;
		for (int i = N - 1; i >= 0; i--) {
			if (X[i] > highest_price) highest_price = X[i];
			else profit += highest_price - X[i];
		}
		cout << "#" <<  test_case << " " << profit << "\n";

	}
	return 0;
}
