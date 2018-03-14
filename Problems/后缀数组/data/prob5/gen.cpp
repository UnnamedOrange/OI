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

const int buffer_size = 8192;
char buffer[buffer_size];
const char name[] = "prob5";
int g_idx;
LL rand(LL from, LL to)
{
#define r(x) ((LL)rand() << x)
	LL ret = r(45) | r(30) | r(15) | r(0);
#undef r
	return from + ret % (to - from + 1);
}
struct CaseBase
{
	CaseBase()
	{
		g_idx++;
		sprintf(buffer, "%s%d.in", name, g_idx);
		freopen(buffer, "w", stdout);

		srand(time(NULL) + clock());
	}
	~CaseBase()
	{
		fclose(stdout);

		sprintf(buffer, "%s.exe < %s%d.in > %s%d.ans", name, name, g_idx, name, g_idx);
		system(buffer);
	}
};
#define GoCase(x, t, ...) for (int o = 0; o < t; o++) x(__VA_ARGS__)

const int maxn = int(1e6);
struct case1 : private CaseBase
{
	int n;
	char str[maxn * 2];

	case1(int limit = 1000)
	{
		n = rand(limit - 100, limit);
		for (int i = 0; i < 26; i++)
			str[i] = 'a' + i;
		std::random_shuffle(str, str + 26);
		for (int i = 26; i < n;)
		{
			int l = rand(0, i - 1);
			int r = rand(l, i - 1);
			memcpy(str + i, str + l, sizeof(char) * (r - l + 1));
			i += r - l + 1;
		}
		for (int i = 0; i < n; i++)
			putchar(str[i]);
		putchar('\n');
		printOut(g_idx == 1 ? 1 : rand(1, n / 50));
	}
};

void run()
{
	GoCase(case1, 6);
	GoCase(case1, 14, int(2e5));
}

int main()
{
	run();
	return 0;
}