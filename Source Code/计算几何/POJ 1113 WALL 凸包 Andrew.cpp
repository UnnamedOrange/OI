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
int n, l;

#define DefinePoint(name)					\
struct name									\
{											\
	double x, y;							\
	name() {}								\
	name(double x, double y) : x(x), y(y) {}\
};
DefinePoint(Point);
DefinePoint(Vector);
Vector operator-(const Point& a, const Point& b)
{
	return Vector(b.x - a.x, b.y - a.y);
}
Vector operator-(const Vector& a, const Vector& b)
{
	return Vector(a.x - b.x, a.y - b.y);
}
double Cross(const Vector& a, const Vector& b)
{
	return a.x * b.y - a.y * b.x;
}
double Dot(const Vector& a, const Vector& b)
{
	return a.x * b.x + a.y * b.y;
}
double Length(const Vector& a)
{
	return std::sqrt(Dot(a, a));
}
int dcmp(const double& x)
{
	const double EPS = 1e-8;
	if (std::abs(x) < EPS) return 0;
	return x < 0 ? -1 : 1;
}

Point points[maxn];
bool comp(const Point& a, const Point& b)
{
	if (dcmp(a.x - b.x)) return a.x < b.x;
	return a.y < b.y;
}
void Andrew()
{
	std::sort(points + 1, points + 1 + n, comp);
	std::vector<Point> s;
	s.push_back(points[1]);
	for (int i = 2; i <= n; i++)
	{
		while (s.size() >= 2 && Cross(s[s.size() - 2] - s[s.size() - 1], s[s.size() - 1] - points[i]) < 0)
			s.pop_back();
		s.push_back(points[i]);
	}
	int certain = s.size();
	for (int i = n - 1; i >= 1; i--)
	{
		while (s.size() > certain && Cross(s[s.size() - 2] - s[s.size() - 1], s[s.size() - 1] - points[i]) < 0)
			s.pop_back();
		s.push_back(points[i]);
	}
	double ans = 0;
	while (s.size() > 1)
	{
		ans += Length(s.back() - s[s.size() - 2]);
		s.pop_back();
	}

	printOut(ans + 2 * PI * l + 0.5);
}

void run()
{
	n = readIn();
	l = readIn();
	for (int i = 1; i <= n; i++)
	{
		points[i].x = readIn();
		points[i].y = readIn();
	}
	Andrew();
}

int main()
{
	run();
	return 0;
}