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
typedef long long INT;
using std::cin;
using std::cout;
using std::endl;
inline INT readIn()
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
inline void printOut(INT x)
{
	char buffer[15];
	INT length = 0;
	bool minus = x < 0;
	if (minus) x = -x;
	do
	{
		buffer[length++] = x % 10 + '0';
		x /= 10;
	}
	while (x);
	if (minus) buffer[length++] = '-';
	do
	{
		putchar(buffer[--length]);
	}
	while (length);
}

const INT maxn = 85;
INT n, m;
INT line[maxn];

struct LargeInt
{
	static const INT digit = 100000000;
	static const INT size = 5;
	INT num[size];

	INT& operator[] (INT x)
	{
		return num[x];
	}
	const INT& operator[] (INT x) const
	{
		return num[x];
	}
	LargeInt() : num() {}
	LargeInt(INT x)
	{
		*this = x;
	}
	LargeInt operator= (INT x)
	{
		memset(num, 0, sizeof(num));
		num[0] = x;
	}
	INT length() const
	{
		for(int i = size - 1; i >= 0; i--)
			if(num[i]) return i + 1;
		return 0;
	}
	void carry()
	{
		for(int i = 0; i < size; i++)
		{
			if(i < size - 1) num[i + 1] += num[i] / digit;
			num[i] %= digit;
		}
	}

	LargeInt operator* (INT x) const
	{
		LargeInt ret;
		INT l = length();
		for(int i = 0; i < size; i++)
			ret[i] = num[i] * x;
		ret.carry();
		return ret;
	}
	LargeInt operator+ (const LargeInt& b) const
	{
		LargeInt ret;
		const LargeInt& a = *this;
		for(int i = 0; i < size; i++)
			ret[i] = a[i] + b[i];
		ret.carry();
		return ret;
	}
	bool operator< (const LargeInt& b) const
	{
		INT la = length();
		INT lb = b.length();
		if(la != lb) return la < lb;
		for(int i = la - 1; i >= 0; i--)
		{
			if(num[i] != b[i]) return num[i] < b[i];
		}
		return false;
	}
	void print()
	{
		INT l = length();
		if(!l) putchar('0');
		else
		{
			printf("%lld", num[l - 1]);
			for(int i = l - 2; i >= 0; i--)
				printf("%08lld", num[i]);
		}
	}
};

LargeInt f[maxn][maxn];
LargeInt mul[maxn];

void run()
{
	n = readIn();
	m = readIn();
	LargeInt ans;
	mul[0] = 1;
	for(int i = 1; i <= m; i++)
		mul[i] = mul[i - 1] * 2;

	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= m; j++)
			line[j] = readIn();

		for(int j = 1; j <= m; j++)
			f[j][j] = mul[m] * line[j];


		for(int l = 2; l <= m; l++)
		{
			for(int j = 1; j + l - 1 <= m; j++)
			{
				INT k = j + l - 1;
				f[j][k] = std::max(f[j][k - 1] + mul[m - l + 1] * line[k],
				                   f[j + 1][k] + mul[m - l + 1] * line[j]);
			}
		}
		ans = ans + f[1][m];
	}
	ans.print();
}

int main()
{
	run();
	return 0;
}
