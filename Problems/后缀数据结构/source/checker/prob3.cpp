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

const int maxn = 2005;
int n;
char str[maxn];

void run()
{
	scanf("%s", str);
	n = strlen(str);
	std::set<std::string> times;
	for (int i = 0; i < n; i++)
		for (int j = i; j < n; j++)
			times.insert(std::string(str + i, str + j + 1));

	ULL ans = 0;
	for (std::set<std::string>::iterator it = times.begin(); it != times.end(); it++)
		ans += (*it).length();
	printf("%llu", ans);
}

int main()
{
#ifndef LOCAL
	freopen("prob3.in", "r", stdin);
	freopen("prob3.out", "w", stdout);
#endif 
	run();
	return 0;
}