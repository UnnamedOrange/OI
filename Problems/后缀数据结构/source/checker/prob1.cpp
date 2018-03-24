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

const int maxn = 2005;
int n;
int k;
char str[maxn];

void run()
{
	scanf("%s", str);
	n = strlen(str);
	k = readIn();
	std::map<std::string, int> times;
	for (int i = 0; i < n; i++)
		for (int j = i; j < n; j++)
			times[std::string(str + i, str + j + 1)]++;

	LL ans = 0;
	for (std::map<std::string, int>::iterator it = times.begin(); it != times.end(); it++)
		ans += it->second == k;
	printOut(ans);
}

int main()
{
#ifndef LOCAL
	freopen("prob1.in", "r", stdin);
	freopen("prob1.out", "w", stdout);
#endif 
	run();
	return 0;
}