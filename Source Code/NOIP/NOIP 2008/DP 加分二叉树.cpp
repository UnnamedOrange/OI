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
typedef long long INT;
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

const INT maxn = 35;
INT n;
INT weight[maxn];
INT f[maxn][maxn];
INT root[maxn][maxn];

INT dp(INT l, INT r)
{
	if(f[l][r]) return f[l][r];
	if(l > r) return 1;
	if(l == r) return weight[l];

	INT& ans = f[l][r];
	for(int i = l; i <= r; i++)
	{
		if(dp(l, i - 1) * dp(i + 1, r) + weight[i] > ans)
		{
			ans = dp(l, i - 1) * dp(i + 1, r) + weight[i];
			root[l][r] = i;
		}
	}
	return ans;
}
void print(INT l, INT r)
{
	if(!root[l][r])
	{
		if(l == r) cout << l << " ";
		return;
	}
	cout << root[l][r] << " ";
	print(l, root[l][r] - 1);
	print(root[l][r] + 1, r);
}

void run()
{
	n = readIn();
	for(int i = 1; i <= n; i++)
	{
		weight[i] = readIn();
	}
	cout << dp(1, n) << endl;
	print(1, n);
}

int main()
{
	run();
	return 0;
}
