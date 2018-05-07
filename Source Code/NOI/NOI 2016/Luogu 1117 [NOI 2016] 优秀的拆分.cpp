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
#define loop register int
typedef long long LL;
typedef unsigned long long ULL;
using std::cin;
using std::cout;
using std::endl;
typedef LL INT_PUT;
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
	putchar('\n');
}

const int maxn = 30005;
int n;
char str[maxn];

#define RunInstance(x) delete new x
struct brute
{
	ULL hashVal[maxn];
	ULL power[maxn];
	brute()
	{
		power[0] = 1;
		for (loop i = 1; i <= n; i++)
			power[i] = power[i - 1] * 131;

		hashVal[0] = 0;
		for (loop i = 1; i <= n; i++)
			hashVal[i] = hashVal[i - 1] * 131 + str[i - 1];

		LL ans = 0;
		for (int i = 2; i <= n - 2; i++)
		{
			int cnt1 = 0, cnt2 = 0;
			for (int l = 1; i - (l << 1) >= 0; l++)
			{
				if (hashVal[i] - hashVal[i - l] * power[l] ==
					hashVal[i - l] - hashVal[i - (l << 1)] * power[l])
					cnt1++;
			}
			for (int l = 1; i + (l << 1) <= n; l++)
			{
				if (hashVal[i + l] - hashVal[i] * power[l] ==
					hashVal[i + (l << 1)] - hashVal[i + l] * power[l])
					cnt2++;
			}
			ans += cnt1 * cnt2;
		}
		printOut(ans);
	}
};
struct work
{
	struct SAHelper
	{
		int SA[maxn];
		int Rank[maxn];
		int Height[maxn];
		void GetSA()
		{
			static int buf[maxn];
			static int x[maxn], y[maxn];

			int buf_size = 26;
			int *rank = x, *SA_second = y;
			for (int i = 0; i < n; i++)
				rank[i] = str[i] - 'a';

			for (int i = 0; i < buf_size; i++) buf[i] = 0;
			for (int i = 0; i < n; i++) buf[rank[i]]++;
			for (int i = 1; i < buf_size; i++) buf[i] += buf[i - 1];
			for (int i = n - 1; ~i; i--) SA[--buf[rank[i]]] = i;

			for (int k = 1; k <= n; k <<= 1)
			{
				int t = 0;
				for (int i = n - k; i < n; i++)
					SA_second[t++] = i;
				for (int i = 0; i < n; i++)
					if (SA[i] >= k) SA_second[t++] = SA[i] - k;

				for (int i = 0; i < buf_size; i++) buf[i] = 0;
				for (int i = 0; i < n; i++) buf[rank[SA_second[i]]]++;
				for (int i = 1; i < buf_size; i++) buf[i] += buf[i - 1];
				for (int i = n - 1; ~i; i--) SA[--buf[rank[SA_second[i]]]] = SA_second[i];

				int* oldRank = rank;
				std::swap(rank, SA_second);
				rank[SA[0]] = 0;
				t = 1;
				for (int i = 1; i < n; i++)
					rank[SA[i]] = (oldRank[SA[i]] == oldRank[SA[i - 1]] &&
						SA[i] + k < n && SA[i - 1] + k < n &&
						oldRank[SA[i] + k] == oldRank[SA[i - 1] + k])
					? t - 1 : t++;
				if (t >= n) break;
				buf_size = t;
			}
		}
		void GetHeight()
		{
			for (int i = 0; i < n; i++)
				Rank[SA[i]] = i;

			int same = 0;
			for (int i = 0; i < n; i++)
			{
				if (same) same--;
				if (Rank[i])
				{
					int pre = SA[Rank[i] - 1];
					while (i + same < n && pre + same < n &&
						str[i + same] == str[pre + same])
						same++;
				}
				else
					same = 0;
				Height[Rank[i]] = same;
			}
		}

		int k;
		int minVal[16][maxn];
		int Log[maxn];
		void init()
		{
			for (int i = 0; i < n; i++)
				minVal[0][i] = Height[i];
			k = 0;
			while (1 << (k + 1) < n) k++;
			for (int i = 1; i <= k; i++)
				for (int j = 0; j + (1 << i) - 1 < n; j++)
					minVal[i][j] = std::min(minVal[i - 1][j],
						minVal[i - 1][j + (1 << (i - 1))]);

			for (register int i = 0; i <= n; i++)
			{
				register int t = 0;
				while (1 << (t + 1) < i) t++;
				Log[i] = t;
			}
		}
		int LCP(int a, int b)
		{
			if (a == b) return n - a;
			a = Rank[a];
			b = Rank[b];
			if (a > b) std::swap(a, b);
			a++;
			register int length = b - a + 1;
			register int t = Log[length];
			return std::min(minVal[t][a], minVal[t][b - (1 << t) + 1]);
		}
	} sa1, sa2;

	int Left[maxn], Right[maxn];

	work() : Left(), Right()
	{
		sa1.GetSA();
		sa1.GetHeight();
		sa1.init();
		std::reverse(str, str + n);
		sa2.GetSA();
		sa2.GetHeight();
		sa2.init();

		for (int l = 1; l <= (n >> 1); l++)
		{
			for (int i = 0, j = l; j < n; i += l, j += l)
			{
				int Forward = std::min(sa1.LCP(i, j), l);
				int Backward = std::min(sa2.LCP(n - 1 - i, n - 1 - j), l);
				int len = Forward + Backward - l - 1;
				if (len >= 0)
				{
					Left[j + Forward - 1 - len]++;
					Left[j + Forward]--;
					Right[i - Backward + 1]++;
					Right[i - Backward + 1 + len + 1]--;
				}
			}
		}
		for (int i = 1; i < n; i++)
			Left[i] += Left[i - 1];
		for (int i = 1; i < n; i++)
			Right[i] += Right[i - 1];
		LL ans = 0;
		for (int i = 1; i < n - 2; i++)
			ans += (LL)Left[i] * Right[i + 1];
		printOut(ans);
	}
};

void run()
{
	int T = readIn();
	while (T--)
	{
		scanf("%s", str);
		n = strlen(str);
		RunInstance(work);
	}
}

int main()
{
	run();
	return 0;
}