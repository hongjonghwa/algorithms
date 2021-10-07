#include<cmath>

/*
벡터의 내적 - 두 벡터의 사이각 얻기 cosine
            - 직각 여부 확인하기
            - projection

벡터의 외적 - 면적 계산
            - 평행 여부 확인하기
            - 방향 판별, 교차여부 ccw
            - 교차점
*/

// const double EPSILON = 1e-8;
// const double PI = 2.0 * acos(0.0);
const double PI = acos(-1);

// 2차원 벡터를 표현한다
struct Vector2D {
	double x, y;

	explicit Vector2D(double _x = 0, double _y = 0) : x(_x), y(_y) {}

	// 두 벡터의 비교
	bool operator == (const Vector2D& rhs) const { return x == rhs.x && y == rhs.y; }
	bool operator < (const Vector2D& rhs) const { if(x != rhs.x) return x < rhs.x; return y < rhs.y; }

	// 벡터의 덧셈과 뺄셈
	Vector2D operator + (const Vector2D& rhs) const { return Vector2D(x + rhs.x, y + rhs.y); }
	Vector2D operator - (const Vector2D& rhs) const { return Vector2D(x - rhs.x, y - rhs.y); }
	Vector2D operator - () const { return Vector2D(-x, -y); }

	// 스칼라로 곱셈
	Vector2D operator * (double rhs) const { return Vector2D(x * rhs, y * rhs); }

	// 벡터의 길이를 반환한다
	double norm() const { return hypot(x, y); }

	// 방향이 같은 단위 벡터 (unit vector) 를 반환한다
	// 영벡터에 대해 호출한 경우 결과값은 정의되지 않는다
	Vector2D normalize() const { double n = norm(); return Vector2D(x / n, y / n); }

	// x축의 양의 방향으로부터 이 벡터까지 반시계방향으로 잰 각도
	double polar() const { return fmod(atan2(y, x) + 2*PI, 2*PI); }

	// 내적/외적의 구현
	double dot(const Vector2D& rhs) const { return x * rhs.x + y * rhs.y; }
	double cross(const Vector2D& rhs) const { return x * rhs.y - rhs.x * y; }

	// 이 벡터를 rhs 에 사영한 결과
	Vector2D project(const Vector2D& rhs) const {
        /* 
            A.dot(B)  ==  |A||B|cosΘ                          ※ 내적
            투영은 크기 |A|cosΘ 에 방향이 B/|B| 인 벡터
            |A|cosΘ * B/|B|
                 = (A.dot(B)/|B|) * (B/|B|) 
                 = A.dot(b) * b                               ※ 단위 벡터 b = B/|B|를 정의하면
                   또는 b * b.dot(a);
        */
		Vector2D r = rhs.normalize();
		return r * r.dot(*this);
	}

	// 이 벡터를 rhs 에 사영한 결과
	Vector2D project2(const Vector2D& rhs) const {

		Vector2D r = rhs.normalize();
		return r * r.dot(*this);
	}
};


// (a,b) 를 포함하는 선과 (c,d) 를 포함하는 선의 교점을 x 에 반환한다.
// 두 선이 평행이면 (겹치는 경우를 포함) 거짓을, 아니면 참을 반환한다.
/*
    [증명]
    P = A + s AB                                      (1)
    P = C + t CD                                      (2)
    s AB = t CD + AC                                  (1)+(2)
    s AB × CD = AC × CD                               (because CD × CD = 0)
    s = AC × CD / AB × CD      ( AB × CD != 0 일 때)  (3)
    P = A + AB * AC × CD / AB × CD                    (1)+(3)
*/
bool lineIntersection(Vector2D a, Vector2D b, Vector2D c, Vector2D d, Vector2D& x) {
	double det = (b - a).cross(d - c); // AB × CD
	if(det == 0) return false;
	x = a + (b - a) * ((c - a).cross(d - c) / det); 
	return true;
}
