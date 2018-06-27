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
	register INT_PUT a = 0;
	register bool positive = true;
	register char ch = getchar();
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
	register int length = 0;
	if (x < 0) putchar('-');
	else x = -x;
	do buffer[length++] = -(x % 10) + '0'; while (x /= 10);
	do putchar(buffer[--length]); while (length);
	putchar('\n');
}

const int maxn = int(2e5) + 5;
int n, q;
char str[maxn];
struct Query
{
	int l, r;
	void read()
	{
		l = readIn();
		r = readIn();
	}
} querys[maxn];

#define RunInstance(x) delete new x
struct brute
{
	int idx[maxn];
	int ans[maxn];
	int f[maxn];

	void initFailure(const char* s, int n)
	{
		f[0] = f[1] = 0;
		int pre = 0;
		for (int i = 1; i < n; i++)
		{
			while (pre && s[i] != s[pre]) pre = f[pre];
			if (s[i] == s[pre]) pre++;
			f[i + 1] = pre;
		}
	}

	brute()
	{
		for (int i = 1; i <= q; i++)
			idx[i] = i;
		std::sort(idx + 1, idx + 1 + q,
			[](const int& a, const int& b)
		{
			return querys[a].l < querys[b].l;
		});

		int cnt = 0;
		for (int i = 1; i <= q; i++)
		{
			const Query& Q = querys[idx[i]];
			if (cnt != Q.l)
			{
				initFailure(str + Q.l, n - Q.l + 1);
				cnt = Q.l;
			}
			ans[idx[i]] = f[Q.r - Q.l + 1];
		}

		for (int i = 1; i <= q; i++)
			printOut(ans[i]);
	}
};
struct work
{
	static const int sqrtN = 512;
	int N;
	int inBlock[maxn];
	int lBegin[maxn]{};
	int rEnd[maxn];
	void initBlocks()
	{
		N = (n - 1) / sqrtN + 1;
		for (int i = 1; i <= n; i++)
		{
			int ib = inBlock[i] = (i - 1) / sqrtN;
			if (!lBegin[ib])
				lBegin[ib] = i;
			rEnd[ib] = i;
		}
	}
	ULL power[maxn];
	ULL hashVal[maxn];
	void initHash()
	{
		power[0] = 1;
		for (int i = 1; i <= n; i++)
			power[i] = power[i - 1] * 131;
		hashVal[0] = 0;
		for (int i = 1; i <= n; i++)
			hashVal[i] = hashVal[i - 1] * 131 + str[i];
	}
	bool comp(int l1, int r1, int l2, int r2)
	{
		return hashVal[r1] - power[r1 - l1 + 1] * hashVal[l1 - 1] ==
			hashVal[r2] - power[r2 - l2 + 1] * hashVal[l2 - 1];
	}
	std::vector<std::vector<int>> offlineQuery;

	int ans[maxn]{};
	int LCP[maxn];
	int next[maxn];
	int LCS[maxn];

	std::vector<std::vector<int>> offlineLeft;
	struct TIB // note：变形的 BIT，求后缀最小值
	{
		int c[maxn];
		TIB()
		{
			for (int i = 0; i < maxn; i++)
				c[i] = INT_MAX;
		}
		static inline int lowbit(int x) { return x & -x; }
		void modify(int pos, int val)
		{
			while (pos)
			{
				c[pos] = std::min(c[pos], val);
				pos ^= lowbit(pos);
			}
		}
		int query(int pos)
		{
			int ret = INT_MAX;
			while (pos <= n)
			{
				ret = std::min(ret, c[pos]);
				pos += lowbit(pos);
			}
			return ret;
		}
		void clear()
		{
			for (int i = 0; i < maxn; i++)
				c[i] = INT_MAX;
		}
	} bit;

	work()
	{
		initBlocks();
		initHash();
		offlineQuery.resize(n + 1);
		for (int i = 1; i <= q; i++)
			offlineQuery[querys[i].l].push_back(i);
		for (int i = 1; i <= q; i++)
		{
			const Query& Q = querys[i];
			for (int j = 1, to = std::min(rEnd[inBlock[Q.l]] - Q.l + 1, Q.r - Q.l); j <= to; j++)
				if (comp(Q.l, Q.l + j - 1, Q.r - j + 1, Q.r))
					ans[i] = j;
		}

		for (int i = 0; i < N - 1; i++)
		{
			int begin, length;
			begin = lBegin[i + 1];
			length = n - rEnd[i];
			LCP[0] = length;
			LCP[1] = 0;
			while (begin + 1 + LCP[1] <= n && str[begin + LCP[1]] == str[begin + 1 + LCP[1]])
				LCP[1]++;
			int pos = 1;
			for (int j = 2; j < length; j++)
			{
				if (pos + LCP[pos] > j + LCP[j - pos])
					LCP[j] = LCP[j - pos];
				else
				{
					LCP[j] = std::max(0, pos + LCP[pos] - j);
					while (begin + j + LCP[j] <= n && str[begin + LCP[j]] == str[begin + j + LCP[j]])
						LCP[j]++;
					pos = j;
				}
			}

			begin = rEnd[i];
			length = rEnd[i] - lBegin[i] + 1;
			next[0] = length;
			next[1] = 0;
			while (begin - 1 - next[1] >= lBegin[i] && str[begin - next[1]] == str[begin - 1 - next[1]])
				next[1]++;
			pos = 1;
			for (int j = 2; j < length; j++)
			{
				if (pos + next[pos] > j + next[j - pos])
					next[j] = next[j - pos];
				else
				{
					next[j] = std::max(0, pos + next[pos] - j);
					while (begin - j - next[j] >= lBegin[i] && str[begin - next[j]] == str[begin - j - next[j]])
						next[j]++;
					pos = j;
				}
			}

			LCS[0] = 0;
			while (begin - LCS[0] >= lBegin[i] && n - LCS[0] > 0 && str[n - LCS[0]] == str[begin - LCS[0]])
				LCS[0]++;
			pos = 0;
			for (int j = 1; j < n; j++)
			{
				if (j - pos < rEnd[i] - lBegin[i] + 1 && pos + LCS[pos] > j + next[j - pos]) // note：必须写前句
					LCS[j] = next[j - pos];
				else
				{
					LCS[j] = std::max(0, pos + LCS[pos] - j);
					while (begin - LCS[j] >= lBegin[i] && n - j - LCS[j] > 0 && str[n - j - LCS[j]] == str[begin - LCS[j]])
						LCS[j]++;
					pos = j;
				}
			}

			offlineLeft.clear();
			offlineLeft.resize(rEnd[i] - lBegin[i] + 2);
			length = n - rEnd[i];
			for (int j = 0; j < length; j++)
				offlineLeft[LCS[j]].push_back(n - j);
			bit.clear();
			LCP[n - lBegin[i + 1] + 1] = 0; // note：边界情况
			for (int j = rEnd[i] - lBegin[i] + 1; j; j--)
			{
				for (auto k : offlineLeft[j])
					bit.modify(k + LCP[k - lBegin[i + 1] + 1], k);

				for (auto k : offlineQuery[lBegin[i + 1] - j])
					ans[k] = std::max(ans[k], querys[k].r - (bit.query(querys[k].r) - j));
			}
		}
		for (int i = 1; i <= q; i++)
			printOut(ans[i]);
	}
};

void run()
{
	n = readIn();
	q = readIn();
	for (int i = 1; i <= n; i++)
	{
		register char ch = getchar();
		while (!std::isalpha(ch)) ch = getchar();
		str[i] = ch;
	}
	for (int i = 1; i <= q; i++)
		querys[i].read();

	RunInstance(work);
}

int main()
{
#ifndef LOCAL
	freopen("str.in", "r", stdin);
	freopen("str.out", "w", stdout);
#endif
	run();
	return 0;
}