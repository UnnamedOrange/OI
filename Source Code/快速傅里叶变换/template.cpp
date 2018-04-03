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
}

struct Complex
{
	double x, y;
	inline Complex() {}
	inline Complex(const double& x, const double& y) : x(x), y(y) {}
	inline friend Complex operator+(const Complex& a, const Complex& b)
	{
		return Complex(a.x + b.x, a.y + b.y);
	}
	inline friend Complex operator-(const Complex& a, const Complex& b)
	{
		return Complex(a.x - b.x, a.y - b.y);
	}
	inline friend Complex operator*(const Complex& a, const Complex& b)
	{
		return Complex(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x);
	}
	inline void operator/= (const double& b)
	{
		x /= b;
		y /= b;
	}
};
const double PI = std::acos((double)-1);
const double EPS = 0.5;
const INT maxn = 262150;
INT n, m;
Complex a[maxn];
Complex b[maxn];
Complex c[maxn];

struct FFT
{
	int n, logn;
	inline int revbit(int x)
	{
		int ret = 0;
		for (int i = 0; i < logn; i++)
			ret = (ret << 1) | (bool)(x & (1 << i));
		return ret;
	}
	FFT(Complex *a, int logn, int sig) : n(1 << logn), logn(logn)
	{
		for (int i = 0; i < n; i++)
		{
			int t = revbit(i);
			if (i < t) std::swap(a[i], a[t]);
		}
		for (int S = 2; S <= n; S <<= 1)
		{
			int half = S >> 1;
			Complex w1(std::cos(2 * PI / S), std::sin(2 * PI / S) * sig);
			for (int j = 0; j < n; j += S)
			{
				Complex *A = a + j;
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
	}
};
struct DFT : private FFT
{
	DFT(Complex *a, int logn) : FFT(a, logn, 1) {}
};
struct IDFT : private FFT
{
	IDFT(Complex *a, int logn) : FFT(a, logn, -1)
	{
		int n = 1 << logn;
		for (int i = 0; i < n; i++)
			a[i] /= n;
	}
};

void run()
{
	n = readIn();
	m = readIn();
	for (int i = 0; i <= n; i++)
		a[i].x = readIn();
	for (int i = 0; i <= m; i++)
		b[i].x = readIn();
	int logn = 0;
	while ((1 << logn) < std::max(n + 1, m + 1))
		logn++;
	logn++;
	DFT(a, logn);
	DFT(b, logn);
	int length = 1 << logn;
	for (int i = 0; i < length; i++)
		c[i] = a[i] * b[i];
	IDFT(c, logn);
	for (int i = 0, to = n + m; i <= to; i++)
	{
		printOut(c[i].x + EPS);
		putchar(' ');
	}
}

int main()
{
	run();
	return 0;
}