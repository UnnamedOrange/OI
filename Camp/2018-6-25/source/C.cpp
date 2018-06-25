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
using INT_PUT = LL;
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

#ifdef LOCAL
#define DebugPrint(x, ...) printf("Debug: " x "\n", __VA_ARGS__) 
#else
#define DebugPrint(...)
#endif

const int maxn = int(1e5) + 5;
int n;
int a[maxn];
int Div, Mod;

#define RunInstance(x) delete new x
struct brute
{
	std::map<std::vector<int>, int> map;
	int search(std::vector<int> vec)
	{
		if (map.count(vec))
			return map[vec];
		bool bOk = true;
		int& ret = map[vec];
		ret = 0;
		for (int i = 0; i < vec.size() - 1; i++)
		{
			int idx;
			for (idx = i + 1; idx < vec.size(); idx++)
				if (vec[idx] - vec[i] > 1)
					break;
			if (idx < vec.size())
			{
				bOk = false;
				std::vector<int> next(vec);
				next[i]++;
				next[idx]--;
				std::sort(next.begin(), next.end());
				ret = std::max(ret, search(next));
			}
		}
		if (bOk)
			return ret = 0;
		return ret = ret + 1;
	}

	brute()
	{
		printOut(search(std::vector<int>(a + 1, a + 1 + n)));
	}
};

void run()
{
	n = readIn();
	for (int i = 1; i <= n; i++)
		a[i] = readIn();
	std::sort(a + 1, a + 1 + n);
	LL sum = 0;
	for (int i = 1; i <= n; i++)
		sum += a[i];
	Div = sum / n;
	Mod = sum - (LL)Div * n;

	if (n <= 10)
		RunInstance(brute);
}

int main()
{
	run();
	return 0;
}