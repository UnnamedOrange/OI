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
using LL = long long;
using ULL = unsigned long long;
using std::cin;
using std::cout;
using std::endl;
using INT_PUT = int;
INT_PUT readIn()
{
	INT_PUT a = 0;
	bool positive = true;
	char ch = getchar();
	while (!(std::isdigit(ch) || ch == '-')) ch = getchar();
	if (ch == '-')
	{
		positive = false;
		ch = getchar();
	}
	while (std::isdigit(ch))
	{
		(a *= 10) -= ch - '0';
		ch = getchar();
	}
	return positive ? -a : a;
}
void printOut(INT_PUT x)
{
	char buffer[20];
	int length = 0;
	if (x < 0) putchar('-');
	else x = -x;
	do buffer[length++] = -(x % 10) + '0'; while (x /= 10);
	do putchar(buffer[--length]); while (length);
}

#define DefinePoint(name)\
struct name\
{\
	double x, y;\
	name() {}\
	name(double x, double y) : x(x), y(y) {}\
};
DefinePoint(Point)
DefinePoint(Vector)
int dcmp(double x)
{
	const double EPS = 1e-6;
	if (std::abs(x) <= EPS)
		return 0;
	return x < 0 ? -1 : 1;
}
Vector operator-(const Point& a, const Point& b)
{
	return Vector(b.x - a.x, b.y - a.y);
}
Vector operator-(const Vector& a, const Vector& b)
{
	return Vector(a.x - b.x, a.y - b.y);
}
Point operator+(const Point& a, const Vector& b)
{
	return Point(a.x + b.x, a.y + b.y);
}
double Cross(const Vector& a, const Vector& b)
{
	return a.x * b.y - a.y * b.x;
}

const int maxn = int(2e5) + 5;
int n;
Vector p[2];
Point lamps[maxn];
int K[maxn];

#define RunInstance(x) delete new x
struct brute
{
	int remain[maxn];
	int ans[maxn];

	bool inRange(int from, int to)
	{
		Vector mid = Vector((p[0].x + p[1].x) / 2, (p[0].y + p[1].y) / 2);
		int test = dcmp(Cross(p[0], mid));
		int test1 = dcmp(Cross(p[0], lamps[from] - lamps[to]));
		int test2 = dcmp(Cross(lamps[from] - lamps[to], p[1]));
		if (test == test1 && test == test2)
			return true;
		if (!test1 && test == test2)
			return true;
		if (test == test1 && !test2)
			return true;
		return false;
	}
	void shine(int idx, int t)
	{
		for (int i = t + 1; i <= n; i++)
		{
			if (ans[i]) continue;
			if (inRange(idx, i))
			{
				if (!(--remain[i]))
				{
					ans[i] = t;
					shine(i, t);
				}
			}
		}
	}

	brute() : ans()
	{
		std::memcpy(remain, K, sizeof(remain));
		for (int i = 1; i <= n; i++)
		{
			if (!ans[i])
			{
				ans[i] = i;
				shine(i, i);
			}
		}

		for (int i = 1; i <= n; i++)
		{
			printOut(ans[i]);
			putchar(' ');
		}
	}
};

void run()
{
	n = readIn();
	p[0].x = readIn();
	p[0].y = readIn();
	p[1].x = readIn();
	p[1].y = readIn();
	for (int i = 1; i <= n; i++)
	{
		lamps[i].x = readIn();
		lamps[i].y = readIn();
	}
	for (int i = 1; i <= n; i++)
		K[i] = readIn();

	if (n <= 1000)
		RunInstance(brute);
}

int main()
{
#ifndef LOCAL
	freopen("lamp.in", "r", stdin);
	freopen("lamp.out", "w", stdout);
#endif
	run();
	return 0;
}