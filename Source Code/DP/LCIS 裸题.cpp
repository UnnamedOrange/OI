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
typedef int INT;
inline INT readIn()
{
	INT a = 0;
	bool minus = false;
	char ch = getchar();
	while (!(ch == EOF || ch == '-' || ch >= '0' && ch <= '9')) ch = getchar();
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

const INT maxn = 5005;
INT n, m;

INT a[maxn], b[maxn];

INT f[maxn];
void work2()
{
	for (int i = 1; i <= n; i++)
	{
		INT max = 0;
		for (int j = 1; j <= m; j++)
		{
			if (a[i] > b[j] && max < f[j])
			{
				max = f[j];
			}
			else if (a[i] == b[j])
			{
				f[j] = max + 1;
			}
		}
	}
}

void run()
{
	n = readIn();
	for (int i = 1; i <= n; i++) a[i] = readIn();
	m = readIn();
	for (int i = 1; i <= n; i++) b[i] = readIn();

	work2();
	INT ans = 0;
	for (int i = 1; i <= m; i++) ans = std::max(ans, f[i]);
	cout << ans << endl;
}

int main()
{
	run();
	return 0;
}
