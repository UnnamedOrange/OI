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
	bool minus = x < 0;
	if (minus) x = -x;
	do
	{
		buffer[length++] = x % 10 + '0';
		x /= 10;
	} while (x);
	if (minus) buffer[length++] = '-';
	do
	{
		putchar(buffer[--length]);
	} while (length);
}

//基础板块
namespace ComputationGeometry
{
	INT dcmp(const double x)
	{
		const double EPS = 1e-10;
		if (std::abs(x) <= EPS) return 0;
		return x < 0 ? -1 : 1;
	}
	struct Point
	{
		double x, y;
		Point() {}
		Point(const double& x, const double& y) : x(x), y(y) {}

		bool operator==(const Point& b) const { return !dcmp(x - b.x) && !dcmp(x - b.x); }
	};
	typedef Point Vector;
	//由于数据类型实质相同，因此需要手动对号入座
	Vector operator+(const Vector& a, const Vector& b)
	{
		return Vector(a.x + b.x, a.y + b.y);
	}
	//A - B，在坐标表示上是 a.x - b.x, a.y - b.y
	//对于点而言，A是终点，B是起点
	Vector operator-(const Vector& a, const Vector& b)
	{
		return Vector(a.x - b.x, a.y - b.y);
	}
	Vector operator*(const Vector& a, const double& b)
	{
		return Vector(a.x * b, a.y * b);
	}
	Vector operator/(const Vector& a, const double& b)
	{
		return Vector(a.x / b, a.y / b);
	}

	//点积
	double Dot(const Vector& a, const Vector& b)
	{
		return a.x * b.x + a.y * b.y;
	}
	//叉积
	double Cross(const Vector& a, const Vector& b)
	{
		return a.x * b.y - b.x * a.y;
	}
	//使用点积计算长度
	double Length(const Vector& a)
	{
		return std::sqrt(Dot(a, a));
	}
	//使用 a * b = |a||b| cos<a, b> 计算夹角
	double Angle(const Vector& a, const Vector& b)
	{
		return std::acos(Dot(a, b) / Length(a) / Length(b));
	}

	//使用三角函数推导向量旋转
	//x0 = L * cos(A)
	//y0 = L * sin(A)
	//x1 = L * cos(A + B) = L * (cosAcosB - sinAsinB)
	//y1 = L * sin(A + B) = L * (sinAcosB + cosAsinB)
	//B 为旋转角
	//cos(A) = x0 / L
	//sin(A) = y0 / L
	//代入 cosA, sinA 即为答案
	//记忆方法：
	//x y，y x，x1 的系数为 cos(A + B) 的 B 的三角函数，y1 的系数为 sin(A + B) 的 B 的三角函数
	//x * cosB - y * sinB, y * cosB + x * sinB
	Vector Rotate(const Vector& a, const double& rad)
	{
		return Vector(a.x * std::cos(rad) - a.y * std::sin(rad), a.y * std::cos(rad) + a.x * std::sin(rad));
	}
	//特殊角：
	//逆时针旋转 π / 4：-y, x
	//顺时针旋转 π / 4：y, -x
}
//点和直线
namespace ComputationGeometry
{
	struct Line
	{
		Point p;
		Vector v;
		Line() {}
		Line(const Point& p, const Vector& v) : p(p), v(v) {}
	};
	//取两直线交点，当且仅当 a × b != 0 时两直线有交点
	//作图，不难得出当右边的系数为正时，u 和 b.v 的手性应相同，就可以得出正确代码了
	Point GetLineIntersection(const Line& a, const Line& b)
	{
		Vector u = a.p - b.p;
		return b.p + b.v * (Cross(a.v, u) / Cross(a.v, b.v));
	}
}
using namespace ComputationGeometry;

Point GetD(Point A, Point B, Point C)
{
	Vector BA = A - B;
	Vector BC = C - B;
	double AngleABC = Angle(BA, BC);
	Vector BD(Rotate(BC, AngleABC / 3));

	Vector CB = B - C;
	Vector CA = A - C;
	double AngleACB = Angle(CA, CB);
	Vector CD(Rotate(CA, AngleACB / 3 * 2));

	Line bd(B, BD);
	Line cd(C, CD);
	return GetLineIntersection(bd, cd);
}

void run()
{
	INT T = readIn();
	while (T--)
	{
		INT buffer[6];
		for (int i = 0; i < 6; i++)
			buffer[i] = readIn();
		Point A(buffer[0], buffer[1]);
		Point B(buffer[2], buffer[3]);
		Point C(buffer[4], buffer[5]);

		Point t = GetD(A, B, C);
		printf("%.6f %.6f ", t.x, t.y);
		t = GetD(B, C, A);
		printf("%.6f %.6f ", t.x, t.y);
		t = GetD(C, A, B);
		printf("%.6f %.6f\n", t.x, t.y);
	}
}

int main()
{
	run();
	return 0;
}