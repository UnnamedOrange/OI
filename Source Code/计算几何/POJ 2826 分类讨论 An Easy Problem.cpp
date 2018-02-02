#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
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
typedef int INT;
using std::cin;
using std::cout;
using std::endl;
INT readIn()
{
	INT a = 0;
	bool minus = false;
	char ch = getchar();
	while (!(ch == '-' || (ch >= '0' && ch <= '9'))) ch = getchar();
	if (ch == '-')
	{
		minus = true;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
	{
		a = a * 10 + (ch - '0');
		ch = getchar();
	}
	if (minus) a = -a;
	return a;
}
void printOut(INT x)
{
	char buffer[20];
	INT length = 0;
	if (x < 0)
	{
		putchar('-');
		x = -x;
	}
	do
	{
		buffer[length++] = x % 10 + '0';
		x /= 10;
	} while (x);
	do
	{
		putchar(buffer[--length]);
	} while (length);
}

const double PI = std::acos((double)-1);
#define DefinePoint(name)\
struct name\
{\
	double x, y;\
	name() {}\
	name(const double& x, const double& y) : x(x), y(y) {}\
};
DefinePoint(Point);
DefinePoint(Vector);

const double EPS = 1e-6;
inline int dcmp(const double& x)
{
	if (std::abs(x) < EPS)
		return 0;
	return x < 0 ? -1 : 1;
}
inline bool operator== (const Vector& a, const Vector& b)
{
	return dcmp(a.x - b.x) == 0 && dcmp(a.y - b.y) == 0;
}
inline Vector operator-(const Point& a, const Point& b)
{
	return Vector(b.x - a.x, b.y - a.y);
}
inline Vector operator+(const Vector& a, const Vector& b)
{
	return Vector(a.x + b.x, a.y + b.y);
}
struct Segment
{
	Point u, v;
	Segment() {}
	Segment(const Point& u, const Point& v) : u(u), v(v) {}
} s1, s2;
inline double Cross(const Vector& a, const Vector& b)
{
	return a.x * b.y - a.y * b.x;
}
inline double Dot(const Vector& a, const Vector& b)
{
	return a.x * b.x + a.y * b.y;
}
inline bool OnSegment(const Point& p, const Segment& s)
{
	return dcmp(Cross(s.u - s.v, s.u - p)) == 0 && dcmp(Dot(p - s.u, p - s.v)) <= 0;
}
int IsSegmentIntersected(const Segment& a, const Segment& b)
{
	if (dcmp(Cross(a.u - a.v, b.u - b.v)) == 0)
		return -1;
	if (OnSegment(a.u, b) || OnSegment(a.v, b) || OnSegment(b.u, a) || OnSegment(b.v, a))
		return true;
	return dcmp(Cross(a.u - a.v, a.u - b.u)) * dcmp(Cross(a.u - a.v, a.u - b.v)) < 0 &&
		dcmp(Cross(b.u - b.v, b.u - a.u)) * dcmp(Cross(b.u - b.v, b.u - a.v)) < 0;
}
struct Line
{
	Point p;
	Vector v;
	Line() {}
	Line(const Point& p, const Vector& v) : p(p), v(v) {}
};
inline double Length(const Vector& a)
{
	return std::sqrt(Dot(a, a));
}
inline Vector operator/ (const Vector& a, const double& b)
{
	return Vector(a.x / b, a.y / b);
}
inline Vector operator* (const Vector& a, const double& b)
{
	return Vector(a.x * b, a.y * b);
}
inline Point operator+ (const Point& a, const Vector& b)
{
	return Point(a.x + b.x, a.y + b.y);
}
inline Point GetLinesIntersection(const Line& a, const Line& b)
{
	return b.p + b.v * Cross(a.p - b.p, a.v) / Cross(a.v, b.v);
}

void readPoint(Point& p)
{
	scanf("%lf%lf", &p.x, &p.y);
}
void run()
{
	INT T = readIn();
	while (T--)
	{
		readPoint(s1.u);
		readPoint(s1.v);
		readPoint(s2.u);
		readPoint(s2.v);
		if (s1.u.y == s1.v.y || s2.u.y == s2.v.y)
		{
			puts("0.00");
			continue;
		}

		if (s1.u.y < s1.v.y) std::swap(s1.u, s1.v);
		if (s2.u.y < s2.v.y) std::swap(s2.u, s2.v);

		Vector vec1 = s1.v - s1.u;
		Vector vec2 = s2.v - s2.u;
		double angle1 = std::atan2(vec1.y, vec1.x);
		double angle2 = std::atan2(vec2.y, vec2.x);
		if (dcmp(angle1 - angle2) > 0)
		{
			std::swap(s1, s2);
			std::swap(vec1, vec2);
			std::swap(angle1, angle2);
		}

		int intersectionTest = IsSegmentIntersected(s1, s2);
		if (intersectionTest <= 0)
		{
			puts("0.00");
			return;
		}

		Line l1(s1.v, vec1);
		Line l2(s2.v, vec2);
		Line lx(Point(0, std::min(s1.u.y, s2.u.y)), Vector(1, 0));
		Point intersection = GetLinesIntersection(l1, l2);
		Point p1 = GetLinesIntersection(l1, lx);
		Point p2 = GetLinesIntersection(l2, lx);
		double ans = std::abs(lx.p.y - intersection.y) * std::abs(p1.x - p2.x) / 2;
		if (dcmp(angle1 - PI / 2) >= 0)
		{
			if (dcmp(s1.u.x - s2.u.x) <= 0)
				puts("0.00");
			else
			{
				printf("%.2f\n", ans + EPS);
			}
		}
		else if (dcmp(angle2 - PI / 2) >= 0)
		{
			printf("%.2f\n", ans + EPS);
		}
		else
		{
			if (dcmp(s2.u.x - s1.u.x) >= 0)
				puts("0.00");
			else
			{
				printf("%.2f\n", ans + EPS);
			}
		}
	}
}

int main()
{
	run();
	return 0;
}