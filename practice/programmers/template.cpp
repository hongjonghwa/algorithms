#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

vector<int> solution(int N, vector<int> stages) {
    vector<int> answer(N);
    vector<int> cnt(N+2);
    vector<int> arrival(N+2);
    for (size_t i = 0 ; i < stages.size() ; ++i) cnt[stages[i]]++;
    for (int i = 0 ; i <= N+1 ; ++i)
        cout << i << ":" << cnt[i] << "\n";
    arrival[N+1] = cnt[N+1];
    for (int i = N ; i > 0 ; --i)
        arrival[i] = arrival[i+1] + cnt[i];
    
    vector<pair<double,int>> fail_per(N+1);
    for (int i = 1; i <= N ; ++i){
        if (arrival[i]) fail_per[i] = make_pair( - double(cnt[i]) / arrival[i], i);
        else fail_per[i] = make_pair(0, i);
    }
    sort(fail_per.begin()+1, fail_per.end());
    for (int i = 1 ; i <= N ; ++i)
        answer[i-1] = fail_per[i].second;


    for (int i = 0 ; i <= N ; ++i){
        cout << i << ":" << arrival[i] << "\n";
    }
    return answer;
}

int main (){
    int N = 5;
    vector<int> test = {2, 1, 2, 6, 2, 4, 3, 3};
    vector<int> ret = solution (N, test);
    for (size_t i = 0 ; i < ret.size(); ++i)
        cout << ret[i] << " ";
    cout << "\n";
}
