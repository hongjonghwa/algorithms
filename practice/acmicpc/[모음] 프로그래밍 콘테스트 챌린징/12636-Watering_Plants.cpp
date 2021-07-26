#include <bits/stdc++.h>
// https://codingcompetitions.withgoogle.com/codejam/round/0000000000432cc7/0000000000432ad3#analysis
using namespace std;

/*
1 ≤ X ≤ 1000
1 ≤ Y ≤ 1000
1 ≤ R ≤ 100
1 ≤ C ≤ 30
1 ≤ N ≤ 40
*/
void solv(){    
    int C,N,X,Y,R;
    cin >> C;
    for (auto c = 1 ; c <= C ; ++c){
        cin >> N;
        for (auto n = 0 ; n < N ; ++n ){
            cin >> X >> Y >> R;
        }
        double ans =  7;
        cout << "Case #" << c << " " << ans << "\n";
    }
    cout << __gcd(3,9) << " ";
}

int main(){
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);  
    freopen("input.txt", "rt", stdin);
    cout << fixed;
    solv();
}