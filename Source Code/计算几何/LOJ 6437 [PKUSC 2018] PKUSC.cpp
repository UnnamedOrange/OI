#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cassert>
#include <cctype>
#include <climits>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <stack>
#include <queue>
#include <deque>
#include <map>
#include <set>
#include <bitset>
#include <list>
#include <functional>
typedef long long LL;
typedef unsigned long long ULL;
using std::cin;
using std::cout;
using std::endl;
typedef int INT_PUT;
INT_PUT readIn()
{
	INT_PUT a = 0; bool positive = true;
	char ch = getchar();
	while (!(ch == '-' || std::isdigit(ch))) ch = getchar();
	if (ch == '-') { positive = false; ch = getchar(); }
	while (std::isdigit(ch)) { a = a * 10 - (ch - '0'); ch = getchar(); }
	return positive ? -a : a;
}
void printOut(INT_PUT x)
{
	char buffer[20]; int length = 0;
	if (x < 0) putchar('-'); else x = -x;
	do buffer[length++] = -(x % 10) + '0'; while (x /= 10);
	do putchar(buffer[--length]); while (length);
}

const double PI = std::acos(double(-1));
const int maxn = 205;
const int maxm = 505;
int n, m;

#define DefinePoint(name)					\
struct name									\
{											\
	double x, y;							\
	name() = default;						\
	name(double x, double y) : x(x), y(y) {}\
}
DefinePoint(Point);
DefinePoint(Vector);

Point enemys[maxn];
Point polys[maxm];

template<typename T>
void readIn(T& t)
{
	t.x = readIn();
	t.y = readIn();
}
inline int dcmp(double x)
{
	const double EPS = 1e-3; // EPS 调小了还真过不了
	if (std::abs(x) <= EPS)
		return 0;
	return x < 0 ? -1 : 1;
}
inline Vector operator-(const Point& a, const Point& b) // 我的点和向量不同
{
	return Vector(b.x - a.x, b.y - a.y);
}
inline Vector operator-(const Vector& a, const Vector& b)
{
	return Vector(a.x - b.x, a.y - b.y);
}
inline Vector operator-(const Vector& a)
{
	return Vector(-a.x, -a.y);
}
inline Vector operator*(const Vector& a, const double& b)
{
	return Vector(a.x * b, a.y * b);
}
inline Point operator+(const Point& a, const Vector& b)
{
	return Point(a.x + b.x, a.y + b.y);
}
inline double Dot(const Vector& a, const Vector& b)
{
	return a.x * b.x + a.y * b.y;
}
inline double Length2(const Vector& a)
{
	return Dot(a, a);
}
inline double Cross(const Vector& a, const Vector& b)
{
	return a.x * b.y - a.y * b.x;
}
inline Vector Rotate(const Vector& v, const double& angle)
{
	return Vector(v.x * std::cos(angle) - v.y * std::sin(angle),
		v.x * std::sin(angle) + v.y * std::cos(angle));
}
inline Vector Normalize(const Vector& v, const double& l)
{
	double ratio = l / std::sqrt(Length2(v));
	return Vector(v.x * ratio, v.y * ratio);
}
inline double atan3(const double& y, const double& x) // 保证角度为正
{
	double t = std::atan2(y, x);
	return dcmp(t) < 0 ? t + 2 * PI : t;
}

struct Circle
{
	Point c;
	double r;
	Circle() = default;
	Circle(const Point& c, const double& r) : c(c), r(r) {}
	Point locate(double angle) const
	{
		return c + Vector(r * std::cos(angle), r * std::sin(angle));
	}
};
struct Line
{
	Point p;
	Vector v;
	Line() = default;
	Line(const Point& p, const Vector& v) : p(p), v(v) {}
	Point point(double k) const
	{
		return p + v * k;
	}
};
struct Segment
{
	Point a, b;
	Segment() = default;
	Segment(const Point& a, const Point& b) : a(a), b(b) {}
};
inline bool OnSegment(const Segment& s, const Point& p)
{
	return !dcmp(Cross(p - s.a, p - s.b)) && dcmp(Dot(p - s.a, p - s.b)) <= 0;
}
void GetSegmentCircleIntersections(const Circle& a, const Segment& s, std::vector<Point>& vec)
{
	Line b(s.a, s.a - s.b);
	double m = b.v.x;
	double n = b.v.y;
	double p = b.p.x - a.c.x;
	double q = b.p.y - a.c.y;
	double r = a.r;
	double A = (m * m + n * n);
	double B = 2 * (m * p + n * q);
	double C = p * p + q * q - r * r;
	double delta = B * B - 4 * A * C;
	if (dcmp(delta) < 0)
		return;
	else if (dcmp(delta) == 0)
	{
		Point t = b.point(-B / (2 * A));
		if (OnSegment(s, t))
			vec.push_back(t);
		return;
	}
	delta = std::sqrt(delta);
	Point p1 = b.point((-B - delta) / (2 * A));
	Point p2 = b.point((-B + delta) / (2 * A));
	if (OnSegment(s, p1)) vec.push_back(p1);
	if (OnSegment(s, p2)) vec.push_back(p2);
}

enum STATUS { ON, OUT, IN };
STATUS CheckPoly(const Point& p)
{
	int wn = 0;
	for (int i = 1; i <= m; i++) // 把第一个点复制到了 m + 1 中
	{
		if (OnSegment(Segment(polys[i], polys[i + 1]), p))
			return ON;

		// inline Vector operator-(const Point& a, const Point& b)
		// {
		//		return Vector(b.x - a.x, b.y - a.y);
		// }
		int k = dcmp(Cross(polys[i] - polys[i + 1], polys[i] - p));
		int d1 = dcmp(polys[i].y - p.y);
		int d2 = dcmp(polys[i + 1].y - p.y);

		if (k > 0 && d1 <= 0 && d2 > 0) wn++; // 起点在下面，想要穿过射线 k 就要大于 0
		if (k < 0 && d2 <= 0 && d1 > 0) wn--; // 起点在下面，想要穿过射线 k 就要小于 0
	}
	if (wn) return IN;
	return OUT;
}

void run()
{
	n = readIn();
	m = readIn();
	for (int i = 1; i <= n; i++)
		readIn(enemys[i]);
	for (int i = 1; i <= m; i++)
		readIn(polys[i]);
	polys[m + 1] = polys[1];

	double ans = 0;
	for (int i = 1; i <= n; i++)
	{
		Vector vec = Point(0, 0) - enemys[i];
		double r2 = Length2(vec);
		Circle circ(Point(0, 0), std::sqrt(r2));
		if (!dcmp(r2))
		{
			if (CheckPoly(enemys[i]) == IN)
				ans += 2 * PI;
			continue;
		}
		std::vector<Point> intersections;

		for (int j = 1; j <= m; j++)
		{
			GetSegmentCircleIntersections(circ,
				Segment(polys[j], polys[j + 1]), intersections);
		}

		if (!intersections.size())
		{
			if (CheckPoly(circ.locate(rand())) == IN) // 必须随机一下，否则可能在多边形的点上
				ans += 2 * PI;
			continue;
		}

		std::vector<double> angles;
		for (const Point& p : intersections)
			angles.push_back(atan3(p.y, p.x));
		std::sort(angles.begin(), angles.end());
		angles.push_back(angles.front() + 2 * PI); // 把第一个点复制一遍

		for (int i = 1; i < angles.size(); i++)
		{
			Point t = circ.locate((angles[i] + angles[i - 1]) / 2);
			if (CheckPoly(t) == IN)
				ans += (angles[i] - angles[i - 1]);
		}
	}
	ans /= 2 * PI;
	printf("%.5f", ans);
}

int main()
{
	run();
	return 0;
}