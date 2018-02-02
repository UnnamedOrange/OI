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
	putchar('\n');
}

struct Point
{
	double x, y;
	Point() {}
	Point(const double& x, const double& y) : x(x), y(y) {}
};
typedef Point Vector;
inline Vector operator-(const Point& a, const Point& b)
{
	return Vector(a.x - b.x, a.y - b.y);
}
inline double Length2(const Vector& a)
{
	return a.x * a.x + a.y * a.y;
}
inline double Length(const Vector& a)
{
	return std::sqrt(Length2(a));
}
inline double Cross(const Vector& a, const Vector& b)
{
	return a.x * b.y - a.y * b.x;
}
inline double Dis(const Point& a, const Point& b, const Point& p)
{
	return std::abs(Cross(b - a, p - a)) / Length(a - b);
}

const INT maxn = 1005;
INT n;

Point points[maxn];
double ans = 1e100;

void run()
{
	n = readIn();
	for (int i = 1; i <= n; i++)
	{
		points[i].x = readIn();
		points[i].y = readIn();
	}
	points[n + 1] = points[1];
	points[n + 2] = points[2];

	for (int i = 1; i <= n; i++)
	{
		ans = std::min(ans, Length(points[i + 1] - points[i]) / 2);
		ans = std::min(ans, Dis(points[i], points[i + 2], points[i + 1]) / 2);
	}
	printf("%.8f\n", ans);
}

int main()
{
	run();
	return 0;
}