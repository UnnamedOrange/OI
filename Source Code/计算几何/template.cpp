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
	//作图，不难发现当代码右边那两个叉积之商应该为正时，u 和 b.v 的左右应相同，这样就能推导出 u = a.p - b.p 而不是其相反向量了（注意起点和终点谁是谁）
	Point GetLinesIntersection(const Line& a, const Line& b)
	{
		Vector u = a.p - b.p;
		return b.p + b.v * (Cross(a.v, u) / Cross(a.v, b.v));
	}
	//求点到直线的距离，使用叉乘
	double DistanceFromPointToLine(const Point& a, const Line& b)
	{
		return std::abs(Cross(a - b.p, b.v) / Length(b.v));
	}
	//点在直线上的投影
	Point GetLineProjection(const Point& a, const Line& b)
	{
		return b.p + b.v * (Dot(a - b.p, b.v) / Dot(b.v, b.v));
	}
}
//点和线段
namespace ComputationGeometry
{
	struct Segment
	{
		Point u, v;
		Segment() {}
		Segment(const Point& u, const Point& v) : u(u), v(v) {}
		double Length() const
		{
			return ComputationGeometry::Length(u - v);
		}
		operator Vector() const
		{
			return v - u;
		}
	};
	//点到线段的距离
	double DistanceFromPointToSegment(const Point& a, const Segment& b)
	{
		if (b.u == b.v) return Length(a - b.u);
		Vector UA = a - b.u;
		Vector VA = a - b.v;
		Vector UV = b.v - b.u;
		if (dcmp(Dot(UA, UV)) < 0)
			return Length(UA);
		else if (dcmp(Dot(VA, UV)) > 0) //VA * VU < 0
			return Length(VA);
		else
			return std::abs(Cross(UA, UV) / b.Length());
	}
	//判断线段是否规范相交
	bool IsSegmentsProperIntersection(const Segment& a, const Segment& b)
	{
		if (dcmp(Cross(a, a.u - b.u)) * dcmp(Cross(a, a.u - b.v)) >= 0) return false;
		if (dcmp(Cross(b, b.u - a.u)) * dcmp(Cross(b, b.u - a.v)) >= 0) return false;
		return true;
	}
	//判断点是否在线段上
	bool IsOnSegment(const Point& a, const Segment& b)
	{
		return dcmp(Cross(a - b.u, a - b.v)) == 0 && dcmp(Dot(a - b.u, a - b.v)) <= 0;
	}
	//判断线段是否相交
	bool IsSegmentsIntersection(const Segment& a, const Segment& b)
	{
		double c1 = Cross(a, a.u - b.u);
		double c2 = Cross(a, a.u - b.v);
		if (!dcmp(c1) && !dcmp(c2))
			return IsOnSegment(a.u, b) || IsOnSegment(a.v, b) || IsOnSegment(b.u, a) || IsOnSegment(b.v, a);
		double c3 = Cross(b, b.u - a.u);
		double c4 = Cross(b, b.u - a.v);
		return dcmp(c1) * dcmp(c2) <= 0 && dcmp(c3) * dcmp(c4) <= 0;
	}
}
using namespace ComputationGeometry;

void run()
{

}

int main()
{
	run();
	return 0;
}