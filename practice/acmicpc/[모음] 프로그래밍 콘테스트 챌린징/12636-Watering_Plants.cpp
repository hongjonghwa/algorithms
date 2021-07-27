#include <bits/stdc++.h>
#include "geom/Vector2D.cpp"

#define F first 
#define S second 
#define pb push_back
#define mp make_pair
// https://codingcompetitions.withgoogle.com/codejam/round/0000000000432cc7/0000000000432ad3#analysis

using namespace std;
const double EPSILON = 1e-8;
typedef pair<Vector2D, double> Circle;

/*
1 ≤ X ≤ 1000
1 ≤ Y ≤ 1000
1 ≤ R ≤ 100
1 ≤ C ≤ 30
1 ≤ N ≤ 40
*/

void assert_touch_boundary(Circle cover, Circle c1){
    double t = hypot(c1.F.x - cover.F.x, c1.F.y - cover.F.y) + c1.S;
    assert(fabs(t - cover.S) < EPSILON);   
}

bool cover(Circle c1, Circle c2, Circle & result){
    const double& x1 = c1.F.x, &y1 = c1.F.y, &r1 = c1.S; // x, y, r
    const double& x2 = c2.F.x, &y2 = c2.F.y, &r2 = c2.S;

    if (x1==x2 && y1==y2) return false;

    double dist = hypot(x2-x1, y2-y1);
    double ratio = (dist + r2 - r1) / (2 * dist);
    result.F.x = x1 + (x2-x1) * ratio;
    result.F.y = y1 + (y2-y1) * ratio;
    result.S = (dist+r1+r2)/2;
    return true;
}

bool cover(Circle c1, Circle c2, Circle c3, Circle & result){
    const double& x1 = c1.F.x, &y1 = c1.F.y, &r1 = c1.S; // x, y, r
    const double& x2 = c2.F.x, &y2 = c2.F.y, &r2 = c2.S;
    const double& x3 = c3.F.x, &y3 = c3.F.y, &r3 = c3.S;

    if (x1==x2 && y1==y2) return false;
    if (x2==x3 && y2==y3) return false;
    if (x1==x3 && y1==y3) return false;
    
    pair<double, double> directionLine1 = MP( GET_X(c2)- GET_X(c1) , GET_Y(c2) -  GET_Y(c1));
    pair<double, double> directionLine2 = MP( GET_X(c3)- GET_X(c1) , GET_Y(c3) -  GET_Y(c1));
    // 외적이 0 이면 평행하고 교차하지 않음 (x1*y2 - y1*x2)
    if ( directionLine1.F*directionLine2.S == directionLine1.S * directionLine2.F ) return false;

    Circle starting1;
    cover(c1,c2,starting1); // starting point
    pair<double, double> tangentLine1 = MP(-directionLine1.S, directionLine1.F);

    Circle starting2;
    cover(c1,c3,starting2);
    pair<double, double> tangentLine2 = MP(-directionLine2.S, directionLine2.F);

    
    double dist = hypot(x2-x1, y2-y1);
    double ratio = (dist + r2 - r1) / (2 * dist);
    double x4 = x1 + (x2-x1) * ratio;
    double y4 = y1 + (y2-y1) * ratio;
    double r4 = (dist+r1+r2)/2;
    return make_tuple(x4,y4,r4);
}

double solv(vector<Circle> v){
    vector<Circle> candidate;
    // 1
    for (size_t i = 0 ; i < v.size() ; ++i)
        candidate.pb(v[i]);
    assert( v.size() == candidate.size() );
    // 2
    for (size_t i = 0 ; i < v.size() ; ++i)
        for (size_t j = i+1 ; j < v.size() ; ++j){
            Circle c;
            if (cover(v[i], v[j], c)) candidate.push_back(c);
            // assertion
            assert_touch_boundary(c, v[i]);
            assert_touch_boundary(c, v[j]);

        }
    // 3
    for (size_t i = 0 ; i < v.size() ; ++i)
        for (size_t j = i+1 ; j < v.size() ; ++j)
            for (size_t k = j+1 ; k < v.size() ; ++k)
    return 0.0;
}

void input(){    
    int C,N,X,Y,R;
    cin >> C;
    for (auto c = 1 ; c <= C ; ++c){
        cin >> N;
        vector<Circle> v;
        v.reserve(N);
        for (auto n = 0 ; n < N ; ++n ){
            cin >> X >> Y >> R;
            v.emplace_back(Vector2D(X,Y),R);
        }
        double ans = solv(v);
        cout << "Case #" << c << " " << ans << "\n";
    }
}

int main(){
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);  
    if (!freopen("input.txt", "rt", stdin)) return 1;
    cout << fixed;
    input();
}