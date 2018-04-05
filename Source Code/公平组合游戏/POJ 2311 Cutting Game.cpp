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

const int maxn = 205;
const char* str[] = { "LOSE", "WIN" };
int a, b;
int SG[maxn][maxn];

int DP(int w, int h)
{
	int& ans = SG[w][h];
	if (ans != -1) return ans;
	bool vis[maxn] = {};
	for (int i = 2; w - i >= 2; i++)
		vis[DP(i, h) ^ DP(w - i, h)] = true;
	for (int i = 2; h - i >= 2; i++)
		vis[DP(w, i) ^ DP(w, h - i)] = true;
	for (int i = 0; i < maxn; i++)
		if (!vis[i]) return ans = i;
}

void run()
{
	memset(SG, -1, sizeof(SG));
	while (~scanf("%d%d", &a, &b))
		puts(str[bool(DP(a, b))]);
}

int main()
{
	run();
	return 0;
}