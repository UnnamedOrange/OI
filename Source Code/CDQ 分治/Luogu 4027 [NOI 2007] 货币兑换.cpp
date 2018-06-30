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

const int maxn = int(1e5) + 5;
int n, s;
double a[maxn], b[maxn], rate[maxn];

#define RunInstance(x) delete new x
struct brute
{
	static const int maxN = 1005;
	double f[maxN];

	double DP(int i, int j)
	{
		double y = f[j] / (rate[j] * a[j] + b[j]);
		double x = rate[j] * y;
		return a[i] * x + b[i] * y;
	}

	brute() : f()
	{
		f[1] = s;
		for (int i = 2; i <= n; i++)
		{
			double& ans = f[i];
			ans = f[i - 1];
			for (int j = 1; j < i; j++)
				ans = std::max(ans, DP(i, j));
		}
		printf("%.3f", f[n]);
	}
};
struct CDQ
{
	long double f[maxn];
	inline long double T(int j) { return f[j] / (a[j] * rate[j] + b[j]); }

	int temp[maxn];
	int stack[maxn];

	static inline int dcmp(long double x)
	{
		const long double EPS = 1e-7;
		if (std::abs(x) <= EPS)
			return 0;
		return x < 0 ? -1 : 1;
	}
	long double slope(int x, int y)
	{
		return (T(x) * rate[x] - T(y) * rate[y]) / (T(x) - T(y));
	}
	long double DP(int i, int j)
	{
		double y = f[j] / (rate[j] * a[j] + b[j]);
		double x = rate[j] * y;
		return a[i] * x + b[i] * y;
	}

	void cdq(int l, int r)
	{
		if (l == r)
		{
			f[l] = std::max(f[l], f[l - 1]);
			return;
		}
		int mid = (l + r) >> 1;
		cdq(l, mid);

		for (int i = l; i <= mid; i++)
			temp[i] = i;
		std::sort(temp + l, temp + mid + 1,
			[&](const int& x, const int& y)
		{
			return T(x) < T(y);
		});
		stack[0] = 0;
		for (int i = l; i <= mid; i++)
		{
			while (stack[0] > 1 && dcmp(slope(temp[i], stack[stack[0]]) - slope(stack[stack[0]], stack[stack[0] - 1])) > 0)
				stack[0]--;
			stack[++stack[0]] = temp[i];
		}

		for (int i = mid + 1; i <= r; i++)
			temp[i] = i;
		std::sort(temp + mid + 1, temp + r + 1,
			[&](const int& x, const int& y)
		{
			return dcmp((-b[x] / a[x]) - (-b[y] / a[y])) > 0;
		});
		int cnt = 1;
		for (int i = mid + 1; i <= r; i++)
		{
			while (cnt < stack[0] && dcmp(slope(stack[cnt + 1], stack[cnt]) - (-b[temp[i]] / a[temp[i]])) > 0)
				cnt++;
			f[temp[i]] = std::max(f[temp[i]], DP(temp[i], stack[cnt]));
		}

		cdq(mid + 1, r);
	}

	CDQ() : f()
	{
		f[0] = s;
		cdq(1, n);
		printf("%.3Lf", f[n]);
	}
};
struct CDQopt
{
	long double f[maxn];
	inline long double T(int j) { return f[j] / (a[j] * rate[j] + b[j]); }

	int temp[maxn];
	int stack[maxn];

	static inline int dcmp(long double x)
	{
		const long double EPS = 1e-7;
		if (std::abs(x) <= EPS)
			return 0;
		return x < 0 ? -1 : 1;
	}
	long double slope(int x, int y)
	{
		return (T(x) * rate[x] - T(y) * rate[y]) / (T(x) - T(y));
	}
	long double DP(int i, int j)
	{
		double y = f[j] / (rate[j] * a[j] + b[j]);
		double x = rate[j] * y;
		return a[i] * x + b[i] * y;
	}

	int idx[maxn]; // 横坐标排序序号
	int sort[18][maxn]; // 不等式右侧排序序号
	void mergesort(int l, int r, int depth)
	{
		if (l == r)
		{
			sort[depth][l] = l;
			return;
		}
		int mid = (l + r) >> 1;
		mergesort(l, mid, depth + 1);
		mergesort(mid + 1, r, depth + 1);
		int i = l;
		int j = mid + 1;
		int k = l;
		while (k <= r)
		{
			int x = sort[depth + 1][i];
			int y = sort[depth + 1][j];
			if (j > r || (i <= mid && dcmp((-b[x] / a[x]) - (-b[y] / a[y])) >= 0))
				sort[depth][k++] = sort[depth + 1][i++];
			else
				sort[depth][k++] = sort[depth + 1][j++];
		}
	}

	void cdq(int l, int r, int depth)
	{
		if (l == r)
		{
			f[l] = std::max(f[l], f[l - 1]);
			return;
		}
		int mid = (l + r) >> 1;
		cdq(l, mid, depth + 1);

		stack[0] = 0;
		for (int i = l; i <= mid; i++)
		{
			while (stack[0] > 1 && dcmp(slope(idx[i], stack[stack[0]]) - slope(stack[stack[0]], stack[stack[0] - 1])) > 0)
				stack[0]--;
			stack[++stack[0]] = idx[i];
		}

		int cnt = 1;
		for (int i = mid + 1; i <= r; i++)
		{
			while (cnt < stack[0] && dcmp(slope(stack[cnt + 1], stack[cnt]) - (-b[sort[depth + 1][i]] / a[sort[depth + 1][i]])) > 0) // note：是 depth + 1
				cnt++;
			f[sort[depth + 1][i]] = std::max(f[sort[depth + 1][i]], DP(sort[depth + 1][i], stack[cnt]));
		}

		cdq(mid + 1, r, depth + 1);

		int i = l;
		int j = mid + 1;
		int k = l;
		while (k <= r)
		{
			if (j > r || (i <= mid && dcmp(T(idx[i]) - T(idx[j])) <= 0))
				temp[k++] = idx[i++];
			else
				temp[k++] = idx[j++];
		}
		for (i = l; i <= r; i++)
			idx[i] = temp[i];
	}

	CDQopt() : f()
	{
		for (int i = 1; i <= n; i++)
			idx[i] = i;
		mergesort(1, n, 0);

		f[0] = s; // note：只是为了方便
		cdq(1, n, 0);
		printf("%.3Lf", f[n]);
	}
};

void run()
{
	n = readIn();
	s = readIn();
	for (int i = 1; i <= n; i++)
		scanf("%lf%lf%lf", a + i, b + i, rate + i);

	RunInstance(CDQopt);
}

int main()
{
	run();
	return 0;
}