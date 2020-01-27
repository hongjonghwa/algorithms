#include<iostream>
#include<algorithm>
#include<cstdio>

using namespace std;

int minimum(int diff_abc, int diff_a, int diff_b, int diff_c){
	int ta = diff_abc; // 3문자열 중 하나와 맞출 수 있는 갯수
	int t1 = diff_a - diff_b;
	int t2 = diff_b - diff_c;

	if (t1 + t2 * 2 <= ta){ // 전부 맞출 수 있을 때
		int remain = ta - (t1+t2*2);
		return diff_abc + max(diff_c - (remain/3), 0);
	}

	if (t1 <= ta){ // A열이라도 맞출 수 있을 때
		int remain = (ta - t1);
		return diff_abc + max(diff_b - (remain/2), 0);
	}

	// A 열 조차 못 맞출때
	return diff_abc + (diff_a - ta);
}

int main(){
	ios::sync_with_stdio(false);
	setbuf(stdout,NULL);
	freopen("sample_input.txt","rt",stdin);
	//freopen("eval_input.txt","rt",stdin);
	//cout << T << endl;
		string A,B,C;
		cin >> A >> B >> C;

		int len = A.size();
		char a,b,c;
		int all_same = 0;
		int diff_abc = 0;
		int diff_a = 0;
		int diff_b = 0;
		int diff_c = 0;
		int r_a = 0;
		int r_b = 0;
		int r_c = 0;
		for (int i = 0 ; i < len ; ++i){
			a = A[i]; b = B[i]; c = C[i];
			if (a == b){
				if (b == c) all_same++;
				else diff_c++;
			}else{
				if (b == c) diff_a++;
				else if(a == c) diff_b++;
				else diff_abc++;
			}
			r_a = diff_a; r_b = diff_b; r_c = diff_c;


		}

		if (diff_a < diff_b) swap(diff_a, diff_b);
		if (diff_b < diff_c) swap(diff_b, diff_c);
		if (diff_a < diff_b) swap(diff_a, diff_b);
		/*
		cout << len << " : "
			<< all_same << "," << diff_abc 
			<< "," << diff_a 
			<< "," << diff_b 
			<< "," << diff_c << endl;
			*/
		cout << minimum(diff_abc, diff_a, diff_b, diff_c) << endl;

	


}
