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
			if (!(S & (1 << i)) && !(S & (1 << (i - 1))))
				return false;
		for (int i = 0; i < n; i++)
			if (!(S & (1 << i)) && !val[i])
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

		// 以连续的一块为单位进行操作
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
	int bEnd{ -1 };
	bool isEnd()
	{
		if (~bEnd) return bEnd;
		return bEnd = (*std::max_element(val, val + n) == 1);
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
		int t = mapSI.size() + 1;
		mapSI[temp] = t;
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
				transfer[i].push_back(mapSI[to]);
		}
}

#define RunInstance(x) delete new x
struct brute
{
	struct Matrix
	{
		static const int maxsize = 260; // n = 8 时，有 259 种状态
		int size;
		int c[maxsize][maxsize];
		int* operator[](int x) { return c[x]; }
		const int* operator[](int x) const { return c[x]; }
		explicit Matrix(int size) : size(size), c() {}
		Matrix(int size, bool) : Matrix(size)
		{
			for (int i = 1; i <= size; i++)
				c[i][i] = 1;
		}
		Matrix operator*(const Matrix& b) const
		{
			register int t = size;
			Matrix ret(t);
			for (int i = 1; i <= t; i++)
				for (int k = 1; k <= t; k++) if (c[i][k])
					for (int j = 1; j <= t; j++)
						ret[i][j] = (ret[i][j] + (LL)c[i][k] * b[k][j]) % mod;
			return ret;
		}
		Matrix operator^(int y) const
		{
			Matrix ret(size, true);
			Matrix x(*this);
			while (y)
			{
				if (y & 1) ret = ret * x;
				x = x * x;
				y >>= 1;
			}
			return ret;
		}
	};
	Matrix base;

	brute() : base(mapSI.size())
	{
		for (int i = 1; i <= mapSI.size(); i++)
			for (int j = 0; j < transfer[i].size(); j++)
				base[i][transfer[i][j]]++;
		for (int i = 1; i <= base.size; i++)
			for (int j = 1; j <= base.size; j++)
				base[i][j] %= mod;

		int ans = 0;
		base = base ^ (m - 1);
		int U = 1 << n;
		for (int S = 0; S < U; S++)
		{
			bool bOk = true;
			for (int i = 1; i < n; i++)
				if (!(S & (1 << i)) && !(S & (1 << (i - 1))))
				{
					bOk = false;
					break;
				}
			if (!bOk) continue;
			Status start;
			int nBlock = 0;
			for (int i = 0; i < n; i++)
				if (S & (1 << i))
					start.val[i] = (i && start.val[i - 1]) ? start.val[i - 1] : ++nBlock;
				else
					start.val[i] = 0;

			int id = mapSI[start];
			for (int i = 1; i <= mapSI.size(); i++)
				if (status[i].isEnd())
					ans = (ans + base[id][i]) % mod;
		}
		printOut(ans);
	}
};

void run()
{
	n = readIn();
	m = readIn();
	mod = readIn();

	search(0, 0);
	initTransfer();

	if (n <= 8)
		RunInstance(brute);
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