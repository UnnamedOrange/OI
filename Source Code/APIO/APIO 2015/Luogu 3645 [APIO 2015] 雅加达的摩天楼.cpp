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

int INF;
const int maxn = 30005;
int n, m;

#define RunInstance(x) delete new x
struct work
{
	static const int maxk = 90;
	int k;
	std::vector<std::vector<int> > appear;
	std::vector<std::vector<int> > fast;
	std::vector<std::vector<int> > slow;
	int pos[maxn];
	int val[maxn];

	static const int size = maxn * maxk;
	int dis[size];
	bool inQ[size];
	int q[size];
	int head, tail;

	void slack(int from, int to, int cost)
	{
		if (dis[from] + cost < dis[to])
		{
			dis[to] = dis[from] + cost;
			if (!inQ[to])
			{
				q[tail] = to;
				tail = tail + 1 == size ? 0 : tail + 1;
				inQ[to] = true;
			}
		}
	}

	void SPFA()
	{
		head = tail = 0;
		memset(dis, 0x3f, sizeof(dis));
		memset(inQ, 0, sizeof(inQ));
		dis[pos[0]] = 0;
		q[tail++] = pos[0];
		inQ[pos[0]] = true;
		while (head != tail)
		{
			int from = q[head];
			inQ[from] = false;
			head = head + 1 == size ? 0 : head + 1;
			if (from >= n)
			{
				int way = from / n;
				int idx = from - way * n;
				int to;
				if (idx - way >= 0)
					slack(from, from - way, 1);
				if (idx + way < n)
					slack(from, from + way, 1);
				slack(from, idx, 0);
			}
			else
			{
				for (int i = 0; i < fast[from].size(); i++)
					slack(from, from + n * fast[from][i], 0);
				for (int i = 0; i < slow[from].size(); i++)
				{
					register int cnt;
					register int step = slow[from][i];
					register int cost;
					cnt = from - step;
					cost = 1;
					while (cnt >= 0)
					{
						slack(from, cnt, cost);
						cnt -= step;
						cost++;
					}
					cnt = from + step;
					cost = 1;
					while (cnt < n)
					{
						slack(from, cnt, cost);
						cnt += step;
						cost++;
					}
				}
			}
		}
	}

	work() : dis(), inQ()
	{
		k = std::sqrt(m / 4);
		appear.resize(n);
		fast.resize(n);
		slow.resize(n);
		for (int i = 0; i < m; i++)
		{
			pos[i] = readIn();
			val[i] = readIn();
			appear[pos[i]].push_back(i);
			if (val[i] <= k) fast[pos[i]].push_back(val[i]);
			else slow[pos[i]].push_back(val[i]);
		}
		for (int i = 0; i < n; i++)
		{
			std::sort(fast[i].begin(), fast[i].end());
			fast[i].resize(std::unique(fast[i].begin(), fast[i].end()) - fast[i].begin());
			std::sort(slow[i].begin(), slow[i].end());
			slow[i].resize(std::unique(slow[i].begin(), slow[i].end()) - slow[i].begin());
		}

		SPFA();
		if (dis[pos[1]] >= INF)
			printOut(-1);
		else
			printOut(dis[pos[1]]);
	}
};

void run()
{
	memset(&INF, 0x3f, sizeof(INF));
	n = readIn();
	m = readIn();
	RunInstance(work);
}

int main()
{
	run();
	return 0;
}