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
#include <array>
using LL = long long;
using ULL = unsigned long long;
using std::cin;
using std::cout;
using std::endl;
using INT_PUT = int;
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

const int maxn = 11;
int n, m, mod;

struct Status
{
	int val[maxn]{}; // 0 - 黑格子，x - 白格子及其连通性编号
	bool operator<(const Status& b) const
	{
		for (int i = 0; i < maxn; i++)
			if (val[i] != b.val[i])
				return val[i] < b.val[i];
		return false;
	}
	struct DS
	{
		int parent[maxn * 2 + 3];
		void clear()
		{
			for (int i = 0; i < ((n + 1) << 1); i++)
				parent[i] = i;
		}
		int find(int x)
		{
			return x == parent[x] ? x : (parent[x] = find(parent[x]));
		}
		void unite(int x, int y)
		{
			parent[find(y)] = find(x);
		}
		bool judge(int x, int y)
		{
			return find(x) == find(y);
		}
	};
	bool makeTransfer(int S, Status& transTo)
	{
		// 相邻的不能是黑块
		for (int i = 1; i < n; i++)
			if (!(S & (1 << i)) && (!(S & (1 << (i - 1))) || !val[i]))
				return false;

		// 转移后上面的不能不连通
		bool appear[maxn]{};
		int maxBlock = 0;
		for (int i = 0; i < n; i++)
			maxBlock = std::max(maxBlock, val[i]);
		for (int i = 0; i < n; i++)
			if (S & (1 << i))
				appear[val[i]] = true;
		for (int i = 1; i <= maxBlock; i++)
			if (!appear[i])
				return false;

		// 根据上一行的连通信息为转移后的行标号
		static DS ds;
		ds.clear();
		int nBlock = 0;
		for (int i = 0; i < n; i++)
			if (S & (1 << i))
				transTo.val[i] = (i && transTo.val[i - 1]) ? transTo.val[i - 1] : ++nBlock;
			else
				transTo.val[i] = 0;
		for (int i = 0; i < n; i++)
			if (val[i] && transTo.val[i])
				ds.unite(transTo.val[i] + n, val[i]);

		for (int i = 0; i < n; i++)
			if (transTo.val[i])
				transTo.val[i] = ds.find(transTo.val[i] + n);
		int newIdx[maxn * 2 + 3]{};
		nBlock = 0;
		for (int i = 0; i < n; i++) if (transTo.val[i])
			if (newIdx[transTo.val[i]])
				transTo.val[i] = newIdx[transTo.val[i]];
			else
				transTo.val[i] = newIdx[transTo.val[i]] = ++nBlock;
		return true;
	}
};
std::map<Status, int> mapSI;
const int maxStatus = 3500;
Status status[maxStatus];
std::vector<int> transfer[maxStatus];
void search(int depth, int nBlock)
{
	static Status temp;
	if (depth >= n)
	{
		mapSI[temp] = mapSI.size() + 1;
		status[mapSI.size()] = temp;
	}
	else
	{
		for (int i = 0; i <= nBlock + 1; i++)
		{
			if (depth)
			{
				if (!i && !temp.val[depth - 1]) // 不能都是黑块
					continue;
				if (i && temp.val[depth - 1] && i != temp.val[depth - 1]) // 相邻白块标号必须一样
					continue;
			}
			temp.val[depth] = i;
			search(depth + 1, std::max(nBlock, i));
		}
	}
}
void initTransfer()
{
	int U = 1 << n;
	for (int i = 1; i <= mapSI.size(); i++)
		for (int S = 0; S < U; S++)
		{
			Status to;
			if (status[i].makeTransfer(S, to))
			{
				assert(mapSI.count(to));
				transfer[i].push_back(mapSI[to]);
			}
		}
}

void run()
{
	n = readIn();
	m = readIn();
	mod = readIn();

	search(0, 0);
	initTransfer();

	int count = 0;
	for (int i = 1; i <= mapSI.size(); i++)
		count += transfer[i].size();
	cout << count << endl;
}

int main()
{
#ifndef LOCAL
	freopen("matrix.in", "r", stdin);
	freopen("matrix.out", "w", stdout);
#endif
	run();
	return 0;
}