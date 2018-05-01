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
}

const int maxn = int(1e5) + 5;
int n, k;
int a[maxn];
LL f[205][maxn];
struct Deque
{
	int c[maxn];
	int head, tail;
	void clear() { head = tail = 0; }
	int size() { return tail - head; }
	void push(int x) { c[tail++] = x; }
	void pop_front() { head++; }
	void pop_back() { tail--; }
	int front() { return c[head]; }
	int front2() { return c[head + 1]; }
	int back() { return c[tail - 1]; }
	int back2() { return c[tail - 2]; }
} dq;

inline LL calcY(int i, int s) { return f[i][s] - (LL)a[s] * a[s]; }
inline LL deltaY(int i, int s, int t) { return calcY(i, s) - calcY(i, t); }
inline double slope(int i, int s, int t) { if (a[s] == a[t]) return 1e18; return (double)deltaY(i, s, t) / (a[s] - a[t]); }
inline LL calc(int i, int j, int s)
{
	return f[i][s] + (LL)a[s] * (a[j] - a[s]);
}

int pre[205][maxn];
void run()
{
	n = readIn();
	k = readIn();
	for (loop i = 1; i <= n; i++)
		a[i] = readIn();
	for (loop i = 2; i <= n; i++)
		a[i] += a[i - 1];

	k++;
	for (loop i = 2; i <= k; i++) // note
	{
		dq.clear();
		dq.push(i - 1); // note
		for (loop j = i; j <= n; j++)
		{
			while (dq.size() > 1 && slope(i - 1, dq.front2(), dq.front()) > -a[j])
				dq.pop_front();
			f[i][j] = calc(i - 1, j, dq.front());
			pre[i][j] = dq.front();

			while (dq.size() > 1 && slope(i - 1, j, dq.back()) > slope(i - 1, dq.back(), dq.back2()))
				dq.pop_back();
			dq.push(j);
		}
	}
	printOut(f[k][n]);
	putchar('\n');
	std::vector<int> ans;
	int cnt = n;
	int t = k;
	for (int i = k; i; cnt = pre[i][cnt], i--)
		ans.push_back(pre[i][cnt]);
	for (int i = ans.size() - 2; ~i; i--)
	{
		printOut(ans[i]);
		putchar(' ');
	}
}

int main()
{
	run();
	return 0;
}