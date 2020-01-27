/* 
 * 15.11 챕터 참조
 */
#include<stdio.h>
#include<vector>
#include<algorithm>
#include<iostream>
using namespace std;
typedef pair<int, pair <int, int> > triple;
triple make_triple(int f, int s, int t){
    return make_pair(f, make_pair(s,t));
}

int N;
struct Rect{
    int y1, x1, y2, x2;
} X[1000];

int test(){
    int ret = 0 ; 
    for (int i = 0 ; i < N ; ++i) ret += (X[i].y2 - X[i].y1) * (X[i].x2 - X[i].x1);
    return ret;
}


int area(){
    // 준비
    vector<int> ys;
    vector<triple> events;
    for (int i = 0 ; i < N ; ++i){
        ys.push_back(X[i].y1);
        ys.push_back(X[i].y2);
        events.push_back(make_triple(X[i].x1, 1, i));
        events.push_back(make_triple(X[i].x2, -1, i));
    }
    sort(ys.begin(), ys.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());
    sort(events.begin(), events.end());
    // for (int i = 0 ; i < ys.size() ; ++i) printf(" ys %d \n", ys[i]);
    // for (int i = 0 ; i < events.size() ; ++i) printf(" events %d %d %d \n", events[i].first, events[i].second.first, events[i].second.second);

    vector<int> count(ys.size()-1, 0); // ys[i] ~ ys[i+1] 에 겹쳐진 사각형의 수 
    int ret = 0;
    for (int i = 0 ; i < events.size(); ++i){
        int x = events[i].first;
        int delta = events[i].second.first;
        int rectangle = events[i].second.second;
        // count[] 갱신
        int y1 = X[rectangle].y1, y2 = X[rectangle].y2;
        for (int j = 0 ; j < ys.size() ; ++j){
            if (y1 <= ys[j] && ys[j] < y2){
                count[j] += delta;
            }
            printf(" count %d %d %d \n", i, j, count[j]);
        } 
        // cutLength 계산
        int cutLength = 0;
        for (int j = 0 ; j < ys.size() - 1 ; ++j)
            if (count[j] > 0)
                cutLength += ys[j+1] - ys[j];
        if (i < events.size() - 1)
            ret += cutLength * (events[i+1].first - x); 
    }
    for (int i = 0 ; i < count.size() ; ++i) printf(" count %d \n", count[i]);

    return ret;
}

int main(){
    freopen("area.txt", "rt", stdin);
    scanf("%d", &N);
    for (int i = 0 ; i < N ; ++i){
        scanf("%d%d%d%d", &X[i].y1, &X[i].x1, &X[i].y2, &X[i].x2);
    }
    printf ("Test: %d\n", test());
    printf ("Ret: %d\n", area());
}
