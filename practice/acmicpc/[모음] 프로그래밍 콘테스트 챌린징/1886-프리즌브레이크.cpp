#include<iostream>
using namespace std;

int N, K;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> N >> K;
    cout << N << ", " << K << "\n";
    for (int i = 0 ; i < N ; ++i){
        for (int j = 0 ; j < K ; ++j){
            char t;
            cin >> t;
            cout << "i:j " << i <<":" << j << " - " <<t << "\n";
        }
    }
    
}