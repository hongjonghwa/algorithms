#include<cmath>

const double EPSILON = 1e-8;
const double PI = 2.0 * acos(0.0);

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