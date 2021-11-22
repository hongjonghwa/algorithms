// https://codingcompetitions.withgoogle.com/codejam/round/0000000000432cc7/0000000000432ad3#analysis

#include <bits/stdc++.h>
using namespace std;
#define pb push_back

const double eps=1e-9;

struct plant{ double x,y,r; };
struct point{
    double x,y; 
    point(double _x, double _y) : x(_x), y(_y) {}
    point(){}
};


/* TEMPORARY */
template<class T> inline T sqr(T x){return x*x;}
double dist(double x1,double y1,double x2,double y2){return sqrt(sqr(x1-x2)+sqr(y1-y2));}
template<class T> T cross(T x0,T y0,T x1,T y1,T x2,T y2){return (x1-x0)*(y2-y0)-(x2-x0)*(y1-y0);}
int compare(double a,double b){return(fabs(a-b)<=eps)?0:((a<b)?-1:1);}
double ppDistance(const point &a,const point &b)
{
	return dist(a.x,a.y,b.x,b.y);
}
/* TEMPORARY */


// 2 circle 의 교점 - https://mathworld.wolfram.com/Circle-CircleIntersection.html
bool intersectionOf2Circle( double x1, double y1, double r1, 
                            double x2, double y2, double r2, point &ret1, point& ret2){
    
    double dy = y2-y1, dx = x2-x1;
    double D = hypot(dx, dy);
    // if (D < fabs(r1-r2) || D > r1+r2) return false; // 교차하지 않음
    if (D < fabs(r1-r2)-eps || D > r1+r2+eps) return false; // try
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


/* temporary */
const int maxn=40+5;
int n;
point C[maxn];
double R[maxn];


bool check(double r){
    vector<point> candidates;
	for (int i = 0 ; i < n ; i++) candidates.pb(C[i]);

	for (int i = 0 ; i < n ; ++i)
		for (int j = i+1 ; j < n ; ++j){
			point p1, p2;
			if (intersectionOf2Circle(C[i].x, C[i].y, r-R[i], 
                                      C[j].x, C[j].y, r-R[j], p1, p2))

            {
                candidates.pb(p1);
                candidates.pb(p2);
            }
        }

    for (size_t i = 0 ; i < candidates.size() ; ++i){
        for (size_t j = i ; j < candidates.size() ; ++j){
            bool all_in = true;
            for (int k = 0 ; k < n ; ++k){

                if ( // 둘 다 out 이면,,, 
                    compare(ppDistance(candidates[i], C[k]), r - R[k]) > 0
                    && compare(ppDistance(candidates[j], C[k]), r - R[k]) > 0)
                {
                    all_in = false;
                    break;
                }
            }
            if (all_in) return true;
        }
    }
    return false;
}


double solv(){
    double l = 0, u = 808;
    for (int i = 0 ; i < n ; ++i)
        if (l < R[i]) 
            l = R[i];
    
    while (fabs(u-l) > 1e-9){
        double r = (u+l)/2.0;
        bool ok = check(r);
        if (ok)  u = r ;
        else {
            l = r;
        }
    }
    return (u+l)/2;
}


int main(){
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    //if (!freopen("input.txt", "rt", stdin)) return 1;
    ios::sync_with_stdio(true);
    // test(); return 0;
    int TC;
    cin >> TC;
    // scanf("%d",&TC);

    for (auto test = 1 ; test <= TC ; ++test){
        cin >> n;
        for (int i=0;i<n;i++)
            cin >> C[i].x >> C[i].y >> R[i];


        double answer = solv();
        cout << setprecision(12);
        // cout <<  "Case #" << test << " " << answer << "\n"; // why wrong?
        printf ( "Case #%d: %.12lf\n",test,answer);
		fflush(stdout);
    }

}