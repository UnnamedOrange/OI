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
using std::cin;
using std::cout;
using std::endl;
typedef int INT;
inline INT readIn()
{
	INT a = 0;
	bool minus = false;
	char ch = getchar();
	while (!(ch == '-' || ch >= '0' && ch <= '9')) ch = getchar();
	if (ch == '-')
	{
		minus = true;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
	{
		a *= 10;
		a += ch;
		a -= '0';
		ch = getchar();
	}
	if (minus) a = -a;
	return a;
}
inline INT read()
{
	char ch = getchar();
	while (!(ch >= '0' && ch <= '9')) ch = getchar();
	return ch - '0';
}

struct Point
{
	double x, y;
	Point(double x = 0, double y = 0) : x(x), y(y) {}
};
typedef Point Vector;

Point operator+ (const Point& a, const Vector& b)
{
	return Point(a.x + b.x, a.y + b.y);
}
Vector operator- (const Point& a, const Point& b)
{
	return Vector(a.x - b.x, a.y - b.y);
}
double Cross(const Vector& a, const Vector& b)
{
	return a.x * b.y - a.y * b.x;
}
const Point delta[] =
{
	Point(0, 0),
	Point(-1, -1),
	Point(0, -1),
	Point(1, -1),
	Point(-1, 0),
	Point(0, 0),
	Point(1, 0),
	Point(-1, 1),
	Point(0, 1),
	Point(1, 1)
};
const double EPS = 1e-8;

void run()
{
	INT T = readIn();
	while (T--)
	{
		double area = 0;
		Point pos;

		INT move;
		while ((move = read()) != 5)
		{
			area += Cross(pos, pos + delta[move]);
			pos = pos + delta[move];
		}

		area /= 2;
		area = std::abs(area);
		if (area - std::floor(area) < EPS)
			printf("%.0f\n", area);
		else
			printf("%.1f\n", area);
	}
}

int main()
{
	run();
	return 0;
}
