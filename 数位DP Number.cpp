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
using std::cin;
using std::cout;
using std::endl;
typedef unsigned long long INT;
inline INT readIn()
{
	INT a = 0;
	bool minus = false;
	char ch = getchar();
	while (!(ch == '-' || ch >= '0' && ch <= '9')) ch = getchar();
	if (ch == '-')
	{
		minus = true;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
	{
		a *= 10;
		a += ch;
		a -= '0';
		ch = getchar();
	}
	if (minus) a = -a;
	return a;
}

const INT maxn = 25;
INT N;
INT n;
INT num[maxn];
INT f[maxn][13][2][2];

INT dp(INT stage, INT mod, bool exist, bool isOne, bool isTop)
{
	if (!stage)
	{
		return exist && !mod;
	}
	if (!isTop && ~f[stage][mod][exist][isOne]) return f[stage][mod][exist][isOne];

	INT ans = 0;
	INT maxDigit = isTop ? num[stage] : 9;
	for (int i = 0; i <= maxDigit; i++)
	{
		ans += dp(stage - 1, (mod * 10 + i) % 13, exist || (isOne && i == 3), i == 1, isTop && i == maxDigit);
	}
	if (!isTop) f[stage][mod][exist][isOne] = ans;
	return ans;
}

void run()
{
	N = readIn();
	while (N)
	{
		num[++n] = N % 10;
		N /= 10;
	}
	memset(f, -1, sizeof(f));
	cout << dp(n, 0, false, false, true) << endl;
}

int main()
{
	run();
	return 0;
}