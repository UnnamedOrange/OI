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
using LL = long long;
using ULL = unsigned long long;
using std::cin;
using std::cout;
using std::endl;
using INT_PUT = int;
INT_PUT readIn()
{
	INT_PUT a = 0;
	bool positive = true;
	char ch = getchar();
	while (!(std::isdigit(ch) || ch == '-')) ch = getchar();
	if (ch == '-')
	{
		positive = false;
		ch = getchar();
	}
	while (std::isdigit(ch))
	{
		(a *= 10) -= ch - '0';
		ch = getchar();
	}
	return positive ? -a : a;
}
void printOut(INT_PUT x)
{
	char buffer[20];
	int length = 0;
	if (x < 0) putchar('-');
	else x = -x;
	do buffer[length++] = -(x % 10) + '0'; while (x /= 10);
	do putchar(buffer[--length]); while (length);
}

const int mod = int(1e9) + 7;
const int maxn = int(5e4) + 5;
int n, m, k;
char str[maxn];
int binary[maxn];

#define RunInstance(x) delete new x


void run()
{
	n = readIn();
	k = readIn();
	scanf("%s", str);
	m = strlen(str);
	std::reverse(str, str + m);
	for (int i = 0; i < m; i++)
		binary[i] = str[i] - '0';
	binary[0]--;
	int cnt = 0;
	while (binary[cnt] < 0)
	{
		binary[cnt] += 2;
		cnt++;
		binary[cnt]--;
	}
	while (m && !binary[m - 1]) m--;

	if (n == 1)
		printOut(1);
	else if (n == 2)
		printOut(0);
}

int main()
{
#ifndef LOCAL
	freopen("mothergoose.in", "r", stdin);
	freopen("mothergoose.out", "w", stdout);
#endif
	run();
	return 0;
}