// https://codingcompetitions.withgoogle.com/codejam/round/0000000000432cc7/0000000000432ad3#analysis

#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define inf 987654321

struct plant{ int x,y,r; };
struct point{
    double x,y; 
    point(double _x, double _y) : x(_x), y(_y) {}
    point(){}
};

// 2 circle 의 교점 - https://mathworld.wolfram.com/Circle-CircleIntersection.html
bool intersectionOf2Circle( double x1, double y1, double r1, 
                            double x2, double y2, double r2, point &ret1, point& ret2){
    
    double dy = y2-y1, dx = x2-x1;
    double D = hypot(dx, dy);
    if (D < fabs(r1-r2) || D > r1+r2) return false; // 교차하지 않음
    /* 피라고라스 
        dp  -  (x1,y1) 에서의 교차점 사이의 직선까지의 거리 
        dq  -  dx에서 교차점까지 떨어진 거리

        dp^2 + dq^2 = r1^2             (1)
        (D-dp)^2 + dq^2 = r2^2         (2)
        D^2 - 2Ddp = r2^2 - r1^2       (2) - (1)
        dp = (D^2 + r1^2 - r2^2) / 2D
    */
    double dp = (D*D + r1*r1 - r2*r2)/(2*D);
    double dq = sqrt(r1*r1 - dp*dp);
    
    double dp_x = dx * dp/D;
    double dp_y = dy * dp/D;
    /* 벡터 회전
       |cosθ -sinθ|
       |sinθ  cosθ|
    */
    double dq_x = dq * -dy/D;
    double dq_y = dq * dx/D;

    ret1.x = x1 + dp_x + dq_x, ret1.y = y1 + dp_y + dq_y;
    ret2.x = x1 + dp_x - dq_x, ret2.y = y1 + dp_y - dq_y;
    return true;
}

double solv(vector<plant> input){
    double l = 0, u = 808;
    for (size_t i = 0 ; i < input.size() ; ++i)
        if (l < input[i].r) 
            l = input[i].r;
    
    while (u-l > 1e-6){
        double r = (u+l)/2;
        vector<point> candidates;

        for (size_t i = 0 ; i < input.size() ; ++i)
            candidates.emplace_back(input[i].x, input[i].y);

        for (size_t i = 0 ; i < input.size() ; ++i)
            for (size_t j = i+1 ; j < input.size() ; ++j){
                point p1, p2;
                if ( intersectionOf2Circle( input[i].x, input[i].y, r-input[i].r,
                                            input[j].x, input[j].y, r-input[j].r, p1, p2 ) )
                {
                    candidates.pb(p1);
                    candidates.pb(p2);
                }
            }

        bool ok = false;
        for (size_t c1 = 0 ; c1 < candidates.size() ; ++c1){
            for (size_t c2 = c1+1 ; c2 < candidates.size() ; ++c2){
                bool all_in = true;
                for (size_t i = 0 ; i < input.size() ; ++i){
                    if ( // 둘 다 out 이면,,, 
                        hypot(candidates[c1].x-input[i].x, candidates[c1].y-input[i].y) + input[i].r - r > 1e-8 &&
                        hypot(candidates[c2].x-input[i].x, candidates[c2].y-input[i].y) + input[i].r - r > 1e-8  ) 
                    {
                        all_in = false;
                        break;
                    }
                }
                if (all_in) {
                    ok = true;
                    break;
                }
            }
            if (ok) break;
        }

        if (ok)  u = r ;
        else {
            l = r;
        }
    }
    return u;
}


void input(){    
    int C,N;
    cin >> C;
    for (auto c = 1 ; c <= C ; ++c){
        cin >> N;
        vector<plant> v;
        v.reserve(N);
        for (auto n = 0 ; n < N ; ++n ){
            plant p;
            cin >> p.x >> p.y >> p.r;
            v.pb(p);
        }
        double ans = solv(v);
        cout << "Case #" << c << " " << ans << "\n";
    }
}

void test(){
    double x1 = 10, y1 = 10, r1 = 13.07200;
    double x2 = 20, y2 = 20 ,r2 = 1.07200;
    point p1, p2;
    bool ret = intersectionOf2Circle(x1,y1,r1, x2,y2,r2, p1,p2);
    cout << "RET : " << ret << "\n";
    cout << "  Circle 1 (" << x1 << ","<< y1 << ","<< r1 << ") ";
    cout << "  Circle 2 (" << x2 << ","<< y2 << ","<< r2 << ") \n";
    cout << "  Intersection 1 (" << p1.x << ","<< p1.y << ") \n";
    cout << "  Intersection 2 (" << p2.x << ","<< p2.y << ") \n\n";
}


int main(){
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);  
    if (!freopen("input.txt", "rt", stdin)) return 1;
    cout << fixed;

    // test(); return 0;

    input();
}