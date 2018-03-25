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

struct Complex
{
	double x, y;
	Complex() {}
	Complex(double x, double y) : x(x), y(y) {}
	friend Complex operator+(const Complex& a, const Complex& b)
	{
		return Complex(a.x + b.x, a.y + b.y);
	}
	friend Complex operator-(const Complex& a, const Complex& b)
	{
		return Complex(a.x - b.x, a.y - b.y);
	}
	friend Complex operator*(const Complex& a, const Complex& b)
	{
		return Complex(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x);
	}
};

const double PI = std::acos((double)-1);
const int maxn = 100005;
int logn;
int max;
int origin[maxn];
int times[maxn];

int revbit[262150];
void init()
{
	int n = 1 << logn;
	logn--;
	for (int i = 0; i < n; i++)
		revbit[i] = (revbit[i >> 1] >> 1) | ((i & 1) << logn);
	logn++;
}
void DFT(Complex* a, int type)
{
	int n = 1 << logn;
	for (int i = 0; i < n; i++)
		if (i < revbit[i])
			std::swap(a[i], a[revbit[i]]);
	for (int i = 1; i <= logn; i++)
	{
		int S = 1 << i;
		int half = S >> 1;
		static double COS[25], SIN[25];
		if (!COS[i]) COS[i] = std::cos(2 * PI / S);
		if (!SIN[i]) SIN[i] = std::sin(2 * PI / S);
		Complex w1(COS[i], SIN[i] * type);
		for (int j = 0; j < n; j += S)
		{
			Complex* A = a + j;
			Complex w(1, 0);
			for (int k = 0; k < half; k++)
			{
				Complex t = w * A[k + half];
				A[k + half] = A[k] - t;
				A[k] = A[k] + t;
				w = w * w1;
			}
		}
	}
	if (!~type)
		for (int i = 0; i < n; i++)
			a[i].x /= n;
}
Complex a[262150];
LL f[maxn * 2];

int n;

void run()
{
	int T = readIn();
	while (T--)
	{
		n = readIn();
		memset(times, 0, sizeof(int) * (max + 1));
		max = 0;
		for (int i = 1; i <= n; i++)
		{
			times[origin[i] = readIn()]++;
			max = std::max(max, origin[i]);
		}
		logn = 0;
		while (1 << logn <= max) logn++;
		logn++;
		init();

		memset(a, 0, sizeof(Complex) * (1 << logn));
		for (int i = 1; i <= max; i++)
			a[i].x = times[i];
		DFT(a, 1);
		int t = 1 << logn;
		for (int i = 0; i < t; i++)
			a[i] = a[i] * a[i];
		DFT(a, -1);
		for (int i = 0, to = max * 2; i <= to; i++)
			f[i] = a[i].x + 0.5;

		LL sum = (LL)n * (n - 1) * (n - 2) / 3;
		for (int i = 1; i <= max; i++)
			f[i * 2] -= times[i];

		LL cannot = 0;
		LL accum = 0;
		for (int i = 1; i <= max; i++)
		{
			accum += f[i];
			cannot += accum * times[i];
		}
		printf("%.7f\n", (double)(sum - cannot) / sum);
	}
}

int main()
{
	run();
	return 0;
}