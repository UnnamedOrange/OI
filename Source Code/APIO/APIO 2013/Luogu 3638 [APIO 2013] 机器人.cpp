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
const int maxn = 505;
int n, w, h;
int rect[maxn][maxn];
typedef std::pair<int, int> Point;
Point pos[10];

enum { RIGHT, UP, LEFT, DOWN };
const int vecx[] = { 0, -1, 0, 1 };
const int vecy[] = { 1, 0, -1, 0 };
Point to[maxn][maxn][4];

int vis[maxn][maxn][4];
int stamp;
void DFS(int x, int y, int dir)
{
	if (to[x][y][dir].first)
		return;
	vis[x][y][dir] = stamp;
	int newz = dir;
	if (rect[x][y] == -2)
		newz = (newz + 1) & 3;
	else if (rect[x][y] == -3)
		newz = (newz + 4 - 1) & 3;
	int newx = x + vecx[newz];
	int newy = y + vecy[newz];
	if (!(1 <= newx && newx <= h && 1 <= newy && newy <= w) || rect[newx][newy] == -1)
	{
		to[x][y][dir] = std::make_pair(x, y);
		return;
	}
	else if (vis[newx][newy][newz] == stamp)
	{
		to[x][y][dir] = std::make_pair(-1, -1);
		return;
	}
	DFS(newx, newy, newz);
	to[x][y][dir] = to[newx][newy][newz];
}
void init()
{
	for (loop x = 1; x <= h; x++)
		for (loop y = 1; y <= w; y++)
			for (loop i = 0; i < 4; i++)
			{
				stamp++;
				DFS(x, y, i);
			}
}

int f[10][10][maxn][maxn];
struct Queue
{
	Point c[maxn * maxn];
	int head, tail;
	Queue() { clear(); }
	void clear() { head = tail = 0; }
	void push(const Point& x) { c[tail++] = x; }
	void pop() { head++; }
	Point front() { return c[head]; }
	int val(int l, int r) { return f[l][r][c[head].first][c[head].second]; }
	bool empty() { return head == tail; }
	void sort(int l, int r)
	{
		std::sort(c + head, c + tail,
			[=](const Point& a, const Point& b)
		{
			return f[l][r][a.first][a.second] < f[l][r][b.first][b.second];
		});
	}
} q1, q2;
bool inQ[maxn * maxn];
void SPFA(int l, int r)
{
	q1.clear();
	q2.clear();
	for (loop x = 1; x <= h; x++)
		for (loop y = 1; y <= w; y++)
			if (f[l][r][x][y] < INF)
			{
				q1.push(std::make_pair(x, y));
				inQ[x * w + y] = true;
			}
	q1.sort(l, r);

	while (!(q1.empty() && q2.empty()))
	{
		Point from;
		if (q2.empty() || (!q1.empty() && q1.val(l, r) <= q2.val(l, r)))
		{
			from = q1.front();
			q1.pop();
		}
		else
		{
			from = q2.front();
			q2.pop();
		}
		inQ[from.first * w + from.second] = false;

		for (int i = 0; i < 4; i++)
		{
			const Point& t = to[from.first][from.second][i];
			if (t.first == -1) continue;
			int update = f[l][r][from.first][from.second] + 1;
			int& ans = f[l][r][t.first][t.second];
			if (update < ans)
			{
				ans = update;
				if (!inQ[t.first * w + t.second])
				{
					q2.push(std::make_pair(t.first, t.second));
					inQ[t.first * w + t.second] = true;
				}
			}
		}
	}
}
void solve()
{
	memset(f, 0x3f, sizeof(f));
	for (int i = 1; i <= n; i++)
		f[i][i][pos[i].first][pos[i].second] = 0;

	for (int len = 1; len <= n; len++)
	{
		for (int l = 1, r = l + len - 1; r <= n; l++, r++)
		{
			if (len > 1)
				for (loop x = 1; x <= h; x++)
					for (loop y = 1; y <= w; y++)
						for (loop i = l; i < r; i++)
							f[l][r][x][y] = std::min(f[l][r][x][y], f[l][i][x][y] + f[i + 1][r][x][y]);

			SPFA(l, r);
		}
	}

	int ans = INF;
	for (int i = 1; i <= h; i++)
		for (int j = 1; j <= w; j++)
			ans = std::min(ans, f[1][n][i][j]);
	if (ans >= INF)
		printOut(-1);
	else
		printOut(ans);
}

void run()
{
	memset(&INF, 0x3f, sizeof(INF));
	n = readIn();
	w = readIn();
	h = readIn();
	for (int x = 1; x <= h; x++)
	{
		for (int y = 1; y <= w; y++)
		{
			char ch = getchar();
			while (!(std::isdigit(ch) || ch == '.' ||
				ch == 'x' || ch == 'A' || ch == 'C'))
				ch = getchar();
			switch (ch)
			{
			case 'x': rect[x][y] = -1; break;
			case 'A': rect[x][y] = -2; break;
			case 'C': rect[x][y] = -3; break;
			case '.': break;
			default: pos[ch - '0'] = std::make_pair(x, y);
			}
		}
	}

	init();
	solve();
}

int main()
{
	run();
	return 0;
}