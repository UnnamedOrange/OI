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
typedef int INT;
using std::cin;
using std::cout;
using std::endl;
inline INT readIn()
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
inline void printOut(INT x)
{
	char buffer[20];
	INT length = 0;
	bool minus = x < 0;
	if (minus) x = -x;
	do
	{
		buffer[length++] = x % 10 + '0';
		x /= 10;
	} while (x);
	if (minus) buffer[length++] = '-';
	do
	{
		putchar(buffer[--length]);
	} while (length);
	putchar('\n');
}

const INT INF = 0x3f3f3f3f;
const INT maxn = 35;
INT n, m, q;
INT rect[maxn][maxn];
INT ex, ey, sx, sy, tx, ty;

const INT vecx[] = { 0, -1, 0, 1 };
const INT vecy[] = { 1, 0, -1, 0 };
const INT veco[] = { 2, 3, 0, 1 };
struct Node
{
	INT x, y, length;
	Node() {}
	Node(INT x, INT y, INT length) : x(x), y(y), length(length) {}
};
INT dis[maxn][maxn];
void BFS()
{
	memset(dis, 0x3f, sizeof(dis));
	std::queue<Node> q;
	q.push(Node(ex, ey, 0));
	dis[ex][ey] = 0;
	while (!q.empty())
	{
		Node from = q.front();
		q.pop();
		for (int i = 0; i < 4; i++)
		{
			INT newx = from.x + vecx[i];
			INT newy = from.y + vecy[i];
			if (newx == sx && newy == sy) continue;
			if (newx > 0 && newx <= n && newy > 0 && newy <= m && rect[newx][newy] && dis[newx][newy] >= INF)
			{
				INT newz = from.length + 1;
				dis[newx][newy] = newz;
				q.push(Node(newx, newy, newz));
			}
		}
	}
}
INT cost[maxn][maxn][4][4];

struct SNode
{
	INT x, y, dir;
	SNode() {}
	SNode(INT x, INT y, INT dir) : x(x), y(y), dir(dir) {}
};
INT Sdis[maxn][maxn][4];
bool inq[maxn][maxn][4];
INT SPFA(INT x, INT y, INT z)
{
	memset(Sdis, 0x3f, sizeof(Sdis));
	memset(inq, 0, sizeof(inq));
	std::queue<SNode> q;
	q.push(SNode(x, y, z));
	inq[x][y][z] = true;
	Sdis[x][y][z] = 0;
	while (!q.empty())
	{
		SNode from = q.front();
		q.pop();
		INT x = from.x;
		INT y = from.y;
		INT z = from.dir;
		inq[x][y][z] = false;
		INT newx = x + vecx[z];
		INT newy = y + vecy[z];
		INT newz = veco[z];
		if (newx > 0 && newx <= n && newy > 0 && newy <= m && rect[newx][newy])
		{
			for (int i = 0; i < 4; i++)
			{
				if (Sdis[x][y][z] + 1 + cost[newx][newy][newz][i] < Sdis[newx][newy][i])
				{
					Sdis[newx][newy][i] = Sdis[x][y][z] + 1 + cost[newx][newy][newz][i];
					if (!inq[newx][newy][i])
					{
						q.push(SNode(newx, newy, i));
						inq[newx][newy][i] = true;
					}
				}
			}
		}
	}

	INT ans = INF;
	for (int i = 0; i < 4; i++)
		ans = std::min(ans, Sdis[tx][ty][i]);
	return ans;
}

void run()
{
	n = readIn();
	m = readIn();
	q = readIn();
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			rect[i][j] = readIn();

	memset(cost, 0x3f, sizeof(cost));
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			sx = i;
			sy = j;
			for (int k = 0; k < 4; k++)
			{
				ex = i + vecx[k];
				ey = j + vecy[k];
				if (ex > 0 && ex <= n && ey > 0 && ey <= m && rect[ex][ey])
				{
					BFS();
					for (int l = 0; l < 4; l++)
						cost[i][j][k][l] = dis[i + vecx[l]][j + vecy[l]];
				}
			}
		}
	}

	while (q--)
	{
		ex = readIn();
		ey = readIn();
		sx = readIn();
		sy = readIn();
		tx = readIn();
		ty = readIn();
		if (sx == tx && sy == ty)
		{
			printOut(0);
			continue;
		}
		BFS();
		INT ans = INF;
		for (int i = 0; i < 4; i++)
		{
			INT newx = sx + vecx[i];
			INT newy = sy + vecy[i];
			INT newz = i;
			if (dis[newx][newy] < INF)
				ans = std::min(ans, dis[newx][newy] + SPFA(sx, sy, newz));
		}
		if (ans >= INF) printOut(-1);
		else printOut(ans);
	}
}

int main()
{
	run();
	return 0;
}
