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
	//求单位向量
	Vector Unit(const Vector& a)
	{
		double length = Length(a);
		return Vector(a.x / length, a.y / length);
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
		Point point(const double& t) const
		{
			return p + v * t;
		}
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
		return dcmp(Cross(a, a.u - b.u)) * dcmp(Cross(a, a.u - b.v)) < 0 &&
			dcmp(Cross(b, b.u - a.u)) * dcmp(Cross(b, b.u - a.v)) < 0;
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
//圆
namespace ComputationGeometry
{
	//应该在草稿纸上推导出计算方法后再照着推导结果打出代码
	struct Circle
	{
		Point c;
		double r;
		Circle() {}
		Circle(const Point& c, const double& r) : c(c), r(r) {}
		Point point(const double& rad) const
		{
			return Point(c.x + std::cos(rad) * r, c.y + std::sin(rad) * r);
		}
	};
	//直线和圆的交点（解方程组法）
	INT GetLineCircleIntersection(const Circle& a, const Line& b, double& t1, double& t2, Point& p1, Point& p2)
	{
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
			return 0;
		else if (dcmp(delta) == 0)
		{
			p1 = p2 = b.point(t1 = t2 = -B / (2 * A));
			return 1;
		}
		//else
		delta = std::sqrt(delta);
		p1 = b.point(t1 = (-B - delta) / (2 * A));
		p2 = b.point(t2 = (-B + delta) / (2 * A));
		return 2;
	}
	//直线和圆的交点（几何法）
	INT GetLineCircleIntersection(const Circle& a, const Line& b, Point& p1, Point& p2)
	{
		Point p = GetLineProjection(a.c, b);
		double d = Length(p - a.c);
		if (dcmp(d - a.r) > 0)
			return 0;
		else if (dcmp(d - a.r) == 0)
		{
			p1 = p2 = p;
			return 1;
		}
		//else
		Vector v = Unit(b.v);
		double L = std::sqrt(a.r * a.r - d * d);
		p1 = p - v * L;
		p2 = p + v * L;
		return 2;
	}
	//求向量极角
	double Angle(const Vector& v)
	{
		return std::atan2(v.y, v.x);
	}
	//圆与圆的交点（余弦定理）
	INT GetCirclesIntersection(const Circle& a, const Circle& b, Point& p1, Point& p2)
	{
		double d = Length(a.c - b.c);
		if (dcmp(d) == 0)
		{
			if (dcmp(a.r - b.r) == 0)
				return -1; //两圆相交
			else
				return 0;
		}
		if (dcmp(a.r + b.r - d) < 0)
			return 0; //外离
		if (dcmp(std::abs(a.r - b.r) - d) > 0)
			return 0; //内含

		double AngleA = Angle(b.c - a.c); //注意以 a 为中心，则向量起点为 a.c
		double AngleDR = std::acos((a.r * a.r + d * d - b.r * b.r) / (2 * a.r * d)); //余弦定理
		p1 = a.point(AngleA - AngleDR);
		p2 = a.point(AngleA + AngleDR);
		return 1 + !(p1 == p2);
	}
	//圆的切线
	INT GetTangents(const Circle& a, const Point& b, Vector& v1, Vector& v2)
	{
		Vector u = a.c - b; //起点为 p
		double d = Length(u);
		if (dcmp(d - a.r) == 0)
		{
			v1 = v2 = Rotate(u, std::acos(-1) / 2); //旋转 90 度
			return 1;
		}
		else if (dcmp(d - a.r) < 0)
			return 0;
		double Angle = asin(a.r / d);
		v1 = Rotate(u, -Angle);
		v2 = Rotate(u, Angle);
		return 2;
	}
	//圆的公切线（求切点）
	INT GetCommonTangents(const Circle& a, const Circle& b, Point* pa, Point* pb)
	{
		if (dcmp(a.r - b.r) < 0)
			return GetCommonTangents(b, a, pb, pa);
		const double PI = std::acos(-1);
		Vector link = b.c - a.c;
		double d2 = Dot(link, link);
		double rDiff = a.r - b.r;
		double rSum = a.r + b.r;
		double base = std::atan2(link.y, link.x); //极角

		if (dcmp(d2) == 0 && dcmp(a.r - b.r) == 0)
			return -1; //两圆完全重合（情况 1）
		else if (dcmp(d2 - rDiff * rDiff) < 0)
			return 0; //内含（情况 2）
		else if (dcmp(d2 - rDiff * rDiff < 0))
		{
			*(pa++) = a.point(base);
			*(pb++) = b.point(base);
			return 1; //内切（情况 3）
		}

		INT ret = 0;
		//剩下的都有两条外公切线
		double ang = std::acos(rDiff / std::sqrt(d2)); //转角
		*(pa++) = a.point(base + ang); *(pb++) = b.point(base + ang); ret++;
		*(pa++) = a.point(base - ang); *(pb++) = b.point(base - ang); ret++; //外公切线对应向量平行
		if (dcmp(d2 - rSum * rSum) == 0) //一条内公切线（情况 5）
		{
			*(pa++) = a.point(base); *(pb++) = b.point(PI + base); ret++; // b 圆为相反方向（加 PI）
		}
		else if (dcmp(d2 - rSum * rSum) > 0) //两条外公切线（情况 6）
		{
			ang = std::acos(rSum / std::sqrt(d2));
			*(pa++) = a.point(base + ang); *(pb++) = b.point(PI + base + ang); ret++;
			*(pa++) = a.point(base - ang); *(pb++) = b.point(PI + base - ang); ret++; //内公切线相对于极角对称（加 PI）
		}
		return ret;
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