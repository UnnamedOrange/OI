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

const double PI = std::acos((double)-1);
const int maxn = 1005;
int n;

const double EPS = 1e-8;
int dcmp(const double& x)
{
	if (std::abs(x) < EPS)
		return 0;
	return x < 0 ? -1 : 1;
}
#define DefinePoint(name)										\
struct name														\
{																\
	double x, y;												\
	name() {}													\
	name(const double& x, const double& y) : x(x), y(y) {}		\
};
DefinePoint(Point);
DefinePoint(Vector);
Vector operator-(const Point& from, const Point& to)
{
	return Vector(to.x - from.x, to.y - from.y);
}
double Dot(const Vector& a, const Vector& b)
{
	return a.x * b.x + a.y * b.y;
}
double Length(const Vector& a)
{
	return std::sqrt(Dot(a, a));
}
struct Circle
{
	Point p;
	double r;
	Circle() {}
	Circle(const Point& p, const double& r) : p(p), r(r) {}
} circles[maxn];
struct Event
{
	double pos;
	bool type;
	Event() {}
	Event(const double& pos, const bool& type) : pos(pos), type(type) {}
	bool operator< (const Event& b) const
	{
		if (dcmp(pos - b.pos))
			return dcmp(pos - b.pos) < 0;
		return type > b.type;
	}
};

enum
{
	COVERED,
	VALID,
	INVALID
};
int GetCirclesRelation(const Circle& a, const Circle& b)
{
	double d = Length(a.p - b.p);
	if (dcmp(a.r - b.r) < 0)
	{
		if (dcmp(d - (b.r - a.r)) <= 0)
			return COVERED;
		else if (dcmp(d - (a.r + b.r)) >= 0)
			return INVALID;
		return VALID;
	}
	else if (dcmp(a.r - b.r) == 0)
	{
		if (dcmp(d) == 0)
			return COVERED;
		else if (dcmp(d - (a.r + b.r)) >= 0)
			return INVALID;
		return VALID;
	}
	else
	{
		if (dcmp(d - (a.r - b.r)) <= 0)
			return INVALID;
		else if (dcmp(d - (a.r + b.r)) >= 0)
			return INVALID;
		return VALID;
	}
}
void GetCirclesIntersection(const Circle& a, const Circle& b, std::vector<Event>& events)
{
	Vector aTob = a.p - b.p;
	double d = Length(aTob);
	double COS = (a.r * a.r + d * d - b.r * b.r) / (2 * a.r * d);
	double angle = std::acos(COS);
	double base = std::atan2(aTob.y, aTob.x);
	if (dcmp(base - angle + PI) <= 0)
	{
		events.push_back(Event(base - angle + 2 * PI, true));
		events.push_back(Event(PI, false));
		events.push_back(Event(-PI, true));
	}
	else
	{
		events.push_back(Event(base - angle, true));
	}
	if (dcmp(base + angle - PI) >= 0)
	{
		events.push_back(Event(PI, false));
		events.push_back(Event(-PI, true));
		events.push_back(Event(base + angle - 2 * PI, false));
	}
	else
	{
		events.push_back(Event(base + angle, false));
	}
}

void run()
{
	n = readIn();
	for (int i = 1; i <= n; i++)
	{
		double r, x, y;
		scanf("%lf%lf%lf", &r, &x, &y);
		circles[i].p.x = x;
		circles[i].p.y = y;
		circles[i].r = r;
	}

	double ans = 0;
	std::vector<Event> events;
	for (int i = 1; i <= n; i++)
	{
		events.clear();
		bool bOk = true;
		for (int j = i + 1; j <= n; j++)
		{
			int res = GetCirclesRelation(circles[i], circles[j]);
			if (res == INVALID) continue;
			else if (res == COVERED)
			{
				bOk = false;
				break;
			}
			GetCirclesIntersection(circles[i], circles[j], events);
		}
		if (!bOk) continue;

		std::sort(events.begin(), events.end());
		double accum = 0;
		double pre;
		int count_ = 0;
		for (int j = 0; j < events.size(); j++)
		{
			if (count_) accum += events[j].pos - pre;
			pre = events[j].pos;
			if (events[j].type)
				count_++;
			else
				count_--;
		}
		ans += (2 * PI - accum) * circles[i].r;
	}
	printf("%.3f", ans);
}

int main()
{
#ifndef LOCAL

#endif
	run();
	return 0;
}