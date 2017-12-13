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

//�������
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
	//������������ʵ����ͬ�������Ҫ�ֶ��Ժ�����
	Vector operator+(const Vector& a, const Vector& b)
	{
		return Vector(a.x + b.x, a.y + b.y);
	}
	//A - B���������ʾ���� a.x - b.x, a.y - b.y
	//���ڵ���ԣ�A���յ㣬B�����
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

	//���
	double Dot(const Vector& a, const Vector& b)
	{
		return a.x * b.x + a.y * b.y;
	}
	//���
	double Cross(const Vector& a, const Vector& b)
	{
		return a.x * b.y - b.x * a.y;
	}
	//ʹ�õ�����㳤��
	double Length(const Vector& a)
	{
		return std::sqrt(Dot(a, a));
	}
	//ʹ�� a * b = |a||b| cos<a, b> ����н�
	double Angle(const Vector& a, const Vector& b)
	{
		return std::acos(Dot(a, b) / Length(a) / Length(b));
	}

	//ʹ�����Ǻ����Ƶ�������ת
	//x0 = L * cos(A)
	//y0 = L * sin(A)
	//x1 = L * cos(A + B) = L * (cosAcosB - sinAsinB)
	//y1 = L * sin(A + B) = L * (sinAcosB + cosAsinB)
	//B Ϊ��ת��
	//cos(A) = x0 / L
	//sin(A) = y0 / L
	//���� cosA, sinA ��Ϊ��
	//���䷽����
	//x y��y x��x1 ��ϵ��Ϊ cos(A + B) �� B �����Ǻ�����y1 ��ϵ��Ϊ sin(A + B) �� B �����Ǻ���
	//x * cosB - y * sinB, y * cosB + x * sinB
	Vector Rotate(const Vector& a, const double& rad)
	{
		return Vector(a.x * std::cos(rad) - a.y * std::sin(rad), a.y * std::cos(rad) + a.x * std::sin(rad));
	}
	//����ǣ�
	//��ʱ����ת �� / 4��-y, x
	//˳ʱ����ת �� / 4��y, -x
}
//���ֱ��
namespace ComputationGeometry
{
	struct Line
	{
		Point p;
		Vector v;
		Line() {}
		Line(const Point& p, const Vector& v) : p(p), v(v) {}
	};
	//ȡ��ֱ�߽��㣬���ҽ��� a �� b != 0 ʱ��ֱ���н���
	//��ͼ�����ѷ��ֵ������ұ����������֮��Ӧ��Ϊ��ʱ��u �� b.v ������Ӧ��ͬ�����������Ƶ��� u = a.p - b.p ���������෴�����ˣ�ע�������յ�˭��˭��
	Point GetLinesIntersection(const Line& a, const Line& b)
	{
		Vector u = a.p - b.p;
		return b.p + b.v * (Cross(a.v, u) / Cross(a.v, b.v));
	}
	//��㵽ֱ�ߵľ��룬ʹ�ò��
	double DistanceFromPointToLine(const Point& a, const Line& b)
	{
		return std::abs(Cross(a - b.p, b.v) / Length(b.v));
	}
	//����ֱ���ϵ�ͶӰ
	Point GetLineProjection(const Point& a, const Line& b)
	{
		return b.p + b.v * (Dot(a - b.p, b.v) / Dot(b.v, b.v));
	}
}
//����߶�
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
	//�㵽�߶εľ���
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
	//�ж��߶��Ƿ�淶�ཻ
	bool IsSegmentsProperIntersection(const Segment& a, const Segment& b)
	{
		if (dcmp(Cross(a, a.u - b.u)) * dcmp(Cross(a, a.u - b.v)) >= 0) return false;
		if (dcmp(Cross(b, b.u - a.u)) * dcmp(Cross(b, b.u - a.v)) >= 0) return false;
		return true;
	}
	//�жϵ��Ƿ����߶���
	bool IsOnSegment(const Point& a, const Segment& b)
	{
		return dcmp(Cross(a - b.u, a - b.v)) == 0 && dcmp(Dot(a - b.u, a - b.v)) <= 0;
	}
	//�ж��߶��Ƿ��ཻ
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