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
	//��ͼ�����ѵó����ұߵ�ϵ��Ϊ��ʱ��u �� b.v ������Ӧ��ͬ���Ϳ��Եó���ȷ������
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