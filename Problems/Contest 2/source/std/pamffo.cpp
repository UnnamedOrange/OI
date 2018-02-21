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
#include <list>
typedef int INT;
using std::cin;
using std::cout;
using std::endl;
INT readIn()
{
	INT a = 0;
	bool minus = false;
	char ch = getchar();
	while (!(ch == '-' || (ch >= '0' && ch <= '9'))) ch = getchar();
	if (ch == '-')
	{
		minus = true;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
	{
		a = a * 10 + (ch - '0');
		ch = getchar();
	}
	if (minus) a = -a;
	return a;
}
void printOut(INT x)
{
	char buffer[20];
	INT length = 0;
	if (x < 0)
	{
		putchar('-');
		x = -x;
	}
	do
	{
		buffer[length++] = x % 10 + '0';
		x /= 10;
	} while (x);
	do
	{
		putchar(buffer[--length]);
	} while (length);
}

const int maxn = INT(1e5) + 5;
int n;

struct Event
{
	int type;
	int people;
	int time;
	int ans;
} events[maxn];
std::map<std::string, int> mapSI;
inline int code(const char* str)
{
	if (!mapSI.count(str))
		return mapSI[str] = mapSI.size();
	return mapSI[str];
}

int idx[maxn];
bool comp(const int& a, const int& b)
{
	if (events[a].time != events[b].time)
		return events[a].time < events[b].time;
	return events[a].type < events[b].type;
}

int rec[maxn];

void run()
{
	n = readIn();
	for (int i = 1; i <= n; i++)
	{
		Event& e = events[i];
		e.type = readIn();
		char name[105];
		scanf("%s", name);
		e.people = code(name);
		e.time = readIn();

		if (e.type == 2)
			readIn();
	}

	for (int i = 1; i <= n; i++)
		idx[i] = i;
	std::sort(idx + 1, idx + 1 + n, comp);

	for (int i = 1; i <= n; i++)
	{
		Event& e = events[idx[i]];
		if (e.type == 1)
			rec[e.people]++;
		else if (e.type == 2)
			e.ans = rec[e.people];
	}

	for (int i = 1; i <= n; i++)
	{
		const Event& e = events[i];
		if (e.type == 2)
		{
			printOut(e.ans);
			putchar('\n');
		}
	}
}

int main()
{
#ifndef LOCAL
	freopen("pamffo.in", "r", stdin);
	freopen("pamffo.out", "w", stdout);
#endif
	run();
	return 0;
}