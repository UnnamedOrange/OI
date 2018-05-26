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
typedef LL INT_PUT;
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

const int mod = int(1e9) + 7;
const int maxn = int(1e6) + 5;
char strn[maxn];
char strm[maxn];
LL n, m;
int a, b, c, d;

struct Matrix
{
	int c[2][2];
	Matrix() : c() {}
	Matrix(bool unit) : c()
	{
		c[0][0] = c[1][1] = 1;
	}
	int* operator[](int x) { return c[x]; }
	const int* operator[](int x) const { return c[x]; }
	Matrix operator*(const Matrix& b) const
	{
		Matrix ret;
		for (int i = 0; i < 2; i++)
			for (int k = 0; k < 2; k++) if (c[i][k])
				for (int j = 0; j < 2; j++)
					ret[i][j] = (ret[i][j] + (LL)c[i][k] * b[k][j]) % mod;
		return ret;
	}
	Matrix operator^(int y) const
	{
		Matrix ret(true);
		Matrix x(*this);
		while (y)
		{
			if (y & 1) ret = ret * x;
			x = x * x;
			y >>= 1;
		}
		return ret;
	}
} matrix, nextline;

void run()
{
	scanf("%s%s", strn, strm);
	a = readIn();
	b = readIn();
	c = readIn();
	d = readIn();
	int tempMod;
	tempMod = mod - (a != 1);
	for (char* ch = strm; *ch; ch++)
		m = (((m << 3) + (m << 1)) + (*ch - '0')) % tempMod;
	m = (m - 1 + tempMod) % tempMod;

	matrix[0][0] = a;
	matrix[0][1] = b;
	matrix[1][0] = 0;
	matrix[1][1] = 1;
	matrix = matrix ^ m;

	nextline[0][0] = c;
	nextline[0][1] = d;
	nextline[1][0] = 0;
	nextline[1][1] = 1;
	nextline = matrix * nextline;

	tempMod = mod - (nextline[0][0] != 1); // note: nextline[0][0] 相当于是新的递推式的系数，所以必须在这里判断是否为 1！直接判断 c 是错的！
	for (char* ch = strn; *ch; ch++)
		n = (((n << 3) + (n << 1)) + (*ch - '0')) % tempMod;
	n = (n - 1 + tempMod) % tempMod;

	matrix = (nextline ^ n) * matrix;
	printOut((matrix[0][0] + matrix[0][1]) % mod);
}

int main()
{
	run();
	return 0;
}

/* input
34578734657863487 38465873465876348 1 23734637 3892734 3849
*/
/* output
467549493
*/